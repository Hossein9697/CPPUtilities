#include "registery/RegistryManager.hpp"

RegistryManager::RegistryManager()
{
}

HKEY RegistryManager::openKey(HKEY rootKey, wchar_t* keyPath) const
{
    HKEY key = nullptr;
    auto error = RegOpenKeyEx(rootKey, keyPath, 0, KEY_READ | KEY_WRITE, &key);
    return key;
}

int RegistryManager::getKey(HKEY key, LPCTSTR keyName) const
{
    DWORD keyValue;
    DWORD size = sizeof(keyValue);
    DWORD type = REG_DWORD;
    auto error = RegQueryValueEx(key, keyName, nullptr, &type, reinterpret_cast<LPBYTE>(&keyValue), &size);

    if (error)
        return -1;

    return keyValue;
}

bool RegistryManager::setKey(HKEY key, LPCTSTR keyName, DWORD keyValue) const
{
    auto error = RegSetValueEx(key, keyName, NULL, REG_DWORD, reinterpret_cast<LPBYTE>(&keyValue), sizeof(DWORD));

    if (error)
        return false;

    return true;
}

bool RegistryManager::setNumberKey(HKEY rootKey, wchar_t* strKey, LPCTSTR keyName, DWORD keyValue) const
{
    auto key = openKey(rootKey, strKey);
    auto error = RegSetValueEx(key, keyName, NULL, REG_DWORD, reinterpret_cast<LPBYTE>(&keyValue), sizeof(DWORD));

    if (error)
        return false;

    RegCloseKey(key);

    return true;
}

bool RegistryManager::setBinaryKey(HKEY rootKey, wchar_t* strKey, LPCTSTR keyName, LPBYTE keyValue) const
{
    auto key = openKey(rootKey, strKey);
    auto error = RegSetValueEx(key, keyName, NULL, REG_BINARY, keyValue, sizeof(DWORD));

    if (error)
        return false;

    RegCloseKey(key);

    return true;
}

bool RegistryManager::setStringKey(HKEY rootKey, wchar_t* keyPath, LPCTSTR keyName, std::string keyValue) const
{
    std::wstring data;
    for (auto i = 0; i < keyValue.length(); ++i)
        data += wchar_t(keyValue[i]);

    WCHAR path[MAX_PATH];
    for (auto i = 0; i < MAX_PATH; i++)
        path[i] = 0;

    for (auto i = 0; i < data.length(); i++)
        path[i] = data[i];

    auto key = openKey(rootKey, keyPath);
    if (!key)
        return false;

    auto error = RegSetValueEx(key, keyName, NULL, REG_SZ, reinterpret_cast<LPBYTE>(path), MAX_PATH);

    if (error)
        return false;

    RegCloseKey(key);

    return true;
}

std::string RegistryManager::getStringKey(HKEY rootKey, wchar_t* keyPath, LPCTSTR keyName) const
{
    wchar_t data[MAX_PATH];
    DWORD size = MAX_PATH;
    DWORD type = REG_SZ;

    auto key = openKey(rootKey, keyPath);
    auto error = RegQueryValueEx(key, keyName, nullptr, &type, reinterpret_cast<LPBYTE>(&data), &size);

    if (error)
        return "";

    RegCloseKey(key);

    std::wstring result(data);
    return std::string(result.begin(), result.end());
}

std::string RegistryManager::getBinaryKey(HKEY rootKey, wchar_t* keyPath, LPCTSTR keyName)
{
    auto data = new BYTE[8000];
    DWORD size = 8000;
    DWORD type = REG_BINARY;

    auto key = openKey(rootKey, keyPath);
    auto error = RegQueryValueEx(key, keyName, nullptr, &type, data, &size);

    if (error)
        return "";

    auto result = BCDToString(data, size * 2);

    RegCloseKey(key);
    delete data;

    return result;
}

LONG RegistryManager::getBinaryKey(HKEY rootKey, wchar_t* keyPath, LPCTSTR keyName, LPBYTE keyValue) const
{
    DWORD size = 8000;
    DWORD type = REG_BINARY;

    auto key = openKey(rootKey, keyPath);
    auto error = RegQueryValueEx(key, keyName, nullptr, &type, keyValue, &size);

    if (error)
        return -1;

    return error;
}

int RegistryManager::getNumberKey(HKEY rootKey, wchar_t* keyPath, LPCTSTR keyName) const
{
    DWORD keyValue;
    DWORD size = sizeof(keyValue);
    DWORD type = REG_DWORD;

    auto key = openKey(rootKey, keyPath);
    auto error = RegQueryValueEx(key, keyName, nullptr, &type, reinterpret_cast<LPBYTE>(&keyValue), &size);

    if (error)
        return -1;

    RegCloseKey(key);

    return keyValue;
}

std::string RegistryManager::BCDToString(const BYTE* buffer, int len, int offset, bool padLeft) const
{
    std::string localString(len, ' ');

    try
    {
        auto start = (((len & 1) == 1) && padLeft) ? 1 : 0;
        for (auto index = start; index < len + start; index++)
        {
            auto iShift = ((index & 1) == 1 ? 0 : 4);
            char ch = (buffer[offset + (index >> 1)] >> iShift) & 0x0F;
            localString[index - start] = ch < 10 ? (ch + '0') : (ch + 'A' - 10);
        }
    }
    catch (std::exception& exp)
    {
        return "";
    }

    return localString;
}
