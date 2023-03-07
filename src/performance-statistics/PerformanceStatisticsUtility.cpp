#include "performance-statistics/PerformanceStatisticsUtility.hpp"

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <iphlpapi.h>

#include "performance-statistics/memory-private-working-set/AccessWSPrivate.hpp"

#pragma comment(lib, "IPHLPAPI.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x)   HeapFree(GetProcessHeap(), 0, (x))

HMODULE PerformanceStatisticsUtility::kernel = nullptr;
GetSystemTimesFunction PerformanceStatisticsUtility::getSystemTimes = nullptr;
CpuUsage PerformanceStatisticsUtility::processCpuUsage;

short PerformanceStatisticsUtility::getCPUUsage()
{
    getSystemTimesAddress();

    FILETIME systemIdleFileTime;
    FILETIME systemKernelFileTime;
    FILETIME systemUserFileTime;

    ULARGE_INTEGER systemIdleValue;
    ULARGE_INTEGER systemKernelValue;
    ULARGE_INTEGER systemUserValue;

    static ULARGE_INTEGER systemIdleOldValue;
    static ULARGE_INTEGER systemKernelOldValue;
    static ULARGE_INTEGER systemUserOldValue;

    char usage = 0;

    getSystemTimes(&systemIdleFileTime, &systemKernelFileTime, &systemUserFileTime);

    CopyMemory(&systemIdleValue, &systemIdleFileTime, sizeof(FILETIME));
    CopyMemory(&systemKernelValue, &systemKernelFileTime, sizeof(FILETIME));
    CopyMemory(&systemUserValue, &systemUserFileTime, sizeof(FILETIME));

    usage = (((((systemKernelValue.QuadPart - systemKernelOldValue.QuadPart) + (systemUserValue.QuadPart - systemUserOldValue.QuadPart)) - (systemIdleValue.QuadPart - systemIdleOldValue.QuadPart)) * (100)) / ((systemKernelValue.QuadPart - systemKernelOldValue.QuadPart + 1) + (systemUserValue.QuadPart - systemUserOldValue.QuadPart)));

    systemIdleOldValue.QuadPart = systemIdleValue.QuadPart;
    systemUserOldValue.QuadPart = systemUserValue.QuadPart;
    systemKernelOldValue.QuadPart = systemKernelValue.QuadPart;

    return usage;
}

short PerformanceStatisticsUtility::getCurrentProcessCPUUsage()
{
    return processCpuUsage.getUsage();
}

void PerformanceStatisticsUtility::getSystemTimesAddress()
{
    if (!kernel)
    {
        kernel = LoadLibrary(L"Kernel32.dll");
        if (kernel)
        {
            getSystemTimes = reinterpret_cast<GetSystemTimesFunction>(GetProcAddress(kernel, "GetSystemTimes"));
            if (!getSystemTimes)
            {
                FreeLibrary(kernel);
                kernel = nullptr;
            }
        }
    }
}

double PerformanceStatisticsUtility::getTotalPhysicalMemory()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);

    if (GlobalMemoryStatusEx(&status))
        return status.ullTotalPhys / (1024 * 1024);

    return 0;
}

double PerformanceStatisticsUtility::getAvailablePhysicalMemory()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);

    if (GlobalMemoryStatusEx(&status))
        return status.ullAvailPhys / (1024 * 1024);

    return 0;
}

double PerformanceStatisticsUtility::getInUsePhysicalMemory()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);

    if (GlobalMemoryStatusEx(&status))
        return (status.ullTotalPhys - status.ullAvailPhys) / (1024 * 1024);

    return 0;
}

DWORD PerformanceStatisticsUtility::getCurrentProcessPrivateWorkingSetMemory()
{
    return getProcessPrivateWorkingSetMemory(GetCurrentProcessId());
}

DWORD PerformanceStatisticsUtility::getProcessPrivateWorkingSetMemory(DWORD processID)
{
    return AccessWSPrivate::calculateWSPrivate(processID);
}

