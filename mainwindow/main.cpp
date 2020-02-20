#include "mainwindow.h"
#include <QApplication>
#include"logindialog.h"
#include"usermodifymainwindow.h"
#include "databasedata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    UserModifyMainWindow u;
    loginDialog login;

    //    //登录成功弹出主界面
    //    if(login.exec()==QDialog::Accepted) {
    //        w.show();
    //        return a.exec();
    //    }
    //    else if(login.exec()==QDialog::Rejected) {
    //        u.show();
    //        return a.exec();
    //    }

    //    else return 0;


    DatabaseData database;
    database.VerificationLogin("aa", "bbb");

    QObject::connect(&login, SIGNAL(sigsendlogin(QString)),
                     &w, SLOT(receivelogin(QString)));

    QObject::connect(&login, SIGNAL(sigsendSig()),
                     &u, SLOT(receiveSig()));

    switch (login.exec()) {
    case QDialog::Accepted:w.show();a.exec();
        break;
    case QDialog::Rejected:a.exec();
        break;
    default:
        break;
    }




}
