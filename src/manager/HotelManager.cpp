#include "HotelManager.h"
#include "utils/StringUtils/StringUtils.h"//Gọi các utils đề thực hiện tính toán
#include "utils/DateUtils/DateUtils.h"

#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <cstdlib>

HotelManager::HotelManager(const std::string &dataDir)
    : dataDir(dataDir) {
    loadAll();
}

void HotelManager::loadAll() {
    loadCustomers();
    loadEmployees();
    loadRooms();
    loadInvoices();
}

void HotelManager::saveAll() {
    saveCustomers();
    saveEmployees();
    saveRooms();
    saveInvoices();
}

void HotelManager::clearScreen() {
    #ifdef _WIN32
        system("cls");//nếu là win 32 thì thực hiện lệnh cls còn không thì lệnh dưới
    #else
        system("clear");
    #endif
}

void HotelManager::loadCustomers() {
    customers.clear();

    std::ifstream ifs(dataDir + "/customers.txt");
    
    if (!ifs) return;
    
    std::string line;
    
    while (std::getline(ifs, line)) {
        line = trim(line);
        if (line.empty()) continue;
        Customer c;
        c.fromCSV(line);
        customers.push_back(c);
    }
}

void HotelManager::saveCustomers() {
    std::ofstream ofs(dataDir + "/customers.txt");
    
    for (const auto &c : customers) {
        ofs << c.toCSV() << "\n";
    }
}

void HotelManager::loadEmployees() {
    employees.clear();
    
    std::ifstream ifs(dataDir + "/employees.txt");

    if (!ifs) return;

    std::string line;

    while (std::getline(ifs, line)) {
        line = trim(line);
        if (line.empty()) continue;
        Employee e;
        e.fromCSV(line);
        employees.push_back(e);
    }
}

void HotelManager::saveEmployees() {
    std::ofstream ofs(dataDir + "/employees.txt");

    for (const auto &e : employees) {
        ofs << e.toCSV() << "\n";
    }
}

void HotelManager::loadRooms() {
    rooms.clear();

    std::ifstream ifs(dataDir + "/rooms.txt");

    if (!ifs) return;
    
    std::string line;
    
    while (std::getline(ifs, line)) {
        line = trim(line);
        if (line.empty()) continue;
        Room r;
        r.fromCSV(line);
        rooms.push_back(r);
    }
}

void HotelManager::saveRooms() {
    std::ofstream ofs(dataDir + "/rooms.txt");
    
    for (const auto &r : rooms) {
        ofs << r.toCSV() << "\n";
    }
}

void HotelManager::loadInvoices() {
    invoices.clear();
    
    std::ifstream ifs(dataDir + "/invoices.txt");
    
    if (!ifs) return;
    
    std::string line;
    
    while (std::getline(ifs, line)) {
        line = trim(line);
        if (line.empty()) continue;
        Invoice inv;
        inv.fromCSV(line);
        invoices.push_back(inv);
    }
}

void HotelManager::saveInvoices() {
    std::ofstream ofs(dataDir + "/invoices.txt");
    
    for (const auto &inv : invoices) {
        ofs << inv.toCSV() << "\n";
    }
}



Customer* HotelManager::findCustomerByCccd(const std::string &cccd) {
    for (auto &c : customers) {
        if (c.getCccd() == cccd) return &c;
    }
    
    return nullptr;
}

Employee* HotelManager::findEmployeeByCccd(const std::string &cccd) {
    for (auto &e : employees) {
        if (e.getCccd() == cccd) return &e;
    }

    return nullptr;
}

Room* HotelManager::findRoomById(const std::string &roomId) {
    for (auto &r : rooms) {
        if (r.getRoomId() == roomId) return &r;
    }

    return nullptr;
}

Invoice* HotelManager::findInvoiceById(const std::string &invId) {
    for (auto &inv : invoices) {
        if (inv.getInvoiceId() == invId) return &inv;
    }

    return nullptr;
}

bool HotelManager::customerExists(const std::string &cccd) const {
    for (const auto &c : customers) {
        if (c.getCccd() == cccd) return true;
    }

    return false;
}

//Console

void HotelManager::runConsole() {
    clearScreen();

    while (true) {
        std::cout << "\n=== Quan Li Hotel Mini===\n";
        std::cout << "1. Quan ly khach hang\n";
        std::cout << "2. Quan ly nhan vien\n";
        std::cout << "3. Quan ly phong\n";
        std::cout << "4. Quan ly hoa don\n";
        std::cout << "5. Tim kiem\n";
        std::cout << "6. Thong ke\n";
        std::cout << "0. Luu & Thoat\n";
        std::cout << "Chon: " << std::flush;
    
        int c;
        if (!(std::cin >> c)) {
            std::cin.clear();
            std::string tmp; std::getline(std::cin, tmp);
            continue;
        }

        switch (c) {
            case 1: 
            customerMenu(); 
            break;

            case 2: 
            employeeMenu(); 
            break;

            case 3: 
            roomMenu(); 
            break;

            case 4: 
            invoiceMenu(); 
            break;

            case 5: 
            searchMenu(); 
            break;

            case 6: 
            statsMenu(); 
            break;

            case 0:
            saveAll();
            std::cout << "Cam on da su dung dich vu!\n";
            return;

            default:
            std::cout << "Noi dung nhap khong hop le vui long nhap lai.\n";
        }
    }
}