std::vector<std::string> PerformanceStatisticsUtility::getInterfacesInformation()
{
    std::vector<std::string> interfacesInformation;

    DWORD size = 0;
    DWORD result = 0;
    unsigned int i, j;

    MIB_IFTABLE* ifTable;
    MIB_IFROW* ifRow;

    ifTable = static_cast<MIB_IFTABLE*>(MALLOC(sizeof(MIB_IFTABLE)));
    if (!ifTable)
        return interfacesInformation;

    size = sizeof(MIB_IFTABLE);
    if (GetIfTable(ifTable, &size, 0) == ERROR_INSUFFICIENT_BUFFER)
    {
        FREE(ifTable);
        ifTable = static_cast<MIB_IFTABLE*>(MALLOC(size));
        if (!ifTable)
            return interfacesInformation;
    }

    if ((result = GetIfTable(ifTable, &size, 0)) == NO_ERROR)
    {
        if (ifTable->dwNumEntries > 0)
        {
            ifRow = static_cast<MIB_IFROW*>(MALLOC(sizeof(MIB_IFROW)));
            if (!ifRow)
            {
                if (ifTable)
                {
                    FREE(ifTable);
                    ifTable = nullptr;
                }
                return interfacesInformation;
            }

            interfacesInformation.push_back("Number of Interface Entries : " + dwordToString(ifTable->dwNumEntries));
            interfacesInformation.push_back("");

            for (i = 0; i < ifTable->dwNumEntries; i++)
            {
                ifRow->dwIndex = ifTable->table[i].dwIndex;
                if ((result = GetIfEntry(ifRow)) == NO_ERROR)
                {
                    interfacesInformation.push_back("Index : " + dwordToString(ifRow->dwIndex));
                    interfacesInformation.push_back("Interface Name [" + dwordToString(i) + "] : " + wstringToString(ifRow->wszName ? ifRow->wszName : L"null"));
                    interfacesInformation.push_back("Description [" + dwordToString(i) + "] : " + std::string(reinterpret_cast<char const*>(ifRow->bDescr), ifRow->dwDescrLen));
                    interfacesInformation.push_back("Index [" + dwordToString(i) + "] : " + dwordToString(ifRow->dwIndex));
                    interfacesInformation.push_back("Type [" + dwordToString(i) + "] : " + getMIBIFROWTypeDescription(ifRow->dwType));
                    interfacesInformation.push_back("The Maximum Transmission Unit (MTU) [" + dwordToString(i) + "] : " + addSeperator(dwordToString(ifRow->dwMtu), 3, '.') + " bytes");
                    interfacesInformation.push_back("Interface Speed [" + dwordToString(i) + "] : " + addSeperator(dwordToString(ifRow->dwSpeed), 3, '.') + " bits per second");

                    std::string physicalAddress = "";
                    for (j = 0; j < ifRow->dwPhysAddrLen; j++)
                        j == ifRow->dwPhysAddrLen - 1 ? physicalAddress += format("%.2X", int(ifRow->bPhysAddr[j])) : physicalAddress += format("%.2X-", int(ifRow->bPhysAddr[j]));
                    interfacesInformation.push_back("Physical Address [" + dwordToString(i) + "] : " + physicalAddress);

                    interfacesInformation.push_back("Administratively Status [" + dwordToString(i) + "] : " + dwordToString(ifRow->dwAdminStatus));
                    interfacesInformation.push_back("Operation Status [" + dwordToString(i) + "] : " + getMIBIFROWOperationStatusDescription(ifRow->dwOperStatus));
                    interfacesInformation.push_back("Last Change From the Last Computer Restart [" + dwordToString(i) + "] : " + dwordToString(ifRow->dwLastChange) + " hundredths of seconds (10^-2 sec)");

                    interfacesInformation.push_back("Number of Octets of Data Received [" + dwordToString(i) + "] : " + dwordToString(ifRow->dwInOctets));
                    interfacesInformation.push_back("Number of Unicast Packets Received [" + dwordToString(i) + "] : " + dwordToString(ifRow->dwInUcastPkts));
                    interfacesInformation.push_back("Number of Non-Unicast Packets Received [" + dwordToString(i) + "] : " + dwordToString(ifRow->dwInNUcastPkts));
                    interfacesInformation.push_back("Number of Incoming Packets That were Discarded (Did Not Have Errors) [" + dwordToString(i) + "] : " + dwordToString(ifRow->dwInDiscards));
                    interfacesInformation.push_back("Number of Incoming Packets That were Discarded (Had Errors) [" + dwordToString(i) + "] : " + dwordToString(ifRow->dwInErrors));
                    interfacesInformation.push_back("Number of Incoming Packets That were Discarded (Unknown Protocol) [" + dwordToString(i) + "] : " + dwordToString(ifRow->dwInUnknownProtos));

                    interfacesInformation.push_back("Number of Octets of Data Sent [" + dwordToString(i) + "] : " + dwordToString(ifRow->dwOutOctets));
                    interfacesInformation.push_back("Number of Unicast Packets Sent [" + dwordToString(i) + "] : " + dwordToString(ifRow->dwOutUcastPkts));
                    interfacesInformation.push_back("Number Non-of Unicast Packets Sent [" + dwordToString(i) + "] : " + dwordToString(ifRow->dwOutNUcastPkts));
                    interfacesInformation.push_back("Number of Outgoing  Packets That were Discarded (Did Not Have Errors) [" + dwordToString(i) + "] : " + dwordToString(ifRow->dwOutDiscards));
                    interfacesInformation.push_back("Number of Outgoing Packets That were Discarded (Had Errors) [" + dwordToString(i) + "] : " + dwordToString(ifRow->dwOutErrors));

                    interfacesInformation.push_back("The Transmit Queue Length [" + dwordToString(i) + "] : " + dwordToString(ifRow->dwOutQLen));
                    interfacesInformation.push_back("");
                }
                else
                {
                    return interfacesInformation;
                }
            }
        }
        else
        {
            return interfacesInformation;
        }
    }

    return interfacesInformation;
}

