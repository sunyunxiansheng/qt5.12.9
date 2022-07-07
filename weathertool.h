#ifndef WEATHERTOOL_H
#define WEATHERTOOL_H
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonValue>
#include<QJsonParseError>
#include<map>
#include<QFile>
#include<QCoreApplication>
#include<QDebug>



class WeatherTool
{
public:
    WeatherTool(){
        QString exeFilePath = QCoreApplication::applicationDirPath();
        exeFilePath += "/citycode-2019-08-23.json";
        QFile file(exeFilePath);
        file.open(QIODevice::ReadOnly|QIODevice::Text);
        QByteArray byteArray = file.readAll();

        file.close();
        QJsonParseError jsonErr;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray,&jsonErr);
        QJsonArray citys = jsonDoc.array();
        for(int i = 0; i < citys.size(); i++)
        {
            QString code = citys.at(i).toObject().value("city_code").toString();
            QString name = citys.at(i).toObject().value("city_name").toString();
            if(code.size() > 0)
            m_mapName2Code.insert(std::pair<QString,QString>(name,code));
        }

    }
public:
    QString operator[](const QString& city)
    {
        std::map<QString,QString>::iterator it = m_mapName2Code.find(city);
        if(it == m_mapName2Code.end())
        {
            it = m_mapName2Code.find(city+u8"ÊÐ");
        }
        if(it != m_mapName2Code.end())
        {

            return it->second;

        }
        return "000000000";
    }
private:
    std::map<QString,QString> m_mapName2Code;
};







#endif // WEATHERTOOL_H


