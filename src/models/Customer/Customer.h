#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "../Person/Person.h"//Kế thừa Person

class Customer : public Person {
private:
    std::string birthdate;
    std::string address;

public:
    Customer() = default;
    Customer(const std::string &cccd,
            const std::string &name,
            const std::string &phone,
            const std::string &email,
            const std::string &birthdate,
            const std::string &address);

    std::string getBirthdate() const;
    void setBirthdate(const std::string &date);

    std::string getAddress() const;
    void setAddress(const std::string &addr);

    std::string toCSV() const override;

    void fromCSV(const std::string &line) override;
};

#endif
