#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_mainwindow.h"
#include "game.h"
#include <QSound>
#include "leveldlg.h"
#include "query.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //绘图事件

    QSound getMusic();
    string str1_string="";

    query c;
signals:
    //自定义信号，只需声明，不需实现
    void mainWindowBack();

private slots:
    void on_pushButton_clicked();

    void on_query_btn_clicked();

    void on_begin_clicked();


    void on_rule_btn_clicked();

    void on_query_btn_2_clicked();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
