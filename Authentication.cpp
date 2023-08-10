
#include "Authentication.h"

Authentication::Authentication(const string& username, const string& password, const string& filename) {
    file = new fstream(filename, fstream::in | fstream::out);

  this->filename=filename;
  this->username=username;
  this->password=password;

}

bool Authentication::authenticate() {


    file->open(filename);
    if (!file->is_open()) {
        cout << "Unable to open file.";
        
        return false;
    }

    string savedUsername, savedPassword;

    file->open("authentication.txt", ios::in);
    file->clear();
    file->seekg(0, ios::beg);

    while (!file->eof()) {
        getline(*file, savedUsername, ';');
        getline(*file, savedPassword);

        if (username == savedUsername && password == savedPassword) {
            file->close();
            return true;
        }
    }

    file->clear();
    file->close();
    return false;
}



