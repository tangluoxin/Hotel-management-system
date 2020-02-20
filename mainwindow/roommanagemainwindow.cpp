#include "RoomManageMainWindow.h"
#include "ui_RoomManageMainWindow.h"
#include <QString>
#include <QMessageBox>
#include <QSqlError>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QModelIndex>
#include <QVariant>
#include <QStringList>
#include <QDebug>
#include <QDateTime>
#include <QColor>
#include <QTableView>
#include <QSqlQuery>
#include "roomdao.h"
#include "member.h"
#include "commodity.h"

const QString gDatabaseName ="./hotel.db" ;
const QString gConnectionName = "testConnection";

RoomManageMainWindow::RoomManageMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RoomManageMainWindow)
{
    ui->setupUi(this);

    DB = QSqlDatabase::addDatabase("QSQLITE");  //添加SQLITE数据库驱动
    DB.setDatabaseName("./hotel.db");                    //设置数据库名称（括号内为数据库名）
    if(!DB.open())
    {
        QMessageBox::warning(this, "错误", "打开数据库失败",
                             QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }
    /*
     * 客房数据表设置
     */
    tabModel = new QSqlTableModel(this, DB);     //数据表
    tabModel->setTable("Room");                  //设置数据表
    tabModel->setSort(tabModel->fieldIndex("roomno"),Qt::AscendingOrder);        //将房间号设为主键
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);       //设置为调用相关函数时保存到数据库

    tabModel->setHeaderData(tabModel->fieldIndex("roomno"), Qt::Horizontal, "房间编号");
    tabModel->setHeaderData(tabModel->fieldIndex("roomtypeno"), Qt::Horizontal, "房间类型");
    tabModel->setHeaderData(tabModel->fieldIndex("location"), Qt::Horizontal, "房间楼层");
    tabModel->setHeaderData(tabModel->fieldIndex("state"), Qt::Horizontal, "房间状态");
    tabModel->setHeaderData(tabModel->fieldIndex("standardprice"), Qt::Horizontal, "房间标准价格");
    tabModel->setHeaderData(tabModel->fieldIndex("discountprice"), Qt::Horizontal, "房间折扣价");
    tabModel->setHeaderData(tabModel->fieldIndex("generalmemberprice"), Qt::Horizontal, "普通用户价");
    tabModel->setHeaderData(tabModel->fieldIndex("vipmemberprice"), Qt::Horizontal, "会员用户价");
    //设置表头************************************************************************************

    ui->tableView->setModel(tabModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);         //设为只能选取整行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);            //设为只能选中一行
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);          //设为不可编辑

    /*
     * 设置结束
     * *********************************************************************************
     */

    /*
     * 预约/入住数据表设置
     */
    tabModel2 = new QSqlTableModel(this, DB);           //数据表
    tabModel2->setTable("BookRoom");            //设置数据表
    tabModel2->setSort(tabModel2->fieldIndex("bookno"), Qt::AscendingOrder);        //将预定单号设为主键
    tabModel2->setEditStrategy(QSqlTableModel::OnManualSubmit);         //设为调用函数时提交更改

    tabModel2->removeColumns(10,3);
    tabModel2->setHeaderData(tabModel2->fieldIndex("bookno"), Qt::Horizontal,"定单号");
    tabModel2->setHeaderData(tabModel2->fieldIndex("roomno"), Qt::Horizontal, "房间编号");
    tabModel2->setHeaderData(tabModel2->fieldIndex("bookpeople"), Qt::Horizontal, "客户姓名");
    tabModel2->setHeaderData(tabModel2->fieldIndex("IDtype"), Qt::Horizontal, "客户证件类型");
    tabModel2->setHeaderData(tabModel2->fieldIndex("IDNumber"), Qt::Horizontal, "客户证件号");
    tabModel2->setHeaderData(tabModel2->fieldIndex("telephone"), Qt::Horizontal, "客户电话");
    tabModel2->setHeaderData(tabModel2->fieldIndex("days"), Qt::Horizontal, "入住天数");
    tabModel2->setHeaderData(tabModel2->fieldIndex("intime"), Qt::Horizontal, "入住时间");
    tabModel2->setHeaderData(tabModel2->fieldIndex("outtime"), Qt::Horizontal, "离店时间");
    tabModel2->setHeaderData(tabModel2->fieldIndex("bookstate"), Qt::Horizontal, "客户状态");
    tabModel2->setHeaderData(tabModel2->fieldIndex("accountReceivable"), Qt::Horizontal, "消费总额");
    //设置表头************************************************************************************


    ui->ordertableView->setModel(tabModel2);
    ui->ordertableView->setSelectionBehavior(QAbstractItemView::SelectRows);        //设为只能选取整行
    ui->ordertableView->setSelectionMode(QAbstractItemView::SingleSelection);            //设为只能选中一行
    ui->ordertableView->setEditTriggers(QAbstractItemView::NoEditTriggers);          //设为不可编辑

    /*
     * 设置结束
     * **************************************************************************************
     */

}

