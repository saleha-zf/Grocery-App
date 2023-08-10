
#include "product.h"
#include "getpass.h"
#include "Order.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>
#include <iomanip> 
using namespace std;

// Product class implementation

Product::Product(const string& name, double price, int quantity, const string& origin)
    : name(name), price(price), quantity(quantity), origin(origin) {}

string Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

string Product::getOrigin() const {
    return origin;
}

void Product::display() const {
    cout << "\033[0;0m\033[1;32mProduct: " << name << endl;
    cout << "\033[3;34mPrice: PKR " << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Origin: " << origin << endl;
}


// Fruit class implementation

Fruit::Fruit(const string& name, double price, int quantity, const string& origin, double weight)
    : Product(name, price, quantity, origin) {
    this->weight = weight;
}

void Fruit::display() const {
    cout << "\033[0;0m\033[1;32mProduct: " << name << endl;
    cout << "\033[3;34mPrice: PKR " << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Origin: " << origin << endl;
    cout << "Weight: " << weight << " kg" << endl;
}

char Fruit::getType() {
    return 'f';
}

// Vegetable class implementation

Vegetable::Vegetable(const string& name, double price, int quantity, const string& origin, double weight)
    : Product(name, price, quantity, origin) {
    this->weight = weight;
}

void Vegetable::display() const {
    cout << "\033[0;0m\033[1;32mProduct: " << name << endl;
    cout << "\033[3;34mPrice: PKR " << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Origin: " << origin << endl;
    cout << "Weight: " << weight << endl;
}

char Vegetable::getType() {
    return 'v';
}

// Dairy class implementation

Dairy::Dairy(const string& name, double price, int quantity, const string& origin, int volume)
    : Product(name, price, quantity, origin) {
    this->volume = volume;
}

void Dairy::display() const {
    cout << "\033[0;0m\033[1;32mProduct: " << name << endl;
    cout << "\033[3;34mPrice: PKR " << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Origin: " << origin << endl;
    cout << "Volume: " << volume << " ml" << endl;
}

char Dairy::getType() {
    return 'd';
}

// BakeryItem class implementation

BakeryItem::BakeryItem(const string& name, double price, int quantity, const string& origin, string expiry_date)
    : Product(name, price, quantity, origin) {
    this->expiry_date = expiry_date;
}

void BakeryItem::display() const {
    cout << "\033[0;0m\033[1;32mProduct: " << name << endl;
    cout << "\033[3;34mPrice: PKR " << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Origin: " << origin << endl;
    cout << "Expiry date: " << expiry_date << endl;
}

char BakeryItem::getType() {
    return 'b';
}

// Confectionery class implementation

Confectionery::Confectionery(const string& name, double price, int quantity, const string& origin, int no_in_pack)
    : Product(name, price, quantity, origin) {
    this->no_in_pack = no_in_pack;
}

void Confectionery::display() const {
    cout << "\033[0;0m\033[1;32mProduct: " << name << endl;
    cout << "\033[3;34mPrice: PKR " << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Origin: " << origin << endl;
    cout << "No. in pack: " << no_in_pack << endl;
}

char Confectionery::getType() {
    return 'c';
}

// PaymentProcessor class implementation

bool PaymentProcessor::processVisaPayment(const string& cardNumber, const string& cvv, const string& expirationDate, double amount) {
    if (cardNumber.length() != 16) {
        cout << "Invalid Visa card number. It should be 16 digits.\n";
        return false;
    }

    if (cvv.length() != 3) {
        cout << "Invalid CVV. It should be 3 digits.\n";
        return false;
    }

    if (expirationDate.length() != 5 || expirationDate[2] != '/') {
        cout << "Invalid expiration date. It should be in the format MM/YY.\n";
        return false;
    }
    cout << "Processing Visa payment..." << endl;
    return true;
}

bool PaymentProcessor::processEasyPaisaPayment(const string& phoneNumber, const string& pin, double amount) {
    if (phoneNumber.length() != 11) {
        cout << "Invalid phone number. It should be 11 digits.\n";
        return false;
    }

    if (pin.length() != 4) {
        cout << "Invalid PIN. It should be 4 digits.\n";
        return false;
    }
    cout << "Processing EasyPaisa payment..." << endl;
    return true;
}

bool PaymentProcessor::processApplePayPayment(const string& applePayToken, double amount) {
    if (applePayToken.empty()) {
        cout << "Invalid Apple Pay token. Token should not be empty.\n";
        return false;
    }

    if (applePayToken.length() != 32) {
        cout << "Invalid Apple Pay token. Token length should be 32.\n";
        return false;
    }

    for (char c : applePayToken) {
        if (!isalnum(c)) {
            cout << "Invalid Apple Pay token. Token should only contain alphanumeric characters.\n";
            return false;
        }
    }

    cout << "Processing Apple Pay payment..." << endl;
    return true;
}

