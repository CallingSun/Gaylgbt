#ifndef INVOICE_H
#define INVOICE_H

#include <string>

class Invoice {
private:
    std::string invoiceId;
    std::string customerCccd; 
    std::string roomId;
    std::string dateFrom;
    std::string dateTo;
    
    double total = 0.0;//set tottal

public:
    Invoice() = default;
    Invoice(const std::string &invoiceId,
            const std::string &customerCccd,
            const std::string &roomId,
            const std::string &dateFrom,
            const std::string &dateTo,
            double total);

    std::string getInvoiceId() const;

    std::string getCustomerCccd() const;

    std::string getRoomId() const;

    std::string getDateFrom() const;

    std::string getDateTo() const;

    double getTotal() const;

    std::string toCSV() const;
    
    void fromCSV(const std::string &line);
};

#endif
