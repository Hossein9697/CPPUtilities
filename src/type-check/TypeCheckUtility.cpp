#include "type-check/TypeCheckUtility.hpp"

#include <sstream>
#include <QDateTime>
#include <algorithm>

bool TypeCheckUtility::isString(std::string data)
{
    return true;
}

bool TypeCheckUtility::isCharacter(std::string data)
{
    return data.size() == 1;
}

bool TypeCheckUtility::isNumber(std::string data)
{
    long double value = 0;
    return (std::istringstream(data) >> value >> std::ws).eof();
}

bool TypeCheckUtility::isDate(std::string data, std::string format /* = DATE_DEFAULT_FORMAT */)
{
    auto date = QDate::fromString(data.c_str(), format.c_str());
    return date.isValid();
}

bool TypeCheckUtility::isTime(std::string data, std::string format /* = TIME_DEFAULT_FORMAT */)
{
    auto time = QTime::fromString(data.c_str(), format.c_str());
    return time.isValid();
}

bool TypeCheckUtility::isDateTime(std::string data, std::string format /* = DATE_TIME_DEFAULT_FORMAT */)
{
    auto dateTime = QDateTime::fromString(data.c_str(), format.c_str());
    return dateTime.isValid();
}

bool TypeCheckUtility::isBoolean(std::string data)
{
    transform(data.begin(), data.end(), data.begin(), ::tolower);
    if (data == "0" || data == "1" || data == "true" || data == "false")
        return true;
    return false;
}
