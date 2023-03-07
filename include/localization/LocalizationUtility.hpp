#ifndef LOCALIZATION_UTILITY_HPP
#define LOCALIZATION_UTILITY_HPP

#include <string>
#include <QLocale>

class LocalizationUtility
{

public:
    /* In order to read in Notepad++, Set the following setting in log file.
       Encoding->Encode in UTF-8-BOM */
    static std::string getLocalizeString(std::wstring data, QLocale::Language language = QLocale::Persian, QLocale::Country country = QLocale::Iran);
};

#endif // LOCALIZATION_UTILITY_HPP
