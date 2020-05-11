#include "ruledialog.h"
#include "ui_ruledialog.h"
#include "mypushbutton.h"
#include "qtimer.h"

RuleDialog::RuleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RuleDialog)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/myImage/2.png"));
    this->setWindowTitle("Rule");
    ui->textEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->textEdit->setFont(QFont("Timers" , 16 ,  QFont::Bold));
}

RuleDialog::~RuleDialog()
{
    delete ui;
}


/*************************************************************************************************/
//退出监听器
void RuleDialog::closeEvent(QCloseEvent *event)
{
    //TODO: 在退出窗口之前，实现希望做的操作
    this->hide();
    this->mainWindowBack();//返回上一层

}

