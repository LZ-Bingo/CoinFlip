#include "mainscene.h"

#include <QApplication>
#include "logindb.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    loginDB log;
    log.show();

    return a.exec();
}
