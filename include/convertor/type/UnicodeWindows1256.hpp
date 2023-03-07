#ifndef UNICODE_WINDOWS_1256_HPP
#define UNICODE_WINDOWS_1256_HPP

#include <map>
#include <string>

class UnicodeWindows1256
{

public:
    UnicodeWindows1256();
    ~UnicodeWindows1256();

    void convert(const std::wstring wstr, std::string& str);

private:
    std::map<int, int> unicode_win1256;
};
#endif // UNICODE_WINDOWS_1256_HPP
