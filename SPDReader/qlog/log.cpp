#include "log.h"
#include <QTextStream>
#include <QDateTime>
#include <QDebug>

static const char * g_levelString[log_level_count] = {
    "CRITICAL",
    "ERROR",
    "WARN",
    "INFO",
    "DEBUG",
    "DEBUG2"
};

Logger::Logger(const QString &strLogFile, int level)
        :m_loglevel(level),m_maxSize(524288)
{
    m_file = new QFile(strLogFile);
    if(m_file && !m_file->open(
                QFile::WriteOnly | QFile::Append))
    {
        delete m_file;
        m_file = 0;
    }
}

Logger::~Logger()
{
    if(m_file)
    {
        m_file->close();
        delete m_file;
    }
}

bool Logger::isValid()
{
    return m_file !=0;
}

void Logger::setLogLevel(int level)
{
    if(level < log_critical)
    {
        m_loglevel = log_critical;
    }
    else if(level > log_debug_2)
    {
        m_loglevel = log_debug_2;
    }
    else
    {
        m_loglevel = level;
    }
}

void Logger::log(int level, const char *fmt,...)
{
    if(level > m_loglevel || !m_file) return;

    char buffer[MAX_LOG_STRING_LEN];
    va_list args;
    va_start(args,fmt);
    vsnprintf(buffer,MAX_LOG_STRING_LEN-1,fmt,args);
    va_end(args);

    QString strLogInfo = QString("%1[%2]: %3\r\n")
            .arg(QDateTime::currentDateTime()
                 .toString("yyyy-MM-dd hh:mm:ss.zzz"))
            .arg(g_levelString[level]).arg(buffer);

    log2file(strLogInfo);
}

void Logger::log(int level, const QString &content)
{
    if(level > m_loglevel || !m_file) return;
    QString strLogInfo = QString("%1[%2]: %3\r\n")
            .arg(QDateTime::currentDateTime()
                 .toString("yyyy-MM-dd hh:mm:ss.zzz"))
            .arg(g_levelString[level]).arg(content);

    log2file(strLogInfo);
}

void Logger::log2file(const QString &log)
{
    if(m_file->size() >= m_maxSize)
    {
        backup();
    }
    m_file->write(log.toLatin1());
    m_file->flush();
}

void Logger::backup()
{
    QString logFileName = m_file->fileName();
    QString magicFileName = QString("%1.magic").arg(logFileName);
    QFile magic(magicFileName);
    int number = 1;
    if(magic.exists())
    {
        magic.open(QFile::ReadWrite);
        QTextStream ts(&magic);
        ts.setCodec("UTF-8");
        ts >> number;
        number++;
        ts.seek(0);
        ts << number;
        ts.flush();
        magic.close();
    }
    else
    {
        magic.open(QFile::WriteOnly);
        QTextStream ts(&magic);
        ts.setCodec("UTF-8");
        ts << 1;
        ts.flush();
        magic.flush();
        magic.close();
    }

    QString backupName = QString("%1.%2")
            .arg(logFileName).arg(number);
    m_file->copy(backupName);
    m_file->open(QFile::WriteOnly|QFile::Truncate);
}

