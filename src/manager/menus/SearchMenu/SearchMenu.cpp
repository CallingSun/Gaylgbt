#include "../../HotelManager.h"
#include <iostream>
#include <limits>


void HotelManager::searchCustomerByName(const std::string &keyword) const {
    std::cout << "Ket qua tim kiem khach theo ten: " << keyword << "\n";
    
    for (const auto &c : customers) {
        if (c.getName().find(keyword) != std::string::npos) {
            std::cout << c.toCSV() << "\n";
        }
    }
}

void HotelManager::searchRoomById(const std::string &roomId) const {
    for (const auto &r : rooms) {
        if (r.getRoomId() == roomId) {
            std::cout << r.toCSV() << "\n";
            return;
        }
    }

    std::cout << "Khong tim thay phong.\n";
}

void HotelManager::searchInvoiceById(const std::string &invId) const {
    for (const auto &inv : invoices) {
        if (inv.getInvoiceId() == invId) {
            std::cout << inv.toCSV() << "\n";
            return;
        }
    }

    std::cout << "Khong tim thay hoa don.\n";
}

void HotelManager::searchMenu() {
    clearScreen();

    while (true) {
        std::cout << "\n-- TIM KIEM --\n";
        std::cout << "1. Tim khach theo ten\n";
        std::cout << "2. Tim phong theo ma\n";
        std::cout << "3. Tim hoa don theo ma\n";
        std::cout << "0. Quay lai\n";
        std::cout << "Chon: " << std::flush;

        int c;
        if (!(std::cin >> c)) {
            std::cin.clear();
            std::string tmp; std::getline(std::cin,tmp);
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (c == 1) {
            std::string kw;
            std::cout << "Nhap ten/chuoi can tim: " << std::flush;
            std::getline(std::cin, kw);
            searchCustomerByName(kw);
        } 
        
        else if (c == 2) {
            std::string roomId;
            std::cout << "Nhap ma phong: " << std::flush;
            std::getline(std::cin, roomId);
            searchRoomById(roomId);
        } 
        
        else if (c == 3) {
            std::string invId;
            std::cout << "Nhap ma hoa don: " << std::flush;
            std::getline(std::cin, invId);
            searchInvoiceById(invId);
        } 
        
        else if (c == 0) break;
        
        else std::cout << "Noi dung nhap khong hop le.\n";
    }
}

