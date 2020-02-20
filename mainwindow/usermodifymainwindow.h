#ifndef USERMODIFYMAINWINDOW_H
#define USERMODIFYMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class UserModifyMainWindow;
}

class UserModifyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserModifyMainWindow(QWidget *parent = 0);
    ~UserModifyMainWindow();

private slots:
    void on_pushButton_clicked();

    void receiveSig();

//private slots:
//    void receiveData(QString data);  //从登录界面链接信号

private:
    Ui::UserModifyMainWindow *ui;
};

#endif // USERMODIFYMAINWINDOW_H
