#ifndef PKGAMEDLG_H
#define PKGAMEDLG_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include "leveldlg.h"
#include <QMessageBox>
namespace Ui {
class PkGameDlg;
}

class PkGameDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PkGameDlg(QWidget *parent = nullptr);
    ~PkGameDlg();

private slots:
    void on_pushButton_clicked();





private:
    Ui::PkGameDlg *ui;
    QTcpServer *tcpserver;
    QTcpSocket *tcpsocket;

    Game *ok;
    QMessageBox *message1;
    int score;
    int a=0;

    void closeEvent(QCloseEvent *event);
};

#endif // PKGAMEDLG_H
