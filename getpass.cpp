#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <limits>
#include "getpass.h"
using namespace std;


//making a getch function bec we dont have conio.h in linux
int getch() {
    struct termios oldSettings, newSettings;
    int ch;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldSettings);

    // Copy the settings
    newSettings = oldSettings;

    // Disable canonical mode and input echo
    newSettings.c_lflag &= ~(ICANON | ECHO);

    // Set the new terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

    // Read a single character
    ch = getchar();

    // Restore the old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);

    return ch;

 
}




string getPassword() {
    string password;
    char ch;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.clear();
    while ((ch = getch()) != '\r' && ch != '\n') {  // Loop until Enter key is pressed
        if (ch == 8) {  // Check for backspace key (ASCII value 8)
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";  // Move the cursor back and overwrite the character with a space
            }
        } else if (ch >= 32 && ch <= 126) {  // Check for printable characters
            password.push_back(ch);
            cout << '*';  // Print an asterisk for each character
        }
    }

    return password;
}