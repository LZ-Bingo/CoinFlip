#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QMouseEvent>

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}

//重写自定义的构造函数  参数1：正常显示的图片路径    参数2：按下后显示的图片路径
MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(false == ret)
    {
        qDebug()<<"图片加载失败！";
        return;
    }

    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}

//特效：向下跳
void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}

//特效：向上跳
void MyPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}

//重写鼠标按下按钮
void MyPushButton::mousePressEvent(QMouseEvent* e)
{
    if(this->pressImgPath != "")  //传入的按下图片不为空，说明需要有按下状态，切换图片
    {
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);
        if(false == ret)
        {
            qDebug()<<"图片加载失败！";
            return;
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}

//重写鼠标释放按钮
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath != "")  //传入的按下图片不为空，说明需要有按下状态，切换成初始图片
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if(false == ret)
        {
            qDebug()<<"图片加载失败！";
            return;
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);
}

