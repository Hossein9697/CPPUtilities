#ifndef REGISTRY_MANAGER_HPP
#define REGISTRY_MANAGER_HPP

#include <windows.h>
#include <iostream>

using std::cout;
using std::endl;

class RegistryManager
{
public:
    RegistryManager();

    HKEY openKey(HKEY rootKey, wchar_t* keyPath) const;
    int getKey(HKEY key, LPCTSTR keyName) const;
    bool setKey(HKEY key, LPCTSTR keyName, DWORD keyValue) const;

    std::string getStringKey(HKEY rootKey, wchar_t* keyPath, LPCTSTR keyName) const;
    int getNumberKey(HKEY rootKey, wchar_t* keyPath, LPCTSTR keyName) const;
    std::string getBinaryKey(HKEY rootKey, wchar_t* keyPath, LPCTSTR keyName);
    LONG getBinaryKey(HKEY rootKey, wchar_t* keyPath, LPCTSTR keyName, LPBYTE keyValue) const;

    bool setNumberKey(HKEY rootKey, wchar_t* keyPath, LPCTSTR keyName, DWORD keyValue) const;
    bool setBinaryKey(HKEY rootKey, wchar_t* keyPath, LPCTSTR keyName, LPBYTE keyValue) const;
    bool setStringKey(HKEY rootKey, wchar_t* keyPath, LPCTSTR keyName, std::string keyValue) const;

private:
    std::string BCDToString(const BYTE* buffer, int len, int offset = 0, bool padLeft = false) const;
};

#endif REGISTRY_MANAGER_HPP