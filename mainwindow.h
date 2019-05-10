#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include"cube.h"
#include <QPoint>
#include <QTextCodec>
#include <QLabel>
#define game_R 44
#define game_C 25
#define start_x 200
#define start_y 10
#define cell_size 20



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
    void Move(int);
    bool check(int);   //检测是否此方块能移动
    void createblock();
    void changestate();  //将移动的方格变成静止的
    void RemoveBlock();  //消除一行全为2的方格，即将2改为0
    bool GetGameState();  //判断游戏是否结束
    void EndGame();   //结束游戏

    virtual void timerEvent(QTimerEvent*e);

public slots:
//    void slotTimeout();
private:
    Ui::MainWindow *ui;
    QTimer Gtime;
    int region[game_C+6][game_R+6];
    int score;
    int updateTime,MoveTime;
    QPoint move_block;
    Cube *cube;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
