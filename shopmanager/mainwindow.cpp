#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQuery>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>


Product::Product(int id, const QString name, const QString department, int quantity)
    : id(id), name(name), department(department), quantity(quantity){};

int Product::getid() const { return id; }
QString Product::getname() const { return name; }
QString Product::getdepartment() const { return department; }
int Product::getquantity() const { return quantity; }

void Product::setname( QString name_) { this->name = name_; }
void Product::setdepartment( QString department_) { this->department = department_; }
void Product::setquantity(int quantity_) { this->quantity = quantity_; }


Store::Store(QObject *parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./shopmanagerdb.db");

    if(!db.open()) {
        qDebug() << "База данных не открылась";
    }

    query = new QSqlQuery(db);
    query->exec(
            "CREATE TABLE Assortment (Id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "Product TEXT, Department TEXT, Quantity INTEGER)"
    );

    model = new QSqlTableModel(parent, db);
    model->setTable("Assortment");
    model->select();
};

QSqlTableModel* Store::getmodel() const
{
    return model;
}

void Store::addproduct(const Product &p)
{
    int row = model->rowCount();
    model->insertRow(row);

    model->setData(model->index(row, 1), p.getname());
    model->setData(model->index(row, 2), p.getdepartment());
    model->setData(model->index(row, 3), p.getquantity());

    model->submitAll();
    model->select();
}
void Store::removeproduct(int id)
{
    for(int i = 0; i < model->rowCount(); ++i){
        if(model->data(model->index(i, 0)).toInt() == id){
            model->removeRow(i);
            model->submitAll();
            model->select();
        }
    }
}


void Store::filterid(const QString id)
{
    model->setFilter(QString("Id LIKE '%%1%'").arg(id));
    model->select();
}
void Store::filtername(const QString name)
{
    model->setFilter(QString("Product LIKE '%%1%'").arg(name));
    model->select();
}
void Store::filterdepart(const QString department)
{
    model->setFilter(QString("Department LIKE '%%1%'").arg(department));
    model->select();
}



bool Auth::login(const QString us, const QString pass)
{
    return (us == validus &&
            pass == validpass);
}

Auth::Auth(const QString us, const QString pass):validus(us), validpass(pass){};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auth = new Auth("admin", "1234");
    if (!authorizeuser()){
        return;
    }
    store = new Store(this);
    ui->tableView->setModel(store->getmodel());
}
MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::authorizeuser()
{
    bool ok;
    QString username = QInputDialog::getText(this, "Авторизация",
        "Логин:", QLineEdit::Normal, "", &ok);
    if (!ok) {
        close();
        return false;
    }
    QString password = QInputDialog::getText(this, "Авторизация",
            "Пароль:", QLineEdit::Password, "", &ok);
    if (!ok) {
        close();
        return false;
    }
    if (auth->login(username, password)) {
        return true;
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль");
        return authorizeuser();
    }
}

void MainWindow::on_pushButton_clicked()
{
    Product p(0, "New product", "Department", 0);
    store->addproduct(p);
}
void MainWindow::on_pushButton_2_clicked()
{
    QSqlTableModel *model = store->getmodel();
    model->removeRow(row);
    model->submitAll();
    model->select();

}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    store->filterid(arg1);
}
void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    store->filtername(arg1);
}
void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    store->filterdepart(arg1);
}

void MainWindow::on_pushButton_3_clicked()
{
    if (row < 0 || row >= store->getmodel()->rowCount()) {
        QMessageBox::warning(this, "Ошибка", "Элемент для редактирования не был выбран");
        return;
    }

    QSqlTableModel *model = store->getmodel();

    int id = model->data(model->index(row, 0)).toInt();
    QString currentName = model->data(model->index(row, 1)).toString();
    QString currentDepartment = model->data(model->index(row, 2)).toString();
    int currentQuantity = model->data(model->index(row, 3)).toInt();

    Product p(id, currentName, currentDepartment, currentQuantity);
    bool ok;

    QString newname = QInputDialog::getText(this, "Изменить название", "Название:",
                QLineEdit::Normal, p.getname(), &ok);
    if (!ok) return;
    p.setname(newname);
    QString newdepartment = QInputDialog::getText(this, "Изменить отдел", "Отдел:",
                QLineEdit::Normal, p.getdepartment(), &ok);
    if (!ok) return;
    p.setdepartment(newdepartment);
    int newquantity = QInputDialog::getInt(this, "Изменить количество", "Количество:",
                p.getquantity(), 0, 1000000, 1, &ok);
    if (!ok) return;
    p.setquantity(newquantity);

    model->setData(model->index(row, 1), p.getname());
    model->setData(model->index(row, 2), p.getdepartment());
    model->setData(model->index(row, 3), p.getquantity());

    model->submitAll();
    model->select();
}
