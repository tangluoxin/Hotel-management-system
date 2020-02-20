#ifndef MEMBER_H
#define MEMBER_H

#include <QObject>
#include<QtSql/QSqlDatabase>
#include<QSqlTableModel>

class member
{

public:

    member();
    static QSqlDatabase getDatabaseConnection(QString connName, QString databaseName);
    static bool createmembertable();
    static bool insertmember(QString no, QString name, QString sex, QString password, QString telephone, QString address, QString vip);
    int identity(QString name);

signals:

public slots:
};

#endif // MEMBER_H
