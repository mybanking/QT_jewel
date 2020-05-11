#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:

    MyPushButton(QString normalImg,QString pressImg = "");

    QString normalImgPath;//默认显示图片路径
    QString pressedPath;//按下后显示图片路径

    //向下跳
    void Zoom1();
    //向上跳
    void Zoom2();


signals:

public slots:
};

#endif // MYPUSHBUTTON_H
