HEADERS += \
    $$PWD/qspddatatype.h \
    $$PWD/qspdevent.h \
    $$PWD/qspdreadutil.h


SOURCES += \
    $$PWD/qspdreadutil.cpp

# 子工程
include ($$PWD/qwinring0/qwinring0.pri)

# 附加包含路径
INCLUDEPATH += \
           $$PWD/qwinring0 \

