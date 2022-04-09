#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"
#include <QSqlDatabase>
#include <QSound>
#include <QLabel>

class playScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit playScene(QWidget *parent = nullptr);

    playScene(int levelNum);



    //重写paintEvent事件， 画背景图
    void paintEvent(QPaintEvent *);

    //维护每个关卡的具体数据
    int gameArray[4][4];

    MyCoin* coinBtn[4][4];

    //判断是否胜利的标志
    bool isWin;

    //从数据库获取地图数据
    void getData(int level);

    void paintCoin();

    ~playScene();

signals:
    //告诉选关窗口，点击了返回
    void chooseSceneBack();

private:

    int levelIndex;               //记录所选的关卡
    int line;                     //地图的行数
    int col;                      //地图的列数
    QVector<QVector<int>> datas;  //地图的具体数据

    QSound* backSound;  //返回按钮音效
    QSound* flipSound;  //翻金币音效
    QSound* winSound;   //胜利的音效

    QLabel* winLabel;   //胜利图片显示

};

#endif // PLAYSCENE_H
