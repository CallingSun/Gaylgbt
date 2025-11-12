#include "../../HotelManager.h"
#include "../../../utils/StringUtils/StringUtils.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>


void HotelManager::addEmployeeInteractive() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string cccd, name, phone, email, pos, salStr;

    double sal = 0.0;

    cccd = getValidatedCccdInput();

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

    pos = getValidatedPositionInput();

    std::cout << "Nhap luong (USD): " << std::flush;

    std::getline(std::cin, salStr);

    try { sal = std::stod(salStr); } catch (...) { sal = 0.0; }

    Employee e(cccd, name, phone, email, pos, sal);

    employees.push_back(e);

    saveEmployees();

    std::cout << "Them nhan vien thanh cong.\n";
}

void HotelManager::addEmployeeBatch(int quantity) {
    int successCount = 0;

    for (int i = 1; i <= quantity; ++i) {
        displayProgressIndicator(i, quantity, "nhap thong tin nhan vien");

        std::string cccd, name, phone, email, pos, salStr;
        double sal = 0.0;

        cccd = getValidatedCccdInput();

        if (findEmployeeByCccd(cccd)) {
            std::cout << "Nhan vien da ton tai. Bo qua.\n";
            continue;
        }

        std::cout << "Nhap ten: " << std::flush;
        std::getline(std::cin, name);

        std::cout << "Nhap so dien thoai: " << std::flush;
        std::getline(std::cin, phone);

        std::cout << "Nhap email: " << std::flush;
        std::getline(std::cin, email);

        pos = getValidatedPositionInput();

        std::cout << "Nhap luong (USD): " << std::flush;
        std::getline(std::cin, salStr);

        try { sal = std::stod(salStr); } catch (...) { sal = 0.0; }

        Employee e(cccd, name, phone, email, pos, sal);
        employees.push_back(e);
        successCount++;
    }

    saveEmployees();
    std::cout << "Da them thanh cong " << successCount << " nhan vien.\n";
}

void HotelManager::listEmployees() const {
    if (employees.empty()) {
        std::cout << "Khong co du lieu.\n";
        return;
    }

    std::cout << "\n---- DANH SACH NHAN VIEN ----\n\n";

    
    std::cout << "+" << std::string(12, '-') << "+" << std::string(25, '-') << "+"
            << std::string(15, '-') << "+" << std::string(30, '-') << "+"
            << std::string(15, '-') << "+" << std::string(15, '-') << "+\n";

    
    std::cout << "| " << std::left << std::setw(10) << "CCCD"
            << " | " << std::left << std::setw(23) << "Ten"
            << " | " << std::left << std::setw(13) << "So Dien Thoai"
            << " | " << std::left << std::setw(28) << "Email"
            << " | " << std::left << std::setw(13) << "Chuc Vu"
            << " | " << std::right << std::setw(13) << "Luong (USD)"
            << " |\n";

    std::cout << "+" << std::string(12, '-') << "+" << std::string(25, '-') << "+"
            << std::string(15, '-') << "+" << std::string(30, '-') << "+"
            << std::string(15, '-') << "+" << std::string(15, '-') << "+\n";

    for (const auto &e : employees) {
        std::cout << "| " << std::left << std::setw(10) << e.getCccd()
                << " | " << std::left << std::setw(23) << e.getName()
                << " | " << std::left << std::setw(13) << e.getPhone()
                << " | " << std::left << std::setw(28) << e.getEmail()
                << " | " << std::left << std::setw(13) << e.getPosition()
                << " | $" << std::right << std::setw(12) << std::fixed << std::setprecision(2) << e.getSalary()
                << " |\n";
    }

    std::cout << "+" << std::string(12, '-') << "+" << std::string(25, '-') << "+"
            << std::string(15, '-') << "+" << std::string(30, '-') << "+"
            << std::string(15, '-') << "+" << std::string(15, '-') << "+\n\n";
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

void HotelManager::editEmployeeByCccd(const std::string &cccd) {
    Employee* e = findEmployeeByCccd(cccd);
    if (!e) {
        std::cout << "Khong tim thay nhan vien.\n";
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string input;

    std::cout << "Ten hien tai: " << e->getName() << ". Nhap ten moi (Enter de giu nguyen): " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty()) {
        e->setName(input);
    }

    std::cout << "So dien thoai hien tai: " << e->getPhone() << ". Nhap so dien thoai moi (Enter de giu nguyen): " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty()) {
        e->setPhone(input);
    }

    std::cout << "Email hien tai: " << e->getEmail() << ". Nhap email moi (Enter de giu nguyen): " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty()) {
        e->setEmail(input);
    }

    std::cout << "Vi tri hien tai: " << e->getPosition() << ". ";
    std::string newPosition = getValidatedPositionInputOptional();
    if (!newPosition.empty()) {
        e->setPosition(newPosition);
    }

    std::cout << "Luong hien tai: $" << e->getSalary() << " USD. Nhap luong moi (USD, Enter de giu nguyen): " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty()) {
        try {
            double sal = std::stod(input);
            e->setSalary(sal);
        } catch (...) {
            std::cout << "Luong khong hop le, giu nguyen.\n";
        }
    }

    saveEmployees();
    std::cout << "Cap nhat thong tin nhan vien thanh cong.\n";
}

