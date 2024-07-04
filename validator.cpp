#include "validator.h"

bool Validator::hasMinimumLength(const QString &password){
    return password.length() >= 8;
}

bool Validator::hasUppercaseLetter(const QString &password){
    QRegularExpression regex("[A-Z]");
    return password.contains(regex);
}

bool Validator::hasLowercaseLetter(const QString &password){
    QRegularExpression regex("[a-z]");
    return password.contains(regex);
}

bool Validator::hasDigit(const QString &password){
    QRegularExpression regex("[0-9]");
    return password.contains(regex);
}

bool Validator::validatePassword(const QString &password){
    return (hasMinimumLength(password) && hasUppercaseLetter(password) && hasLowercaseLetter(password) && hasDigit(password));
}

bool Validator::validateLogin(const QString& login) {
    return login.length() >= 5 && login.length() <= 30 && (hasUppercaseLetter(login) || hasLowercaseLetter(login));
}
