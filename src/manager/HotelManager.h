#ifndef HOTEL_MANAGER_H
#define HOTEL_MANAGER_H

#include <string>
#include <vector>
#include "models/Customer/Customer.h"//Gọi lớp customer
#include "models/Employee/Employee.h"//Gọi lớp employee
#include "models/Room/Room.h"//Gọi lớp room
#include "models/Invoice/Invoice.h"//Gọi lớp invoice

class HotelManager {
private:
    std::string dataDir;
    std::vector<Customer> customers;
    std::vector<Employee> employees;
    std::vector<Room> rooms;
    std::vector<Invoice> invoices;
    //Tạo các vector cho các lớp

    
    void loadCustomers();
    void loadEmployees();
    void loadRooms();
    void loadInvoices();
    //Tạo các hàm load cho các lớp


    void saveCustomers();
    void saveEmployees();
    void saveRooms();
    void saveInvoices();
    //Tạo các hàm save cho các lớp


    void clearScreen();
    //Hàm để xoá màn hình làm gọn console


    void customerMenu();
    void employeeMenu();
    void roomMenu();
    void invoiceMenu();
    void searchMenu();
    void statsMenu();
    //Tạo các hàm menu cho các lớp


    Customer* findCustomerByCccd(const std::string &cccd);
    Employee* findEmployeeByCccd(const std::string &cccd);
    Room* findRoomById(const std::string &roomId);
    Invoice* findInvoiceById(const std::string &invId);
    //Tạo các hàm tìm kiếm cho các lớp


    bool customerExists(const std::string &cccd) const;
    //Kiểm tra khác hàng tồn tại hay chưa


    void addCustomerInteractive();
    void listCustomers() const;
    void deleteCustomerByCccd(const std::string &cccd);
    //Tạo các hàm cho menu của customer



    void addEmployeeInteractive();
    void listEmployees() const;
    void deleteEmployeeByCccd(const std::string &cccd);
    //Tạo các hàm cho menu của employee


    void addRoomInteractive();
    void listRooms() const;
    void deleteRoomById(const std::string &roomId);
    //Tạo các hàm cho menu của room


    void createInvoiceInteractive();
    void listInvoices() const;
    void deleteInvoiceById(const std::string &invId);
    //Tạo các hàm cho menu của invoice


    void searchCustomerByName(const std::string &keyword) const;
    void searchRoomById(const std::string &roomId) const;
    void searchInvoiceById(const std::string &invId) const;
    //Tạo các hàm tìm kiếm cho các lớp


    double totalRevenue() const;
    double revenueInRange(const std::string &from, const std::string &to) const;
    void topCustomers(int n) const;
    //Tạo các hàm cho menu của thống kê


    
public:
    HotelManager(const std::string &dataDir = "data");
    void loadAll();
    void saveAll();
    void runConsole();
};

#endif
