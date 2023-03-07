#pragma once

#include <curl/curl.h>
#include <functional>
#include <string>

class RestApiClient
{
public:
    static CURLcode httpJsonPost(bool useSSL, const std::string& url, const std::string& data, long timeout, long& response_code, std::function<size_t(void*, size_t, size_t, void*)> callbackFunc = nullptr);
};