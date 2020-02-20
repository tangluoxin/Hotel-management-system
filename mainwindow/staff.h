#ifndef STAFF_H
#define STAFF_H

#include <QObject>
#include<QtSql/QSqlDatabase>
#include<QSqlTableModel>

class staff
{

public:
    staff();
    static QSqlDatabase getDatabaseConnection(QString connName, QString databaseName);
    static bool createstafftable();

signals:

public slots:
};

#endif // STAFF_H
