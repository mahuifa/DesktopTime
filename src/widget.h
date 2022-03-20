#ifndef WIDGET_H
#define WIDGET_H

#include <QTimer>
#include <QWidget>
#include "setshowinfo.h"
#include "config.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void init();
    void initConfig();       // 初始化配置

    void on_timeout();
    void on_mouseTimeout();
    void on_setShowInfo();
    void on_newFont(QFont font, SetShowInfo::SetType type);
    void on_newColor(QColor color, SetShowInfo::SetType type);
    void on_newBgImage(QString path);
    void on_newStyle(QString style, SetShowInfo::SetType type);
    void on_newSpace(int value);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::Widget *ui;

    QTimer m_timer;
    QTimer m_timerMouse;
    SetShowInfo* m_setShowInfo = nullptr;
    ConfigData m_configData;
};
#endif // WIDGET_H
