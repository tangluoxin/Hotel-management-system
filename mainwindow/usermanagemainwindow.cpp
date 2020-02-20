#include "usermanagemainwindow.h"
#include "ui_usermanagemainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlTableModel>
#include <QObject>
#include <QMessageBox>
#include <QSqlError>
#include <QString>
#include <QSqlQuery>
#include <QPalette>

#include"member.h"
#include"staff.h"

const QString gDatabaseName ="./hotel.db" ;
const QString gConnectionName = "testConnection";

UserManageMainWindow::UserManageMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserManageMainWindow)
{
    ui->setupUi(this);

    //改变按键颜色
    QString button_style="QPushButton{background-color:rgb(129, 207, 209);\
                          color: white;}"
                          "QPushButton:hover{background-color:rgb(195, 213, 223); \
                          color: white;}";
    QString button_style2="QPushButton{background-color:rgb(25, 61, 95);\
                      color: white;}"
                      "QPushButton:hover{background-color:rgb(195, 213, 223); \
                      color: white;}";
    ui->search_pB->setStyleSheet(button_style);
    ui->alllist_pB->setStyleSheet(button_style);
    ui->withdraw_pB->setStyleSheet(button_style2);
    ui->submit_pB->setStyleSheet(button_style2);
    ui->delete_pB->setStyleSheet(button_style2);
    ui->pushButton_2->setStyleSheet(button_style2);
    ui->searchpushButton->setStyleSheet(button_style);
    ui->submitpushButton->setStyleSheet(button_style);
    ui->Tjiao_pushButton->setStyleSheet(button_style2);
    ui->Cxiao_pushButton->setStyleSheet(button_style2);
    ui->Fhui_pushButton->setStyleSheet(button_style2);
    ui->Xzeng_pushButton->setStyleSheet(button_style2);
    ui->Schu_pushButton->setStyleSheet(button_style2);

    //改变label颜色
    QPalette palette;

    palette.setColor(QPalette::Background, QColor(195, 213, 223));

    ui->label_4->setAutoFillBackground(true);
    ui->label_4->setPalette(palette);

    ui->label_5->setAutoFillBackground(true);
    ui->label_5->setPalette(palette);

    ui->label_6->setAutoFillBackground(true);
    ui->label_6->setPalette(palette);

    ui->label_7->setAutoFillBackground(true);
    ui->label_7->setPalette(palette);

    ui->label_8->setAutoFillBackground(true);
    ui->label_8->setPalette(palette);

    ui->label_9->setAutoFillBackground(true);
    ui->label_9->setPalette(palette);

    ui->label_10->setAutoFillBackground(true);
    ui->label_10->setPalette(palette);

    ui->label->setAutoFillBackground(true);
    ui->label->setPalette(palette);

    ui->label_2->setAutoFillBackground(true);
    ui->label_2->setPalette(palette);

    ui->label_3->setAutoFillBackground(true);
    ui->label_3->setPalette(palette);

    //    QWidget *widget = new QWidget();
    //         widget->setAutoFillBackground(true);
    //         QPalette palette;
    //         QPixmap pixmap(":/Resources/Penguins.jpg");
    //         palette.setBrush(QPalette::Window, QBrush(pixmap));
    //         widget->setPalette(palette);
    //         widget->show();

    //打开会员表
    UserManageMainWindow::openmembertable();
    ui->tableView->setModel(membermodel);

    //    membermodel->removeColumn(2);
    //    membermodel->removeColumn(3);
    //    membermodel->removeColumn(3);
    //    membermodel->removeColumn(3);

    //创建员工表，打开员工表
    //    staff a;
    //    a.createstafftable();
    UserManageMainWindow::openstafftable();
    ui->tableView_3->setModel(staffmodel);
    // ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
    }

UserManageMainWindow::~UserManageMainWindow()
{
    delete ui;
}

