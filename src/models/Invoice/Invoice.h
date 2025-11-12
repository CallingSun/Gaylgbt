#ifndef INVOICE_H
#define INVOICE_H

#include <string>

class Invoice {
private:
    std::string invoiceId;
    std::string customerCccd;
    std::string employeeCccd;
    std::string roomId;
    std::string dateFrom;
    std::string dateTo;

    double total = 0.0;//set tottal

public:
    Invoice() = default;
    Invoice(const std::string &invoiceId,
            const std::string &customerCccd,
            const std::string &employeeCccd,
            const std::string &roomId,
            const std::string &dateFrom,
            const std::string &dateTo,
            double total);

    std::string getInvoiceId() const;
    void setInvoiceId(const std::string &id);

    std::string getCustomerCccd() const;
    void setCustomerCccd(const std::string &cccd);

    std::string getEmployeeCccd() const;
    void setEmployeeCccd(const std::string &cccd);

    std::string getRoomId() const;
    void setRoomId(const std::string &id);

    std::string getDateFrom() const;
    void setDateFrom(const std::string &date);

    std::string getDateTo() const;
    void setDateTo(const std::string &date);

    double getTotal() const;
    void setTotal(double amount);

    std::string toCSV() const;

    void fromCSV(const std::string &line);
};

#endif
