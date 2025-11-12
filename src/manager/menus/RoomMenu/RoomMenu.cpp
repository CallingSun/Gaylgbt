#include "../../HotelManager.h"
#include "../../../utils/StringUtils/StringUtils.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>


void HotelManager::addRoomInteractive() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string type;
    double price = 0.0;

    std::string roomId = generateNextRoomId();

    type = getValidatedRoomTypeInput();

    price = getValidatedRoomPriceInput(type);

    Room r(roomId, type, price, true);
    rooms.push_back(r);
    saveRooms();
    std::cout << "Them phong thanh cong. Ma phong: " << roomId << "\n";
}

void HotelManager::addRoomBatch(int quantity) {
    int successCount = 0;

    for (int i = 1; i <= quantity; ++i) {
        displayProgressIndicator(i, quantity, "nhap thong tin phong");

        std::string type;
        double price = 0.0;

        std::string roomId = generateNextRoomId();
        type = getValidatedRoomTypeInput();
        price = getValidatedRoomPriceInput(type);

        Room r(roomId, type, price, true);
        rooms.push_back(r);
        successCount++;
    }

    saveRooms();
    std::cout << "Da them thanh cong " << successCount << " phong.\n";
}

void HotelManager::listRooms() const {
    if (rooms.empty()) {
        std::cout << "Khong co du lieu.\n";
        return;
    }

    std::cout << "\n------ DANH SACH PHONG ------\n\n";

    std::cout << "+" << std::string(10, '-') << "+" << std::string(15, '-') << "+"
            << std::string(15, '-') << "+" << std::string(15, '-') << "+\n";

    std::cout << "| " << std::left << std::setw(8) << "Ma Phong"
            << " | " << std::left << std::setw(13) << "Loai Phong"
            << " | " << std::right << std::setw(13) << "Gia/Dem (USD)"
            << " | " << std::left << std::setw(13) << "Trang Thai"
            << " |\n";

    std::cout << "+" << std::string(10, '-') << "+" << std::string(15, '-') << "+"
            << std::string(15, '-') << "+" << std::string(15, '-') << "+\n";

    for (const auto &r : rooms) {
        std::string status = r.isAvailable() ? "Con Trong" : "Da Dat";
        std::cout << "| " << std::left << std::setw(8) << r.getRoomId()
                << " | " << std::left << std::setw(13) << r.getType()
                << " | $" << std::right << std::setw(12) << std::fixed << std::setprecision(2) << r.getPrice()
                << " | " << std::left << std::setw(13) << status
                << " |\n";
    }

    std::cout << "+" << std::string(10, '-') << "+" << std::string(15, '-') << "+"
            << std::string(15, '-') << "+" << std::string(15, '-') << "+\n\n";
}

void HotelManager::deleteRoomById(const std::string &roomId) {
    auto it = std::remove_if(rooms.begin(), rooms.end(),[&](const Room &r){
        return r.getRoomId() == roomId;
        }
    );

    if (it != rooms.end()) {
        rooms.erase(it, rooms.end());
        // Sắp xếp lại mã phòng
        reorderRoomIds();
        std::cout << "Da xoa va sap xep lai ma phong.\n";
    }

    else {
        std::cout << "Khong tim thay.\n";
    }
}

void HotelManager::editRoomById(const std::string &roomId) {
    Room* r = findRoomById(roomId);
    if (!r) {
        std::cout << "Khong tim thay phong.\n";
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string input;
    std::string currentType = r->getType();

    std::cout << "Loai phong hien tai: " << currentType << ". ";
    input = getValidatedRoomTypeInputOptional();
    if (!input.empty()) {
        r->setType(input);
        currentType = input;
    }

    std::cout << "Gia hien tai: $" << r->getPrice() << " USD. ";
    double newPrice = getValidatedRoomPriceInputOptional(currentType);
    if (newPrice >= 0.0) {
        r->setPrice(newPrice);
    }

    saveRooms();
    std::cout << "Cap nhat thong tin phong thanh cong.\n";
}

void HotelManager::editRoomBatch(int quantity) {
    int successCount = 0;

    for (int i = 1; i <= quantity; ++i) {
        displayProgressIndicator(i, quantity, "chinh sua phong");

        std::string roomId = displayRoomsForSelection();

        if (!roomId.empty()) {
            editRoomById(roomId);
            successCount++;
        }
    }

    std::cout << "Da chinh sua thanh cong " << successCount << " phong.\n";
}

void HotelManager::deleteRoomBatch(int quantity) {
    std::vector<std::string> selectedRoomIds;

    for (int i = 1; i <= quantity; ++i) {
        displayProgressIndicator(i, quantity, "chon phong can xoa");

        std::string roomId = displayRoomsForSelection();

        if (!roomId.empty()) {
            selectedRoomIds.push_back(roomId);
        }
    }

    if (selectedRoomIds.empty()) {
        std::cout << "Khong co phong nao duoc chon.\n";
        return;
    }

    if (getConfirmation("Ban co chac chan muon xoa " + std::to_string(selectedRoomIds.size()) + " phong?")) {
        int deleteCount = 0;
        for (const auto &roomId : selectedRoomIds) {
            auto it = std::remove_if(rooms.begin(), rooms.end(), [&](const Room &r){
                return r.getRoomId() == roomId;
            });

            if (it != rooms.end()) {
                rooms.erase(it, rooms.end());
                deleteCount++;
            }
        }

        reorderRoomIds();
        saveRooms();
        std::cout << "Da xoa thanh cong " << deleteCount << " phong.\n";
    } else {
        std::cout << "Huy thao tac xoa.\n";
    }
}

void HotelManager::roomMenu() {
    clearScreen();

    while (true) {
        std::cout << "\n-- QUAN LY PHONG --\n";
        std::cout << "1. Them phong\n";
        std::cout << "2. Chinh sua thong tin phong\n";
        std::cout << "3. Liet ke phong\n";
        std::cout << "4. Xem chi tiet phong\n";
        std::cout << "5. Xoa phong\n";
        std::cout << "0. Quay lai\n";
        std::cout << "Chon: " << std::flush;

        int c;
        if (!(std::cin >> c)) {
            std::cin.clear();
            std::string tmp; std::getline(std::cin, tmp);
            continue;
        }

        if (c == 1) {
            int quantity = getValidatedQuantityInput();
            if (quantity == 1) {
                addRoomInteractive();
            } else {
                addRoomBatch(quantity);
            }
        }

        else if (c == 2) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string roomId = displayRoomsForSelection();
            if (!roomId.empty()) {
                int quantity = getValidatedQuantityInput();
                if (quantity == 1) {
                    editRoomById(roomId);
                } else {
                    editRoomBatch(quantity);
                }
            }
        }

        else if (c == 3) listRooms();

        else if (c == 4) {
            std::cout << "Nhap ma phong: " << std::flush;
            std::string roomId;
            std::cin >> roomId;

            searchRoomById(roomId);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        else if (c == 5) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string roomId = displayRoomsForSelection();
            if (!roomId.empty()) {
                int quantity = getValidatedQuantityInput();
                if (quantity == 1) {
                    deleteRoomById(roomId);
                } else {
                    deleteRoomBatch(quantity);
                }
            }
        }

        else if (c == 0) break;

        else std::cout << "Noi dung nhap khong hop le.\n";
    }
}

