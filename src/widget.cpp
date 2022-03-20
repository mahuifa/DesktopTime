#include "widget.h"
#include "ui_widget.h"

#include <QAction>
#include <QDateTime>
#include <QMenu>
#include <qdebug.h>
#include <QStyle>
#include <QDir>
#include "head.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    init();
    initConfig();
}

Widget::~Widget()
{
    Config::write(m_configData);
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

    m_configData.colorTime = Qt::black;
    m_configData.colorDate = Qt::black;
    m_configData.colorBg = this->palette().background().color();
    m_configData.fontTime = ui->label_time->font();
    m_configData.fontDate = ui->label_Date->font();
    m_configData.strTimeStyle = "hh:mm:ss";
    m_configData.strDateStyle = "yyyy年MM月dd日 dddd";

    this->setMouseTracking(true);                     // 开启鼠标移动监测
    ui->widget_bg->setMouseTracking(true);
    this->setWindowFlags(Qt::FramelessWindowHint);    // 取消标题栏
    this->showFullScreen();                           // 最大化显示

    m_setShowInfo = new SetShowInfo();
    connect(m_setShowInfo, &SetShowInfo::newFont, this, &Widget::on_newFont);
    connect(m_setShowInfo, &SetShowInfo::newColor, this, &Widget::on_newColor);
    connect(m_setShowInfo, &SetShowInfo::newSpace, this, &Widget::on_newSpace);
    connect(m_setShowInfo, &SetShowInfo::newBgImage, this, &Widget::on_newBgImage);
    connect(m_setShowInfo, &SetShowInfo::newStyle, this, &Widget::on_newStyle);

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
    connect(&m_timerMouse, &QTimer::timeout, this, &Widget::on_mouseTimeout);
    m_timer.start(1000);
    m_timerMouse.setInterval(3000);

    ui->label_time->setText(QDateTime::currentDateTime().toString(m_configData.strTimeStyle));
    ui->label_Date->setText(QDateTime::currentDateTime().toString(m_configData.strDateStyle));

}

void Widget::initConfig()
{
    if(!QFile::exists(Config::m_strConfigPath))
    {
        Config::write(m_configData);
    }
    else
    {
        m_configData = Config::read();
        on_newFont(m_configData.fontTime, SetShowInfo::Time);
        on_newFont(m_configData.fontDate, SetShowInfo::Date);
        on_newColor(m_configData.colorTime, SetShowInfo::Time);
        on_newColor(m_configData.colorDate, SetShowInfo::Date);
        if(m_configData.strBgImage.isEmpty())
        {
            on_newColor(m_configData.colorBg, SetShowInfo::Background);
        }
        else
        {
            on_newBgImage(m_configData.strBgImage);
        }

    }
}

void Widget::on_timeout()
{
    ui->label_time->setText(QDateTime::currentDateTime().toString(m_configData.strTimeStyle));
    ui->label_Date->setText(QDateTime::currentDateTime().toString(m_configData.strDateStyle));
}

/**
 * @brief 鼠标3秒没移动则隐藏
 */
void Widget::on_mouseTimeout()
{
    m_timerMouse.stop();
    this->setCursor(Qt::BlankCursor);
}

void Widget::on_setShowInfo()
{
    m_setShowInfo->show();
    m_setShowInfo->setFont(ui->label_time->font(), ui->label_Date->font());
}

/**
 * @brief         设置字体
 * @param font
 * @param type
 */
void Widget::on_newFont(QFont font, SetShowInfo::SetType type)
{
    if(SetShowInfo::Time == type)
    {
        ui->label_time->setFont(font);
    }
    else if(SetShowInfo::Date == type)
    {
        ui->label_Date->setFont(font);
    }
    else
    {
        ui->label_time->setFont(font);
        ui->label_Date->setFont(font);
    }
}

void Widget::on_newColor(QColor color, SetShowInfo::SetType type)
{
    QString str = QString("color: rgb(%1, %2, %3);")
            .arg(color.red())
            .arg(color.green())
            .arg(color.blue());
    if(SetShowInfo::Time == type)
    {
        m_configData.colorTime = color;
        ui->label_time->setStyleSheet(str);
    }
    else if(SetShowInfo::Date == type)
    {
        m_configData.colorDate = color;
        ui->label_Date->setStyleSheet(str);
    }
    else if(SetShowInfo::AllFont == type)
    {
        m_configData.colorTime = color;
        m_configData.colorDate = color;
        ui->label_time->setStyleSheet(str);
        ui->label_Date->setStyleSheet(str);
    }
    else
    {
        str = QString("#widget_bg{background-color: rgb(%1, %2, %3);}")
                .arg(color.red())
                .arg(color.green())
                .arg(color.blue());
        m_configData.colorBg = color;
        ui->widget_bg->setStyleSheet(str);
        m_configData.strBgImage.clear();
    }
}

void Widget::on_newBgImage(QString path)
{
    if(!QFile::exists(path))
    {
        return;
    }
    ui->widget_bg->setStyleSheet("");
    ui->widget_bg->setStyleSheet(QString("#widget_bg{border-image: url(%1);}").arg(path));
    ui->widget_bg->style()->polish(ui->widget_bg);
    m_configData.strBgImage = path;
}

void Widget::on_newStyle(QString style, SetShowInfo::SetType type)
{
    if(SetShowInfo::Time == type)
    {
        m_configData.strTimeStyle = style;
    }
    else if(SetShowInfo::Date == type)
    {
        m_configData.strDateStyle = style;
    }
    else
    {
        m_configData.strTimeStyle = style;
        m_configData.strDateStyle = style;
    }
}

void Widget::on_newSpace(int value)
{
    m_configData.space = value;
    ui->verticalLayout->setSpacing(value);
}

/**
 * @brief        鼠标移动则显示光标
 * @param event
 */
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    this->setCursor(Qt::ArrowCursor);
    m_timerMouse.start();
}

