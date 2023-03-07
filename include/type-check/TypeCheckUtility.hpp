#ifndef TYPE_CHECK_UTILITY_HPP
#define TYPE_CHECK_UTILITY_HPP

#include <string>

#define DATE_DEFAULT_FORMAT      "yyyyMMdd"
#define TIME_DEFAULT_FORMAT      "hhmmss"
#define DATE_TIME_DEFAULT_FORMAT "yyyyMMddhhmmss"

class TypeCheckUtility
{

public:
    static bool isString(std::string data);
    static bool isCharacter(std::string data);
    static bool isNumber(std::string data);
    static bool isDate(std::string data, std::string format = DATE_DEFAULT_FORMAT);
    static bool isTime(std::string data, std::string format = TIME_DEFAULT_FORMAT);
    static bool isDateTime(std::string data, std::string format = DATE_TIME_DEFAULT_FORMAT);
    static bool isBoolean(std::string data);
};

#endif // TYPE_CHECK_UTILITY_HPP
