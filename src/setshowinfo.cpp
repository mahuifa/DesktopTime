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

    showColor();
    connect(ui->horizontalSlider_R, &QSlider::valueChanged, this, &SetShowInfo::showColor);
    connect(ui->horizontalSlider_G, &QSlider::valueChanged, this, &SetShowInfo::showColor);
    connect(ui->horizontalSlider_B, &QSlider::valueChanged, this, &SetShowInfo::showColor);
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

void SetShowInfo::setColor(const QColor &time, const QColor &date)
{
    m_colorTime = time;
    m_colorDate = date;

    ui->horizontalSlider_R->setValue(time.red());
    ui->horizontalSlider_G->setValue(time.green());
    ui->horizontalSlider_B->setValue(time.blue());
}

void SetShowInfo::showColor()
{
    ui->label_color->setStyleSheet(QString("background-color: rgb(%1, %2, %3);")
                                   .arg(ui->horizontalSlider_R->value())
                                   .arg(ui->horizontalSlider_G->value())
                                   .arg(ui->horizontalSlider_B->value()));

    if(ui->but_font->isChecked())
    {
        if(ui->but_time->isChecked())
        {
            m_colorTime.setRed(ui->horizontalSlider_R->value());
            m_colorTime.setGreen(ui->horizontalSlider_G->value());
            m_colorTime.setBlue(ui->horizontalSlider_B->value());
        }
        else
        {
            m_colorDate.setRed(ui->horizontalSlider_R->value());
            m_colorDate.setGreen(ui->horizontalSlider_G->value());
            m_colorDate.setBlue(ui->horizontalSlider_B->value());
        }

        emit newColor(m_colorTime, m_colorDate);
    }
    else
    {
        QColor color(ui->horizontalSlider_R->value(), ui->horizontalSlider_G->value(), ui->horizontalSlider_B->value());
        emit newBgColor(color);
    }
}

void SetShowInfo::showEvent(QShowEvent *event)
{
    ui->but_time->setChecked(true);
}


void SetShowInfo::on_but_date_clicked()
{
    ui->comboBox_size->setCurrentText(QString("%1").arg(m_fontDate.pointSize()));
    ui->fontComboBox->setCurrentFont(m_fontDate);

    ui->horizontalSlider_R->setValue(m_colorDate.red());
    ui->horizontalSlider_G->setValue(m_colorDate.green());
    ui->horizontalSlider_B->setValue(m_colorDate.blue());
}


void SetShowInfo::on_but_time_clicked()
{
    ui->comboBox_size->setCurrentText(QString("%1").arg(m_fontTime.pointSize()));
    ui->fontComboBox->setCurrentFont(m_fontTime);

    ui->horizontalSlider_R->setValue(m_colorTime.red());
    ui->horizontalSlider_G->setValue(m_colorTime.green());
    ui->horizontalSlider_B->setValue(m_colorTime.blue());
}


void SetShowInfo::on_fontComboBox_currentFontChanged(const QFont &f)
{
    if(ui->but_time->isChecked())
    {
        m_fontTime = f;
        m_fontTime.setPointSize(ui->comboBox_size->currentData().toInt());
    }
    else
    {
        m_fontDate = f;
        m_fontDate.setPointSize(ui->comboBox_size->currentData().toInt());
    }
    emit newFont(m_fontTime, m_fontDate);
}


void SetShowInfo::on_comboBox_size_activated(int index)
{
    if(ui->but_time->isChecked())
    {
        m_fontTime.setPointSize(ui->comboBox_size->currentData().toInt());
    }
    else
    {
        m_fontDate.setPointSize(ui->comboBox_size->currentData().toInt());
    }
    emit newFont(m_fontTime, m_fontDate);
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
        emit newBgColor(color);
    }
    else
    {
        emit newBgImage(arg1);
        qDebug() << arg1;
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
    emit newTimeStyle(arg1);
}


void SetShowInfo::on_com_date_activated(const QString &arg1)
{
    emit newDateStyle(arg1);
}

