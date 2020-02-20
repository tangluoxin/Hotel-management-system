#include "roomdao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QDebug>
#include<QObject>

const QString gDatabaseName = "./hotel.db";
const QString gConnectionName = "testConnection";

roomdao::roomdao()
{}

QSqlDatabase roomdao::getDatabaseConnection(QString connName, QString databaseName)
{
    QSqlDatabase db;
    // 1.加载数据库驱动
    if (QSqlDatabase::contains(connName))  // 判断是否已经存在该连接
    {
        db = QSqlDatabase::database(connName);
    }
    else
    {
        db= QSqlDatabase::addDatabase("QSQLITE", connName);

        // 2.设置数据库名
        db.setDatabaseName(databaseName);
        qDebug() << db.databaseName();

    }
    return db;
}

bool roomdao::createroomtable()
{
    // 0.获取数据库连接
    QSqlDatabase db = getDatabaseConnection(gConnectionName, gDatabaseName);


    // 1.打开数据
    if (!db.open())
    {
        return false;
    }


    QString b = QString("CREATE TABLE Room(roomno varchar(50), roomtypeno varchar(50), state varchar(50), location varchar(50), standardprice int(4), discountprice int(4), generalmemberprice int(4), vipmemberprice int (4))");
    QSqlQuery query(db);
    bool buscess = query.exec(b);
    if(!buscess)
    {
        qDebug("table is error");
    }
    else
    {
        qDebug("table is sucess");
    }

    // 关闭数据库
    //    db.close();
    return true;

}
