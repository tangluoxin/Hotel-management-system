#include "basicinformationmainwindow.h"
#include "ui_basicinformationmainwindow.h"
#include "mainwindow.h"
#include <QtSql/QSqlTableModel>
#include <QMessageBox>
#include "roomdao.h"
#include "commodity.h"
#include <QSqlError>
#include <QObject>
#include <QtSql/QSqlRecord>
#include<QPixmap>
#include<QBrush>
#include<QHeaderView>

const QString gDatabaseName = "./hotel.db";
const QString gConnectionName = "testConnection";

BasicInformationMainWindow::BasicInformationMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BasicInformationMainWindow)
{
    ui->setupUi(this);

    //改变按钮颜色
    QString button_style1="QPushButton { background-color: rgb(129, 207, 209); "
                         "border-radius: 3px; "
                         "color: rgb(255, 255, 255); }";
    QString button_style2="QPushButton { background-color: rgb(25,61,95);  "
                          "color: rgb(255, 255, 255); }";
    QString button_style3="QPushButton { background-color: rgb(104, 160, 177);  "
                          "color: rgb(255, 255, 255); } }";

    ui->addbtn->setStyleSheet(button_style1);
    ui->deletebtn->setStyleSheet(button_style1);
    ui->querybtn->setStyleSheet(button_style1);
    ui->returnbtn->setStyleSheet(button_style1);
    ui->savebtn->setStyleSheet(button_style1);

    ui->addbtn_2->setStyleSheet(button_style2);
    ui->deletebtn_2->setStyleSheet(button_style2);
    ui->pushButton_2->setStyleSheet(button_style2);
    ui->querybtn_2->setStyleSheet(button_style2);
    ui->fanhui_pushButton->setStyleSheet(button_style2);

    ui->pushButton->setStyleSheet(button_style3);
    ui->pushButton_3->setStyleSheet(button_style3);
    ui->pushButton_6->setStyleSheet(button_style3);
    ui->pushbtn_addfloor->setStyleSheet(button_style3);

//    QPixmap pixmap(":/195-3.jpg");//窗口背景添加（注意整合时修改路径
//            QPalette palett;
//            palett.setBrush(backgroundRole(), QBrush(pixmap));
//            setPalette(palett);

    //创建房间表，打开房间表
//    roomdao b;
//    b.createroomtable();
    BasicInformationMainWindow::openroomtable();
    ui->tableView->setModel(roommodel);

    //创建商品表，打开商品表
//    commodity a;
//    a.createcommoditytable();
    BasicInformationMainWindow::opencommodity();
    ui->tableView_commodity->setModel(commoditymodel);

    //打开楼层表
    BasicInformationMainWindow::openfloortable();
    ui->tableView_2->setModel(floormodel);
    BasicInformationMainWindow::locationlimit();

}

BasicInformationMainWindow::~BasicInformationMainWindow()
{
    delete ui;
}

//房间管理打开
bool BasicInformationMainWindow::openroomtable()
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

    //设置表头
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

//楼层管理打开
bool BasicInformationMainWindow::openfloortable()
{
    QSqlDatabase db = roomdao::getDatabaseConnection(gConnectionName, gDatabaseName);

    // 1.打开数据
    if (!db.open())
    {
        return false;
    }

    floormodel = new QSqlTableModel(this,db);
    floormodel->setTable("Room");
    floormodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //除房间号，房间类型，楼层外其余不显示
    floormodel->removeColumn(2);
    floormodel->removeColumns(3,4);
    floormodel->setHeaderData(0,Qt::Horizontal,tr("房间号"));
    floormodel->setHeaderData(1,Qt::Horizontal,tr("房间类型"));
    floormodel->setHeaderData(2,Qt::Horizontal,tr("楼层"));
    floormodel->select();
    return true;
}

//根据房间类型进行筛选
bool BasicInformationMainWindow::selectroom(QString roomtype)
{
    roommodel->setFilter(QObject::tr("roomtypeno = '%1'").arg(roomtype));
    roommodel->select();
       return true;
}
//通过房间号查找房间
bool BasicInformationMainWindow::selectroomByno(QString no)
{
    roommodel->setFilter(QObject::tr("roomno = '%1'").arg(no));
    roommodel->select();
    return true;
}

//根据房间楼层进行筛选
bool BasicInformationMainWindow::selectfloor(QString floor)
{
    roommodel->setFilter(QObject::tr("location = '%1'").arg(floor));
    roommodel->select();
    return true;
}

//完成查询全部房间功能
void BasicInformationMainWindow::on_querybtn_clicked()
{
    QString strnum=ui->lineEdit_num->text();
    QString strtype=ui->lineEdit_type->text();
    if(strnum.toInt())
    {
        //根据房间号码输出
        BasicInformationMainWindow::selectroomByno(strnum);
    }
    else
    {
        //根据房间类型输出
        BasicInformationMainWindow::selectroom(strtype);
    }
}

