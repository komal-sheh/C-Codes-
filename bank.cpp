#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class Account {
public:
    string accountNumber;
    string accountHolder;
    double balance;

    Account(string number, string holder, double initialBalance) {
        accountNumber = number;
        accountHolder = holder;
        balance = initialBalance;
    }
};

class Bank {
private:
    vector<Account> accounts;

public:
    void addAccount(string number, string holder, double initialBalance) {
        Account newAccount(number, holder, initialBalance);
        accounts.push_back(newAccount);
        cout << "Account created successfully!" << endl;
    }

    void displayAccounts() {
        if (accounts.empty()) {
            cout << "No accounts found." << endl;
            return;
        }

        cout << "Accounts List:" << endl;
        for (vector<Account>::iterator it = accounts.begin(); it != accounts.end(); ++it) {
            cout << "Account Number: " << it->accountNumber << "\t Account Holder: " << it->accountHolder
                 << "\t Balance: " << it->balance << endl;
        }
    }

    void depositMoney(string accountNumber, double amount) {
        for (vector<Account>::iterator it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->accountNumber == accountNumber) {
                it->balance += amount;
                cout << "Amount deposited successfully!" << endl;
                return;
            }
        }
        cout << "Account not found. Deposit failed." << endl;
    }

    void withdrawMoney(string accountNumber, double amount) {
        for (vector<Account>::iterator it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->accountNumber == accountNumber) {
                if (amount <= it->balance) {
                    it->balance -= amount;
                    cout << "Amount withdrawn successfully!" << endl;
                } else {
                    cout << "Insufficient balance. Withdrawal failed." << endl;
                }
                return;
            }
        }
        cout << "Account not found. Withdrawal failed." << endl;
    }

    void balanceInquiry(string accountNumber) {
        for (vector<Account>::iterator it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->accountNumber == accountNumber) {
                cout << "Account Balance: " << it->balance << endl;
                return;
            }
        }
        cout << "Account not found. Balance inquiry failed." << endl;
    }

    void searchAccount(string accountNumber) {
        for (vector<Account>::iterator it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->accountNumber == accountNumber) {
                cout << "Account found!" << endl;
                cout << "Account Number: " << it->accountNumber << "\t Account Holder: " << it->accountHolder
                     << "\t Balance: " << it->balance << endl;
                return;
            }
        }
        cout << "Account not found." << endl;
    }
};

int main() {
    Bank bank;

    while (true) {
        cout << "\nBank Management System Menu:" << endl;
        cout << "1. Add Account" << endl;
        cout << "2. Display Accounts" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Balance Inquiry" << endl;
        cout << "6. Search Account" << endl;
        cout << "7. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string accountNumber, accountHolder;
                double initialBalance;

                cout << "Enter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Account Holder Name: ";
                cin.ignore();
                getline(cin, accountHolder);
                cout << "Enter Initial Balance: ";
                cin >> initialBalance;

                bank.addAccount(accountNumber, accountHolder, initialBalance);
                break;
            }
            case 2:
                bank.displayAccounts();
                break;
            case 3: {
                string accountNumber;
                double amount;

                cout << "Enter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Amount to Deposit: ";
                cin >> amount;

                bank.depositMoney(accountNumber, amount);
                break;
            }
            case 4: {
                string accountNumber;
                double amount;

                cout << "Enter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Amount to Withdraw: ";
                cin >> amount;

                bank.withdrawMoney(accountNumber, amount);
                break;
            }
            case 5: {
                string accountNumber;
                cout << "Enter Account Number: ";
                cin >> accountNumber;

                bank.balanceInquiry(accountNumber);
                break;
            }
            case 6: {
                string accountNumber;
                cout << "Enter Account Number to Search: ";
                cin >> accountNumber;

                bank.searchAccount(accountNumber);
                break;
            }
            case 7:
                cout << "Exiting the program. Thank you!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    return 0;
}
