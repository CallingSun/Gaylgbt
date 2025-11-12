#ifndef HOTEL_MANAGER_H
#define HOTEL_MANAGER_H

#include <string>
#include <vector>
#include "models/Customer/Customer.h"//Gọi lớp customer
#include "models/Employee/Employee.h"//Gọi lớp employee
#include "models/Room/Room.h"//Gọi lớp room
#include "models/Invoice/Invoice.h"//Gọi lớp invoice
#include "AuthManager/AuthManager.h"//Gọi lớp AuthManager

class HotelManager {
private:
    std::string dataDir;
    std::vector<Customer> customers;
    std::vector<Employee> employees;
    std::vector<Room> rooms;
    std::vector<Invoice> invoices;
    AuthManager authManager;

    std::string currentUsername;
    int currentRole;
    std::string currentCccd;
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
    void editCustomerByCccd(const std::string &cccd);
    void addCustomerBatch(int quantity);
    void editCustomerBatch(int quantity);
    void deleteCustomerBatch(int quantity);
    //Tạo các hàm cho menu của customer



    void addEmployeeInteractive();
    void listEmployees() const;
    void deleteEmployeeByCccd(const std::string &cccd);
    void editEmployeeByCccd(const std::string &cccd);
    void addEmployeeBatch(int quantity);
    void editEmployeeBatch(int quantity);
    void deleteEmployeeBatch(int quantity);
    //Tạo các hàm cho menu của employee


    void addRoomInteractive();
    void listRooms() const;
    void deleteRoomById(const std::string &roomId);
    void editRoomById(const std::string &roomId);
    void addRoomBatch(int quantity);
    void editRoomBatch(int quantity);
    void deleteRoomBatch(int quantity);
    //Tạo các hàm cho menu của room


    void createInvoiceInteractive();
    void listInvoices() const;
    void deleteInvoiceById(const std::string &invId);
    void editInvoiceById(const std::string &invId);
    void createInvoiceBatch(int quantity);
    void editInvoiceBatch(int quantity);
    void deleteInvoiceBatch(int quantity);
    //Tạo các hàm cho menu của invoice


    void searchCustomerByName(const std::string &keyword) const;
    void searchCustomerByBirthdate(const std::string &date) const;
    void searchCustomerByBirthdateRange(const std::string &fromDate, const std::string &toDate) const;
    void searchRoomById(const std::string &roomId) const;
    void searchInvoiceById(const std::string &invId) const;
    void searchInvoiceByCheckInDate(const std::string &date) const;
    void searchInvoiceByCheckOutDate(const std::string &date) const;
    void searchInvoiceByDateRange(const std::string &fromDate, const std::string &toDate) const;
    //Tạo các hàm tìm kiếm cho các lớp


    double totalRevenue() const;
    double revenueInRange(const std::string &from, const std::string &to) const;
    void topCustomers(int n) const;
    void employeeInvoiceCount() const;
    void topEmployeesBySalary(int n) const;
    //Tạo các hàm cho menu của thống kê


    std::string displayCustomersForSelection();
    std::string displayEmployeesForSelection();
    std::string displayRoomsForSelection();
    std::string displayInvoicesForSelection();
    //Tạo các hàm hiển thị danh sách với lựa chọn

    std::string generateNextRoomId();
    std::string generateNextInvoiceId();
    void reorderRoomIds();
    void reorderInvoiceIds();
    void updateInvoiceRoomReferences(const std::string &oldRoomId, const std::string &newRoomId);
    //Tạo các hàm tự động sinh ID và sắp xếp lại ID

    void promoteToStaff();

    void customerMainMenu();
    void viewCustomerInfo();
    void viewCustomerInvoices();

    void staffMainMenu();

public:
    HotelManager(const std::string &dataDir = "data");
    void loadAll();
    void saveAll();
    void runConsole();
    void adminMainMenu();

    void homeMenu();
    void setCurrentUser(const std::string &username, int role, const std::string &cccd);
    std::string getCurrentUsername() const;
    int getCurrentRole() const;
    std::string getCurrentCccd() const;
    bool isAdmin() const;
    bool isStaff() const;
    bool isCustomer() const;
};

#endif
