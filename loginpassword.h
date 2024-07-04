#ifndef LOGINPASSWORD_H
#define LOGINPASSWORD_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginPassword;
}
QT_END_NAMESPACE

class LoginPassword : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPassword(QWidget *parent = nullptr);
    ~LoginPassword();

    void setMessage(const QString &message);
signals:
    void Registration(const QString &login, const QString &password);
    void Login(const QString &login, const QString &password);
public slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();
private:
    Ui::LoginPassword *ui;
};

#endif // LOGINPASSWORD_H
