#include "game.h"
#include "ui_game.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QSound>
#include <QMessageBox>
#include <QSqlQuery>
#include "logindlg.h"
Game::Game(int num,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    start=0;
    time_pause=0;//时间暂停
    game_pause=0;//游戏暂停
    text=num;//接受第几关，选择所需要的关卡
    size=9;//游戏地图大小9*9
    ui->setupUi(this);

    //倒计时进度条
    ui->progressBar->setRange(0,1999);

    //设置初始
    ui->progressBar->setValue(0);
   //加载图片并保存到数组中
    pix=new QPixmap[60];
    pix[0].load(":/myImage/9.jpg");
    pix[1].load(":/myImage/6.jpg");
    pix[2].load(":/myImage/7.jpg");
    pix[3].load(":/myImage/8.jpg");
    pix[4].load(":/huli.jpg");
   // pix[5].load(":/mao.png");
    pix[6].load(":/bannana.jpg");
    pix[7].load(":/bomb.png");
    pix[8].load(":/myImage/11.png");
   // pix[9].load(":/mark.png");
    pix[10].load(":/guoguan.jpg");
    pix[11].load(":/ice.jpg");
    pix[12].load(":/caise.png");
    pix[13].load(":/dianji.png");
  // pix[14].load(":/bobing.png");

    pix[16].load(":/shuxiong.png");
    pix[17].load(":/shulan.png");
    pix[18].load(":/shuji.png");
    pix[19].load(":/shuwa.png");
    pix[20].load(":/shuhuli.png");
   //pix[21].load(":/shumao.png");

    pix[32].load(":/hengxiong.png");
    pix[33].load(":/henglan.png");
    pix[34].load(":/hengji.png");
    pix[35].load(":/hengwa.png");
    pix[36].load(":/henghuli.png");
   // pix[37].load(":/hengmao.png");

    pix[48].load(":/quanxiong.png");
    pix[49].load(":/quanlan.png");
    pix[50].load(":/quanji.png");
    pix[51].load(":/quanwa.png");
    pix[52].load(":/quanhuli.png");
   // pix[53].load("");

    //初始化储存宝石数组，二维数组
    jewels=new jewel*[size];
    for(int i=0;i<size;i++){
        jewels[i]=new jewel[size];
    }
    //初始化储存特效缓存数组，一维数组
    specialJewels=new  jewel[size*size];
    //初始化特效个数
    spJewNum=0;
    //初始化分数
    mark=0;
   //初始化第一次消除
    inital=0;
    //初始化第一次点击
    firstclick=-1;
    //选择读取的关卡数
    setText(text);
    //加载声音，并循环播放
    so = new QSound(":/myImage/BackbroundSound.wav");
    so -> play();
    so->setLoops(-1);
    //进行第一次消除
    ThreeElimination();
    //是否更新
    upDate();
    inital=1;
    //初始化为音乐不暂停
    pause=1;
    //初始化无消除现象
    flag=0;
    //设置时间
    // init TIMER.

      // 设置字体


          QFont font("宋体", 12, QFont::Bold, true);
          ui->label->setFont(font);

       //设置颜色
          QPalette pa,pb;
          pa.setColor(QPalette::WindowText,Qt::red);
          pb.setColor(QPalette::WindowText,Qt::blue);
          ui->label->setPalette(pa);

          time1= 30;
          QString num1 = QString::number(time1);
          ui->label->setText(num1);

}

Game::~Game()
{
    delete ui;
}

