#include "qtool.h"
#include <QObject>
#include <QDir>
#include <QApplication>
#include <QStandardPaths>

void QTool::CreateStartupMenuLink(bool IsAutoRun)
{
    QString strAppPath =  QCoreApplication::applicationDirPath() + "/SPDReader.exe";//要创建快捷方式的应用程序绝对路径
    QFile fApp(strAppPath);

    QString strMenuLink = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation) + "/";
    strMenuLink += "Startup/";

    QDir pathDir;
    pathDir.mkpath(strMenuLink);
    strMenuLink += "SPDReader.lnk";

    QFileInfo  dir(strMenuLink);
    if (dir.isFile()){
       QFile::remove(strMenuLink);
    }

    //生成开机启动快捷方式
    if(IsAutoRun){
        fApp.link(strMenuLink);
    }
}
