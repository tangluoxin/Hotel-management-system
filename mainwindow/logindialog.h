#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

#include <databasedata.h>
#include "usermodifymainwindow.h"

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();

    void sendlogin();

    void sendSig();
//signals:
//    void  sendData(QString);//
signals:
    void sigsendlogin(QString);

    void sigsendSig();

private slots:
    void on_exitpushButton_clicked();

    void on_loginpushButton_clicked();

    void on_UexitpushButton_clicked();

    void on_UloginpushButton_clicked();//用户登录


private:
    Ui::loginDialog *ui;
    UserModifyMainWindow *viewUserModMW;
};

#endif // LOGINDIALOG_H