//画图
void Game::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//画家
    //根据储存的信息画游戏地图，
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            //画图片
            painter.drawPixmap(jewels[i][j].x,jewels[i][j].y,50,50,pix[jewels[i][j].index]);
            if(jewels[i][j].click==1){
                 painter.drawPixmap(jewels[i][j].x,jewels[i][j].y,50,50,pix[13]);
            }
        }
    }

    //画得分，字体宋体，10榜，加粗，深黄
        QString str=QString::number(mark);
        QFont font("宋体", 12, QFont::Bold, true);
        painter.setFont(font);
        painter.setPen(QColor(Qt::red));
        painter.drawText(710,140,str);

}
//鼠标监听器
void Game::mousePressEvent(QMouseEvent *e)
{
  if(!start){
        return;
  }
  //鼠标点击触发音效
  QSound::play(":/Clicked.wav");
  //根据坐标判断选中的图片
  for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){

                if(jewels[i][j].x<e->x()&&jewels[i][j].x>e->x()-50){
                    if(jewels[i][j].y<e->y()&&jewels[i][j].y>e->y()-50){
                        //不能选中冰块//不能选中空
                        if(jewels[i][j].index==11||jewels[i][j].index==8){
                            return;
                        }

                        //判断是否为第一次点击
                           //设置点击特效，并重新绘图
                            jewels[i][j].click=1;
                            repaint();


                        if(firstclick!=-1){

                            //清空点击效果，并重绘
                            jewels[firstclick/size][firstclick%size].click=0;
                            repaint();
                            //判断第二次点击是否在其上下左右
                            if(firstclick+1==i*size+j||firstclick+size==i*size+j||firstclick-1==i*size+j||firstclick-size==i*size+j){
                                //设置不可消除标志
                                flag=0;
                                    //判定是否为魔力鸟，若为魔力鸟，将消除和魔力鸟交换的颜色相同的所有动物
                                   //第一次点击的是魔力鸟
                                   if(jewels[firstclick/size][firstclick%size].index==12&&jewels[i][j].index!=12){
                                      specialJewel(i,j,firstclick);//魔力鸟特效函数

                                    }

                                    //换子，交换坐标的信息
                                    int in=jewels[i][j].index;
                                    jewels[i][j].index=jewels[firstclick/size][firstclick%size].index;
                                    jewels[firstclick/size][firstclick%size].index=in;
                                   //判定是否为魔力鸟，若为魔力鸟，将消除和魔力鸟交换的颜色相同的所有动物
                                   //第二次点击的是魔力鸟
                                    if(jewels[firstclick/size][firstclick%size].index==12&&jewels[i][j].index!=12){
                                       specialJewel(i,j,firstclick);//魔力鸟特效函数
                                     }
                                    //两次点击全是魔力鸟
                                    if(jewels[firstclick/size][firstclick%size].index==12&&jewels[i][j].index==12){
                                        //全消
                                        add(i,j,54);
                                        //存在消除现象
                                          flag=1;
                                    }


                                    //判断选中两个是否都是特效动物
                                    if(jewels[firstclick/size][firstclick%size].index>=16&& jewels[i][j].index>=16){
                                      //加入特效数组中
                                            add(i,j,jewels[i][j].index);
                                            add(firstclick/size,firstclick%size,jewels[firstclick/size][firstclick%size].index);
                                      //存在消除现象
                                        flag=1;
                                    }
                                    //进行消除
                                    ThreeElimination();
                                    //进度条
                                   int a=mark;
                                   if(mark>1999){
                                       a=1999;
                                   }
                                   ui->progressBar->setValue(a);
                                    if(inital!=0&&amazing==1){
                                        QEventLoop eventloop;
                                        QTimer::singleShot(120, &eventloop, SLOT(quit()));
                                        eventloop.exec();
                                        QSound::play(":/Amazing.wav");
                                        amazing=0;
                                    }
                                    //是否更新
                                    upDate();

                                    if(flag){//可实现消除
                                           flag=0;
                                           //清空点击效果并重绘
                                           jewels[i][j].click=0;
                                           repaint();
                                    }
                                    else{
                                        //不可实现消除
                                        //将交换的动物，交换回来
                                        //开启定时器，进行重绘游戏地图
                                        //清空点击效果并重绘
                                     jewels[i][j].click=0;
                                     id2=startTimer(100);
                                     jewels[firstclick/size][firstclick%size].index=jewels[i][j].index;
                                     jewels[i][j].index=in;
                                    }

                                    //第一次点击初始为-1
                                    firstclick=-1;
                            }
                            else{
                                //第一次点击赋值

                                firstclick=i*size+j;

                            }
                        }

                        else{
                            //第一次点击赋值
                            firstclick=i*size+j;
                        }
                    }
                }
        }
  }


}

