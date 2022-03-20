/******************************************************************************
 * @�ļ���       config.h
 * @����        �����ļ���д
 *
 * @������     mhf
 * @ʱ��       2022/03/20
 * @��ע
 *****************************************************************************/
#ifndef CONFIG_H
#define CONFIG_H
#include <QFont>
#include <QColor>
#include <QString>

typedef struct
{
    QFont fontTime;         // ʱ������
    QFont fontDate;         // ��������
    QColor colorTime;       // ʱ��������ɫ
    QColor colorDate;       // ����������ɫ
    QColor colorBg;         // ������ɫ
    QString strBgImage;     // ����ͼƬ·��
    QString strTimeStyle;   // ʱ����ʾ��ʽ
    QString strDateStyle;   // ������ʾ��ʽ
    int space;              // �����о�
}ConfigData;      // ������Ϣ

class Config
{
public:
    Config();

    static void write(const ConfigData& data);
    static ConfigData read();
    static QString m_strConfigPath;       // �����ļ�·��
};

#endif // CONFIG_H
