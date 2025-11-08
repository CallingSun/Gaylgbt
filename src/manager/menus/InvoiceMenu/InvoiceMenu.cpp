#include "../../HotelManager.h"
#include "../../../utils/DateUtils/DateUtils.h"
#include <iostream>
#include <limits>
#include <algorithm>


void HotelManager::createInvoiceInteractive() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string invId, cccd, roomId, from, to;

    std::cout << "Nhap ma hoa don: " << std::flush;
    std::getline(std::cin, invId);
    
    if (findInvoiceById(invId)) {
        std::cout << "Hoa don da ton tai.\n";
        return;
    }

    std::cout << "Nhap CCCD khach: " << std::flush;
    std::getline(std::cin, cccd);
    
    Customer *c = findCustomerByCccd(cccd);
    if (!c) {
        std::cout << "Khong tim thay khach.\n";
        return;
    }

    std::cout << "Nhap ma phong: " << std::flush;
    std::getline(std::cin, roomId);

    Room *r = findRoomById(roomId);
    
    if (!r) {
        std::cout << "Khong tim thay phong.\n";
        return;
    }

    if (!r->isAvailable()) {
        std::cout << "Phong dang duoc thue.\n";
        return;
    }

    std::cout << "Nhap ngay den (YYYY-MM-DD): " << std::flush;
    std::getline(std::cin, from);

    std::cout << "Nhap ngay di (YYYY-MM-DD): " << std::flush;
    std::getline(std::cin, to);

    int nights = nightsBetween(from, to);
    if (nights <= 0) {
        std::cout << "Khoang ngay khong hop le.\n";
        return;
    }

    double total = nights * r->getPrice();

    Invoice inv(invId, cccd, roomId, from, to, total);
    invoices.push_back(inv);

    r->setAvailable(false);

    saveInvoices();
    saveRooms();

    std::cout << "Tao hoa don thanh cong. Tong tien: " << total << "\n";
}

void HotelManager::listInvoices() const {
    std::cout << "---- DANH SACH HOA DON ----\n";

    for (const auto &inv : invoices) {
        std::cout << inv.toCSV() << "\n";
    }
}

void HotelManager::deleteInvoiceById(const std::string &invId) {
    std::string roomId;
    bool found = false;

    for (const auto &inv : invoices) {
        if (inv.getInvoiceId() == invId) {
            roomId = inv.getRoomId();
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Khong tim thay hoa don.\n";
        return;
    }

    auto it = std::remove_if(invoices.begin(), invoices.end(), [&](const Invoice &inv){
        return inv.getInvoiceId() == invId;
        }
    );
    invoices.erase(it, invoices.end());

    for (auto &r : rooms) {
        if (r.getRoomId() == roomId) {
            r.setAvailable(true);
            break;
        }
    }

    saveInvoices();
    saveRooms();

    std::cout << "Da xoa hoa don.\n";
}

void HotelManager::invoiceMenu() {
    clearScreen();

    while (true) {
        std::cout << "\n-- QUAN LY HOA DON --\n";
        std::cout << "1. Tao hoa don\n";
        std::cout << "2. Liet ke hoa don\n";
        std::cout << "3. Xoa hoa don\n";
        std::cout << "0. Quay lai\n";
        std::cout << "Chon: " << std::flush;

        int c;
        if (!(std::cin >> c)) {
            std::cin.clear();
            std::string tmp; std::getline(std::cin,tmp);
            continue;
        }

        if (c == 1) {
            createInvoiceInteractive();
        }

        else if (c == 2) listInvoices();

        else if (c == 3) {
            std::cout << "Nhap ma hoa don can xoa: " << std::flush;
            
            std::string invId;
            std::cin >> invId;

            deleteInvoiceById(invId);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        else if (c == 0) break;

        else std::cout << "Noi dung nhap khong hop le.\n";
    }
}

