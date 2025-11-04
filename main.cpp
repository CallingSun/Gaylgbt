#include <bits/stdc++.h>
using namespace std;



//ho tro nhap xuat file csv
static inline vector<string> split(const string &s, char delim) {
    vector<string> out;
    string cur;
    stringstream ss(s);
    while (getline(ss, cur, delim)) out.push_back(cur);
    return out;
}

static inline string trim(const string &s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

//so sanh date
struct Date {
    int y, m, d;
    Date(): y(0), m(0), d(0) {}
    Date(int yy, int mm, int dd): y(yy), m(mm), d(dd) {}
    static Date fromString(const string &s) {
        Date res;
        if (s.size() >= 10 && s[4]=='-' && s[7]=='-') {
            res.y = stoi(s.substr(0,4));
            res.m = stoi(s.substr(5,2));
            res.d = stoi(s.substr(8,2));
        }
        return res;
    }
    string toString() const {
        char buf[16];
        sprintf(buf, "%04d-%02d-%02d", y, m, d);
        return string(buf);
    }
    bool operator<(const Date &o) const {
        if (y!=o.y) return y<o.y;
        if (m!=o.m) return m<o.m;
        return d<o.d;
    }
    bool operator==(const Date &o) const { return y==o.y && m==o.m && d==o.d; }
};

// --------------------------- Khởi tạo Person, Customer, Employee ---------------------------
class Person {
protected://nen de protected de ke thua
    string id;
    string name;
    string phone;
    string email;
public:
    Person() {

    }
    Person(const string &_id, const string &_name, const string &_phone, const string &_email)
    : id(_id), name(_name), phone(_phone), email(_email) {

    }
    virtual ~Person() {

    }
    string getId() const { 
        return id; 
    }
    string getName() const {
        return name; 
    }
    virtual void display() const {
        cout << "ID: " << id << " | Ten: " << name << " | SDT: " << phone << " | Email: " << email;
    }
    virtual string toCSV() const {
        stringstream ss;
        ss << id << "," << name << "," << phone << "," << email;
        return ss.str();
    }
    // nhap du lieu tu vector<string> (da tach bang dau ,)
    virtual void fromCSVFields(const vector<string> &fields) {
        if (fields.size() >= 4) {
            id = trim(fields[0]);
            name = trim(fields[1]);
            phone = trim(fields[2]);
            email = trim(fields[3]);
        }
    }
    friend ostream& operator<<(ostream &os, const Person &p) {
        p.display();
        return os;
    }
};

class Customer : public Person {
private:
    string dateOfBirth;
    string address;
public:
    Customer() {
        
    }
    Customer(const string &_id, const string &_name, const string &_phone, const string &_email, const string &_dob, const string &_addr)
    : Person(_id,_name,_phone,_email), dateOfBirth(_dob), address(_addr) {

    }
    void display() const override {
        Person::display();
        cout << " | Ngay sinh: " << dateOfBirth << " | Dia chi: " << address;
    }
    string toCSV() const override {
        stringstream ss;
        ss << id << "," << name << "," << phone << "," << email << "," << dateOfBirth << "," << address;
        return ss.str();
    }
    void fromCSVFields(const vector<string> &fields) override {
        Person::fromCSVFields(fields);
        if (fields.size() >= 6) {
            dateOfBirth = trim(fields[4]);
            address = trim(fields[5]);
        }
    }
    friend istream& operator>>(istream &is, Customer &c) {
        cout << "Nhap ID: "; getline(is, c.id);
        cout << "Nhap Ten: "; getline(is, c.name);
        cout << "Nhap SDT: "; getline(is, c.phone);
        cout << "Nhap Email: "; getline(is, c.email);
        cout << "Nhap ngay sinh (YYYY-MM-DD): "; getline(is, c.dateOfBirth);
        cout << "Nhap dia chi: "; getline(is, c.address);
        return is;
    }
    friend ostream& operator<<(ostream &os, const Customer &c) {
        os << c.toCSV();
        return os;
    }
};

class Employee : public Person {
private:
    string position;
    double salary = 0.0;
public:
    Employee() {}
    Employee(const string &_id, const string &_name, const string &_phone, const string &_email, const string &_pos, double _sal)
    : Person(_id,_name,_phone,_email), position(_pos), salary(_sal) {

    }
    void display() const override {
        Person::display();
        cout << " | Vi tri: " << position << " | Luong: " << salary;
    }
    string toCSV() const override {
        stringstream ss;
        ss << id << "," << name << "," << phone << "," << email << "," << position << "," << fixed << setprecision(2) << salary;
        return ss.str();
    }
    void fromCSVFields(const vector<string> &fields) override {
        Person::fromCSVFields(fields);
        if (fields.size() >= 6) {
            position = trim(fields[4]);
            try { salary = stod(trim(fields[5])); } catch(...) { salary = 0.0; }
        }
    }
    friend istream& operator>>(istream &is, Employee &e) {
        cout << "Nhap ID: "; getline(is, e.id);
        cout << "Nhap Ten: "; getline(is, e.name);
        cout << "Nhap Phone: "; getline(is, e.phone);
        cout << "Nhap Email: "; getline(is, e.email);
        cout << "Nhap Vi tri: "; getline(is, e.position);
        cout << "Nhap Luong: "; string tmp; getline(is, tmp); e.salary = stod(tmp);
        return is;
    }
    friend ostream& operator<<(ostream &os, const Employee &e) {
        os << e.toCSV();
        return os;
    }
};

// --------------------------- Khoi tao class Room ---------------------------
enum class RoomType { SINGLE, DOUBLE, FAMILY, UNKNOWN };
//gioi han loai phong
static inline string roomTypeToString(RoomType t) {
    switch(t) {
        case RoomType::SINGLE: return "Single";
        case RoomType::DOUBLE: return "Double";
        case RoomType::FAMILY: return "Family";
        default: return "Unknown";
    }
}
//chuyen doi chuoi thanh loai phong
static inline RoomType stringToRoomType(const string &s) {
    string s2 = s;
    for (auto &c: s2) c = tolower(c);
    if (s2.find("single")!=string::npos) return RoomType::SINGLE;
    if (s2.find("double")!=string::npos) return RoomType::DOUBLE;
    if (s2.find("family")!=string::npos) return RoomType::FAMILY;
    return RoomType::UNKNOWN;
}

class Room {
protected:
    string roomNumber;
    RoomType type = RoomType::UNKNOWN;
    double price = 0.0;
    bool available = true;
public:
    Room() {

    }
    Room(const string &rn, RoomType rt, double p, bool av=true) : roomNumber(rn), type(rt), price(p), available(av) {

    }
    string getRoomNumber() const { return roomNumber; }
    double getPrice() const {
        return price; 
    }
    bool isAvailable() const { 
        return available; 
    }
    void setAvailable(bool v) { 
        available = v; 
    }
    void display() const {
        cout << "Phong: " << roomNumber << " | Loai Phong: " << roomTypeToString(type)
            << " | Gia/1 đem: " << price << " | Con trong: " << (available ? "Co":"Khong");
    }
    string toCSV() const {
        stringstream ss;
        ss << roomNumber << "," << roomTypeToString(type) << "," << fixed << setprecision(2) << price << "," << (available?1:0);
        return ss.str();
    }
    void fromCSV(const string &line) {
        auto f = split(line, ',');
        if (f.size()>=4) {
            roomNumber = trim(f[0]);
            type = stringToRoomType(trim(f[1]));
            try { price = stod(trim(f[2])); } catch(...) { price = 0.0; }
            available = (trim(f[3])=="1" || trim(f[3])=="true");
        }
    }
    friend istream& operator>>(istream &is, Room &r) {
        cout << "Nhap So phong: "; getline(is, r.roomNumber);
        cout << "Nhap Loai Phong (Single/Double/Family): "; string t; getline(is, t); r.type = stringToRoomType(t);
        cout << "Nhap Gia 1 đem: "; string tmp; getline(is,tmp); r.price = stod(tmp);
        r.available = true;
        return is;
    }
    friend ostream& operator<<(ostream &os, const Room &r) {
        os << r.toCSV();
        return os;
    }
    bool operator<(const Room &o) const {
        return roomNumber < o.roomNumber;
    }
};

// ---------------------------Khoi tao Invoice ---------------------------
class Invoice {
protected:
    string invoiceID;
    string customerID;
    string roomNumber;
    string dateFrom; // dinh dang: YYYY-MM-DD
    string dateTo;   // dinh dang: YYYY-MM-DD
    double totalAmount = 0.0;
public:
    Invoice() {

    }
    Invoice(const string &_inv, const string &_cid, const string &_room, const string &_from, const string &_to, double amt)
    : invoiceID(_inv), customerID(_cid), roomNumber(_room), dateFrom(_from), dateTo(_to), totalAmount(amt) {
        
    }
    string getID() const {
        return invoiceID; 
    }
    string getCustomerID() const { 
        return customerID; 
    }
    string getRoomNumber() const { 
        return roomNumber; 
    }
    string getFrom() const { 
        return dateFrom; 
    }
    string getTo() const { 
        return dateTo; 
    }
    double getAmount() const { 
        return totalAmount; 
    }
    void display() const {
        cout << "ID hoa don: " << invoiceID << " | Khach hang: " << customerID << " | Phong: " << roomNumber
            << " | Tu ngay: " << dateFrom << " | Den ngay: " << dateTo << " | Tong: " << totalAmount;
    }
    string toCSV() const {
        stringstream ss;
        ss << invoiceID << "," << customerID << "," << roomNumber << "," << dateFrom << "," << dateTo << "," << fixed << setprecision(2) << totalAmount;
        return ss.str();
    }
    void fromCSV(const string &line) {
        auto f = split(line, ',');
        if (f.size() >= 6) {
            invoiceID = trim(f[0]);
            customerID = trim(f[1]);
            roomNumber = trim(f[2]);
            dateFrom = trim(f[3]);
            dateTo = trim(f[4]);
            try { totalAmount = stod(trim(f[5])); } catch(...) { totalAmount = 0.0; }
        }
    }
    // sap xep giam dan theo so tien hoa don
    friend bool compareInvoiceAmountDesc(const Invoice &a, const Invoice &b) {
        return a.totalAmount > b.totalAmount;
    }
    // vi du ham ban so sanh hai hoa don theo so tien
    friend ostream& operator<<(ostream &os, const Invoice &inv) {
        os << inv.toCSV();
        return os;
    }
};

//tinh so dem (duoc tinh bao gom ngay di va khong bao gom ngay ve hay noi cach khac la [from, to) )
int nightsBetween(const string &fromS, const string &toS) {
    Date f = Date::fromString(fromS);
    Date t = Date::fromString(toS);
    // su dung thu vien time.h de tinh so ngay giua hai date
    tm tmf = {}, tmt = {};
    tmf.tm_year = f.y - 1900; tmf.tm_mon = f.m - 1; tmf.tm_mday = f.d;
    tmt.tm_year = t.y - 1900; tmt.tm_mon = t.m - 1; tmt.tm_mday = t.d;
    time_t tf = mktime(&tmf);
    time_t tt = mktime(&tmt);
    if (tf== (time_t)-1 || tt == (time_t)-1) return 0;
    double diff = difftime(tt, tf);
    int days = (int)(diff / (60*60*24));
    return max(0, days);
}

// ---------------------------Khởi tạo HotelManager ---------------------------
class HotelManager {
protected:
    vector<Customer> customers;
    vector<Employee> employees;
    vector<Room> rooms;
    vector<Invoice> invoices;

    const string fn_customers = "customers.txt";
    const string fn_employees = "employees.txt";
    const string fn_rooms = "rooms.txt";
    const string fn_invoices = "invoices.txt";

public:
    HotelManager() {
        loadAll();
    }

    // ---------- Nhap xuat IO files ----------
    void loadAll() {
        loadRooms();
        loadCustomers();
        loadEmployees();
        loadInvoices();
    }
    void saveAll() {
        saveRooms();
        saveCustomers();
        saveEmployees();
        saveInvoices();
    }

    void loadCustomers() {
        customers.clear();
        ifstream ifs(fn_customers);
        if (!ifs) {
            cout << "File customer chua duoc tao, hay khoi tao.\n";
            return;
        }
        string line;
        while (getline(ifs, line)) {
            if (trim(line).empty()) continue;
            auto f = split(line, ',');
            Customer c;
            c.fromCSVFields(f);
            customers.push_back(c);
        }
    }
    void saveCustomers() {
        ofstream ofs(fn_customers);
        for (auto &c: customers) ofs << c.toCSV() << "\n";
    }

    void loadEmployees() {
        employees.clear();
        ifstream ifs(fn_employees);
        if (!ifs)
        {
            cout << "File employee chua duoc tao, hay khoi tao.\n";
            return;
        }
        string line;
        while (getline(ifs, line)) {
            if (trim(line).empty()) continue;
            auto f = split(line, ',');
            Employee e;
            e.fromCSVFields(f);
            employees.push_back(e);
        }
    }
    void saveEmployees() {
        ofstream ofs(fn_employees);
        for (auto &e: employees) ofs << e.toCSV() << "\n";
    }

    void loadRooms() {
        rooms.clear();
        ifstream ifs(fn_rooms);
        if (!ifs) 
        {
            cout << "File room chua duoc tao, hay khoi tao.\n";
            return;
        }
        string line;
        while (getline(ifs, line)) {
            if (trim(line).empty()) continue;
            Room r; r.fromCSV(line);
            rooms.push_back(r);
        }
    }
    void saveRooms() {
        ofstream ofs(fn_rooms);
        for (auto &r: rooms) ofs << r.toCSV() << "\n";
    }

    void loadInvoices() {
        invoices.clear();
        ifstream ifs(fn_invoices);
        if (!ifs) 
        {
            cout << "File invoice chua duoc tao, hay khoi tao.\n";
            return;
        }
        string line;
        while (getline(ifs, line)) {
            if (trim(line).empty()) continue;
            Invoice inv; inv.fromCSV(line);
            invoices.push_back(inv);
        }
    }
    void saveInvoices() {
        ofstream ofs(fn_invoices);
        for (auto &inv: invoices) ofs << inv.toCSV() << "\n";
    }

    // ---------- Cac tien ich ----------
    bool customerExists(const string &id) const {
        for (auto &c: customers) if (c.getId()==id) return true;
        return false;
    }
    Customer* findCustomer(const string &id) {
        for (auto &c: customers) if (c.getId()==id) return &c;
        return nullptr;
    }
    Employee* findEmployee(const string &id) {
        for (auto &e: employees) if (e.getId()==id) return &e;
        return nullptr;
    }
    Room* findRoom(const string &roomNo) {
        for (auto &r: rooms) if (r.getRoomNumber()==roomNo) return &r;
        return nullptr;
    }
    Invoice* findInvoice(const string &invId) {
        for (auto &inv: invoices) if (inv.getID()==invId) return &inv;
        return nullptr;
    }

    // ---------- CRUD(Create, Read, Update, Delete) Customers ----------
    void addCustomerInteractive() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (true) {
            Customer c;
            cin >> c; // đọc toàn bộ thông tin khách

            if (customerExists(c.getId())) {
                cout << "Da ton tai khach hang co ID nay!\n";
                cout << "Nhan 'r' de nhap lai, 'c' de huy: ";
                string ans;
                getline(cin, ans);
                if (ans.empty()) getline(cin, ans);
                if (!ans.empty() && (ans[0]=='c' || ans[0]=='C')) {
                    cout << "Huy them khach hang.\n";
                    return;
                }
                cout << "Nhap lai khach hang...\n";
                continue; // lặp để người dùng nhập lại
            }

            customers.push_back(c);
            saveCustomers();
            cout << "Da them khach hang\n";
            return;
        }
    }
    void listCustomers() const {
        cout << "---- Khach hang ----\n";
        for (const auto &c: customers) {
            cout << c.toCSV() << "\n";
        }
    }
    void deleteCustomer(const string &id) {
        auto it = remove_if(customers.begin(), customers.end(), [&](const Customer &c){ return c.getId()==id; });
        if (it != customers.end()) {
            customers.erase(it, customers.end());
            saveCustomers();
            cout << "Da xoa khach hang.\n";
        } else cout << "Khong tin thay.\n";
    }

    // ---------- CRUD voi Employees ----------
    void addEmployeeInteractive() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (true) {
            Employee e;
            cin >> e;
            if (findEmployee(e.getId())) {
                cout << "Nhan vien co ID tren da ton tai.\n";
                cout << "Nhan 'r' de nhap lai, 'c' de huy: ";
                string ans;
                getline(cin, ans);
                if (ans.empty()) getline(cin, ans);
                if (!ans.empty() && (ans[0]=='c' || ans[0]=='C')) {
                    cout << "Huy them nhan vien.\n";
                    return;
                }
                cout << "Nhap lai nhan vien...\n";
                continue;
            }
            employees.push_back(e);
            saveEmployees();
            cout << "Da them nhan vien.\n";
            return;
        }
    }
    void listEmployees() const {
        cout << "---- Nhan vien ----\n";
        for (const auto &e: employees) cout << e.toCSV() << "\n";
    }
    void deleteEmployee(const string &id) {
        auto it = remove_if(employees.begin(), employees.end(), [&](const Employee &e){ return e.getId()==id; });
        if (it != employees.end()) {
            employees.erase(it, employees.end());
            saveEmployees();
            cout << "Da xoa nhan vien.\n";
        } else cout << "Khong tim thay.\n";
    }

    // ---------- CRUD voi Rooms ----------
    void addRoomInteractive() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (true) {
            Room r;
            cin >> r;
            if (findRoom(r.getRoomNumber())) {
                cout << "Phong da ton tai.\n";
                cout << "Nhan 'r' de nhap lai, 'c' de huy: ";
                string ans;
                getline(cin, ans);
                if (ans.empty()) getline(cin, ans);
                if (!ans.empty() && (ans[0]=='c' || ans[0]=='C')) {
                    cout << "Huy them phong.\n";
                    return;
                }
                cout << "Nhap lai phong...\n";
                continue;
            }
            rooms.push_back(r);
            saveRooms();
            cout << "Da them phong.\n";
            return;
        }
    }
    void listRooms() const {
        cout << "---- Rooms ----\n";
        for (const auto &r: rooms) cout << r.toCSV() << "\n";
    }
    void listRoomsPretty() const {
        cout << left << setw(10) << "Phong so" << setw(12) << "Loai phong" << setw(12) << "Gia" << setw(10) << "Con trong" << "\n";
        for (const auto &r: rooms) {
            cout << left << setw(10) << r.getRoomNumber()
                << setw(12) << roomTypeToString( stringToRoomType(r.toCSV().empty() ? "Unknown" : "Unknown") ) 
                << setw(12) << r.getPrice()
                << setw(10) << (r.isAvailable() ? "Yes" : "No") << "\n";
        }
    }

    // ---------- Cac chuc nang voi  Invoicing ----------
    // tao hoa don moi, kiem tra tinh hop le (khach hang ton tai, phong con trong, tinh so dem o hop le), tinh tien
    void createInvoiceInteractive() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (true) {
            string invId, custId, roomNo, from, to;
            cout << "ID Hoa don: ";
            getline(cin, invId);
            if (invId.empty()) { cout << "ID khong duoc de trong.\n"; continue; }
            if (findInvoice(invId)) {
                cout << "Hoa don ton tai\n";
                cout << "Nhan 'r' de nhap lai, 'c' de huy: ";
                string ans; getline(cin, ans);
                if (ans.empty()) getline(cin, ans);
                if (!ans.empty() && (ans[0]=='c' || ans[0]=='C')) { cout << "Huy tao hoa don.\n"; return; }
                continue;
            }

            cout << "ID Khach hang: ";
            getline(cin, custId);
            if (!customerExists(custId)) {
                cout << "Khong tim thay khach hang\n";
                cout << "Nhan 'r' de nhap lai, 'c' de huy: ";
                string ans; getline(cin, ans);
                if (ans.empty()) getline(cin, ans);
                if (!ans.empty() && (ans[0]=='c' || ans[0]=='C')) { cout << "Huy tao hoa don.\n"; return; }
                continue;
            }

            cout << "Phong so: ";
            getline(cin, roomNo);
            Room* r = findRoom(roomNo);
            if (!r) {
                cout << "Khong tim thay phong\n";
                cout << "Nhan 'r' de nhap lai, 'c' de huy: ";
                string ans; getline(cin, ans);
                if (ans.empty()) getline(cin, ans);
                if (!ans.empty() && (ans[0]=='c' || ans[0]=='C')) { cout << "Huy tao hoa don.\n"; return; }
                continue;
            }
            if (!r->isAvailable()) {
                cout << "Phong khong kha dung\n";
                cout << "Nhan 'r' de nhap lai, 'c' de huy: ";
                string ans; getline(cin, ans);
                if (ans.empty()) getline(cin, ans);
                if (!ans.empty() && (ans[0]=='c' || ans[0]=='C')) { cout << "Huy tao hoa don.\n"; return; }
                continue;
            }

            cout << "Tu ngay (YYYY-MM-DD): ";
            getline(cin, from);
            cout << "Den (YYYY-MM-DD): ";
            getline(cin, to);
            int nights = nightsBetween(from, to);
            if (nights <= 0) {
                cout << "Loi nhap ngay (ngay di phai truoc ngay den).\n";
                cout << "Nhan 'r' de nhap lai, 'c' de huy: ";
                string ans; getline(cin, ans);
                if (ans.empty()) getline(cin, ans);
                if (!ans.empty() && (ans[0]=='c' || ans[0]=='C')) { cout << "Huy tao hoa don.\n"; return; }
                continue;
            }

            double total = nights * r->getPrice();
            Invoice inv(invId, custId, roomNo, from, to, total);
            invoices.push_back(inv);
            r->setAvailable(false);
            saveInvoices();
            saveRooms();
            cout << "Hoa don da duoc tao. Tong tien: " << total << "\n";
            return;
        }
    }

    void listInvoices() const {
        cout << "---- Hoa don ----\n";
        for (const auto &inv: invoices) cout << inv.toCSV() << "\n";
    }

    // ----------Chuc nang tim kiem theo ten ----------
    void searchCustomerByName(const string &sub) const {
        cout << "Tim kiem khach hang co ten chua \"" << sub << "\":\n";
        for (const auto &c: customers) {
            if (c.getName().find(sub) != string::npos) cout << c.toCSV() << "\n";
        }
    }
    void searchRoomByNumber(const string &rn) const {
        Room *r = const_cast<HotelManager*>(this)->findRoom(rn);
        if (r) r->display(), cout << "\n"; else cout << "Khong tim thay phong.\n";
    }
    void searchInvoiceByID(const string &id) const {
        for (const auto &inv: invoices) if (inv.getID()==id) { inv.display(); cout << "\n"; return; }
        cout << "Khong tim thay hoa don.\n";
    }

    // ---------- Thong ke so lieu ----------
    double totalRevenue() const {
        double s=0;
        for (auto &inv: invoices) s += inv.getAmount();
        return s;
    }
    double revenueInRange(const string &from, const string &to) const {
        Date df = Date::fromString(from), dt = Date::fromString(to);
        double s=0;
        for (auto &inv: invoices) {
            Date inf = Date::fromString(inv.getFrom()), intd = Date::fromString(inv.getTo());
            // kiem tra xem co giao nhau khong
            if (!(intd < df) && !(dt < inf)) s += inv.getAmount();
        }
        return s;
    }
    void topCustomersBySpending(int topN=5) const {
        unordered_map<string,double> mp;
        for (auto &inv: invoices) mp[inv.getCustomerID()] += inv.getAmount();
        vector<pair<string,double>> arr;
        for (auto &kv: mp) arr.emplace_back(kv.first, kv.second);
        sort(arr.begin(), arr.end(), [](auto &a, auto &b){ return a.second > b.second; });
        cout << "Top " << topN << " khach hang boi viec tieu dung:\n";
        for (int i=0;i< (int)arr.size() && i<topN; ++i) {
            cout << i+1 << ". ID khach hang: " << arr[i].first << " | Tong: " << arr[i].second << "\n";
        }
    }

    // ---------- Void Menu ----------
    void runConsole() {
        while (true) {
            cout << "\n===== Quan Ly Hotel Mini =====\n";
            cout << "1. Quan ly khach hang\n";
            cout << "2. Quan ly nhan vien\n";
            cout << "3. Quan ly phong\n";
            cout << "4. Quan ly hoa don\n";
            cout << "5. Tim kiem\n";
            cout << "6. Thong ke doanh thu\n";
            cout << "0. Luu & Thoat\n";
            cout << "Chon: ";
            int choice;
            if (!(cin >> choice)) {
                cin.clear();
                string tmp; getline(cin, tmp);
                continue;
            }
            switch(choice) {
                case 1: 
                customerMenu(); 
                break;
                case 2: 
                employeeMenu(); 
                break;
                case 3: 
                roomMenu(); 
                break;
                case 4: 
                invoiceMenu(); 
                break;
                case 5: 
                searchMenu(); 
                break;
                case 6: 
                statsMenu(); 
                break;
                case 0: 
                saveAll(); cout << "Cam on vi da su dung chuong trinh. Hen gap lai.\n"; 
                return;
                default: 
                cout << "Lua chon khong hop le vui long nhap lai.\n";
            }
        }
    }

    void customerMenu() {
        system("cls");
        while (true) {
            cout << "\n-- Menu khach hang --\n1. Them khach hang\n2. Danh sach khach hang\n3. Xoa khach\n0. Quay lai\nLua chon: ";
            int c; 
            if (!(cin>>c)) {
                cin.clear(); 
                string sk; 
                getline(cin,sk); 
                continue; 
            }
            if (c==1) addCustomerInteractive();
            else if (c==2) listCustomers();
            else if (c==3) {
                cout << "ID to delete: "; 
                string id; 
                cin >> id; 
                deleteCustomer(id); 
            }
            else if (c==0) break;
        }
    }
    void employeeMenu() {
        system("cls");
        while (true) {
            cout << "\n-- Menu nhan vien --\n1. Them nhan vien\n2. Danh sach nhan vien\n0. Quay lai\nLua chon: ";
            int c; 
            if (!(cin>>c)) {
                cin.clear(); 
                string sk; 
                getline(cin,sk); 
                continue; 
            }
            if (c==1) addEmployeeInteractive();
            else if (c==2) listEmployees();
            else if (c==0) break;
        }
    }
    void roomMenu() {
        system("cls");
        while (true) {
            cout << "\n-- Menu phong --\n1. Them phong\n2. Danh sach phong\n3. Hien thong tin phong\n0. Quay lai\nLua chon: ";
            int c; 
            if (!(cin>>c)) { 
                cin.clear(); 
                string sk; 
                getline(cin,sk); 
                continue; 
            }
            if (c==1) addRoomInteractive();
            else if (c==2) listRooms();
            else if (c==3) { 
                cout << "Phong so: "; string rn; cin >> rn; 
                searchRoomByNumber(rn); 
            }
            else if (c==0) break;
        }
    }
    void invoiceMenu() {
        system("cls");
        while (true) {
            cout << "\n-- Menu hoa don --\n1. Tao hoa don\n2. Danh sach hoa don\n0. Quay lai\nLua chon: ";
            int c;
            if (!(cin>>c)){
                cin.clear(); 
                string sk; 
                getline(cin,sk); 
                continue; 
            }
            if (c==1) createInvoiceInteractive();
            else if (c==2) listInvoices();
            else if (c==0) break;
        }
    }
    void searchMenu() {
        system("cls");
        while (true) {
            cout << "\n-- Tim kiem --\n1. Tim khach hang theo ten\n2. Tim phong theo so\n3. Tim hoa don theo id\n0. Quay lai\nLua chon: ";
            int c; 
            if (!(cin>>c)) {
                cin.clear(); 
                string sk; 
                getline(cin,sk); 
                continue; 
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (c==1) { 
                cout << "Tim kiem ten khach hang co tu: "; 
                string s; 
                getline(cin, s); 
                searchCustomerByName(s); }
            else if (c==2) { 
                cout << "Enter room no: "; 
                string r; 
                getline(cin, r); 
                searchRoomByNumber(r); }
            else if (c==3) { 
                cout << "Enter invoice id: "; 
                string id; 
                getline(cin, id); 
                searchInvoiceByID(id); }
            else if (c==0) break;
        }
    }
    void statsMenu() {
        system("cls");
        while (true) {
            cout << "\n-- Thong ke --\n1. Tong doanh thu\n2. Doanh trong khoang thoi gian(Tu ngay nao do den ngay nao do)\n3. Top khach hang\n0. Quay lai\nLua chon: ";
            int c; 
            if (!(cin>>c)) {
                cin.clear();
                string sk;
                getline(cin,sk);
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (c==1) { 
                cout << "Tong doanh thu: " << totalRevenue() << "\n"; 
            }
            else if (c==2) {
                cout << "Tu (YYYY-MM-DD): "; string f; getline(cin,f);
                cout << "Den (YYYY-MM-DD): "; string t; getline(cin,t);
                cout << "Doanh thu: " << revenueInRange(f,t) << "\n";
            } 
            else if (c==3) {
                cout << "Top : "; 
                int n; 
                if (!(cin>>n)) {
                    cin.clear();
                    string sk; 
                    getline(cin,sk); 
                    continue; 
                }
                topCustomersBySpending(n);
            } else if (c==0) break;
        }
    }
};

// --------------------------- Ham main ---------------------------
int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    system("cls");
    HotelManager hm;
    hm.runConsole();
    return 0;
}
