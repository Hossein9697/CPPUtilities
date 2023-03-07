#ifndef PERFORMANCE_STATISTICS_UTILITY_HPP
#define PERFORMANCE_STATISTICS_UTILITY_HPP

#include <Windows.h>
#include <string>

#include "cpu-usage/CpuUsage.hpp"

typedef BOOL(__stdcall* GetSystemTimesFunction)(LPFILETIME idleTime, LPFILETIME kernelTime, LPFILETIME userTime);

class PerformanceStatisticsUtility
{

public:
    static short getCPUUsage();
    static short getCurrentProcessCPUUsage();
    static double getTotalPhysicalMemory();
    static double getAvailablePhysicalMemory();
    static double getInUsePhysicalMemory();
    static DWORD getCurrentProcessPrivateWorkingSetMemory();
    static DWORD getProcessPrivateWorkingSetMemory(DWORD processID);
    static std::vector<std::string> getInterfacesInformation();

private:
    static void getSystemTimesAddress();
    static std::string getMIBIFROWTypeDescription(DWORD type);
    static std::string getMIBIFROWOperationStatusDescription(DWORD operationStatus);
    static std::string dwordToString(DWORD number);
    static std::string wstringToString(std::wstring data);
    static std::string intToString(int number);
    static std::string addSeperator(std::string value, int count, char seperator);
    static std::string format(const char* data, ...);
    static std::string vformat(const char* data, va_list params);

private:
    static HMODULE kernel;
    static CpuUsage processCpuUsage;
    static GetSystemTimesFunction getSystemTimes;
};

#endif // PERFORMANCE_STATISTICS_UTILITY_HPP
