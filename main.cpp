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


// Function to show ATM menu after login
void atmMenu(int accNo, string name, double& balance) {
    int choice;
    
    do {
        cout << "\n===== ATM MENU =====\n";
        cout << "1. Balance Inquiry\n";
        cout << "2. Withdraw\n";
        cout << "3. Fast Cash\n";
        cout << "4. Deposit\n";
        cout << "5. Logout\n";
        cout << "Enter Choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                // Balance Inquiry
                cout << "\nAccount Holder: " << name << endl;
                cout << "Balance: $" << balance << endl;
                break;
            }
            
            case 2: {
                // Withdraw
                double amount;
                cout << "\nEnter Amount to Withdraw: $";
                cin >> amount;
                
                if (amount <= 0) {
                    cout << "Invalid amount!\n";
                }
                else if (amount > balance) {
                    cout << "Insufficient Balance!\n";
                }
                else if (amount > 20000) {
                    cout << "Withdrawal limit is $20,000!\n";
                }
                else {
                    balance = balance - amount;
                    updateBalance(accNo, balance);
                    cout << "Withdrawal Successful!\n";
                    cout << "New Balance: $" << balance << endl;
                }
                break;
            }
            
            case 3: {
                // Fast Cash
                int option, amount;
                cout << "\n===== FAST CASH =====\n";
                cout << "1. $500\n";
                cout << "2. $1,000\n";
                cout << "3. $2,000\n";
                cout << "4. $3,000\n";
                cout << "5. $4,000\n";
                cout << "6. $5,000\n";
                cout << "Choose option: ";
                cin >> option;
                
                if (option == 1) amount = 500;
                else if (option == 2) amount = 1000;
                else if (option == 3) amount = 2000;
                else if (option == 4) amount = 3000;
                else if (option == 5) amount = 4000;
                else if (option == 6) amount = 5000;
                else {
                    cout << "Invalid option!\n";
                    break;
                }
                
                if (amount > balance) {
                    cout << "Insufficient Balance!\n";
                }
                else {
                    balance = balance - amount;
                    updateBalance(accNo, balance);
                    cout << "Fast Cash Successful!\n";
                    cout << "New Balance: $" << balance << endl;
                }
                break;
            }
            
            case 4: {
                // Deposit
                double deposit;
                cout << "\nEnter Deposit Amount: $";
                cin >> deposit;
                
                if (deposit <= 0) {
                    cout << "Invalid amount!\n";
                }
                else {
                    balance = balance + deposit;
                    updateBalance(accNo, balance);
                    cout << "Deposit Successful!\n";
                    cout << "New Balance: $" << balance << endl;
                }
                break;
            }
            
            case 5: {
                // Logout
                cout << "\nLogged Out Successfully!\n";
                cout << "Thank you, " << name << "!\n";
                break;
            }
            
            default: {
                cout << "Invalid choice! Please try again.\n";
            }
        }
    } while (choice != 5);
}
