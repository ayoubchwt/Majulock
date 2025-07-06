#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <QString>
#include <QRegularExpression>
#include "pawnedchecker.h"
class Validator
{
public:
    Validator();
    static bool validateEmail(const QString &email);
    static bool validatePassword(const QString &password);
    static bool validateLabel(const QString &label);
};

#endif // VALIDATOR_H
