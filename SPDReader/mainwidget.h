#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <qspdserver.h>

namespace Ui {
class MainWidget;
}
class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

protected:
    void showEvent(QShowEvent *event);
    void changeEvent(QEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

private:
    void init();
    void initUi();
    void initConnect();
    void setWindowZoom();
    void setZoomButtonState(QString state);
    qreal frameBorderThickness() const;

signals:
    void windowStateChanged();

private:
    Ui::MainWidget *ui;
    QSPDServer m_spdServer;
};

#endif // MAINWIDGET_H