RoomManageMainWindow::~RoomManageMainWindow()
{
    delete ui;
}

void RoomManageMainWindow::showone(QString bookno)
{
    tabModel2->setFilter(QObject::tr("bookno = '%1'").arg(bookno));
    tabModel2->select();
}

/*
 * 改变按钮颜色函数
 */
void RoomManageMainWindow::changeColor(QPushButton *button)
{
    if(button->isEnabled())
    {
        button->setStyleSheet("QPushButton { background-color: rgb(104, 160, 177); color: rgb(255, 255, 255); }");
    }
    else{
        button->setStyleSheet("QPushButton { background-color:rgb(195, 213, 223); color: rgb(122, 136, 127) }");
    }
}

/*
 * 计算商品消费函数
 */
int RoomManageMainWindow::countmoney(QString bookno)
{
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    int price1 = 0;
    int price2 = 0;
    int price3 = 0;
    int standardprice = 0;
    int memberprice = 0;
    int vipprice = 0;
    QVariant temp_roomno = tabModel2->data(tabModel2->index(0, 1));
    QString m_roomno = temp_roomno.toString();
    QSqlDatabase db = roomdao::getDatabaseConnection(gConnectionName,gDatabaseName);
    if(db.open())
    {
        QSqlQuery query(db);

        //获取消费商品数量
        if( query.exec("SELECT * FROM BookRoom where bookno >= 0"))
        {
            while(query.next())
            {
                QString no = query.value(0).toString().trimmed();//trimmed函数表示去除QString两边的空格
                int m_count1 = query.value(10).toInt();
                int m_count2 = query.value(11).toInt();
                int m_count3 = query.value(12).toInt();

                if(bookno.trimmed() == no)
                {
                    count1 = m_count1;
                    count2 = m_count2;
                    count3 = m_count3;
                }
            }
        }

        commodity aa;
        aa.commodity::reducenumber(count1, count2, count3);

        //获取商品价格
        if( query.exec("SELECT * FROM commodity where no >= 0"))
        {
            while(query.next())
            {
                QString no = query.value(0).toString().trimmed();//trimmed函数表示去除QString两边的空格
                int m_price = query.value(3).toInt();
                if(no == "1"){price1 = m_price;}
                if(no == "2"){price2 = m_price;}
                if(no == "3"){price3 = m_price;}
            }
        }

        //获取房间价格
        if( query.exec("SELECT * FROM room where roomno >= 0"))
        {
            while(query.next())
            {
                QString no = query.value(0).toString().trimmed();//trimmed函数表示去除QString两边的空格
                int m_standardprice = query.value(4).toInt();
                int m_memberprice  = query.value(6).toInt();
                int m_vipprice = query.value(7).toInt();
                if(m_roomno == no){
                    standardprice = m_standardprice;
                    memberprice = m_memberprice;
                    vipprice = m_vipprice;
                }
            }
        }
    }

    int commoditytotal = count1*price1 + count2*price2 + count3*price3;

    QVariant temp_days = tabModel2->data(tabModel2->index(0, 6));
    int days = temp_days.toInt();

    QVariant temp_name = tabModel2->data(tabModel2->index(0, 2));
    QString name = temp_name.toString();

    member qw;
    int test = qw.identity(name);
    if(test == 0){return commoditytotal+standardprice*days;}
    else if(test == 1){return commoditytotal+memberprice*days;}
    else if(test == 2){return commoditytotal+vipprice*days;}

}


void RoomManageMainWindow::on_pushButton_clicked()
{
    close();
}

