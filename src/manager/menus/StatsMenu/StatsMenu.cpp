#include "../../HotelManager.h"
#include "../../../utils/DateUtils/DateUtils.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <vector>


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
        std::cout << i+1 << ". CCCD: " << arr[i].first << " | Tong: " << arr[i].second << "\n";
    }

}

void HotelManager::statsMenu() {
    clearScreen();

    while (true) {
        std::cout << "\n-- THONG KE --\n";
        std::cout << "1. Tong doanh thu\n";
        std::cout << "2. Doanh thu theo khoang ngay\n";
        std::cout << "3. Top khach chi nhieu\n";
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
            std::cout << "Tong doanh thu: " << totalRevenue() << "\n";
        } 
        
        else if (c == 2) {
            std::string f, t;
            std::cout << "Nhap tu ngay (YYYY-MM-DD): " << std::flush;
            std::getline(std::cin, f);
            std::cout << "Nhap den ngay (YYYY-MM-DD): " << std::flush;
            std::getline(std::cin, t);
            std::cout << "Doanh thu: " << revenueInRange(f,t) << "\n";
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
        else if (c == 0) break;
        
        else std::cout << "Noi dung nhap khong hop le.\n";
    }
}

