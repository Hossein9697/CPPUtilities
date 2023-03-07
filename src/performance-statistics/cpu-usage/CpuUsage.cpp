#include <windows.h>
#include "performance-statistics/cpu-usage/CpuUsage.hpp"

CpuUsage::CpuUsage()
{
    clearFileTimes();
    clearControlMembers();
    processHandle = nullptr;
}

CpuUsage::CpuUsage(HANDLE processHandle)
{
    clearFileTimes();
    clearControlMembers();
    this->processHandle = processHandle;
}

void CpuUsage::clearFileTimes()
{
    ZeroMemory(&previousSystemKernelFileTime, sizeof(FILETIME));
    ZeroMemory(&previousSystemUserFileTime, sizeof(FILETIME));

    ZeroMemory(&previousProcessKernelFileTime, sizeof(FILETIME));
    ZeroMemory(&previousProcessUserFileTime, sizeof(FILETIME));
}

void CpuUsage::clearControlMembers()
{
    cpuUsage = -1;
    lastRun = 0;
    runCount = 0;
}

short CpuUsage::getUsage()
{
    // create A Local Copy To Protect Against Race Conditions In Setting The Members
    auto localCpuUsage = cpuUsage;
    if (InterlockedIncrement(&runCount) == 1)
    {
        // If This Is Called Too Often, The Measurement Itself Will Greatly Affect The Results.

        if (!enoughTimePassed())
        {
            InterlockedDecrement(&runCount);
            return localCpuUsage;
        }

        FILETIME systemIdleFileTime, systemKernelFileTime, systemUserFileTime;
        FILETIME processCreationFileTime, processExitFileTime, processKernelFileTime, processUserFileTime;

        if (!GetSystemTimes(&systemIdleFileTime, &systemKernelFileTime, &systemUserFileTime) || !GetProcessTimes(processHandle ? processHandle : GetCurrentProcess(), &processCreationFileTime, &processExitFileTime, &processKernelFileTime, &processUserFileTime))
        {
            InterlockedDecrement(&runCount);
            return localCpuUsage;
        }

        if (!isFirstRun())
        {
            // CPU Usage Is Calculated By Getting The Total Amount Of Time The System Has Operated Since The Last Measurement (Made Up Of Kernel + User) And The Total Amount Of Time The Process Has Run (Kernel + User).
            auto systemKernelFileTimeDifference = subtractTimes(systemKernelFileTime, previousSystemKernelFileTime);
            auto systemUserFileTimeDifference = subtractTimes(systemUserFileTime, previousSystemUserFileTime);

            auto processKernelFileTimeDifference = subtractTimes(processKernelFileTime, previousProcessKernelFileTime);
            auto processUserFileTimeDifference = subtractTimes(processUserFileTime, previousProcessUserFileTime);

            auto totalSystemDifference = systemKernelFileTimeDifference + systemUserFileTimeDifference;
            auto totalProcessDifference = processKernelFileTimeDifference + processUserFileTimeDifference;

            if (totalSystemDifference > 0)
                cpuUsage = short((100.0 * totalProcessDifference) / totalSystemDifference);
        }

        previousSystemKernelFileTime = systemKernelFileTime;
        previousSystemUserFileTime = systemUserFileTime;
        previousProcessKernelFileTime = processKernelFileTime;
        previousProcessUserFileTime = processUserFileTime;

        lastRun = GetTickCount64();

        localCpuUsage = cpuUsage;
    }

    InterlockedDecrement(&runCount);

    return localCpuUsage;
}

ULONGLONG CpuUsage::subtractTimes(const FILETIME& firstFileTime, const FILETIME& secondFileTime)
{
    LARGE_INTEGER firstFileTimeLargeInteger, secondFileTimeLargeInteger;

    firstFileTimeLargeInteger.LowPart = firstFileTime.dwLowDateTime;
    firstFileTimeLargeInteger.HighPart = firstFileTime.dwHighDateTime;

    secondFileTimeLargeInteger.LowPart = secondFileTime.dwLowDateTime;
    secondFileTimeLargeInteger.HighPart = secondFileTime.dwHighDateTime;

    return firstFileTimeLargeInteger.QuadPart - secondFileTimeLargeInteger.QuadPart;
}

bool CpuUsage::enoughTimePassed() const
{
    const auto minElapsedMS = 250; // Milli Seconds
    auto currentTickCount = GetTickCount64();
    return (currentTickCount - lastRun) > minElapsedMS;
}

bool CpuUsage::isFirstRun() const
{
    return lastRun == 0;
}
