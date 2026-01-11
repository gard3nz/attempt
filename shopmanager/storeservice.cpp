#include "storeservice.h"

void StoreService::addProduct(const QString& name, double price, int quantity) {
    repository.addProduct(Product(0, name, price, quantity));
}

QVector<Product> StoreService::getProducts() {
    return repository.getAllProducts();
}

void StoreService::updateProduct(const Product& product) {
    repository.updateProduct(product);
}

void StoreService::deleteProduct(int id) {
    repository.removeProduct(id);
}
