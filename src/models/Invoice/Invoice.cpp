#include "Invoice.h"
#include <sstream>
#include <limits>
#include <fstream>

Invoice::Invoice(const std::string &invoiceId,
                const std::string &customerCccd,
                const std::string &roomId,
                const std::string &dateFrom,
                const std::string &dateTo,
                double total)
    : invoiceId(invoiceId),
    customerCccd(customerCccd),
    roomId(roomId),
    dateFrom(dateFrom),
    dateTo(dateTo),
    total(total) {

    }

std::string Invoice::getInvoiceId() const {
    return invoiceId; 
}

std::string Invoice::getCustomerCccd() const {
    return customerCccd; 
}

std::string Invoice::getRoomId() const {
    return roomId; 
}

std::string Invoice::getDateFrom() const {
    return dateFrom; 
}

std::string Invoice::getDateTo() const {
    return dateTo; 
}

double Invoice::getTotal() const {
    return total; 
}

std::string Invoice::toCSV() const {
    std::ostringstream oss;

    oss << invoiceId << "," << customerCccd << "," << roomId << "," << dateFrom << "," << dateTo << "," << total;
    
        return oss.str();
}

void Invoice::fromCSV(const std::string &line) {
    std::stringstream ss(line);
    std::string totalStr;
    std::getline(ss, invoiceId, ',');
    std::getline(ss, customerCccd, ',');
    std::getline(ss, roomId, ',');
    std::getline(ss, dateFrom, ',');
    std::getline(ss, dateTo, ',');
    std::getline(ss, totalStr, ',');
    
    try {
        total = std::stod(totalStr);
    } 
    catch (...) {
        total = 0.0;
    }
}
