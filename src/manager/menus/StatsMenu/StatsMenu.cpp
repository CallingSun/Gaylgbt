#include "../../HotelManager.h"
#include "../../../utils/DateUtils/DateUtils.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <iomanip>


double HotelManager::totalRevenue() const {
    double s = 0.0;
    
    for (const auto &inv : invoices) {
        s += inv.getTotal();
    }

    return s;
}

double HotelManager::revenueInRange(const std::string &from, const std::string &to) const {
    Date df = Date::fromString(from);
    
    Date dt = Date::fromString(to);
    
    double s = 0.0;
    
    for (const auto &inv : invoices) {
        Date ifrom = Date::fromString(inv.getDateFrom());
        Date ito   = Date::fromString(inv.getDateTo());

        if (!(ito < df) && !(dt < ifrom)) {
            s += inv.getTotal();
        }
    }

    return s;
}

void HotelManager::topCustomers(int n) const {
    std::unordered_map<std::string, double> spend;

    for (const auto &inv : invoices) {
        spend[inv.getCustomerCccd()] += inv.getTotal();
    }

    std::vector<std::pair<std::string, double>> arr(spend.begin(), spend.end());

    std::sort(arr.begin(), arr.end(), [](const auto &a, const auto &b){
        return a.second > b.second;
        }
    );

    std::cout << "Top " << n << " khach chi tieu nhieu nhat:\n";

    for (int i = 0; i < (int)arr.size() && i < n; ++i) {
        std::cout << i+1 << ". CCCD: " << arr[i].first << " | Tong: $" << arr[i].second << " USD\n";
    }

}

void HotelManager::employeeInvoiceCount() const {
    if (employees.empty()) {
        std::cout << "Khong co nhan vien nao.\n";
        return;
    }

    std::cout << "\n---- THONG KE SO HOA DON THEO NHAN VIEN ----\n\n";

    std::unordered_map<std::string, int> invoiceCount;

    for (const auto &inv : invoices) {
        invoiceCount[inv.getEmployeeCccd()]++;
    }

    std::vector<std::pair<const Employee*, int>> employeeStats;

    for (const auto &emp : employees) {
        int count = invoiceCount[emp.getCccd()];
        employeeStats.push_back({&emp, count});
    }

    std::sort(employeeStats.begin(), employeeStats.end(), [](const auto &a, const auto &b){
        return a.second > b.second;
    });

    std::cout << "+" << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(15, '-') << "+" << std::string(15, '-') << "+\n";

    std::cout << "| " << std::left << std::setw(10) << "CCCD"
            << " | " << std::left << std::setw(18) << "Ho Ten"
            << " | " << std::left << std::setw(13) << "Chuc Vu"
            << " | " << std::right << std::setw(13) << "So Hoa Don"
            << " |\n";

    std::cout << "+" << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(15, '-') << "+" << std::string(15, '-') << "+\n";

    for (const auto &stat : employeeStats) {
        std::cout << "| " << std::left << std::setw(10) << stat.first->getCccd()
                << " | " << std::left << std::setw(18) << stat.first->getName()
                << " | " << std::left << std::setw(13) << stat.first->getPosition()
                << " | " << std::right << std::setw(13) << stat.second
                << " |\n";
    }

    std::cout << "+" << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(15, '-') << "+" << std::string(15, '-') << "+\n\n";
}

void HotelManager::topEmployeesBySalary(int n) const {
    if (employees.empty()) {
        std::cout << "Khong co nhan vien nao.\n";
        return;
    }

    std::cout << "\n---- TOP NHAN VIEN THEO LUONG ----\n\n";

    std::vector<const Employee*> empList;

    for (const auto &emp : employees) {
        empList.push_back(&emp);
    }

    // Sắp xếp danh sách nhân viên theo lương giảm dần
    std::sort(empList.begin(), empList.end(), [](const auto &a, const auto &b){
        return a->getSalary() > b->getSalary();
    });

    std::cout << "+" << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(15, '-') << "+" << std::string(15, '-') << "+\n";

    std::cout << "| " << std::left << std::setw(10) << "CCCD"
            << " | " << std::left << std::setw(18) << "Ho Ten"
            << " | " << std::left << std::setw(13) << "Chuc Vu"
            << " | " << std::right << std::setw(13) << "Luong (USD)"
            << " |\n";

    std::cout << "+" << std::string(12, '-') << "+" << std::string(20, '-') << "+"
              << std::string(15, '-') << "+" << std::string(15, '-') << "+\n";

    for (int i = 0; i < (int)empList.size() && i < n; ++i) {
        std::cout << "| " << std::left << std::setw(10) << empList[i]->getCccd()
                << " | " << std::left << std::setw(18) << empList[i]->getName()
                << " | " << std::left << std::setw(13) << empList[i]->getPosition()
                << " | $" << std::right << std::setw(11) << std::fixed << std::setprecision(2) << empList[i]->getSalary()
                << " |\n";
    }

    
    std::cout << "+" << std::string(12, '-') << "+" << std::string(20, '-') << "+"
            << std::string(15, '-') << "+" << std::string(15, '-') << "+\n\n";
}

void HotelManager::statsMenu() {
    clearScreen();

    while (true) {
        std::cout << "\n-- THONG KE --\n";
        std::cout << "1. Tong doanh thu\n";
        std::cout << "2. Doanh thu theo khoang ngay\n";
        std::cout << "3. Top khach chi nhieu\n";
        std::cout << "4. So hoa don theo nhan vien\n";
        std::cout << "5. Top nhan vien theo luong\n";
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
            std::cout << "Tong doanh thu: $" << totalRevenue() << " USD\n";
        }

        else if (c == 2) {
            std::string f, t;
            std::cout << "Nhap tu ngay: " << std::flush;
            f = getValidatedDateInput();
            std::cout << "Nhap den ngay: " << std::flush;
            t = getValidatedDateInput();
            std::cout << "Doanh thu: $" << revenueInRange(f,t) << " USD\n";
        }

        else if (c == 3) {
            std::cout << "Nhap so luong top: " << std::flush;
            int n;
            if (!(std::cin >> n)) {
                std::cin.clear();
                std::string tmp; std::getline(std::cin,tmp);
                continue;
            }
            topCustomers(n);
        }

        else if (c == 4) {
            employeeInvoiceCount();
        }

        else if (c == 5) {
            std::cout << "Nhap so luong nhan vien: " << std::flush;
            int n;
            if (!(std::cin >> n)) {
                std::cin.clear();
                std::string tmp; std::getline(std::cin,tmp);
                continue;
            }
            topEmployeesBySalary(n);
        }

        else if (c == 0) break;

        else std::cout << "Noi dung nhap khong hop le.\n";
    }
}