/********************************************************************************************************/
//消除函数
void Game:: ThreeElimination(){

    int r,c;//行消除和列消除的返回值

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
             r=-1;
             c=-1;
           //先进行行删除
            if(j<size-2){
                 r=rowElimination(i,j);
            }
            //再进行列消除
            if(i<size-2){
                c= ColElimination(i,j);//列消除
            }
            //判断消除中是否有特效动物，将特效一一实现

            while(spJewNum>0){
              //实现特效，一列消除，一行消除，周围爆炸消除效果
              Del(specialJewels[spJewNum].x,specialJewels[spJewNum].y,specialJewels[spJewNum].index);
              amazing=1;
              r=1;
            }
            //根据返回值，若返回值都为—1，说明无消除现象
            if(c!=-1||r!=-1){
                //重绘游戏地图
                 repaint();
                //程序停止0.1s
                 flag=1;//存在消除现象
               if(inital!=0){
                         QEventLoop eventloop;
                         QTimer::singleShot(120, &eventloop, SLOT(quit()));
                         eventloop.exec();

                }
            }
      }
    }


//下落宝石
   int returnL= layJewel();//下落

   repaint();//重绘
   if(returnL==1){//有下落，再次判断是否还可以经行消除
        ThreeElimination();
   }

}


/***************************************************************************************/

//下落函数
int Game::layJewel(){
   //冰块消除
   int cycle=0;
   cycle=lay(7);
   //再次检查冰消除后是按列找
   int temp=0;
   int n;
   int p=0;
   int q=0;
  for(int m=0;m<size;m++){

      n=size-1;
      //动物

      while(n>=0){
          p=0;
          //空
          if(jewels[n][m].index==8){

           //记录位置
           temp=n;
           for(int l=n;l>=0;l--){
               //冰
               if(jewels[l][m].index==11){
                   p=1;
                   break;
               }//是动物
               else if(jewels[l][m].index%16>=0&&jewels[l][m].index%16<=5){
                   p=1;
                   q=1;//有下落
                   jewels[temp][m].index=jewels[l][m].index;
                   jewels[l][m].index=8;
                   break;
               }

             }
           if(p==0){
               while(temp>=0){
                   q=1;//有下落
                   rand = qrand() % 5;//产生随机数
                   jewels[temp][m].index=rand;
                   temp--;
               }


           }

          }
         n--;
      }
  }
  if(q==1){
      lay(8);
  }
   return cycle;
}
/************************************************************************/
int Game::lay(int ice){
    int cycle=0;//判断是否有下落
    //遍历并且下落
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){

              //如果有消除的图片，进行下路，随机产生图片
            if(jewels[i][j].index==ice){
                  cycle=1;//有下落

                  rand = qrand() % 5;//产生随机数
                  int k=1;
                  while(i-k>=0){//下落
                      //上方被阻塞
                      if((jewels[i-k][j].index==11||jewels[i-k][j].index==8)){
                           //左边阻塞
                          if((j-1>=0&&(jewels[i-k+1][j-1].index==11||jewels[i-k+1][j-1].index==8))||j-1<0){

                              //右边阻塞
                           if((j+1<size&&(jewels[i-k+1][j+1].index==11||jewels[i-k+1][j+1].index==8))||j+1>=size){
                                    jewels[i-k+1][j].index=8;
                                    k=9;
                                    break;
                            }//右边未阻塞
                           else{
                                //右上角未阻塞
                            if(j+1<size&&jewels[i-k][j+1].index%16>=0&&jewels[i-k][j+1].index%16<=5){
                                j=j+1;
                               jewels[i-k+1][j-1].index=jewels[i-k][j].index;

                             }//右上角阻塞
                            else{
                               jewels[i-k+1][j].index=8;
                                  k=9;
                                  break;
                             }

                            }

                          }
                          else{//左边未阻塞
                              //左上角未阻塞
                              if(j-1>=0&&jewels[i-k][j-1].index%16>=0&&jewels[i-k][j-1].index%16<=5){
                                   j=j-1;
                                   jewels[i-k+1][j+1].index=jewels[i-k][j].index;


                              }//左上角阻塞
                              else{//右边阻塞
                                  if((j+1<size&&(jewels[i-k+1][j+1].index==11||jewels[i-k+1][j+1].index==8))||j+1>=size){
                                      jewels[i-k+1][j].index=8;
                                      k=9;
                                      break;
                                  }//右边未阻塞
                                  else{
                                      //右上角未阻塞
                                      if(j+1<size&&jewels[i-k][j+1].index%16>=0&&jewels[i-k][j+1].index%16<=5){
                                           j=j+1;
                                           jewels[i-k+1][j-1].index=jewels[i-k][j].index;

                                      }//右上角阻塞
                                      else{
                                          jewels[i-k+1][j].index=8;
                                          k=9;
                                          break;
                                      }

                                  }

                              }

                          }

                      }
                      else{
                             jewels[i-k+1][j].index= jewels[i-k][j].index;

                          }
                       k++;


                  }
                  if(k!=9){

                           jewels[0][j].index=rand;
                  }


           }


         }
    }


    return cycle;

}
/*********************************************************************************/
//列消除函数
int Game:: ColElimination(int i,int j){//列消除


        int strElimination=3;//初始化，消除的个数是三个
        //初始化储存的值，两个返回值
        int c=-1;
        int d=-1;
        int a= -1;
        //是否存在三个一样的图片并且该图片不是消除图片
        if(jewels[i][j].index%16!=8&&jewels[i][j].index%16!=7&&jewels[i][j].index%16==jewels[i+1][j].index%16){

            if(jewels[i][j].index%16==jewels[i+2][j].index%16){

                //判断一列是否超过三个，超过三个继续加消除个数的长度
                while(i+strElimination<size&&jewels[i][j].index%16==jewels[i+ strElimination][j].index%16){
                    strElimination++;
                }
                //储存该坐标的图片
                c=jewels[i][j].index%16;

                //消除音乐
                if(inital!=0){
                    //设置分数
                     setMark(strElimination,1);
                     QSound::play(":/xiaochu.wav");
                }

                //判读此列是否实现行消除
                if(jewels[i][j].index>=16){
                    //把特效加入特效数组中
                    add(i,j,jewels[i][j].index);
                }
                //进行列消除
                Icemark(i,j);
                jewels[i][j].index=7;

                //判断列消除的每个动物是否存在行消除
                for(int k=1;k<strElimination;k++){

                    for(int m=0;m<=j&&m<size-2;m++){

                       //行消除
                        d=rowElimination(i+k,m)%16;
                        if(d!=-1){
                            a=d;
                        }

                    }
                    //判断消除的是否为特效，若为特效，加入特效数组
                    if(jewels[i+k][j].index>=16){
                        add(i+k,j,jewels[i+k][j].index);
                    }
                    //存在返回值，产生可以消除周围的爆炸特效//否则设置7
                    if(a!=-1){
                        jewels[i+k][j].index=a%16+16*3;
                        a=-1;
                    }else{
                        Icemark(i+k,j);
                        jewels[i+k][j].index=7;

                    }

                }
                //五连消  产生魔力鸟特效
                if( strElimination==5){

                    jewels[i+2][j].index=12;
                }//四连消，产生消除一行的直线特效
                if(strElimination==4){

                    jewels[i+1][j].index=c+16*2;
                }
                  //设置存在消除现象
                 flag=1;
            }

        }
return c;//返回是否存在消除现象

}
/***********************************************************/

 void Game::Icemark(int i,int j){//冰块得分
     if(j-1>=0&&jewels[i][j-1].index==11){
         //冰块100分
         setMark(1,10);
         jewels[i][j-1].index=7;
     }
     if(j+1<size&&jewels[i][j+1].index==11){
         //冰块100分
         setMark(1,10);
         jewels[i][j+1].index=7;
     }
     if(i-1>=0&&jewels[i-1][j].index==11){
         //冰块100分
         setMark(1,10);
         jewels[i-1][j].index=7;
     }
     if(i+1<size&&jewels[i+1][j].index==11){
         //冰块100分
         setMark(1,10);
         jewels[i+1][j].index=7;
     }

 }

