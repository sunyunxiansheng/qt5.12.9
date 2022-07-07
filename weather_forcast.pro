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
    weatherIcons/day/÷–µΩ¥Û”Í.png \
    weatherIcons/day/÷–µΩ¥Û—©.png \
    weatherIcons/day/÷–”Í.png \
    weatherIcons/day/÷–—©.png \
    weatherIcons/day/∂≥”Í.png \
    weatherIcons/day/∂‡‘∆.png \
    weatherIcons/day/¥ÛµΩ±©”Í.png \
    weatherIcons/day/¥ÛµΩ±©—©.png \
    weatherIcons/day/¥Û±©”Í.png \
    weatherIcons/day/¥Û±©”ÍµΩÃÿ¥Û±©”Í.png \
    weatherIcons/day/¥Û”Í.png \
    weatherIcons/day/¥Û—©.png \
    weatherIcons/day/–°µΩ÷–”Í.png \
    weatherIcons/day/–°µΩ÷–—©.png \
    weatherIcons/day/–°”Í.png \
    weatherIcons/day/–°—©.png \
    weatherIcons/day/«ø…≥≥æ±©.png \
    weatherIcons/day/—Ô…≥.png \
    weatherIcons/day/«Á.png \
    weatherIcons/day/±©”Í.png \
    weatherIcons/day/±©”ÍµΩ¥Û±©”Í.png \
    weatherIcons/day/±©—©.png \
    weatherIcons/day/…≥≥æ±©.png \
    weatherIcons/day/∏°≥¡.png \
    weatherIcons/day/Ãÿ¥Û±©”Í.png \
    weatherIcons/day/“ı.png \
    weatherIcons/day/’Û”Í.png \
    weatherIcons/day/’Û—©.png \
    weatherIcons/day/”Í.png \
    weatherIcons/day/”Íº–—©.png \
    weatherIcons/day/—©.png \
    weatherIcons/day/¿◊’Û”Í.png \
    weatherIcons/day/¿◊’Û”Í∞È”–±˘±¢.png \
    weatherIcons/day/ŒÌ.png \
    weatherIcons/day/ˆ≤.png \
    weatherIcons/night/undefined.png \
    weatherIcons/night/÷–µΩ¥Û”Í.png \
    weatherIcons/night/÷–µΩ¥Û—©.png \
    weatherIcons/night/÷–”Í.png \
    weatherIcons/night/÷–—©.png \
    weatherIcons/night/∂≥”Í.png \
    weatherIcons/night/∂‡‘∆.png \
    weatherIcons/night/¥ÛµΩ±©”Í.png \
    weatherIcons/night/¥ÛµΩ±©—©.png \
    weatherIcons/night/¥Û±©”Í.png \
    weatherIcons/night/¥Û±©”ÍµΩÃÿ¥Û±©”Í.png \
    weatherIcons/night/¥Û”Í.png \
    weatherIcons/night/¥Û—©.png \
    weatherIcons/night/–°µΩ÷–”Í.png \
    weatherIcons/night/–°µΩ÷–—©.png \
    weatherIcons/night/–°”Í.png \
    weatherIcons/night/–°—©.png \
    weatherIcons/night/«ø…≥≥æ±©.png \
    weatherIcons/night/—Ô…≥.png \
    weatherIcons/night/«Á.png \
    weatherIcons/night/±©”Í.png \
    weatherIcons/night/±©”ÍµΩ¥Û±©”Í.png \
    weatherIcons/night/±©—©.png \
    weatherIcons/night/…≥≥æ±©.png \
    weatherIcons/night/∏°≥¡.png \
    weatherIcons/night/Ãÿ¥Û±©”Í.png \
    weatherIcons/night/“ı.png \
    weatherIcons/night/’Û”Í.png \
    weatherIcons/night/’Û—©.png \
    weatherIcons/night/”Í.png \
    weatherIcons/night/”Íº–—©.png \
    weatherIcons/night/—©.png \
    weatherIcons/night/¿◊’Û”Í.png \
    weatherIcons/night/¿◊’Û”Í∞È”–±˘±¢.png \
    weatherIcons/night/ŒÌ.png \
    weatherIcons/night/ˆ≤.png
