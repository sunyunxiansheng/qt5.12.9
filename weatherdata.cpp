#include "weatherdata.h"
#include <QDate>
#include <QJsonArray>
#include <QDebug>

Today::Today()
{
    date = "0000-00-00";//
    city = "null";
    fl = u8"������";
    fx = u8"������";
    ganmao = u8"������";//
    notice = u8"������";
    pm25 = u8"������";//
    quality = u8"������";//
    shidu = u8"������";//
    sunrise = "00:00";
    sunset = "00:00";
    wendu = "null";//
    type = u8"������";
}

Today &Today::operator=(const QJsonObject &obj)
{
    QString dateStr = obj.value("date").toString();
    date = QDate::fromString(dateStr,"yyyyMMdd").toString("yyyy-MM-dd");
    city = obj.value("cityInfo").toObject().value("city").toString();

    //����data12
    QJsonObject dataObj = obj.value("data").toObject();
    shidu = dataObj.value("shidu").toString();
    pm25 = QString::number(dataObj.value("pm25").toDouble());
    quality = dataObj.value("quality").toString();
    wendu = dataObj.value("wendu").toString() + u8"��";
    ganmao = dataObj.value("ganmao").toString();

    QJsonArray forecastArr = dataObj.value("forecast").toArray();
    QJsonObject todayObj = forecastArr.at(0).toObject();
    sunrise = todayObj.value("sunrise").toString();
    sunset = todayObj.value("sunset").toString();
    fx = todayObj.value("fx").toString();
    fl = todayObj.value("fl").toString();
    type = todayObj.value("type").toString();
    notice =todayObj.value("notice").toString();
    return *this;
}

Forecast::Forecast()
{
    aqi = "0";
    date = u8"00������0";
    week = u8"����0";
    high = u8"���� 0.0��C";
    low = u8"���� 0.0��C";
    type = "undefined";
}

Forecast &Forecast::operator=(const QJsonObject &obj)
{
    date = obj.value("date").toString();
    week = obj.value("week").toString();
    high = obj.value("high").toString();
    low = obj.value("low").toString();
    aqi = QString::number(obj.value("aqi").toDouble());
    type = obj.value("type").toString();
    return *this;
}