/*
 * 点击查询来查询所有房间
 */
void RoomManageMainWindow::on_queryEmptyRoomButton_clicked()
{
    openTable();                                  //打开数据表
}

/*
 * 用于打开数据表显示出来
 */
void RoomManageMainWindow::openTable()
{
    tabModel->setFilter(QObject::tr("state = '%1'").arg("0"));

    if (!(tabModel->select()))   //查询数据
    {
        QMessageBox::critical(this, "错误", "打开数据表错误，错误信息\n" + tabModel->lastError().text(),
                              QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }

}

/*
 * 获取选定房间房间号信息
 * 在预定/登记表中添加一行来填写信息
 * 预定/登记单号用当前时间（精确到毫秒）
 */
void RoomManageMainWindow::on_orderRoomButton_clicked()
{
    int curRow = ui->tableView->currentIndex().row();
    m_roomno = tabModel->data(tabModel->index(curRow, 0), Qt::DisplayRole);

    QDateTime now_time = QDateTime::currentDateTime();
    m_bookno = now_time.toString("yyyyMMddhhmmsszzz");       //获取当前时间并转为QString类型

    int rowNum = tabModel2->rowCount(); //获取最大行数
    tabModel2->insertRow(rowNum);           //添加一行
    tabModel2->setData(tabModel2->index(rowNum, 0), m_bookno);          //设置预定/登记单号
    tabModel2->setData(tabModel2->index(rowNum, 1), m_roomno);          //设置本次预定/登记的房间号
    tabModel2->submitAll();             //将信息先存入数据库

    tabModel2->setFilter(QObject::tr("bookno = '%1'").arg(m_bookno));
    tabModel2->select();            //只显示这一行

    information = new CheckinformationDialog(this);
    connect(information, SIGNAL(sigsendbookinformation(QString,QString,QString,QString,QString,QString)),
            this, SLOT(receivebookinformation(QString,QString,QString,QString,QString,QString)));
    information->setAttribute(Qt::WA_DeleteOnClose, true);
    information->setModal(true);
    information->show();

    ui->orderRoomButton->setEnabled(false);  //添加该房间后不可是使用预订房间按钮
    changeColor(ui->orderRoomButton);
    ui->cancelupdateButton->setEnabled(true);  //在添加信息后可以使用取消更改信息按钮
    changeColor(ui->cancelupdateButton);
    ui->liveinButton->setEnabled(true);              //添加信息后可以使用确认登记信息按扭
    changeColor(ui->liveinButton);
    ui->beginupdateButton->setEnabled(false);           //添加信息后不可以使用开始更改信息按钮
    changeColor(ui->beginupdateButton);
    ui->deletcheckinButton->setEnabled(false);          //添加信息后不可以使用删除信息按扭
    changeColor(ui->deletcheckinButton);
    ui->searchOrderButton->setEnabled(false);           //添加信息后不可以使用搜索信息按扭
    changeColor(ui->searchOrderButton);

}

/*
 * 点击确认登记信息
 * 将修改的信息保存在数据库中
 */
void RoomManageMainWindow::on_liveinButton_clicked()
{
    if(tabModel2->rowCount() == 1)
    {
        QVariant temp_bookstate = tabModel2->data(tabModel2->index(0, 9));
        QString bookstate = temp_bookstate.toString();

        if(bookstate == "预定")
        {

        }
        else
        {
            QDateTime temp_now_time = QDateTime::currentDateTime();
            QString now_time = temp_now_time.toString("yyyy-MM-dd");
            tabModel2->setData(tabModel2->index(0, 7), now_time);           //如果状态为入住则记录入住时间
        }

        tabModel2->setData(tabModel2->index(0, 1), m_roomno);          //将房间号设为预定时的房间号（防止不小心修改)
        tabModel2->setData(tabModel2->index(0, 0), m_bookno);          //将订单号设为预设订单号防止被修改

        QVariant temp = tabModel2->data(tabModel2->index(0, 2));           //获取预定人名字信息
        tabModel2->submitAll();         //保存至数据库

        QString temp_string = temp.toString();
        tabModel2->setFilter(QObject::tr("bookpeople = '%1'").arg(temp_string));            //查询预定人名字的信息
        tabModel2->select();            //只显示该预定人的所有预定/登记信息

        int tabModel_row = ui->tableView->currentIndex().row();
        if(bookstate == "预定")
        {
            tabModel->setData(tabModel->index(tabModel_row, 2), "1");          //将预定/登记的信息更新至房间信息
            tabModel->submitAll();          //执行存储操作
            tabModel->setFilter(QObject::tr("state = '%1'").arg("0"));
            tabModel->select();         //只显示空房信息至房间信息表
        }
        else
        {
            tabModel->setData(tabModel->index(tabModel_row, 2), "2");          //将预定/登记的信息更新至房间信息
            tabModel->submitAll();          //执行存储操作
            tabModel->setFilter(QObject::tr("state = '%1'").arg("0"));
            tabModel->select();         //只显示空房信息至房间信息表
        }

        ui->orderRoomButton->setEnabled(true);          //在提交信息后可以添加新的预定/登记信息
        changeColor(ui->orderRoomButton);
        ui->cancelupdateButton->setEnabled(false);          //在提交信息后取消更改按钮变为不可用
        changeColor(ui->cancelupdateButton);
        ui->liveinButton->setEnabled(false);            //在提交信息后确认更改信息按钮变为不可用
        changeColor(ui->liveinButton);
        ui->searchOrderButton->setEnabled(true);            //在提交信息后搜索信息按钮变为可用
        changeColor(ui->searchOrderButton);
    }

}

/*
 * 设置取消更改按钮
 */
void RoomManageMainWindow::on_cancelupdateButton_clicked()
{
    int ok = QMessageBox::warning(this, tr("取消更改"),
                                  tr("确认取消所有更改？"),
                                  QMessageBox::Yes,
                                  QMessageBox::No);
    if (ok == QMessageBox::Yes)
    {
        tabModel2->revertAll();         //取消所有更改
        tabModel2->removeRow(0);
        tabModel2->submitAll();

        ui->orderRoomButton->setEnabled(true);          //在取消更改时可以添加房间
        changeColor(ui->orderRoomButton);
        ui->cancelupdateButton->setEnabled(false);          //在取消完更改信息后取消更改信息按钮变为不可用
        changeColor(ui->cancelupdateButton);
        ui->liveinButton->setEnabled(false);            //在后确认更改信息按钮变为不可用
        changeColor(ui->liveinButton);
        ui->searchOrderButton->setEnabled(true);            //在取消更改信息后搜索信息按钮变为可用
        changeColor(ui->searchOrderButton);
    }
    else
    {

    }
}

/*
 * 设置查询预定/登记按钮
 * 仅支持按客户名字查询
 */
void RoomManageMainWindow::on_searchOrderButton_clicked()
{
    QString temp_bookpeople = ui->searchOrderEdit->text();          //获取输入框输入的客户姓名

    tabModel2->setFilter(QObject::tr("bookpeople = '%1'").arg(temp_bookpeople));
    tabModel2->select();            //查询并显示出来

    ui->beginupdateButton->setEnabled(true);           //在搜索出指定预定人信息后更改信息变为可用
    changeColor(ui->beginupdateButton);
    ui->deletcheckinButton->setEnabled(true);          //在搜索出指定预定人信息后删除已存入信息变为可用
    changeColor(ui->deletcheckinButton);
    ui->orderToliveButton->setEnabled(true);            //在搜索出预定人信息后转入住变为可用
    changeColor(ui->orderToliveButton);
}

/*
 * 设置删除更改按钮
 */
void RoomManageMainWindow::on_deletcheckinButton_clicked()
{
    int curRow = ui->ordertableView->currentIndex().row();
    tabModel2->removeRow(curRow);           //获取当前行并删除

    int ok = QMessageBox::warning(this, tr("删除当前行"),
                                  tr("确认删除当前行？"),
                                  QMessageBox::Yes,
                                  QMessageBox::No);

    if (ok == QMessageBox::No)
    {
        tabModel2->revertAll();         //不确认时取消之前的删除操作
    }
    else
    {
        tabModel2->submitAll();         //确认时提交之前删除的更改

        ui->deletcheckinButton->setEnabled(false);          //确认删除信息后删除已存入信息按钮变为不可用
        changeColor(ui->deletcheckinButton);
    }
}

/*
 * 设置转入住按钮
 */
void RoomManageMainWindow::on_orderToliveButton_clicked()
{
    int ok = QMessageBox::warning(this, tr("确认信息"),
                                  tr("确认转入住?"),
                                  QMessageBox::Yes,
                                  QMessageBox::No);
    if (ok == QMessageBox::Yes)
    {
        int curRow = ui->ordertableView->currentIndex().row();          //获取表2当前行
        QVariant temp_roomno = tabModel2->data(tabModel2->index(curRow, 1));            //获取房间编号
        QString roomno = temp_roomno.toString();

        QVariant temp_bookno = tabModel2->data(tabModel2->index(curRow, 0));            //获取预定单号
        QString bookno = temp_bookno.toString();

        tabModel->setFilter(QObject::tr("roomno = '%1'").arg(roomno));              //查询出该房间号的客房信息
        tabModel->select();

        if(tabModel->rowCount() == 1)
        {
            tabModel->setData(tabModel->index(0, 2), QObject::tr("2"));               //转为入住
            tabModel->submitAll();              //确认信息存入数据库

            tabModel->setFilter(QObject::tr("state = '%1'").arg("0"));
            tabModel->select();         //只显示空房信息至房间信息表
        }

        tabModel2->setFilter(QObject::tr("bookno = '%1'").arg(bookno));               //查询出该预定单号的信息
        tabModel2->select();

        if(tabModel2->rowCount() == 1)
        {
            tabModel2->setData(tabModel2->index(0, 9), QObject::tr("已入住"));         //转为入住

            QDateTime now_time = QDateTime::currentDateTime();
            QString now_time_string = now_time.toString("yyyy-MM-dd");
            tabModel2->setData(tabModel2->index(0, 7), now_time_string);                //记录入住时间

            tabModel2->submitAll();         //将确认信息存入数据库

            tabModel2->setFilter(QObject::tr("bookno = '%1'").arg(bookno));
            tabModel2->select();            //只显示该订单的房间
        }

        ui->orderToliveButton->setEnabled(false);           //确认完转入住后转入住按钮变为不可用
        changeColor(ui->orderToliveButton);
    }
}

/*
 * 退房按钮设置
 */
void RoomManageMainWindow::on_checkoutButton_clicked()
{
    int curRow = ui->ordertableView->currentIndex().row();

    QVariant temp_bookno = tabModel2->data(tabModel2->index(curRow, 0));        //获取退房的预定单号
    QString bookno = temp_bookno.toString();

    QVariant temp_roomno = tabModel2->data(tabModel2->index(curRow, 1));        //获取退房房间号
    QString roomno = temp_roomno.toString();

    tabModel->setFilter(QObject::tr("roomno = '%1'").arg(roomno));              //查询出该房间号的客房信息
    tabModel->select();

    if(tabModel->rowCount() == 1)
    {
        tabModel->setData(tabModel->index(0, 2), QObject::tr("0"));               //转为空房

        tabModel->submitAll();          //将转为空房信息存入数据库
        tabModel->setFilter(QObject::tr("state = '%1'").arg("0"));
        tabModel->select();         //只显示空房信息
    }

    tabModel2->setFilter(QObject::tr("bookno = '%1'").arg(bookno));               //查询出该预定单号的信息
    tabModel2->select();

    if(tabModel2->rowCount() == 1)
    {
        tabModel2->setData(tabModel2->index(0, 9), QObject::tr("已退房"));         //转为已退房

        QDateTime now_time = QDateTime::currentDateTime();
        QString now_time_string = now_time.toString("yyyy-MM-dd");
        tabModel2->setData(tabModel2->index(0, 8), now_time_string);            //记录退房时间
        QVariant temp_no = tabModel2->data(tabModel2->index(0, 0));
        QString bookno = temp_no.toString();
        int a = countmoney(bookno);
        tabModel2->setData(tabModel2->index(0,10),a);

        tabModel2->submitAll();         //将退房信息存入数据库
        tabModel2->setFilter(QObject::tr("bookno = '%1'").arg(bookno));
        tabModel2->select();                //只显示该订单号
    }

}

/*
 * 设置更改按钮
 * 需要更改信息时按更改按钮
 */
void RoomManageMainWindow::on_beginupdateButton_clicked()
{
    int Row = ui->ordertableView->currentIndex().row();
    m_roomno = tabModel2->data(tabModel2->index(Row, 1));
    QVariant temp_bookno = tabModel2->data(tabModel2->index(Row, 0));
    m_bookno = temp_bookno.toString();          //获取修改的行数信息

    tabModel2->setFilter(QObject::tr("bookno = '%1'").arg(m_bookno));
    tabModel2->select();            //只显示修改要修改的行数

    updateinformation = new CheckinformationDialog(this);
    connect(updateinformation, SIGNAL(sigsendbookinformation(QString,QString,QString,QString,QString,QString)),
            this, SLOT(receivebookinformation(QString,QString,QString,QString,QString,QString)));
    updateinformation->setAttribute(Qt::WA_DeleteOnClose, true);
    updateinformation->setModal(true);

    if(tabModel2->rowCount() == 1)
    {
        updateinformation->showupdate(tabModel2->data(tabModel2->index(0, 2)).toString(),
                                      tabModel2->data(tabModel2->index(0, 3)).toString(),
                                      tabModel2->data(tabModel2->index(0, 4)).toString(),
                                      tabModel2->data(tabModel2->index(0, 5)).toString(),
                                      tabModel2->data(tabModel2->index(0, 6)).toString(),
                                      tabModel2->data(tabModel2->index(0, 9)).toString());
    }

    ui->checkupdateButton->setEnabled(true);            //开始更改信息后确认更改信息可用
    changeColor(ui->checkupdateButton);
    ui->beginupdateButton->setEnabled(false);           //开始更改信息后更改信息按钮变为不可用
    changeColor(ui->beginupdateButton);
    ui->cancelchangeButton->setEnabled(true);           //开始更改信息后取消更改的信息可用
    changeColor(ui->cancelchangeButton);
}

/*
 * 设置确认更改信息按钮
 */
void RoomManageMainWindow::on_checkupdateButton_clicked()
{
    int ok = QMessageBox::warning(this, tr("确认信息"),
                                  tr("确认更改信息？"),
                                  QMessageBox::Yes,
                                  QMessageBox::No);
    if(ok == QMessageBox::Yes)
    {
        tabModel2->setData(tabModel2->index(0, 0), m_bookno);
        QVariant temp_bookpeople = tabModel2->data(tabModel2->index(0, 2));
        QString temp_bookpeople_string = temp_bookpeople.toString();
        ui->searchOrderEdit->setText(temp_bookpeople_string);

        tabModel2->submitAll();
        tabModel2->setFilter(QObject::tr("bookpeople = '%1'").arg(
                                 temp_bookpeople_string));
        tabModel2->select();

        ui->checkupdateButton->setEnabled(false);           //确认完更改信息后确认更改信息按钮变为不可用
        changeColor(ui->checkupdateButton);
        ui->cancelchangeButton->setEnabled(false);          //确认完更改信息后取消更改信息按钮变为不可用
        changeColor(ui->cancelchangeButton);
        ui->beginupdateButton->setEnabled(true);            //确认完更改信息后更改信息按钮变为可用
        changeColor(ui->beginupdateButton);
    }
}

void RoomManageMainWindow::receivebookinformation(QString bookpeople, QString booktype, QString bookid, QString telephone, QString days, QString bookstate)
{

    tabModel2->setData(tabModel2->index(0, 2), bookpeople);
    tabModel2->setData(tabModel2->index(0, 3), booktype);
    tabModel2->setData(tabModel2->index(0, 4), bookid);
    tabModel2->setData(tabModel2->index(0, 5), telephone);
    tabModel2->setData(tabModel2->index(0, 6), days);
    tabModel2->setData(tabModel2->index(0, 9), bookstate);

}

void RoomManageMainWindow::on_cancelchangeButton_clicked()
{
    tabModel2->revertAll();

    ui->checkupdateButton->setEnabled(false);           //取消更改信息后确认更改信息变为不可用
    changeColor(ui->checkupdateButton);
    ui->beginupdateButton->setEnabled(true);            //取消更改信息后更改信息变为可用
    changeColor(ui->beginupdateButton);
    ui->cancelchangeButton->setEnabled(false);          //取消更改信息后取消更改信息变为不可用
    changeColor(ui->cancelchangeButton);

}
