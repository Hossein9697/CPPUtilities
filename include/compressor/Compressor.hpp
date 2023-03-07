#ifndef COMPRESSOR_HPP
#define COMPRESSOR_HPP

#include <string>
#include <vector>
#include <QStringList>

typedef std::vector<std::string> FileNames;

class Compressor
{

public:
    Compressor();
    ~Compressor();

    bool compressFile(std::string fileName, std::string compressDirectoryFileName, std::string compressFilePassword, bool deleteOriginalFiles) const;
    bool compressDirectory(FileNames fileNames, std::string compressDirectoryFileName, std::string compressFilePassword, bool deleteOriginalFiles, bool compressInUseFiles = true) const;
    bool compressDirectory(std::string directoryFileName, std::string filesExtension, std::string compressDirectoryFileName, std::string compressFilePassword, bool deleteOriginalFiles, bool compressInUseFiles = true) const;

    bool decompressFile(std::string compressFileName, std::string compressFilePassword, std::string decompressFileName) const;

private:
    void deleteFile(std::string fileName) const;
    QStringList convertFileNamesToQStringList(FileNames fileNames) const;
    FileNames getListOfAllFilesInDirectory(std::string directoryFileName, std::string extension = "*.*") const;
    std::wstring stringToWString(const std::string& data) const;
    std::string wstringToString(std::wstring data) const;
    std::string getFileNameFromPath(std::string path) const;
};

#endif // COMPRESSOR_HPP
