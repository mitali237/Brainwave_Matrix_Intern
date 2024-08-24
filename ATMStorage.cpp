#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Customer {
public:
    string name;
    string account_number;
    int balance;
    string pin;
    //Customer Constructor
    Customer(string name, string account_number, int balance, string pin) {
        this->name = name;
        this->account_number = account_number;
        this->balance = balance;
        this->pin = pin;
    }
};

class ATM {
private:
    vector<Customer> customers;

public:
    // Add customers to the ATM system
    void addCustomer(Customer customer) {
        customers.push_back(customer);
    }

    // Verify PIN for a specific account
    Customer* verifyAccount(string account_number, string entered_pin) {
        for (auto& customer : customers) {
            if (customer.account_number == account_number && customer.pin == entered_pin) {
                return &customer;
            }
        }
        return nullptr;
    }

    // Check balance
    void checkBalance(Customer* customer) {
        cout << "Your current balance is: $" << customer->balance << endl;
    }

    // Withdraw cash
    void withdrawCash(Customer* customer, int amount) {
        if (amount > customer->balance) {
            cout << "Insufficient balance!" << endl;
        } else {
            customer->balance -= amount;
            cout << "You have successfully withdrawn $" << amount << endl;
            cout << "Your new balance is: $" << customer->balance << endl;
        }
    }

    // Deposit cash
    void depositCash(Customer* customer, int amount) {
        customer->balance += amount;
        cout << "You have successfully deposited $" << amount << endl;
        cout << "Your new balance is: $" << customer->balance << endl;
    }

    // Change PIN
    void changePIN(Customer* customer, string new_pin) {
        customer->pin = new_pin;
        cout << "Your PIN has been successfully changed." << endl;
    }

    // Account inquiry
    void accountInquiry(Customer* customer) {
        cout << "Account Details:" << endl;
        cout << "Name: " << customer->name << endl;
        cout << "Account Number: " << customer->account_number << endl;
        cout << "Balance: $" << customer->balance << endl;
    }
};

int main() {
    string name;
    string account_number;
    int balance;
    string pin;
    ATM atm;

    // Adding customers to the ATM system
    atm.addCustomer(Customer("Alice", "123456", 5000, "1111"));
    atm.addCustomer(Customer("Bob", "789012", 3000, "2222"));
    atm.addCustomer(Customer("Charlie", "345678", 7000, "3333"));

    string acc_number, entered_pin;
    int choice;

    // Account and PIN verification
    cout << "Welcome to the ATM!" << endl;
    cout << "Please enter your account number: ";
    cin >> acc_number;
    cout << "Please enter your PIN: ";
    cin >> entered_pin;

    Customer* customer = atm.verifyAccount(acc_number, entered_pin);

    if (customer == nullptr) {
        cout << "Incorrect account number or PIN. Exiting..." << endl;
        return 0;
    }

    while(1){
        // Display menu options
        cout << "\nATM Menu:" << endl;
        cout << "1. Check Balance" << endl;
        cout << "2. Withdraw Cash" << endl;
        cout << "3. Deposit Cash" << endl;
        cout << "4. Change PIN" << endl;
        cout << "5. Account Inquiry" << endl; 
        cout << "6. New Customer" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            atm.checkBalance(customer);
            break;
        case 2: {
            int withdraw_amount;
            cout << "Enter amount to withdraw: $";
            cin >> withdraw_amount;
            atm.withdrawCash(customer, withdraw_amount);
            break;
        }
        case 3: {
            int deposit_amount;
            cout << "Enter amount to deposit: $";
            cin >> deposit_amount;
            atm.depositCash(customer, deposit_amount);
            break;
        }
        case 4: {
            string new_pin;
            cout << "Enter your new PIN: ";
            cin >> new_pin;
            atm.changePIN(customer, new_pin);
            break;
        }
        case 5:
            atm.accountInquiry(customer);
            break;
        case 6: {
            cout << "Enter name\n";
            cin.ignore();
            // To use space in string
            getline(cin, name);
            cout << "Enter Account number\n";
            cin >> account_number;
            cout << "Enter Balance\n";
            cin >> balance;
            cout << "Enter Pin\n";
            cin >> pin;
            Customer newCustomer(name, account_number, balance, pin);
            atm.addCustomer(newCustomer);
    
            // Now set the customer pointer to the newly added customer
            customer = atm.verifyAccount(account_number, pin);

            cout << "New customer added and logged in." << endl;
            break;
        }
        case 7:
            cout << "Thank you for using the ATM. Goodbye!" << endl;
            exit(1);
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}