#include "mainwindow.h"
#include <QApplication>
#include "logindlg.h"
#include "registredlg.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    LoginDlg loginDlg;//建立自己的类对象
    loginDlg.setWindowTitle("Login");

    loginDlg.exec();
    return a.exec();


}