void HotelManager::editEmployeeBatch(int quantity) {
    int successCount = 0;

    for (int i = 1; i <= quantity; ++i) {
        displayProgressIndicator(i, quantity, "chinh sua nhan vien");

        std::string cccd = displayEmployeesForSelection();

        if (!cccd.empty()) {
            editEmployeeByCccd(cccd);
            successCount++;
        }
    }

    std::cout << "Da chinh sua thanh cong " << successCount << " nhan vien.\n";
}

void HotelManager::deleteEmployeeBatch(int quantity) {
    std::vector<std::string> selectedCccd;

    for (int i = 1; i <= quantity; ++i) {
        displayProgressIndicator(i, quantity, "chon nhan vien can xoa");

        std::string cccd = displayEmployeesForSelection();

        if (!cccd.empty()) {
            selectedCccd.push_back(cccd);
        }
    }

    if (selectedCccd.empty()) {
        std::cout << "Khong co nhan vien nao duoc chon.\n";
        return;
    }

    if (getConfirmation("Ban co chac chan muon xoa " + std::to_string(selectedCccd.size()) + " nhan vien?")) {
        int deleteCount = 0;
        for (const auto &cccd : selectedCccd) {
            auto it = std::remove_if(employees.begin(), employees.end(), [&](const Employee &e){
                return e.getCccd() == cccd;
            });

            if (it != employees.end()) {
                employees.erase(it, employees.end());
                deleteCount++;
            }
        }

        saveEmployees();
        std::cout << "Da xoa thanh cong " << deleteCount << " nhan vien.\n";
    } else {
        std::cout << "Huy thao tac xoa.\n";
    }
}

void HotelManager::employeeMenu() {
    clearScreen();

    while (true) {
        std::cout << "\n-- QUAN LY NHAN VIEN --\n";
        std::cout << "1. Them nhan vien\n";
        std::cout << "2. Chinh sua thong tin nhan vien\n";
        std::cout << "3. Liet ke nhan vien\n";
        std::cout << "4. Xoa nhan vien\n";
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
                addEmployeeInteractive();
            } else {
                addEmployeeBatch(quantity);
            }
        }

        else if (c == 2) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string cccd = displayEmployeesForSelection();
            if (!cccd.empty()) {
                int quantity = getValidatedQuantityInput();
                if (quantity == 1) {
                    editEmployeeByCccd(cccd);
                } else {
                    editEmployeeBatch(quantity);
                }
            }
        }
        else if (c == 3) listEmployees();
        else if (c == 4) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string cccd = displayEmployeesForSelection();
            if (!cccd.empty()) {
                int quantity = getValidatedQuantityInput();
                if (quantity == 1) {
                    deleteEmployeeByCccd(cccd);
                } else {
                    deleteEmployeeBatch(quantity);
                }
            }
        }

        else if (c == 0) break;

        else std::cout << "Noi dung nhap khong hop le.\n";
    }
}

