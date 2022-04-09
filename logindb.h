#ifndef LOGINDB_H
#define LOGINDB_H

#include <QWidget>
#include "mainscene.h"

namespace Ui {
class loginDB;
}

class loginDB : public QWidget
{
    Q_OBJECT

public:
    explicit loginDB(QWidget *parent = nullptr);
    ~loginDB();

private slots:
    void on_button_login_clicked();

    void on_button_cancel_clicked();


private:
    Ui::loginDB *ui;

    MainScene* ms;

    QSqlDatabase db;

};

#endif // LOGINDB_H
