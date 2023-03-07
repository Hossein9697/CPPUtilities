#ifndef SERVICE_UTILITY_HPP
#define SERVICE_UTILITY_HPP

#include <Windows.h>

#include <string>

class ServiceUtility
{

public:
    static bool isServiceExists(const wchar_t* serviceName);
    static int getServiceStatus(const wchar_t* serviceName);
    static bool startService(const wchar_t* serviceName);
    static bool stopService(const wchar_t* serviceName);

private:
    static bool stopDependentServices(SC_HANDLE serviceHandle);
};

#endif // SERVICE_UTILITY_HPP
