#ifndef ROOM_H
#define ROOM_H

#include <string>

class Room {
private:
    std::string roomId;     
    std::string type;       
    double price = 0.0;
    bool available = true;

public:
    Room() = default;
    Room(const std::string &roomId,
        const std::string &type,
        double price,
        bool available);

    std::string getRoomId() const;
    void setRoomId(const std::string &id);
    std::string getType() const;
    void setType(const std::string &t);
    double getPrice() const;
    void setPrice(double p);
    bool isAvailable() const;

    void setAvailable(bool value);

    std::string toCSV() const;
    void fromCSV(const std::string &line);
};

#endif
