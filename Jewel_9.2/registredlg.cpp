#include "registredlg.h"
#include "ui_registredlg.h"
#include "query.h"
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
/********************连接数据库****************************************/
RegistreDlg::RegistreDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistreDlg)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/myImage/2.png"));


    qDebug() << QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("yang");

    if(!db.open()){
       QMessageBox::warning(this,"error",db.lastError().text());
        return;
    }
}

RegistreDlg::~RegistreDlg()
{
    delete ui;
}
/********************连接数据库和插入数据库信息****************************************/
void RegistreDlg::on_btn_ok_clicked()
{
    //插入数据库信息
    QString name = ui->name_edit->text();
    QString code = ui->code_edit->text();
    QString score1 = "0";
      QString score2 = "0";
        QString score3 = "0";
          QString score4 = "0";
            QString score5 = "0";
              QString score6 = "0";
   QString str = QString("insert into player(id,name,code,score1,score2,score3,score4,score5,score6) values('%1', '%2', '%3','%4','%5','%6','%7','%8','%9');").arg("0").arg(name).arg(code).arg(score1).arg(score2).arg(score3).arg(score4).arg(score5).arg(score6);
    qDebug()<< str;
    QSqlQuery query;
    query.exec(str);

    //弹框提示
    QMessageBox message(QMessageBox::NoIcon, "Yes", "Regedit Success!",QMessageBox::Yes );
    message.setIconPixmap(QPixmap(":/guoguan.jpg"));
    message.exec();
}

//返回退出
void RegistreDlg::on_btn_quit_clicked()
{
    this->close();
}
