#ifndef CONSUMPTIONMAINWINDOW_H
#define CONSUMPTIONMAINWINDOW_H

#include <QMainWindow>
#include <Qtsql/QSqlTableModel>
#include <Qtsql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QObject>
#include <QPushButton>

namespace Ui {
class ConsumptionMainWindow;
}

class ConsumptionMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConsumptionMainWindow(QWidget *parent = 0);
    ~ConsumptionMainWindow();
    bool openconsumetable();
    bool selectbyroomno(QString roomno);
    bool opencommodity();

private slots:
        void on_savebtn_clicked();

        void on_querybtn_clicked();

        void on_returnbtn_clicked();

private:
    Ui::ConsumptionMainWindow *ui;
    QSqlTableModel *consumemodel;
    QSqlTableModel *commoditymodel;

};

#endif // CONSUMPTIONMAINWINDOW_H
