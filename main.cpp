#include "mainscn.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDesktopWidget>
#include "splashscreen.h"
#include <QThread>

QSqlQuery writeQuery;
QSqlQuery readQuery;


int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);

    SplashScreen splashScreen("C:/Users/29856/Desktop/image");
    splashScreen.move((QApplication::desktop()->width() - splashScreen.width()) / 2 ,(QApplication::desktop()->height() - splashScreen.height()) / 2);
    splashScreen.show();
    a.processEvents();

//    QThread::msleep(1000);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("library.db");
    if(db.open()){
        writeQuery = QSqlQuery(db);
        readQuery = QSqlQuery(db);
    }

    MainScn w;
    w.show();
    splashScreen.finish(&w);

    return a.exec();
}
