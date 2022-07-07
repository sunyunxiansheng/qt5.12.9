QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    weatherdata.cpp

HEADERS += \
    mainwindow.h \
    weatherdata.h \
    weathertool.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons/icons.qrc \
    images/images.qrc \
    weatherIcons/weatypeico.qrc

DISTFILES += \
    icons/close.ico \
    icons/leaf.ico \
    icons/location.ico \
    icons/refresh.ico \
    icons/search.ico \
    images/weaUI.png \
    weatherIcons/day/undefined.png \
    weatherIcons/day/�е�����.png \
    weatherIcons/day/�е���ѩ.png \
    weatherIcons/day/����.png \
    weatherIcons/day/��ѩ.png \
    weatherIcons/day/����.png \
    weatherIcons/day/����.png \
    weatherIcons/day/�󵽱���.png \
    weatherIcons/day/�󵽱�ѩ.png \
    weatherIcons/day/����.png \
    weatherIcons/day/���굽�ش���.png \
    weatherIcons/day/����.png \
    weatherIcons/day/��ѩ.png \
    weatherIcons/day/С������.png \
    weatherIcons/day/С����ѩ.png \
    weatherIcons/day/С��.png \
    weatherIcons/day/Сѩ.png \
    weatherIcons/day/ǿɳ����.png \
    weatherIcons/day/��ɳ.png \
    weatherIcons/day/��.png \
    weatherIcons/day/����.png \
    weatherIcons/day/���굽����.png \
    weatherIcons/day/��ѩ.png \
    weatherIcons/day/ɳ����.png \
    weatherIcons/day/����.png \
    weatherIcons/day/�ش���.png \
    weatherIcons/day/��.png \
    weatherIcons/day/����.png \
    weatherIcons/day/��ѩ.png \
    weatherIcons/day/��.png \
    weatherIcons/day/���ѩ.png \
    weatherIcons/day/ѩ.png \
    weatherIcons/day/������.png \
    weatherIcons/day/��������б���.png \
    weatherIcons/day/��.png \
    weatherIcons/day/��.png \
    weatherIcons/night/undefined.png \
    weatherIcons/night/�е�����.png \
    weatherIcons/night/�е���ѩ.png \
    weatherIcons/night/����.png \
    weatherIcons/night/��ѩ.png \
    weatherIcons/night/����.png \
    weatherIcons/night/����.png \
    weatherIcons/night/�󵽱���.png \
    weatherIcons/night/�󵽱�ѩ.png \
    weatherIcons/night/����.png \
    weatherIcons/night/���굽�ش���.png \
    weatherIcons/night/����.png \
    weatherIcons/night/��ѩ.png \
    weatherIcons/night/С������.png \
    weatherIcons/night/С����ѩ.png \
    weatherIcons/night/С��.png \
    weatherIcons/night/Сѩ.png \
    weatherIcons/night/ǿɳ����.png \
    weatherIcons/night/��ɳ.png \
    weatherIcons/night/��.png \
    weatherIcons/night/����.png \
    weatherIcons/night/���굽����.png \
    weatherIcons/night/��ѩ.png \
    weatherIcons/night/ɳ����.png \
    weatherIcons/night/����.png \
    weatherIcons/night/�ش���.png \
    weatherIcons/night/��.png \
    weatherIcons/night/����.png \
    weatherIcons/night/��ѩ.png \
    weatherIcons/night/��.png \
    weatherIcons/night/���ѩ.png \
    weatherIcons/night/ѩ.png \
    weatherIcons/night/������.png \
    weatherIcons/night/��������б���.png \
    weatherIcons/night/��.png \
    weatherIcons/night/��.png
