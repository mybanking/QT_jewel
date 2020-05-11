#include "logindlg.h"
#include "ui_logindlg.h"
#include "registredlg.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QSqlQuery>
#include <QSqlRecord>

#include "mainwindow.h"

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
    this->setFixedSize(750,550);
    this->setWindowIcon(QIcon(":/myImage/2.png"));
}

void LoginDlg::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   QPixmap pix;
   pix.load(":/login.png");
   painter.drawPixmap(0,0,this->width(),this->height(),pix);

}

LoginDlg::~LoginDlg()
{
    delete ui;
}



void LoginDlg::on_loginBtn_clicked()
{

    // 判断用户名和密码是否正确，
    // 如果错误则弹出警告对话框
    mainWindow =new MainWindow;
    connect(mainWindow,&MainWindow::mainWindowBack,[=](){
        mainWindow->hide();
        this->show();
    });

    str1 = ui->userLineEdit->text();
    QString str3="select code from player where name = '"+str1+"';";
    qDebug()<<str3;
    QSqlQuery query;
        query.exec(str3);
        qDebug()<<"insert1";
        QSqlRecord rec = query.record();
        while(query.next())
        {
            qDebug()<<"insert";
            rec = query.record();
            int snamecol = rec.indexOf("code");
            QString value = query.value(snamecol).toString();
            qDebug()<<"code:"<<value;
            if(ui->userLineEdit->text()==str1&& ui->pwdLineEdit->text() ==value){
                mainWindow->str1_string = str1.toStdString();
                mainWindow->show();
                this->hide();
            }
            else{
                QMessageBox::warning(this, tr("Waring"),
                                      tr("user name or password error!"),
                                      QMessageBox::Yes);
                // 清空内容并定位光标
                      ui->userLineEdit->clear();
                      ui->pwdLineEdit->clear();
                      ui->userLineEdit->setFocus();

            }
        }

}

void LoginDlg::mousePressEvent(QMouseEvent *e)
{
   ui->showPoint->setText(tr("(%1,%2)").arg(e->x()).arg(e->y()));
}
void LoginDlg::keyPressEvent(QKeyEvent *e)
{
   int x = ui->showPoint->x();
   int y = ui->showPoint->y();
   switch (e->key())
   {
   case Qt::Key_W : ui->showPoint->move(x, y-10); break;
   case Qt::Key_S : ui->showPoint->move(x, y+10); break;
   case Qt::Key_A : ui->showPoint->move(x-10, y); break;
   case Qt::Key_D : ui->showPoint->move(x+10, y); break;
   }
}

//注册
void LoginDlg::on_register_2_clicked()
{


     registerDlg.setWindowTitle("Registration");
     QPixmap pixmap = QPixmap(":/GameBackGround.png").scaled(registerDlg.width(),registerDlg.height());
     QPalette  palette (registerDlg.palette());
     palette .setBrush(QPalette::Background, QBrush(pixmap));
     registerDlg.setPalette( palette );
     registerDlg.setModal(true);
     registerDlg.show();


}

//关闭登陆窗
void LoginDlg::on_exitBtn_clicked()
{
    this->close();
}