/*******************************************************************************/

//行消除
int Game::rowElimination(int i,int j){//行消除
    int strElimination=3;//初始化，消除的个数是三个
     //初始化储存的值，两个返回值
    int r=-1;
    int d=-1;
    int a=-1;
    //判断一行是否存在三个一样
    if(jewels[i][j].index%16!=8&&jewels[i][j].index%16!=7&&jewels[i][j].index%16==jewels[i][j+1].index%16&&jewels[i][j+1].index%16==jewels[i][j+2].index%16){
       //判断一列是否超过三个，超过三个继续加消除个数的长度
        while(j+strElimination<size&&jewels[i][j].index%16==jewels[i][j+strElimination].index%16){
            strElimination++;
        }
        //播放消除音效
        if(inital!=0){
            //设置分数
            setMark(strElimination,1);
             QSound::play(":/xiaochu.wav");
        }
         //储存该坐标的图片
        r=jewels[i][j].index%16;

        //判断此行是否存在列消除
        for(int k=0;k<strElimination;k++){
            if(i<size-2){

               d=ColElimination(i,j+k);//列消除
               if(d!=-1){
                   a=d;
               }

            }
            //消除的是否为特效
            if(jewels[i][j+k].index>=16){
               add(i,j+k,jewels[i][j+k].index);//加入特效到特效数组
            }//存在行消除和列消除，产生周围全消的爆炸效果
            if(a!=-1){
                 jewels[i][j+k].index=a%16+16*3;
                 a=-1;
            }else{//否则设置7
                 Icemark(i,j+k);
                 jewels[i][j+k].index=7;
            }

        }
        //五连消 产生魔力鸟
        if( strElimination==5){

            jewels[i][j+2].index=12;
        }//四连消，产生消除一列的特效
        if(strElimination==4){

            jewels[i][j+1].index=r+16;
        }
        //消除现象标志
         flag=1;
    }
  return r;//返回值
}
/*******************************************************************************************************/
//定时器
void Game::timerEvent(QTimerEvent *event)
{
    static int a=0;
    if (event->timerId() == id2) {       // 判断是哪个定时器
          if(a==1){
              repaint();//重绘
              killTimer(id2);//杀死定时器
              a=0;
          }
          a++;
       }



}


