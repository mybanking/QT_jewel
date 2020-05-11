#include "query.h"
#include "ui_query.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include<QStandardItemModel>
#include <QAbstractItemView>

QStandardItemModel *model = new QStandardItemModel();
/********************初始化建立表格****************************************/

query::query(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::query)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/myImage/2.png"));
    ui->lineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->tableView->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->tableView->setModel(model);//初始化排行榜
         model->setColumnCount(9);
         model->setHeaderData(0,Qt::Horizontal,"ID");//初始化表头
         model->setHeaderData(1,Qt::Horizontal,"Name");
         model->setHeaderData(2,Qt::Horizontal,"Code");
         model->setHeaderData(3,Qt::Horizontal,"Score1");
         model->setHeaderData(4,Qt::Horizontal,"Score2");
         model->setHeaderData(5,Qt::Horizontal,"Score3");
         model->setHeaderData(6,Qt::Horizontal,"Score4");
         model->setHeaderData(7,Qt::Horizontal,"Score5");
         model->setHeaderData(8,Qt::Horizontal,"Score6");
         ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
         ui->tableView->verticalHeader()->setVisible(false);//设置为不可修改
         ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
         ui->tableView->setColumnWidth(0,100);
         ui->tableView->setColumnWidth(1,100);
         ui->tableView->setColumnWidth(2,100);
         ui->tableView->setColumnWidth(3,100);
         ui->tableView->setColumnWidth(4,100);
         ui->tableView->setColumnWidth(5,100);
         ui->tableView->setColumnWidth(6,100);
         ui->tableView->setColumnWidth(7,100);
         ui->tableView->setColumnWidth(8,100);



}

query::~query()
{
    delete ui;
}

/***************************************************************/
//查询查找功能
void query::on_pushButton_clicked()
{
    int i=0;
      QSqlQuery query;
      int index = ui->comboBox->currentIndex();
      QString cnt = ui->lineEdit->text();

      if(index == 0){//总览所有用户信息

          QString str3="select * from player;";
          query.exec(str3);

          while(query.next())
          {        QString value = query.value(0).toString();
              QString value2 = query.value(1).toString();
              QString value3 = query.value(2).toString();
              QString value4 = query.value(3).toString();
              QString value5 = query.value(4).toString();
              QString value6 = query.value(5).toString();
              QString value7 = query.value(6).toString();
              QString value8 = query.value(7).toString();
              QString value9 = query.value(8).toString();
              qDebug()<<value<<" "<<value2<<" "<<value3<<" "<<value4<<endl;
                      model->setItem(i,0,new QStandardItem(value));
                      model->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,1,new QStandardItem(value2));
                      model->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,2,new QStandardItem(value3));
                      model->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,3,new QStandardItem(value4));
                      model->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,4,new QStandardItem(value5));
                      model->item(i,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,5,new QStandardItem(value6));
                      model->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,6,new QStandardItem(value7));
                      model->item(i,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,7,new QStandardItem(value8));
                      model->item(i,7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,8,new QStandardItem(value9));
                      model->item(i,8)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      i++;  }
      }
