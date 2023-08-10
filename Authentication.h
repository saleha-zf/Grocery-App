#include <iostream>
#include <limits>
#include <iostream>
#include <fstream>

#ifndef AUTHENTICATION_H
# define AUTHENTICATION_H

using namespace std;

class Authentication {
protected:
    fstream* file;
    string filename;

public:
    string username, password;

    Authentication(const string& username, const string& password, const string& filename);

    bool authenticate();
};

#endif