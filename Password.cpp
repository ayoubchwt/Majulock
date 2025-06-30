#include "Password.h"
Password::Password() {}
Password::Password(QString id, QString label,QString email,QString username,QString pass, QString created, QString lastModified){
    this->id = id;
    this->label = label;
    this->email = email;
    this->username = username;
    this->pass = pass;
    this->created = created;
    this->lastModified = lastModified;
}
//getters :
QString Password::getId() const{
    return this->id;
}
QString Password::getLabel() const{
    return this->label;
}
QString Password::getEmail() const{
    return this->email;
}
QString Password::getUsername() const{
    return this->username;
}
QString Password::getPass() const{
    return this->pass;
}
QString Password::getCreated() const{
    return this->created;
}
QString Password::getLastModified() const{
    return this->lastModified;
}
//setters:
void Password::setId(const QString& id){
    this->id = id;
}
void Password::setLabel(const QString& label){
    this->label = label;
}
void Password::setEmail(const QString& email){
    this->email = email ;
}
void Password::setUsername(const QString& username){
    this->username = username;
}
void Password::setPass(const QString& pass){
    this->pass = pass;
}
void Password::setCreated(const QString& created){
    this->created = created;
}
void Password::setLastModified(const QString& lastModified){
    this->lastModified = lastModified;
}
bool Password::createPassword(Password p){
    QSqlQuery query;
    query.prepare("INSERT INTO password(label, email, username, pass, created, lastModified) VALUES(:label, :email, :username, :pass, :created, :lastModified)");
    query.bindValue(":label", p.getLabel());
    query.bindValue(":email", p.getEmail());
    query.bindValue(":username", p.getUsername());
    query.bindValue(":pass", p.getPass());
    query.bindValue(":created", p.getCreated());
    query.bindValue(":lastModified", p.getLastModified());
    qDebug() << query.boundValues();
    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError().text();
        return false;
    } else {
        qDebug() << "Password inserted successfully!";
        return true;
    }
}
QList<Password> Password::listPassword() {
    QList<Password> passwordList;
    QSqlQuery query;
    query.prepare("SELECT * FROM password");
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return passwordList;
    }
    while (query.next()) {
        Password p(
            query.value("id").toString(),
            query.value("label").toString(),
            query.value("email").toString(),
            query.value("username").toString(),
            query.value("pass").toString(),
            query.value("created").toString(),
            query.value("lastModified").toString()
            );
        passwordList.append(p);
    }
    return passwordList;
}
bool Password::deletePassword(QString id){
    QSqlQuery query;
    query.prepare("DELETE FROM password WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Error deleting password:" << query.lastError().text();
        return false;
    }
    return true;
}
Password Password::searchPassword(QString id){
    QSqlQuery query;
    query.prepare("SELECT * FROM password WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error searching password:" << query.lastError().text();
        return Password();
    }
    if (query.next()) {
        return Password(
            query.value(0).toString(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toString()
            );
    }
    return Password();
}