//打开会员表
bool UserManageMainWindow::openmembertable(){
    QSqlDatabase db = member::getDatabaseConnection(gConnectionName, gDatabaseName);

    // 1.打开数据
    if (!db.open())
    {
        return false;
    }

    //    QString a = QString("insert into member (no,name,sex"
    //                        ""
    //                        ",password,telephone,address,vip) values('1','jack','女','123','1234','中国','是')");
    //    QSqlQuery query(db);
    //    query.exec(a);

    membermodel = new QSqlTableModel(this,db);
    membermodel->setTable("Member");
    membermodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    membermodel->removeColumn(3);
    membermodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
    membermodel->setHeaderData(1,Qt::Horizontal,tr("姓名"));
    membermodel->setHeaderData(2,Qt::Horizontal,tr("性别"));
    membermodel->setHeaderData(3,Qt::Horizontal,tr("电话"));
    membermodel->setHeaderData(4,Qt::Horizontal,tr("地址"));
    membermodel->setHeaderData(5,Qt::Horizontal,tr("VIP"));
    membermodel->select();

    return true;

}

//打开员工表
bool UserManageMainWindow::openstafftable(){
    QSqlDatabase db = staff::getDatabaseConnection(gConnectionName, gDatabaseName);

    // 1.打开数据
    if (!db.open())
    {
        return false;
    }
    //    QString a = QString("insert into member (no,name,sex"
    //                        ""
    //                        ",password,telephone,address,vip) values('1','jack','女','123','1234','中国','是’)");
    //    QSqlQuery query(db);
    //    query.exec(a);

    staffmodel = new QSqlTableModel(this,db);
    staffmodel->setTable("staff");
    staffmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    staffmodel->removeColumn(2);
    staffmodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
    staffmodel->setHeaderData(1,Qt::Horizontal,tr("姓名"));
    staffmodel->setHeaderData(2,Qt::Horizontal,tr("权限"));

    staffmodel->select();
    return true;

}

void UserManageMainWindow::on_pushButton_clicked()
{
    close();
}

//通过会员编码筛选会员
bool UserManageMainWindow::selectmember(QString no){

    membermodel->setFilter(QObject::tr("no = '%1'").arg(no)); //根据姓名进行筛选

    membermodel->select();
    return true;
}

//查找会员
void UserManageMainWindow::on_search_pB_clicked()
{
    QString id=ui->IDsearchlineEdit->text();
    bool a = selectmember(id);
    if(!a){
        qDebug()<<"ERROR";
    }
    else{
        qDebug()<<"SUCCESS";
    }
}

//撤回修改
void UserManageMainWindow::on_withdraw_pB_clicked()
{
    membermodel->revertAll();
}

//提交修改
void UserManageMainWindow::on_submit_pB_clicked()
{
    membermodel->database().transaction(); //开始事务操作
    if (membermodel->submitAll())
    {
        membermodel->database().commit(); //提交
    }
    else
    {
        membermodel->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1")
                             .arg(membermodel->lastError().text()));
    }
}

//删除行
void UserManageMainWindow::on_delete_pB_clicked()
{
    qDebug() << "curRow";
    int curRow = ui->tableView->currentIndex().row();
    //获取选中的行
    membermodel->removeRow(curRow);
    //删除该行
    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定"
                                                       "删除当前行吗？"),
                                  QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        membermodel->revertAll(); //如果不删除，则撤销
    }
    else membermodel->submitAll(); //否则提交，在数据库中删除该行
}

//提交修改
void UserManageMainWindow::on_add_pB_clicked()
{
    membermodel->database().transaction(); //开始事务操作
    if (membermodel->submitAll()) {
        membermodel->database().commit(); //提交
    } else {
        membermodel->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1")
                             .arg(membermodel->lastError().text()));
    }
}

//添加行
void UserManageMainWindow::on_addhang_pB_clicked()
{
    int rowNum = membermodel->rowCount(); //获得表的行数
    int id = 1;
    membermodel->insertRow(rowNum); //添加一行
    membermodel->setData(membermodel->index(rowNum,0),id);
    //model->submitAll();
}

