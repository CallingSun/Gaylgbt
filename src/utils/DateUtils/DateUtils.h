#ifndef DATE_UTILS_H
#define DATE_UTILS_H

#include <string>

struct Date {
    int y = 0;
    int m = 0;
    int d = 0;
    //Khới tạo y,m,d =0

    static Date fromString(const std::string &s);

    std::string toString() const;
    bool operator<(const Date &o) const;
    bool operator==(const Date &o) const;
};

int nightsBetween(const std::string &fromS, const std::string &toS);

//Gọi các hàm ngày tháng
bool isLeapYear(int year);
int getDaysInMonth(int month, int year);
bool isValidDateFormat(const std::string &s);
bool isValidDate(int year, int month, int day);
std::string getValidatedDateInput();
std::string getValidatedDateInputOptional();

#endif
