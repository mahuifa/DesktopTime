/******************************************************************************
 * @文件名       config.h
 * @功能        配置文件读写
 *
 * @开发者     mhf
 * @时间       2022/03/20
 * @备注
 *****************************************************************************/
#ifndef CONFIG_H
#define CONFIG_H
#include <QFont>
#include <QColor>
#include <QString>

typedef struct
{
    QFont fontTime;         // 时间字体
    QFont fontDate;         // 日期字体
    QColor colorTime;       // 时间字体颜色
    QColor colorDate;       // 日期字体颜色
    QColor colorBg;         // 背景颜色
    QString strBgImage;     // 背景图片路径
    QString strTimeStyle;   // 时间显示样式
    QString strDateStyle;   // 日期显示样式
    int space;              // 字体行距
}ConfigData;      // 配置信息

class Config
{
public:
    Config();

    static void write(const ConfigData& data);
    static ConfigData read();
    static QString m_strConfigPath;       // 配置文件路径
};

#endif // CONFIG_H
