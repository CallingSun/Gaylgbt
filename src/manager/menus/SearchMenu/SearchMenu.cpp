#include "../../HotelManager.h"
#include "../../../utils/DateUtils/DateUtils.h"
#include <iostream>
#include <limits>
#include <iomanip>


void HotelManager::searchCustomerByName(const std::string &keyword) const {
    std::cout << "Ket qua tim kiem khach theo ten: " << keyword << "\n";

    for (const auto &c : customers) {
        if (c.getName().find(keyword) != std::string::npos) {
            std::cout << c.toCSV() << "\n";
        }
    }
}

void HotelManager::searchCustomerByBirthdate(const std::string &date) const {
    std::cout << "\n---- KET QUA TIM KIEM KHACH THEO NGAY SINH: " << date << " ----\n\n";

    bool found = false;

    std::cout << "+" << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(12, '-') << "+" << std::string(20, '-') << "+\n";

    std::cout << "| " << std::left << std::setw(10) << "CCCD"
            << " | " << std::left << std::setw(18) << "Ho Ten"
            << " | " << std::left << std::setw(10) << "Dien Thoai"
            << " | " << std::left << std::setw(18) << "Email"
            << " | " << std::left << std::setw(10) << "Ngay Sinh"
            << " | " << std::left << std::setw(18) << "Dia Chi"
            << " |\n";

    std::cout << "+" << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(12, '-') << "+" << std::string(20, '-') << "+\n";

    for (const auto &c : customers) {
        if (c.getBirthdate() == date) {
            std::cout << "| " << std::left << std::setw(10) << c.getCccd()
                    << " | " << std::left << std::setw(18) << c.getName()
                    << " | " << std::left << std::setw(10) << c.getPhone()
                    << " | " << std::left << std::setw(18) << c.getEmail()
                    << " | " << std::left << std::setw(10) << c.getBirthdate()
                    << " | " << std::left << std::setw(18) << c.getAddress()
                    << " |\n";
            found = true;
        }
    }

    std::cout << "+" << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(12, '-') << "+" << std::string(20, '-') << "+\n\n";

    if (!found) {
        std::cout << "Khong tim thay khach hang co ngay sinh: " << date << "\n\n";
    }
}

void HotelManager::searchCustomerByBirthdateRange(const std::string &fromDate, const std::string &toDate) const {
    std::cout << "\n---- KET QUA TIM KIEM KHACH THEO KHOANG NGAY SINH: " << fromDate << " - " << toDate << " ----\n\n";

    Date from = Date::fromString(fromDate);
    Date to = Date::fromString(toDate);
    bool found = false;

    std::cout << "+" << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(12, '-') << "+" << std::string(20, '-') << "+\n";

    std::cout << "| " << std::left << std::setw(10) << "CCCD"
            << " | " << std::left << std::setw(18) << "Ho Ten"
            << " | " << std::left << std::setw(10) << "Dien Thoai"
            << " | " << std::left << std::setw(18) << "Email"
            << " | " << std::left << std::setw(10) << "Ngay Sinh"
            << " | " << std::left << std::setw(18) << "Dia Chi"
            << " |\n";

    std::cout << "+" << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(12, '-') << "+" << std::string(20, '-') << "+\n";

    for (const auto &c : customers) {
        Date birthDate = Date::fromString(c.getBirthdate());
        if (!(birthDate < from) && !(to < birthDate)) {
            std::cout << "| " << std::left << std::setw(10) << c.getCccd()
                    << " | " << std::left << std::setw(18) << c.getName()
                    << " | " << std::left << std::setw(10) << c.getPhone()
                    << " | " << std::left << std::setw(18) << c.getEmail()
                    << " | " << std::left << std::setw(10) << c.getBirthdate()
                    << " | " << std::left << std::setw(18) << c.getAddress()
                    << " |\n";
            found = true;
        }
    }

    std::cout << "+" << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(12, '-') << "+" << std::string(20, '-') << "+\n\n";

    if (!found) {
        std::cout << "Khong tim thay khach hang trong khoang ngay sinh: " << fromDate << " - " << toDate << "\n\n";
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

void HotelManager::searchInvoiceByCheckInDate(const std::string &date) const {
    std::cout << "\n---- KET QUA TIM KIEM HOA DON THEO NGAY NHAN: " << date << " ----\n\n";

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
        if (inv.getDateFrom() == date) {
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
        std::cout << "Khong tim thay hoa don co ngay nhan: " << date << "\n\n";
    }
}

void HotelManager::searchInvoiceByCheckOutDate(const std::string &date) const {
    std::cout << "\n---- KET QUA TIM KIEM HOA DON THEO NGAY TRA: " << date << " ----\n\n";

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
        if (inv.getDateTo() == date) {
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
        std::cout << "Khong tim thay hoa don co ngay tra: " << date << "\n\n";
    }
}

void HotelManager::searchInvoiceByDateRange(const std::string &fromDate, const std::string &toDate) const {
    std::cout << "\n---- KET QUA TIM KIEM HOA DON TRONG KHOANG NGAY: " << fromDate << " - " << toDate << " ----\n\n";

    Date from = Date::fromString(fromDate);
    Date to = Date::fromString(toDate);
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
        Date checkIn = Date::fromString(inv.getDateFrom());
        Date checkOut = Date::fromString(inv.getDateTo());

        if (!(checkOut < from) && !(to < checkIn)) {
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
        std::cout << "Khong tim thay hoa don trong khoang ngay: " << fromDate << " - " << toDate << "\n\n";
    }
}

void HotelManager::searchMenu() {
    clearScreen();

    while (true) {
        std::cout << "\n-- TIM KIEM --\n";
        std::cout << "1. Tim khach theo ten\n";
        std::cout << "2. Tim khach theo ngay sinh\n";
        std::cout << "3. Tim khach theo khoang ngay sinh\n";
        std::cout << "4. Tim phong theo ma\n";
        std::cout << "5. Tim hoa don theo ma\n";
        std::cout << "6. Tim hoa don theo ngay nhan\n";
        std::cout << "7. Tim hoa don theo ngay tra\n";
        std::cout << "8. Tim hoa don theo khoang ngay\n";
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
            std::string date = getValidatedDateInput();
            searchCustomerByBirthdate(date);
        }

        else if (c == 3) {
            std::string fromDate = getValidatedDateInput();
            std::cout << "Nhap den ngay: " << std::flush;
            std::string toDate = getValidatedDateInput();
            searchCustomerByBirthdateRange(fromDate, toDate);
        }

        else if (c == 4) {
            std::string roomId;
            std::cout << "Nhap ma phong: " << std::flush;
            std::getline(std::cin, roomId);
            searchRoomById(roomId);
        }

        else if (c == 5) {
            std::string invId;
            std::cout << "Nhap ma hoa don: " << std::flush;
            std::getline(std::cin, invId);
            searchInvoiceById(invId);
        }

        else if (c == 6) {
            std::string date = getValidatedDateInput();
            searchInvoiceByCheckInDate(date);
        }

        else if (c == 7) {
            std::string date = getValidatedDateInput();
            searchInvoiceByCheckOutDate(date);
        }

        else if (c == 8) {
            std::string fromDate = getValidatedDateInput();
            std::cout << "Nhap den ngay: " << std::flush;
            std::string toDate = getValidatedDateInput();
            searchInvoiceByDateRange(fromDate, toDate);
        }

        else if (c == 0) break;

        else std::cout << "Noi dung nhap khong hop le.\n";
    }
}

