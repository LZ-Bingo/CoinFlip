/********************************************************************************
** Form generated from reading UI file 'logindb.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDB_H
#define UI_LOGINDB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginDB
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *button_login;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *button_cancel;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_passWord;
    QLineEdit *lineEdit_passWord;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_userName;
    QLineEdit *lineEdit_userName;

    void setupUi(QWidget *loginDB)
    {
        if (loginDB->objectName().isEmpty())
            loginDB->setObjectName(QString::fromUtf8("loginDB"));
        loginDB->resize(488, 391);
        widget = new QWidget(loginDB);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(70, 250, 361, 61));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        button_login = new QPushButton(widget);
        button_login->setObjectName(QString::fromUtf8("button_login"));

        horizontalLayout->addWidget(button_login);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        button_cancel = new QPushButton(widget);
        button_cancel->setObjectName(QString::fromUtf8("button_cancel"));

        horizontalLayout->addWidget(button_cancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        widget1 = new QWidget(loginDB);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(70, 160, 361, 61));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_passWord = new QLabel(widget1);
        label_passWord->setObjectName(QString::fromUtf8("label_passWord"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(20);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_passWord->sizePolicy().hasHeightForWidth());
        label_passWord->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_passWord);

        lineEdit_passWord = new QLineEdit(widget1);
        lineEdit_passWord->setObjectName(QString::fromUtf8("lineEdit_passWord"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(100);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_passWord->sizePolicy().hasHeightForWidth());
        lineEdit_passWord->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(lineEdit_passWord);

        widget2 = new QWidget(loginDB);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(70, 70, 361, 61));
        horizontalLayout_3 = new QHBoxLayout(widget2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_userName = new QLabel(widget2);
        label_userName->setObjectName(QString::fromUtf8("label_userName"));
        sizePolicy.setHeightForWidth(label_userName->sizePolicy().hasHeightForWidth());
        label_userName->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_userName);

        lineEdit_userName = new QLineEdit(widget2);
        lineEdit_userName->setObjectName(QString::fromUtf8("lineEdit_userName"));
        sizePolicy1.setHeightForWidth(lineEdit_userName->sizePolicy().hasHeightForWidth());
        lineEdit_userName->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(lineEdit_userName);


        retranslateUi(loginDB);

        QMetaObject::connectSlotsByName(loginDB);
    } // setupUi

    void retranslateUi(QWidget *loginDB)
    {
        loginDB->setWindowTitle(QCoreApplication::translate("loginDB", "Form", nullptr));
        button_login->setText(QCoreApplication::translate("loginDB", "\347\231\273\345\275\225", nullptr));
        button_cancel->setText(QCoreApplication::translate("loginDB", "\345\217\226\346\266\210", nullptr));
        label_passWord->setText(QCoreApplication::translate("loginDB", "\345\257\206\347\240\201\357\274\232", nullptr));
        label_userName->setText(QCoreApplication::translate("loginDB", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginDB: public Ui_loginDB {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDB_H
