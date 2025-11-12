#include "Room.h"
#include <sstream>
#include <fstream>


Room::Room(const std::string &roomId,
        const std::string &type,
        double price,
        bool available)
    : roomId(roomId), type(type), price(price), available(available) {

    }

std::string Room::getRoomId() const {
    return roomId;
}

void Room::setRoomId(const std::string &id) {
    roomId = id;
}

std::string Room::getType() const {
    return type;
}

void Room::setType(const std::string &t) {
    type = t;
}

double Room::getPrice() const {
    return price;
}

void Room::setPrice(double p) {
    price = p;
}

bool Room::isAvailable() const {
    return available;
}

void Room::setAvailable(bool value) {
    available = value;
}

std::string Room::toCSV() const {
    std::ostringstream oss;
    oss << roomId << "," << type << "," << price << "," << (available ? 1 : 0);
    return oss.str();
}

void Room::fromCSV(const std::string &line) {
    std::stringstream ss(line);
    std::string priceStr, availableStr;
    std::getline(ss, roomId, ',');
    std::getline(ss, type, ',');
    std::getline(ss, priceStr, ',');
    std::getline(ss, availableStr, ',');
    
    try {
        price = std::stod(priceStr);
    } 
    catch (...) {
        price = 0.0;
    }

    available = (availableStr == "1");//Để giá trị khi phòng còn trống bằng 1
    //Khi khởi tạo phòng luôn có giá trị =1 chỉ khi được thêm vào hoá đơn mới chuyển thành 0
    //Và ngược lại
}
