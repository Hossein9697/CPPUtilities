#pragma once

#include <string>
#include <vector>
#include <memory>

#include "ProgressBar.hpp"

#define FILE_SERVER_PASSWORD  "Btm1398"
#define SERVER_DIR_PATH       "/in_file/"
#define SERVER_ROOT_DIR_PATH  "logs/rahsam/"
#define FILE_SERVER_USER_NAME "btm"
#define FILE_SERVER_PASSWORD  "Btm1398"

typedef std::vector<std::string> FileNames;

class FileTransferUtility
{
public:
    static bool uploadFile(const std::string& sourcePath, const std::string& url, std::string& error, bool useSSL = true, std::shared_ptr<ProgressBar> bar = nullptr);
    static bool downloadFile(const std::string& destinationPath, const std::string& url, std::string& error, bool useSSL = true, std::shared_ptr<ProgressBar> bar = nullptr);
    static bool getDirectoryInformation(std::string reportFileName, std::string directory, std::string url, std::string& error);
    static bool checkConnection(const std::string& ip, const std::string& port, std::string& error);
    static bool checkConnection(const std::string& url, std::string& error);

    static std::string getDestinationFilePath(std::string fileName, std::string destinationDirectory, std::string scenarioNumber, std::string terminalId);
    static std::string getFileDate(std::string fileName);

private:
    static size_t curlWriteInFileCallbackFunction(void* ptr, size_t size, size_t nmemb, void* data);
};