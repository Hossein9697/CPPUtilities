#ifndef CURRENCY_HPP
#define CURRENCY_HPP

#include <string>
#include <vector>

#define RIAL_CURRENCY_CODE   "364"
#define DOLLAR_CURRENCY_CODE "840"
#define EURO_CURRENCY_CODE   "978"

class Currency
{

public:
    Currency();
    Currency(std::string entity, std::string currency, std::string alpha, int currencyCode, int minorUnit);

    std::string getEntity() const;
    void setEntity(const std::string entity);

    std::string getCurrency() const;
    void setCurrency(const std::string currency);

    std::string getAlpha() const;
    void setAlpha(const std::string alpha);

    int getCurrencyCode() const;
    void setCurrencyCode(const int currencyCode);

    int getMinorUnit() const;
    void setMinorUnit(const int minorUnit);

    bool isEmpty() const;
    std::string toString() const;

private:
    static std::string eraseSubStrings(std::string data, std::string subString);

private:
    std::string entity;
    std::string currency;
    std::string alpha;
    int currencyCode;
    int minorUnit;
};

#endif // CURRENCY_HPP
