#include "process//ProcessUtility.hpp"

#include <exception>
#include <algorithm>
#include <Tlhelp32.h>

#include "string/StringUtility.hpp"
#include "convertor/type/TypeConvertor.hpp"

bool ProcessUtility::isProcessActive(std::string processName)
{
    auto processWName = TypeConvertor::stringToWString(processName);

    HANDLE processSnapshotHandles;
    PROCESSENTRY32 processEntry32;

    // Take A Snapshot Of All Processes In The System
    processSnapshotHandles = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (processSnapshotHandles == INVALID_HANDLE_VALUE)
        return false;

    // Set The Size Of The Structure Before Using It
    processEntry32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve Information About The First Process And Exit If Unsuccessful
    if (!Process32First(processSnapshotHandles, &processEntry32))
    {
        CloseHandle(processSnapshotHandles); // Must Clean Up The Snapshot Object
        return false;
    }

    // Now Walk The Snapshot Of Processes And Display Information About Each Process In Turn
    do
    {
        if (!_wcsicmp(processWName.c_str(), processEntry32.szExeFile))
        {
            CloseHandle(processSnapshotHandles); // Must Clean Up The Snapshot Object
            return true;
        }

    } while (Process32Next(processSnapshotHandles, &processEntry32));

    CloseHandle(processSnapshotHandles); // Must Clean Up The Snapshot Object

    return false;
}

bool ProcessUtility::isProcessActiveAlready(std::string processName)
{
    auto processExistenceCount = false;
    auto processWName = TypeConvertor::stringToWString(processName);

    HANDLE processSnapshotHandles;
    PROCESSENTRY32 processEntry32;

    // Take A Snapshot Of All Processes In The System
    processSnapshotHandles = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (processSnapshotHandles == INVALID_HANDLE_VALUE)
        return false;

    // Set The Size Of The Structure Before Using It
    processEntry32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve Information About The First Process And Exit If Unsuccessful
    if (!Process32First(processSnapshotHandles, &processEntry32))
    {
        CloseHandle(processSnapshotHandles); // Must Clean Up The Snapshot Object
        return false;
    }

    // Now Walk The Snapshot Of Processes And Display Information About Each Process In Turn
    do
    {
        if (!_wcsicmp(processWName.c_str(), processEntry32.szExeFile))
        {
            if (processExistenceCount)
            {
                // With processExistenceCount We Skip First Match And If We Find It Again Its Mean We Have Two Armaghan Active
                CloseHandle(processSnapshotHandles); // Must Clean Up The Snapshot Object
                return true;
            }

            // First Match Found, Probably The Current Process!
            processExistenceCount = true;
        }

    } while (Process32Next(processSnapshotHandles, &processEntry32));

    CloseHandle(processSnapshotHandles); // Must Clean Up The Snapshot Object

    return false;
}

bool ProcessUtility::killProcess(std::string processName)
{
    auto processWName = TypeConvertor::stringToWString(processName);

    // Get Snapshot of Process
    auto processSnapshotHandles = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);

    PROCESSENTRY32 processEntry32;
    processEntry32.dwSize = sizeof(processEntry32);

    // Find Process
    auto found = Process32First(processSnapshotHandles, &processEntry32);
    while (found)
    {
        if (_wcsicmp(processEntry32.szExeFile, processWName.c_str()) == 0)
        {
            auto processHandle = OpenProcess(PROCESS_TERMINATE, 0, DWORD(processEntry32.th32ProcessID));
            if (processHandle != nullptr)
            {
                auto result = TerminateProcess(processHandle, 9);
                CloseHandle(processHandle);
                if (!result)
                    return false;
            }
        }

        found = Process32Next(processSnapshotHandles, &processEntry32);
    }

    CloseHandle(processSnapshotHandles);
    return true;
}

std::string ProcessUtility::getCurrentProcessName()
{
    return StringUtility::getBaseNameFromFileName(getCurrentModulePath());
}

std::string ProcessUtility::getCurrentModulePath()
{
    TCHAR moduleFileName[MAX_PATH + 1];
    GetModuleFileName(nullptr, moduleFileName, MAX_PATH + 1);
    return TypeConvertor::wstringToString(std::wstring(moduleFileName));
}

void ProcessUtility::terminateApplicationProcess()
{
    // exit(0);
    // killProcess(getCurrentProcessName());
    system(std::string("taskkill /f /im " + getCurrentProcessName()).c_str());
}

bool ProcessUtility::isApplicationProcessActiveAlready()
{
    return isProcessActiveAlready(getCurrentProcessName());
}

