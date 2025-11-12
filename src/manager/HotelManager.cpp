#include "HotelManager.h"
#include "utils/StringUtils/StringUtils.h"//Gọi các utils đề thực hiện tính toán
#include "utils/DateUtils/DateUtils.h"

#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <cstdlib>
#include <iomanip>
#include <sstream>

HotelManager::HotelManager(const std::string &dataDir)
    : dataDir(dataDir), authManager(dataDir), currentRole(-1) {
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


std::string HotelManager::displayCustomersForSelection() {
    if (customers.empty()) {
        std::cout << "Khong co khach hang nao.\n";
        return "";
    }

    std::cout << "\n---- DANH SACH KHACH HANG ----\n";
    std::cout << "STT | CCCD | Ten | So dien thoai | Email\n";
    std::cout << "----+------+-----+---------------+-------\n";

    for (size_t i = 0; i < customers.size(); ++i) {
        std::cout << (i + 1) << ". " << customers[i].getCccd() << " | "
                << customers[i].getName() << " | "
                << customers[i].getPhone() << " | "
                << customers[i].getEmail() << "\n";
    }

    std::cout << "\nChon so thu tu (1-" << customers.size() << ") hoac 0 de huy: " << std::flush;
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::string tmp; std::getline(std::cin, tmp);
        return "";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice < 1 || choice > static_cast<int>(customers.size())) {
        if (choice != 0) {
            std::cout << "Lua chon khong hop le.\n";
        }
        return "";
    }

    return customers[choice - 1].getCccd();
}

std::string HotelManager::displayEmployeesForSelection() {
    if (employees.empty()) {
        std::cout << "Khong co nhan vien nao.\n";
        return "";
    }

    std::cout << "\n---- DANH SACH NHAN VIEN ----\n";
    std::cout << "STT | CCCD | Ten | Vi tri | Luong\n";
    std::cout << "----+------+-----+--------+-------\n";

    for (size_t i = 0; i < employees.size(); ++i) {
        std::cout << (i + 1) << ". " << employees[i].getCccd() << " | "
                << employees[i].getName() << " | "
                << employees[i].getPosition() << " | "
                << employees[i].getSalary() << "\n";
    }

    std::cout << "\nChon so thu tu (1-" << employees.size() << ") hoac 0 de huy: " << std::flush;
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::string tmp; std::getline(std::cin, tmp);
        return "";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice < 1 || choice > static_cast<int>(employees.size())) {
        if (choice != 0) {
            std::cout << "Lua chon khong hop le.\n";
        }
        return "";
    }

    return employees[choice - 1].getCccd();
}

std::string HotelManager::displayRoomsForSelection() {
    if (rooms.empty()) {
        std::cout << "Khong co phong nao.\n";
        return "";
    }

    std::cout << "\n---- DANH SACH PHONG ----\n";
    std::cout << "STT | Ma phong | Loai phong | Gia (USD) | Trang thai\n";
    std::cout << "----+----------+------------+-----------+-----------\n";

    for (size_t i = 0; i < rooms.size(); ++i) {
        std::string status = rooms[i].isAvailable() ? "Trong" : "Dang su dung";
        std::cout << (i + 1) << ". " << rooms[i].getRoomId() << " | "
                << rooms[i].getType() << " | "
                << "$" << rooms[i].getPrice() << " | "
                << status << "\n";
    }

    std::cout << "\nChon so thu tu (1-" << rooms.size() << ") hoac 0 de huy: " << std::flush;
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::string tmp; std::getline(std::cin, tmp);
        return "";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice < 1 || choice > static_cast<int>(rooms.size())) {
        if (choice != 0) {
            std::cout << "Lua chon khong hop le.\n";
        }
        return "";
    }

    return rooms[choice - 1].getRoomId();
}

std::string HotelManager::displayInvoicesForSelection() {
    if (invoices.empty()) {
        std::cout << "Khong co hoa don nao.\n";
        return "";
    }

    std::cout << "\n---- DANH SACH HOA DON ----\n";
    std::cout << "STT | Ma hoa don | CCCD khach | Ma phong | Tong tien (USD)\n";
    std::cout << "----+------------+------------+----------+----------------\n";

    for (size_t i = 0; i < invoices.size(); ++i) {
        std::cout << (i + 1) << ". " << invoices[i].getInvoiceId() << " | "
                << invoices[i].getCustomerCccd() << " | "
                << invoices[i].getRoomId() << " | "
                << "$" << invoices[i].getTotal() << "\n";
    }

    std::cout << "\nChon so thu tu (1-" << invoices.size() << ") hoac 0 de huy: " << std::flush;
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::string tmp; std::getline(std::cin, tmp);
        return "";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice < 1 || choice > static_cast<int>(invoices.size())) {
        if (choice != 0) {
            std::cout << "Lua chon khong hop le.\n";
        }
        return "";
    }

    return invoices[choice - 1].getInvoiceId();
}

