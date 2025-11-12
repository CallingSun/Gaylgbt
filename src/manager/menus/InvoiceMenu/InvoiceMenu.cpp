#include "../../HotelManager.h"
#include "../../../utils/DateUtils/DateUtils.h"
#include "../../../utils/StringUtils/StringUtils.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>


void HotelManager::createInvoiceInteractive() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string invId, customerCccd, employeeCccd, roomId, from, to;

    invId = generateNextInvoiceId();

    customerCccd = getValidatedCccdInput();

    Customer *c = findCustomerByCccd(customerCccd);
    if (!c) {
        std::cout << "Khong tim thay khach.\n";
        return;
    }

    std::cout << "\n-- Chon nhan vien tao hoa don --\n";
    employeeCccd = displayEmployeesForSelection();
    if (employeeCccd.empty()) {
        std::cout << "Khong co nhan vien duoc chon.\n";
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

    from = getValidatedDateInput();
    to = getValidatedDateInput();

    int nights = nightsBetween(from, to);
    if (nights <= 0) {
        std::cout << "Khoang ngay khong hop le.\n";
        return;
    }

    double total = nights * r->getPrice();

    Invoice inv(invId, customerCccd, employeeCccd, roomId, from, to, total);
    invoices.push_back(inv);

    r->setAvailable(false);

    saveInvoices();
    saveRooms();

    std::cout << "Tao hoa don thanh cong. Ma hoa don: " << invId << ", Tong tien: $" << total << " USD\n";
}

void HotelManager::createInvoiceBatch(int quantity) {
    int successCount = 0;

    for (int i = 1; i <= quantity; ++i) {
        displayProgressIndicator(i, quantity, "nhap thong tin hoa don");

        std::string invId, customerCccd, employeeCccd, roomId, from, to;

        invId = generateNextInvoiceId();
        customerCccd = getValidatedCccdInput();

        Customer *c = findCustomerByCccd(customerCccd);
        if (!c) {
            std::cout << "Khong tim thay khach. Bo qua.\n";
            continue;
        }

        employeeCccd = displayEmployeesForSelection();
        if (employeeCccd.empty()) {
            std::cout << "Khong co nhan vien duoc chon. Bo qua.\n";
            continue;
        }

        std::cout << "Nhap ma phong: " << std::flush;
        std::getline(std::cin, roomId);

        Room *r = findRoomById(roomId);
        if (!r) {
            std::cout << "Khong tim thay phong. Bo qua.\n";
            continue;
        }

        if (!r->isAvailable()) {
            std::cout << "Phong dang duoc thue. Bo qua.\n";
            continue;
        }

        from = getValidatedDateInput();
        to = getValidatedDateInput();

        int nights = nightsBetween(from, to);
        if (nights <= 0) {
            std::cout << "Khoang ngay khong hop le. Bo qua.\n";
            continue;
        }

        double total = nights * r->getPrice();

        Invoice inv(invId, customerCccd, employeeCccd, roomId, from, to, total);
        invoices.push_back(inv);
        r->setAvailable(false);
        successCount++;
    }

    saveInvoices();
    saveRooms();
    std::cout << "Da tao thanh cong " << successCount << " hoa don.\n";
}

