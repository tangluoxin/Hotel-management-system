#ifndef ROOMDAO_H
#define ROOMDAO_H

#include <QObject>
#include<QtSql/QSqlDatabase>
#include<QSqlTableModel>

class roomdao
{
public:
    roomdao();
    static QSqlDatabase getDatabaseConnection(QString connName, QString databaseName);

        static bool createroomtable();

signals:

public slots:
};

#endif // ROOMDAO_H
