#ifndef CHECKINFORMATIONDIALOG_H
#define CHECKINFORMATIONDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class CheckinformationDialog;
}

class CheckinformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckinformationDialog(QWidget *parent = 0);
    ~CheckinformationDialog();

    QString bookpeople() const;
    void setBookpeople(const QString &bookpeople);

    QString booktype() const;
    void setBooktype(const QString &booktype);

    QString bookid() const;
    void setBookid(const QString &bookid);

    QString telephone() const;
    void setTelephone(const QString &telephone);

    QString bookstate() const;
    void setBookstate(const QString &bookstate);

    void sendbookinformation();

    void showupdate(QString bookpeople,
                    QString booktype,
                    QString bookid,
                    QString telephone,
                    QString days,
                    QString bookstate);

    QString days() const;
    void setDays(const QString &days);

signals:
    void sigsendbookinformation(QString bookpeople,
                                QString booktype,
                                QString bookid,
                                QString telephone,
                                QString days,
                                QString bookstate);

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::CheckinformationDialog *ui;
    QString m_bookpeople;
    QString m_booktype;
    QString m_bookid;
    QString m_telephone;
    QString m_days;
    QString m_bookstate;
};

#endif // CHECKINFORMATIONDIALOG_H
