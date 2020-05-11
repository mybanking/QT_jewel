#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImg,QString pressImg )
{
    this->normalImgPath=normalImg;
    this->pressedPath=pressImg;

    QPixmap pix;
    bool ret=pix.load(this->normalImgPath);

    if(!ret)
    {
        QString str=QString("%1 图片加载失败").arg(this->normalImgPath);
        qDebug()<< str;
    }

    //设定图片大小
    this->setFixedSize(pix.width()*0.5,pix.height()*0.5);

    //设置不规则图片
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图片
    this->setIcon(pix);

    this->setIconSize(QSize(pix.width()*0.5,pix.height()*0.5));
}


//向下跳
void MyPushButton::Zoom1()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设定时间间隔
    animation->setDuration(200);
    //设置动态对象起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height() ));
    //设置动画对象结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height() ));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();

}
//向上跳
void MyPushButton::Zoom2()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设定时间间隔
    animation->setDuration(200);
    //设置动态对象起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height() ));
    //设置动画对象结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height() ));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}
