#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to check if account number exists
bool accountExists(int accNo) {
    ifstream file("account.txt");
    if (!file) return false;
    
    int savedAcc, savedPin;
    double balance;
    string name;
    
    while (file >> savedAcc) {
        file.ignore(); // Skip newline
        getline(file, name);
        file >> savedPin;
        file >> balance;
        
        if (savedAcc == accNo) {
            file.close();
            return true;
        }
    }
    
    file.close();
    return false;
}

// Function to create a new account
void createAccount() {
    int accNo, pin;
    string name;
    double balance;
    
    cout << "\nEnter Account Number: ";
    cin >> accNo;
    
    // Check if account already exists
    if (accountExists(accNo)) {
        cout << "\nAccount number already exists!\n";
        return;
    }
    
    cin.ignore(); // Clear input buffer
    cout << "Enter Account Holder Name: ";
    getline(cin, name);
    
    cout << "Create PIN (4 digits): ";
    cin >> pin;
    
    // Check if PIN is 4 digits
    if (pin < 1000 || pin > 9999) {
        cout << "\nPIN must be 4 digits!\n";
        return;
    }
    
    cout << "Enter Starting Balance: $";
    cin >> balance;
    
    if (balance < 0) {
        cout << "\nBalance cannot be negative!\n";
        return;
    }