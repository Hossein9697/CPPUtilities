#include "performance-statistics/memory-private-working-set/AccessWSPrivate.hpp"

#include <Psapi.h>

static DWORD dWorkingSetPages[1024 * 128]; // hold the working set information get from QueryWorkingSet()
static DWORD dPageSize = 0x1000;

int AccessWSPrivate::compare(const void* Val1, const void* Val2)
{
    if (*(PDWORD)Val1 == *(PDWORD)Val2)
        return 0;

    return *(PDWORD)Val1 > *(PDWORD)Val2 ? 1 : -1;
}

DWORD AccessWSPrivate::calculateWSPrivate(DWORD processID)
{
    DWORD dSharedPages = 0;
    DWORD dPrivatePages = 0;
    DWORD dPageTablePages = 0;

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

    if (!hProcess)
        return 0;

    __try
    {
        char szBuffer[MAX_PATH * 4];

        if (!QueryWorkingSet(hProcess, dWorkingSetPages, sizeof(dWorkingSetPages)))
            __leave;

        DWORD dPages = dWorkingSetPages[0];

        qsort(&dWorkingSetPages[1], dPages, sizeof(DWORD), compare);

        for (DWORD i = 1; i <= dPages; i++)
        {
            DWORD dCurrentPageStatus = 0;
            DWORD dCurrentPageAddress;
            DWORD dNextPageAddress;
            DWORD dNextPageFlags;
            DWORD dPageAddress = dWorkingSetPages[i] & 0xFFFFF000;
            DWORD dPageFlags = dWorkingSetPages[i] & 0x00000FFF;

            while (i <= dPages) // iterate all pages
            {
                dCurrentPageStatus++;

                if (i == dPages) // if last page
                    break;

                dCurrentPageAddress = dWorkingSetPages[i] & 0xFFFFF000;
                dNextPageAddress = dWorkingSetPages[i + 1] & 0xFFFFF000;
                dNextPageFlags = dWorkingSetPages[i + 1] & 0x00000FFF;

                // decide whether iterate further or exit(this is non-contiguous page or have different flags)
                if ((dNextPageAddress == (dCurrentPageAddress + dPageSize)) && (dNextPageFlags == dPageFlags))
                {
                    i++;
                }
                else
                    break;
            }

            if ((dPageAddress < 0xC0000000) || (dPageAddress > 0xE0000000))
            {
                if (dPageFlags & 0x100) // this is shared one
                    dSharedPages += dCurrentPageStatus;
                else // private one
                    dPrivatePages += dCurrentPageStatus;
            }
            else
                dPageTablePages += dCurrentPageStatus; // page table region
        }

        DWORD dTotal = dPages * 4;
        DWORD dShared = dSharedPages * 4;
        DWORD WSPrivate = dTotal - dShared;

        return WSPrivate;
    }
    __finally
    {
        CloseHandle(hProcess);
    }
}
