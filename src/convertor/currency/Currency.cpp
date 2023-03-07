#include "convertor/currency/Currency.hpp"
#include <convertor/type/TypeConvertor.hpp>

Currency::Currency()
{
    entity.empty();
    currency.empty();
    alpha.empty();
    currencyCode = -1;
    minorUnit = -1;
}

Currency::Currency(std::string entity, std::string currency, std::string alpha, int currencyCode, int minorUnit)
{
    this->entity = entity;
    this->currency = currency;
    this->alpha = alpha;
    this->currencyCode = currencyCode;
    this->minorUnit = minorUnit;
}

std::string Currency::getEntity() const { return entity; }

void Currency::setEntity(const std::string entity) { this->entity = entity; }

std::string Currency::getCurrency() const { return currency; }

void Currency::setCurrency(const std::string currency) { this->currency = currency; }

std::string Currency::getAlpha() const { return alpha; }

void Currency::setAlpha(const std::string alpha) { this->alpha = alpha; }

int Currency::getCurrencyCode() const { return currencyCode; }

void Currency::setCurrencyCode(const int currencyCode) { this->currencyCode = currencyCode; }

int Currency::getMinorUnit() const { return minorUnit; }

void Currency::setMinorUnit(const int minorUnit) { this->minorUnit = minorUnit; }

bool Currency::isEmpty() const { return entity.empty() || eraseSubStrings(currency, " ").empty() || eraseSubStrings(alpha, " ").empty() || currencyCode == -1 || minorUnit == -1; }

std::string Currency::toString() const
{
    return std::string("[") + "Entity:" + (entity.empty() ? "null" : entity) + " , " + "Currency:" + (currency.empty() ? "null" : currency) + " , " + "Alpha:" + (alpha.empty() ? "null" : alpha) +
           " , " + "Currency Code:" + TypeConvertor::intToString(currencyCode) + " , " + "Minor Unit:" + TypeConvertor::intToString(minorUnit) + "]";
}

std::string Currency::eraseSubStrings(std::string data, std::string subString)
{
    auto position = std::string::npos;
    while ((position = data.find(subString)) != std::string::npos)
        data.erase(position, subString.length());
    return data;
}
