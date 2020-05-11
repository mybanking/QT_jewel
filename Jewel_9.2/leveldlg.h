#ifndef LEVELDLG_H
#define LEVELDLG_H

#include <QDialog>
#include <QPainter>
#include <QSound>
#include "game.h"
#include "string"

using namespace std;
/*关卡界面*/
namespace Ui {
class LevelDlg;
}

class LevelDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LevelDlg(QWidget *parent = nullptr);
    ~LevelDlg();
    string str1_string;
signals:
    //自定义信号，只需声明，不需实现
    void mainWindowBack();
protected:

    void closeEvent(QCloseEvent *event);
private slots:
    void on_game_1_clicked();
    void on_game_2_clicked();
    void on_game_3_clicked();
    void on_game_4_clicked();
    void on_game_5_clicked();
    void on_game_6_clicked();
public :
    int getMark_fromGame();
    int getTime_fromGame();
    void createGame(int i);
private:
    Ui::LevelDlg *ui;
    Game *gamedlg;
};

#endif // LEVELDLG_H
