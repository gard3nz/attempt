#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Product {
private:
    int id;
    string name;
    int quantity;

public:
    Product(int productId, const string& productName, int productQuantity)
        : id(productId), name(productName), quantity(productQuantity) {}

    int getId() const {return id;}
    string getName() const {return name;}
    int getQuantity() const {return quantity;}

    void setName(const string& newName) {name = newName;}
    void setQuantity(int newQuantity) {quantity = newQuantity;}

    void display() const {
        cout << "ID: " << id << ", Название: " << name 
                  << ", Количество: " << quantity << endl;
    }
};

int main(){

}
