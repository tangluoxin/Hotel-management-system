#include "member.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QDebug>

const QString gDatabaseName ="./hotel.db" ;
const QString gConnectionName = "testConnection";


member::member()
{}


QSqlDatabase member::getDatabaseConnection(QString connName, QString databaseName)
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
bool member::createmembertable(){
    QSqlDatabase db = getDatabaseConnection(gConnectionName, gDatabaseName);


    // 1.打开数据
    if (!db.open())
    {
        return false;
    }


    QString b = QString("CREATE TABLE Member(no varchar(50), name varchar(50), sex varchar(50), password varchar(50), telephone varchar(50), address varchar(50), vip varchar(50))");

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

//插入会员数据
bool member::insertmember(QString no, QString name, QString sex, QString password,
                          QString telephone, QString address, QString vip)
{
    QSqlDatabase db = getDatabaseConnection(gConnectionName, gDatabaseName);


    // 1.打开数据
    if (!db.open())
    {
        return false;
    }
    QString a = QString("insert into member(no,name,sex,password,telephone,address,vip) values('%1','%2','%3','%4','%5','%6','%7')")
            .arg(no).arg(name).arg(sex).arg(password).arg(telephone).arg(address).arg(vip);
    QSqlQuery query(db);
    bool buscess = query.exec(a);
    if(!buscess)
    {
        qDebug("error");
    }
    else
    {
        qDebug("sucess");
    }

    //    db.close();
    return true;
}

int member::identity(QString name)
{
    QSqlDatabase db = member::getDatabaseConnection(gConnectionName,gDatabaseName);
    if(db.open())

    {

        //数据库操作
        QSqlQuery query(db);


        if( query.exec("SELECT * FROM member  where no >= 0"))//代表选择id=3的一行内容
        {
            qDebug()<<"ertsgssdfsdf";
            while(query.next())//遍历数据表格member每一行，从第0行到最后一行

            {

                QString m_name = query.value(1).toString().trimmed();//trimmed函数表示去除QString两边的空格

                QString vip = query.value(6).toString();

                if(name.trimmed() == m_name){
                    if(vip == "是"){return 2;}
                    else{return 1;}
                }

            }
            return 0;
        }
    }

}
