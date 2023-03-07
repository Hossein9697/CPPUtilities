#include "date-time/DateTimeUtility.hpp"

#include <Windows.h>
#include <iomanip>
#include <iostream>
#include <sstream>

std::string DateTimeUtility::getCurrentDate(std::string format /* = FULL_DATE_FORMAT */)
{
    QDate date = QDate::currentDate();
    return QLocale().toString(date, format.c_str()).toStdString();
}

std::string DateTimeUtility::getCurrentTime(std::string format /* = FULL_TIME_FORMAT */)
{
    QTime time = QTime::currentTime();
    return QLocale().toString(time, format.c_str()).toStdString();
}

std::string DateTimeUtility::getCurrentDateTime(std::string format /* = DATE_TIME_FORMAT */)
{
    QDateTime dateTime = QDateTime::currentDateTime();
    return QLocale().toString(dateTime, format.c_str()).toStdString();
}

std::string DateTimeUtility::getCurrentDateWithDayDelay(int dayDelay, std::string format)
{
    auto date = QDate::currentDate();
    date = date.addDays(dayDelay);
    return QLocale().toString(date, format.c_str()).toStdString();
}

std::string DateTimeUtility::getJalaliDate(std::string seperator /* = "" */) { return convertMiladiToJalaliDate(getCurrentDate(), seperator); }