// ProductCatalogue class implementation

ProductCatalogue::ProductCatalogue() {
    loadProductsFromFile();
}

void ProductCatalogue::loadProductsFromFile() {
    ifstream inFile("txt files/products.txt");
    if (!inFile) {
        cerr << "Unable to open file";
        exit(1);
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string category, name, origin;
        double price;
        int quantity;
        Product* to_push;
        ss >> category;
        if (category == "Fruit") {
            double weight;
            ss >> name >> price >> quantity >> origin >> weight;
            to_push = new Fruit(name, price, quantity, origin, weight);
        }
        else if (category == "Vegetable") {
            double weight;
            ss >> name >> price >> quantity >> origin >> weight;
            to_push = new Vegetable(name, price, quantity, origin, weight);
        }
        else if (category == "Dairy") {
            int volume;
            ss >> name >> price >> quantity >> origin >> volume;
            to_push = new Dairy(name, price, quantity, origin, volume);
        }
        else if (category == "BakeryItem") {
            string expiry_date;
            ss >> name >> price >> quantity >> origin >> expiry_date;
            to_push = new BakeryItem(name, price, quantity, origin, expiry_date);
        }
        else if (category == "Confectionery") {
            int no_in_pack;
            ss >> name >> price >> quantity >> origin >> no_in_pack;
            to_push = new Confectionery(name, price, quantity, origin, no_in_pack);
        }
        else {
            cout << "Invalid category: " << category << endl;
            continue;
        }

        addProduct(to_push);
    }

    inFile.close();  // Closigns
}

void ProductCatalogue::addProduct(Product* product) {
    products.push_back(product);
}
void ProductCatalogue::WriteToFile()
{
    string name, price, quantity, origin, type, attribute;
    cin.ignore();
    cout << "Enter product type: ";
    getline(cin, type);

    cout << "Enter product name: ";
    getline(cin, name);

    cout << "Enter product price: ";
    getline(cin, price);

    cout << "Enter product quantity: ";
    getline(cin, quantity);
  
    cout << "Enter product origin: ";
    getline(cin, origin);

    cout << "Enter weight/volume OR expiry date: ";
    getline(cin, attribute);

    loadProductsFromFile();  // Load existing products

    ofstream outFile("txt files/products.txt", ios::app);  // to append new products

    if (!outFile) {
        cout << "Failed to open file for writing." << endl;
        return;
    }

  outFile << type << " " << name << " " << price << " " << quantity << " " << origin << " " << attribute;
    outFile << endl;
    outFile.close();
    loadProductsFromFile();  // Reload products after appending the new one
    cout << "\033[1;32mProduct added successfully." << endl;
}



void ProductCatalogue::displayCatalogue() const {
    const int columnWidth = 20;
    const int productsPerRow = 5;

    cout << "\n\033[1;37mProduct Catalogue:\n" << endl;

    // Print products
    int count = 0;
    for (const Product* product : products) {
       cout << setw(columnWidth) << left << "Product: " + product->getName();
        cout << setw(columnWidth) << left << "Price: PKR " + to_string(product->getPrice());
        cout << setw(columnWidth) << left << "Quantity: " + to_string(product->getQuantity());
        cout << setw(columnWidth) << left << "Origin: " + product->getOrigin();

        // Start a new line after printing the specified number of products per row
        if (++count % productsPerRow == 0) {
            cout << endl;
        }
    }

    // Add an extra newline if the last row is not complete
    if (count % productsPerRow != 0) {
        cout << endl;
    }

    cout << endl;
}

double ProductCatalogue::calculateTotalAmount(const vector<Product*>& selectedProducts) const {
    double totalAmount = 0.0;
    for (const Product* product : selectedProducts) {
        totalAmount += product->getPrice();
    }
    return totalAmount;
}

void ProductCatalogue::generateReceipt(const vector<Product*>& selectedProducts, double totalAmount, const string& paymentMethod) const {
  cout<<"\033[47m";
    cout << "\033[0;30m---------------------" << endl;
    cout << "       RECEIPT       " << endl;
    cout << "---------------------" << endl;
    cout << endl;
    cout << "Selected Products:" << endl;
    cout << endl;

    for (const Product* product : selectedProducts) {
        cout << "Product: " << product->getName() << endl;
        cout << "Price: PKR " << product->getPrice() << endl;
        cout << "Quantity: " << product->getQuantity() << endl;
        cout << "Origin: " << product->getOrigin() << endl;
        cout << "---------------------" << endl;
    }

    cout << "Total Amount: PKR " << totalAmount << endl;
    cout << "Payment Method: " << paymentMethod << endl;
    cout << endl;
    cout << "---------------------\033[0m" << endl;
}

