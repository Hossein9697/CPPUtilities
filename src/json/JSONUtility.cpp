#include "json/JSONUtility.hpp"

QJsonObject JSONUtility::toObject(QString json)
{
    QJsonObject object;
    auto jsonDocument = QJsonDocument::fromJson(json.toUtf8());
    if (!jsonDocument.isNull())
    {
        if (jsonDocument.isObject())
        {
            object = jsonDocument.object();
        }
    }

    return object;
}

QJsonObject JSONUtility::toObject(std::string json)
{
    QJsonObject object;
    auto jsonDocument = QJsonDocument::fromJson(QString(json.c_str()).toUtf8());
    if (!jsonDocument.isNull())
    {
        if (jsonDocument.isObject())
        {
            object = jsonDocument.object();
        }
    }

    return object;
}

QJsonObject JSONUtility::toObject(JSONMap map)
{
    QJsonObject json;
    for (auto pair : map)
    {
        json.insert(pair.first.c_str(), pair.second.c_str());
    }
    return json;
}

JSONMap JSONUtility::toMapFromObjectLessJSON(std::string json)
{
    JSONMap jsonMap;
    jsonMap.clear();

    auto jsonDocument = QJsonDocument::fromJson(QString(json.c_str()).toUtf8());
    for (auto currentPair : jsonDocument.array())
    {
        auto jsonObject = currentPair.toObject();
        foreach (auto key, jsonObject.keys())
        {
            jsonMap.insert(std::pair<std::string, std::string>(key.toStdString(), jsonObject.value(key).toString().toStdString()));
        }
    }

    return jsonMap;
}

JSONMap JSONUtility::toMap(std::string json)
{
    return toStringMap(toObject(json));
}

JSONMap JSONUtility::toMap(QJsonObject json)
{
    JSONMap jsonMap;
    jsonMap.clear();

    foreach (auto key, json.keys())
    {
        jsonMap.insert(std::pair<std::string, std::string>(key.toStdString(), json.value(key).toString().toStdString()));
    }

    return jsonMap;
}

JSONMap JSONUtility::toStringMap(QJsonObject json)
{
    JSONMap jsonMap;
    jsonMap.clear();

    foreach (auto key, json.keys())
    {
        jsonMap.insert(std::pair<std::string, std::string>(key.toStdString(), json.value(key).toString().toStdString()));
    }

    return jsonMap;
}

JSONMap JSONUtility::toStringMap(QJsonArray jsonArray)
{
    JSONMap jsonMap;
    jsonMap.clear();
    auto i = 0;
    for (auto filed : jsonArray)
    {
        jsonMap.insert(std::pair<std::string, std::string>(intToString(i++), filed.toString().toStdString()));
    }

    return jsonMap;
}

std::string JSONUtility::toString(QJsonObject json)
{
    return eraseFromString(eraseFromString(QJsonDocument(json).toJson().toStdString(), '\n'), ' '); // Erase All New-Line And Space From Buffer
}

std::string JSONUtility::toString(JSONMap map)
{
    QJsonDocument doc(toObject(map));
    return QString(doc.toJson(QJsonDocument::Compact)).toStdString();
}

std::string JSONUtility::toString(QJsonArray jsonArray)
{
    QJsonDocument doc(jsonArray);
    return QString(doc.toJson(QJsonDocument::Compact)).toStdString();
}

QJsonArray JSONUtility::toArray(std::string json)
{
    QJsonArray array;
    auto jsonDocument = QJsonDocument::fromJson(QString(json.c_str()).toUtf8());
    if (!jsonDocument.isNull())
    {
        if (jsonDocument.isArray())
        {
            array = jsonDocument.array();
        }
    }

    return array;
}

QJsonArray JSONUtility::toArray(JSONMap map)
{
    QJsonArray json;
    auto count = 0;
    for (auto pair : map)
    {
        json.insert(count, pair.second.c_str());
    }
    return json;
}

std::string JSONUtility::eraseFromString(std::string data, char character)
{
    data.erase(std::remove(data.begin(), data.end(), character), data.end());
    return data;
}

std::string JSONUtility::intToString(int number)
{
    std::stringstream stringStream;
    stringStream << number;
    return stringStream.str();
}