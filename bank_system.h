#pragma once
#ifndef BANK_SYSTEM_H
#define BANK_SYSTEM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <sstream>
#include <cctype>
#include <locale>

using namespace std;

// Trim from start (in place)
static inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
}

// Trim from end (in place)
static inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

// Trim from both ends (in place)
static inline void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}

class User {
private:
    string username;
    string password;
    string companyName;
    string accountNo;
    string firstName;
    string lastName;
    string email;
    double balance;
    double loan;
    bool isFrozen = false;

public:
    User(const string& user = "", const string& pass = "", const string& company = "", const string& first = "", const string& last = "", const string& mail = "", double bal = 0.0, double ln = 0.0, const string& accNumber = "")
        : username(user), password(pass), companyName(company), firstName(first), lastName(last), email(mail), balance(bal), loan(ln), accountNo(accNumber) {}

    string getUsername() const { return username; }
    string getAccountNo() const { return accountNo; }
    string getPassword() const { return password; }
    bool checkPassword(const string& pass) const { return password == pass; }
    string getCompanyName() const { return companyName; }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getEmail() const { return email; }
    double getBalance() const { return balance; }
    double getLoan() const { return loan; }
    bool getIsFrozen() const { return isFrozen; }

    void setPassword(const string& newPassword) { password = newPassword; }
    void setCompanyName(const string& c) { companyName = c; }
    void setFirstName(const string& f) { firstName = f; }
    void setLastName(const string& l) { lastName = l; }
    void setEmail(const string& e) { email = e; }
    void setBalance(double bal) { balance = bal; }
    void setLoan(double ln) { loan = ln; }
    void setIsFrozen(bool frozen) { isFrozen = frozen; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }
    bool withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }
    bool transfer(double amount, User& recipient) {
        if (withdraw(amount)) {
            recipient.deposit(amount);
            return true;
        }
        return false;
    }

    void takeLoan(double amount) { loan += amount; balance += amount; }
    bool repayLoan(double amount) {
        if (amount > balance) return false;
        loan -= amount;
        balance -= amount;
        return true;
    }

    friend bool saveUser(ofstream& ofs, const User& user);
    friend bool loadUser(istream& is, User& user);

    void display() const {
        cout << "Username: " << username << "\nCompany: " << companyName << "\nName: " << firstName << " " << lastName << "\nEmail: " << email << "\nBalance: " << balance << "\nLoan: " << loan << "\nFrozen: " << (isFrozen ? "Yes" : "No") << endl;
    }
};

bool saveUser(ofstream& ofs, const User& user) {
    ofs << user.username << ' ' << user.password << ' ' << user.companyName << ' ' << user.firstName << ' ' << user.lastName << ' ' << user.email << ' ' << user.balance << ' ' << user.loan << ' ' << user.accountNo << ' ' << user.isFrozen << '\n';
    return ofs.good();
}

bool loadUser(istream& is, User& user) {
    is >> user.username >> user.password >> user.companyName >> user.firstName >> user.lastName >> user.email >> user.balance >> user.loan >> user.accountNo >> user.isFrozen;
    return is.good();
}

class Admin {
private:
    string adminUsername;
    string adminPassword;

public:
    Admin(const string& user = "", const string& pass = "")
        : adminUsername(user), adminPassword(pass) {}

    string getAdminUsername() const { return adminUsername; }

    bool login(const string& user, const string& pass) const {
        return adminUsername == user && adminPassword == pass;
    }

    void changeCredentials(const string& newUsername, const string& newPassword) {
        adminUsername = newUsername;
        adminPassword = newPassword;
    }
};

class BankSystem {
private:
    vector<User> users;
    Admin admin;
    const string loginFile = "login.txt";
    const string userDataFile = "user_data.txt";

    string generateAccountNumber() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 9);
        string accountNumber;
        for (int i = 0; i < 16; ++i) {
            accountNumber += to_string(dis(gen));
        }
        return accountNumber;
    }

