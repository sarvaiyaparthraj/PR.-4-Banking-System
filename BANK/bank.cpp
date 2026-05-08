#include <iostream>
using namespace std;

class BankAccount{
protected:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(int no, string name, double bal){
        accountNumber = no;
        accountHolderName = name;
        balance = bal;
    }

    virtual void deposit(double amount){
        balance += amount;
        cout << "Amount Deposited Successfully.\n";
    }

    virtual void withdraw(double amount){
        if (amount <= balance){
            balance -= amount;
            cout << "Amount Withdrawn Successfully.\n";
        }
        else{
            cout << "Insufficient Balance!\n";
        }
    }

    double getBalance(){
        return balance;
    }

    virtual void calculateInterest(){}

    virtual void displayAccountInfo(){
        cout << "\nAccount Number : " << accountNumber << endl;
        cout << "Holder Name      : " << accountHolderName << endl;
        cout << "Balance          : " << balance << endl;
    }

    virtual ~BankAccount() {}
};

class SavingsAccount : public BankAccount{
    double interestRate;

public:
    SavingsAccount(int no, string name, double bal, double rate)
        : BankAccount(no, name, bal){
        interestRate = rate;
    }

    void calculateInterest() override{
        double interest = balance * interestRate / 100;
        balance += interest;
        cout << "Savings Interest Added: " << interest << endl;
    }
};

class CheckingAccount : public BankAccount{
    double overdraftLimit;

public:
    CheckingAccount(int no, string name, double bal, double limit)
        : BankAccount(no, name, bal){
        overdraftLimit = limit;
    }

    void withdraw(double amount) override{
        if (amount <= balance + overdraftLimit){
            balance -= amount;
            cout << "Amount Withdrawn.\n";
        }
        else{
            cout << "Overdraft Limit Exceeded!\n";
        }
    }
};

class FixedDepositAccount : public BankAccount{
    int term;

public:
    FixedDepositAccount(int no, string name, double bal, int t)
        : BankAccount(no, name, bal){
        term = t;
    }

    void calculateInterest() override{
        double rate = 6.5;
        double interest = balance * rate * term / 100;
        balance += interest;
        cout << "FD Interest Added: " << interest << endl;
    }
};

int main(){
    BankAccount *acc = nullptr;
    int choice;

    do{
        cout << "\n----- BANK MENU -----" << endl;
        cout << "1. Create Savings Account" << endl;
        cout << "2. Create Checking Account" << endl;
        cout << "3. Create Fixed Deposit Account" << endl;
        cout << "4. Deposit" << endl;
        cout << "5. Withdraw" << endl;
        cout << "6. Calculate Interest" << endl;
        cout << "7. Display Account Info" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        int no, term;
        string name;
        double bal, rate, limit, amount;

       if (choice == 1) {
            cout << "Enter Account Number: ";
            cin >> no;
            cin.ignore();

            cout << "Enter Holder Name: ";
            cin >> name;

            cout << "Enter Initial Balance: ";
            cin >> bal;
            cin.ignore();

            cout << "Enter Interest Rate: ";
            cin >> rate;
            cin.ignore();

            acc = new SavingsAccount(no, name, bal, rate);
            cout << "Savings Account Created.\n";
        }
        else if (choice == 2) {
            cout << "Enter Account Number: ";
            cin >> no;
            cin.ignore();

            cout << "Enter Holder Name: ";
            cin >> name;
            cout << "Enter Initial Balance: ";
            cin >> bal;
            cin.ignore();

            cout << "Enter Overdraft Limit: ";
            cin >> limit;
            cin.ignore();

            acc = new CheckingAccount(no, name, bal, limit);
            cout << "Checking Account Created.\n";
        }
        else if (choice == 3) {
            cout << "Enter Account Number: ";
            cin >> no;
            cin.ignore();

            cout << "Enter Holder Name: ";
            cin >> name;
            cout << "Enter Initial Balance: ";
            cin >> bal;
            cin.ignore();

            cout << "Enter Term (Years): ";
            cin >> term;
            cin.ignore();

            acc = new FixedDepositAccount(no, name, bal, term);
            cout << "Fixed Deposit Account Created.\n";
        }
        else if (choice == 4) {
            if (acc) {
                cout << "Enter Amount: ";
                cin >> amount;
                acc->deposit(amount);
            } else {
                cout << "Create Account First!\n";
            }
        }
        else if (choice == 5) {
            if (acc) {
                cout << "Enter Amount: ";
                cin >> amount;
                acc->withdraw(amount);
            } else {
                cout << "Create Account First!\n";
            }
        }
        else if (choice == 6) {
            if (acc)
                acc->calculateInterest();
            else
                cout << "Create Account First!\n";
        }
        else if (choice == 7) {
            if (acc)
                acc->displayAccountInfo();
            else
                cout << "Create Account First!\n";
        }

    } while (choice != 0);

    return 0;
}