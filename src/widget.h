#ifndef WIDGET_H
#define WIDGET_H

#include <QTimer>
#include <QWidget>
#include "setshowinfo.h"

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

    void on_timeout();
    void on_setShowInfo();
    void on_newFont(QFont time, QFont date);
    void on_newColor(QColor time, QColor date);
    void on_newBgColor(QColor color);
    void on_newBgImage(QString path);
    void on_newTimeStyle(QString style);
    void on_newDateStyle(QString style);

private:
    Ui::Widget *ui;

    QTimer m_timer;
    SetShowInfo* m_setShowInfo = nullptr;
    QString m_timeStyle;
    QString m_dateStyle;
};
#endif // WIDGET_H