void HotelManager::listInvoices() const {
    if (invoices.empty()) {
        std::cout << "Khong co du lieu.\n";
        return;
    }

    std::cout << "\n---- DANH SACH HOA DON ----\n\n";

    std::cout << "+" << std::string(12, '-') << "+" << std::string(12, '-') << "+"
            << std::string(12, '-') << "+" << std::string(10, '-') << "+"
            << std::string(12, '-') << "+" << std::string(12, '-') << "+"
            << std::string(15, '-') << "+\n";

    std::cout << "| " << std::left << std::setw(10) << "Ma Hoa Don"
            << " | " << std::left << std::setw(10) << "CCCD Khach"
            << " | " << std::left << std::setw(10) << "CCCD NV"
            << " | " << std::left << std::setw(8) << "Ma Phong"
            << " | " << std::left << std::setw(10) << "Ngay Nhan"
            << " | " << std::left << std::setw(10) << "Ngay Tra"
            << " | " << std::right << std::setw(13) << "Tong Tien (USD)"
            << " |\n";

    std::cout << "+" << std::string(12, '-') << "+" << std::string(12, '-') << "+"
            << std::string(12, '-') << "+" << std::string(10, '-') << "+"
            << std::string(12, '-') << "+" << std::string(12, '-') << "+"
            << std::string(15, '-') << "+\n";

    for (const auto &inv : invoices) {
        std::cout << "| " << std::left << std::setw(10) << inv.getInvoiceId()
                << " | " << std::left << std::setw(10) << inv.getCustomerCccd()
                << " | " << std::left << std::setw(10) << inv.getEmployeeCccd()
                << " | " << std::left << std::setw(8) << inv.getRoomId()
                << " | " << std::left << std::setw(10) << inv.getDateFrom()
                << " | " << std::left << std::setw(10) << inv.getDateTo()
                << " | $" << std::right << std::setw(12) << std::fixed << std::setprecision(2) << inv.getTotal()
                << " |\n";
    }

    std::cout << "+" << std::string(12, '-') << "+" << std::string(12, '-') << "+"
            << std::string(12, '-') << "+" << std::string(10, '-') << "+"
            << std::string(12, '-') << "+" << std::string(12, '-') << "+"
            << std::string(15, '-') << "+\n\n";
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

    reorderInvoiceIds();

    std::cout << "Da xoa hoa don va sap xep lai ma hoa don.\n";
}

void HotelManager::editInvoiceById(const std::string &invId) {
    Invoice* inv = findInvoiceById(invId);
    if (!inv) {
        std::cout << "Khong tim thay hoa don.\n";
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string input;
    std::string oldRoomId = inv->getRoomId();
    std::string newRoomId = oldRoomId;

    std::cout << "CCCD khach hien tai: " << inv->getCustomerCccd() << ". ";
    input = getValidatedCccdInputOptional();
    if (!input.empty()) {
        if (findCustomerByCccd(input)) {
            inv->setCustomerCccd(input);
        } else {
            std::cout << "Khach hang khong ton tai.\n";
        }
    }

    std::cout << "CCCD nhan vien hien tai: " << inv->getEmployeeCccd() << ". Nhap CCCD nhan vien moi (Enter de giu nguyen): " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty()) {
        if (findEmployeeByCccd(input)) {
            inv->setEmployeeCccd(input);
        } else {
            std::cout << "Nhan vien khong ton tai.\n";
        }
    }

    std::cout << "Ma phong hien tai: " << inv->getRoomId() << ". Nhap ma phong moi (Enter de giu nguyen): " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty()) {
        Room* newRoom = findRoomById(input);
        if (!newRoom) {
            std::cout << "Phong khong ton tai.\n";
        } else if (!newRoom->isAvailable() && input != oldRoomId) {
            std::cout << "Phong dang duoc thue.\n";
        } else {
            newRoomId = input;
            inv->setRoomId(input);
        }
    }

    std::cout << "Ngay den hien tai: " << inv->getDateFrom() << ". Nhap ngay den moi (Enter de giu nguyen): " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty()) {
        inv->setDateFrom(input);
    }

    std::cout << "Ngay di hien tai: " << inv->getDateTo() << ". " << std::flush;
    input = getValidatedDateInputOptional();
    if (!input.empty()) {
        inv->setDateTo(input);
    }

    int nights = nightsBetween(inv->getDateFrom(), inv->getDateTo());
    if (nights > 0) {
        Room* r = findRoomById(inv->getRoomId());
        if (r) {
            double total = nights * r->getPrice();
            inv->setTotal(total);
        }
    }

    if (newRoomId != oldRoomId) {
        for (auto &r : rooms) {
            if (r.getRoomId() == oldRoomId) {
                r.setAvailable(true);
                break;
            }
        }
        
        for (auto &r : rooms) {
            if (r.getRoomId() == newRoomId) {
                r.setAvailable(false);
                break;
            }
        }
    }

    saveInvoices();
    saveRooms();
    std::cout << "Cap nhat hoa don thanh cong.\n";
}

