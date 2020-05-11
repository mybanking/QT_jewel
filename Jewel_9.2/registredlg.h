#ifndef REGISTREDLG_H
#define REGISTREDLG_H

#include <QDialog>


namespace Ui {
class RegistreDlg;
}

class RegistreDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RegistreDlg(QWidget *parent = nullptr);
    ~RegistreDlg();


private slots:
    void on_btn_ok_clicked();
    void on_btn_quit_clicked();

private:
    Ui::RegistreDlg *ui;
};

#endif // REGISTREDLG_H
