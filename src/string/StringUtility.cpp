#include "string/StringUtility.hpp"

#include <algorithm>
#include <functional>
#include <iomanip>
#include <sstream>

bool StringUtility::caseInsensitiveCompare(const std::string str1, const std::string str2)
{
    auto str1Temp(str1);
    auto str2Temp(str2);
    transform(str1Temp.begin(), str1Temp.end(), str1Temp.begin(), ::tolower);
    transform(str2Temp.begin(), str2Temp.end(), str2Temp.begin(), ::tolower);
    return (str1Temp == str2Temp);
}

std::string StringUtility::ltrim(std::string data)
{
    data.erase(data.begin(), std::find_if(data.begin(), data.end(), [](int c)
                                          { return !std::isspace(c); }));
    return data;
}

std::string StringUtility::rtrim(std::string data)
{
    data.erase(std::find_if(data.rbegin(), data.rend(), [](int c)
                            { return !std::isspace(c); })
                   .base(),
               data.end());
    return data;
}

std::string StringUtility::trim(std::string data, bool removeSpaceFromMiddle /* = false*/)
{
    if (removeSpaceFromMiddle)
    {
        return erase(data, ' ');
    }
    return ltrim(rtrim(data));
}

std::string StringUtility::left(std::string data, int count)
{
    return data.substr(0, count);
}

std::string StringUtility::right(std::string data, int count)
{

    return data.substr(data.length() - count);
}

std::string StringUtility::mid(std::string data, int from, int size)
{
    return data.substr(from, size);
}

std::string StringUtility::fill(int data, char character, int size)
{
    std::ostringstream ostringstream;
    ostringstream << std::setw(size) << std::setfill(character) << data;
    return ostringstream.str();
}

std::string StringUtility::fill(std::string data, char character, int size)
{
    size -= data.length();
    if (size > 0)
    {
        return std::string(size, character).append(data);
    }
    return data;
}

std::string StringUtility::toUpper(std::string data)
{
    transform(data.begin(), data.end(), data.begin(), ::toupper);
    return data;
}

std::string StringUtility::toLower(std::string data)
{
    transform(data.begin(), data.end(), data.begin(), ::tolower);
    return data;
}

std::string StringUtility::erase(std::string data, int from, int size)
{
    return data.erase(from, size);
}

std::string StringUtility::subString(std::string data, int from, int size)
{
    return data.substr(from, size);
}

int StringUtility::subStringStartIndex(std::string data, std::string subString)
{
    auto index = data.find(subString);
    if (index != std::string::npos)
    {
        return index;
    }
    return -1;
}

int StringUtility::subStringStartIndex(std::string data, std::string subString, int position)
{
    auto index = data.find(subString, position);
    if (index != std::string::npos)
    {
        return index;
    }
    return -1;
}

bool StringUtility::isNumber(std::string data)
{
    return !data.empty() && find_if(data.begin(), data.end(), [](char c)
                                    { return !isdigit(c); }) == data.end();
}

std::string StringUtility::deleteLeftZero(std::string data)
{
    for (auto it = 0; it < data.size(); ++it)
    {
        if (data.at(it) == '0')
        {
            continue;
        }
        return subString(data, it, data.size() - it);
    }
    return data;
}

std::string StringUtility::getBaseNameFromFileName(std::string fileName)
{
    return {std::find_if(fileName.rbegin(), fileName.rend(), [](char c)
                         { return c == '/' || c == '\\'; })
                .base(),
            fileName.end()};
}

std::string StringUtility::removeFileNameFromPath(std::string path)
{
    return path.substr(0, path.find_last_of("\\/"));
}

std::vector<std::string> StringUtility::split(std::string data, std::string delimiter)
{
    std::vector<std::string> splits;
    splits.clear();

    size_t pos = 0;
    std::string token;
    while ((pos = data.find(delimiter)) != std::string::npos)
    {
        token = data.substr(0, pos);
        splits.push_back(token);
        data.erase(0, pos + delimiter.length());
    }

    splits.push_back(data);

    return splits;
}

std::string StringUtility::replaceSubString(std::string data, std::string subString, std::string newSubString)
{
    data.replace(data.find(subString), subString.length(), newSubString);
    return data;
}

std::string StringUtility::erase(std::string data, char character)
{
    data.erase(std::remove(data.begin(), data.end(), character), data.end());
    return data;
}

bool StringUtility::contain(std::string data, std::string subString)
{
    auto found = data.find(subString);
    if (found != std::string::npos)
    {
        return true;
    }
    return false;
}

std::string StringUtility::eraseSubString(std::string data, std::string subString)
{
    auto position = data.find(subString);
    if (position != std::string::npos)
    {
        data.erase(position, subString.length());
    }
    return data;
}

std::string StringUtility::eraseSubStrings(std::string data, std::string subString)
{
    auto position = std::string::npos;
    while ((position = data.find(subString)) != std::string::npos)
    {
        data.erase(position, subString.length());
    }
    return data;
}

std::vector<std::string> StringUtility::removeSpaces(std::string data)
{
    std::vector<std::string> result;
    std::istringstream iss(data);
    for (std::string s; iss >> s;)
    {
        result.push_back(s);
    }
    return result;
}

std::string StringUtility::addSeperator(std::string value, int count, char seperator)
{
    if (value.length() <= count)
    {
        return value;
    }

    int i = value.length();
    std::string buffer = "";
    auto j = 0;
    do
    {
        buffer.insert(0, value.substr(i--, 1));
        if (j == count && i > -1)
        {
            buffer = seperator + buffer;
            j = 0;
        }
        j++;
    } while (i > -1);
    return buffer;
}

bool StringUtility::findVectorInVector(std::vector<std::string> dataStrings, std::vector<std::string> secondVector)
{
    if (dataStrings.size() == 0 || secondVector.size() == 0)
    {
        return false;
    }

    auto foundCount = count_if(dataStrings.begin(), dataStrings.end(), [secondVector](std::string num)
                               {
                                   auto found = find_if(secondVector.begin(), secondVector.end(), [num](std::string value){return contain(num, value); });
                                   return found != secondVector.end() ? true : false; });

    return foundCount >= 1 ? true : false;
}