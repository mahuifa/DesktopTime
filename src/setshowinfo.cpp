#include "setshowinfo.h"
#include "ui_setshowinfo.h"
#include <QFileDialog>
#include <qdebug.h>
#include "head.h"

SetShowInfo::SetShowInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetShowInfo)
{
    ui->setupUi(this);

    this->setWindowTitle("显示设置");

    for(int i = 1; i < 100; i++)
    {
        ui->comboBox_size->addItem(QString("%1").arg(i), i);
    }

}

SetShowInfo::~SetShowInfo()
{
    delete ui;
}

/**
 * @brief         传入需要设置的字体
 * @param time    时间字体
 * @param date    日期字体
 */
void SetShowInfo::setFont(const QFont &time, const QFont &date)
{
    m_fontDate = date;
    m_fontTime = time;

    ui->comboBox_size->setCurrentText(QString("%1").arg(time.pointSize()));
    ui->fontComboBox->setCurrentFont(time);
}

void SetShowInfo::on_fontComboBox_currentFontChanged(const QFont &f)
{
    m_fontTime = f;
    m_fontTime.setPointSize(ui->comboBox_size->currentData().toInt());

    if(ui->check_time->isChecked())
    {
        emit newFont(m_fontTime, SetType::Time);
    }
    if(ui->check_date->isChecked())
    {
        emit newFont(m_fontTime, SetType::Date);
    }
}


void SetShowInfo::on_comboBox_size_activated(int index)
{
    on_fontComboBox_currentFontChanged(ui->fontComboBox->font());
}


void SetShowInfo::on_horizontalSlider_space_valueChanged(int value)
{
    emit newSpace(value);
}


void SetShowInfo::on_comboBox_activated(const QString &arg1)
{
    if(arg1 == "无")
    {
        emit newBgImage("none");
        QColor color(255, 255, 255);
        emit newColor(color, SetType::Background);
    }
    else
    {
        emit newBgImage(arg1);
    }
}


void SetShowInfo::on_but_open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "选择图片！",
                                                    "./",
                                                    "图片文件(*png *jpg)");
    ui->lineEdit_path->setText(fileName);
    emit newBgImage(fileName);
}


void SetShowInfo::on_com_time_activated(const QString &arg1)
{
    emit newStyle(arg1, SetType::Time);
}


void SetShowInfo::on_com_date_activated(const QString &arg1)
{
    emit newStyle(arg1, SetType::Date);
}


void SetShowInfo::on_but_fontColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white);
    if(ui->check_time->isChecked())
    {
        emit newColor(color, SetType::Time);
    }
    if(ui->check_date->isChecked())
    {
        emit newColor(color, SetType::Date);
    }
}


void SetShowInfo::on_but_bgColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white);
    emit newColor(color, SetType::Background);
}

