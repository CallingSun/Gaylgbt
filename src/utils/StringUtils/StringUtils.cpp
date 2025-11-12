#include "StringUtils.h"
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cctype>
#include <limits>

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> out;

    std::string cur;

    std::stringstream ss(s);

    while (std::getline(ss, cur, delim)) {
        out.push_back(cur);
    }

    return out;
}

std::string trim(const std::string &s) {
    std::size_t a = s.find_first_not_of(" \t\r\n");

    if (a == std::string::npos) return "";

    std::size_t b = s.find_last_not_of(" \t\r\n");

    return s.substr(a, b - a + 1);
}

std::string getValidatedCccdInput() {
    std::string cccd;

    while (true) {
        std::cout << "Nhap CCCD (12 chu so): " << std::flush;
        std::getline(std::cin, cccd);


        cccd = trim(cccd);


        if (cccd.length() != 12) {
            std::cout << "CCCD khong hop le. Vui long nhap dung 12 chu so.\n";
            continue;
        }

        // Kiểm tra xem CCCD có phải là số không
        bool allDigits = true;
        for (char c : cccd) {
            if (!std::isdigit(c)) {
                allDigits = false;
                break;
            }
        }

        if (!allDigits) {
            std::cout << "CCCD khong hop le. Vui long nhap dung 12 chu so.\n";
            continue;
        }
        return cccd;
    }
}

std::string getValidatedCccdInputOptional() {
    std::string cccd;

    while (true) {
        std::cout << "Nhap CCCD moi (12 chu so, Enter de giu nguyen): " << std::flush;
        std::getline(std::cin, cccd);

        // Nếu bỏ trống cccd thì bỏ qua
        if (cccd.empty()) {
            return "";
        }

        cccd = trim(cccd);

        if (cccd.empty()) {
            return "";
        }

        // Kiểm tra độ dài xem đùng bằng 12 không
        if (cccd.length() != 12) {
            std::cout << "CCCD khong hop le. Vui long nhap dung 12 chu so.\n";
            continue;
        }

        // Kiểm tra xem CCCD có phải là số không
        bool allDigits = true;
        for (char c : cccd) {
            if (!std::isdigit(c)) {
                allDigits = false;
                break;
            }
        }

        if (!allDigits) {
            std::cout << "CCCD khong hop le. Vui long nhap dung 12 chu so.\n";
            continue;
        }

        return cccd;
    }
}

//Hàm tim giá phòng tối thiểu
double getMinimumPriceForRoomType(const std::string &roomType) {
    
    if (roomType == "Standard") return 20.0;
    if (roomType == "Superior") return 30.0;
    if (roomType == "Deluxe") return 40.0;
    if (roomType == "Family") return 50.0;
    if (roomType == "Double") return 25.0;
    if (roomType == "Suite") return 70.0;

    // Loại phòng không hợp lệ thì trả về 0.0
    return 0.0;
}


std::string getValidatedRoomTypeInput() {
    std::string type;
    const std::vector<std::string> validTypes = {"Standard", "Superior", "Deluxe", "Family", "Double", "Suite"};

    while (true) {
        std::cout << "Nhap loai phong (Standard/Superior/Deluxe/Family/Double/Suite): " << std::flush;
        std::getline(std::cin, type);

        type = trim(type);

        if (type.empty()) {
            std::cout << "Loai phong khong duoc de trong. Vui long nhap lai.\n";
            continue;
        }

        // Kiểm tra xem loại phòng có hợp lệ không
        bool isValid = false;
        for (const auto &validType : validTypes) {
            if (type == validType) {
                isValid = true;
                break;
            }
        }

        if (!isValid) {
            std::cout << "Loai phong khong hop le. Cac loai phong hop le: Standard, Superior, Deluxe, Family, Double, Suite.\n";
            continue;
        }

        return type;
    }
}


std::string getValidatedRoomTypeInputOptional() {
    std::string type;
    const std::vector<std::string> validTypes = {"Standard", "Superior", "Deluxe", "Family", "Double", "Suite"};

    while (true) {
        std::cout << "Nhap loai phong moi (Standard/Superior/Deluxe/Family/Double/Suite, Enter de giu nguyen): " << std::flush;
        std::getline(std::cin, type);

        if (type.empty()) {
            return "";
        }

        type = trim(type);

        if (type.empty()) {
            return "";
        }

        bool isValid = false;
        for (const auto &validType : validTypes) {
            if (type == validType) {
                isValid = true;
                break;
            }
        }

        if (!isValid) {
            std::cout << "Loai phong khong hop le. Cac loai phong hop le: Standard, Superior, Deluxe, Family, Double, Suite.\n";
            continue;
        }

        return type;
    }
}

