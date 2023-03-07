#include "path/PathUtility.hpp"

#include <QDir>
#include <QFile>
#include <wtypes.h>
#include <QDirIterator>
#include <QtCore/qfileinfo.h>

std::string PathUtility::getActiveDirectoryPath()
{
    TCHAR path[MAX_PATH];
    GetModuleFileName(nullptr, path, MAX_PATH);

    int pathLength = wcslen(static_cast<wchar_t*>(path));
    auto wideStringPath = new char[2 * pathLength + 1];
    wcstombs(wideStringPath, static_cast<wchar_t*>(path), 2 * pathLength + 1);
    std::string activeDirectoryPath = wideStringPath;
    delete[] wideStringPath;

    auto lastSectionIndex = activeDirectoryPath.rfind('\\');
    activeDirectoryPath = activeDirectoryPath.substr(0, lastSectionIndex);

    return activeDirectoryPath;
}

bool PathUtility::fileExists(std::string fileName)
{
    return QFile::exists(fileName.c_str());
}

std::string PathUtility::makeAbsolutePath(std::string relativePath)
{
    if (relativePath.at(0) == '/' || relativePath.at(0) == '\\')
        return getActiveDirectoryPath() + relativePath;
    else
        return getActiveDirectoryPath() + '/' + relativePath;
}

bool PathUtility::isRelativePath(std::string path)
{
    QFileInfo fileInfo(path.c_str());
    return fileInfo.isRelative();
}

std::vector<std::string> PathUtility::getListOfSystemDrives()
{
    std::vector<std::string> arrayOfDrives;
    char* szDrives = new char[MAX_PATH]();
    if (GetLogicalDriveStringsA(MAX_PATH, szDrives))
        ;
    for (int i = 0; i < 100; i += 4)
        if (szDrives[i] != (char)0)
            arrayOfDrives.push_back(std::string{szDrives[i], szDrives[i + 1], szDrives[i + 2]});
    delete[] szDrives;
    return arrayOfDrives;
}

std::string PathUtility::getOtherDrivePath()
{
    for (auto driver : getListOfSystemDrives())
    {
        if (driver.find("D") != std::string::npos)
        {
            driver = driver.substr(0, driver.rfind('\\'));
            return driver;
        }
    }
    return "";
}

std::string PathUtility::getImagesFilePath()
{
    for (auto driver : getListOfSystemDrives())
    {
        if (driver.find("D") != std::string::npos)
        {
            driver = driver.substr(0, driver.rfind('\\'));
            return driver + "/images";
        }
    }
    return "";
}

bool PathUtility::getVolumePaths(__in PWCHAR VolumeName, std::string& outputPath)
{
    outputPath = "";
    DWORD CharCount = MAX_PATH + 1;

    auto names = (PWCHAR) new BYTE[(CharCount + 1) * sizeof(WCHAR)];
    if (!names)
        return false;
    memset(names, 0, (CharCount + 1) * sizeof(WCHAR));

    if (!GetVolumePathNamesForVolumeNameW(VolumeName, names, CharCount, &CharCount))
    {
        if (names != NULL)
        {
            delete[] names;
            names = nullptr;
        }
        return false;
    }

    auto driveType = GetDriveType(names);
    if (driveType == DRIVE_REMOVABLE)
    {
        const std::wstring ws = names;
        outputPath = std::string(ws.begin(), ws.end());
        if (names != NULL)
        {
            delete[] names;
            names = nullptr;
        }
        return true;
    }

    if (names != NULL)
    {
        delete[] names;
        names = nullptr;
    }
    return false;
}

std::string PathUtility::getExternalStoragePath()
{
    WCHAR volumeName[MAX_PATH] = L"";
    std::string drivePath = "";
    auto findHandle = FindFirstVolumeW(volumeName, ARRAYSIZE(volumeName));
    if (findHandle != INVALID_HANDLE_VALUE)
    {
        do
        {
            volumeName[wcslen(volumeName) - 1] = L'\0';
            WCHAR deviceName[MAX_PATH] = L"";
            auto CharCount = QueryDosDeviceW(&volumeName[4], deviceName, ARRAYSIZE(deviceName));
            volumeName[wcslen(volumeName)] = L'\\';
            if (CharCount == 0)
                break;

            if (getVolumePaths(volumeName, drivePath))
                break;

            if (!FindNextVolumeW(findHandle, volumeName, ARRAYSIZE(volumeName)))
            {
                if (GetLastError() != ERROR_NO_MORE_FILES)
                    break;
                break;
            }
        } while (true);

        FindVolumeClose(findHandle);
        findHandle = INVALID_HANDLE_VALUE;
    }
    return drivePath;
}

std::string PathUtility::getDirectoryPathFromFullAbsolutePath(std::string fullAbsolutePath)
{
    replace(fullAbsolutePath.begin(), fullAbsolutePath.end(), '\\', '/');
    const auto lastBackSlashIndex = fullAbsolutePath.rfind('/');
    if (std::string::npos != lastBackSlashIndex)
		return fullAbsolutePath.substr(0, lastBackSlashIndex);
	return "";
}
