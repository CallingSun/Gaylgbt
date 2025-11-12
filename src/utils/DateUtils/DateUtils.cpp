#include "DateUtils.h"
#include <ctime>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <iostream>

Date Date::fromString(const std::string &s) {
    Date res;

    if (s.size() >= 10 && s[4]=='-' && s[7]=='-') {
        try {
            res.y = std::stoi(s.substr(0,4));
            res.m = std::stoi(s.substr(5,2));
            res.d = std::stoi(s.substr(8,2));
        } catch(...) {}
    }

    return res;
}

std::string Date::toString() const {
    char buf[16];

    std::sprintf(buf, "%04d-%02d-%02d", y, m, d);//Định dạng lại ngày tháng; năm 4 tháng 2 ngày 2 chữ số nếu thiếu tự động thêm số 0 ở đằng trước
    
    return std::string(buf);
}

bool Date::operator<(const Date &o) const {
    if (y != o.y) return y < o.y;
    if (m != o.m) return m < o.m;
    return d < o.d;
}

bool Date::operator==(const Date &o) const {
    return y == o.y && m == o.m && d == o.d;
}

int nightsBetween(const std::string &fromS, const std::string &toS) {
    Date f = Date::fromString(fromS);
    Date t = Date::fromString(toS);

    std::tm tmf = {};
    std::tm tmt = {};
    tmf.tm_year = f.y - 1900;
    tmf.tm_mon  = f.m - 1;
    tmf.tm_mday = f.d;

    tmt.tm_year = t.y - 1900;
    tmt.tm_mon  = t.m - 1;
    tmt.tm_mday = t.d;

    std::time_t tf = std::mktime(&tmf);
    std::time_t tt = std::mktime(&tmt);
    if (tf == (std::time_t)-1 || tt == (std::time_t)-1) return 0;

    double diff = std::difftime(tt, tf);
    int days = static_cast<int>(diff / (60*60*24));
    return std::max(0, days);
}//Biểu diên thuật toán đơn giản là quy tất cả ngày/tháng/năm về giây và sau đó chia cho 60*60*24(số giây trong 1 ngày) để ra số ngày

// Kiểm tra năm nhuận
bool isLeapYear(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

// Lấy số ngày trong tháng
int getDaysInMonth(int month, int year) {
    if (month < 1 || month > 12) return 0;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && isLeapYear(year)) {
        return 29;
    }

    return daysInMonth[month - 1];
}

// Kiểm tra định dạng ngày tháng xem đúng không
bool isValidDateFormat(const std::string &s) {
    if (s.length() != 10) return false;
    if (s[4] != '-' || s[7] != '-') return false;

    // Kiểm tra các ký tự khác dấu '-' phải là số
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (s[i] < '0' || s[i] > '9') return false;
    }

    return true;
}

// Kiểm tra ngày tháng xem hợp lệ không
bool isValidDate(int year, int month, int day) {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > getDaysInMonth(month, year)) return false;

    return true;
}

// Nhâp ngày tháng từ người dùng
std::string getValidatedDateInput() {
    std::string input;

    while (true) {
        std::cout << "Nhap ngay (dinh dang: YYYY-MM-DD, vi du: 2025-11-15): " << std::flush;
        std::getline(std::cin, input);

        if (!isValidDateFormat(input)) {
            std::cout << "Dinh dang ngay khong hop le. Vui long nhap theo dinh dang YYYY-MM-DD\n";
            continue;
        }

        try {
            int year = std::stoi(input.substr(0, 4));
            int month = std::stoi(input.substr(5, 2));
            int day = std::stoi(input.substr(8, 2));

            if (!isValidDate(year, month, day)) {
                std::cout << "Ngay khong hop le. Vui long kiem tra lai.\n";
                continue;
            }

            return input;
        } catch (...) {
            std::cout << "Dinh dang ngay khong hop le. Vui long nhap theo dinh dang YYYY-MM-DD\n";
        }
    }
}

std::string getValidatedDateInputOptional() {
    std::string input;

    while (true) {
        std::cout << "Nhap ngay (dinh dang: YYYY-MM-DD, vi du: 2025-11-15) hoac Enter de bo qua: " << std::flush;
        std::getline(std::cin, input);

        
        if (input.empty()) {
            return "";
        }

        if (!isValidDateFormat(input)) {
            std::cout << "Dinh dang ngay khong hop le. Vui long nhap theo dinh dang YYYY-MM-DD\n";
            continue;
        }

        try {
            int year = std::stoi(input.substr(0, 4));
            int month = std::stoi(input.substr(5, 2));
            int day = std::stoi(input.substr(8, 2));

            if (!isValidDate(year, month, day)) {
                std::cout << "Ngay khong hop le. Vui long kiem tra lai.\n";
                continue;
            }

            return input;
        } catch (...) {
            std::cout << "Dinh dang ngay khong hop le. Vui long nhap theo dinh dang YYYY-MM-DD\n";
        }
    }
}
