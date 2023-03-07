#include "RestApiClient/RestApiClient.h"

CURLcode RestApiClient::httpJsonPost(bool useSSL, const std::string& url, const std::string& data, long timeout, long& response_code, std::function<size_t(void*, size_t, size_t, void*)> callbackFunc)
{
    CURL* curl = curl_easy_init();
    CURLcode res = CURLE_FAILED_INIT;

    if (curl)
    {
        // Set the URL to send the request to
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the request type to POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Set the headers for the request
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set the data to send in the POST request
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        // Set the timeout to SEND_REQUEST_TIME_OUT_INTERVAL seconds
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);

        if (callbackFunc)
        {
            // Set the callback function to handle the response
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &callbackFunc);
        }

        if (useSSL)
        {
            // Set to use SSL
            curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        }

        // Perform the request
        res = curl_easy_perform(curl);

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

        curl_easy_cleanup(curl);
    }
    return res;
}