/******************************************************************************************/
//重新绘图函数
void Game::on_pushButton_clicked()
{
        start =1;//开始
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(showTimelimit()));
        timer->start( 1000 );  //1000ms 表示1秒
        //设置不可点击
        ui->pushButton->setEnabled(false);


}
/***->************************************************************/
//显示时间
void Game::showTimelimit(){
    //

    // show time-limit
    if(!time_pause&&time1!=0)
    {
        time1 = time1 -1; //注意字符类型
        QString num = QString::number(time1);
        ui->label->setText(num);

    }
    if(time1==0){
        win();
        time1=-1;


    }

}

/**********************************************************************************************/
//音乐暂停按钮
void Game::on_pushButton_103_clicked()
{

           if(!pause){
            so -> play();//循环播放
            so->setLoops(-1);
            pause =1;
           }
            else{
                so->stop();//暂停
                pause=0;
            }

}
/*************************************************************************************************/
//退出监听器
void Game::closeEvent(QCloseEvent *event)
{
    //TODO: 在退出窗口之前，实现希望做的操作
    save();//保存信息
    if(pause ==1){
        so->stop();
    }
    time1=-1;
    pause=1;
    this->hide();
    if(text!=12){
            this->mainWindowBack();//返回上一层
    }



}
/****************************************************************************************************/
//选择关卡
void Game::setText(int text){//选择读取的关
    switch (text) {
         case 0:file=new QFile(":/text1.txt");break;
         case 1:file=new QFile(":/text2.txt");break;
         case 2:file=new QFile(":/text3.txt");break;
         case 3:file=new QFile(":/text4.txt");break;
         case 4:file=new QFile(":/text5.txt");break;
         case 5:file=new QFile(":/text6.txt");break;
         case 6:file=new QFile(":/text7.txt");break;
         case 7:file=new QFile(":/text8.txt");break;
         case 8:file=new QFile(":/text9.txt");break;
         case 9:file=new QFile(":/text10.txt");break;
         case 10:file=new QFile(":/text11.txt");break;
         case 11:file=new QFile(":/text12.txt");break;
         case 12:randCreate(); start =1;//开始
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(showTimelimit()));
        timer->start( 1000 );  //1000ms 表示1秒
        //设置不可点击
        ui->pushButton->setEnabled(false);break;
    }
   if(text!=12){

       file->open(QIODevice::ReadOnly|QIODevice::Text);//打开文件
       QTextStream in(file);//文件流读取
       int a;//数据
       for(int i=0;i<size;i++){
           for(int j=0;j<size;j++){
                in>>a;
                jewels[i][j].x=50+j*50;
                jewels[i][j].y=50+i*50;
                jewels[i][j].index=a;
                jewels[i][j].click=0;

           }
       }
       file->close();//关闭文件

   }


}
 void Game::randCreate(){//随机产生
     for(int i=0;i<size;i++){
         for(int j=0;j<size;j++){
              rand = qrand() % 5;
              jewels[i][j].x=50+j*50;
              jewels[i][j].y=50+i*50;
              jewels[i][j].index=rand;
              jewels[i][j].click=0;
         }
     }
     inital=0;
     ThreeElimination();
     //是否更新
     upDate();
     inital=1;
     repaint();

 }
