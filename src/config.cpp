#include "config.h"

#include <QFileInfo>
#include <QSettings>

Config::Config()
{

}

QString Config::m_strConfigPath = "./config.ini";

void Config::write(const ConfigData &data)
{
    QSettings settings(Config::m_strConfigPath, QSettings::IniFormat);
    settings.setIniCodec("utf-8");// 解决乱码

    settings.beginGroup("color");
    settings.setValue("colorTime", data.colorTime.name());
    settings.setValue("colorDate", data.colorDate.name());
    settings.setValue("colorBg", data.colorBg.name());
    settings.endGroup();

    settings.beginGroup("font");
    settings.setValue("fontTime", data.fontTime.toString());
    settings.setValue("fontDate", data.fontDate.toString());
    settings.endGroup();

    settings.beginGroup("image");
    settings.setValue("strBgImage", data.strBgImage);
    settings.endGroup();

    settings.beginGroup("style");
    settings.setValue("strTimeStyle", data.strTimeStyle);
    settings.setValue("strDateStyle", data.strDateStyle);
    settings.endGroup();

    settings.beginGroup("space");
    settings.setValue("space", data.space);
    settings.endGroup();
}

ConfigData Config::read()
{
    ConfigData data;

    QSettings settings(Config::m_strConfigPath, QSettings::IniFormat);
    settings.setIniCodec("utf-8");// 解决乱码

    settings.beginGroup("color");
    data.colorTime.setNamedColor(settings.value("colorTime").toString());
    data.colorDate.setNamedColor(settings.value("colorDate").toString());
    data.colorBg.setNamedColor(settings.value("colorBg").toString());
    settings.endGroup();

    settings.beginGroup("font");
    data.fontTime.fromString(settings.value("fontTime").toString());
    data.fontDate.fromString(settings.value("fontDate").toString());
    settings.endGroup();

    settings.beginGroup("image");
    data.strBgImage = settings.value("strBgImage").toString();
    settings.endGroup();

    settings.beginGroup("style");
    data.strTimeStyle = settings.value("strTimeStyle").toString();
    data.strDateStyle = settings.value("strDateStyle").toString();
    settings.endGroup();

    settings.beginGroup("space");
    data.space = settings.value("space").toInt();
    settings.endGroup();

    return data;
}