std::string PerformanceStatisticsUtility::getMIBIFROWTypeDescription(DWORD type)
{

    switch (type)
    {
        case IF_TYPE_OTHER:
            return "Other";
        case IF_TYPE_ETHERNET_CSMACD:
            return "Ethernet";
        case IF_TYPE_ISO88025_TOKENRING:
            return "Token Ring";
        case IF_TYPE_PPP:
            return "PPP";
        case IF_TYPE_SOFTWARE_LOOPBACK:
            return "Software Lookback";
        case IF_TYPE_ATM:
            return "ATM";
        case IF_TYPE_IEEE80211:
            return "IEEE 802.11 Wireless";
        case IF_TYPE_TUNNEL:
            return "Tunnel type encapsulation";
        case IF_TYPE_IEEE1394:
            return "IEEE 1394 Firewire";
        default:
            return "Unknown Type (" + dwordToString(type) + ")";
    }
}

std::string PerformanceStatisticsUtility::getMIBIFROWOperationStatusDescription(DWORD operationStatus)
{
    switch (operationStatus)
    {
        case IF_OPER_STATUS_NON_OPERATIONAL:
            return "Non Operational";
        case IF_OPER_STATUS_UNREACHABLE:
            return "Unreasonable";
        case IF_OPER_STATUS_DISCONNECTED:
            return "Disconnected";
        case IF_OPER_STATUS_CONNECTING:
            return "Connecting";
        case IF_OPER_STATUS_CONNECTED:
            return "Connected";
        case IF_OPER_STATUS_OPERATIONAL:
            return "Operational";
        default:
            return "Unknown Status (" + dwordToString(operationStatus) + ")";
    }
}

std::string PerformanceStatisticsUtility::dwordToString(DWORD number)
{
    std::stringstream stringStream;
    stringStream << int(number);
    return stringStream.str();
}

std::string PerformanceStatisticsUtility::wstringToString(std::wstring data)
{
    return std::string(data.begin(), data.end());
}

std::string PerformanceStatisticsUtility::intToString(int number)
{
    std::stringstream stringStream;
    stringStream << number;
    return stringStream.str();
}

std::string PerformanceStatisticsUtility::addSeperator(std::string value, int count, char seperator)
{
    if (value.length() <= count)
        return value;

    int i = value.length();
    std::string buffer = "";
    auto j = 0;
    do
    {
        buffer.insert(0, value.substr(i--, 1));
        if (j == count && i > -1)
        {
            buffer = seperator + buffer;
            j = 0;
        }
        j++;
    } while (i > -1);
    return buffer;
}

#include <cstdarg>

std::string PerformanceStatisticsUtility::format(const char* data, ...)
{
    va_list ap;
    va_start(ap, data);
    auto buffer = vformat(data, ap);
    va_end(ap);
    return buffer;
}

std::string PerformanceStatisticsUtility::vformat(const char* data, va_list params)
{
    size_t size = 1024;
    char buffer[1024];

    va_list apcopy;
    va_copy(apcopy, params);
    auto needed = vsnprintf(&buffer[0], size, data, params);

    if (needed <= size && needed >= 0)
        return std::string(&buffer[0]);

    std::vector<char> output;
    size = needed;
    output.resize(size);
    needed = vsnprintf(&output[0], size, data, apcopy);
    return std::string(&output[0]);
}
