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
    std::string getType() const;
    double getPrice() const;
    bool isAvailable() const;

    void setAvailable(bool value);

    std::string toCSV() const;
    void fromCSV(const std::string &line);
};

#endif
