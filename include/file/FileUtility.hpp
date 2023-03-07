#ifndef FILE_UTILITY_HPP
#define FILE_UTILITY_HPP

#include <string>
#include <vector>

#define ARCHIVE_APPLICATION_DATA_DATE_SEPARATOR        "-D"
#define ARCHIVE_APPLICATION_DATA_TIME_SEPARATOR        "-T"
#define ARCHIVE_APPLICATION_DATA_TERMINAL_ID_SEPARATOR "I"

typedef std::vector<std::string> FileNames;

class FileUtility
{

public:
    static bool fileExists(std::string fileName);
    static bool directoryExists(std::string fileName);
    static std::string getDirectoryPathFromFullAbsolutePath(std::string fullAbsolutePath);
    static std::string getFileNameFromPath(std::string path);
    static std::string getFileNameWithoutExtension(std::string path);
    static bool copyFile(std::string source, std::string destination);
    static bool moveFile(std::string source, std::string destination);
    static bool copyDirectory(std::string source, std::string destination, std::string extension = "*.*");
    static bool makeDirectory(std::string path);
    static bool removeFile(std::string path);
    static bool removeDirectory(std::string path);
    static bool removeFilesInDirectory(std::string path, std::string extension = "*.*");
    static bool renameDirectory(std::string directory, std::string newDirectory);
    static bool renameFile(std::string fileName, std::string newFileName);
    static FileNames getListOfAllSubDirectoriesInDirectory(std::string directoryFileName);
    static FileNames getListOfAllFilesInDirectory(std::string directoryFileName, std::string extension = "*.*");
    static FileNames getListOfAllFilesInDirectoryAndSubDirectories(std::string directoryFileName, std::string extension = "*.*");
    static int getFileSize(std::string path);
    static void removeEmptyFolders(std::string directory);

private:
    static std::wstring stringToWstring(const std::string& data);
    static std::string wstringToString(std::wstring data);
};

#endif // FILE_UTILITY_HPP
