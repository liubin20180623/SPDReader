#ifndef SPDREADOPTION_H
#define SPDREADOPTION_H
#include <qconfig.h>
#include <QSettings>

class SPDReadOption
{
public:
    SPDReadOption()
    :m_interval(120)
    ,m_type(2)
    {}

    void reset()
    {}

    int  m_type;
    int  m_interval;
};
static SPDReadOption *g_spdread_options = 0;

static void SPDOptionParser(QSettings *setting)
{
    if(g_spdread_options==0)
    {
        g_spdread_options = new SPDReadOption;
    }
    else
    {
        g_spdread_options->reset();
    }
    setting->beginGroup("Config");
    g_spdread_options->m_interval = setting->value("interval_time", 120).toInt();
    g_spdread_options->m_type     = setting->value("TYPE", 2).toInt();
    setting->endGroup();
}
REGISTER_CONFIG_PARSER(SPDOptionParser);

#endif // SPDREADOPTION_H
