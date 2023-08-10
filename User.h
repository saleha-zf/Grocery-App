#include <iostream>
#include <limits>
#include <iostream>
#include <fstream>
#include "Authentication.h"
#include "Feedback.h"
#include "product.h"
#include "getpass.h"
#include "Order.h"

#ifndef USER_H
# define USER_H

using namespace std;

class User {
protected:
    Authentication authentication;
    ofstream file;

public:
    bool isAuthenticated;
    ProductCatalogue catalogue;
    User(const string& username, const string& password, const string& filename);
    friend void loginMenu();

    virtual void login() = 0;


    SuggestionAndComplaints SC;
};
#endif

User::User(const string& username, const string& password, const string& filename)
    : authentication(username, password, filename) {}


class Buyer : public User {
public:
    Buyer(const string& username, const string& password, const string& filename);

    void login() override;
    void createUser();
    SuggestionAndComplaints SC;
};

Buyer::Buyer(const string& username, const string& password, const string& filename)
    : User(username, password, filename) {
    file.open("txt files/buyer.txt", ios::app);
}


void Buyer::login() {
    if (authentication.authenticate()) {
        isAuthenticated = true;
        cout << "\033[2J\033[0;0H"; // clears the screen
        cout << "\n\033[2;32mUser Login successful. Welcome, " << authentication.username << "!\n\n\033[0;0m";
    } else {
        isAuthenticated = false;
        cout << "\033[2J\033[0;0H"; // clears the screen
        cout << "\n\033[0;31mUser login failed. Invalid credentials.\n\033[0;0m";
    }

    if (isAuthenticated) {
        int choice;
        bool exitMenu = false;

        while (!exitMenu) {
            // User Menu
            cout << "\033[1;36mUser Menu:\033[0;0m" << std::endl;
            cout << "\033[3;34m1. Shop Now" << std::endl;
            cout << "2. Register Complaint" << std::endl;
            cout << "3. Exit" << std::endl;
            cout << "\033[4;36mEnter your choice: ";

            if (!(cin >> choice)) {
                cout << "\033[0m"; // Reset text colors
                cin.clear();       // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters in input buffer
                cout << "\033[0;31mInvalid input. Please enter a valid option.\n" << endl;
                continue;
            }

            switch (choice) {
                case 1: {
                    ProductCatalogue catalogue;
                    catalogue.startShopping();
                    catalogue.Purchase();
                    break;
                }
                case 2:
                    SC.registerComplaint(authentication.username);
                    break;
                case 3:
                    exitMenu = true;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
            cout << endl;
        }
    }
}



void Buyer::createUser() {
    if (!file.is_open()) {
        cout << "Unable to open file.";
        return;
    }

NewUserInput:
    cout << "\n\n\033[4;34mEnter New Username:";
    cin >> authentication.username;

    cout << "Enter Password:";
    authentication.password = getPassword();

    while (authentication.authenticate()) {
        cout << "\n\033[0;31mUser already exists. Try again.\033[0;0m";
        goto NewUserInput;
    }

    file << authentication.username << ';' << authentication.password << endl;
    cout << "\033[2J\033[0;0H";//clears the screen
    cout << "\n\033[1;35mNew user created!\n\033[0;0m";


}


class Admin : public User {
public:
    Admin(const string& username, const string& password, const string& filename);

    void login() override;
};

Admin::Admin(const string& username, const string& password, const string& filename)
    : User(username, password, filename) {
    file.open("txt files/admin.txt", ios::app);
}

void Admin::login() {
    cout << "\033[2J\033[0;0H"; // clears the screen

    if (authentication.authenticate()) {
        isAuthenticated = true;
        cout << "\n\033[2;32mAdmin login successful. Welcome, " << authentication.username << "!\n\033[0;0m";
    } else {
        isAuthenticated = false;
        cout << "\n\033[0;31mAdmin login failed. Invalid credentials.\n\033[0;0m";
    }

    if (isAuthenticated) {
        int choice;
        bool exitMenu = false;

        while (!exitMenu) {
            // Admin Menu
            cout << "\n\033[1;36m=== Admin Menu ===\033[0;0m" << endl;
            cout << "\033[3;34m1. Add Product" << endl;
            cout << "2. Read Feedback" << endl;
            cout << "3. Exit" << endl;
            cout << "\033[4;36mEnter your choice: ";

            if (!(cin >> choice)) {
                cout << "\033[0m"; // Reset text colors
                cin.clear();       // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters in input buffer
                cout << "\033[0;31mInvalid input. Please enter a valid option." << endl;
                continue;
            }

            switch (choice) {
                case 1:
                    catalogue.WriteToFile();
                    break;
                case 2:
                    SC.viewComplaints();
                    break;
                case 3:
                    cout << "\033[2J\033[0;0H"; // clears the screen
                    exitMenu = true;
                    break;
                default:
                    cout << "\033[31mInvalid choice. Please try again." << endl;
            }
        }
    }
}



void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void loginMenu()
{
    ProductCatalogue catalogue;
    int userType;
    while (true)
    {
        // cout << "\033[2J\033[0;0H"; // clears the screen

        std::cout << "\n\033[1;36m=== Login Menu ===\033[0;0m" << std::endl;
        std::cout << "\033[3;34m1. User Login" << std::endl;
        std::cout << "2. User SignUp" << std::endl;
        std::cout << "3. Admin Login" << std::endl;
        std::cout << "4. Proceed as Guest" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "\033[4;36mEnter your choice: ";

        if (!(std::cin >> userType))
        {
            std::cout << "\033[0m"; // Reset text colors
            clearInputBuffer();     // Clear input stream
            std::cout << "\033[0;31mInvalid input. Please enter a valid option." << std::endl;
            continue;
        }

        if (userType == 1 || userType == 3)
        {
            std::string username, password;
            std::cout << "Enter Username: ";
            std::cin >> username;
            std::cout << "Enter Password: ";
            password = getPassword();

            if (userType == 1) // for buyer login
            {
                Buyer buyer(username, password, "txt files/buyer.txt");
                buyer.login();
            }
            else if (userType == 3) // Admin login
            {
                Admin admin(username, password, "txt files/admin.txt");
                admin.login();
                // admin functions
            }
        }
        else if (userType == 2) // buyer signup
        {
            Buyer buyer("", "", "txt files/buyer.txt");
            buyer.createUser();
            buyer.login();
        }
        else if (userType == 4) // for non-logged-in members
        {
            // show product catalogue
            catalogue.startShopping();
            std::cout << "\033[2J\033[0;0H"; // clears the screen
            std::cout << "\n\033[1;35mPlease login to continue shopping. ";
            continue;
        }
        else if (userType == 5) // exit
        {
            std::cout << "\033[2J\033[0;0H"; // clears the screen
            std::cout << "\n\033[1;35mThank you for using our program. Goodbye! ";
            break;
        }
        else
        {
            std::cout << "Enter a valid option." << std::endl;
        }
    }
}

