#include "file-transfer/FileTransferUtility.hpp"

#include "file/FileUtility.hpp"
#include "string/StringUtility.hpp"
#include <sys/stat.h>

bool FileTransferUtility::uploadFile(const std::string& sourcePath, const std::string& url, std::string& error, bool useSSL, std::shared_ptr<ProgressBar> bar)
{
    FILE* file;
    file = fopen(sourcePath.c_str(), "rb");

    if (!file)
    {
        error = "Can not open source file";
        return false;
    }
    struct stat fileInformation;

    if (fstat(fileno(file), &fileInformation) != 0)
    {
        error = "Can not get source file information";
        return false;
    }

    if (url.empty())
    {
        error = "Url is empty - URL : " + std::string(StringUtility::replaceSubString(url, FILE_SERVER_PASSWORD, "******"));
        return false;
    }

    CURL* curl;
    curl_global_init(CURL_GLOBAL_ALL);

    auto curlResultCode = CURLE_FAILED_INIT;
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, file);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, curl_off_t(fileInformation.st_size));
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curl, CURLOPT_FTP_CREATE_MISSING_DIRS, CURLFTP_CREATE_DIR_RETRY);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3600L);
    }

    if (useSSL)
    {
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }

    if (bar)
    {
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, ProgressBar::xferinfo);
        curl_easy_setopt(curl, CURLOPT_XFERINFODATA, bar.get());
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    }
    curlResultCode = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    fclose(file);

    error = curl_easy_strerror(curlResultCode);
    return curlResultCode == CURLE_OK;
}

bool FileTransferUtility::downloadFile(const std::string& destinationPath, const std::string& url, std::string& error, bool useSSL, std::shared_ptr<ProgressBar> bar)
{
    if (url.empty())
    {
        error = "Url is empty";
        return false;
    }

    if (destinationPath.empty())
    {
        error = "Destination path is empty";
        return false;
    }

    CURL* curl;
    auto curlResultCode = CURLE_FAILED_INIT;
    curl = curl_easy_init();
    if (curl)
    {
        FILE* file;
        auto errorCode = fopen_s(&file, destinationPath.c_str(), "wb");
        if (errorCode != 0 || !file)
        {
            error = "Can not open destination file";
            return false;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteInFileCallbackFunction);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 0L);

        if (useSSL)
        {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        }

        if (bar)
        {
            curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, ProgressBar::xferinfo);
            curl_easy_setopt(curl, CURLOPT_XFERINFODATA, bar.get());
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
        }
        curlResultCode = curl_easy_perform(curl);
        fclose(file);
    }
    curl_easy_cleanup(curl);
    error = curl_easy_strerror(curlResultCode);
    return curlResultCode == CURLE_OK;
}

bool FileTransferUtility::getDirectoryInformation(std::string reportFileName, std::string directory, std::string url, std::string& error)
{
    CURL* curl;
    auto curlResultCode = CURLE_FAILED_INIT;

    curl = curl_easy_init();
    if (curl)
    {
        FILE* file;
        file = fopen(reportFileName.c_str(), "wb");
        if (!file)
        {
            error = "Can not open report file";
            return false;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 0L);
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteInFileCallbackFunction);
        curlResultCode = curl_easy_perform(curl);

        fclose(file);
    }
    error = curl_easy_strerror(curlResultCode);
    curl_easy_cleanup(curl);

    return curlResultCode != CURLE_OK ? false : true;
}

size_t FileTransferUtility::curlWriteInFileCallbackFunction(void* ptr, size_t size, size_t nmemb, void* data)
{
    auto file = static_cast<FILE*>(data);
    return fwrite(ptr, size, nmemb, file);
}

std::string FileTransferUtility::getDestinationFilePath(std::string fileName, std::string destinationDirectory, std::string scenarioNumber,
                                                        std::string terminalId)
{
    std::string serverFullPath = SERVER_DIR_PATH + scenarioNumber + "/" + destinationDirectory;
    std::string fileDate = getFileDate(fileName);
    if (fileDate.empty())
        return "";

    return serverFullPath + fileDate.substr(0, 4) + "/" + fileDate.substr(4, 2) + "/" + fileDate + "/" + terminalId + "/";
}

std::string FileTransferUtility::getFileDate(std::string fileName)
{
    auto from = fileName.find(ARCHIVE_APPLICATION_DATA_DATE_SEPARATOR);
    auto to = fileName.find(ARCHIVE_APPLICATION_DATA_TIME_SEPARATOR);

    if (from != std::string::npos && to != std::string::npos)
    {
        return fileName.substr(from + 2, to - from - 2);
    }
    return "";
}
bool FileTransferUtility::checkConnection(const std::string& ip, const std::string& port, std::string& error)
{
    return FileTransferUtility::checkConnection(ip + ':' + port, error);
}

bool FileTransferUtility::checkConnection(const std::string& url, std::string& error)
{
    CURL* curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);

        auto res = curl_easy_perform(curl);
        error = curl_easy_strerror(res);
        curl_easy_cleanup(curl);
        return res == CURLE_OK;
    }
    return false;
}
