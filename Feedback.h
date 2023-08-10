#include <iostream>
#include <limits>
#include <iostream>
#include <fstream>
#ifndef FEEDBACK_H
# define FEEDBACK_H
using namespace std;


class SuggestionAndComplaints {
public:
    void registerComplaint(string);
    void viewComplaints();
 
};

void SuggestionAndComplaints::registerComplaint(string Username) {
    string complaint;
    cout << "\nEnter your feeback: \n";
    cin.ignore();
    getline(cin, complaint);
    ofstream outfile("txt files/feedback.txt", ios::app);
    outfile <<Username<<": "<<complaint<<endl;
    outfile.close();
    cout << "\033[2J\033[0;0H";//clears the screen
    cout << "\033[1;32mComplaint registered successfully!\n";
}

void SuggestionAndComplaints::viewComplaints() {
    ifstream infile("txt files/feedback.txt");
    string complaint;

    cout << "List of complaints:\n";
    while (getline(infile, complaint)) {
        cout << "- " << complaint << endl;
    }

    infile.close();
}




#endif