#include "usermodifymainwindow.h"
#include "ui_usermodifymainwindow.h"
#include<QSqlDatabase>
#include<QDebug>
#include<QSqlQuery>
#include<QString>
#include<QMessageBox>
#include"member.h"
#include"logindialog.h"

const QString gDatabaseName ="./hotel.db" ;
const QString gConnectionName = "testConnection";

UserModifyMainWindow::UserModifyMainWindow(QWidget *parent) ://用户信息修改窗口
    QMainWindow(parent),
    ui(new Ui::UserModifyMainWindow)
{
    ui->setupUi(this);

    //改变按钮颜色
    QString button_style="QPushButton{background-color:rgb(104, 160, 177);\
                          color: white;}"
                          "QPushButton:hover{background-color:rgb(195, 213, 223); \
                          color: white;}"
                          "QPushButton:pressed{background-color:rgb(25, 61, 95);\
                          color: white;}";
    ui->pushButton->setStyleSheet(button_style);

    //改变label颜色
    QPalette palette;

    palette.setColor(QPalette::Background, QColor(195, 213, 223));

    ui->label_2->setAutoFillBackground(true);
    ui->label_2->setPalette(palette);

    ui->label_3->setAutoFillBackground(true);
    ui->label_3->setPalette(palette);

    ui->label_4->setAutoFillBackground(true);
    ui->label_4->setPalette(palette);


    ui->pwdlineEdit->setEchoMode(QLineEdit::Password);//让密码输入时为暗文
    ui->tpwdlineEdit->setEchoMode(QLineEdit::Password);//让密码输入时为暗文

//    ui->setupUi(this);
//       //信号槽方式下父子窗体传值的测试
//       loginDialog *dlg = new loginDialog;
//       //关联信号和槽函数
//       connect(dlg,SIGNAL(sendData(QString)),this,SLOT(receiveData(QString)));
//       dlg->setModal(true); //不论是模态或者非模态都可以正常传值
//       dlg->show();
}

UserModifyMainWindow::~UserModifyMainWindow()
{
    delete ui;
}

//用户修改密码
void UserModifyMainWindow::on_pushButton_clicked()
{
    ui->pwdlineEdit->setEchoMode(QLineEdit::Password);
    QString name = ui->idlineEdit->text();
    QString password = ui->pwdlineEdit->text();
    QString tpassword = ui->tpwdlineEdit->text();
    QSqlDatabase db = member::getDatabaseConnection(gConnectionName, gDatabaseName);
    if(password==tpassword){
        // 1.打开数据
        if (!db.open())
        {

        }
        QString b = QString("update member set password = '%1' where no = '%2'").arg(password).arg(name);
        QSqlQuery query(db);
        bool buscess = query.exec(b);
        if(!buscess)
        {
            qDebug("error");
        }
        else
        {
            qDebug("sucess");
            QMessageBox::information(this,tr("提示"),tr("修改成功"),QMessageBox::Yes);
        }

    }
    else{
        QMessageBox::warning(this,tr("警告！"),tr("两次输入密码不相同"),QMessageBox::Yes);
    }

}

//接收login信号显示窗口
void UserModifyMainWindow::receiveSig()
{
    this->show();
}


