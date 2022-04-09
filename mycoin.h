#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);

    //参数代表 传入的金币路径还是银币路径
    MyCoin(QString btnImg);

    //金币的属性
    int posX;
    int posY;
    bool flag;  //代表正反面

    //翻转效果
    void changeFlag();
    QTimer* timer1;   //正面翻反面的定时器
    QTimer* timer2;   //反面翻正面的定时器
    int min = 1;
    int max = 8;

    //执行动画的标志
    bool isAnimation = false;

    //重写 按下
    void mousePressEvent(QMouseEvent*);

    //判断是否可点击进行翻转，因为在翻转过程中，其他金币应该不可以翻转
    bool isWin = false;

signals:

};

#endif // MYCOIN_H
