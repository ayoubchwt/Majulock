#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class connection
{
public:
    connection();
    static QSqlDatabase getConnection();
    static bool createConnection();
};
#endif // CONNECTION_H
