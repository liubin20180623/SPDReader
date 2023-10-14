#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QFile>
#include <QSettings>
#include <qtool.h>
#include <framelesswindowsmanager.h>
#include <utilities.h>
FRAMELESSHELPER_USE_NAMESPACE

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    init();
    m_spdServer.start();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::init()
{
    initUi();
    initConnect();

    m_spdServer.addDevice(1,(void*)ui->tableView);
    m_spdServer.addDevice(2,(void*)ui->tableView_2);
    m_spdServer.addDevice(3,(void*)ui->tableView_3);
    m_spdServer.addDevice(4,(void*)ui->tableView_4);

    QTool::instance().CreateStartupMenuLink(true);
}

void MainWidget::initUi()
{
    ui->Title_App->setText("SPD Reader V1.0");
    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->display("00:00:00");

    QFile file_0(":/qss/MainWidget.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = file_0.readAll();
    this->setStyleSheet(stylehoot_0);
    file_0.close();

    if(isMaximized() || isFullScreen())
    {
       setZoomButtonState("Max");
    }
    else
    {
       setZoomButtonState("Min");
    }
}

void MainWidget::initConnect()
{
    connect(ui->MinimizeButton, &QPushButton::clicked, this, [this](){
        this->showMinimized();
    });

    connect(ui->ZoomButton, &QPushButton::clicked, this, [this](){
        if (isMaximized() || isFullScreen()) {
            showNormal();
        } else {
            showMaximized();
        }
    });

    connect(this, &MainWidget::windowStateChanged, this, [this](){
        ui->ZoomButton->setChecked(isMaximized());
    });

    connect(ui->CloseButton, &QPushButton::clicked, this, [=](){
        m_spdServer.remove();
        QTool::instance().CreateStartupMenuLink(false);
        QApplication::exit(0);
    });


    connect(&m_spdServer,&QSPDServer::sigTimerCount,
            this,[=](int iDuration){
        int nHour,nMinute, nSecond;
        nHour = iDuration / 3600;
        nMinute = (iDuration % 3600) / 60;
        nSecond = (iDuration % 3600) % 60;
        ui->lcdNumber->display(QString("%0:%1:%2")
                               .arg(nHour,2,10,QLatin1Char('0'))
                               .arg(nMinute,2,10,QLatin1Char('0'))
                               .arg(nSecond,2,10,QLatin1Char('0')));
    });

}

void MainWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    static bool inited = false;
    if (!inited) {
        const auto win = windowHandle();
        if (win) {
            FramelessWindowsManager::addWindow(win);
            FramelessWindowsManager::setHitTestVisible(win, ui->MinimizeButton, true);
            FramelessWindowsManager::setHitTestVisible(win, ui->ZoomButton, true);
            FramelessWindowsManager::setHitTestVisible(win, ui->CloseButton, true);
            inited = true;
        }
    }
}

void MainWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange)
    {
        if (isMaximized() || isFullScreen())
        {
            setContentsMargins(0, 0, 0, 0);
        } else if (!isMinimized()) {
            const auto margin = static_cast<int>(qRound(frameBorderThickness()));
            setContentsMargins(margin, margin, margin, margin);
        }
        Q_EMIT windowStateChanged();
    }
}

bool MainWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::Resize)
    {
        if(isMaximized() || isFullScreen())
        {
            setZoomButtonState("Max");
        } else {
            setZoomButtonState("Min");
        }
    }
    return QWidget::eventFilter(watched, event);
}

void MainWidget::setWindowZoom()
{
    if(!isMaximized())
    {
        showMaximized();
        ui->verticalLayout->setContentsMargins(9,9,9,0);
        setZoomButtonState("Max");
    } else {
        showNormal();
        ui->verticalLayout->setContentsMargins(0,0,0,0);
        setZoomButtonState("Min");
    }
}

void MainWidget::setZoomButtonState(QString state)
{
    ui->ZoomButton->setProperty("State", state);
    ui->ZoomButton->setStyle(QApplication::style());
}

qreal MainWidget::frameBorderThickness() const
{
    return (static_cast<qreal>(Utilities::getWindowVisibleFrameBorderThickness(winId())) / devicePixelRatioF());
}

