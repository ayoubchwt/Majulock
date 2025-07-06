#include "pawnedchecker.h"

PawnedChecker::PawnedChecker(QObject *parent)
    : QObject(parent),
    manager(new QNetworkAccessManager(this))
{
}

void PawnedChecker::checkPassword(const QString &password)
{
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1).toHex().toUpper();
    QString prefix = hash.left(5);
    QString suffix = hash.mid(5);

    QString url = QString("https://api.pwnedpasswords.com/range/%1").arg(prefix);

    QNetworkRequest request{QUrl(url)};
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QList<QByteArray> lines = response.split('\n');
            bool found = false;

            for (const QByteArray &line : lines) {
                QList<QByteArray> parts = line.split(':');
                if (parts.size() >= 2) {
                    if (parts[0].trimmed() == suffix) {
                        found = true;
                        int count = parts[1].trimmed().toInt();
                        emit passwordPwned(count);
                        break;
                    }
                }
            }

            if (!found) {
                emit passwordSafe();
            }
        } else {
            emit checkFailed(reply->errorString());
        }
        reply->deleteLater();
    });
}