std::string DateTimeUtility::convertMiladiToJalaliDate(std::string miladiDate, std::string seperator /* = "" */)
{
    int sumOfDaysInMiladiMonths[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int sumOfDaysInMiladiMonthsThatIsLeap[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};

    auto miladiYear = stringToInt(miladiDate.substr(0, 4));
    auto miladiMonth = stringToInt(miladiDate.substr(4, 2));
    auto miladiDay = stringToInt(miladiDate.substr(6, 2));
    auto farvardinDaysDiff = 79;

    int jalaliYear, jalaliMonth, jalaliDay;
    int daysCount, DeyMonthDaysDiff;

    if (isMiladiYearLeap(miladiYear))
    {
        daysCount = sumOfDaysInMiladiMonthsThatIsLeap[miladiMonth - 1] + miladiDay;
    }
    else
    {
        daysCount = sumOfDaysInMiladiMonths[miladiMonth - 1] + miladiDay;
    }

    if ((isMiladiYearLeap(miladiYear - 1)))
    {
        DeyMonthDaysDiff = 11;
    }
    else
    {
        DeyMonthDaysDiff = 10;
    }

    if (daysCount > farvardinDaysDiff)
    {
        daysCount = daysCount - farvardinDaysDiff;
        if (daysCount <= 186)
        {
            switch (daysCount % 31)
            {
                case 0:
                    jalaliMonth = daysCount / 31;
                    jalaliDay = 31;
                    break;
                default:
                    jalaliMonth = (daysCount / 31) + 1;
                    jalaliDay = (daysCount % 31);
                    break;
            }
            jalaliYear = miladiYear - 621;
        }
        else
        {
            daysCount = daysCount - 186;
            switch (daysCount % 30)
            {
                case 0:
                    jalaliMonth = (daysCount / 30) + 6;
                    jalaliDay = 30;
                    break;
                default:
                    jalaliMonth = (daysCount / 30) + 7;
                    jalaliDay = (daysCount % 30);
                    break;
            }
            jalaliYear = miladiYear - 621;
        }
    }
    else
    {
        daysCount = daysCount + DeyMonthDaysDiff;
        switch (daysCount % 30)
        {
            case 0:
                jalaliMonth = (daysCount / 30) + 9;
                jalaliDay = 30;
                break;
            default:
                jalaliMonth = (daysCount / 30) + 10;
                jalaliDay = (daysCount % 30);
                break;
        }
        jalaliYear = miladiYear - 622;
    }

    return fill(jalaliYear, '0', 4) + seperator + fill(jalaliMonth, '0', 2) + seperator + fill(jalaliDay, '0', 2);
}

void DateTimeUtility::convertJalaliToMiladiDate(const std::string& jalaliDate, std::string& miladiDate)
{

    try
    {
        if (jalaliDate.size() != 8)
        {
            throw "size of inputed jalali date is invalid.";
        }

        for (char ch : jalaliDate)
        {
            if (!isdigit(ch))
            {
                throw "format of inputed jalali date is invalid.";
            }
        }

        int daymiladiMonth[]{30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 28, 31};

        int iJalaliYear = std::stoi(jalaliDate.substr(0, 4));
        int iJalaliMonth = std::stoi(jalaliDate.substr(4, 2));
        int iJalaliDay = std::stoi(jalaliDate.substr(6, 2));

        int imiladiYear = iJalaliYear + 621;

        int marchDayDiff;
        // Detemining the Farvardin the First
        if (isMiladiYearLeap(imiladiYear))
        {
            // this is a Miladi leap year so Jalali is leap too so the 1st of Farvardin is March 20 (3/20)
            marchDayDiff = 12;
        }
        else
        {
            // this is not a Miladi leap year so Jalali is not leap too so the 1st of Farvardin is March 21 (3/21)
            marchDayDiff = 11;
        }

        // If next year is leap we will add one day to Feb.
        if (isMiladiYearLeap(imiladiYear + 1))
        {
            daymiladiMonth[10] = daymiladiMonth[10] + 1; // Adding one day to Feb
        }

        // Calculate the day count for input Jalali date from 1st Farvadin
        int dayCount = 0;
        if ((iJalaliMonth >= 1) && (iJalaliMonth <= 6))
        {
            dayCount = ((iJalaliMonth - 1) * 31) + iJalaliDay;
        }
        else
        {
            dayCount = (6 * 31) + ((iJalaliMonth - 7) * 30) + iJalaliDay;
        }

        int miladiDay, miladiMonth, miladiYear;
        // Finding the correspond miladi month and day
        if (dayCount <= marchDayDiff)
        { // So we are in 20(for leap year) or 21for none leap year) to 31 march
            miladiDay = dayCount + (31 - marchDayDiff);
            miladiMonth = 3;
            miladiYear = imiladiYear;
        }
        else
        {
            int remainDay = dayCount - marchDayDiff;

            int i = 0; // starting from April
            while ((remainDay > daymiladiMonth[i]))
            {
                remainDay = remainDay - daymiladiMonth[i];
                i++;
            }
            miladiDay = remainDay;

            if (i > 8)
            { // We are in the next Miladi Year
                miladiMonth = i - 8;
                miladiYear = imiladiYear + 1;
            }
            else
            {
                miladiMonth = i + 4;
                miladiYear = imiladiYear;
            }
        }
        std::string sMiladiMonth = std::to_string(miladiMonth);
        if (sMiladiMonth.size() == 1)
        {
            sMiladiMonth.insert(0, "0");
        }

        std::string sMiladiDay = std::to_string(miladiDay);
        if (sMiladiDay.size() == 1)
        {
            sMiladiDay.insert(0, "0");
        }

        miladiDate = std::to_string(miladiYear) + sMiladiMonth + sMiladiDay;
    }
    catch (const char* error)
    {
        std::cerr << error << std::endl;
        throw error;
    }
}

bool DateTimeUtility::isMiladiYearLeap(int miladiYear)
{
    if (((miladiYear % 100) != 0 && (miladiYear % 4) == 0) || ((miladiYear % 100) == 0 && (miladiYear % 400) == 0))
    {
        return true;
    }
    return false;
}

std::string DateTimeUtility::getJalaliDateTime(std::string dateSeperator, std::string timeSeperator)
{
    return getJalaliDate(dateSeperator) + getCurrentTime("hh" + timeSeperator + "mm" + timeSeperator + "ss");
}

QDate DateTimeUtility::getDateFromString(std::string date, std::string format /* = FULL_DATE_FORMAT */) { return QDate::fromString(date.c_str(), format.c_str()); }

QDateTime DateTimeUtility::getDateTimeFromString(std::string dateTime, std::string format) { return QDateTime::fromString(dateTime.c_str(), format.c_str()); }

std::string DateTimeUtility::convertDateTimeFormat(std::string dateTime, std::string baseFormat /* = DATE_TIME_FORMAT */, std::string toFormat /* = DATE_TIME_FORMAT */)
{
    QDateTime dateTimeObject = QDateTime::fromString(dateTime.c_str(), baseFormat.c_str());
    return QLocale().toString(dateTimeObject, toFormat.c_str()).toStdString();
}

bool DateTimeUtility::isDateTimePassedMinutes(QDateTime dateTime, int minutes)
{
    if (dateTime.secsTo(QDateTime::currentDateTime()) >= minutes * 60)
    {
        return true;
    }
    return false;
}

int DateTimeUtility::stringToInt(std::string data)
{
    if (data.empty())
    {
        return -1;
    }

    return std::stoi(data);
}

std::string DateTimeUtility::fill(int data, char character, int size)
{
    std::ostringstream ostringstream;
    ostringstream << std::setw(size) << std::setfill(character) << data;
    return ostringstream.str();
}

bool DateTimeUtility::setCurrentDate(int year, int month, int day)
{
    return (BOOL)ShellExecute(nullptr, L"open", L"cmd", stringToWString("/C date " + intToString(month) + "-" + intToString(day) + "-" + intToString(year)).c_str(), nullptr, SW_HIDE);
}

bool DateTimeUtility::setCurrentTime(int hour, int minute, int second)
{
    ShellExecute(nullptr, L"open", L"cmd", stringToWString("/C tzutil /s \"Iran Standard Time\"_dstoff").c_str(), nullptr, SW_HIDE);
    if (hour >= 0 && hour < 12)
    {
        return (BOOL)ShellExecute(nullptr, L"open", L"cmd", stringToWString("/C time " + intToString(hour) + ":" + intToString(minute) + ":" + intToString(second) + " am").c_str(), nullptr, SW_HIDE);
    }
    if (hour >= 12 && hour < 24)
    {
        return (BOOL)ShellExecute(nullptr, L"open", L"cmd", stringToWString("/C time " + intToString(hour) + ":" + intToString(minute) + ":" + intToString(second) + " pm").c_str(), nullptr, SW_HIDE);
    }
}

std::wstring DateTimeUtility::stringToWString(const std::string& data)
{
    int length;
    auto stringLength = int(data.length()) + 1;
    length = MultiByteToWideChar(CP_ACP, 0, data.c_str(), stringLength, 0, 0);
    auto wideString = new wchar_t[length];
    MultiByteToWideChar(CP_ACP, 0, data.c_str(), stringLength, wideString, length);
    std::wstring wideStringData(wideString);
    delete[] wideString;
    return wideStringData;
}

std::string DateTimeUtility::intToString(int number)
{
    std::stringstream stringStream;
    stringStream << number;
    return stringStream.str();
}
