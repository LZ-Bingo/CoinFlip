#include "logindb.h"
#include "ui_logindb.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QString>
#include <QDebug>
#include <QSqlQuery>


loginDB::loginDB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginDB)
{
    ui->setupUi(this);

    this->setFixedSize(500,400);
    this->setWindowTitle("登录");

    //打印Qt支持的数据库驱动
    //qDebug()<<QSqlDatabase::drivers();

    //添加MySQL数据库
    db = QSqlDatabase::addDatabase("QMYSQL");
    //连接数据库
    db.setHostName("127.0.0.1");      //数据库服务器IP
    db.setUserName("study");          //数据库用户名
    db.setPassword("study");          //密码
    db.setDatabaseName("coinflip");   //使用哪个数据库
    //打开数据库
    if(!db.open())  //数据库打开失败
    {
        QMessageBox::critical(this,"错误",db.lastError().text());
        exit(0);
    }
}

loginDB::~loginDB()
{
    delete ui;
}

void loginDB::on_button_login_clicked()
{
    QString userName = ui->lineEdit_userName->text();
    QString passWord = ui->lineEdit_passWord->text();

    if(userName == "" || passWord == "") {
        return;
    }

    QSqlQuery query;
    QString sql = QString("select * from user where userName = '%1' and passWord = '%2'").arg(userName).arg(passWord);
    query.exec(sql);

    if(query.size() == 0) {
        QMessageBox::critical(this,"错误","用户名和密码错误");
        return;
    }

    this->hide();
    ms = new MainScene;
    ms->show();
}

void loginDB::on_button_cancel_clicked()
{
    ui->lineEdit_userName->clear();
    ui->lineEdit_passWord->clear();
}