void ProductCatalogue::processPayment(const vector<Product*>& selectedProducts, double totalAmount, const string& paymentMethod) const {
    cout << "\033[1;37mTotal Amount: PKR " << totalAmount << endl;

    bool paymentSuccess = false;

    if (paymentMethod == "Visa") {
        string cardNumber, cvv, expirationDate;
        cout << "\033[1;36mEnter card number: ";
        cin >> cardNumber;
        cout << "Enter CVV: ";
        cvv = getPassword();
        cout << "\nEnter expiration date (MM/YY): ";
        cin >> expirationDate;

        paymentSuccess = PaymentProcessor::processVisaPayment(cardNumber, cvv, expirationDate, totalAmount);
    }
    else if (paymentMethod == "EasyPaisa") {
        string phoneNumber, pin;
        cout << "\033[1;36mEnter phone number: ";
        cin >> phoneNumber;
        cout << "Enter PIN: ";
        pin = getPassword();

        paymentSuccess = PaymentProcessor::processEasyPaisaPayment(phoneNumber, pin, totalAmount);
    }
    else if (paymentMethod == "ApplePay") {
        string applePayToken;
        cout << "\033[1;36mEnter Apple Pay token: ";
        cin >> applePayToken;

        paymentSuccess = PaymentProcessor::processApplePayPayment(applePayToken, totalAmount);
    }
    else {
        cout << "\033[1;31mInvalid payment method selected." << endl;
    }

    if (paymentSuccess) {
        cout << "\033[1;32mPayment successful." << endl;
        
        generateReceipt(selectedProducts, totalAmount, paymentMethod);
        
    }
    else {
        cout << "\033[1;31mPayment failed.\033[0m" << endl;
    }
}


ProductCatalogue::~ProductCatalogue() {
    for (Product* product : products) {
        delete product;
    }
}

void ProductCatalogue::startShopping() {
     continueShopping = true;

    while (continueShopping) {
        //new
      
      
        cout << "\n\e[0;90m\033[1;32mSearch & Filter" << endl;
        cout << "\033[2;30m1. Search Product by Name" << endl;
        cout << "2. Find Products by Country" << endl;
        cout << "3. Find Products by Price Range" << endl;
        cout << "4. Sort Catalogue by Price (High to Low)" << endl;
        cout << "5. Sort Catalogue by Price (Low to High)" << endl;
        cout << "6. Sort by type" << endl;
        cout << "7. Add to cart" << endl;
        cout << "Enter option (1-7): ";
        int option;

      //here
      
       
        while (!(cin >> option)) {
            cin.clear(); // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
          
          cout << "\033[2J\033[1;1H";
            cout << "\033[0;31mInvalid input. Please enter a valid option (1-6): \nPress Enter to continue.\033[0m";
          break;
        }
        cin.ignore(); // Ignore any remaining newline character

        try {
            switch (option) {
                case 1: {
                    string productName;
                    cout << "\033[35mEnter the name of the product: ";
                    getline(cin, productName);
                    const Product* foundProduct = findProductByName(productName);
                    if (foundProduct) {
                        foundProduct->display();
                    } else {
                        cout << "Product not found!" << endl;
                    }
                    break;
                }
                case 2: {
                    string countryName;
                    int flag = 0;
                    cout << "Enter the country name (USA,UK,France,Germany,Thailand,Greece,Mexico,Turkey,Italy,Switzerland,India,Pakistan): ";
                    getline(cin, countryName);
                    for (const auto& product : products) {
                        if (countryName == product->getOrigin()) {
                            product->display();
                            cout << "\033[35m---------------------" << endl;
                            flag = 1;
                        }
                    }
                    if (flag == 0) cout << "No product found from the country. Try again.";
                    break;
                }
                case 3: {
                    double lowerPrice, upperPrice;
                    cout << "\033[35mEnter the lower price: ";
                    cin >> lowerPrice;
                    cout << "\033[35mEnter the upper price: ";
                    cin >> upperPrice;
                    findByPriceRange(upperPrice, lowerPrice);
                    break;
                }
                case 4:
                    sortByPriceHtoL();
                    break;
                case 5:
                    sortByPriceLtoH();
                    break;
                case 6:
                    sortByType();
                    break;
                case 7:
                    continueShopping = false;
                    break;
                default:
                  {
                    cout << "\033[2J\033[1;1H";
                    throw runtime_error("Invalid option. Please try again.");
                  }
            }
        } catch (const exception& e) {
            cout << "\033[0;31m" << e.what() << endl;
        }
    }
}