bool ProcessUtility::runProcess(std::string execuatableFileName, std::string activeDirectory, DWORD creationFlags, bool waitToEnd)
{
    PROCESS_INFORMATION ProcessInformation;
    STARTUPINFO startupInformation = {0, nullptr, nullptr, nullptr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, nullptr, nullptr, nullptr, nullptr};
    startupInformation.cb = sizeof(STARTUPINFO);
    if (!::CreateProcess(stringToWString(execuatableFileName).c_str(), nullptr, nullptr, nullptr, FALSE, creationFlags | CREATE_NEW_CONSOLE, nullptr, stringToWString(activeDirectory).c_str(), &startupInformation, &ProcessInformation))
    {
        LPVOID messageBuffer = nullptr;
        auto lastError = GetLastError();
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, lastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPTSTR>(&messageBuffer), 0, nullptr);
        auto error(static_cast<LPWSTR>(messageBuffer));
        return false;
    }

    if (waitToEnd)
        WaitForSingleObject(ProcessInformation.hProcess, INFINITE);

    return true;
}

std::wstring ProcessUtility::stringToWString(const std::string& data)
{
    int length;
    auto stringLength = int(data.length()) + 1;
    length = MultiByteToWideChar(CP_ACP, 0, data.c_str(), stringLength, nullptr, 0);
    auto wideString = new wchar_t[length];
    MultiByteToWideChar(CP_ACP, 0, data.c_str(), stringLength, wideString, length);
    std::wstring wideStringData(wideString);
    delete[] wideString;
    return wideStringData;
}

HANDLE ProcessUtility::getProcessHandle(std::string processName)
{
    auto processWName = stringToWString(processName);

    PROCESSENTRY32 processEntry32;
    processEntry32.dwSize = sizeof(PROCESSENTRY32);

    auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &processEntry32) == TRUE)
    {
        while (Process32Next(snapshot, &processEntry32) == TRUE)
        {
            // if (stricmp(processEntry32.szExeFile, "target.exe") == 0)
            if (caseInsensitiveCompare(processEntry32.szExeFile, processWName))
            {
                // HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processEntry32.th32ProcessID);
                //  Do stuff..
                CloseHandle(snapshot);
                return OpenProcess(PROCESS_ALL_ACCESS, FALSE, processEntry32.th32ProcessID);
                // CloseHandle(hProcess);
            }
        }
    }

    CloseHandle(snapshot);

    return nullptr;
}
ProcessInformations ProcessUtility::getProcessInformations(std::string processName)
{
    ProcessInformations processInformations;
    auto processWName = stringToWString(processName);

    PROCESSENTRY32 processEntry32;
    processEntry32.dwSize = sizeof(PROCESSENTRY32);

    auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &processEntry32) == TRUE)
    {
        while (Process32Next(snapshot, &processEntry32) == TRUE)
        {
            // if (stricmp(processEntry32.szExeFile, "target.exe") == 0)
            if (caseInsensitiveCompare(processEntry32.szExeFile, processWName))
            {
                // HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processEntry32.th32ProcessID);
                //  Do stuff..
                processInformations.insert(std::pair<DWORD, HANDLE>(processEntry32.th32ProcessID, OpenProcess(PROCESS_ALL_ACCESS, FALSE, processEntry32.th32ProcessID)));
                // CloseHandle(hProcess);
            }
        }
    }

    CloseHandle(snapshot);

    return processInformations;
}

ProcessExecutableInformations ProcessUtility::getProcessExecutableInformation()
{
    ProcessExecutableInformations processExecutableInformations;

    // Get Snapshot of Process
    auto processSnapshotHandles = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);

    PROCESSENTRY32 processEntry32;
    processEntry32.dwSize = sizeof(processEntry32);

    // Find Process
    auto found = Process32First(processSnapshotHandles, &processEntry32);
    while (found)
    {
        processExecutableInformations.push_back(make_pair(processEntry32.th32ProcessID, wstringToString(processEntry32.szExeFile)));
        found = Process32Next(processSnapshotHandles, &processEntry32);
    }

    CloseHandle(processSnapshotHandles);
    return processExecutableInformations;
}
std::string ProcessUtility::wstringToString(const std::wstring& data)
{
    return std::string(data.begin(), data.end());
}

bool ProcessUtility::caseInsensitiveCompare(const std::wstring str1, const std::wstring str2)
{
    auto str1Temp(str1);
    auto str2Temp(str2);
    transform(str1Temp.begin(), str1Temp.end(), str1Temp.begin(), ::tolower);
    transform(str2Temp.begin(), str2Temp.end(), str2Temp.begin(), ::tolower);
    return (str1Temp == str2Temp);
}
