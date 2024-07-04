#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QString>
#include <QRegularExpression>

class Validator {
private:
    bool hasMinimumLength(const QString &password);
    bool hasUppercaseLetter(const QString &password);
    bool hasLowercaseLetter(const QString &password);
    bool hasDigit(const QString &password);

public:
    bool validatePassword(const QString &password);
    bool validateLogin(const QString& login);
};

#endif // VALIDATOR_H