/************************************************************************************/
//设置分数
void Game::setMark(int length,double signal){//设置分数
    //分数: 一个小动物10分，消除特效*消除动物的个数*10；
    mark=mark+10*signal*length;

    //LoginDlg *logindlg = new LoginDlg();


}




void Game::save(){

    QSqlQuery que;
    QString marking = QString::number(mark);
    QString qstr1 = QString::fromStdString(str1_string);
    qDebug() << qstr1;
    //连接数据库：设置分数
    if(text == 0){
    QString ex ="update player set score1 = "+marking+" where name='" +qstr1+"';";
    qDebug() << ex;
    que.exec(ex);
    }
    if(text == 1){
    QString ex ="update player set score2 = "+marking+" where name='" +qstr1+"';";
    qDebug() << ex;
    que.exec(ex);
    }
    if(text == 2){
   QString ex ="update player set score3 = "+marking+" where name='" +qstr1+"';";
    qDebug() << ex;
    que.exec(ex);
    }
    if(text == 3){
    QString ex ="update player set score4 = "+marking+" where name='" +qstr1+"';";
    qDebug() << ex;
    que.exec(ex);
    }
    if(text == 4){
   QString ex ="update player set score5 = "+marking+" where name='" +qstr1+"';";
    qDebug() << ex;
    que.exec(ex);
    }
    if(text == 5){
   QString ex ="update player set score6 = "+marking+" where name='" +qstr1+"';";
    qDebug() << ex;
    que.exec(ex);
    }
}
/***************************************************************/
//判断是否胜利
bool Game::win(){
    //判断分数
    if((text!=12&&mark<1999)){

        QMessageBox message(QMessageBox::NoIcon, "Fail", "Sorry！You Didn't Acomplish In Time！",QMessageBox::Yes);
        message.setIconPixmap(pix[10]);
        if(message.exec() == QMessageBox::Yes)
        {
             save();
            if(pause ==1){
                so->stop();
            }

            pause=1;
            this->hide();
            if(text!=12){
                  this->mainWindowBack();//返回上一层
            }

        }
     }
    if((mark>=1999&&text!=12)){
       start=0;
       QString str = QString::number(mark);
       QString str1 = QString::number(30-time1);
       time_pause=1;
       QString s="Great：\n Score： "+str+"min\nTime："+str1+"sec\nClick to return！";

       QMessageBox message(QMessageBox::NoIcon, "Congratulations", s,QMessageBox::Yes);
       message.setIconPixmap(pix[10]);

       if(message.exec() == QMessageBox::Yes)
       {
            save();
           if(pause ==1){
               so->stop();
           }

           pause=1;
           this->hide();
           if(text!=12){
                 this->mainWindowBack();//返回上一层
           }
      }
       return true;

    }
    else{
        return false;
    }

}
/*************************************************************************************/
//魔力鸟消除函数
void Game::specialJewel(int i,int j,int firstclick){//彩色消除函数
   //消除所有和魔力鸟交换的所有颜色相同的动物


     int a=jewels[i][j].index;
         for(int m=0;m<size;m++){
               for(int n=0;n<size;n++){
                    //直线特效和魔力鸟结合，所有相同颜色变成特效动物
                   if(a>=16&&a<=37&&jewels[m][n].index%16==a%16){
                       rand = qrand() % 2+1;//产生随机数
                       add(m,n,a%16+rand*16);//横消纵消随机

                   } //爆炸和魔力鸟结合
                   else if(a>=16&&a>=48&&jewels[m][n].index%16==a%16){
                        add(m,n,a);//颜色相同的全部爆炸
                   }//普通和魔力鸟结合
                   else if(a<16){//加入特效
                       if(jewels[m][n].index%16==a&&jewels[m][n].index>=16){
                           add(m,n,jewels[m][n].index);
                       }//消除
                       else if(jewels[m][n].index%16==a&&jewels[m][n].index<16){
                           if(inital!=0){
                                  setMark(1,2.5);//积分，特效2.5倍
                              }
                          // Icemark(m,n);
                           jewels[m][n].index=7;
                       }

                   }


               }

         }
         //清除魔力鸟
         jewels[firstclick/size][firstclick%size].index=7;
         repaint();//重绘
         if(inital!=0){
                   QEventLoop eventloop;
                   QTimer::singleShot(500, &eventloop, SLOT(quit()));
                   eventloop.exec();

          }
         ThreeElimination();
         //是否更新
         upDate();
         repaint();

}
/*******************************************************************************************/
//特效函数 一列消除，一行删除，爆炸特效
void Game::Del(int i,int j,int k){
       spJewNum--;//特效个数减一

       if(k>=16&&k<=21){//一列消除特效
           QSound::play(":/LineRemove.wav");
            //判断消除过程中，是否存在特效，存在加到特效数组中
                 for(int m=0;m<size;m++){

                        if(jewels[m][j].index==12){
                            add(m,j,jewels[m][j].index);

                        }
                         if(jewels[m][j].index>=16){
                          add(m,j,jewels[m][j].index);
                         }
                          if(inital!=0){
                            setMark(1,1.5);//直线特效分数 1.5倍
                            }
                          //判断是否是冰块
                          if(  jewels[m][j].index==11){
                              //一个冰块100分
                               setMark(1,10);
                               jewels[m][j].index=7;

                          }
                          else{
                                //Icemark(m,j);
                                jewels[m][j].index=7;
                          }

                 }

     }
     if(k>=32&&k<=37){//行消除

             QSound::play(":/LineRemove.wav");
         //判断消除过程中，是否存在特效，存在加到特效数组中
                      for(int m=0;m<size;m++){

                          if(jewels[i][m].index==12){
                              add(m,j,12);
                          }
                            if(jewels[i][m].index>=16){
                               add(i,m,jewels[i][m].index);

                             }
                            if(inital!=0){
                            setMark(1,1.5);//直线特效分数 1.5倍
                            }
                            //判断是否是冰块
                            if(jewels[i][m].index==11){
                                //一个冰块100分
                                setMark(1,10);
                                jewels[i][m].index=7;

                            }

                            else{
                                 Icemark(i,m);
                                 jewels[i][m].index=7;
                            }


                    }

        }
     if(k>=48&&k<=53){//爆炸效果
         //判断消除过程中，是否存在特效，存在加到特效数组中
                  for(int m=-1;m<=1&&i+m<size&&i+m>=0;m++){
                      for(int n=-1;n<=1&&j+n<size&&j+n>=0;n++){
                          if(jewels[i+m][j+n].index==12){
                              add(i+m,j+n,12);
                          }
                          if(jewels[i+m][j+n].index>=16){
                              add(i+m,j+n,jewels[i+m][j+n].index);
                          }
                          if(inital!=0){
                          setMark(1,2.0);//爆炸特效分数 2倍
                          }

                          //判断是否是冰块
                          if(jewels[i+m][j+n].index==11){
                              //一个冰块100分
                              setMark(1,10);
                              jewels[i+m][j+n].index=7;

                          }
                          else{
                             Icemark(i+m,j+n);

                              jewels[i+m][j+n].index=7;
                          }
                      }



                   }

      }
     if(k==54){//全消


             for(int m=0;m<size;m++){
                 for(int n=0;n<size;n++){
                     if(jewels[m][n].index==11){
                         //一个冰块100分
                         setMark(1,10);
                         jewels[m][n].index=7;
                     }
                     else{
                          setMark(1,5);
                          jewels[m][n].index=7;
                     }
                 }
             }


         //    5倍特效

     }
     if(k==12){
         rand=qrand()%5;
         for(int m=0;m<size;m++){
             for(int n=0;n<size;n++){
                 if(jewels[m][n].index>=16&&jewels[m][n].index%16==rand){
                     add(m,n,jewels[m][n].index);

                 }
                 else if(jewels[m][n].index==rand){
                     setMark(1,5);
                     jewels[m][n].index=7;

                 }

             }

         }



     }

}
/********************************************************/
//加特效到特效数组函数
 void Game::add(int i,int j,int k){//加特效到特效数组中
     spJewNum++;//个数加一
     //赋值
     specialJewels[spJewNum].x=i;
     specialJewels[spJewNum].y=j;
     specialJewels[spJewNum].index=k;

}
/********************************************************/

