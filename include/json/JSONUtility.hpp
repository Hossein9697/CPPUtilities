#ifndef JSON_UTILITY_HPP
#define JSON_UTILITY_HPP

#include <QtCore>
#include <map>
#include <string>

typedef std::map<std::string, std::string> JSONMap;

class JSONUtility
{

public:
    static QJsonObject toObject(QString json);
    static QJsonObject toObject(std::string json);
    static QJsonObject toObject(JSONMap map);
    static JSONMap toMapFromObjectLessJSON(std::string json);
    static JSONMap toMap(std::string json);
    static JSONMap toMap(QJsonObject json);
    static JSONMap toStringMap(QJsonObject json);
    static JSONMap toStringMap(QJsonArray jsonArray);
    static std::string toString(QJsonObject json);
    static std::string toString(JSONMap map);
    static std::string toString(QJsonArray jsonArray);
    static QJsonArray toArray(std::string json);
    static QJsonArray toArray(JSONMap map);

private:
    static std::string eraseFromString(std::string data, char character);
    static std::string intToString(int number);
};

#endif // JSON_UTILITY_HPP