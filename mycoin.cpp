 #include "mycoin.h"
#include <QDebug>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

//参数代表 传入的金币路径还是银币路径
MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(false == ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面的信号，并且翻转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //如果翻完了，将min重置1
        if(this->min > this->max)
        {
            this->min = 1;
            isAnimation = false;
            timer1->stop();
        }
    });

    //监听反面翻正面的信号，并且翻转金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //如果翻完了，将max重置8
        if(this->min > this->max)
        {
            this->max = 8;
            isAnimation = false;
            timer2->stop();
        }
    });
}

//重写 按下
void MyCoin::mousePressEvent(QMouseEvent* e)
{
    if(this->isAnimation == true || this->isWin == true)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}


//翻转效果
void MyCoin::changeFlag()
{
    //如果是正面，翻成反面
    if(this->flag == true)
    {
        timer1->start(30);
        isAnimation = true;
        this->flag = false;
    }
    else
    {
        timer2->start(30);
        isAnimation = true;
        this->flag = true;
    }
}
