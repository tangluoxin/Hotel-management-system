#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QWidget>
#include <QDialog>
#include<QDebug>
#include"staff.h"
#include<QSqlError>


const QString gDatabaseName ="./hotel.db" ;
const QString gConnectionName = "testConnection";

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);

    //改变按钮颜色
    QString button_style = "QPushButton { background-color: rgba(25, 61, 95, 70%); "
                           "color: rgb(255, 255, 255); }";
    ui->loginpushButton->setStyleSheet(button_style);
    ui->exitpushButton->setStyleSheet(button_style);
    ui->UexitpushButton->setStyleSheet(button_style);
    ui->UloginpushButton->setStyleSheet(button_style);

    ui->pwdlineEdit->setEchoMode(QLineEdit::Password);//让密码输入时为暗文
    ui->UpwdlineEdit->setEchoMode(QLineEdit::Password);//让用户登录界面密码输入为暗文
}

loginDialog::~loginDialog()
{
    delete ui;
}
/*
 * 发送登录信息函数
 */
void loginDialog::sendlogin()
{
    QString username = ui->usrlineEdit->text();
    QSqlDatabase db = staff::getDatabaseConnection(gConnectionName,gDatabaseName);
    if(db.open())

    {
        QSqlQuery query(db);


        if( query.exec("SELECT * FROM staff  where no >= 0"))
        {
            qDebug()<<"erttsrd";
            while(query.next())//遍历数据表格staff每一行，从第0行到最后一行

            {

                QString no = query.value(0).toString().trimmed();//trimmed函数表示去除QString两边的空格

                QString authority = query.value(3).toString().trimmed();

                if(username.trimmed() == no){
                    QString m_authority = authority;
                    emit sigsendlogin(m_authority);
                }

            }


        }
        else{
            qDebug()<<query.lastError();
        }

    }

}

//发送信号打开usermodify窗口
void loginDialog::sendSig()
{
    emit sigsendSig();
}

//管理员登录界面退出
void loginDialog::on_exitpushButton_clicked()
{
    close();
}

//管理员登录界面登录
void loginDialog::on_loginpushButton_clicked()
{
    QString utr = ui->usrlineEdit->text().trimmed();
    QString uts = ui->pwdlineEdit->text();
    //连接数据库
    DatabaseData database;
    //判断用户名和密码是否正确
    //如果错误则弹出警告对话框
    //读取数据库的用户名和密码
    if(database.GVerificationLogin(utr,uts))
    {
        //登录成功，则触发accept函数
        //viewUserModMW = new UserModifyMainWindow;
        //viewUserModMW->show();
        accept();
        //emit sendData(ui->UusrlineEdit->text());
        sendlogin();
    }
    else
    {
        //登录失败，清空用户编辑框，密码编辑框，设置光标到用户编辑框
        QMessageBox::warning(this,tr("警告！"),tr("用户名或者密码错误！"),QMessageBox::Yes);
        ui->UusrlineEdit->clear();//清空用户编辑框
        ui->UpwdlineEdit->clear();
        ui->UusrlineEdit->setFocus();//设置光标到用户编辑框
    }
}

//用户登录界面退出
void loginDialog::on_UexitpushButton_clicked()
{
       close();
}
//用户登录界面登录
void loginDialog::on_UloginpushButton_clicked()
{

       QString utr = ui->UusrlineEdit->text().trimmed();
       QString uts = ui->UpwdlineEdit->text();
       //连接数据库
       DatabaseData database;
       //判断用户名和密码是否正确
       //如果错误则弹出警告对话框
       //读取数据库的用户名和密码
       if(database.VerificationLogin(utr,uts))
       {
           //登录成功，则触发accept函数
           //viewUserModMW = new UserModifyMainWindow;
           //viewUserModMW->show();
           //emit sendData(ui->UusrlineEdit->text());
           sendSig();
           close();
       }
       else
       {
           //登录失败，清空用户编辑框，密码编辑框，设置光标到用户编辑框
           QMessageBox::warning(this,tr("警告！"),tr("用户名或者密码错误！"),QMessageBox::Yes);
           ui->UusrlineEdit->clear();//清空用户编辑框
           ui->UpwdlineEdit->clear();
           ui->UusrlineEdit->setFocus();//设置光标到用户编辑框
       }
}
