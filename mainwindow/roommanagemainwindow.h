#ifndef ROOMMANAGEMAINWINDOW_H
#define ROOMMANAGEMAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <checkinformationdialog.h>

namespace Ui {
class RoomManageMainWindow;
}

class RoomManageMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RoomManageMainWindow(QWidget *parent = 0);
    ~RoomManageMainWindow();

    void showone(QString bookno);

    void changeColor(QPushButton *button);

    int countmoney(QString bookno);

public slots:
    void receivebookinformation(QString bookpeople,
                                QString booktype,
                                QString bookid,
                                QString telephone,
                                QString days,
                                QString bookstate);

private slots:
    void on_pushButton_clicked();

    void on_queryEmptyRoomButton_clicked();

    void on_orderRoomButton_clicked();

    void on_liveinButton_clicked();

    void on_searchOrderButton_clicked();

    void on_cancelupdateButton_clicked();

    void on_deletcheckinButton_clicked();

    void on_orderToliveButton_clicked();

    void on_checkoutButton_clicked();

    void on_beginupdateButton_clicked();

    void on_checkupdateButton_clicked();

    void on_cancelchangeButton_clicked();

private:
    Ui::RoomManageMainWindow *ui;
    
    QSqlDatabase DB;
    void openTable();
    QSqlTableModel *tabModel;
    void openTable2();
    QSqlTableModel *tabModel2;
    QVariant m_roomno;
    QString m_bookno;
    CheckinformationDialog *information;
    CheckinformationDialog *updateinformation;

};

#endif // RoomManageMainWindow_H
