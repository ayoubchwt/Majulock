#ifndef PASSWORD_H
#define PASSWORD_H
#include <QString>
#include <QDateTime>
#include <QSqlQuery>
#include <QList>
#include <QSqlError>
#include <QDebug>
#include "connection.h"
using namespace std ;
class Password
{
private:
    QString id;
    QString label;
    QString email;
    QString username;
    QString pass;
    QString created;
    QString lastModified;
public:
    Password();
    Password(QString id, QString label,QString email,QString username,QString pass, QString created, QString lastModified);
    //getters :
    QString getId() const;
    QString getLabel()const;
    QString getEmail()const;
    QString getUsername()const;
    QString getPass()const;
    QString getCreated() const;
    QString getLastModified() const;
    //setters:
    void setId(const QString& id);
    void setLabel(const QString& label);
    void setEmail(const QString& email);
    void setUsername(const QString& username);
    void setPass(const QString& pass);
    void setCreated(const QString& created);
    void setLastModified(const QString& lastModified);
    //functions:
    bool createPassword(Password p);
    QList<Password> listPassword();
    bool deletePassword(QString id);
    Password searchPassword(QString id);

};

#endif // PASSWORD_H
