#ifndef TENANTMANAGEMAINWINDOW_H
#define TENANTMANAGEMAINWINDOW_H

#include <QMainWindow>
#include <Qtsql/QSqlTableModel>
#include <Qtsql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QObject>
#include <QPushButton>
namespace Ui {
class TenantManageMainWindow;
}

class TenantManageMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TenantManageMainWindow(QWidget *parent = 0);
    ~TenantManageMainWindow();
    bool openroomtable();
    static QSqlDatabase getDatabaseConnection(QString connName, QString databaseName);
    bool selectbyroomno(QString roomno);
    bool selectbyprice(QString price);
    bool selectbyfloor(QString floor);
    bool selectbystate(QString state);
    bool selectbytype(QString type);
    bool changeroomcolor(int roomnum,int roomstate);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_refresh_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_addroom_clicked();

private:
    Ui::TenantManageMainWindow *ui;
     QSqlTableModel *roommodel;
      QPushButton *button[36];
};

#endif // TENANTMANAGEMAINWINDOW_H
