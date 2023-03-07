#include "compressor/Compressor.hpp"

#include <QuaZip-Qt6-1.3/quazip/JlCompress.h>
#include <Windows.h>

Compressor::Compressor()
{
}

Compressor::~Compressor()
{
}

bool Compressor::compressFile(std::string fileName, std::string compressDirectoryFileName, std::string compressFilePassword, bool deleteOriginalFiles) const
{
    if (fileName.empty())
        return false;

    auto result = JlCompress::compressFile(compressDirectoryFileName.c_str(), fileName.c_str());
    if (deleteOriginalFiles)
        deleteFile(fileName);

    return result;
}

bool Compressor::compressDirectory(FileNames fileNames, std::string compressDirectoryFileName, std::string compressFilePassword, bool deleteOriginalFiles, bool compressInUseFiles /* = true */) const
{
    if (fileNames.empty())
        return true;

    if (JlCompress::compressFiles(compressDirectoryFileName.c_str(), convertFileNamesToQStringList(fileNames)))
    {
        for (auto fileName : fileNames)
        {
            if (deleteOriginalFiles)
                deleteFile(fileName);
        }

        return true;
    }

    return false;
}

bool Compressor::compressDirectory(std::string directoryFileName, std::string filesExtension, std::string compressDirectoryFileName, std::string compressFilePassword, bool deleteOriginalFiles, bool compressInUseFiles /* = true */) const
{
    auto fileNames = getListOfAllFilesInDirectory(directoryFileName, filesExtension);
    if (fileNames.empty())
        return true;

    return compressDirectory(fileNames, compressDirectoryFileName, compressFilePassword, deleteOriginalFiles, compressInUseFiles);
}

FileNames Compressor::getListOfAllFilesInDirectory(std::string directoryFileName, std::string extension /* = "*.*" */) const
{
    FileNames fileNames;
    fileNames.clear();

    WIN32_FIND_DATA findData;
    auto findDataHandle = ::FindFirstFile(stringToWString(directoryFileName + "/" + extension).c_str(), &findData);
    if (findDataHandle != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                fileNames.push_back(directoryFileName + "/" + wstringToString(findData.cFileName));
        } while (::FindNextFile(findDataHandle, &findData));
        ::FindClose(findDataHandle);
    }
    return fileNames;
}

bool Compressor::decompressFile(std::string compressFileName, std::string compressFilePassword, std::string decompressedFileName) const
{
    if (compressFileName.empty())
        return false;

    auto result = JlCompress::extractDir(compressFileName.c_str(), decompressedFileName.c_str());

    if (result.isEmpty())
        return false;
    else
        return true;
}

void Compressor::deleteFile(std::string fileName) const
{
    try
    {
        remove(fileName.c_str());
    }
    catch (std::exception exp)
    {
        // Do Nothing
    }
}

QStringList Compressor::convertFileNamesToQStringList(FileNames fileNames) const
{
    QStringList stringList;
    for (auto fileName : fileNames)
        stringList.push_back(fileName.c_str());
    return stringList;
}

std::wstring Compressor::stringToWString(const std::string& data) const
{
    int length;
    auto stringLength = int(data.length()) + 1;
    length = MultiByteToWideChar(CP_ACP, 0, data.c_str(), stringLength, 0, 0);
    auto wideString = new wchar_t[length];
    MultiByteToWideChar(CP_ACP, 0, data.c_str(), stringLength, wideString, length);
    std::wstring wideStringData(wideString);
    delete[] wideString;
    return wideStringData;
}

std::string Compressor::wstringToString(std::wstring data) const
{
    return std::string(data.begin(), data.end());
}

std::string Compressor::getFileNameFromPath(std::string path) const
{
    return {find_if(path.rbegin(), path.rend(), [](char c)
                    { return c == '/' || c == '\\'; })
                .base(),
            path.end()};
}