//保存房间修改
void BasicInformationMainWindow::on_savebtn_clicked()
{
    //保存房间修改
    roommodel->database().transaction(); //开始事务操作
    if (roommodel->submitAll()) {
        roommodel->database().commit(); //提交
    } else {
        roommodel->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1")
                             .arg(roommodel->lastError().text()));
    }
    for(int i=0;i<roommodel->rowCount();i++)
    {
        QSqlRecord aRec=roommodel->record(i);
        int roomnum=aRec.value("roomno").toInt();
        if(location[roomnum/100]==1)
        {
        }
        else
        {
            QMessageBox::warning(this,QObject::tr("输入违规"),QObject::tr("不存在该楼层"),
                                 QMessageBox::Yes);
            roommodel->removeRow(i);
            roommodel->submitAll();
        }
    }
}

//删除房间
void BasicInformationMainWindow::on_deletebtn_clicked()
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
    }else
    {
        roommodel->submitAll();
    }
}

//添加行
void BasicInformationMainWindow::on_addbtn_clicked()
{
    //增加房间
    int rowNum = roommodel->rowCount(); //获得表的行数
    int id = 1;
    roommodel->insertRow(rowNum); //添加一行
    roommodel->setData(roommodel->index(rowNum,0),id);
}

//返回全表
void BasicInformationMainWindow::on_returnbtn_clicked()
{
    roommodel->setTable("Room");
    roommodel->setHeaderData(0,Qt::Horizontal,tr("房间号"));
    roommodel->setHeaderData(1,Qt::Horizontal,tr("房间类型"));
    roommodel->setHeaderData(2,Qt::Horizontal,tr("房间状态"));
    roommodel->setHeaderData(3,Qt::Horizontal,tr("楼层"));
    roommodel->setHeaderData(4,Qt::Horizontal,tr("标准价格"));
    roommodel->setHeaderData(5,Qt::Horizontal,tr("折后价"));
    roommodel->setHeaderData(6,Qt::Horizontal,tr("普通会员价"));
    roommodel->setHeaderData(7,Qt::Horizontal,tr("VIP会员价"));
    roommodel->select();
}

//打开商品表
bool BasicInformationMainWindow::opencommodity()
{
    QSqlDatabase db = commodity::getDatabaseConnection(gConnectionName, gDatabaseName);
    // 1.打开数据
    if (!db.open())
    {
        return false;;
    }
    commoditymodel = new QSqlTableModel(this,db);
    commoditymodel->setTable("Commodity");
    commoditymodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    commoditymodel->setHeaderData(0,Qt::Horizontal,tr("商品代码"));
    commoditymodel->setHeaderData(1,Qt::Horizontal,tr("商品名称"));
    commoditymodel->setHeaderData(2,Qt::Horizontal,tr("商品类型"));
    commoditymodel->setHeaderData(3,Qt::Horizontal,tr("价格"));
    commoditymodel->setHeaderData(4,Qt::Horizontal,tr("单位"));
    commoditymodel->select();
    return true;
}

//添加行
void BasicInformationMainWindow::on_addbtn_2_clicked()
{
    int rowNum = commoditymodel->rowCount(); //获得表的行数
    int id = 1;
    commoditymodel->insertRow(rowNum); //添加一行
    commoditymodel->setData(commoditymodel->index(rowNum,0),id);
    commoditymodel->submitAll();
    commoditymodel->select();
}

//执行修改操作
void BasicInformationMainWindow::on_pushButton_2_clicked()
{
    commoditymodel->database().transaction(); //开始事务操作
    if (commoditymodel->submitAll())
    {
        commoditymodel->database().commit(); //提交
    }
    else
    {
        commoditymodel->database().rollback(); //回滚
        QMessageBox::warning(this, QObject::tr("tableModel"),
                             QObject::tr("数据库错误: %1")
                             .arg(commoditymodel->lastError().text()));
    }
}

//删除商品
void BasicInformationMainWindow::on_deletebtn_2_clicked()
{
    int curRow = ui->tableView_commodity->currentIndex().row();
    commoditymodel->removeRow(curRow);
    //删除该行
    int ok = QMessageBox::warning(this,QObject::tr("删除当前行!"),QObject::tr("你确定"
                                                                         "删除当前行吗？"),
                                  QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        commoditymodel->revertAll(); //如果不删除，则撤销
    }
    else commoditymodel->submitAll(); //否则提交，在数据库中删除该行
}

