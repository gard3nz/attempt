#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QString>

class Product
{
public:
    Product(int id, QString name, QString department, int quantity);
    void setname( QString name);
    void setdepartment( QString department);
    void setquantity(int quantity);

    int getid() const;
    QString getname() const;
    QString getdepartment() const;
    int getquantity() const;



private:
    int id;
    QString name;
    QString department;
    int quantity;
};

class Store
{
public:
    Store(QObject *parent = nullptr);

    QSqlTableModel* getmodel() const;

    void addproduct(const Product &p);
    void removeproduct(int id);
    void filterid(const QString id);
    void filtername(const QString name);
    void filterdepart(const QString department);

private:
    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlQuery *query;

};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Auth
{
public:
    Auth(const QString us, const QString pass);
    bool login(const QString us, const QString pass);

private:
    QString validus;
    QString validpass;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    Store *store;
    int row;
    Auth *auth;
    bool authorizeuser();
};

#endif // MAINWINDOW_H
