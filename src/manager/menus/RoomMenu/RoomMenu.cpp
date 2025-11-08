#include "../../HotelManager.h"
#include <iostream>
#include <limits>
#include <algorithm>


void HotelManager::addRoomInteractive() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string roomId, type, priceStr;
    double price = 0.0;

    std::cout << "Nhap ma phong: " << std::flush;
    std::getline(std::cin, roomId);

    if (findRoomById(roomId)) {
        std::cout << "Phong da ton tai.\n";
        return;
    }

    std::cout << "Nhap loai phong (Single/Double/Family): " << std::flush;
    std::getline(std::cin, type);

    std::cout << "Nhap gia/phong/dem: " << std::flush;
    std::getline(std::cin, priceStr);
    try { price = std::stod(priceStr); } catch(...) { price = 0.0; }

    Room r(roomId, type, price, true);
    rooms.push_back(r);
    saveRooms();
    std::cout << "Them phong thanh cong.\n";
}

void HotelManager::listRooms() const {
    std::cout << "------ DANH SACH PHONG ------\n";
    std::cout << "0=Phong dang su dung, 1=Phong trong\n";
    
    for (const auto &r : rooms) {
        std::cout << r.toCSV() << "\n";
    }

}

void HotelManager::deleteRoomById(const std::string &roomId) {
    auto it = std::remove_if(rooms.begin(), rooms.end(),[&](const Room &r){
        return r.getRoomId() == roomId; 
        }
    );
    
    if (it != rooms.end()) {
        rooms.erase(it, rooms.end());
        saveRooms();
        std::cout << "Da xoa.\n";
    } 
    
    else {
        std::cout << "Khong tim thay.\n";
    }
}

void HotelManager::roomMenu() {
    clearScreen();
    
    while (true) {
        std::cout << "\n-- QUAN LY PHONG --\n";
        std::cout << "1. Them phong\n";
        std::cout << "2. Liet ke phong\n";
        std::cout << "3. Xem chi tiet phong\n";
        std::cout << "4. Xoa phong\n";
        std::cout << "0. Quay lai\n";
        std::cout << "Chon: " << std::flush;
        
        int c;
        if (!(std::cin >> c)) {
            std::cin.clear();
            std::string tmp; std::getline(std::cin, tmp);
            continue;
        }

        if (c == 1) {
            addRoomInteractive();
        }

        else if (c == 2) listRooms();

        else if (c == 3) {
            std::cout << "Nhap ma phong: " << std::flush;
            std::string roomId;
            std::cin >> roomId;

            searchRoomById(roomId);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        else if (c == 4) {
            std::cout << "Nhap ma phong can xoa: " << std::flush;
            std::string roomId;
            std::cin >> roomId;

            deleteRoomById(roomId);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        else if (c == 0) break;

        else std::cout << "Noi dung nhap khong hop le.\n";
    }
}

