

#ifndef PRODUCT_H
#define PRODUCT_H

#include <vector>
#include <string>
using namespace std;

class Product {
protected:
    std::string name;
    double price;
    int quantity;
    std::string origin;

public:
    Product(const std::string& name, double price, int quantity, const std::string& origin);

    std::string getName() const;
    double getPrice() const;
    int getQuantity() const;
    std::string getOrigin() const;

    virtual void display() const = 0;
    virtual char getType() = 0;

};

class Fruit : public Product {
private:
    double weight;
public:
    Fruit(const std::string& name, double price, int quantity, const std::string& origin, double weight);
    void display() const;
    char getType();
};

class Vegetable : public Product {
private:
    double weight;
public:
    Vegetable(const std::string& name, double price, int quantity, const std::string& origin, double weight);
    void display() const;
    char getType();
};

class Dairy : public Product {
private:
    int volume;
public:
    Dairy(const std::string& name, double price, int quantity, const std::string& origin, int volume);
    void display() const;
    char getType();
};

class BakeryItem : public Product {
private:
    std::string expiry_date;
public:
    BakeryItem(const std::string& name, double price, int quantity, const std::string& origin, std::string expiry_date);
    void display() const;
    char getType();
};

class Confectionery : public Product {
private:
    int no_in_pack;
public:
    Confectionery(const std::string& name, double price, int quantity, const std::string& origin, int no_in_pack);
    void display() const;
    char getType();
};

class PaymentProcessor {
public:
    static bool processVisaPayment(const std::string& cardNumber, const std::string& cvv, const std::string& expirationDate, double amount);
    static bool processEasyPaisaPayment(const std::string& phoneNumber, const std::string& pin, double amount);
    static bool processApplePayPayment(const std::string& applePayToken, double amount);
};

class Order;
class ProductCatalogue {
private:
    bool continueShopping;
    std::vector<Product*> products;
    std::vector<Order> ordersList;

public:
    ProductCatalogue();
    ~ProductCatalogue();

    void loadProductsFromFile();
    void addProduct(Product* product);
    void displayCatalogue() const;
    Product* findProductByName(const std::string& name) const;
    double calculateTotalAmount(const std::vector<Product*>& selectedProducts) const;
    void generateReceipt(const std::vector<Product*>& selectedProducts, double totalAmount, const std::string& paymentMethod) const;
    void processPayment(const std::vector<Product*>& selectedProducts, double totalAmount, const std::string& paymentMethod) const;
    void startShopping();
    //const Product* findProduct(const std::string& productName) const;
    Product* findByCountry(const std::string& countryName);
    void findByPriceRange(double upperprice, double lowerprice) const;
    void sortByPriceHtoL();
    void sortByPriceLtoH();
    void Purchase();
    void saveOrdersToFile();
    void WriteToFile();
    void sortByType();
};

#endif  // HEADER_H