//返回全表
void UserManageMainWindow::on_alllist_pB_clicked()
{
    membermodel->setTable("member");
    membermodel->removeColumn(3);
    membermodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
    membermodel->setHeaderData(1,Qt::Horizontal,tr("姓名"));
    membermodel->setHeaderData(2,Qt::Horizontal,tr("性别"));
    membermodel->setHeaderData(3,Qt::Horizontal,tr("电话"));
    membermodel->setHeaderData(4,Qt::Horizontal,tr("地址"));
    membermodel->setHeaderData(5,Qt::Horizontal,tr("VIP"));
    membermodel->select();
}

//根据姓名查找用户
void UserManageMainWindow::on_searchpushButton_clicked()
{
    QString id=ui->userIDlineEdit->text();
    staffmodel->setFilter(QObject::tr("no = '%1'").arg(id)); //根据姓名进行筛选

    staffmodel->select();
}

//管理员修改用户密码
void UserManageMainWindow::on_submitpushButton_clicked()
{
    ui->userpwdlineEdit->setEchoMode(QLineEdit::Password);
    QString name = ui->userIDlineEdit->text();
    QString password = ui->userpwdlineEdit->text();
    QSqlDatabase db = staff::getDatabaseConnection(gConnectionName, gDatabaseName);

    // 1.打开数据
    if (!db.open())
    {

    }
    QString b = QString("update staff set password = '%1' where no = '%2'").arg(password).arg(name);
    QSqlQuery query(db);
    bool buscess = query.exec(b);
    if(!buscess)
    {
        qDebug("error");
    }
    else
    {
        ui->userpwdlineEdit->setEchoMode(QLineEdit::Password);
        qDebug("sucess");
    }
}

//新建会员提交
void UserManageMainWindow::on_pushButton_2_clicked()
{
    QString no = ui->lineEdit->text();
    qDebug()<<no;
    QString name = ui->lineEdit_2->text();
    QString sex = ui->lineEdit_3->text();
    QString password = ui->lineEdit_4->text();
    QString telephone = ui->lineEdit_5->text();
    QString address = ui->lineEdit_6->text();
    QString vip = ui->lineEdit_7->text();
    bool a = member::insertmember(no,name,sex,password,telephone,address,vip);
    if(!a){
        qDebug()<<"gggg";
    }
    else{
        qDebug()<<"ssss";
    }
    UserManageMainWindow::openmembertable();
    ui->tableView->setModel(membermodel);
}

void UserManageMainWindow::on_pushButton_3_clicked()
{
    qDebug()<<"ffdfddfdfdf";
}

//员工修改提交
void UserManageMainWindow::on_Tjiao_pushButton_clicked()
{
    staffmodel->database().transaction(); //开始事务操作
    if (staffmodel->submitAll()) {
        staffmodel->database().commit(); //提交
    } else {
        staffmodel->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1")
                             .arg(staffmodel->lastError().text()));
    }
}

//员工修改删除此行
void UserManageMainWindow::on_Schu_pushButton_clicked()
{
    qDebug() << "curRow";
    int curRow = ui->tableView_3->currentIndex().row();
    //获取选中的行
    staffmodel->removeRow(curRow);
    //删除该行
    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定"
                                                       "删除当前行吗？"),
                                  QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        staffmodel->revertAll(); //如果不删除，则撤销
    }
    else staffmodel->submitAll(); //否则提交，在数据库中删除该行
}

//员工信息撤销修改
void UserManageMainWindow::on_Cxiao_pushButton_clicked()
{
    staffmodel->revertAll();
}

//员工管理返回全表
void UserManageMainWindow::on_Fhui_pushButton_clicked()
{
    staffmodel->setTable("staff");
    staffmodel->removeColumn(2);
    staffmodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
    staffmodel->setHeaderData(1,Qt::Horizontal,tr("姓名"));
    staffmodel->setHeaderData(2,Qt::Horizontal,tr("权限"));
    staffmodel->select();
}

//新增员工
void UserManageMainWindow::on_Xzeng_pushButton_clicked()
{
    int rowNum = staffmodel->rowCount(); //获得表的行数
    int id = 1;
    staffmodel->insertRow(rowNum); //添加一行
    staffmodel->setData(staffmodel->index(rowNum,0),id);
    //model->submitAll();
}
