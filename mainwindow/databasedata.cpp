#include "databasedata.h"
#include "member.h"
#include "staff.h"
#include <QSqlDatabase>
#include <QDebug>
#include<QSqlTableModel>
#include<QObject>
#include <QMessageBox>
#include <QSqlError>
#include<QString>
#include <QSqlQuery>

const QString gDatabaseName ="./hotel.db" ;
const QString gConnectionName = "testConnection";

DatabaseData::DatabaseData()
{
}

//用户名密码检索
bool DatabaseData::VerificationLogin(QString Username, QString Password)
{
    //把登录信息的账号密码传进来，然后跟数据库进行比较，相同则验证成功，否则失败

    //连接数据库
    //QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","testConnection");

    QSqlDatabase db = member::getDatabaseConnection(gConnectionName,gDatabaseName);

    //    db.setHostName("./hotel.db");//localhost
    //    db.setDatabaseName("Hotel");
    //    db.setUserName("qwqwq");
    //    db.setPassword("qwqwq");
    if(db.open())

    {

        //数据库操作
        //member a;
        //a.createmembertable();
        QSqlQuery query(db);//实例一个查询对象SELECT*FROMmqtt.account;


        if( query.exec("SELECT * FROM member  where no >= 0"))//代表选择id=3的一行内容
        {
            qDebug()<<"ertsgssdfsdf";
            while(query.next())//遍历数据表格member每一行，从第0行到最后一行

            {

                QString no= query.value(0).toString().trimmed();//trimmed函数表示去除QString两边的空格

                QString password=query.value(3).toString().trimmed();

                if((Username.trimmed() == no)&&(Password == password))

                {return true;}

            }
            return false;


        }
        else{
            qDebug()<<query.lastError();
        }

    }



}

//管理员用户名密码检索
bool DatabaseData::GVerificationLogin(QString name, QString word)
{
    //把登录信息的账号密码传进来，然后跟数据库进行比较，相同则验证成功，否则失败

    //连接数据库
    //QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","testConnection");

    QSqlDatabase db = staff::getDatabaseConnection(gConnectionName,gDatabaseName);

    //    db.setHostName("./hotel.db");//localhost
    //    db.setDatabaseName("Hotel");
    //    db.setUserName("qwqwq");
    //    db.setPassword("qwqwq");
    if(db.open())

    {

        //数据库操作

        QSqlQuery query(db);//实例一个查询对象SELECT*FROMmqtt.account;


        if( query.exec("SELECT * FROM staff  where no >= 0"))//代表选择id=3的一行内容
        {
            qDebug()<<"ertsgssdfsdf";
            while(query.next())//遍历数据表格member每一行，从第0行到最后一行

            {

                QString no= query.value(0).toString().trimmed();//trimmed函数表示去除QString两边的空格

                QString password=query.value(2).toString().trimmed();

                if((name.trimmed() == no)&&(word == password))

                {return true;}

            }
            return false;


        }
        else{
            qDebug()<<query.lastError();
        }

    }



}






