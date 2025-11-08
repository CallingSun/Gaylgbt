#include "Employee.h"
#include <sstream>
#include <limits>
#include <fstream>

Employee::Employee(const std::string &cccd,
                const std::string &name,
                const std::string &phone,
                const std::string &email,
                const std::string &position,
                double salary)
    : Person(cccd, name, phone, email),
    position(position),
    salary(salary) {

    }//Hàm tạo nhân viên

std::string Employee::getPosition() const {
    return position; 
}

double Employee::getSalary() const {
    return salary; 
}

std::string Employee::toCSV() const {
    std::ostringstream oss;
    
    oss << cccd << "," << name << "," << phone << "," << email << ","
        << position << "," << salary;
    return oss.str();
}

void Employee::fromCSV(const std::string &line) {
    std::stringstream ss(line);
    std::string salaryStr;
    std::getline(ss, cccd, ',');
    std::getline(ss, name, ',');
    std::getline(ss, phone, ',');
    std::getline(ss, email, ',');
    std::getline(ss, position, ',');
    std::getline(ss, salaryStr, ',');
    
    try {
        salary = std::stod(salaryStr);
    } 
    catch (...) {
        salary = 0.0;
    }
}
