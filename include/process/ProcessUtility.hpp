#ifndef PROCESS_UTILITY_HPP
#define PROCESS_UTILITY_HPP

#include <map>
#include <string>
#include <vector>
#include <Windows.h>

typedef std::vector<std::pair<DWORD, std::string>> ProcessExecutableInformations;
typedef std::map<DWORD, HANDLE> ProcessInformations;
class ProcessUtility
{

public:
    static bool isProcessActive(std::string processName);
    static bool isProcessActiveAlready(std::string processName);
    static bool killProcess(std::string processName);

    static std::string getCurrentProcessName();

    static void terminateApplicationProcess();
    static bool isApplicationProcessActiveAlready();

    static bool runProcess(std::string execuatableFileName, std::string activeDirectory, DWORD creationFlags, bool waitToEnd);

    static HANDLE getProcessHandle(std::string processName);
    static ProcessInformations getProcessInformations(std::string processName);

    static ProcessExecutableInformations getProcessExecutableInformation();

private:
    static std::string getCurrentModulePath();
    static std::wstring stringToWString(const std::string& data);
    static std::string wstringToString(const std::wstring& data);
    static bool caseInsensitiveCompare(const std::wstring str1, const std::wstring str2);
};

#endif // PROCESS_UTILITY_HPP