//Console

void HotelManager::runConsole() {
    clearScreen();
    while (true) {
        if (currentRole == -1) {
            homeMenu();
        } else if (currentRole == 0) {
            adminMainMenu();
        } else if (currentRole == 1) {
            staffMainMenu();
        } else if (currentRole == 2) {
            customerMainMenu();
        }
    }
}

void HotelManager::adminMainMenu() {
    while (currentRole == 0) {
        std::cout << "\n=== Quan Li Hotel Mini ===\n";
        std::cout << "Xin chao: " << currentUsername << "\n";
        std::cout << "1. Quan ly khach hang\n";
        std::cout << "2. Quan ly nhan vien\n";
        std::cout << "3. Quan ly phong\n";
        std::cout << "4. Quan ly hoa don\n";
        std::cout << "5. Tim kiem\n";
        std::cout << "6. Thong ke\n";
        std::cout << "7. Cap quyen staff\n";
        std::cout << "0. Dang xuat\n";
        std::cout << "Chon: " << std::flush;

        int c;
        if (!(std::cin >> c)) {
            std::cin.clear();
            std::string tmp; std::getline(std::cin, tmp);
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

            case 7:
            promoteToStaff();
            break;

            case 0:
            saveAll();
            currentRole = -1;
            currentUsername = "";
            currentCccd = "";
            break;

            default:
            std::cout << "Noi dung nhap khong hop le vui long nhap lai.\n";
        }
    }
}

//Tự động sinh mã phòng
std::string HotelManager::generateNextRoomId() {
    int maxNum = 0;

    for (const auto &r : rooms) {
        std::string id = r.getRoomId();
        // Định dạng mã phòng = R## 
        if (id.length() > 1 && id[0] == 'R') {
            try {
                int num = std::stoi(id.substr(1));
                if (num > maxNum) {
                    maxNum = num;
                }
            } catch (...) {
                
            }
        }
    }

    
    maxNum++;
    std::ostringstream oss;
    oss << "R" << std::setfill('0') << std::setw(3) << maxNum;
    return oss.str();
}

// Tự động sinh id hoá đơn
std::string HotelManager::generateNextInvoiceId() {
    int maxNum = 0;

    for (const auto &inv : invoices) {
        std::string id = inv.getInvoiceId();
        // id hoá hơn = INV##
        if (id.length() > 3 && id.substr(0, 3) == "INV") {
            try {
                int num = std::stoi(id.substr(3));
                if (num > maxNum) {
                    maxNum = num;
                }
            } catch (...) {
                
            }
        }
    }

    
    maxNum++;
    std::ostringstream oss;
    oss << "INV" << std::setfill('0') << std::setw(3) << maxNum;
    return oss.str();
}


void HotelManager::reorderRoomIds() {
    if (rooms.empty()) return;

    //Sắp xếp lại các phòng theo mã phòng
    std::sort(rooms.begin(), rooms.end(), [](const Room &a, const Room &b) {
        return a.getRoomId() < b.getRoomId();
    });

    //Gán lại mã phòng theo thứ tự
    for (int i = 0; i < rooms.size(); ++i) {
        std::ostringstream oss;
        oss << "R" << std::setfill('0') << std::setw(3) << (i + 1);
        std::string newId = oss.str();
        std::string oldId = rooms[i].getRoomId();

        // Nếu mã phòng thay đổi thì cập nhật lại mã phòng trong hoá đơn
        if (oldId != newId) {
            
            updateInvoiceRoomReferences(oldId, newId);
            // Cập nhật lại mã phòng
            rooms[i].setRoomId(newId);
        }
    }

    saveRooms();
    saveInvoices();
}


