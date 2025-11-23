#include <iostream>
#include <string>
#include <vector>
using namespace std;

// --------------------- КЛАСС ТОВАРА ------------------------
class Product {
private:
    int id;
    string name;
    double price;
    int quantity;

public:
    Product(int id, string name, double price, int quantity)
        : id(id), name(name), price(price), quantity(quantity) {}

    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void setName(const string& newName) { name = newName; }
    void setPrice(double newPrice) { price = newPrice; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }

    void printInfo() const {
        cout << "ID: " << id
             << " | Название: " << name
             << " | Цена: " << price
             << " | Кол-во: " << quantity << endl;
    }
};

// --------------------- КЛАСС МАГАЗИНА ------------------------
class Store {
private:
    vector<Product> products;
    int nextId = 1;

public:
    // Добавление товара
    void addProduct(const string& name, double price, int quantity) {
        products.emplace_back(nextId++, name, price, quantity);
        cout << "Товар добавлен!\n";
    }

    // Удаление товара
    void removeProduct(int id) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if (it->getId() == id) {
                products.erase(it);
                cout << "Товар удалён!\n";
                return;
            }
        }
        cout << "Товар с таким ID не найден.\n";
    }

    // Редактирование данных товара
    void editProduct(int id, string newName, double newPrice) {
        for (auto &p : products) {
            if (p.getId() == id) {
                p.setName(newName);
                p.setPrice(newPrice);
                cout << "Информация обновлена!\n";
                return;
            }
        }
        cout << "Товар с таким ID не найден.\n";
    }

    // Изменение количества
    void changeQuantity(int id, int newQuantity) {
        for (auto &p : products) {
            if (p.getId() == id) {
                p.setQuantity(newQuantity);
                cout << "Количество изменено!\n";
                return;
            }
        }
        cout << "Товар с таким ID не найден.\n";
    }

    // Вывод всех товаров
    void listProducts() const {
        if (products.empty()) {
            cout << "Нет товаров.\n";
            return;
        }
        cout << "\n===== АССОРТИМЕНТ МАГАЗИНА =====\n";
        for (const auto &p : products)
            p.printInfo();
        cout << "=================================\n\n";
    }
};

// ------------------------- MAIN -----------------------------
int main() {
    setlocale(LC_ALL, "Russian");
    Store store;

    int choice;
    while (true) {
        cout << "1. Добавить товар\n"
             << "2. Удалить товар\n"
             << "3. Редактировать товар\n"
             << "4. Изменить количество\n"
             << "5. Показать все товары\n"
             << "0. Выход\n"
             << "Выберите действие: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                string name;
                double price;
                int qty;
                cout << "Название: ";
                cin >> name;
                cout << "Цена: ";
                cin >> price;
                cout << "Количество: ";
                cin >> qty;
                store.addProduct(name, price, qty);
                break;
            }
            case 2: {
                int id;
                cout << "Введите ID товара: ";
                cin >> id;
                store.removeProduct(id);
                break;
            }
            case 3: {
                int id;
                string name;
                double price;
                cout << "Введите ID товара: ";
                cin >> id;
                cout << "Новое название: ";
                cin >> name;
                cout << "Новая цена: ";
                cin >> price;
                store.editProduct(id, name, price);
                break;
            }
            case 4: {
                int id, qty;
                cout << "Введите ID товара: ";
                cin >> id;
                cout << "Новое количество: ";
                cin >> qty;
                store.changeQuantity(id, qty);
                break;
            }
            case 5:
                store.listProducts();
                break;

            default:
                cout << "Неверный ввод!\n";
        }
    }

    return 0;
}
