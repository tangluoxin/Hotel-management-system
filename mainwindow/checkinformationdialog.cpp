#include "checkinformationdialog.h"
#include "ui_checkinformationdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QRegExp>

CheckinformationDialog::CheckinformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckinformationDialog)
{
    ui->setupUi(this);

    //改变按钮颜色
    QString button_style = "QPushButton { background-color: rgba(195, 213, 223, 70%); "
                           "color: black; }";
    ui->okButton->setStyleSheet(button_style);
    ui->cancelButton->setStyleSheet(button_style);

    QRegExp regx_telephone("^1(3|5|7|8)\\d{9}$");
    QRegExpValidator *pregx_telephone = new QRegExpValidator(regx_telephone);
    ui->telephoneEdit->setValidator(pregx_telephone);

    QRegExp regx_bookid("^\\d{6}(19|20)\\d{2}(0\\d{1}|10|11|12)(0\\d{1}|1\\d{1}|2\\d{1}|30|31)\\d{3}(\\d{1}|X)$");
    QRegExpValidator *pregx_bookid = new QRegExpValidator(regx_bookid);
    ui->bookidEdit->setValidator(pregx_bookid);

    QRegExp regx_day("^\\d{0,}$");
    QRegExpValidator *pregx_day = new QRegExpValidator(regx_day);
    ui->lineEdit->setValidator(pregx_day);
}

CheckinformationDialog::~CheckinformationDialog()
{
    delete ui;
}
QString CheckinformationDialog::bookpeople() const
{
    return m_bookpeople;
}

void CheckinformationDialog::setBookpeople(const QString &bookpeople)
{
    m_bookpeople = bookpeople;
}
QString CheckinformationDialog::booktype() const
{
    return m_booktype;
}

void CheckinformationDialog::setBooktype(const QString &booktype)
{
    m_booktype = booktype;
}
QString CheckinformationDialog::bookid() const
{
    return m_bookid;
}

void CheckinformationDialog::setBookid(const QString &bookid)
{
    m_bookid = bookid;
}
QString CheckinformationDialog::telephone() const
{
    return m_telephone;
}

void CheckinformationDialog::setTelephone(const QString &telephone)
{
    m_telephone = telephone;
}
QString CheckinformationDialog::bookstate() const
{
    return m_bookstate;
}

void CheckinformationDialog::setBookstate(const QString &bookstate)
{
    m_bookstate = bookstate;
}

void CheckinformationDialog::sendbookinformation()
{
    emit sigsendbookinformation(m_bookpeople, m_booktype, m_bookid,
                                m_telephone, m_days, m_bookstate);
}

void CheckinformationDialog::showupdate(QString bookpeople, QString booktype, QString bookid, QString telephone, QString days, QString bookstate)
{
    ui->bookpeopleEdit->setText(bookpeople);
    ui->booktypecomboBox->setCurrentText(booktype);
    ui->bookidEdit->setText(bookid);
    ui->telephoneEdit->setText(telephone);
    ui->lineEdit->setText(days);
    this->setBookstate(bookstate);
    ui->bookstatecomboBox->setEnabled(false);
    this->show();
}

void CheckinformationDialog::on_cancelButton_clicked()
{
    this->close();
}

QString CheckinformationDialog::days() const
{
    return m_days;
}

void CheckinformationDialog::setDays(const QString &days)
{
    m_days = days;
}

void CheckinformationDialog::on_okButton_clicked()
{

    if(ui->bookpeopleEdit->text() == "")
    {
        QMessageBox::information(this,tr("请输入完整信息"),
                                 tr("请输入客户姓名"));
    }
    else if(ui->bookidEdit->text() == "")
    {


        QMessageBox::information(this,tr("请输入完整信息"),
                                 tr("请输入客户证件号"));
    }
    else if(ui->telephoneEdit->text() == "")
    {
        QMessageBox::information(this,tr("请输入完整信息"),
                                 tr("请输入客户电话"));
    }
    else if(ui->lineEdit->text() == "")
    {
        QMessageBox::information(this,tr("请输入完整信息"),
                                 tr("请输入入住天数"));
    }
    else
    {
        int ok = QMessageBox::warning(this, tr("确认输入信息"),
                                      tr("确认信息输入正确"),
                                      QMessageBox::Yes,
                                      QMessageBox::No);

        if(ok == QMessageBox::No)
        {
            return;
        }
        else
        {

            m_bookpeople = ui->bookpeopleEdit->text();
            m_booktype = ui->booktypecomboBox->currentText();
            m_bookid = ui->bookidEdit->text();
            m_telephone = ui->telephoneEdit->text();
            m_days = ui->lineEdit->text();
            if(ui->bookstatecomboBox->isEnabled())
            {
                m_bookstate = ui->bookstatecomboBox->currentText();
            }
            else
            {

            }

            sendbookinformation();
            this->close();
        }
    }


}

