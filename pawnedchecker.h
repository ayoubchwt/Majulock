#ifndef PAWNEDCHECKER_H
#define PAWNEDCHECKER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QCryptographicHash>

class PawnedChecker : public QObject
{
    Q_OBJECT
public:
    explicit PawnedChecker(QObject *parent = nullptr);
    void checkPassword(const QString &password);

signals:
    void passwordPwned(int count);
    void passwordSafe();
    void checkFailed(const QString &error);

private:
    QNetworkAccessManager *manager;
};

#endif // PAWNEDCHECKER_H
