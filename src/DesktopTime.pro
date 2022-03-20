QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

VERSION = 1.0.1
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DESTDIR = $$PWD/../bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    config.cpp \
    main.cpp \
    setshowinfo.cpp \
    widget.cpp

HEADERS += \
    config.h \
    head.h \
    setshowinfo.h \
    widget.h

FORMS += \
    setshowinfo.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Image.qrc
