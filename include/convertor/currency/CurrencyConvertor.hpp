#ifndef CURRENCY_CONVERTOR_HPP
#define CURRENCY_CONVERTOR_HPP

// Currency Codes (ISO 4217)

#include <string>
#include <vector>

#include "Currency.hpp"

typedef std::vector<Currency> CurrencyTable;

class CurrencyConvertor
{

public:
    static Currency getCurrency(std::string alpha);
    static Currency getCurrency(int currencyCode);

private:
    static CurrencyTable createCurrencyTable();

private:
    static CurrencyTable currencyTable;
};

#endif // CURRENCY_CONVERTOR_HPP
