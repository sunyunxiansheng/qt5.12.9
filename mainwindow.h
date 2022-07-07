#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include "weathertool.h"
#include "weatherdata.h"
#include <QLabel>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void getWeatherInfo(QNetworkAccessManager* manager);
    void parseDates(QByteArray &byteArray);
    void setLabelContent();
    void paintSunRiseSet();
    void paintCurve();
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void slot_exitapp();
    void finishedReply(QNetworkReply* reply);


    void on_searchToolBtn_clicked();

    void on_refreshToolBtn_clicked();

private:
    Ui::MainWindow *ui;
    QAction* act;
    QMenu* menu;
    QPoint m_point;
    QList<QLabel*> forecast_week_list;  //星期
    QList<QLabel*> forecast_date_list; //日期
    QList<QLabel*> forecast_aqi_list;  //空气质量
    QList<QLabel*> forecast_type_list; //天气
    QList<QLabel*> forecast_typeico_list; //天气图标
    QList<QLabel*> forecast_high_list; //高温
    QList<QLabel*> forecast_low_list; //低温

    //网络请求
    QString url;
    QString city;
    QString cityTmp;
    WeatherTool tool;
    QNetworkAccessManager* manager;

    //本地数据
    Today today;
    Forecast forecast[6];

    static const QPoint sun[2];
    static const QRect sunRiseSet[2];
    static const QRect rect[2];

    QTimer* sunTimer;
};
#endif // MAINWINDOW_H
