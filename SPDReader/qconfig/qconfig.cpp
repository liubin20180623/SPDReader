#include "qconfig.h"
#include <QSettings>
#include <QFile>
#include <QFileSystemWatcher>
#include <qt_windows.h>

static LPFNPARSECONFIG* g_configParser = NULL;
static int g_parserCapacity = 0;
static int g_parserSize = 0;
#define PARSER_INIT_SIZE 8
#define PARSER_INCREMENT 4

void registerConfigParser(LPFNPARSECONFIG lpfn)
{
    if(g_configParser == NULL)
    {
        g_configParser = (LPFNPARSECONFIG*)calloc(PARSER_INIT_SIZE,sizeof(LPFNPARSECONFIG));
        g_parserCapacity = PARSER_INIT_SIZE;
        g_parserSize = 0;
    }
    if(g_parserCapacity == g_parserSize)
    {
        g_parserCapacity += PARSER_INCREMENT;
        g_configParser = (LPFNPARSECONFIG*)realloc(g_configParser,sizeof(LPFNPARSECONFIG)*g_parserCapacity);
    }

    g_configParser[g_parserSize++] = lpfn;
}

QConfig::QConfig()
{
    m_fileWatcher = new QFileSystemWatcher(this);
    connect(m_fileWatcher,&QFileSystemWatcher::fileChanged,
            this,&QConfig::slotConfigFileChange);

}

QConfig::~QConfig()
{

}

QConfig &QConfig::instance()
{
    static QConfig config;
    return config;
}

void QConfig::loadConfig(const char *config)
{
   if(!config || !QFile::exists(config))
   {
       config = "config.conf";
       if(!QFile::exists(config)){
           return;
       }
   }
   m_fileWatcher->addPath(config);
   parseModuleConfig(config);
}

void QConfig::slotConfigFileChange(const QString &path)
{
    parseModuleConfig(path);
}

void QConfig::parseModuleConfig(const QString &path)
{
    QSettings conf(path, QSettings::IniFormat);
    for(int i = 0; i < g_parserSize; i++)
    {
        if(g_configParser[i])
        {
            g_configParser[i](&conf);
        }
    }
}
