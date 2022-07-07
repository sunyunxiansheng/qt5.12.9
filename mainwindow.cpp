#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QMouseEvent>
#include <QMenu>
#include <QDebug>
#include <QMessageBox>
#include <QNetworkReply>
#include <QMessageBox>
#include <QPainter>


// �ճ��������
const QPoint MainWindow::sun[2] = {
//    QPoint(147,327),
//    QPoint(260,327)
//    QPoint(20,75),
//    QPoint(130,75)
    QPoint(7,61),
    QPoint(125,61)
};

// �ճ�����ʱ��
const QRect MainWindow::sunRiseSet[2] ={
    QRect(5,66,33,16),
    QRect(95,66,31,16)
};

// �ճ�����Բ��
const QRect MainWindow::rect[2] = {
    QRect(7,25,118,72),//����Բ��
    QRect(37,66,54,12)//�ճ������ı�

};

#define SPAN_INDEX 0.5 // �¶����߼��ָ��
#define ORIGIN_SIZE 3 //�¶�����ԭ���С
#define TEMPRATURE_STARING_COORDINATE 35 //����ƽ��ֵ��ʼ����

MainWindow::MainWindow(QWidget *parent)
    :  QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    setFixedSize(width(),height());
    act = new QAction;
    menu = new QMenu(this);

    act->setText(u8"�˳�");
    act->setIcon(QIcon(":/weathericon./close.ico"));
    menu->addAction(act);
    connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_exitapp()));

    //UI��ʼ��
    forecast_week_list << ui->week0Lb << ui->week1Lb << ui->week2Lb << ui->week3Lb << ui->week4Lb << ui->week5Lb;
    forecast_date_list << ui->date0Lb << ui->date1Lb << ui->date2Lb << ui->date3Lb << ui->date4Lb << ui->date5Lb;
    forecast_aqi_list << ui->quality0Lb << ui->quality1Lb << ui->quality2Lb << ui->quality3Lb << ui->quality4Lb << ui->quality5Lb;
    forecast_type_list << ui->type0Lb << ui->type1Lb << ui->type2Lb << ui->type3Lb << ui->type4Lb << ui->type5Lb;
    forecast_typeico_list << ui->typeico0Lb << ui->typeico1Lb << ui->typeico2Lb << ui->typeico3Lb << ui->typeico4Lb << ui->typeico5Lb;
    forecast_high_list << ui->high0Lb << ui->high1Lb << ui->high2Lb << ui->high3Lb << ui->high4Lb << ui->high5Lb;
    forecast_low_list << ui->low0Lb << ui->low1Lb << ui->low2Lb << ui->low3Lb << ui->low4Lb << ui->low5Lb;

    for(int i = 0; i < 6; i++)
    {
        forecast_week_list[i]->setStyleSheet("background-color: rgba(0,255,255,100);");
        forecast_date_list[i]->setStyleSheet("background-color: rgba(0,255,255,100);");
    }

    ui->cityLineEdit->setStyleSheet("QLineEdit{background-color:rgba(60,60,60,130);border:1px solid gray"
     ";border-radius:4px;color:rgb(255,255,255);}QLineEdit::hover{border-color:rgb(101,255,101);}");

    url = "http://t.weather.itboy.net/api/weather/city/";
    city = u8"��ɳ";
    cityTmp = city;
    manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this, SLOT(finishedReply(QNetworkReply*)));
    getWeatherInfo(manager);

    ui->sunrisesetLb->installEventFilter(this);
    ui->curveLb->installEventFilter(this);
    sunTimer = new QTimer(this);
    connect(sunTimer, SIGNAL(timeout()),ui->sunrisesetLb,SLOT(update()));
    sunTimer->start(1000);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    menu->exec(QCursor::pos());
    event->accept();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    m_point = event->globalPos()-this->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos()-m_point);
}

void MainWindow::getWeatherInfo(QNetworkAccessManager *manager)
{
    QString code = tool[city];
    if(code == "000000000")
    {
        QMessageBox::warning(this,u8"����",u8"Ҫָ���ĳ����������벻����",QMessageBox::Ok);
        return;
    }
    url = "http://t.weather.itboy.net/api/weather/city/";
    url+=code;
    QUrl jsonUrl(url);
   // qDebug()<<url;
    manager->get(QNetworkRequest(jsonUrl));
}

void MainWindow::parseDates(QByteArray &byteArray)
{
    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray, &err);
    if(err.error != QJsonParseError::NoError ) //json��ʽ����
    {
        return;
    }
    QJsonObject jsonObj = jsonDoc.object();
    today = jsonObj;
