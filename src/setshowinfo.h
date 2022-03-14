#ifndef SETSHOWINFO_H
#define SETSHOWINFO_H

#include <QFont>
#include <QWidget>
#include <qcolor.h>

namespace Ui {
class SetShowInfo;
}

class SetShowInfo : public QWidget
{
    Q_OBJECT

public:
    explicit SetShowInfo(QWidget *parent = nullptr);
    ~SetShowInfo();

    void setFont(const QFont& time, const QFont& date);
    void setColor(const QColor& time, const QColor& date);

signals:
    void newFont(QFont time, QFont date);
    void newColor(QColor time, QColor date);
    void newBgColor(QColor color);
    void newBgImage(QString path);
    void newSpace(int value);
    void newTimeStyle(QString style);
    void newDateStyle(QString style);

private:
    void showColor();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_but_date_clicked();

    void on_but_time_clicked();

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_comboBox_size_activated(int index);

    void on_horizontalSlider_space_valueChanged(int value);

    void on_comboBox_activated(const QString &arg1);

    void on_but_open_clicked();

    void on_com_time_activated(const QString &arg1);

    void on_com_date_activated(const QString &arg1);

private:
    Ui::SetShowInfo *ui;

    QFont m_fontTime;
    QFont m_fontDate;
    QColor m_colorTime;
    QColor m_colorDate;
};

#endif // SETSHOWINFO_H
