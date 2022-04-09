#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include "mycoin.h"
#include <QPropertyAnimation>
#include <QSqlQuery>

#define WIDTH 400
#define HEIGHT 700

playScene::playScene(int levelNum)
{
//    QString str = QString("进入了第%1关").arg(levelNum);
//    qDebug()<<str;

    this->getData(levelNum);

    this->levelIndex=levelNum;

    //初始化游戏场景
    this->setFixedSize(WIDTH,HEIGHT);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币场景");


    QMenuBar* bar = menuBar();                           //创建菜单栏
    setMenuBar(bar);    
    QMenu *startMenu = bar->addMenu("开始");             //创建开始菜单
    QAction *quitAction = startMenu->addAction("退出");  //创建退出菜单项
    //点击退出，实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });


    this->backSound = new QSound(":/res/BackButtonSound.wav",this);   //返回按钮音效
    this->flipSound = new QSound(":/res/ConFlipSound.wav",this);      //翻金币音效
    this->winSound = new QSound(":/res/LevelWinSound.wav",this);      //胜利的音效

    // 返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){

        //播放返回按钮音效
        backSound->play();

        //延时返回
        QTimer::singleShot(300,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    //显示当前关卡数
    QLabel* label = new QLabel;
    label->setParent(this);
    //设置字体样式
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(15);
    QString str1 = QString("Level：%1").arg(this->levelIndex);
    //将字体设置到标签中
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30,this->height()-50,150,50);

    //初始化每个关卡的二维数组
    for(int i = 0;i<4;i++) {
        for(int j=0 ;j<4;j++) {
            this->gameArray[i][j] = this->datas[i][j];
        }
    }

    //胜利图片显示
    this->winLabel = new QLabel();
    QPixmap temPix;
    temPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,temPix.width(),temPix.height());
    winLabel->setPixmap(temPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - temPix.width())*0.5,-temPix.height());

    this->paintCoin();

}

//重写paintEvent事件， 画背景图
void playScene::paintEvent(QPaintEvent *)
{
    //创建背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);  //根据窗口进行拉伸

    //画背景上的标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);
}

//从数据库获取初始数据
void playScene::getData(int level)
{
    QSqlQuery query;
    QString sql = QString("select line,col,datas from data where levelNum = %1").arg(level);
    query.exec(sql);
    query.next();

    line = query.value("line").toInt();
    col = query.value("col").toInt();
    QString data = query.value("datas").toString();

    //将字符串转换为地图
    int index = 0;
    for(int i=0;i<line;i++) {
        QVector<int> temp;
        for(int j=0;j<col*2-1;j++) {
            if(data[index] != ',') {
                temp.push_back(data[index].digitValue());
            }
            index++;
        }
        index++;
        datas.push_back(temp);
    }

//    //调试：打印地图具体数据
//    QTextStream cout(stdout,QIODevice::WriteOnly);
//    for(int i=0;i<line;i++) {
//        for(int j=0;j<col;j++) {
//            cout << datas[i][j] << " ";
//        }
//        cout<<endl;
    //    }
}

void playScene::paintCoin()
{
    int leftMargin = (WIDTH - 50 * this->col) / 2;
    int topMargin = (HEIGHT - 50 * this->line) /2;

    //显示金币背景图案
    for(int i=0;i<this->line;i++)
    {
        for(int j=0;j<this->col;j++)
        {
            //背景图片
            QPixmap pix = QPixmap(":/res/BoardNode.png");
            QLabel* label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(leftMargin+i*50,topMargin+j*50);

            //创建金币
            QString str;
            if(this->gameArray[i][j] ==1) {
                //显示金币
                str = ":/res/Coin0001.png";
            }
            else {
                //显示银币
                str = ":/res/Coin0008.png";
            }
            MyCoin *coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(leftMargin+2+i*50,topMargin+3+j*50);

            //给金币属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];  //1正面，0反面

            //将金币放入到金币的二维数组里，以便后期的维护
            coinBtn[i][j] = coin;



            //点击金币，进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                //播放翻金币的音效
                flipSound->play();

                //点击后，在未完成翻转前，禁止其他可以进行点击
                for(int i=0;i<this->line;i++) {
                    for(int j=0;j<this->col;j++) {
                        this->coinBtn[i][j]->isWin = true;
                    }
                }

                coin->changeFlag();
                this->gameArray[i][j] ^= 1;

                //翻转周围的金币,延时翻转
                QTimer::singleShot(300,this,[=](){
                    //1>右侧金币翻转
                    if(coin->posX + 1 <= this->line - 1) {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] ^= 1;
                    }
                    //2>左侧金币翻转
                    if(coin->posX - 1 >= 0) {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] ^= 1;
                    }
                    //3>上侧金币翻转
                    if(coin->posY + 1 <= this->col - 1) {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] ^= 1;
                    }
                    //4>下侧金币翻转
                    if(coin->posY - 1 >= 0) {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] ^= 1;
                    }

                    //翻转完后，其他金币才可以进行点击
                    for(int i=0;i<this->line;i++) {
                        for(int j=0;j<this->col;j++) {
                            this->coinBtn[i][j]->isWin = false;
                        }
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for (int i=0;i<this->line;i++) {
                        for (int j=0;j<this->col;j++) {
                            //只要有一个反面，就算失败
                            if(coinBtn[i][j]->flag == false) {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin == true) {
                        //播放胜利的音效,并无限循环播放
                        winSound->setLoops(-1);
                        winSound->play();

                        //将所有按钮的胜利标志改为true,即不能再点击金币按钮
                        for (int i=0;i<this->line;i++) {
                            for (int j=0;j<this->col;j++) {
                                coinBtn[i][j]->isWin = true;
                            }
                        }

                        //胜利图片移动下来
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+210,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();
                    }

                });
            });
        }
   }
}

playScene::~playScene()
{

}
