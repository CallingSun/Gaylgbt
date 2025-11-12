#include "Invoice.h"
#include <sstream>
#include <limits>
#include <fstream>

Invoice::Invoice(const std::string &invoiceId,
                const std::string &customerCccd,
                const std::string &employeeCccd,
                const std::string &roomId,
                const std::string &dateFrom,
                const std::string &dateTo,
                double total)
    : invoiceId(invoiceId),
    customerCccd(customerCccd),
    employeeCccd(employeeCccd),
    roomId(roomId),
    dateFrom(dateFrom),
    dateTo(dateTo),
    total(total) {

    }

std::string Invoice::getInvoiceId() const {
    return invoiceId;
}

void Invoice::setInvoiceId(const std::string &id) {
    invoiceId = id;
}

std::string Invoice::getCustomerCccd() const {
    return customerCccd;
}

void Invoice::setCustomerCccd(const std::string &cccd) {
    customerCccd = cccd;
}

std::string Invoice::getEmployeeCccd() const {
    return employeeCccd;
}

void Invoice::setEmployeeCccd(const std::string &cccd) {
    employeeCccd = cccd;
}

std::string Invoice::getRoomId() const {
    return roomId;
}

void Invoice::setRoomId(const std::string &id) {
    roomId = id;
}

std::string Invoice::getDateFrom() const {
    return dateFrom;
}

void Invoice::setDateFrom(const std::string &date) {
    dateFrom = date;
}

std::string Invoice::getDateTo() const {
    return dateTo;
}

void Invoice::setDateTo(const std::string &date) {
    dateTo = date;
}

double Invoice::getTotal() const {
    return total;
}

void Invoice::setTotal(double amount) {
    total = amount;
}

std::string Invoice::toCSV() const {
    std::ostringstream oss;

    oss << invoiceId << "," << customerCccd << "," << employeeCccd << "," << roomId << "," << dateFrom << "," << dateTo << "," << total;

        return oss.str();
}

void Invoice::fromCSV(const std::string &line) {
    std::stringstream ss(line);
    std::string totalStr;
    std::getline(ss, invoiceId, ',');
    std::getline(ss, customerCccd, ',');
    std::getline(ss, employeeCccd, ',');
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
