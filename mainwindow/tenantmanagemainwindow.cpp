#include "tenantmanagemainwindow.h"
#include "ui_tenantmanagemainwindow.h"
#include"mainwindow.h"
#include<QPalette>
#include<QtSql/QSqlTableModel>
#include<QMessageBox>
#include"roomdao.h"
#include<QSqlError>
#include<QObject>
#include<QtSql/QSqlRecord>

const QString gDatabaseName = "./hotel.db";
const QString gConnectionName = "testConnection";

TenantManageMainWindow::TenantManageMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TenantManageMainWindow)
{
    ui->setupUi(this);

    //生成按键
    button[0]=ui->pushButton_2;
    for(int i=1;i<=35;i++)
    {
        button[i]=new QPushButton(this);
        button[i]->setGeometry((i%6)*200+20,(80+(i/6)*150),181,131);
        button[i]->setStyleSheet("QPushButton { background-color:rgba(240, 240, 240,0%); border-radius: 3px; color: rgb(240, 240, 240); font: 9qt '微软雅黑'; }");
    }

    //    roomdao room;
    //    room.createroomtable();
    TenantManageMainWindow::openroomtable();
    ui->tableView->setModel(roommodel);
}

TenantManageMainWindow::~TenantManageMainWindow()
{
    delete ui;
}

//打开房间表
bool TenantManageMainWindow::openroomtable()
{
    QSqlDatabase db = roomdao::getDatabaseConnection(gConnectionName, gDatabaseName);
    // 1.打开数据
    if (!db.open())
    {
        return false;
    }
    roommodel = new QSqlTableModel(this,db);
    roommodel->setTable("Room");
    roommodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    roommodel->setHeaderData(0,Qt::Horizontal,tr("房间号"));
    roommodel->setHeaderData(1,Qt::Horizontal,tr("房间类型"));
    roommodel->setHeaderData(2,Qt::Horizontal,tr("房间状态"));
    roommodel->setHeaderData(3,Qt::Horizontal,tr("楼层"));
    roommodel->setHeaderData(4,Qt::Horizontal,tr("标准价格"));
    roommodel->setHeaderData(5,Qt::Horizontal,tr("折后价"));
    roommodel->setHeaderData(6,Qt::Horizontal,tr("普通会员价"));
    roommodel->setHeaderData(7,Qt::Horizontal,tr("VIP会员价"));
    roommodel->select();
    return true;
}

//根据房间号筛选房间
bool TenantManageMainWindow::selectbyroomno(QString roomno)
{
    roommodel->setFilter(QObject::tr("roomno = '%1'").arg(roomno));
    roommodel->select();
    return true;
}

//通过价格筛选房间
bool TenantManageMainWindow::selectbyprice(QString price)
{
    roommodel->setFilter(QObject::tr("standardprice = '%1'").arg(price));
    roommodel->select();
    return true;
}

//通过楼层修改房间
bool TenantManageMainWindow::selectbyfloor(QString floor)
{
    roommodel->setFilter(QObject::tr("location='%1'").arg(floor));
    roommodel->select();
    return true;
}

//通过房间状态筛选房间
bool TenantManageMainWindow::selectbystate(QString state)
{
    roommodel->setFilter(QObject::tr("state='%1'").arg(state));
    roommodel->select();
    return true;
}

//通过方关键类型筛选房间
bool TenantManageMainWindow::selectbytype(QString type)
{
    roommodel->setFilter(QObject::tr("roomtypeno='%1'").arg(type));
    roommodel->select();
    return true;
}

//根据房间状态改变按键颜色
bool TenantManageMainWindow::changeroomcolor(int roomnum, int roomstate)
{
    //将房间号与pushbutton数组相关联,房间对应的pushbutton数组应为（a-1)*6+b-1
    int a=roomnum/100;
    int b=roomnum%100;
    int c=(a-1)*6+b-1;
     if(0==roomstate)
     {
         //房间是空房,颜色切换为:QPushButton { background-color:rgb(195, 213, 223); border-radius: 3px; color: rgb(122, 136, 127) }
         button[c]->setStyleSheet("QPushButton { background-color:rgb(195, 213, 223); border-radius: 3px; color: rgb(122, 136, 127); font: 9qt '微软雅黑';  }");
         return true;
     }
      else if(1==roomstate)
     {
        //房间已经被预订，颜色切换为：QPushButton { background-color: rgb(104, 160, 177); border-radius: 3px; color: rgb(255, 255, 255); }
         button[c]->setStyleSheet("QPushButton { background-color:rgb(104, 160, 177); border-radius: 3px; color: rgb(255, 255, 255); font: 9qt '微软雅黑';  }");
         return true;
     }
      else if(2==roomstate)
     {
        //房间已经入住客人颜色切换为：QPushButton { background-color: rgb(25, 61, 95); border-radius: 3px; color: rgb(255, 255, 255); }
         button[c]->setStyleSheet("QPushButton { background-color: rgb(25, 61, 95); border-radius: 3px; color: rgb(255, 255, 255); font: 9qt '微软雅黑'; }");
         return true;
      }

    else if(3==roomstate)
    {
        //房间正在处于装修或其它原因无法使用阶段颜色切换为QPushButton { background-color: rgb(129, 207, 209); border-radius: 3px; color: rgb(255, 255, 255); }
         button[c]->setStyleSheet("QPushButton { background-color: rgb(129, 207, 209); border-radius: 3px; color: rgb(255, 255, 255); font: 9qt '微软雅黑'; }");
         return true;
    }

    return true;
}

