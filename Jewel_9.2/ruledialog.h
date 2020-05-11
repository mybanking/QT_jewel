#ifndef RULEDIALOG_H
#define RULEDIALOG_H

#include <QDialog>

namespace Ui {
class RuleDialog;
}

class RuleDialog : public QDialog
{
    Q_OBJECT


signals:
    void mainWindowBack();

public:
    explicit RuleDialog(QWidget *parent = nullptr);
    ~RuleDialog();

    void closeEvent(QCloseEvent *event);

private:
    Ui::RuleDialog *ui;
};

#endif // RULEDIALOG_H
