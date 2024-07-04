#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>

#include "validator.h"
#include "loginpassword.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void changeTable(int index);
    void onSaveButtonClicked();
    void onAddRowClicked();
    void onDeleteRowClicked();

    void onLogin(const QString &login, const QString &password);
    void onRegister(const QString &login, const QString &password);

private:
    Ui::MainWindow *ui;

    QSqlTableModel *model;
    Validator validator;

    bool checkCredentials(const QString &login, const QString &password);
    void registerUser(const QString &login, const QString &password);
    void showTableControls();
    void hideTableControls();

};
#endif // MAINWINDOW_H
