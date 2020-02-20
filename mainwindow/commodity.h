#ifndef COMMODITY_H
#define COMMODITY_H

#include <QObject>
#include<QtSql/QSqlDatabase>
#include<QSqlTableModel>

class commodity
{

public:
    commodity();
    static QSqlDatabase getDatabaseConnection(QString connName, QString databaseName);
    static bool createcommoditytable();
    void reducenumber(int count1, int count2, int count3);

signals:

public slots:
};

#endif // COMMODITY_H
