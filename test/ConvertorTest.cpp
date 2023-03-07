#include "convertor/currency/Currency.hpp"
#include "convertor/currency/CurrencyConvertor.hpp"
#include "convertor/type/TypeConvertor.hpp"
#include "convertor/type/UnicodeWindows1256.hpp"
#include <gtest/gtest.h>

class EmptyCurrency : public ::testing::Test
{
public:
    Currency emptyCurrenct;
};

class InitializedCurrency : public ::testing::Test
{
public:
    Currency initializedCurrenct{Currency("ÅLAND ISLANDS", "Euro", "EUR", 978, 2)};
};

TEST_F(EmptyCurrency, ToEmpty) { ASSERT_TRUE(emptyCurrenct.isEmpty()); }

TEST_F(EmptyCurrency, ToString) { EXPECT_EQ(emptyCurrenct.toString(), "[Entity:null , Currency:null , Alpha:null , Currency Code:-1 , Minor Unit:-1]"); }

TEST_F(InitializedCurrency, ToEmpty) { ASSERT_FALSE(initializedCurrenct.isEmpty()); }

TEST_F(InitializedCurrency, ToString) { EXPECT_EQ(initializedCurrenct.toString(), "[Entity:ÅLAND ISLANDS , Currency:Euro , Alpha:EUR , Currency Code:978 , Minor Unit:2]"); }

TEST_F(EmptyCurrency, Initializing)
{
    emptyCurrenct.setAlpha("IRR");
    EXPECT_EQ(emptyCurrenct.getAlpha(), "IRR");
    ASSERT_TRUE(emptyCurrenct.isEmpty());
    emptyCurrenct.setCurrency("Iranian Rial");
    EXPECT_EQ(emptyCurrenct.getCurrency(), "Iranian Rial");
    ASSERT_TRUE(emptyCurrenct.isEmpty());
    emptyCurrenct.setEntity("IRAN (ISLAMIC REPUBLIC OF)");
    EXPECT_EQ(emptyCurrenct.getEntity(), "IRAN (ISLAMIC REPUBLIC OF)");
    ASSERT_TRUE(emptyCurrenct.isEmpty());
    emptyCurrenct.setCurrencyCode(364);
    EXPECT_EQ(emptyCurrenct.getCurrencyCode(), 364);
    ASSERT_TRUE(emptyCurrenct.isEmpty());
    emptyCurrenct.setMinorUnit(2);
    EXPECT_EQ(emptyCurrenct.getMinorUnit(), 2);
    ASSERT_FALSE(emptyCurrenct.isEmpty());
    EXPECT_EQ(emptyCurrenct.toString(), "[Entity:IRAN (ISLAMIC REPUBLIC OF) , Currency:Iranian Rial , Alpha:IRR , Currency Code:364 , Minor Unit:2]");
}

TEST(CurrencyConvertor, GetCurrency)
{
    Currency firstCurrency = CurrencyConvertor::getCurrency(840);
    ASSERT_FALSE(firstCurrency.isEmpty());
    EXPECT_EQ(firstCurrency.toString(), "[Entity:AMERICAN SAMOA , Currency:US Dollar , Alpha:USD , Currency Code:840 , Minor Unit:2]");
    Currency secondCurrency = CurrencyConvertor::getCurrency("IRR");
    ASSERT_FALSE(secondCurrency.isEmpty());
    EXPECT_EQ(secondCurrency.toString(), "[Entity:IRAN (ISLAMIC REPUBLIC OF) , Currency:Iranian Rial , Alpha:IRR , Currency Code:364 , Minor Unit:2]");
}

TEST(TypeConvertor, ToStrings)
{
    EXPECT_EQ(TypeConvertor::dwordToString(DWORD(123ul)), "123");
    EXPECT_EQ(TypeConvertor::unsignedLongLongToString(123ull), "123");
    EXPECT_EQ(TypeConvertor::hexDWORDToString(0x123), "123");
    EXPECT_EQ(TypeConvertor::intToString(-123), "-123");
    EXPECT_EQ(TypeConvertor::ulongToString(123ul), "123");
    EXPECT_EQ(TypeConvertor::wstringToString(L"123"), "123");
    EXPECT_EQ(TypeConvertor::byteArrayToString(TypeConvertor::stringToByteArray("123")), "123");
    EXPECT_EQ(TypeConvertor::stringToWString("123"), L"123");
    EXPECT_EQ(TypeConvertor::stringToInt("-123"), -123);
    EXPECT_EQ(TypeConvertor::stringToUnsignedLong("123"), 123);
    EXPECT_EQ(TypeConvertor::stringToLong("-123"), -123);
    EXPECT_EQ(TypeConvertor::intToBool(123), true);
    EXPECT_EQ(TypeConvertor::hexStringToHex("123"), 0x123);
}

TEST(UnicodeWindows1256, ConvertTo1256)
{
    auto farsi = L"سلام";
    auto english = L"ok";
    UnicodeWindows1256 convertor;
    std::string result;
    convertor.convert(farsi, result);
    EXPECT_EQ(result, "\xD3\xE1\xC7\xE3");
    convertor.convert(english, result);
    EXPECT_EQ(result, "\x6F\x6B");
}
