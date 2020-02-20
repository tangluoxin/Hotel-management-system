#ifndef BASICINFORMATIONMAINWINDOW_H
#define BASICINFORMATIONMAINWINDOW_H

#include <QMainWindow>
#include <Qtsql/QSqlTableModel>
#include <Qtsql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QObject>
namespace Ui {
class BasicInformationMainWindow;
}

class BasicInformationMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BasicInformationMainWindow(QWidget *parent = 0);
    ~BasicInformationMainWindow();
    bool openroomtable();
    bool opencommodity();
    bool selectroom(QString roomtype);
    bool selectroomByno(QString no);
    bool openfloortable();
    bool selectfloor(QString floor);
    static QSqlDatabase getDatabaseConnection(QString connName, QString databaseName);
    static bool createcommoditytable();
    bool selectcommodityByname(QString strname);
    bool selectcommodityByno(QString no);
    bool selectcommodityBytype(QString type);
    bool selectcommodityByprice(int price);
    bool selectcommodity(QString type, int price);
    int location[10]={0};
    bool locationlimit();
private slots:
    void on_querybtn_clicked();

    void on_savebtn_clicked();

    void on_deletebtn_clicked();

    void on_addbtn_clicked();

    void on_returnbtn_clicked();

    void on_addbtn_2_clicked();

    void on_pushButton_2_clicked();

    void on_deletebtn_2_clicked();

    void on_querybtn_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushbtn_addfloor_clicked();

    void on_fanhui_pushButton_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::BasicInformationMainWindow *ui;
    QSqlTableModel *roommodel;
    QSqlTableModel *commoditymodel;
    QSqlTableModel *floormodel;
};

#endif // BASICINFORMATIONMAINWINDOW_H
