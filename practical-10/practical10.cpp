#include <iostream>
#include <stdexcept>
#include <string>

/**
 * Custom Exception Hierarchy derived from std::exception:
 *  - BankingException (Base class for all domain-specific banking errors)
 *      ├── InvalidAmount (Thrown when transaction amount <= 0)
 *      └── InsufficientFunds (Thrown when withdrawal amount > current balance)
 */
class BankingException : public std::exception {
protected:
    std::string message_;

public:
    explicit BankingException(std::string message)
        : message_(std::move(message)) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }
};

class InvalidAmount : public BankingException {
public:
    explicit InvalidAmount(const std::string& message = "Error: Invalid Amount!")
        : BankingException(message) {}
};

class InsufficientFunds : public BankingException {
public:
    explicit InsufficientFunds(const std::string& message = "Error: Insufficient Funds!")
        : BankingException(message) {}
};

class BankAccount {
private:
    std::string accountHolder_;
    double balance_;

public:
    BankAccount(std::string accountHolder, double initialBalance)
        : accountHolder_(std::move(accountHolder)), balance_(initialBalance) {}

    double getBalance() const {
        return balance_;
    }

    const std::string& getAccountHolder() const {
        return accountHolder_;
    }

    // Strong exception guarantee: if validation throws, `balance_` remains unchanged.
    void withdraw(double amount) {
        std::cout << "Withdrawal Amount: Rs. " << amount << "\n";
        if (amount <= 0.0) {
            throw InvalidAmount("Error: Invalid Amount!");
        }
        if (amount > balance_) {
            throw InsufficientFunds("Error: Insufficient Funds!");
        }
        balance_ -= amount;
        std::cout << "Transaction Successful!\n";
        std::cout << "Remaining Balance: Rs. " << balance_ << "\n";
    }
};

int main() {
    std::cout << "----- BANKING TRANSACTION SYSTEM -----\n";
    std::cout << "Student Name: Satinderpal Singh Chaney\n";
    std::cout << "Roll Number: E26B00S2034\n";

    BankAccount account("Satinderpal Singh Chaney", 10000);
    std::cout << "Account Holder: " << account.getAccountHolder() << "\n";
    std::cout << "Initial Balance: Rs. " << account.getBalance() << "\n";

    // 1. Successful Transaction
    std::cout << "----- SUCCESSFUL TRANSACTION -----\n";
    try {
        account.withdraw(2000);
    } catch (const InvalidAmount& e) {
        std::cout << e.what() << "\nTransaction Failed!\nBalance: Rs. " << account.getBalance() << "\n";
    } catch (const InsufficientFunds& e) {
        std::cout << e.what() << "\nTransaction Failed!\nBalance: Rs. " << account.getBalance() << "\n";
    }

    // 2. Failed Transaction: Insufficient Funds
    std::cout << "----- INSUFFICIENT FUNDS -----\n";
    try {
        account.withdraw(12000);
    } catch (const InvalidAmount& e) {
        std::cout << e.what() << "\nTransaction Failed!\nBalance: Rs. " << account.getBalance() << "\n";
    } catch (const InsufficientFunds& e) {
        std::cout << e.what() << "\nTransaction Failed!\nBalance: Rs. " << account.getBalance() << "\n";
    }

    // 3. Failed Transaction: Invalid Amount
    std::cout << "----- INVALID AMOUNT -----\n";
    try {
        account.withdraw(-500);
    } catch (const InvalidAmount& e) {
        std::cout << e.what() << "\nTransaction Failed!\nBalance: Rs. " << account.getBalance() << "\n";
    } catch (const InsufficientFunds& e) {
        std::cout << e.what() << "\nTransaction Failed!\nBalance: Rs. " << account.getBalance() << "\n";
    }

    std::cout << "Custom Exception Handling Demonstrated Successfully!\n";
    std::cout << "Program executed successfully.\n";

    return 0;
}
