#pragma once

#include <functional>
#include <utility>

#include <curl/curl.h>
#include <curl/easy.h>
#include <sys/stat.h>

class ProgressBar
{
private:
    std::function<void(int, int)> uploadSignal;

public:
    static int xferinfo(void* p, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
    {
        static_cast<ProgressBar*>(p)->uploadSignal((int)dlnow, (int)dltotal);
        return 0;
    }
    void setUploadSignal(std::function<void(int, int)> func)
    {
        uploadSignal = std::move(func);
    }
};