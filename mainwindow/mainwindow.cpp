#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//弹出基础信息管理主界面
void MainWindow::on_basicInformation_pB_clicked()
{
    viewBasicIMW = new BasicInformationMainWindow;
    viewBasicIMW->show();

}

//弹出用户会员管理主界面
void MainWindow::on_userManage_pB_clicked()
{
    viewUserMMW = new UserManageMainWindow;
    viewUserMMW->show();
}

//弹出房间管理主界面
void MainWindow::on_tenantManage_pB_clicked()
{
    viewRoomMMW = new RoomManageMainWindow;
    viewRoomMMW->show();
}

//弹出房客管理主界面
void MainWindow::on_roomManage_pB_clicked()
{
    viewTenantMMW = new TenantManageMainWindow;
    viewTenantMMW->show();
}

/*
 * 接收登录时的信息进行设置
 */
void MainWindow::receivelogin(QString logininformation)
{
    if(logininformation == "前台"){
        ui->basicInformation_pB->setEnabled(false);
        changeColor(ui->basicInformation_pB);
        ui->userManage_pB->setEnabled(false);
        changeColor(ui->userManage_pB);
        ui->tenantManage_pB->setEnabled(true);
        changeColor(ui->tenantManage_pB);
        ui->roomManage_pB->setEnabled(false);
        changeColor(ui->roomManage_pB);
        ui->pushButton->setEnabled(true);
        changeColor(ui->pushButton);
    }
    if(logininformation == "经理"){
        ui->basicInformation_pB->setEnabled(true);
        changeColor(ui->basicInformation_pB);
        ui->userManage_pB->setEnabled(true);
        changeColor(ui->userManage_pB);
        ui->tenantManage_pB->setEnabled(true);
        changeColor(ui->tenantManage_pB);
        ui->roomManage_pB->setEnabled(true);
        changeColor(ui->roomManage_pB);
        ui->pushButton->setEnabled(true);
        changeColor(ui->pushButton);
    }
    if(logininformation == "管理员"){
        ui->basicInformation_pB->setEnabled(true);
        changeColor(ui->basicInformation_pB);
        ui->userManage_pB->setEnabled(true);
        changeColor(ui->userManage_pB);
        ui->tenantManage_pB->setEnabled(true);
        changeColor(ui->tenantManage_pB);
        ui->roomManage_pB->setEnabled(true);
        changeColor(ui->roomManage_pB);
        ui->pushButton->setEnabled(true);
        changeColor(ui->pushButton);
    }
}

//根据按键是否能用改变按键颜色
void MainWindow::changeColor(QPushButton *button)
{
    if(button->isEnabled())
    {
        button->setStyleSheet("QPushButton { background-color: rgba(129, 207, 209, 50%);  color: rgb(255, 255, 255); }");
    }
    else{
        button->setStyleSheet("QPushButton { background-color:rgba(195, 213, 223, 50%); color: rgb(255, 255, 255) }");
    }
}



void MainWindow::on_pushButton_clicked()
{
    viewConsumMW = new ConsumptionMainWindow;
    viewConsumMW->show();
}
