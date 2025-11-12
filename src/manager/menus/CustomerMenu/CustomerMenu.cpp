#include "../../HotelManager.h"
#include "../../../utils/DateUtils/DateUtils.h"
#include "../../../utils/StringUtils/StringUtils.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>

void HotelManager::addCustomerInteractive() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string cccd, name, phone, email, dob, addr;

    cccd = getValidatedCccdInput();

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

    dob = getValidatedDateInput();

    std::cout << "Nhap dia chi: " << std::flush;

    std::getline(std::cin, addr);

    Customer c(cccd, name, phone, email, dob, addr);

    customers.push_back(c);

    saveCustomers();

    std::cout << "Them khach thanh cong.\n";
}

void HotelManager::addCustomerBatch(int quantity) {
    int successCount = 0;

    for (int i = 1; i <= quantity; ++i) {
        displayProgressIndicator(i, quantity, "nhap thong tin khach");

        std::string cccd, name, phone, email, dob, addr;

        cccd = getValidatedCccdInput();

        if (customerExists(cccd)) {
            std::cout << "Khach voi CCCD nay da ton tai. Bo qua.\n";
            continue;
        }

        std::cout << "Nhap ten: " << std::flush;
        std::getline(std::cin, name);

        std::cout << "Nhap so dien thoai: " << std::flush;
        std::getline(std::cin, phone);

        std::cout << "Nhap email: " << std::flush;
        std::getline(std::cin, email);

        dob = getValidatedDateInput();

        std::cout << "Nhap dia chi: " << std::flush;
        std::getline(std::cin, addr);

        Customer c(cccd, name, phone, email, dob, addr);
        customers.push_back(c);
        successCount++;
    }

    saveCustomers();
    std::cout << "Da them thanh cong " << successCount << " khach hang.\n";
}

void HotelManager::listCustomers() const {
    if (customers.empty()) {
        std::cout << "Khong co du lieu.\n";
        return;
    }

    std::cout << "\n---- DANH SACH KHACH HANG ----\n\n";

    std::cout << "+" << std::string(12, '-') << "+" << std::string(25, '-') << "+"
            << std::string(15, '-') << "+" << std::string(30, '-') << "+"
            << std::string(12, '-') << "+" << std::string(30, '-') << "+\n";

    std::cout << "| " << std::left << std::setw(10) << "CCCD"
            << " | " << std::left << std::setw(23) << "Ten"
            << " | " << std::left << std::setw(13) << "So Dien Thoai"
            << " | " << std::left << std::setw(28) << "Email"
            << " | " << std::left << std::setw(10) << "Ngay Sinh"
            << " | " << std::left << std::setw(28) << "Dia Chi"
            << " |\n";

    std::cout << "+" << std::string(12, '-') << "+" << std::string(25, '-') << "+"
            << std::string(15, '-') << "+" << std::string(30, '-') << "+"
            << std::string(12, '-') << "+" << std::string(30, '-') << "+\n";

    for (const auto &c : customers) {
        std::cout << "| " << std::left << std::setw(10) << c.getCccd()
                << " | " << std::left << std::setw(23) << c.getName()
                << " | " << std::left << std::setw(13) << c.getPhone()
                << " | " << std::left << std::setw(28) << c.getEmail()
                << " | " << std::left << std::setw(10) << c.getBirthdate()
                << " | " << std::left << std::setw(28) << c.getAddress()
                << " |\n";
    }

    std::cout << "+" << std::string(12, '-') << "+" << std::string(25, '-') << "+"
            << std::string(15, '-') << "+" << std::string(30, '-') << "+"
            << std::string(12, '-') << "+" << std::string(30, '-') << "+\n\n";
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

void HotelManager::editCustomerByCccd(const std::string &cccd) {
    Customer* c = findCustomerByCccd(cccd);
    if (!c) {
        std::cout << "Khong tim thay khach hang.\n";
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string input;

    std::cout << "Ten hien tai: " << c->getName() << ". Nhap ten moi (Enter de giu nguyen): " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty()) {
        c->setName(input);
    }

    std::cout << "So dien thoai hien tai: " << c->getPhone() << ". Nhap so dien thoai moi (Enter de giu nguyen): " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty()) {
        c->setPhone(input);
    }

    std::cout << "Email hien tai: " << c->getEmail() << ". Nhap email moi (Enter de giu nguyen): " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty()) {
        c->setEmail(input);
    }

    std::cout << "Ngay sinh hien tai: " << c->getBirthdate() << ". " << std::flush;
    input = getValidatedDateInputOptional();
    if (!input.empty()) {
        c->setBirthdate(input);
    }

    std::cout << "Dia chi hien tai: " << c->getAddress() << ". Nhap dia chi moi (Enter de giu nguyen): " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty()) {
        c->setAddress(input);
    }

    saveCustomers();
    std::cout << "Cap nhat thong tin khach hang thanh cong.\n";
}

