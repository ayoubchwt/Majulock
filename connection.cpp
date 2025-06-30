    #include "connection.h"

    connection::connection() {}
    QSqlDatabase connection::getConnection(){
        return QSqlDatabase::database();
    }
    bool connection::createConnection(){
        QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE");
        dataBase.setDatabaseName("Majulock.db");
        if(!dataBase.open()){
            qDebug() << "Error opening DB:" << dataBase.lastError().text();
            return false;
        }
        QString createPasswords = R"(
        CREATE TABLE IF NOT EXISTS password (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            label TEXT NOT NULL,
            email TEXT NOT NULL,
            username TEXT,
            pass TEXT NOT NULL,
            created DATETIME DEFAULT CURRENT_TIMESTAMP,
            lastModified DATETIME DEFAULT CURRENT_TIMESTAMP
        )
        )";
        QString createUsers = R"(
            CREATE TABLE IF NOT EXISTS user (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT,
                address TEXT NOT NULL,
                password TEXT NOT NULL
            )
        )";
        QSqlQuery passwordQuery;
        QSqlQuery userQuery;
        if (!passwordQuery.exec(createPasswords)) {
            qDebug() << "Error creating password table:" << passwordQuery.lastError().text();
            return false;
        }
        if (!userQuery.exec(createUsers)) {
            qDebug() << "Error creating user table:" << userQuery.lastError().text();
            return false;
        }
        qDebug() << "Database initialized successfully.";
        return true;
    }

