#ifndef DATE_TIME_UTILITY_HPP
#define DATE_TIME_UTILITY_HPP

#include <QDate>
#include <QDateTime>
#include <string>

#define FULL_DATE_FORMAT             "yyyyMMdd"
#define FULL_TIME_FORMAT             "hhmmss"
#define DATE_TIME_FORMAT             "yyyyMMddhhmmss"
#define DETAILED_DATE_TIME_FORMAT    "yyyyMMddhhmmsszzz"
#define TRANSACTION_DATE_TIME_FORMAT "yyyyMMdd_hhmmss"

class DateTimeUtility
{

public:
    static std::string getCurrentDate(std::string format = FULL_DATE_FORMAT);
    static std::string getCurrentTime(std::string format = FULL_TIME_FORMAT);
    static std::string getCurrentDateTime(std::string format = DATE_TIME_FORMAT);
    static std::string getCurrentDateWithDayDelay(int dayDelay, std::string format = FULL_DATE_FORMAT);
    static QDate getDateFromString(std::string date, std::string format = FULL_DATE_FORMAT);
    static std::string getJalaliDateTime(std::string dateSeperator = "", std::string timeSeperator = "");
    static std::string convertMiladiToJalaliDate(std::string miladiDateTime, std::string seperator = "");
    static void convertJalaliToMiladiDate(const std::string& jalaliDate, std::string& miladiDate);
    static QDateTime getDateTimeFromString(std::string dateTime, std::string format = DATE_TIME_FORMAT);
    static std::string convertDateTimeFormat(std::string dateTime, std::string baseFormat = DATE_TIME_FORMAT, std::string toFormat = DATE_TIME_FORMAT);
    static bool isDateTimePassedMinutes(QDateTime dateTime, int minutes);
    static bool setCurrentDate(int year, int month, int day);
    static bool setCurrentTime(int hour, int minute, int second);
    static std::string getJalaliDate(std::string seperator="");

private:
    static bool isMiladiYearLeap(int miladiYear);
    static int stringToInt(std::string data);
    static std::string fill(int data, char character, int size);
    static std::wstring stringToWString(const std::string& data);
    static std::string intToString(int number);
};

#endif // DATE_TIME_UTILITY_HPP
