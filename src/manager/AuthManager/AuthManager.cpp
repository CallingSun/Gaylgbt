#include "AuthManager.h"
#include <fstream>
#include <iostream>

AuthManager::AuthManager(const std::string &dataDir) : dataDir(dataDir) {
    loadAccounts();
}

void AuthManager::loadAccounts() {
    accounts.clear();
    std::ifstream file(dataDir + "/accounts.txt");
    
    if (!file.is_open()) {
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            Account acc;
            acc.fromCSV(line);
            accounts.push_back(acc);
        }
    }
    
    file.close();
}

void AuthManager::saveAccounts() {
    std::ofstream file(dataDir + "/accounts.txt");
    
    if (!file.is_open()) {
        std::cerr << "Cannot open accounts.txt for writing\n";
        return;
    }
    
    for (const auto &acc : accounts) {
        file << acc.toCSV() << "\n";
    }
    
    file.close();
}

bool AuthManager::login(const std::string &username, const std::string &password, int &role, std::string &cccd) {
    for (const auto &acc : accounts) {
        if (acc.getUsername() == username && acc.getPassword() == password) {
            role = acc.getRole();
            cccd = acc.getCccd();
            return true;
        }
    }
    return false;
}

bool AuthManager::registerCustomer(const std::string &username, const std::string &password, const std::string &cccd, int role) {
    if (accountExists(username)) {
        return false;
    }

    Account newAcc(username, password, role, cccd);
    accounts.push_back(newAcc);
    saveAccounts();
    return true;
}

bool AuthManager::changePassword(const std::string &username, const std::string &oldPassword, const std::string &newPassword) {
    for (auto &acc : accounts) {
        if (acc.getUsername() == username && acc.getPassword() == oldPassword) {
            acc.setPassword(newPassword);
            saveAccounts();
            return true;
        }
    }
    return false;
}

bool AuthManager::forgotPassword(const std::string &username, const std::string &cccd) {
    for (auto &acc : accounts) {
        if (acc.getUsername() == username && acc.getCccd() == cccd) {
            acc.setPassword(username);
            saveAccounts();
            return true;
        }
    }
    return false;
}

bool AuthManager::promoteToStaff(const std::string &username) {
    for (auto &acc : accounts) {
        if (acc.getUsername() == username && acc.getRole() == 2) {
            acc.setRole(1);
            saveAccounts();
            return true;
        }
    }
    return false;
}

Account* AuthManager::findAccountByUsername(const std::string &username) {
    for (auto &acc : accounts) {
        if (acc.getUsername() == username) {
            return &acc;
        }
    }
    return nullptr;
}

bool AuthManager::accountExists(const std::string &username) const {
    for (const auto &acc : accounts) {
        if (acc.getUsername() == username) {
            return true;
        }
    }
    return false;
}

std::vector<Account> AuthManager::getCustomerAccounts() const {
    std::vector<Account> customers;
    for (const auto &acc : accounts) {
        if (acc.getRole() == 2) {
            customers.push_back(acc);
        }
    }
    return customers;
}

