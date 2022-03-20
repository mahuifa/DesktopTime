#ifndef SETSHOWINFO_H
#define SETSHOWINFO_H

#include <QFont>
#include <QWidget>
#include <qcolor.h>
#include <QColorDialog>

namespace Ui {
class SetShowInfo;
}

class SetShowInfo : public QWidget
{
    Q_OBJECT

public:
    explicit SetShowInfo(QWidget *parent = nullptr);
    ~SetShowInfo();
    enum SetType          // 判断需要设置的类型
    {
        Time,              // 时间字体
        Date,              // 日期字体
        AllFont,           // 设置所有字体
        Background         // 设备背景
    };

    void setFont(const QFont& time, const QFont& date);

signals:
    /**
     * @brief        设置字体
     * @param font   新字体
     * @param type   设置的类型是时间还是日期
     */
    void newFont(QFont font, SetType type);
    void newColor(QColor color, SetType type);       // 设置字体、背景颜色
    void newBgImage(QString path);                   // 设置背景图片
    void newSpace(int value);                        // 设置字体行距
    void newStyle(QString style, SetType type);      // 设置时间、日期显示格式


private slots:

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_comboBox_size_activated(int index);

    void on_horizontalSlider_space_valueChanged(int value);

    void on_comboBox_activated(const QString &arg1);

    void on_but_open_clicked();

    void on_com_time_activated(const QString &arg1);

    void on_com_date_activated(const QString &arg1);

    void on_but_fontColor_clicked();

    void on_but_bgColor_clicked();

private:
    Ui::SetShowInfo *ui;

    QFont m_fontTime;
    QFont m_fontDate;
    QColorDialog m_dialog;
};

#endif // SETSHOWINFO_H