//游戏暂停
void Game::on_pushButton_2_clicked()
{
    QMessageBox message(QMessageBox::NoIcon, "Pause", "Continue？",QMessageBox::Yes );
    message.setIconPixmap(pix[10]);
    time_pause=1;
    if(message.exec() == QMessageBox::Yes)
    {
         time_pause=0;
    }
}
/************************************************************/
int Game::getMark(){//获得分数
    return mark;
    }
int Game::getTime(){//获得时间
    return time1;
    }
/*************************************************************/
//提示
void Game::on_Tip_clicked()
{
   Tip(1);
   QSound::play(":/tip.wav");
}
/********************************************************************/
//是否可消除
bool Game::IsDel(int i,int j){

    //魔力鸟特效
    if(jewels[i][j].index==12){
          return true;
     }//双特效 行
     else if(j+1<size&&jewels[i][j].index>=16&&jewels[i][j+1].index>=16){
          return true;
     }//双特效 列
     else if(i+1<size&&jewels[i][j].index>=16&&jewels[i+1][j].index>=16){
          return true;
     }

    //是否行消
    for(int k=0;k<j;k++){
        if(jewels[i][k].index!=8&&k+2<size&&jewels[i][k].index%16==jewels[i][k+1].index%16&&jewels[i][k+1].index%16==jewels[i][k+2].index%16){
             return true;
        }
    }
    //是否列消
   for(int k=0;k<size;k++){
     if(jewels[k][j].index!=8&&k+2<size&&jewels[k][j].index%16==jewels[k+1][j].index%16&&jewels[k][j].index%16==jewels[k+2][j].index%16){
         return true;
        }
    }
    return false;

}
/***************************************************************/
//提示
bool Game::Tip(int jug){//提示

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(j+1<size){
                //不是冰块
                if(jewels[i][j+1].index!=8&&jewels[i][j].index!=8&&jewels[i][j].index!=11&&jewels[i][j+1].index!=11){
                    //交换信息 横着交换
                     int in=jewels[i][j].index;
                     jewels[i][j].index=jewels[i][j+1].index;
                     jewels[i][j+1].index=in;
                     //判断是否可消除
                     if(IsDel(i,j)||IsDel(i,j+1)){
                         //交换信息
                          jewels[i][j+1].index=jewels[i][j].index;
                          jewels[i][j].index=in;
                          //设置提示，并重绘
                          if(jug==1){
                              jewels[i][j+1].click=1;
                              jewels[i][j].click=1;
                              repaint();
                              //取消提示，不重绘
                              jewels[i][j+1].click=0;
                              jewels[i][j].click=0;
                          }

                          return true;

                     }
                     else{
                          //交换信息
                         jewels[i][j+1].index=jewels[i][j].index;
                         jewels[i][j].index=in;
                     }

                   }
                }

             if(i+1<size){
                 //不是冰块
                 if(jewels[i][j].index!=8&&jewels[i][j].index!=11&&jewels[i+1][j].index!=11&&jewels[i+1][j].index!=8){
                     //交换信息 列交换
                      int in=jewels[i][j].index;
                      jewels[i][j].index=jewels[i+1][j].index;
                      jewels[i+1][j].index=in;
                      //判断是否可消除
                      if(IsDel(i,j)||IsDel(i+1,j)){
                           //交换信息
                           jewels[i+1][j].index=jewels[i][j].index;
                           jewels[i][j].index=in;
                            //设置提示，并重绘
                           if(jug==1){
                               jewels[i+1][j].click=1;
                               jewels[i][j].click=1;
                               repaint();
                               //取消提示，不重绘
                               jewels[i+1][j].click=0;
                               jewels[i][j].click=0;
                           }

                           return true;

                      }
                      else{ //交换信息
                          jewels[i+1][j].index=jewels[i][j].index;
                          jewels[i][j].index=in;
                      }
                 }



            }

        }

    }
   return false;
}
/*************************************************************/
//更新
bool Game::upDate(){//更新
    //不能提示了，更新
    if(!Tip(0)){
        QMessageBox message(QMessageBox::NoIcon, "Tip", "Can not shade,Whether rebrush？",QMessageBox::Yes );
        message.setIconPixmap(pix[10]);
        time_pause=1;
        if(message.exec() == QMessageBox::Yes)
        {
             time_pause=0;
        }
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                 rand = qrand() % 5;
                 jewels[i][j].x=50+j*50;
                 jewels[i][j].y=50+i*50;
                 if(jewels[i][j].index!=11){
                     jewels[i][j].index=rand;
                 }

            }
        }
        inital=0;
        ThreeElimination();
        //是否更新
        upDate();
        inital=1;
        repaint();
        return true;


    }
    return false;
}
