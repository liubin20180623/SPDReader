#ifndef QCONFIG_H
#define QCONFIG_H
#include <QObject>

class QSettings;
class QFileSystemWatcher;

typedef void(*LPFNPARSECONFIG)(QSettings* conf);
void registerConfigParser(LPFNPARSECONFIG lpfn);
class QConfigParserRegisterHelper
{
public:
    QConfigParserRegisterHelper(LPFNPARSECONFIG lpfn)
    {
        registerConfigParser(lpfn);
    }
};
#define REGISTER_CONFIG_PARSER(fn) \
    static QConfigParserRegisterHelper g_parserRegister(fn);

class QConfig : public QObject
{
    Q_OBJECT
private:
    QConfig();
public:
    ~QConfig();
    static QConfig & instance();
    void loadConfig(const char* config);

private:
    void parseModuleConfig(const QString &path);

protected slots:
    void slotConfigFileChange(const QString &path);

private:
    QFileSystemWatcher *m_fileWatcher;

};

#endif // QCONFIG_H
