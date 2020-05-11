#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QTableView>
#include <mypushbutton.h>
#include <QTimer>
#include <QSound>
#include <QPainter>
#include "pkgamedlg.h"
#include "ruledialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


        ui->pushButton->setText(" ");
        this->setWindowTitle("My Home");
        this->setWindowIcon(QIcon(":/myImage/2.png"));

     this->setFixedSize(1000,562);


}

void MainWindow::paintEvent(QPaintEvent *)
{
   QPainter painter1(this);
   QPixmap pix;
   pix.load(":/home.png");
   painter1.drawPixmap(0,0,this->width(),this->height(),pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*************************************************************************************************/
//退出监听器
void MainWindow::closeEvent(QCloseEvent *event)
{
    //TODO: 在退出窗口之前，实现希望做的操作
    this->hide();

    this->mainWindowBack();//返回上一层



}

void MainWindow::on_pushButton_clicked()
{
    PkGameDlg *dlg = new PkGameDlg(this);
    dlg->setGeometry(600,200,500,700);
    dlg->setWindowIcon(QIcon(":/myImage/2.png"));
    dlg->setWindowTitle("PK Hall");

    QPixmap pixmap = QPixmap(":/pkgame.png").scaled(dlg->width(),dlg->height());
    QPalette  palette (dlg->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    dlg->setPalette( palette );
    dlg->setModal(true);
    dlg->show();
}

void MainWindow::on_query_btn_clicked() //闯关监听器
{
     this->hide();
     LevelDlg *leveldlg=new LevelDlg();
     leveldlg->str1_string=this->str1_string;
     connect(leveldlg,&LevelDlg::mainWindowBack,[=](){
         leveldlg->hide();
         this->show();
     });
     leveldlg->setWindowTitle("Level Select");

     QPixmap pixmap = QPixmap(":/level.jpg").scaled(leveldlg->width(),leveldlg->height());
     QPalette  palette (leveldlg->palette());
     palette.setBrush(QPalette::Background, QBrush(pixmap));
     leveldlg->setPalette( palette );
     leveldlg->setModal(true);
     leveldlg->show();
}

void MainWindow::on_begin_clicked() //自由(畅玩)模式
{

    this->hide();
    Game *game=new Game(7);
    connect(game,&Game::mainWindowBack,[=](){
        game->hide();
        this->show();
    });

    QPixmap pixmap = QPixmap(":/gameb.png").scaled(game->width(),game->height());
    QPalette  palette (game->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    game->setWindowTitle("Free Times");
    game->setPalette( palette );
    game->setModal(true);
    game->show();


}


void MainWindow::on_rule_btn_clicked()
{
    this->hide();
    RuleDialog *ruledlg=new RuleDialog();
    connect(ruledlg,&RuleDialog::mainWindowBack,[=](){
        ruledlg->hide();
        this->show();
    });

    QPixmap pixmap = QPixmap(":/rule.png").scaled(ruledlg->width(),ruledlg->height());
    QPalette  palette (ruledlg->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    ruledlg->setPalette( palette );
    ruledlg->setModal(true);
    ruledlg->show();

}

void MainWindow::on_query_btn_2_clicked()
{

    QPixmap pixmap = QPixmap(":/query.jpg").scaled(c.width(),c.height());
    QPalette  palette (c.palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    c.setPalette( palette );
    c.setWindowTitle("Query Imformation");
    c.show();
}
