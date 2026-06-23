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
    // Save to file
    ofstream file("account.txt", ios::app);
    file << accNo << endl;
    file << name << endl;
    file << pin << endl;
    file << balance << endl;
    file << "------------------------" << endl; // Separator between accounts
    file.close();
    
    cout << "\nAccount Created Successfully!\n";
}
// Function to find account and return its details
bool findAccount(int accNo, int& savedPin, double& balance, string& name) {
    ifstream file("account.txt");
    if (!file) return false;
    
    int tempAcc, tempPin;
    double tempBalance;
    string tempName;
    
    while (file >> tempAcc) {
        file.ignore();
        getline(file, tempName);
        file >> tempPin;
        file >> tempBalance;
        
        if (tempAcc == accNo) {
            savedPin = tempPin;
            balance = tempBalance;
            name = tempName;
            file.close();
            return true;
        }
    }
    
    file.close();
    return false;
}

// Function to update account balance
void updateBalance(int accNo, double newBalance) {
    ifstream file("account.txt");
    ofstream temp("temp.txt");
    
    int tempAcc, tempPin;
    double tempBalance;
    string tempName;
    
    while (file >> tempAcc) {
        file.ignore();
        getline(file, tempName);
        file >> tempPin;
        file >> tempBalance;
        
        if (tempAcc == accNo) {
            // Update this account with new balance
            temp << tempAcc << endl;
            temp << tempName << endl;
            temp << tempPin << endl;
            temp << newBalance << endl;
            temp << "------------------------" << endl;
        } else {
            // Copy as is
            temp << tempAcc << endl;
            temp << tempName << endl;
            temp << tempPin << endl;
            temp << tempBalance << endl;
            temp << "------------------------" << endl;
        }
    }
    
    file.close();
    temp.close();
    
    remove("account.txt");
    rename("temp.txt", "account.txt");
}