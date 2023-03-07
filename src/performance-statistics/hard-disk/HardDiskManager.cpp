#include "performance-statistics/hard-disk/HardDiskManager.hpp"

#include <sstream>

HardDiskManager::HardDiskManager()
{
    directoryName.clear();
    // Bytes Available To Caller
    freeBytesAvailable.QuadPart = 0L;
    // Bytes On Disk
    totalNumberOfBytes.QuadPart = 0L;
    // Free Bytes On Disk
    totalNumberOfFreeBytes.QuadPart = 0L;
}

HardDiskManager::~HardDiskManager()
{
}

bool HardDiskManager::checkFreeSpace(std::wstring directoryName)
{
    this->directoryName = directoryName;

    if (!GetDiskFreeSpaceEx(
            directoryName.c_str(),
            &freeBytesAvailable,      // Bytes Available To Caller
            &totalNumberOfBytes,      // Bytes On Disk
            &totalNumberOfFreeBytes)) // Free Bytes On Disk
        return false;

    return true;
}

DWORD64 HardDiskManager::getFreeBytesAvailable(void) const
{
    return freeBytesAvailable.QuadPart;
}

DWORD64 HardDiskManager::getTotalNumberOfBytes(void) const
{
    return totalNumberOfBytes.QuadPart;
}

DWORD64 HardDiskManager::getTotalNumberOfFreeBytes(void) const
{
    return totalNumberOfFreeBytes.QuadPart;
}

double HardDiskManager::getFreeGBytesAvailable(void) const
{
    return static_cast<double>(static_cast<signed __int64>(freeBytesAvailable.QuadPart) / 1.0e9);
}

double HardDiskManager::getTotalNumberOfGBytes(void) const
{
    return static_cast<double>(static_cast<signed __int64>(totalNumberOfBytes.QuadPart) / 1.0e9);
}

double HardDiskManager::getTotalNumberOfFreeGBytes(void) const
{
    return static_cast<double>(static_cast<signed __int64>(totalNumberOfFreeBytes.QuadPart) / 1.0e9);
}

std::vector<std::string> HardDiskManager::toString()
{
    std::vector<std::string> information;
    // information.push_back("Directory : " + wstringToString(directoryName));
    information.push_back("Free Bytes Available : " + doubleToString(getFreeGBytesAvailable()) + " GB");
    information.push_back("Total Number Of Bytes : " + doubleToString(getTotalNumberOfGBytes()) + " GB");
    information.push_back("Total Number Of Free Bytes : " + doubleToString(getTotalNumberOfFreeGBytes()) + " GB");
    return information;
}

std::string HardDiskManager::wstringToString(std::wstring data)
{
    return std::string(data.begin(), data.end());
}

std::string HardDiskManager::doubleToString(double number)
{
    std::stringstream stringStream;
    stringStream << double(number);
    return stringStream.str();
}

std::string HardDiskManager::dword64oString(DWORD64 number)
{
    std::stringstream stringStream;
    stringStream << DWORD64(number);
    return stringStream.str();
}
