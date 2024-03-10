#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnection();
    MainWindow w;
    if(test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),QObject::tr("Connection Successful"), QMessageBox::Ok);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),QObject::tr("Connection Failed"), QMessageBox::Ok);
    }
    return a.exec();
}
