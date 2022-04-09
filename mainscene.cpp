#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QPixmap>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //配置主场景
    //1>设置固定大小
    setFixedSize(400,700);
    //2>设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //3>设置标题
    setWindowTitle("翻金币主场景");

    //菜单栏退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //准备按下开始按钮的音效
    QSound* startSound = new QSound(":/res/TapButtonSound.wav",this);

    //开始按钮
    MyPushButton* startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5 - startBtn->width()*0.5,this->height()*0.7);

    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    //监听选择关卡的返回信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
        //设置mainScene场景的位置,让每个场景都在同一位置
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();  //选择关卡隐藏
        this->show();         //主场景显示
    });

    connect(startBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"开始按钮被按下";

        //播放开始按钮音效
        startSound->play();
        //按钮上下跳跃特效
        startBtn->zoom1();
        startBtn->zoom2();

        //延时进入到选择关卡场景
        //1>延时,为了看按钮动画
        QTimer::singleShot(500,this,[=](){
            //设置chooseScene场景的位置,让每个场景都在同一位置
            chooseScene->setGeometry(this->geometry());

            //2>自身隐藏
            this->hide();
            //3>显示选择关卡场景
            chooseScene->show();
        });

    });
}

//重写paintEvent事件， 画背景图
void MainScene::paintEvent(QPaintEvent *)
{
    //画主背景图
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);  //根据窗口进行拉伸

    //画背景上的图标
    pix.load(":/res/Title.png");
    pix.scaled(pix.width()*0.5,pix.height()*0.5);  //缩放0.5倍
    painter.drawPixmap(10,30,pix);
}

MainScene::~MainScene()
{
    delete ui;
}

