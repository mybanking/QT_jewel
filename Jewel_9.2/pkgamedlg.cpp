#include "pkgamedlg.h"
#include "ui_pkgamedlg.h"
#include "pkgamedlg.h"
#include "game.h"
#include <QDebug>


PkGameDlg::PkGameDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PkGameDlg)
{
    ui->setupUi(this);//初始化
    ui->lineEdit->setText("8080");
    ui->lineEdit->setFont(QFont("Timers" , 16 ,  QFont::Bold));
    ui->lineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_2->setFont(QFont("Timers" , 16 ,  QFont::Bold));
    ui->lineEdit_2->setText("127.0.0.1");
    ui->lineEdit_2->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->textEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->textEdit->setFont(QFont("Timers" , 16 ,  QFont::Bold));
    tcpsocket=nullptr;

    tcpsocket=new QTcpSocket(this);

    QPixmap pix;
    pix.load(":/guoguan.jpg");

    connect(tcpsocket,&QTcpSocket::connected,[=](){//如果连接成功
        ui->textEdit->setText("Success to connect server");
    });
    connect(tcpsocket,&QTcpSocket::readyRead,[=](){
        QByteArray array=tcpsocket->readAll();
        QString str=array;
        qDebug()<<str;
        if(str=="OK"){//如果已有两名玩家连入服务器，服务器返回客户端“ok”并开始游戏

           if(a==1){
               message1->close();
               a=0;
           }
           ok=new Game(12);


           ok->setWindowTitle("PK Game");
           QPixmap pixmap = QPixmap(":/gameb.png").scaled(ok->width(),ok->height());
           QPalette  palette (ok->palette());
           palette.setBrush(QPalette::Background, QBrush(pixmap));
           ok->setPalette( palette );
           ok->setModal(true);
           ok->show();

            ui->textEdit->append("Player two is ready,game is going！");
        }
        else if(str=="成功连接，等待第二位玩家进入..."){//如果当前只有一名玩家
            a=1;
            message1=new QMessageBox(QMessageBox::NoIcon, "Waiting", "Matching！Please wait for player two！",QMessageBox::Yes);
            message1->setIconPixmap(pix);
            message1->show();

        }
        else if(str=="score"){//如果查询成绩
            score=0;
            score=ok->getMark();
            tcpsocket->write(QString::number(score).toUtf8().data());//传出成绩
            qDebug()<<score<<endl;
            qDebug()<<"query"<<endl;
        }
        else if(str=="You Win!")//如果服务器返回“you win”，则此客户端玩家在pk中获胜，弹出胜利对话框
        {
                QString str=QString ::number(score);
                QMessageBox message(QMessageBox::NoIcon, "WIN", "Congratulations!！You’ve won！\nYour Score："+str,QMessageBox::Yes);
                message.setIconPixmap(pix);
                if(message.exec() == QMessageBox::Yes)
                {
                      ok->close();
                }
        }
        else if(str=="You Lose!"){//如果服务器返回“you lose”，则此客户端玩家在pk中输了，弹出失败对话框
            QMessageBox message(QMessageBox::NoIcon, "Lose", "Sorry！You Lose！",QMessageBox::Yes);
            message.setIconPixmap(pix);
            if(message.exec() == QMessageBox::Yes)
            {
                  ok->close();
            }
        }
        else
            ui->textEdit->append(array);
    });
}

PkGameDlg::~PkGameDlg()
{
    delete ui;
}

void PkGameDlg::on_pushButton_clicked()//人工向服务器发送信息
{
    QString ip=ui->lineEdit_2->text();
    qint16 port=ui->lineEdit->text().toInt();

    tcpsocket->connectToHost(QHostAddress(ip),port);
    ui->pushButton->setEnabled(false);
}

//退出
void PkGameDlg::closeEvent(QCloseEvent *event)
{
    //TODO: 在退出窗口之前，实现希望做的操作

    tcpsocket->disconnectFromHost();//主动和客户端断开连接
        tcpsocket->close();
        tcpsocket = NULL;
       ui->textEdit->setText("Disconnect with the server already!");

}


