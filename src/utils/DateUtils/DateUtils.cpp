#include "DateUtils.h"
#include <ctime>
#include <fstream>
#include <cstdio>
#include <algorithm>

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