void HotelManager::editInvoiceBatch(int quantity) {
    int successCount = 0;

    for (int i = 1; i <= quantity; ++i) {
        displayProgressIndicator(i, quantity, "chinh sua hoa don");

        std::string invId = displayInvoicesForSelection();

        if (!invId.empty()) {
            editInvoiceById(invId);
            successCount++;
        }
    }

    std::cout << "Da chinh sua thanh cong " << successCount << " hoa don.\n";
}

void HotelManager::deleteInvoiceBatch(int quantity) {
    std::vector<std::string> selectedInvIds;

    for (int i = 1; i <= quantity; ++i) {
        displayProgressIndicator(i, quantity, "chon hoa don can xoa");

        std::string invId = displayInvoicesForSelection();

        if (!invId.empty()) {
            selectedInvIds.push_back(invId);
        }
    }

    if (selectedInvIds.empty()) {
        std::cout << "Khong co hoa don nao duoc chon.\n";
        return;
    }

    if (getConfirmation("Ban co chac chan muon xoa " + std::to_string(selectedInvIds.size()) + " hoa don?")) {
        int deleteCount = 0;
        for (const auto &invId : selectedInvIds) {
            std::string roomId;
            bool found = false;

            for (const auto &inv : invoices) {
                if (inv.getInvoiceId() == invId) {
                    roomId = inv.getRoomId();
                    found = true;
                    break;
                }
            }

            if (found) {
                auto it = std::remove_if(invoices.begin(), invoices.end(), [&](const Invoice &inv){
                    return inv.getInvoiceId() == invId;
                });

                if (it != invoices.end()) {
                    invoices.erase(it, invoices.end());

                    for (auto &r : rooms) {
                        if (r.getRoomId() == roomId) {
                            r.setAvailable(true);
                            break;
                        }
                    }
                    deleteCount++;
                }
            }
        }

        reorderInvoiceIds();
        saveInvoices();
        saveRooms();
        std::cout << "Da xoa thanh cong " << deleteCount << " hoa don.\n";
    } else {
        std::cout << "Huy thao tac xoa.\n";
    }
}

void HotelManager::invoiceMenu() {
    clearScreen();

    while (true) {
        std::cout << "\n-- QUAN LY HOA DON --\n";
        std::cout << "1. Tao hoa don\n";
        std::cout << "2. Chinh sua hoa don\n";
        std::cout << "3. Liet ke hoa don\n";
        std::cout << "4. Xoa hoa don\n";
        std::cout << "0. Quay lai\n";
        std::cout << "Chon: " << std::flush;

        int c;
        if (!(std::cin >> c)) {
            std::cin.clear();
            std::string tmp; std::getline(std::cin,tmp);
            continue;
        }

        if (c == 1) {
            int quantity = getValidatedQuantityInput();
            if (quantity == 1) {
                createInvoiceInteractive();
            } else {
                createInvoiceBatch(quantity);
            }
        }

        else if (c == 2) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string invId = displayInvoicesForSelection();
            if (!invId.empty()) {
                int quantity = getValidatedQuantityInput();
                if (quantity == 1) {
                    editInvoiceById(invId);
                } else {
                    editInvoiceBatch(quantity);
                }
            }
        }

        else if (c == 3) listInvoices();

        else if (c == 4) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string invId = displayInvoicesForSelection();
            if (!invId.empty()) {
                int quantity = getValidatedQuantityInput();
                if (quantity == 1) {
                    deleteInvoiceById(invId);
                } else {
                    deleteInvoiceBatch(quantity);
                }
            }
        }

        else if (c == 0) break;

        else std::cout << "Noi dung nhap khong hop le.\n";
    }
}

