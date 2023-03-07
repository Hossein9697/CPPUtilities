#ifndef TYPE_CONVERTOR_HPP
#define TYPE_CONVERTOR_HPP

#include <atomic>
#include <string>
#include <vector>
#include <wtypes.h>

typedef std::vector<BYTE> ByteArray;

class TypeConvertor
{

public:
    static std::string dwordToString(DWORD number);
    static std::string unsignedLongLongToString(unsigned long long number);
    static std::string hexDWORDToString(DWORD number);
    static std::string intToString(int number);
    static std::string ulongToString(ULONG number);
    static std::wstring stringToWString(const std::string& data);
    static std::string wstringToString(std::wstring data);
    static TCHAR* stringToTChar(std::string data);
    static int stringToInt(std::string data);
    static unsigned long long stringToUnsignedLong(std::string data);
    static long stringToLong(std::string data);
    static bool intToBool(int number);
    static unsigned long hexStringToHex(std::string hexString);
    static std::string binaryCodedDecimalToString(const ByteArray buffer, int bufferLength, int offset, bool padLeft);
    static std::string binaryCodedDecimalToString(const BYTE* buffer, int bufferLength, int offset, bool padLeft);
    static std::string byteArrayToString(const unsigned char bytes[], int size);
    static void asciiToNibble(std::string ascii, LPBYTE nibblesBuffer, short nibblesBufferLength);
    static std::string nibbleToAscii(LPBYTE nibblesBuffer, short nibblesBufferLength);
    static std::string byteArrayToString(ByteArray data);
    static ByteArray stringToByteArray(std::string data);
    static std::wstring base64StringToWString(std::string base64String);
    static std::string format(const char* data, ...);

private:
    static std::string vformat(const char* data, va_list params);
};

#endif // TYPE_CONVERTOR_HPP
