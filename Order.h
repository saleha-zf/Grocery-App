#ifndef ORDER_H
# define ORDER_H
#include "product.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;
class Order {
public:
    Order(string customerInfo, const vector<Product*> products)
        : orderDate(time(nullptr)), customerInfo(customerInfo), products(products) {}

    const vector<Product*> getProducts() const {
        return products;
    }

    time_t getOrderDate() const {
        return orderDate;
    }

    string getCustomerInfo() const {
        return customerInfo;
    }

private:
    time_t orderDate;
    string customerInfo;
    vector<Product*> products;
};

/*cout << "Order history:" << endl;
                for (const auto& order : store.getOrderHistory()) {
                    time_t orderDate = order.getOrderDate();
                    tm timeinfo;
                    char buffer[26];
                    localtime_s(&timeinfo, &orderDate);
                    asctime_s(buffer, sizeof(buffer), &timeinfo);

                    cout << "Order Date: " << buffer
                        << "Customer Info: " << order.getCustomerInfo() << endl
                        << "Ordered products:" << endl;
                    for (const auto& orderedProduct : order.getProducts()) {
                        cout << "- " << orderedProduct.getName() << " - $" << orderedProduct.getPrice()
                            << " - " << orderedProduct.getDescription() << endl;
                    }
                    cout << endl;
                }


//NEW PART

vector<Order> ordersList; // Universal orders list

void addOrder(const string& customerName, const vector<Product>& products) {
    Order newOrder(customerName, products);
    ordersList.push_back(newOrder);
}

void saveOrdersToFile(const string& filename) {
    ofstream outFile(filename);

    for (const Order& order : ordersList) {
        outFile << order.getCustomerInfo() << ",";
        outFile << order.getOrderDate() << ",";

        const vector<Product>& products = order.getProducts();
        outFile << products.size() << ",";

        for (const Product& product : products) {
            outFile << product.getName() << ";" << product.getPrice() << ";";
        }
        outFile << endl;
    }

    outFile.close();
}

void loadOrdersFromFile(const string& filename) {
    ifstream inFile(filename);
    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string customerName;
        getline(ss, customerName, ',');

        string orderDateString;
        getline(ss, orderDateString, ',');
        time_t orderDate = stoi(orderDateString);

        string productsCountStr;
        getline(ss, productsCountStr, ',');
        size_t productsCount = stoi(productsCountStr);

        vector<Product> products;
        for (size_t i = 0; i < productsCount; ++i) {
            string productInfo;
            getline(ss, productInfo, ';');
            string productName = productInfo;

            getline(ss, productInfo, ';');
            double productPrice = stod(productInfo);

            products.emplace_back(productName, productPrice);
        }

        ordersList.emplace_back(customerName, products);
    }

    inFile.close();
}

vector<Order> getOrdersByCustomer(const string& customerName) {
    vector<Order> customerOrders;

    for (const Order& order : ordersList) {
        if (order.getCustomerInfo() == customerName) {
            customerOrders.push_back(order);
        }
    }

    return customerOrders;
}

void ProductCatalogue:: Purchase() {
    // ... (the existing code in the function stays the same)

        processPayment(selectedProducts, totalAmount, paymentMethod);

        string buyerName;
        cout << "Enter the buyer's name: ";
        cin >> buyerName;

        vector<Product> purchasedProducts;
        for (const Product* product : selectedProducts) {
            purchasedProducts.push_back(*product);
        }

        addOrder(buyerName, purchasedProducts);
        saveOrdersToFile("orders.txt");

        char response;
        cout << "Do you want to continue shopping? (y/n): ";
        cin >> response;

        if (response != 'y' && response != 'Y') {
            continueShopping = false;
        }
}*/

#endif