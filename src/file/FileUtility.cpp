#include "file/FileUtility.hpp"

#include <Windows.h>

#include <QDir>
#include <QDirIterator>
#include <QFile>

bool FileUtility::fileExists(std::string fileName)
{
    return QFile::exists(fileName.c_str());
}

bool FileUtility::directoryExists(std::string fileName)
{
    return QDir().exists(fileName.c_str());
}

std::string FileUtility::getDirectoryPathFromFullAbsolutePath(std::string fullAbsolutePath)
{
    replace(fullAbsolutePath.begin(), fullAbsolutePath.end(), '\\', '/');
    const auto lastBackSlashIndex = fullAbsolutePath.rfind('/');
    if (std::string::npos != lastBackSlashIndex)
    {
        return fullAbsolutePath.substr(0, lastBackSlashIndex);
    }
    return "";
}

std::string FileUtility::getFileNameFromPath(std::string path)
{
    return {find_if(path.rbegin(), path.rend(), [](char c)
                    { return c == '/' || c == '\\'; })
                .base(),
            path.end()};
}

std::string FileUtility::getFileNameWithoutExtension(std::string path)
{
    return path.substr(0, path.find_last_of("."));
}

bool FileUtility::copyFile(std::string source, std::string destination)
{
    auto directory = getDirectoryPathFromFullAbsolutePath(destination);
    if (!directoryExists(directory))
    {
        makeDirectory(directory);
    }
    return QFile::copy(source.c_str(), destination.c_str());
}

bool FileUtility::moveFile(std::string source, std::string destination)
{
    if (copyFile(source, destination))
    {
        return removeFile(source);
    }
    return false;
}

bool FileUtility::copyDirectory(std::string source, std::string destination, std::string extension)
{
    for (auto currentFile : getListOfAllFilesInDirectoryAndSubDirectories(source, extension))
    {
        if (!copyFile(currentFile, destination + "/" + getFileNameFromPath(currentFile)))
        {
            return false;
        }
    }
    return true;
}

bool FileUtility::makeDirectory(std::string path)
{
    return QDir().mkpath(path.c_str());
}

bool FileUtility::removeFile(std::string path)
{
    if (remove(path.c_str()) != 0)
    {
        return false;
    }
    return true;
}

bool FileUtility::removeDirectory(std::string path)
{
    QDir directory(path.c_str());
    return directory.removeRecursively();
}

bool FileUtility::removeFilesInDirectory(std::string path, std::string extension)
{
    for (auto currentFile : getListOfAllFilesInDirectoryAndSubDirectories(path, extension))
    {
        if (!removeFile(currentFile))
        {
            return false;
        }
    }
    return true;
}

bool FileUtility::renameDirectory(std::string directory, std::string newDirectory)
{
    QDir currentDirectory(directory.c_str());
    return currentDirectory.rename(directory.c_str(), newDirectory.c_str());
}

bool FileUtility::renameFile(std::string fileName, std::string newFileName)
{
    return QFile::rename(fileName.c_str(), newFileName.c_str());
}

FileNames FileUtility::getListOfAllSubDirectoriesInDirectory(std::string directoryFileName)
{
    FileNames fileNames;
    fileNames.clear();

    QDirIterator it(directoryFileName.c_str(), QDir::Dirs | QDir::NoSymLinks /* | QDir::Hidden */ | QDir::NoDotAndDotDot);
    while (it.hasNext())
    {
        fileNames.push_back(it.next().toStdString());
    }

    return fileNames;
}

FileNames FileUtility::getListOfAllFilesInDirectory(std::string directoryFileName, std::string extension /* = "*.*" */)
{
    FileNames fileNames;
    fileNames.clear();

    WIN32_FIND_DATA findData;
    auto findDataHandle = ::FindFirstFile(stringToWstring(directoryFileName + "/" + extension).c_str(), &findData);
    if (findDataHandle != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                fileNames.push_back(directoryFileName + "/" + wstringToString(findData.cFileName));
            }
        } while (::FindNextFile(findDataHandle, &findData));
        ::FindClose(findDataHandle);
    }
    return fileNames;
}

FileNames FileUtility::getListOfAllFilesInDirectoryAndSubDirectories(const std::string directoryFileName, std::string extension /* = "*.*" */)
{
    FileNames fileNames;
    fileNames.clear();

    QDirIterator it(directoryFileName.c_str(), QStringList() << extension.c_str(), QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        fileNames.push_back(it.next().toStdString());
    }

    return fileNames;
}

std::wstring FileUtility::stringToWstring(const std::string& data)
{
    int length;
    auto stringLength = int(data.length()) + 1;
    length = MultiByteToWideChar(CP_ACP, 0, data.c_str(), stringLength, 0, 0);
    auto widestring = new wchar_t[length];
    MultiByteToWideChar(CP_ACP, 0, data.c_str(), stringLength, widestring, length);
    std::wstring widestringData(widestring);
    delete[] widestring;
    return widestringData;
}

std::string FileUtility::wstringToString(std::wstring data)
{
    return std::string(data.begin(), data.end());
}

int FileUtility::getFileSize(std::string path)
{
    return QFileInfo(path.c_str()).size();
}

void FileUtility::removeEmptyFolders(std::string directory)
{
    QDir dir(directory.c_str());
    QStringList entries = dir.entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    foreach (QString entry, entries)
    {
        QDir folder(dir.path() + "/" + entry);
        QFileInfo fileInfo(folder.path());

        if (fileInfo.isDir() && folder.entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot).isEmpty())
        {
            folder.removeRecursively();
        }
        else
        {
            removeEmptyFolders(fileInfo.filePath().toStdString());
        }
    }
    dir.rmdir(dir.absolutePath());
}