void TenantManageMainWindow::on_pushButton_clicked()
{
    close();
}

void TenantManageMainWindow::on_pushButton_2_clicked()
{

}

/* 遍历数据库根据存在的房间确定颜色
* 根据state确定颜色
* 加入楼层限制，和每层最大房间数目限制 */
void TenantManageMainWindow::on_pushButton_refresh_clicked()
{

    roommodel->setTable("room");
    roommodel->setHeaderData(0,Qt::Horizontal,tr("房间号"));
    roommodel->setHeaderData(1,Qt::Horizontal,tr("房间类型"));
    roommodel->setHeaderData(2,Qt::Horizontal,tr("房间状态"));
    roommodel->setHeaderData(3,Qt::Horizontal,tr("楼层"));
    roommodel->setHeaderData(4,Qt::Horizontal,tr("标准价格"));
    roommodel->setHeaderData(5,Qt::Horizontal,tr("折后价"));
    roommodel->setHeaderData(6,Qt::Horizontal,tr("普通会员价"));
    roommodel->setHeaderData(7,Qt::Horizontal,tr("VIP会员价"));
    roommodel->select();
    for(int i=0;i<=35;i++)
    {
        button[i]->setStyleSheet("QPushButton { background-color:rgba(240, 240, 240, 0%); border-radius: 3px; color: rgb(240,240, 240); font: 9qt '微软雅黑'; }");
    }
    if(roommodel->rowCount()==0)
    {
    }
    else
    {
        for(int i=0;i<roommodel->rowCount();i++)
        {
            QSqlRecord aRec=roommodel->record(i);
            int roomnum=aRec.value("roomno").toInt();
            int roomstate=aRec.value("state").toInt();
            QString roomnumstring=aRec.value("roomno").toString();
            QString roomtypestring=aRec.value("roomtypeno").toString();
            QString c=roomnumstring+roomtypestring;
            button[(roomnum/100-1)*6+roomnum%100-1]->setText(c);
            TenantManageMainWindow::changeroomcolor(roomnum,roomstate);
        }
    }
}

//根据各种方式及信息筛选可供选择的房间
void TenantManageMainWindow::on_pushButton_25_clicked()
{

    QString roomnumber=ui->lineEdit_roomno->text();
    int roomnum=roomnumber.toInt();
    int price=(ui->lineEdit_price->text()).toInt();
    QString roomtype=ui->lineEdit_roomtype->text();
    int floor=(ui->lineEdit_floor->text()).toInt();
    int state=(ui->lineEdit_state->text()).toInt();
    if(roomnum)
    {
        TenantManageMainWindow::selectbyroomno(roomnumber);
    }
    else if(price)
    {
        TenantManageMainWindow::selectbyprice(ui->lineEdit_price->text());
    }
    else if(floor)
    {
        TenantManageMainWindow::selectbyfloor(ui->lineEdit_floor->text());
    }
    else if(roomtype!=NULL)
    {
        TenantManageMainWindow::selectbytype(roomtype);
    }
    else if(state)//state的数值需要在数据库中进行修改，0不可以做为状态出现
    {
        TenantManageMainWindow::selectbystate(ui->lineEdit_state->text());
    }
    else
    {
        QMessageBox::warning(this,QObject::tr("未输入！！！"),QObject::tr("请输入内容"),
                             QMessageBox::Yes);
    }

}

//保存修改操作
void TenantManageMainWindow::on_pushButton_22_clicked()
{
    int curRow = ui->tableView->currentIndex().row();
    QSqlRecord aRec=roommodel->record(curRow);
    roommodel->database().transaction(); //开始事务操作
    if (roommodel->submitAll())
    {
        roommodel->database().commit(); //提交
    }
    else
    {
        roommodel->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1")
                             .arg(roommodel->lastError().text()));
    }
}

//删除选中行
void TenantManageMainWindow::on_pushButton_delete_clicked()
{
    int curRow = ui->tableView->currentIndex().row();
    //获取选中的行
    roommodel->removeRow(curRow);
    //删除该行
    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定"
                                                       "删除当前行吗？"),
                                  QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        roommodel->revertAll(); //如果不删除，则撤销
    }
    else
    {
        roommodel->submitAll();
    }
}

//增加行
void TenantManageMainWindow::on_pushButton_addroom_clicked()
{
    int rowNum = roommodel->rowCount(); //获得表的行数
    int id = 1;
    roommodel->insertRow(rowNum); //添加一行
    roommodel->setData(roommodel->index(rowNum,0),id);
}