void HotelManager::reorderInvoiceIds() {
    if (invoices.empty()) return;

    //Sắp xếp lại các hoá đơn theo mã hoá đơn
    std::sort(invoices.begin(), invoices.end(), [](const Invoice &a, const Invoice &b) {
        return a.getInvoiceId() < b.getInvoiceId();
    });

    //Gán lại mã hoá đơn theo thứ tự
    for (int i = 0; i < invoices.size(); ++i) {
        std::ostringstream oss;
        oss << "INV" << std::setfill('0') << std::setw(3) << (i + 1);
        std::string newId = oss.str();
        invoices[i].setInvoiceId(newId);
    }

    saveInvoices();
}

// Cập nhật lại mã phòng trong hoá đơn
void HotelManager::updateInvoiceRoomReferences(const std::string &oldRoomId, const std::string &newRoomId) {
    for (auto &inv : invoices) {
        if (inv.getRoomId() == oldRoomId) {
            inv.setRoomId(newRoomId);
        }
    }
}

void HotelManager::setCurrentUser(const std::string &username, int role, const std::string &cccd) {
    currentUsername = username;
    currentRole = role;
    currentCccd = cccd;
}

std::string HotelManager::getCurrentUsername() const {
    return currentUsername;
}

int HotelManager::getCurrentRole() const {
    return currentRole;
}

std::string HotelManager::getCurrentCccd() const {
    return currentCccd;
}

bool HotelManager::isAdmin() const {
    return currentRole == 0;
}

bool HotelManager::isStaff() const {
    return currentRole == 1;
}

bool HotelManager::isCustomer() const {
    return currentRole == 2;
}

