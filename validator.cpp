#include "validator.h"

Validator::Validator() {}
bool Validator::validateEmail(const QString &email){
    static QRegularExpression emailRegex(
        R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)"
        );
    return emailRegex.match(email).hasMatch();
}
bool Validator::validatePassword(const QString &password){
    return password.trimmed().length() >= 8;
}
bool Validator::validateLabel(const QString &label){
    return label.trimmed().length() >= 2;
}