void ProductCatalogue::saveOrdersToFile() {
    ofstream outFile("txt files/orders.txt", ios::app);

    for (Order order : ordersList) {
        outFile << order.getCustomerInfo() << " ";
        outFile << order.getOrderDate() << " ";

        vector<Product*> products = order.getProducts();
        for (Product* product : products) {
            outFile << product->getName() << " " << product->getPrice() << " ";
        }
        outFile << endl;
    }

    outFile.close();
}

//void ProductCatalogue::loadOrdersFromFile(string inputname) {
//    ifstream inFile("orders.txt");
//    string line;
//    while (getline(inFile, line)) {
//        stringstream ss(line);
//        string buyername; time_t time; string productname; double price;
//        vector<Product*> temproducts;
//        ss >> buyername >> time;
//        if (buyername == )
//        cout << buyername << time;
//        while (ss) {
//            ss >> productname >> price;
//            cout << productname << price;
//        }
//    }
//    inFile.close();
//}

void ProductCatalogue::Purchase() {
    vector<Product*> selectedProducts;
    string productName;
    char addMoreProducts;

    do {
        cout << "\033[34mEnter the name of the product you want to purchase: ";
        cin >> productName;

        Product* product = findProductByName(productName);
        if (product) {
            selectedProducts.push_back(product);
        }
        else {
            cout << "\033[1;31mProduct not found!" << endl;
        }

        cout << "\033[1;34mDo you want to add more products? (y/n): ";
        cin >> addMoreProducts;
        cin.ignore();
    } while (addMoreProducts == 'y' || addMoreProducts == 'Y');

    double totalAmount = calculateTotalAmount(selectedProducts);

    string paymentMethod;
  
  
    cout << "\033[1;34mSelect a payment method (Visa, EasyPaisa, ApplePay): ";
    cin >> paymentMethod;

    processPayment(selectedProducts, totalAmount, paymentMethod);

    string buyerName;
    cout << "\033[1;34mEnter the buyer's name: ";
    cin >> buyerName;
    
    Order order(buyerName, selectedProducts);
    ordersList.push_back(order);
    saveOrdersToFile();

    char response;
    cout << "\033[1;34mDo you want to continue shopping? (y/n): ";
    cin >> response;

    if (response != 'y' && response != 'Y') {
        continueShopping = false;
    }
}



//Abdullah's functions
Product* ProductCatalogue::findProductByName(const string& name) const {
    for (Product* product : products) {
        std::string productName = product->getName();
        std::transform(productName.begin(), productName.end(), productName.begin(),
            [](unsigned char c) { return std::tolower(c); });

        std::string l_name = name;
        std::transform(l_name.begin(), l_name.end(), l_name.begin(),
            [](unsigned char c) { return std::tolower(c); });
        if (productName == l_name) {
            return product;
        }
    }
    return nullptr;
}

Product* ProductCatalogue::findByCountry(const std::string& countryName) {
    for (auto& product : products) {
        if (product->getOrigin() == countryName) {
            return product;
        }
    }
    return nullptr;
}

void ProductCatalogue::findByPriceRange(double upperprice, double lowerprice) const {
    for (const auto& product : products) {
        if (product->getPrice() >= lowerprice && product->getPrice() <= upperprice) {
            product->display();
            cout << "\033[3;30m---------------------" << endl;
        }
    }
}

void ProductCatalogue::sortByPriceHtoL() {
    vector<Product*> templist = products;
    sort(templist.begin(), templist.end(), [](const Product* a, const Product* b) {
        return a->getPrice() > b->getPrice();
        });

    cout << "\nCatalogue sorted by price high to low:" << endl;
    for (const auto& product : templist) {
        product->display();
        cout << "\033[3;30m---------------------" << endl;
    }
}

void ProductCatalogue::sortByPriceLtoH() {
    vector<Product*> templist = products;
    sort(templist.begin(), templist.end(), [](const Product* a, const Product* b) {
        return a->getPrice() < b->getPrice();
        });

    cout << "\nCatalogue sorted by price low to high:" << endl;
    for (const auto& product : templist) {
        product->display();
        cout << "\033[3;30m---------------------" << endl;
    }
}

void ProductCatalogue::sortByType() {
    vector<Product*> templist = products;
    char type;
    cout << "\nWhich type of products do you wish to see?\n>Fruits (f)\n>Vegetables (v)\n>Dairy (d)\n>Bakery Items (b)\n>Confectionery (c)\n";
    cout << "Enter the type (must be a letter): "; cin >> type; cout << endl;
    if (type != 'f' && type != 'v' && type != 'd' && type != 'b' && type != 'c') {
        cout << "Invalid input. Please pick from the given options!" << endl;
        sortByType();
    }

    cout << "Catalogue sorted by given type:" << endl;
    for (const auto& product : templist) {
        if (product->getType() == type) {
            product->display();
            cout << "\033[3;30m---------------------" << endl;
        }
    }
}

