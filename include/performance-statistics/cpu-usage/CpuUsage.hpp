#ifndef CPU_USAGE_HPP
#define CPU_USAGE_HPP

/********************************************************************************************************************************************
 * Class Information
 * Returns The Percent Of The CPU That The Process Has Used Since The Last Time The Method (getUsage()) Was Called.
 * NOTE :
 * If There Is Not Enough Information, -1 Is Returned.
 * If The Method Is Recalled To Quickly, The Previous Value Is Returned.
 *********************************************************************************************************************************************/

#include <windows.h>
#include <string>
#include <vector>
#include <memory>

class CpuUsage
{

public:
    CpuUsage();
    explicit CpuUsage(HANDLE processHandle);

    short getUsage();

private:
    void clearFileTimes();
    void clearControlMembers();
    ULONGLONG subtractTimes(const FILETIME& firstFileTime, const FILETIME& secondFileTime);
    bool enoughTimePassed() const;
    bool isFirstRun() const;

private:
    FILETIME previousSystemKernelFileTime;
    FILETIME previousSystemUserFileTime;
    FILETIME previousProcessKernelFileTime;
    FILETIME previousProcessUserFileTime;

    short cpuUsage;
    ULONGLONG lastRun;
    volatile LONG runCount;

    HANDLE processHandle;
};

typedef std::vector<CpuUsage*> CpuUsagesPointers;
typedef std::vector<std::unique_ptr<CpuUsage>> CpuUsages;

#endif // CPU_USAGE_HPP