#ifndef STRING_UTILITY_HPP
#define STRING_UTILITY_HPP

#include <vector>
#include <string>

class abc
{
private:
    abc() = default;
    static abc m_abc;

public:
    const abc& getInstance()
    {
        static abc a_b_c;
        return (std::reference_wrapper<abc>(a_b_c));
    }
    abc* const getIns()
    {
        static abc* a_b_c = new abc;
        return (a_b_c);
    }
};
class StringUtility
{
public:
    static bool caseInsensitiveCompare(const std::string str1, const std::string str2);
    static std::string ltrim(std::string data);
    static std::string rtrim(std::string data);
    static std::string trim(std::string data, bool removeSpaceFromMiddle = false);
    static std::string left(std::string data, int count);
    static std::string right(std::string data, int count);
    static std::string mid(std::string data, int from, int size);
    static std::string fill(int data, char character, int size);
    static std::string fill(std::string data, char character, int size);
    static std::string toUpper(std::string data);
    static std::string toLower(std::string data);
    static std::string erase(std::string data, int from, int size);
    static std::string subString(std::string data, int from, int size);
    static bool isNumber(std::string data);
    static std::string deleteLeftZero(std::string data);
    static std::string getBaseNameFromFileName(std::string fileName);
    static std::string removeFileNameFromPath(std::string path);
    static std::vector<std::string> split(std::string data, std::string delimiter);
    static std::string replaceSubString(std::string data, std::string subString, std::string newSubString);
    static std::string erase(std::string data, char character);
    static bool contain(std::string data, std::string subString);
    static std::string eraseSubString(std::string data, std::string subString);
    static std::string eraseSubStrings(std::string data, std::string subString);
    static std::vector<std::string> removeSpaces(std::string data);
    static std::string addSeperator(std::string value, int count, char seperator);
    static int subStringStartIndex(std::string data, std::string subString);
    static int subStringStartIndex(std::string data, std::string subString, int position);
    static bool findVectorInVector(std::vector<std::string> dataStrings, std::vector<std::string> secondVector);
};

#endif // STRING_UTILITY_HPP
