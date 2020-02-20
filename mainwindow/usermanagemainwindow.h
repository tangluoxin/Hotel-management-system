#ifndef USERMANAGEMAINWINDOW_H
#define USERMANAGEMAINWINDOW_H

#include <QMainWindow>

#include <QSqlTableModel>

namespace Ui {
class UserManageMainWindow;
}

class UserManageMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserManageMainWindow(QWidget *parent = 0);
    ~UserManageMainWindow();

    bool openmembertable();
    bool openstafftable();

    bool selectmember(QString no);

private slots:
    void on_pushButton_clicked();

    void on_search_pB_clicked();

    void on_withdraw_pB_clicked();

    void on_submit_pB_clicked();

    void on_delete_pB_clicked();

    void on_add_pB_clicked();

    void on_addhang_pB_clicked();

    void on_alllist_pB_clicked();

    void on_searchpushButton_clicked();

    void on_submitpushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_Tjiao_pushButton_clicked();

    void on_Schu_pushButton_clicked();

    void on_Cxiao_pushButton_clicked();

    void on_Fhui_pushButton_clicked();

    void on_Xzeng_pushButton_clicked();

private:
    Ui::UserManageMainWindow *ui;
    QSqlTableModel *staffmodel;
    QSqlTableModel *membermodel;
};

#endif // USERMANAGEMAINWINDOW_H