//    qDebug()<<jsonObj;
//    qDebug()<<"---------------\r\n";
//    qDebug()<<jsonObj.value("message").toString();

    QString message = jsonObj.value("message").toString();
    if(message.contains("success") == false)
    {
        QMessageBox::information(this,tr("The information of Json_desc"),u8"����:���д���",QMessageBox::Ok);
        return;
    }
    QJsonObject dataObj = jsonObj.value("data").toObject();
    forecast[0] = dataObj.value("yesterday").toObject();

    QJsonArray forecastArr = dataObj.value("forecast").toArray();
    int j=1;
    for(int i=0; i<5; i++)
    {
        forecast[j++] = forecastArr.at(i).toObject();
    }
    setLabelContent();
    ui->curveLb->update();
}

void MainWindow::setLabelContent()
{
    ui->dateLb->setText(today.date);
    ui->tempLb->setText(today.wendu);
    ui->cityLb->setText(today.city);
    ui->typeLb->setText(today.type);
    ui->noticeLb->setText(today.notice);
    ui->shiduLb->setText(today.shidu);
    ui->pm25Lb->setText(today.pm25);
    ui->fxLb->setText(today.fx);
    ui->flLb->setText(today.fl);
    ui->ganmaotextBrowser->setText(today.ganmao);
    ui->quailtyLb->setText(today.quality);
    for(int i=0; i<6; i++)
    {
        forecast_week_list[i]->setText(forecast[i].week);
        forecast_high_list[i]->setText(forecast[i].high.split(" ").at(1));
        forecast_low_list[i]->setText(forecast[i].low.split(" ").at(1));
        forecast_type_list[i]->setText(forecast[i].type);
        forecast_date_list[i]->setText(forecast[i].date);
        forecast_typeico_list[i]->setStyleSheet(tr("image:url(:/day/day/%1.png);").arg(forecast[i].type));
        if(forecast[i].aqi.toInt() >=0 && forecast[i].aqi.toInt() <= 50)
        {
            forecast_aqi_list[i]->setText(u8"����");
            forecast_aqi_list[i]->setStyleSheet("color:rgb(0,255,0)");
        }
        else if(forecast[i].aqi.toInt() >=50 && forecast[i].aqi.toInt() <= 100)
        {
            forecast_aqi_list[i]->setText(u8"����");
            forecast_aqi_list[i]->setStyleSheet("color:rgb(255,255,0)");
        }
        else if(forecast[i].aqi.toInt() >=100 && forecast[i].aqi.toInt() <= 150)
        {
            forecast_aqi_list[i]->setText(u8"�����Ⱦ");
            forecast_aqi_list[i]->setStyleSheet("color:rgb(255,170,0)");
        }
        else if(forecast[i].aqi.toInt() >=150 && forecast[i].aqi.toInt() <= 200)
        {
            forecast_aqi_list[i]->setText(u8"�ض���Ⱦ");
            forecast_aqi_list[i]->setStyleSheet("color:rgb(255,0,0)");
        }
        else
        {
            forecast_aqi_list[i]->setText(u8"������Ⱦ");
            forecast_aqi_list[i]->setStyleSheet("color:rgb(0,255,0)");
        }

    }

    ui->typeicoLb->setStyleSheet(tr("border-image:url(:/day/day/%1.png);background-color: rgba(60, 60, 60, 0);").arg(forecast[1].type));
    //ui->typeicoLb->setStyleSheet("backgrounnd-color:rgba(60,60,60,130)");
    ui->week0Lb->setText(u8"����");
    ui->week1Lb->setText(u8"����");
}

void MainWindow::paintSunRiseSet()
{
    //qDebug()<<u8"������";
    QPainter painter(ui->sunrisesetLb);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.save();
    QPen pen = painter.pen();
    pen.setWidthF(0.5);
    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    painter.drawLine(sun[0],sun[1]);
    painter.restore();

    painter.save();
    painter.setFont(QFont("Microsoft Yahei",8,QFont::Normal));
    painter.setPen(Qt::white);
    if(today.sunrise != "" && today.sunset != "")
    {
        painter.drawText(sunRiseSet[0],Qt::AlignHCenter,today.sunrise);
         painter.drawText(sunRiseSet[1],Qt::AlignHCenter,today.sunset);
    }
     painter.drawText(rect[1],Qt::AlignHCenter,u8"�ճ�����");
     painter.restore();

     //����Բ��
     painter.save();
     pen.setWidthF(0.5);
     pen.setStyle(Qt::DotLine);
     painter.setPen(pen);
     painter.drawArc(rect[0],0*16, 180*16);
     painter.restore();

     if(today.sunrise != "" && today.sunset !="")
     {
         painter.setPen(Qt::NoPen);//�رձ�
         painter.setBrush(QColor(255,85,0,100));
         int startAngle, spanAngle;
         QString sunsetTime = today.date + " " + today.sunset;
         //qDebug() << sunsetTime;
         if(QDateTime::currentDateTime() > QDateTime::fromString(sunsetTime, "yyyy-MM-dd hh:mm"))
         {
             startAngle = 0*16;
             spanAngle = 180*16;
         }
         else
         {
             static QStringList sunSetTime = today.sunset.split(":");
             static QStringList sunRiseTime = today.sunrise.split(":");

             static QString sunsetHour = sunSetTime.at(0);
             static QString sunsetMint = sunSetTime.at(1);
             static QString sunriseHour = sunRiseTime.at(0);
             static QString sunriseMint = sunRiseTime.at(1);

             static int sunrise = sunriseHour.toInt() * 60 + sunsetMint.toInt();
             static int sunset = sunsetHour.toInt() * 60 + sunsetMint.toInt();
             int now = QTime::currentTime().hour() * 60 + QTime::currentTime().minute();

             startAngle = ((double)(sunset - now) / (sunset - sunrise)) * 180 * 16;
             spanAngle = ((double)(now - sunrise) / (sunset - sunrise)) * 180 * 16;
         }
         if(startAngle >=0 && spanAngle >=0)
         {
             painter.drawPie(rect[0], startAngle, spanAngle);

         }

     }

}

