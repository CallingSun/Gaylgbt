#include "Person.h"

Person::Person(const std::string &cccd,
            const std::string &name,
            const std::string &phone,
            const std::string &email)
    : cccd(cccd), name(name), phone(phone), email(email) {
        
    };

std::string Person::getCccd() const {
    return cccd; 
};

std::string Person::getName() const {
    return name; 
};

std::string Person::getPhone() const {
    return phone; 
};

std::string Person::getEmail() const {
    return email; 
};

void Person::setName(const std::string &name) {
    this->name = name; 
};

void Person::setPhone(const std::string &phone) {
    this->phone = phone; 
};

void Person::setEmail(const std::string &email) {
    this->email = email; 
};
