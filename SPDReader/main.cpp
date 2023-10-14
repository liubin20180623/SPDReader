#include "mainwidget.h"

#include <QApplication>
#include <QConfig.h>
#include <asynclog.h>
#include <qt_windows.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QConfig & config = QConfig::instance();
    config.loadConfig("Config.ini");

    aInfo() << "Start";

    MainWidget w;
    w.showMaximized();
    return a.exec();
}
