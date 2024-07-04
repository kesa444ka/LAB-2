#include "loginpassword.h"
#include "ui_loginpassword.h"

LoginPassword::LoginPassword(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginPassword)
{
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginPassword::onLoginButtonClicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &LoginPassword::onRegisterButtonClicked);
}

void LoginPassword::setMessage(const QString& message){
    ui->messageLabel->setText(message);
}

void LoginPassword::onLoginButtonClicked() {
    QString login = ui->loginInput->text();
    QString password = ui->passwordInput->text();
    emit Login(login, password);
}


void LoginPassword::onRegisterButtonClicked() {
    QString login = ui->loginInput->text();
    QString password = ui->passwordInput->text();
    emit Registration(login, password);
}

LoginPassword::~LoginPassword()
{
    delete ui;
}