void HotelManager::homeMenu() {
    clearScreen();

    while (currentRole == -1) {
        std::cout << "\n=== QUAN LY HOTEL MINI ===\n";
        std::cout << "1. Dang nhap\n";
        std::cout << "2. Dang ky\n";
        std::cout << "3. Doi mat khau\n";
        std::cout << "4. Quen mat khau\n";
        std::cout << "0. Thoat chuong trinh\n";
        std::cout << "Chon: " << std::flush;

        int c;
        if (!(std::cin >> c)) {
            std::cin.clear();
            std::string tmp; std::getline(std::cin, tmp);
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (c == 1) {
            // Login
            std::string username, password;
            std::cout << "Nhap ten dang nhap: " << std::flush;
            std::getline(std::cin, username);
            std::cout << "Nhap mat khau: " << std::flush;
            std::getline(std::cin, password);

            int role;
            std::string cccd;
            if (authManager.login(username, password, role, cccd)) {
                setCurrentUser(username, role, cccd);
                std::cout << "Dang nhap thanh cong!\n";
                std::cout << "Nhan Enter de tiep tuc..." << std::flush;
                std::cin.ignore();
            } else {
                std::cout << "Ten dang nhap hoac mat khau khong dung.\n";
                std::cout << "Nhan Enter de tiep tuc..." << std::flush;
                std::cin.ignore();
            }
        }

        else if (c == 2) {
            // Register
            std::string username, password, cccd;
            std::cout << "Nhap ten dang nhap: " << std::flush;
            std::getline(std::cin, username);

            if (authManager.accountExists(username)) {
                std::cout << "Ten dang nhap da ton tai.\n";
                std::cout << "Nhan Enter de tiep tuc..." << std::flush;
                std::cin.ignore();
                continue;
            }

            std::cout << "Nhap mat khau: " << std::flush;
            std::getline(std::cin, password);
            std::cout << "Nhap CCCD: " << std::flush;
            std::getline(std::cin, cccd);

            bool isEmployee = findEmployeeByCccd(cccd) != nullptr;
            bool isCustomer = customerExists(cccd);

            if (!isEmployee && !isCustomer) {
                std::cout << "CCCD khong ton tai trong he thong.\n";
                std::cout << "Nhan Enter de tiep tuc..." << std::flush;
                std::cin.ignore();
                continue;
            }

            int role = isEmployee ? 1 : 2;

            if (authManager.registerCustomer(username, password, cccd, role)) {
                if (isEmployee) {
                    std::cout << "CCCD la nhan vien. Tai khoan duoc tao voi quyen Staff.\n";
                } else {
                    std::cout << "Dang ky thanh cong! Vui long dang nhap.\n";
                }
                std::cout << "Nhan Enter de tiep tuc..." << std::flush;
                std::cin.ignore();
            } else {
                std::cout << "Dang ky that bai.\n";
                std::cout << "Nhan Enter de tiep tuc..." << std::flush;
                std::cin.ignore();
            }
        }

        else if (c == 3) {
            // Change password (not for admin)
            std::cout << "Vui long dang nhap truoc.\n";
            std::cout << "Nhan Enter de tiep tuc..." << std::flush;
            std::cin.ignore();
        }

        else if (c == 4) {
            // Forgot password (not for admin)
            std::cout << "Vui long dang nhap truoc.\n";
            std::cout << "Nhan Enter de tiep tuc..." << std::flush;
            std::cin.ignore();
        }

        else if (c == 0) {
            exit(0);
        }

        else {
            std::cout << "Noi dung nhap khong hop le.\n";
        }
    }
}

void HotelManager::staffMainMenu() {
    clearScreen();

    while (currentRole == 1) {
        std::cout << "\n=== MENU NHAN VIEN ===\n";
        std::cout << "Xin chao: " << currentUsername << "\n";
        std::cout << "1. Quan ly khach hang\n";
        std::cout << "2. Quan ly hoa don\n";
        std::cout << "3. Doi mat khau\n";
        std::cout << "4. Quen mat khau\n";
        std::cout << "0. Dang xuat\n";
        std::cout << "Chon: " << std::flush;

        int c;
        if (!(std::cin >> c)) {
            std::cin.clear();
            std::string tmp; std::getline(std::cin, tmp);
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (c == 1) {
            customerMenu();
        } else if (c == 2) {
            invoiceMenu();
        } else if (c == 3) {
            // Change password
            std::string oldPass, newPass;
            std::cout << "Nhap mat khau cu: " << std::flush;
            std::getline(std::cin, oldPass);
            std::cout << "Nhap mat khau moi: " << std::flush;
            std::getline(std::cin, newPass);

            if (authManager.changePassword(currentUsername, oldPass, newPass)) {
                std::cout << "Doi mat khau thanh cong!\n";
            } else {
                std::cout << "Mat khau cu khong dung.\n";
            }
            std::cout << "Nhan Enter de tiep tuc..." << std::flush;
            std::cin.ignore();
        } else if (c == 4) {
            // Forgot password
            std::string cccd;
            std::cout << "Nhap CCCD: " << std::flush;
            std::getline(std::cin, cccd);

            if (authManager.forgotPassword(currentUsername, cccd)) {
                std::cout << "Mat khau da duoc dat lai thanh ten dang nhap.\n";
            } else {
                std::cout << "CCCD khong khop.\n";
            }
            std::cout << "Nhan Enter de tiep tuc..." << std::flush;
            std::cin.ignore();
        } else if (c == 0) {
            currentRole = -1;
            currentUsername = "";
            currentCccd = "";
        } else {
            std::cout << "Noi dung nhap khong hop le.\n";
        }
    }
}

void HotelManager::customerMainMenu() {
    clearScreen();

    while (currentRole == 2) {
        std::cout << "\n=== MENU KHACH HANG ===\n";
        std::cout << "Xin chao: " << currentUsername << "\n";
        std::cout << "1. Xem thong tin ca nhan\n";
        std::cout << "2. Xem hoa don\n";
        std::cout << "3. Doi mat khau\n";
        std::cout << "4. Quen mat khau\n";
        std::cout << "0. Dang xuat\n";
        std::cout << "Chon: " << std::flush;

        int c;
        if (!(std::cin >> c)) {
            std::cin.clear();
            std::string tmp; std::getline(std::cin, tmp);
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (c == 1) {
            viewCustomerInfo();
        } else if (c == 2) {
            viewCustomerInvoices();
        } else if (c == 3) {
            // Change password
            std::string oldPass, newPass;
            std::cout << "Nhap mat khau cu: " << std::flush;
            std::getline(std::cin, oldPass);
            std::cout << "Nhap mat khau moi: " << std::flush;
            std::getline(std::cin, newPass);

            if (authManager.changePassword(currentUsername, oldPass, newPass)) {
                std::cout << "Doi mat khau thanh cong!\n";
            } else {
                std::cout << "Mat khau cu khong dung.\n";
            }
            std::cout << "Nhan Enter de tiep tuc..." << std::flush;
            std::cin.ignore();
        } else if (c == 4) {
            // Forgot password
            std::string cccd;
            std::cout << "Nhap CCCD: " << std::flush;
            std::getline(std::cin, cccd);

            if (authManager.forgotPassword(currentUsername, cccd)) {
                std::cout << "Mat khau da duoc dat lai thanh ten dang nhap.\n";
            } else {
                std::cout << "CCCD khong khop.\n";
            }
            std::cout << "Nhan Enter de tiep tuc..." << std::flush;
            std::cin.ignore();
        } else if (c == 0) {
            currentRole = -1;
            currentUsername = "";
            currentCccd = "";
        } else {
            std::cout << "Noi dung nhap khong hop le.\n";
        }
    }
}

void HotelManager::viewCustomerInfo() {
    clearScreen();
    std::cout << "\n---- THONG TIN CA NHAN ----\n\n";

    Customer* cust = findCustomerByCccd(currentCccd);
    if (cust) {
        std::cout << "CCCD: " << cust->getCccd() << "\n";
        std::cout << "Ho Ten: " << cust->getName() << "\n";
        std::cout << "Dien Thoai: " << cust->getPhone() << "\n";
        std::cout << "Email: " << cust->getEmail() << "\n";
        std::cout << "Ngay Sinh: " << cust->getBirthdate() << "\n";
        std::cout << "Dia Chi: " << cust->getAddress() << "\n";
    } else {
        std::cout << "Khong tim thay thong tin khach hang.\n";
    }

    std::cout << "\nNhan Enter de tiep tuc..." << std::flush;
    std::cin.ignore();
}

void HotelManager::viewCustomerInvoices() {
    clearScreen();
    std::cout << "\n---- HOA DON CUA BAN ----\n\n";

    bool found = false;

    
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
        if (inv.getCustomerCccd() == currentCccd) {
            std::cout << "| " << std::left << std::setw(10) << inv.getInvoiceId()
                    << " | " << std::left << std::setw(10) << inv.getCustomerCccd()
                    << " | " << std::left << std::setw(10) << inv.getEmployeeCccd()
                    << " | " << std::left << std::setw(8) << inv.getRoomId()
                    << " | " << std::left << std::setw(10) << inv.getDateFrom()
                    << " | " << std::left << std::setw(10) << inv.getDateTo()
                    << " | $" << std::right << std::setw(12) << std::fixed << std::setprecision(2) << inv.getTotal()
                    << " |\n";
            found = true;
        }
    }

    std::cout << "+" << std::string(12, '-') << "+" << std::string(12, '-') << "+"
            << std::string(12, '-') << "+" << std::string(10, '-') << "+"
            << std::string(12, '-') << "+" << std::string(12, '-') << "+"
            << std::string(15, '-') << "+\n\n";

    if (!found) {
        std::cout << "Ban khong co hoa don nao.\n\n";
    }

    std::cout << "Nhan Enter de tiep tuc..." << std::flush;
    std::cin.ignore();
}

void HotelManager::promoteToStaff() {
    clearScreen();
    std::cout << "\n---- CAP QUYEN STAFF ----\n\n";

    auto customers = authManager.getCustomerAccounts();

    if (customers.empty()) {
        std::cout << "Khong co tai khoan khach hang de cap quyen.\n";
        std::cout << "Nhan Enter de tiep tuc..." << std::flush;
        std::cin.ignore();
        return;
    }

    std::cout << "Danh sach tai khoan khach hang:\n\n";
    for (int i = 0; i < customers.size(); ++i) {
        std::cout << i + 1 << ". " << customers[i].getUsername()
                << " (CCCD: " << customers[i].getCccd() << ")\n";
    }

    std::cout << "\nChon tai khoan de cap quyen (0 de huy): " << std::flush;
    int choice;
    if (!(std::cin >> choice) || choice < 0 || choice > customers.size()) {
        std::cin.clear();
        std::string tmp; std::getline(std::cin, tmp);
        std::cout << "Lua chon khong hop le.\n";
        std::cout << "Nhan Enter de tiep tuc..." << std::flush;
        std::cin.ignore();
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 0) {
        return;
    }

    std::string username = customers[choice - 1].getUsername();
    std::string cccd = customers[choice - 1].getCccd();

    // Kiểm tra xem CCCD có tồn tại trong danh sách nhân viên hay không
    if (!findEmployeeByCccd(cccd)) {
        std::cout << "CCCD khong ton tai trong danh sach nhan vien.\n";
        std::cout << "Nhan Enter de tiep tuc..." << std::flush;
        std::cin.ignore();
        return;
    }

    if (authManager.promoteToStaff(username)) {
        std::cout << "Cap quyen thanh cong! " << username << " da tro thanh nhan vien.\n";
    } else {
        std::cout << "Cap quyen that bai.\n";
    }

    std::cout << "Nhan Enter de tiep tuc..." << std::flush;
    std::cin.ignore();
}
