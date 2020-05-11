#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QPainter>
#include "ui_game.h"
#include <QMouseEvent>
#include <QtGui>
#include <QSound>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <string>

using namespace std;
//宝石储存信息，x 横坐标，y纵坐标，index是图标序号
struct jewel{
  int x;
  int y;
  int index;
  int click;
};

namespace Ui {
class Game;
}
//Game类
class Game : public QDialog
{
    Q_OBJECT

public:
    //构造器 num传进来的值代表关卡数
    explicit Game(int num,QWidget *parent = nullptr);
    //析构函数
    ~Game();
    string str1_string="";

signals:
    //自定义信号，只需声明，不需实现
    void mainWindowBack();
private slots:
    //槽

    void on_pushButton_clicked();
    void on_pushButton_103_clicked();
    void showTimelimit();
    void on_pushButton_2_clicked();

    void on_Tip_clicked();

private:
    Ui::Game *ui;
    jewel **jewels; //宝石储存
    jewel *specialJewels;//特殊效果的保存
    int spJewNum;//特殊效果的个数
    int firstclick;//第一次点击
    int id1,id2,id3;//三个定时器
    int flag;//用来判断是否存在消除现象
    int rand;//随机数
    QSound *so;//音效
    int inital;//用来初始化，把音效去掉
    int pause;//对音乐开关做判断
    int size;//游戏大小，size*size的表格
    int text;//判断读取哪一个文件的信息
    int mark;//分数
    int game_pause;//游戏暂停
    QPixmap *pix;//保存图片
    QTimer *timer;//计时
    //QTimer *timer2;//倒计时

    int time1;//时间
    bool time_pause;//时间暂停
    int start;//是否开始
    bool amazing;
protected:
    void paintEvent(QPaintEvent *);//画图函数
    void mousePressEvent(QMouseEvent *);//鼠标监听器
    void ThreeElimination();//连续三个或者四个进行消除
    int  ColElimination(int x,int y);//实现列消除
    int  rowElimination(int x,int y);//实现行消除
    int layJewel();//实现宝石下落功能函数
    int lay(int ice);//实现宝石下落功能函数
    void timerEvent(QTimerEvent *);//定时器
    bool win();
    void closeEvent(QCloseEvent *event);//关闭
    void setText(int text);//选择读取的文件
    void setMark(int length,double signal);//设置分数
    void specialJewel(int i,int j,int firstclick);//魔力鸟特效消除函数
    void Del(int i,int j,int k);//特效 消除 一行 一列 周围 消
    void add(int i,int j,int k);//加特效到特效数组中
    bool IsDel(int i,int j);//是否可以消除
    bool Tip(int jug);//提示
    bool upDate();//更新
    void Icemark(int i,int j);//冰块得分
    void save();//保存用户分数信息

    void randCreate();//随机产生
public:
    int getMark();//获得分数
    int getTime();//获得时间
    QFile *file;//文件
};

#endif // GAME_H


