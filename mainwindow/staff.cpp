#include "staff.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QDebug>

const QString gDatabaseName ="./hotel.db" ;
const QString gConnectionName = "testConnection";


staff::staff()
{}


QSqlDatabase staff::getDatabaseConnection(QString connName, QString databaseName)
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

//创建会员表
bool staff::createstafftable(){
    QSqlDatabase db = getDatabaseConnection(gConnectionName, gDatabaseName);


    // 1.打开数据
    if (!db.open())
    {
        return false;
    }


    QString b = QString("CREATE TABLE staff(no varchar(50), name varchar(50), password varchar(50), authority varchar(50))");

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

    //    db.close();
    return true;
}