void HotelManager::editCustomerBatch(int quantity) {
    int successCount = 0;

    for (int i = 1; i <= quantity; ++i) {
        displayProgressIndicator(i, quantity, "chinh sua khach");

        std::string cccd = displayCustomersForSelection();

        if (!cccd.empty()) {
            editCustomerByCccd(cccd);
            successCount++;
        }
    }

    std::cout << "Da chinh sua thanh cong " << successCount << " khach hang.\n";
}

void HotelManager::deleteCustomerBatch(int quantity) {
    std::vector<std::string> selectedCccd;

    for (int i = 1; i <= quantity; ++i) {
        displayProgressIndicator(i, quantity, "chon khach can xoa");

        std::string cccd = displayCustomersForSelection();

        if (!cccd.empty()) {
            selectedCccd.push_back(cccd);
        }
    }

    if (selectedCccd.empty()) {
        std::cout << "Khong co khach hang nao duoc chon.\n";
        return;
    }

    if (getConfirmation("Ban co chac chan muon xoa " + std::to_string(selectedCccd.size()) + " khach hang?")) {
        int deleteCount = 0;
        for (const auto &cccd : selectedCccd) {
            auto it = std::remove_if(customers.begin(), customers.end(), [&](const Customer &c){
                return c.getCccd() == cccd;
            });

            if (it != customers.end()) {
                customers.erase(it, customers.end());
                deleteCount++;
            }
        }

        saveCustomers();
        std::cout << "Da xoa thanh cong " << deleteCount << " khach hang.\n";
    } else {
        std::cout << "Huy thao tac xoa.\n";
    }
}

void HotelManager::customerMenu() {
    clearScreen();

    while (true) {
        std::cout << "\n-- QUAN LY KHACH HANG --\n";
        std::cout << "1. Them khach\n";
        std::cout << "2. Chinh sua thong tin khach hang\n";
        std::cout << "3. Liet ke khach\n";
        std::cout << "4. Xoa khach theo CCCD\n";
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
                addCustomerInteractive();
            } else {
                addCustomerBatch(quantity);
            }
        }
        else if (c == 2) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string cccd = displayCustomersForSelection();
            if (!cccd.empty()) {
                int quantity = getValidatedQuantityInput();
                if (quantity == 1) {
                    editCustomerByCccd(cccd);
                } else {
                    editCustomerBatch(quantity);
                }
            }
        }
        else if (c == 3) listCustomers();
        else if (c == 4) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string cccd = displayCustomersForSelection();
            if (!cccd.empty()) {
                int quantity = getValidatedQuantityInput();
                if (quantity == 1) {
                    deleteCustomerByCccd(cccd);
                } else {
                    deleteCustomerBatch(quantity);
                }
            }
        }
        else if (c == 0) break;
        else std::cout << "Noi dung nhap khong hop le.\n";
    }
}

