#if !defined(AFX_HARDDISKMANAGER_H__27F8E542_FA4A_43FF_B29D_59BCD13E31C3__INCLUDED_)
#define AFX_HARDDISKMANAGER_H__27F8E542_FA4A_43FF_B29D_59BCD13E31C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <string>

#include "ProcessDiskInformation.hpp"

class HardDiskManager
{

public:
    HardDiskManager();
    virtual ~HardDiskManager();

    bool checkFreeSpace(std::wstring directoryName);

    DWORD64 getFreeBytesAvailable(void) const;
    DWORD64 getTotalNumberOfBytes(void) const;
    DWORD64 getTotalNumberOfFreeBytes(void) const;

    double getFreeGBytesAvailable(void) const;
    double getTotalNumberOfGBytes(void) const;
    double getTotalNumberOfFreeGBytes(void) const;

    std::vector<std::string> toString();

private:
    std::string wstringToString(std::wstring data);
    std::string doubleToString(double number);
    std::string dword64oString(DWORD64 number);

private:
    std::wstring directoryName;
    ULARGE_INTEGER freeBytesAvailable;
    ULARGE_INTEGER totalNumberOfBytes;
    ULARGE_INTEGER totalNumberOfFreeBytes;
};

#endif // !defined(AFX_HARDDISKMANAGER_H__27F8E542_FA4A_43FF_B29D_59BCD13E31C3__INCLUDED_)