void MainWindow::paintCurve()
{
    //qDebug()<<u8"��������";
    QPainter painter(ui->curveLb);
    painter.setRenderHint(QPainter::Antialiasing,true);

    int tempTotal = 0;
    int high[6] = {};
    int low[6] = {};

    //����ƽ��ֵ
    QString h,l;
    for(int i=0; i<6; i++)
    {
        h = forecast[i].high.split(" ").at(1);
        h = h.left(h.length() - 1);
        high[i] = (int)(h.toDouble());
        tempTotal += high[i];

        l = forecast[i].low.split(" ").at(1);
        l = l.left(h.length() - 1);
        low[i] = (int)(l.toDouble());
    }
    int tempAverage = (int)(tempTotal / 6); //�����ƽ��ֵ

    int pointX[6] = {35,85,135,185,235,285};
    int pointHY[6] = {0};
    int pointLY[6] = {0};
    for(int i=0; i<6; i++)
    {
        pointHY[i] = TEMPRATURE_STARING_COORDINATE - ((high[i] - tempAverage)*SPAN_INDEX);
        pointLY[i] = TEMPRATURE_STARING_COORDINATE + ((tempAverage - low[i])*SPAN_INDEX);
//        qDebug()<<"pointHy:"<<pointHY[i];
//        qDebug()<<"pointLy:"<<pointLY[i];
    }

    QPen pen = painter.pen();
    pen.setWidth(1);

    //�������߻���
    painter.save();
    pen.setColor(QColor(255,170,0));
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.setBrush(QColor(255,170,0));
    painter.drawEllipse(QPoint(pointX[0],pointHY[0]),ORIGIN_SIZE,ORIGIN_SIZE);
    painter.drawEllipse(QPoint(pointX[1],pointHY[1]),ORIGIN_SIZE,ORIGIN_SIZE);
    painter.drawLine(pointX[0],pointHY[0],pointX[1],pointHY[1]);


    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    painter.setPen(pen);

    for(int i=1; i<5; i++)
    {
        painter.drawEllipse(QPoint(pointX[i+1],pointHY[i+1]),ORIGIN_SIZE,ORIGIN_SIZE);
        painter.drawLine(pointX[i], pointHY[i],pointX[i+1],pointHY[i+1]);
    }
    painter.restore();

    //�������߻���
    pen.setColor(QColor(0,255,255));
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.setBrush(QColor(255,170,0));
    painter.drawEllipse(QPoint(pointX[0],pointLY[0]),ORIGIN_SIZE,ORIGIN_SIZE);
    painter.drawEllipse(QPoint(pointX[1],pointLY[1]),ORIGIN_SIZE,ORIGIN_SIZE);
    painter.drawLine(pointX[0],pointLY[0],pointX[1],pointLY[1]);


    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    painter.setPen(pen);

    for(int i=1; i<5; i++)
    {
        painter.drawEllipse(QPoint(pointX[i+1],pointLY[i+1]),ORIGIN_SIZE,ORIGIN_SIZE);
        painter.drawLine(pointX[i], pointLY[i],pointX[i+1],pointLY[i+1]);
    }

}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->sunrisesetLb && event->type() == QEvent::Paint)
    {
        paintSunRiseSet();
    }
    if(watched == ui->curveLb && event->type() == QEvent::Paint)
    {
        paintCurve();
    }
    return QWidget::eventFilter(watched, event);
}


void MainWindow::slot_exitapp()
{
    qApp->exit(0);
}

void MainWindow::finishedReply(QNetworkReply* reply)
{
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(reply->error() != QNetworkReply::NoError || status_code !=200)
    {
        QMessageBox::warning(this, u8"����",u8"�������������ݴ��󣬼����������",QMessageBox::Ok);
        return;
    }
    QByteArray byteArray = reply->readAll();
    parseDates(byteArray);
}




void MainWindow::on_searchToolBtn_clicked()
{
    cityTmp = city;
    city = ui->cityLineEdit->text();
    getWeatherInfo(manager);
}



void MainWindow::on_refreshToolBtn_clicked()
{
    getWeatherInfo(manager);
    ui->curveLb->update();
}
