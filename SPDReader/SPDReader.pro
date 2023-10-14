QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
RC_ICONS = $$PWD/resources/Images/GIGABYTE.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwidget.cpp \
    qspdserver.cpp

HEADERS += \
    mainwidget.h \
    qspdserver.h

FORMS += \
    mainwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include ($$PWD/mvc/mvc.pri)
include ($$PWD/qspd/qspd.pri)
include ($$PWD/qlog/qlog.pri)
include ($$PWD/qtool/qtool.pri)
include ($$PWD/qconfig/qconfig.pri)
include ($$PWD/qspdtableview/qspdtableview.pri)
include ($$PWD/qframelesshelper/qframelesshelper.pri)


INCLUDEPATH += \
        $$PWD/mvc \
        $$PWD/qlog \
        $$PWD/qspd \
        $$PWD/qtool \
        $$PWD/qconfig \
        $$PWD/qspdtableview \
        $$PWD/qframelesshelper \
        $$PWD/third_party/WinRing0/include \

# 依赖模块
win32 {
    contains(QT_ARCH, x86_64) {

    LIBS += \
    }else {
    LIBS += \
            -lstrmiids -lOle32 -lOleAut32
    }
}

# 输出目录
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/output/debug
} else {
    QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"
    DESTDIR = $$PWD/output/release
}

RESOURCES += \
    Resources/res.qrc