public:
    BankSystem(const string& adminUser, const string& adminPass)
        : admin(adminUser, adminPass) {
        users = loadUsersFromFile();
    }

    BankSystem() {
        users = loadUsersFromFile();
    }

    ~BankSystem() {
        saveUsersToFile(users);
    }
    bool deleteAccount(const string& username, const string& password) {
        auto it = find_if(users.begin(), users.end(), [&username, &password](const User& u) { return u.getUsername() == username && u.checkPassword(password); });

        if (it != users.end()) {
            users.erase(it);
            saveUsersToFile(users);
            cout << "Account deleted successfully!\n";
            return true;
        }
        else {
            cout << "Error: Username or password incorrect!\n";
            return false;
        }
    }
    bool changeCredentials(const string& newUsername, const string& newPassword) {
        admin.changeCredentials(newUsername, newPassword);
        cout << "Admin credentials updated successfully!\n";
        return true;
    }
    bool authenticateUserFromFile(const std::string& username, const std::string& password) {
        // Open the file containing login information
        std::ifstream file("login.txt");
        if (!file.is_open()) {
            throw std::runtime_error("Error opening login file.");
        }

        // Read each line in the file
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string storedUsername, storedPassword;
            if (iss >> storedUsername >> storedPassword) {
                // Check if the username and password match
                if (storedUsername == username && storedPassword == password) {
                    // Credentials match, return true
                    file.close();
                    return true;
                }
            }
        }

        // No matching user found, return false
        file.close();
        return false;
    }
    double checkBalance(const std::string& username) {
        // Open the file containing user information
        std::ifstream file("login.txt");
        if (!file.is_open()) {
            throw std::runtime_error("Error opening user data file.");
        }

        // Read each line in the file
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string storedUsername, storedPassword;
            double balance;
            if (iss >> storedUsername >> storedPassword >> balance) {
                // Check if the username matches
                if (storedUsername == username) {
                    // Close the file and return the balance
                    file.close();
                    return balance;
                }
            }
        }

        // No matching user found, throw an exception
        file.close();
        throw std::invalid_argument("Invalid username.");
    }

    bool addUser(const string& user, const string& pass, const string& company, const string& first, const string& last, const string& mail, double bal, double ln) {
        string accountNumber = generateAccountNumber();
        User newUser(user, pass, company, first, last, mail, bal, ln, accountNumber);
        users.push_back(newUser);
        return saveUsersToFile(users);
    }

    bool loginUser(const string& username, const string& password) {
        for (const User& user : users) {
            if (user.getUsername() == username && user.checkPassword(password)) {
                return true;
            }
        }
        return false;
    }

    User* getUserByUsername(const string& username) {
        auto it = find_if(users.begin(), users.end(), [&username](const User& u) { return u.getUsername() == username; });
        if (it != users.end()) {
            return &(*it);
        }
        cout << "Error: User not found!\n";
        return nullptr;
    }

    User* getUserByAccountNumber(const string& accountNo) {
        auto it = find_if(users.begin(), users.end(), [&accountNo](const User& u) { return u.getAccountNo() == accountNo; });
        if (it != users.end()) {
            return &(*it);
        }
        cout << "Error: Account not found!\n";
        return nullptr;
    }

    bool transferMoney(const string& senderUsername, const string& receiverUsername, double amount) {
        User* sender = getUserByUsername(senderUsername);
        User* receiver = getUserByUsername(receiverUsername);

        if (!sender || !receiver) {
            cout << "Error: Sender or receiver not found!\n";
            return false;
        }

        if (sender->getBalance() < amount) {
            cout << "Error: Insufficient balance!\n";
            return false;
        }

        if (sender->transfer(amount, *receiver)) {
            saveUsersToFile(users);
            cout << "Money transferred successfully!\n";
            return true;
        }
        return false;
    }

    bool freezeAccount(const string& accountNo) {
        User* user = getUserByAccountNumber(accountNo);
        if (!user) {
            cout << "Error: Account not found!\n";
            return false;
        }
        user->setIsFrozen(true);
        return saveUsersToFile(users);
    }

    bool unfreezeAccount(const string& accountNo) {
        User* user = getUserByAccountNumber(accountNo);
        if (!user) {
            cout << "Error: Account not found!\n";
            return false;
        }
        user->setIsFrozen(false);
        return saveUsersToFile(users);
    }

    bool deposit(const string& accountNo, double amount) {
        User* user = getUserByAccountNumber(accountNo);
        if (!user) {
            cout << "Error: Account not found!\n";
            return false;
        }
        user->deposit(amount);
        return saveUsersToFile(users);
    }

    bool withdraw(const string& accountNo, double amount) {
        User* user = getUserByAccountNumber(accountNo);
        if (!user) {
            cout << "Error: Account not found!\n";
            return false;
        }
        if (!user->withdraw(amount)) {
            cout << "Error: Insufficient balance!\n";
            return false;
        }
        return saveUsersToFile(users);
    }

    bool saveUsersToFile(const vector<User>& users) {
        ofstream file(loginFile);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file for saving users.\n";
            return false;
        }

        for (const User& user : users) {
            if (!saveUser(file, user)) {
                cerr << "Error: Unable to save user data.\n";
                return false;
            }
        }
        file.close();
        return true;
    }

    vector<User> loadUsersFromFile() {
        vector<User> users;
        ifstream file(loginFile);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file for loading users.\n";
            return users;
        }

        User user;
        while (loadUser(file, user)) {
            users.push_back(user);
        }
        file.close();
        return users;
    }

    bool AdminLogin(const string& username, const string& password) {
        ifstream AdminloginFile("Adminlogin.txt");
        string fileUsername, filePassword;

        if (!AdminloginFile.is_open()) {
            cerr << "Error: Unable to open login file." << endl;
            return false;
        }

        cout << "Reading from file..." << endl; // Debug message

        while (AdminloginFile >> fileUsername >> filePassword) {
            // Trim whitespace from file data
            trim(fileUsername);
            trim(filePassword);

            cout << "Read username: '" << fileUsername << "', password: '" << filePassword << "'" << endl; // Debug message

            // Trim whitespace from input data
            string trimmedUsername = username;
            string trimmedPassword = password;
            trim(trimmedUsername);
            trim(trimmedPassword);

            cout << "Comparing with input username: '" << trimmedUsername << "', password: '" << trimmedPassword << "'" << endl; // Debug message

            if (fileUsername == trimmedUsername && filePassword == trimmedPassword) {
                AdminloginFile.close();
                return true;
            }
        }

        AdminloginFile.close();
        cout << "No matching credentials found." << endl; // Debug message
        return false;
    }
};

#endif // BANK_SYSTEM_H
