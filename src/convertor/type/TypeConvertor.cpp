#include "convertor/type/TypeConvertor.hpp"

#include <QString>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

std::string TypeConvertor::dwordToString(DWORD number)
{
    std::stringstream stringStream;
    stringStream << int(number);
    return stringStream.str();
}

std::string TypeConvertor::unsignedLongLongToString(uint64_t number)
{
    std::stringstream stringStream;
    stringStream << uint64_t(number);
    return stringStream.str();
}

std::string TypeConvertor::hexDWORDToString(DWORD number)
{
    std::stringstream stringStream;
    stringStream << std::hex << int(number);
    return stringStream.str();
}

std::string TypeConvertor::intToString(int number)
{
    std::stringstream stringStream;
    stringStream << number;
    return stringStream.str();
}

std::string TypeConvertor::ulongToString(ULONG number)
{
    std::stringstream stringStream;
    stringStream << number;
    return stringStream.str();
}

std::wstring TypeConvertor::stringToWString(const std::string& data)
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

std::string TypeConvertor::wstringToString(std::wstring data) { return std::string(data.begin(), data.end()); }

TCHAR* TypeConvertor::stringToTChar(std::string data)
{
    auto dataBuffer = data.c_str();
    int length = 1 + strlen(dataBuffer);
    auto wideString = new wchar_t[length];
    size_t outSize;
    mbstowcs_s(&outSize, wideString, length, dataBuffer, length - 1);
    // mbstowcs(wideString, dataBuffer, length);
    return static_cast<TCHAR*>(wideString);
}

int TypeConvertor::stringToInt(std::string data)
{
    if (data.empty())
        return -1;

    return std::stoi(data);
}

unsigned long long TypeConvertor::stringToUnsignedLong(std::string data)
{
    if (data.empty())
        return -1;

    return std::stoull(data);
}

long TypeConvertor::stringToLong(std::string data)
{
    if (data.empty())
        return -1;

    return std::stol(data);
}

bool TypeConvertor::intToBool(int number)
{
    if (number == 0)
        return false;

    return true;
}

unsigned long TypeConvertor::hexStringToHex(std::string hexString) { return strtoul(hexString.c_str(), nullptr, 16); }

std::string TypeConvertor::binaryCodedDecimalToString(const ByteArray buffer, int bufferLength, int offset, bool padLeft)
{
    // Maps A Nibble Into A Character By Hex Format
    // For Example : ([0000,0001][0010,0011] , 0, 3, true) ---> "123"

    std::string bufferString(bufferLength, ' ');

    auto start = (((bufferLength & 1) == 1) && padLeft) ? 1 : 0;
    for (auto index = start; index < bufferLength + start; index++)
    {
        auto shift = ((index & 1) == 1 ? 0 : 4);
        char character = (buffer[offset + (index >> 1)] >> shift) & 0x0F;
        bufferString[index - start] = character < 10 ? (character + '0') : (character + 'A' - 10);
    }

    return bufferString;
}

std::string TypeConvertor::binaryCodedDecimalToString(const BYTE* buffer, int bufferLength, int offset, bool padLeft)
{
    // Maps A Nibble Into A Character By Hex Format
    // For Example : ([0000,0001][0010,0011] , 0, 3, true) ---> "123"

    std::string bufferString(bufferLength, ' ');

    auto start = (((bufferLength & 1) == 1) && padLeft) ? 1 : 0;
    for (auto index = start; index < bufferLength + start; index++)
    {
        auto shift = ((index & 1) == 1 ? 0 : 4);
        char character = (buffer[offset + (index >> 1)] >> shift) & 0x0F;
        bufferString[index - start] = character < 10 ? (character + '0') : (character + 'A' - 10);
    }

    return bufferString;
}

std::string TypeConvertor::byteArrayToString(const unsigned char bytes[], int size)
{
    std::ostringstream ostringStream;
    ostringStream << std::hex << std::uppercase;
    for (auto i = 0; i < size; ++i)
        ostringStream << std::setw(2) << std::setfill('0') << unsigned(bytes[i]);

    return ostringStream.str();
}

void TypeConvertor::asciiToNibble(std::string ascii, LPBYTE nibblesBuffer, short nibblesBufferLength) // Convert String To LPBYTE
{
    char tempCharacter1, tempCharacter2;
    short index;
    short asciiLength = ascii.length();
    if (asciiLength % 2)
    {
        ascii = "0" + ascii;
        asciiLength = ascii.length();
    }

    SecureZeroMemory(nibblesBuffer, nibblesBufferLength);

    if (asciiLength > 2 * nibblesBufferLength)
        asciiLength = 2 * nibblesBufferLength;

    for (index = 0; index < 2 * nibblesBufferLength - asciiLength; ++index)
        *(nibblesBuffer + index) = 0;

    transform(ascii.begin(), ascii.end(), ascii.begin(), ::toupper);

    for (; index < 2 * nibblesBufferLength; ++(++index))
    {
        tempCharacter1 = ascii.at(index);
        tempCharacter1 -= (tempCharacter1 >= '0' && tempCharacter1 <= '9') ? 0x30 : 0x37;
        tempCharacter2 = ascii.at(index + 1);
        tempCharacter2 -= (tempCharacter2 >= '0' && tempCharacter2 <= '9') ? 0x30 : 0x37;
        *(nibblesBuffer + (index / 2)) = (tempCharacter1 << 4) + tempCharacter2;
    }

    nibblesBufferLength = index / 2;
}

std::string TypeConvertor::nibbleToAscii(LPBYTE nibblesBuffer, short nibblesBufferLength) // Convert LPBYTE To String
{
    char tempCharacter;
    std::string ascii = "";

    for (short index = 0; index < nibblesBufferLength; ++index)
    {
        tempCharacter = (nibblesBuffer[index] >> 4);
        tempCharacter += (tempCharacter < 0x0a ? 0x30 : 0x37);
        ascii += tempCharacter;
        tempCharacter = (nibblesBuffer[index] & 0x0f);
        tempCharacter += (tempCharacter < 0x0a ? 0x30 : 0x37);
        ascii += tempCharacter;
    }

    return ascii;
}

std::string TypeConvertor::byteArrayToString(ByteArray data) { return std::string(data.begin(), data.end()); }

ByteArray TypeConvertor::stringToByteArray(std::string data) { return ByteArray(data.data(), data.data() + data.size()); }

std::wstring TypeConvertor::base64StringToWString(std::string base64String)
{
    if (base64String.empty())
        return L"";
    return QString(QByteArray::fromBase64(base64String.c_str())).toStdWString();
}

std::string TypeConvertor::format(const char* data, ...)
{
    va_list ap;
    va_start(ap, data);
    auto buffer = vformat(data, ap);
    va_end(ap);
    return buffer;
}

std::string TypeConvertor::vformat(const char* data, va_list params)
{
    size_t size = 1024;
    char buffer[1024];

    va_list apcopy;
    va_copy(apcopy, params);
    auto needed = vsnprintf(&buffer[0], size, data, params);

    if (needed <= size && needed >= 0)
        return std::string(&buffer[0]);

    std::vector<char> output;
    size = needed;
    output.resize(size);
    needed = vsnprintf(&output[0], size, data, apcopy);
    return std::string(&output[0]);
}