//提供通过名字，价格，种类，商品代码，以及同时包含类别和价格进行筛选
void BasicInformationMainWindow::on_querybtn_2_clicked()
{

    QString strname=ui->commodity_name->text();
    QString strtype=ui->commodity_type->text();
    QString strprice=ui->commodity_price->text();
    QString strno=ui->commodity_no->text();
    int price=strprice.toInt();
    if(strname!=NULL)
    {
        BasicInformationMainWindow::selectcommodityByname(strname);
    }
    else if((strtype!=NULL)&&(price!=0))
    {
        BasicInformationMainWindow::selectcommodity(strtype,price);
    }
    else if((strtype==NULL)&&(price!=0))
    {
        BasicInformationMainWindow::selectcommodityByprice(price);
    }
    else if((strtype!=NULL)&&(price==0))
    {
        BasicInformationMainWindow::selectcommodityBytype(strtype);
    }
    else
    {
        BasicInformationMainWindow::selectcommodityByno(strno);
    }
}

//通过商品名称筛选商品
bool BasicInformationMainWindow::selectcommodityByname(QString name){
    commoditymodel->setFilter(QObject::tr("name = '%1'").arg(name));
    commoditymodel->select();
    return true;
}

//通过商品代码筛选商品
bool BasicInformationMainWindow::selectcommodityByno(QString no)
{
    commoditymodel->setFilter(QObject::tr("no = '%1'").arg(no));
    commoditymodel->select();
    return true;
}

//通过商品类型筛选商品
bool BasicInformationMainWindow::selectcommodityBytype(QString type)
{
    commoditymodel->setFilter(QObject::tr("type = '%1'").arg(type));
    commoditymodel->select();
    return true;
}

//通过商品价格挑选商品
bool BasicInformationMainWindow::selectcommodityByprice(int price)
{
    commoditymodel->setFilter(QObject::tr("price == %1").arg(price));
    commoditymodel->select();
    return true;
}

//通过商品类型和商品价格筛选商品
bool BasicInformationMainWindow::selectcommodity(QString type, int price)
{
    commoditymodel->setFilter(QObject::tr("type = '%1' and price <= %2").arg(type).arg(price));
    commoditymodel->select();
    return true;
}

bool BasicInformationMainWindow::locationlimit()
{
    for(int i=0;i<roommodel->rowCount();i++)
    {
        QSqlRecord aRec=roommodel->record(i);
        int roomnum=aRec.value("roomno").toInt();
        location[roomnum/100]=1;//location作为数组保存楼层信息，在增加楼层信息时需要对location进行判断，如果location为0则不可添加楼层信息
    }
    return true;
}

//楼层查询
void BasicInformationMainWindow::on_pushButton_clicked()
{
    QString floor=ui->floor_edit->text();
    floormodel->setFilter(QObject::tr("location = '%1'").arg(floor));
    floormodel->select();

}

//楼层删除功能
void BasicInformationMainWindow::on_pushButton_3_clicked()
{
    QString floor=ui->floor_edit->text();
    location[floor.toInt()]=0;
    for(int i=0;i<roommodel->rowCount();i++)
    {
        QSqlRecord aRec=roommodel->record(i);
        int roomnum=aRec.value("location").toInt();
        if(roomnum==floor.toInt())
        {
            roommodel->removeRow(i);
            roommodel->submitAll();

        }
    }

}

//楼层增加功能
void BasicInformationMainWindow::on_pushbtn_addfloor_clicked()
{
    int floor=(ui->floor_edit->text()).toInt();
    location[floor]=1;
    QMessageBox::warning(this,QObject::tr("楼层成功添加"),QObject::tr("你已成功添加新楼层"),
                         QMessageBox::Yes);
}

//返回商品全表
void BasicInformationMainWindow::on_fanhui_pushButton_clicked()
{
    commoditymodel->setTable("Commodity");
    commoditymodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    commoditymodel->setHeaderData(0,Qt::Horizontal,tr("商品代码"));
    commoditymodel->setHeaderData(1,Qt::Horizontal,tr("商品名称"));
    commoditymodel->setHeaderData(2,Qt::Horizontal,tr("商品类型"));
    commoditymodel->setHeaderData(3,Qt::Horizontal,tr("价格"));
    commoditymodel->setHeaderData(4,Qt::Horizontal,tr("单位"));
    commoditymodel->select();
}

//返回楼层全表
void BasicInformationMainWindow::on_pushButton_6_clicked()
{
    floormodel->setTable("Room");


    //除房间号，房间类型，楼层外其余不显示
    floormodel->removeColumn(2);
    floormodel->removeColumns(3,4);
    floormodel->setHeaderData(0,Qt::Horizontal,tr("房间号"));
    floormodel->setHeaderData(1,Qt::Horizontal,tr("房间类型"));
    floormodel->setHeaderData(2,Qt::Horizontal,tr("楼层"));
    floormodel->select();

}
