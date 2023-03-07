#ifndef PATH_UTILITY_HPP
#define PATH_UTILITY_HPP

#include <string>
#include <vector>
#include <Windows.h>

typedef std::vector<std::string> FileNames;

class PathUtility
{

public:
    static std::string getActiveDirectoryPath();
    static bool fileExists(std::string fileName);
    static std::string makeAbsolutePath(std::string relativePath);
    static bool isRelativePath(std::string path);
    static std::vector<std::string> getListOfSystemDrives();
    static std::string getOtherDrivePath();
    static std::string getImagesFilePath();
    static std::string getExternalStoragePath();
    static std::string getDirectoryPathFromFullAbsolutePath(std::string fullAbsolutePath);

private:
    static bool getVolumePaths(__in PWCHAR VolumeName, std::string& outputPath);
};

#endif // PATH_UTILITY_HPP