/***************************************************************/
      if(index == 1){//排行榜模式，按名字查询某用户信息

    model->removeRows(1, model->rowCount()-1);
          QString str1 = "select * from player where name="+cnt+";";
          query.exec(str1);
          QSqlRecord rec = query.record();
          while(query.next())
          {
              rec = query.record();
              int id_num = rec.indexOf("id");
              int password = rec.indexOf("code");
              int point = rec.indexOf("score");

              QString value = query.value(0).toString();
                          QString value2 = query.value(1).toString();
                          QString value3 = query.value(2).toString();
                          QString value4 = query.value(3).toString();
                          QString value5 = query.value(4).toString();
                          QString value6 = query.value(5).toString();
                          QString value7 = query.value(6).toString();
                          QString value8 = query.value(7).toString();
                          QString value9 = query.value(8).toString();
                          qDebug()<<value<<" "<<value2<<" "<<value3<<" "<<value4<<endl;
                                  model->setItem(i,0,new QStandardItem(value));
                                  model->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                  model->setItem(i,1,new QStandardItem(value2));
                                  model->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                  model->setItem(i,2,new QStandardItem(value3));
                                  model->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                  model->setItem(i,3,new QStandardItem(value4));
                                  model->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                  model->setItem(i,4,new QStandardItem(value5));
                                  model->item(i,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                  model->setItem(i,5,new QStandardItem(value6));
                                  model->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                  model->setItem(i,6,new QStandardItem(value7));
                                  model->item(i,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                  model->setItem(i,7,new QStandardItem(value8));
                                  model->item(i,7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                  model->setItem(i,8,new QStandardItem(value9));
                                  model->item(i,8)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
          }


/***************************************************************/
      }
      if(index == 2){//排行榜模式，按关卡1成绩降序查看所有用户信息

          QString str3="select * from player;";
          query.exec(str3);

          while(query.next())
          {        QString value = query.value(0).toString();
              QString value2 = query.value(1).toString();
              QString value3 = query.value(2).toString();
              QString value4 = query.value(3).toString();
              QString value5 = query.value(4).toString();
              QString value6 = query.value(5).toString();
              QString value7 = query.value(6).toString();
              QString value8 = query.value(7).toString();
              QString value9 = query.value(8).toString();
              qDebug()<<value<<" "<<value2<<" "<<value3<<" "<<value4<<endl;
                      model->setItem(i,0,new QStandardItem(value));
                      model->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,1,new QStandardItem(value2));
                      model->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,2,new QStandardItem(value3));
                      model->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,3,new QStandardItem(value4));
                      model->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,4,new QStandardItem(value5));
                      model->item(i,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,5,new QStandardItem(value6));
                      model->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,6,new QStandardItem(value7));
                      model->item(i,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,7,new QStandardItem(value8));
                      model->item(i,7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,8,new QStandardItem(value9));
                      model->item(i,8)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      i++;  }
          model->sort(3,Qt::DescendingOrder);//降序排序
}
      if(index == 3){//排行榜模式，按关卡2成绩降序查看所有用户信息

          QString str3="select * from player;";
          query.exec(str3);

          while(query.next())
          {        QString value = query.value(0).toString();
              QString value2 = query.value(1).toString();
              QString value3 = query.value(2).toString();
              QString value4 = query.value(3).toString();
              QString value5 = query.value(4).toString();
              QString value6 = query.value(5).toString();
              QString value7 = query.value(6).toString();
              QString value8 = query.value(7).toString();
              QString value9 = query.value(8).toString();
              qDebug()<<value<<" "<<value2<<" "<<value3<<" "<<value4<<endl;
                      model->setItem(i,0,new QStandardItem(value));
                      model->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,1,new QStandardItem(value2));
                      model->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,2,new QStandardItem(value3));
                      model->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,3,new QStandardItem(value4));
                      model->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,4,new QStandardItem(value5));
                      model->item(i,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,5,new QStandardItem(value6));
                      model->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,6,new QStandardItem(value7));
                      model->item(i,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,7,new QStandardItem(value8));
                      model->item(i,7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,8,new QStandardItem(value9));
                      model->item(i,8)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      i++;  }
          model->sort(4,Qt::DescendingOrder);
}
/***************************************************************/
      if(index == 4){//排行榜模式，按关卡3成绩降序查看所有用户信息

          QString str3="select * from player;";
          query.exec(str3);

          while(query.next())
          {        QString value = query.value(0).toString();
              QString value2 = query.value(1).toString();
              QString value3 = query.value(2).toString();
              QString value4 = query.value(3).toString();
              QString value5 = query.value(4).toString();
              QString value6 = query.value(5).toString();
              QString value7 = query.value(6).toString();
              QString value8 = query.value(7).toString();
              QString value9 = query.value(8).toString();
              qDebug()<<value<<" "<<value2<<" "<<value3<<" "<<value4<<endl;
                      model->setItem(i,0,new QStandardItem(value));
                      model->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,1,new QStandardItem(value2));
                      model->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,2,new QStandardItem(value3));
                      model->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,3,new QStandardItem(value4));
                      model->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,4,new QStandardItem(value5));
                      model->item(i,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,5,new QStandardItem(value6));
                      model->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,6,new QStandardItem(value7));
                      model->item(i,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,7,new QStandardItem(value8));
                      model->item(i,7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,8,new QStandardItem(value9));
                      model->item(i,8)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      i++;  }
          model->sort(5,Qt::DescendingOrder);
}
/***************************************************************/
      if(index == 5){//排行榜模式，按关卡4成绩降序查看所有用户信息
          QString str3="select * from player;";
          query.exec(str3);

          while(query.next())
          {        QString value = query.value(0).toString();
              QString value2 = query.value(1).toString();
              QString value3 = query.value(2).toString();
              QString value4 = query.value(3).toString();
              QString value5 = query.value(4).toString();
              QString value6 = query.value(5).toString();
              QString value7 = query.value(6).toString();
              QString value8 = query.value(7).toString();
              QString value9 = query.value(8).toString();
              qDebug()<<value<<" "<<value2<<" "<<value3<<" "<<value4<<endl;
                      model->setItem(i,0,new QStandardItem(value));
                      model->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,1,new QStandardItem(value2));
                      model->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,2,new QStandardItem(value3));
                      model->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,3,new QStandardItem(value4));
                      model->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,4,new QStandardItem(value5));
                      model->item(i,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,5,new QStandardItem(value6));
                      model->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,6,new QStandardItem(value7));
                      model->item(i,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,7,new QStandardItem(value8));
                      model->item(i,7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,8,new QStandardItem(value9));
                      model->item(i,8)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      i++;  }
          model->sort(6,Qt::DescendingOrder);
}
/***************************************************************/
      if(index == 6){//排行榜模式，按关卡5成绩降序查看所有用户信息

          QString str3="select * from player;";
          query.exec(str3);

          while(query.next())
          {        QString value = query.value(0).toString();
              QString value2 = query.value(1).toString();
              QString value3 = query.value(2).toString();
              QString value4 = query.value(3).toString();
              QString value5 = query.value(4).toString();
              QString value6 = query.value(5).toString();
              QString value7 = query.value(6).toString();
              QString value8 = query.value(7).toString();
              QString value9 = query.value(8).toString();
              qDebug()<<value<<" "<<value2<<" "<<value3<<" "<<value4<<endl;
                      model->setItem(i,0,new QStandardItem(value));
                      model->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,1,new QStandardItem(value2));
                      model->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,2,new QStandardItem(value3));
                      model->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,3,new QStandardItem(value4));
                      model->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,4,new QStandardItem(value5));
                      model->item(i,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,5,new QStandardItem(value6));
                      model->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,6,new QStandardItem(value7));
                      model->item(i,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,7,new QStandardItem(value8));
                      model->item(i,7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,8,new QStandardItem(value9));
                      model->item(i,8)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      i++;  }
          model->sort(7,Qt::DescendingOrder);
}
/***************************************************************/
      if(index == 7){//排行榜模式，按关卡6成绩降序查看所有用户信息
          QString str3="select * from player;";
          query.exec(str3);

          while(query.next())
          {        QString value = query.value(0).toString();
              QString value2 = query.value(1).toString();
              QString value3 = query.value(2).toString();
              QString value4 = query.value(3).toString();
              QString value5 = query.value(4).toString();
              QString value6 = query.value(5).toString();
              QString value7 = query.value(6).toString();
              QString value8 = query.value(7).toString();
              QString value9 = query.value(8).toString();
              qDebug()<<value<<" "<<value2<<" "<<value3<<" "<<value4<<endl;
                      model->setItem(i,0,new QStandardItem(value));
                      model->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,1,new QStandardItem(value2));
                      model->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,2,new QStandardItem(value3));
                      model->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,3,new QStandardItem(value4));
                      model->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,4,new QStandardItem(value5));
                      model->item(i,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,5,new QStandardItem(value6));
                      model->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,6,new QStandardItem(value7));
                      model->item(i,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,7,new QStandardItem(value8));
                      model->item(i,7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      model->setItem(i,8,new QStandardItem(value9));
                      model->item(i,8)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                      i++;  }
          model->sort(8,Qt::DescendingOrder);
}
}
