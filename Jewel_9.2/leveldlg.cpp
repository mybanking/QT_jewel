#include "leveldlg.h"
#include "ui_leveldlg.h"
LevelDlg::LevelDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LevelDlg)
{
   ui->setupUi(this);


}

LevelDlg::~LevelDlg()
{
    delete ui;
}

void LevelDlg::createGame(int i){

    this->hide();
    gamedlg=new Game(i);
    gamedlg->str1_string=this->str1_string;
    connect(gamedlg,&Game::mainWindowBack,[=](){
        gamedlg->hide();
        this->show();
    });

    QString str = QString::number(i+1);
    QString s="Level "+str;
    gamedlg->setWindowTitle(s);
    QPixmap pixmap = QPixmap(":/gameb.png").scaled(gamedlg->width(),gamedlg->height());
    QPalette  palette (gamedlg->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    gamedlg->setPalette( palette );
    gamedlg->setModal(true);
    gamedlg->show();

}
void LevelDlg::closeEvent(QCloseEvent *event)
{
    //TODO: 在退出窗口之前，实现希望做的操作
    this->hide();
    this->mainWindowBack();

}

void LevelDlg::on_game_1_clicked()
{
    createGame(0);
}

void LevelDlg::on_game_2_clicked()
{
    createGame(1);
}

void LevelDlg::on_game_3_clicked()
{
     createGame(2);
}

void LevelDlg::on_game_4_clicked()
{
     createGame(3);
}

void LevelDlg::on_game_5_clicked()
{
    createGame(4);
}

void LevelDlg::on_game_6_clicked()
{
    createGame(5);
}
int LevelDlg::getMark_fromGame(){
    return gamedlg->getMark();
}
int LevelDlg::getTime_fromGame(){
    return gamedlg->getTime();
}
