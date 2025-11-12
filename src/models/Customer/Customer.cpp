#include "Customer.h"
#include <sstream>

Customer::Customer(const std::string &cccd, const std::string &name,
                const std::string &phone,
                const std::string &email,
                const std::string &birthdate,
                const std::string &address)
    : Person(cccd, name, phone, email),
    birthdate(birthdate),
    address(address) {

    }//Hàm tạo khách hàng

std::string Customer::getBirthdate() const {
    return birthdate;
}

void Customer::setBirthdate(const std::string &date) {
    birthdate = date;
}

std::string Customer::getAddress() const {
    return address;
}

void Customer::setAddress(const std::string &addr) {
    address = addr;
}

std::string Customer::toCSV() const {
    std::ostringstream oss;
    
    oss << cccd << "," << name << "," << phone << "," << email << "," << birthdate << "," << address;
    return oss.str();
}

void Customer::fromCSV(const std::string &line) {
    std::stringstream ss(line);
    std::getline(ss, cccd, ',');
    std::getline(ss, name, ',');
    std::getline(ss, phone, ',');
    std::getline(ss, email, ',');
    std::getline(ss, birthdate, ',');
    std::getline(ss, address, ',');
}
