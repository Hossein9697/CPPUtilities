#include "localization/LocalizationUtility.hpp"

std::string LocalizationUtility::getLocalizeString(std::wstring data, QLocale::Language language /* = QLocale::Persian */, QLocale::Country country /* = QLocale::Iran */)
{
    QLocale locale(language, country);
    return locale.quoteString(QString::fromStdWString(data)).toStdString();
}
