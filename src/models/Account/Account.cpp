#include "Account.h"
#include <sstream>

Account::Account(const std::string &username,
                const std::string &password,
                int role,
                const std::string &cccd)
    : username(username), password(password), role(role), cccd(cccd) {

}//Hàm tạo tài khoản

std::string Account::getUsername() const {
    return username;
}

void Account::setUsername(const std::string &username) {
    this->username = username;
}

std::string Account::getPassword() const {
    return password;
}

void Account::setPassword(const std::string &password) {
    this->password = password;
}

int Account::getRole() const {
    return role;
}

void Account::setRole(int role) {
    this->role = role;
}

std::string Account::getCccd() const {
    return cccd;
}

void Account::setCccd(const std::string &cccd) {
    this->cccd = cccd;
}

std::string Account::toCSV() const {
    return username + "," + password + "," + std::to_string(role) + "," + cccd;
}

void Account::fromCSV(const std::string &line) {
    std::stringstream ss(line);
    std::string token;

    if (std::getline(ss, token, ',')) {
        username = token;
    }

    if (std::getline(ss, token, ',')) {
        password = token;
    }

    if (std::getline(ss, token, ',')) {
        try {
            role = std::stoi(token);
        } catch (...) {
            role = 2;
        }
    }

    if (std::getline(ss, token, ',')) {
        cccd = token;
    }
}

