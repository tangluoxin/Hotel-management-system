#include "commodity.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QDebug>

const QString gDatabaseName = "./hotel.db";
const QString gConnectionName = "testConnection";

commodity::commodity()
{}

QSqlDatabase commodity::getDatabaseConnection(QString connName, QString databaseName)
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

bool commodity::createcommoditytable(){
    QSqlDatabase db = getDatabaseConnection(gConnectionName, gDatabaseName);


    // 1.打开数据
    if (!db.open())
    {
        return false;
    }


    QString b = QString("CREATE TABLE Commodity(no varchar(50), name varchar(50), type varchar(50), price int(4), unit varchar(50))");
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

void commodity::reducenumber(int count1, int count2, int count3)
{
    int number1 = 0;
    int number2 = 0;
    int number3 = 0;
    QSqlDatabase db = getDatabaseConnection(gConnectionName, gDatabaseName);


    // 1.打开数据
    if (!db.open())
    {
        qDebug()<<"werwerwre";
    }
    QSqlQuery query(db);
    if( query.exec("SELECT * FROM commodity where no >= 0"))
    {
        while(query.next())
        {
            QString no = query.value(0).toString().trimmed();//trimmed函数表示去除QString两边的空格
            int m_number = query.value(4).toInt();
            if(no == "1"){number1 = m_number - count1;}
            if(no == "2"){number2 = m_number - count2;}
            if(no == "3"){number3 = m_number - count3;}

        }
    }
    QString a = QString("update commodity set unit = %1 where no == '1'").arg(number1);
    query.exec(a);
    QString b = QString("update commodity set unit = %1 where no == '2'").arg(number2);
    query.exec(b);
    QString c = QString("update commodity set unit = %1 where no == '3'").arg(number3);
    query.exec(c);

    //    db.close();
}
