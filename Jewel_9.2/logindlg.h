#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include "registredlg.h"
#include "mainwindow.h"

namespace Ui {
class LoginDlg;
}

class LoginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget *parent = nullptr);
    ~LoginDlg();
    //绘图事件
    void paintEvent(QPaintEvent *);
    MainWindow *mainWindow;
    QString str1;



private slots:
    void on_loginBtn_clicked();

    void on_register_2_clicked();

    void on_exitBtn_clicked();

protected:
    void mousePressEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
   // void timerEvent(QTimerEvent *);
private:
    Ui::LoginDlg *ui;
    RegistreDlg registerDlg;//注册界面
   //  int id1, id2;
};

#endif // LOGINDLG_H
