#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<windef.h>
#include"basicinformationmainwindow.h"
#include"usermanagemainwindow.h"
#include"roommanagemainwindow.h"
#include"tenantmanagemainwindow.h"
#include"consumptionmainwindow.h"
#include"logindialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

     void changeColor(QPushButton *button);

public slots:

    void receivelogin(QString);

private slots:
    void on_basicInformation_pB_clicked();

    void on_userManage_pB_clicked();

    void on_tenantManage_pB_clicked();

    void on_roomManage_pB_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    BasicInformationMainWindow *viewBasicIMW;//弹出基础信息管理界面的指针
    UserManageMainWindow *viewUserMMW;//弹出用户会员管理指针
    RoomManageMainWindow *viewRoomMMW;//弹出客房管理界面的指针
    TenantManageMainWindow *viewTenantMMW;//弹出房客管理主界面的指针
    ConsumptionMainWindow *viewConsumMW;//弹出消费管理界面指针
};

#endif // MAINWINDOW_H
