#include "../../HotelManager.h"
#include <iostream>
#include <limits>
#include <algorithm>

void HotelManager::addCustomerInteractive() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::string cccd, name, phone, email, dob, addr;

    std::cout << "Nhap CCCD khach: " << std::flush;
    
    std::getline(std::cin, cccd);

    if (customerExists(cccd)) {
        std::cout << "Khach voi CCCD nay da ton tai.\n";
        return;
    }

    std::cout << "Nhap ten: " << std::flush;
    
    std::getline(std::cin, name);

    std::cout << "Nhap so dien thoai: " << std::flush;
    
    std::getline(std::cin, phone);

    std::cout << "Nhap email: " << std::flush;
    
    std::getline(std::cin, email);

    std::cout << "Nhap ngay sinh (YYYY-MM-DD): " << std::flush;
    
    std::getline(std::cin, dob);

    std::cout << "Nhap dia chi: " << std::flush;
    
    std::getline(std::cin, addr);

    Customer c(cccd, name, phone, email, dob, addr);
    
    customers.push_back(c);
    
    saveCustomers();
    
    std::cout << "Them khach thanh cong.\n";
}

void HotelManager::listCustomers() const {
    std::cout << "---- DANH SACH KHACH HANG ----\n";
    
    for (const auto &c : customers) {
        std::cout << c.toCSV() << "\n";
    }

}

void HotelManager::deleteCustomerByCccd(const std::string &cccd) {
    auto it = std::remove_if(customers.begin(), customers.end(), [&](const Customer &c){
        return c.getCccd() == cccd; 
        }
    );

    if (it != customers.end()) {
        customers.erase(it, customers.end());
        
        saveCustomers();
        
        std::cout << "Da xoa khach hang!.\n";
    } 
    else {
        std::cout << "Khong tim thay khach hang.\n";
    }
}

void HotelManager::customerMenu() {
    clearScreen();
    
    while (true) {
        std::cout << "\n-- QUAN LY KHACH HANG --\n";
        std::cout << "1. Them khach\n";
        std::cout << "2. Liet ke khach\n";
        std::cout << "3. Xoa khach theo CCCD\n";
        std::cout << "0. Quay lai\n";
        std::cout << "Chon: " << std::flush;
        int c;
        if (!(std::cin >> c)) {
            std::cin.clear();
            
            std::string tmp; std::getline(std::cin,tmp);
            
            continue;
        }
        if (c == 1) {
            addCustomerInteractive();
        }
        else if (c == 2) listCustomers();
        else if (c == 3) {
            std::cout << "Nhap CCCD can xoa: " << std::flush;
            
            std::string cccd;
            
            std::cin >> cccd;
            
            deleteCustomerByCccd(cccd);
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (c == 0) break;
        else std::cout << "Noi dung nhap khong hop le.\n";
    }
}

