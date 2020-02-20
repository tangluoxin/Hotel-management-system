#include "consumptionmainwindow.h"
#include "ui_consumptionmainwindow.h"
#include "mainwindow.h"
#include <QPalette>
#include <QtSql/QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>
#include <QObject>
#include <QDebug>
#include <QtSql/QSqlRecord>
#include "commodity.h"

const QString gDatabaseName = "./hotel.db";
const QString gConnectionName = "testConnection";

ConsumptionMainWindow::ConsumptionMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConsumptionMainWindow)
{
    ui->setupUi(this);

    //设置按钮颜色
    QString button_style = "QPushButton { background-color: rgb(129, 207, 209); "
                           "color: rgb(255, 255, 255);}";
    ui->querybtn->setStyleSheet(button_style);
    ui->returnbtn->setStyleSheet(button_style);
    ui->savebtn->setStyleSheet(button_style);

    ConsumptionMainWindow::openconsumetable();
    ui->tableView->setModel(consumemodel);

    ConsumptionMainWindow::opencommodity();

}

ConsumptionMainWindow::~ConsumptionMainWindow()
{
    delete ui;
}

bool ConsumptionMainWindow::openconsumetable()
{
    QSqlDatabase db = commodity::getDatabaseConnection(gConnectionName, gDatabaseName);

    // 1.打开数据
    if (!db.open())
    {
        return false;
    }

    consumemodel = new QSqlTableModel(this,db);
    consumemodel->setTable("BookRoom");
    consumemodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    consumemodel->removeColumns(3,6);

    //设置表头
    consumemodel->setHeaderData(0,Qt::Horizontal,tr("订单号"));
    consumemodel->setHeaderData(1,Qt::Horizontal,tr("房间号"));
    consumemodel->setHeaderData(2,Qt::Horizontal,tr("预订人"));
    consumemodel->setHeaderData(3,Qt::Horizontal,tr("客户状态"));
    consumemodel->setHeaderData(4,Qt::Horizontal,tr("商品1消费数量"));
    consumemodel->setHeaderData(5,Qt::Horizontal,tr("商品2消费数量"));
    consumemodel->setHeaderData(6,Qt::Horizontal,tr("商品3消费数量"));
    consumemodel->setHeaderData(7,Qt::Horizontal,tr("消费总额"));
    consumemodel->select();
    return true;
}

bool ConsumptionMainWindow::opencommodity()
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

bool ConsumptionMainWindow::selectbyroomno(QString roomno)
{
    consumemodel->setFilter(QObject::tr("roomno = '%1'").arg(roomno));
    consumemodel->select();
    return true;
}

void ConsumptionMainWindow::on_savebtn_clicked()
{
    consumemodel->database().transaction(); //开始事务操作
    if (consumemodel->submitAll()) {
        consumemodel->database().commit(); //提交
    }
    else
    {
        consumemodel->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1")
                             .arg(consumemodel->lastError().text()));
    }
    /*int curRow = ui->tableView->currentIndex().row();
    QVariant temp_count1 = consumemodel->data(consumemodel->index(curRow, 4));
    int count1 = temp_count1.toInt();
    qDebug()<<count1;
    QVariant temp_count2 = consumemodel->data(consumemodel->index(curRow, 5));
    int count2 = temp_count2.toInt();
    qDebug()<<count2;
    QVariant temp_count3 = consumemodel->data(consumemodel->index(curRow, 6));
    int count3 = temp_count3.toInt();
    qDebug()<<count3;*/

}

void ConsumptionMainWindow::on_querybtn_clicked()
{
    QString roomnumber=ui->lineEdit_roomno->text();
    ConsumptionMainWindow::selectbyroomno(roomnumber);
}

void ConsumptionMainWindow::on_returnbtn_clicked()
{
    consumemodel->setTable("BookRoom");
    consumemodel->removeColumns(3,5);

    //设置表头
    consumemodel->setHeaderData(0,Qt::Horizontal,tr("订单号"));
    consumemodel->setHeaderData(1,Qt::Horizontal,tr("房间号"));
    consumemodel->setHeaderData(2,Qt::Horizontal,tr("预订人"));
    consumemodel->setHeaderData(3,Qt::Horizontal,tr("客户状态"));
    consumemodel->setHeaderData(4,Qt::Horizontal,tr("商品1消费数量"));
    consumemodel->setHeaderData(5,Qt::Horizontal,tr("商品2消费数量"));
    consumemodel->setHeaderData(6,Qt::Horizontal,tr("商品3消费数量"));
    consumemodel->setHeaderData(7,Qt::Horizontal,tr("消费总额"));
    consumemodel->select();
}
