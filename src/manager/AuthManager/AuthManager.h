#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include <string>
#include <vector>
#include "../../models/Account/Account.h"

class AuthManager {
private:
    std::string dataDir;
    std::vector<Account> accounts;

public:
    AuthManager(const std::string &dataDir = "data");

    void loadAccounts();
    void saveAccounts();

    bool login(const std::string &username, const std::string &password, int &role, std::string &cccd);
    bool registerCustomer(const std::string &username, const std::string &password, const std::string &cccd, int role = 2);
    bool changePassword(const std::string &username, const std::string &oldPassword, const std::string &newPassword);
    bool forgotPassword(const std::string &username, const std::string &cccd);

    bool promoteToStaff(const std::string &username);
    Account* findAccountByUsername(const std::string &username);
    bool accountExists(const std::string &username) const;
    std::vector<Account> getCustomerAccounts() const;
};

#endif

