#include "../../HotelManager.h"
#include <iostream>
#include <limits>
#include <algorithm>


void HotelManager::addEmployeeInteractive() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string cccd, name, phone, email, pos, salStr;

    double sal = 0.0;

    std::cout << "Nhap CCCD nhan vien: " << std::flush;

    std::getline(std::cin, cccd);

    if (findEmployeeByCccd(cccd)) {
        std::cout << "Nhan vien da ton tai.\n";
        return;
    }

    std::cout << "Nhap ten: " << std::flush;

    std::getline(std::cin, name);

    std::cout << "Nhap so dien thoai: " << std::flush;

    std::getline(std::cin, phone);

    std::cout << "Nhap email: " << std::flush;

    std::getline(std::cin, email);

    std::cout << "Nhap vi tri: " << std::flush;

    std::getline(std::cin, pos);

    std::cout << "Nhap luong: " << std::flush;

    std::getline(std::cin, salStr);

    try { sal = std::stod(salStr); } catch (...) { sal = 0.0; }

    Employee e(cccd, name, phone, email, pos, sal);
    
    employees.push_back(e);
    
    saveEmployees();
    
    std::cout << "Them nhan vien thanh cong.\n";
}

void HotelManager::listEmployees() const {
    std::cout << "---- DANH SACH NHAN VIEN ----\n";
    
    for (const auto &e : employees) {
        std::cout << e.toCSV() << "\n";
    }

}

void HotelManager::deleteEmployeeByCccd(const std::string &cccd) {
    auto it = std::remove_if(employees.begin(), employees.end(), [&](const Employee &e){
        return e.getCccd() == cccd; 
        }
    );
    if (it != employees.end()) {
        employees.erase(it, employees.end());
        
        saveEmployees();
        
        std::cout << "Da xoa nhan vien.\n";
    } 
    else {
        std::cout << "Khong tim thay nhan vien can xoa.\n";
    }
}

void HotelManager::employeeMenu() {
    clearScreen();
    
    while (true) {
        std::cout << "\n-- QUAN LY NHAN VIEN --\n";
        std::cout << "1. Them nhan vien\n";
        std::cout << "2. Liet ke nhan vien\n";
        std::cout << "3. Xoa nhan vien\n";
        std::cout << "0. Quay lai\n";
        std::cout << "Chon: " << std::flush;
    
        int c;
        if (!(std::cin >> c)) {
            std::cin.clear();
    
            std::string tmp; std::getline(std::cin,tmp);
            continue;
        }

        if (c == 1) {
            addEmployeeInteractive();
        }

        else if (c == 2) listEmployees();
        else if (c == 3) {
            std::cout << "Nhap CCCD can xoa: " << std::flush;
            
            std::string cccd;
            std::cin >> cccd;

            deleteEmployeeByCccd(cccd);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        else if (c == 0) break;
        
        else std::cout << "Noi dung nhap khong hop le.\n";
    }
}

