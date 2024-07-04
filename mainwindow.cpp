#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
   // , loginWidget(new LoginPassword(this))
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("flowershop.db");

    connect(ui->loginWidget, &LoginPassword::Login, this, &MainWindow::onLogin);
    connect(ui->loginWidget, &LoginPassword::Registration, this, &MainWindow::onRegister);

    model = new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->view->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->view->setModel(model);

    connect(ui->menu, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::changeTable);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::onSaveButtonClicked);
    connect(ui->addRow, &QPushButton::clicked, this, &MainWindow::onAddRowClicked);
    connect(ui->deleteRow, &QPushButton::clicked, this, &MainWindow::onDeleteRowClicked);

    hideTableControls();
   // loginWidget->show();
}

void MainWindow::changeTable(int index) {
    QString tableName;
    if (index == 1) {
        tableName = "Flowers";
    } else if (index == 2) {
        tableName = "Compositions";
    } else if (index == 3) {
        tableName = "Flower_Comp";
    } else if (index == 4) {
        tableName = "Order";
    } else if (index == 5) {
        tableName = "User";
    }
    model->setTable(tableName);
    model->select();
}

void MainWindow::onAddRowClicked(){
    int row = model->rowCount();
    model->insertRow(row);
}

void MainWindow::onDeleteRowClicked(){
    QModelIndexList rows = ui->view->selectionModel()->selectedRows();

    for (const QModelIndex& index: rows){
        model->removeRow(index.row());
    }
}

void MainWindow::onSaveButtonClicked() {
    model->submitAll();
}

void MainWindow::onLogin(const QString &login, const QString &password) {
    if (checkCredentials(login, password)) {
        showTableControls();
    } else {
        ui->loginWidget->setMessage("Неправильный логин или пароль.");
    }
}

void MainWindow::onRegister(const QString &login, const QString &password) {
    if (!validator.validatePassword(password) || !validator.validateLogin(login)) {
        ui->loginWidget->setMessage("Пароль или логин не соответствует требованиям.\n"
                              "Логин должен содержать от 5 до 30 символов и хотя бы одну латинскую букву.\n"
                              "Пароль должен содержать не менее 8 символов, хотя бы одну строчную латинскую букву,\n"
                              "хотя бы одну заглавную латинскую букву и хотя бы одну цифру.");
        return;
    }

    registerUser(login, password);
    showTableControls();
}

bool MainWindow::checkCredentials(const QString &login, const QString &password) {
    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE login = :login AND password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.exec();

    return query.next();
}

void MainWindow::registerUser(const QString &login, const QString &password) {
    QSqlQuery query;
    query.prepare("INSERT INTO User (login, password) VALUES (:login, :password)");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.exec();
}

void MainWindow::showTableControls(){
    ui->loginWidget->hide();

    ui->label->show();
    ui->menu->show();
    ui->view->show();
    ui->addRow->show();
    ui->deleteRow->show();
    ui->saveButton->show();
}

void MainWindow::hideTableControls(){
    ui->label->hide();
    ui->menu->hide();
    ui->view->hide();
    ui->addRow->hide();
    ui->deleteRow->hide();
    ui->saveButton->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