double getValidatedRoomPriceInput(const std::string &roomType) {
    std::string priceStr;
    double minPrice = getMinimumPriceForRoomType(roomType);

    while (true) {
        std::cout << "Nhap gia/phong/dem (toi thieu $" << minPrice << " USD): " << std::flush;
        std::getline(std::cin, priceStr);

        
        priceStr = trim(priceStr);

        if (priceStr.empty()) {
            std::cout << "Gia khong duoc de trong. Vui long nhap lai.\n";
            continue;
        }

        double price = 0.0;
        try {
            price = std::stod(priceStr);
        } catch (...) {
            std::cout << "Gia khong hop le. Vui long nhap mot so.\n";
            continue;
        }

        // Kiem tra xem giá có lớn hơn giá tối thiểu không
        if (price < minPrice) {
            std::cout << "Gia khong hop le. Gia toi thieu cho loai phong " << roomType << " la $" << minPrice << " USD.\n";
            continue;
        }

        return price;
    }
}

double getValidatedRoomPriceInputOptional(const std::string &roomType) {
    std::string priceStr;
    double minPrice = getMinimumPriceForRoomType(roomType);

    while (true) {
        std::cout << "Nhap gia moi (toi thieu $" << minPrice << " USD, Enter de giu nguyen): " << std::flush;
        std::getline(std::cin, priceStr);

        // Nếu bỏ trống trả về -1
        if (priceStr.empty()) {
            return -1.0;
        }

        priceStr = trim(priceStr);

        if (priceStr.empty()) {
            return -1.0;
        }

        double price = 0.0;
        try {
            price = std::stod(priceStr);
        } catch (...) {
            std::cout << "Gia khong hop le. Vui long nhap mot so.\n";
            continue;
        }

        if (price < minPrice) {
            std::cout << "Gia khong hop le. Gia toi thieu cho loai phong " << roomType << " la $" << minPrice << " USD.\n";
            continue;
        }

        return price;
    }
}



std::string getValidatedPositionInput() {
    std::string position;
    const std::vector<std::string> validPositions = {"Receptionist", "Housekeeper", "Chef", "Manager"};

    while (true) {
        std::cout << "Nhap vi tri (Receptionist/Housekeeper/Chef/Manager): " << std::flush;
        std::getline(std::cin, position);

        position = trim(position);

        if (position.empty()) {
            std::cout << "Vi tri khong duoc de trong. Vui long nhap lai.\n";
            continue;
        }

        bool isValid = false;
        for (const auto &validPos : validPositions) {
            if (position == validPos) {
                isValid = true;
                break;
            }
        }

        if (!isValid) {
            std::cout << "Vi tri khong hop le. Cac vi tri hop le: Receptionist, Housekeeper, Chef, Manager.\n";
            continue;
        }

        return position;
    }
}


std::string getValidatedPositionInputOptional() {
    std::string position;
    const std::vector<std::string> validPositions = {"Receptionist", "Housekeeper", "Chef", "Manager"};

    while (true) {
        std::cout << "Nhap vi tri moi (Receptionist/Housekeeper/Chef/Manager, Enter de giu nguyen): " << std::flush;
        std::getline(std::cin, position);

        
        if (position.empty()) {
            return "";
        }

        position = trim(position);

        if (position.empty()) {
            return "";
        }

        bool isValid = false;
        for (const auto &validPos : validPositions) {
            if (position == validPos) {
                isValid = true;
                break;
            }
        }

        if (!isValid) {
            std::cout << "Vi tri khong hop le. Cac vi tri hop le: Receptionist, Housekeeper, Chef, Manager.\n";
            continue;
        }

        return position;
    }
}


int getValidatedQuantityInput() {
    int quantity;

    while (true) {
        std::cout << "Nhap so luong muon thuc hien: " << std::flush;

        if (!(std::cin >> quantity)) {
            std::cin.clear();
            std::string tmp;
            std::getline(std::cin, tmp);
            std::cout << "Vui long nhap mot so nguyen duong.\n";
            continue;
        }

        if (quantity < 1) {
            std::cout << "So luong phai lon hon hoac bang 1.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return quantity;
    }
}

void displayProgressIndicator(int current, int total, const std::string &action) {
    std::cout << "Dang " << action << " thu " << current << "/" << total << "...\n";
}

bool getConfirmation(const std::string &message) {
    std::string response;

    while (true) {
        std::cout << message << " (y/n): " << std::flush;
        std::getline(std::cin, response);

        response = trim(response);

        if (response.empty()) {
            std::cout << "Vui long nhap y hoac n.\n";
            continue;
        }

        if (response == "y" || response == "Y") {
            return true;
        } else if (response == "n" || response == "N") {
            return false;
        } else {
            std::cout << "Vui long nhap y hoac n.\n";
        }
    }
}