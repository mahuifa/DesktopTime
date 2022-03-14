#include "widget.h"
#include "ui_widget.h"

#include <QAction>
#include <QDateTime>
#include <QMenu>
#include <qdebug.h>
#include <QStyle>
#include "head.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    init();
}

Widget::~Widget()
{
    if(m_setShowInfo)
    {
        m_setShowInfo->close();
        delete m_setShowInfo;
        m_setShowInfo = nullptr;
    }
    delete ui;
}

/**
 * @brief 初始化
 */
void Widget::init()
{
    m_timeStyle = "hh:mm:ss";
    m_dateStyle = "yyyy年MM月dd日 dddd";

    this->setWindowFlags(Qt::FramelessWindowHint);    // 取消标题栏
    this->showFullScreen();                           // 最大化显示
    m_setShowInfo = new SetShowInfo();
    connect(m_setShowInfo, &SetShowInfo::newFont, this, &Widget::on_newFont);
    connect(m_setShowInfo, &SetShowInfo::newColor, this, &Widget::on_newColor);
    connect(m_setShowInfo, &SetShowInfo::newSpace, ui->verticalLayout, &QVBoxLayout::setSpacing);
    connect(m_setShowInfo, &SetShowInfo::newBgColor, this, &Widget::on_newBgColor);
    connect(m_setShowInfo, &SetShowInfo::newBgImage, this, &Widget::on_newBgImage);
    connect(m_setShowInfo, &SetShowInfo::newTimeStyle, this, &Widget::on_newTimeStyle);
    connect(m_setShowInfo, &SetShowInfo::newDateStyle, this, &Widget::on_newDateStyle);

    ui->but_set->setToolButtonStyle( Qt::ToolButtonTextUnderIcon);
    ui->but_set->setPopupMode(QToolButton::InstantPopup);

    // 创建QMenu
    QMenu *menu = new QMenu(this);
    QAction* actionClose = new QAction("退出", menu);
    QAction* actionFont = new QAction("显示设置", menu);
    menu->addAction(actionClose);
    menu->addAction(actionFont);
    connect(actionClose, &QAction::triggered, this, &Widget::close);
    connect(actionFont, &QAction::triggered, this, &Widget::on_setShowInfo);

    ui->but_set->setMenu(menu);

    connect(&m_timer, &QTimer::timeout, this, &Widget::on_timeout);
    m_timer.start(1000);

    ui->label_time->setText(QDateTime::currentDateTime().toString(m_timeStyle));
    ui->label_Date->setText(QDateTime::currentDateTime().toString(m_dateStyle));
}

void Widget::on_timeout()
{
    ui->label_time->setText(QDateTime::currentDateTime().toString(m_timeStyle));
    ui->label_Date->setText(QDateTime::currentDateTime().toString(m_dateStyle));
}

void Widget::on_setShowInfo()
{
    m_setShowInfo->show();
    m_setShowInfo->setFont(ui->label_time->font(), ui->label_Date->font());
}

void Widget::on_newFont(QFont time, QFont date)
{
    ui->label_time->setFont(time);
    ui->label_Date->setFont(date);
}

void Widget::on_newColor(QColor time, QColor date)
{
    ui->label_time->setStyleSheet(QString("color: rgb(%1, %2, %3);")
                                  .arg(time.red())
                                  .arg(time.green())
                                  .arg(time.blue()));
    ui->label_Date->setStyleSheet(QString("color: rgb(%1, %2, %3);")
                                  .arg(date.red())
                                  .arg(date.green())
                                  .arg(date.blue()));
}

void Widget::on_newBgColor(QColor color)
{
    ui->widget_bg->setStyleSheet("");
    ui->widget_bg->setStyleSheet(QString("#widget_bg{background-color: rgba(%1, %2, %3, %4);}")
                                 .arg(color.red())
                                 .arg(color.green())
                                 .arg(color.blue())
                                 .arg(color.alpha()));
}

void Widget::on_newBgImage(QString path)
{
    ui->widget_bg->setStyleSheet("");
    ui->widget_bg->setStyleSheet(QString("#widget_bg{border-image: url(%1);}").arg(path));
    ui->widget_bg->style()->polish(ui->widget_bg);
}

void Widget::on_newTimeStyle(QString style)
{
    m_timeStyle = style;
}

void Widget::on_newDateStyle(QString style)
{
    m_dateStyle = style;
}

