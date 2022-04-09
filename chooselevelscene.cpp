#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QPixmap>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "playscene.h"
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(400,700);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar* bar = menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu *startMenu = bar->addMenu("开始");
    //创建退出菜单项
    QAction *quitAction = startMenu->addAction("退出");
    //点击退出，实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //选择关卡音效
    QSound * chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    //返回按钮音效
    QSound * backSound = new QSound(":/res/BackButtonSound.wav",this);

    // 返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"点击了返回按钮";

        //播放返回按钮音效
        backSound->play();

        //延时返回
        QTimer::singleShot(300,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    //创建选择关卡的按钮
    for(int i=0;i<20;i++)
    {
        MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(65+i%4*75,200+i/4*75);

        //监听每个按钮的点击事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
//            QString str = QString("你选择的是第%1关").arg(i+1);
//            qDebug()<<str;

            //播放选择关卡音效
            chooseSound->play();

            //进入游戏场景
            //1>隐藏选关场景
            this->hide();
            //2>创建游戏场景
            this->play = new playScene(i+1);
            //3>设置playScene场景的位置,让每个场景都在同一位置
            play->setGeometry(this->geometry());
            //4>显示游戏场景
            this->play->show();

            connect(play,&playScene::chooseSceneBack,[=](){
                //设置chooseScene场景的位置,让每个场景都在同一位置
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = NULL;
            });
        });

        //关卡数
        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(65+i%4*75,200+i/4*75);

        //设置label上的对齐方式  水平居中和垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置让鼠标进行穿透,否则标签会阻挡按钮
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

//重写paintEvent事件， 画背景图
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    //画主背景图
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);  //根据窗口进行拉伸

    //画背景上的标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);
}






