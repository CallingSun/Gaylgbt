# HotelMini - Hệ Thống Quản Lý Khách Sạn

## 1. Phát biểu bài toán và lý do chọn

**Tổng quan về đề tài HotelMini** 
-Phát biểu bài toán: Xây dựng một hệ thống phần mềm quản lý cho một “Khách sạn mini” (Hotel Mini) cho phép quản lý thông tin: khách hàng, phòng, nhân viên, và hóa đơn. Hệ thống phải hỗ trợ thao tác thêm/sửa/xóa/danh sách, tìm kiếm, lưu/đọc dữ liệu từ file và thống kê doanh thu.
-Lý do chọn: Khách sạn nhỏ/nhà nghỉ/nhà trọ là một bài toán điển hình cho OOP: có nhiều thực thể (khách hàng, phòng, nhân viên, hóa đơn) tương tác với nhau; cần lưu trữ bền vững; có nghiệp vụ (đặt phòng, thanh toán, thống kê) phù hợp để thể hiện kế thừa, đóng gói, đa hình, và xử lý file
### Các Tính Năng Chính

- **Quản Lý Khách Hàng**: Thêm, liệt kê và xóa hồ sơ khách hàng với thông tin cá nhân
- **Quản Lý Nhân Viên**: Quản lý nhân viên khách sạn với thông tin vị trí và lương
- **Quản Lý Phòng**: Duy trì kho phòng với giá và trạng thái sẵn có
- **Quản Lý Hóa Đơn**: Tạo và quản lý hóa đơn khách hàng với theo dõi tự động trạng thái phòng
- **Chức Năng Tìm Kiếm**: Tìm kiếm khách hàng theo tên, phòng theo ID và hóa đơn theo ID
- **Thống Kê**: Xem báo cáo doanh thu và xác định khách hàng hàng đầu
- **Lưu Trữ Dữ Liệu**: Tất cả dữ liệu được tự động lưu vào các tệp CSV trong thư mục `data/`

---

## 2. Cấu Trúc Dữ Liệu

### Phân tích về cấp lớp và mối quan hệ

```
Person (Lớp Cơ Sở Trừu Tượng)
├── Customer (Khách Hàng)
└── Employee (Nhân Viên)

Room (Phòng - Độc Lập)

Invoice (Hóa Đơn - Độc Lập)

HotelManager (Lớp Quản Lý Chính - Độc Lập)
```

### Mô Tả Chi Tiết Các Lớp

#### **Person** (Lớp Cơ Sở)
Lớp cơ sở cho tất cả những người trong hệ thống.

**Thuộc Tính:**
- `cccd` (chuỗi): Số CCCD
- `name` (chuỗi): Họ và tên
- `phone` (chuỗi): Số điện thoại
- `email` (chuỗi): Địa chỉ email

**Phương Thức:**
- `getCccd()`, `getName()`, `getPhone()`, `getEmail()`: Các hàm lấy dữ liệu
- `setName()`, `setPhone()`, `setEmail()`: Các hàm đặt dữ liệu
- `toCSV()`: Chuyển đổi sang định dạng CSV (thuẩn ảo)
- `fromCSV()`: Phân tích từ định dạng CSV (thuần ảo)

#### **Customer** (Kế Thừa từ Person)
Đại diện cho một khách hàng khách sạn.

**Được kế thức toàn bộ thuộc tính và phương thức lấy từ person(Lớp cha)**

**Thuộc Tính Bổ Sung:**
- `birthdate` (chuỗi): Ngày sinh (định dạng YYYY-MM-DD)
- `address` (chuỗi): Địa chỉ cư trú

**Phương Thức Mới:**
- `getBirthdate()`, `getAddress()`: Các hàm lấy dữ liệu
- `toCSV()`, `fromCSV()`: Tuần tự hóa CSV

#### **Employee** (Kế Thừa từ Person)
Đại diện cho một nhân viên khách sạn.

**Được kế thức toàn bộ thuộc tính và phương thức lấy từ person(Lớp cha)**

**Thuộc Tính Bổ Sung:**
- `position` (chuỗi): Vị trí công việc (ví dụ: Quản Lý, Lễ Tân)
- `salary` (số thực): Lương hàng tháng

**Phương Thức Mới:**
- `getPosition()`, `getSalary()`: Các hàm lấy dữ liệu
- `toCSV()`, `fromCSV()`: Tuần tự hóa CSV

#### **Room** (Phòng)
Đại diện cho một phòng khách sạn.

**Thuộc Tính:**
- `roomId` (chuỗi): Mã phòng duy nhất (ví dụ: R101, R202)
- `type` (chuỗi): Loại phòng (ví dụ: Đơn, Đôi, Gia Đình)
- `price` (số thực): Giá mỗi đêm
- `available` (boolean): Trạng thái sẵn có (true = có sẵn, false = đã đặt)

**Phương Thức:**
- `getRoomId()`, `getType()`, `getPrice()`, `isAvailable()`: Các hàm lấy dữ liệu
- `setAvailable()`: Đặt trạng thái sẵn có
- `toCSV()`, `fromCSV()`: Tuần tự hóa CSV

#### **Invoice** (Hóa Đơn)
Đại diện cho một đơn đặt phòng/hóa đơn khách hàng.

**Thuộc Tính:**
- `invoiceId` (chuỗi): Mã hóa đơn duy nhất
- `customerCccd` (chuỗi): Tham chiếu đến CCCD khách hàng
- `roomId` (chuỗi): Tham chiếu đến phòng được đặt
- `dateFrom` (chuỗi): Ngày nhận phòng (YYYY-MM-DD)
- `dateTo` (chuỗi): Ngày trả phòng (YYYY-MM-DD)
- `total` (số thực): Tổng số tiền tính phí

**Phương Thức:**
- `getInvoiceId()`, `getCustomerCccd()`, `getRoomId()`, `getDateFrom()`, `getDateTo()`, `getTotal()`: Các hàm lấy dữ liệu
- `toCSV()`, `fromCSV()`: Tuần tự hóa CSV

#### **HotelManager** (Lớp Quản Lý Chính)
Lớp quản lý trung tâm điều phối tất cả các hoạt động của chương trình.

**Thuộc Tính:**
- `dataDir` (chuỗi): Đường dẫn đến thư mục dữ liệu
- `customers` (vector<Customer>): Tất cả khách hàng
- `employees` (vector<Employee>): Tất cả nhân viên
- `rooms` (vector<Room>): Tất cả phòng
- `invoices` (vector<Invoice>): Tất cả hóa đơn

**Phương Thức Chính:**
- `loadAll()`, `saveAll()`: Tải/lưu tất cả dữ liệu
- `customerMenu()`, `employeeMenu()`, `roomMenu()`, `invoiceMenu()`: Các hàm menu
- `searchMenu()`, `statsMenu()`: Các hàm tìm kiếm và thống kê
- `runConsole()`: Vòng lặp bảng điều khiển chính

### Cấu Trúc Thư Mục Dự Án

```
HotelMini/
├── CMakeLists.txt              # Cấu hình xây dựng CMake
├── README.md                   # Tệp này
├── main.cpp                    # Điểm vào chương trình
├── build/                      # Thư mục đầu ra xây dựng (được tạo)
│   └── bin/
│       └── HotelMini.exe       # Tệp thực thi đã biên dịch
├── data/                       # Lưu trữ dữ liệu (tệp CSV)
│   ├── customers.txt           # Dữ liệu khách hàng
│   ├── employees.txt           # Dữ liệu nhân viên
│   ├── rooms.txt               # Dữ liệu phòng
│   └── invoices.txt            # Dữ liệu hóa đơn
└── src/
    ├── manager/
    │   ├── HotelManager.h
    │   ├── HotelManager.cpp
    │   └── menus/              # Triển khai menu
    │       ├── CustomerMenu/   # Menu quản lý khách hàng
    │       ├── EmployeeMenu/   # Menu quản lý nhân viên
    │       ├── RoomMenu/       # Menu quản lý phòng
    │       ├── InvoiceMenu/    # Menu quản lý hóa đơn
    │       ├── SearchMenu/     # Menu tìm kiếm
    │       └── StatsMenu/      # Menu thống kê
    ├── models/                 # Các lớp mô hình dữ liệu
    │   ├── Person/             # Lớp Người
    │   ├── Customer/           # Lớp Khách Hàng
    │   ├── Employee/           # Lớp Nhân Viên
    │   ├── Room/               # Lớp Phòng
    │   └── Invoice/            # Lớp Hóa Đơn
    └── utils/                  # Các hàm tiện ích
        ├── DateUtils/          # Tiện ích xử lý ngày tháng
        └── StringUtils/        # Tiện ích xử lý chuỗi
```

---

## 3. Hướng Dẫn Sử Dụng!

### Yêu Cầu Tiên Quyết

- **CMake**: Phiên bản 3.16 trở lên
- **Trình Biên Dịch C++**: MinGW g++ 13.2.0 hoặc trình biên dịch C++17 tương thích
- **Hệ Điều Hành**: Windows (với MinGW đã cài đặt)

### Các Bước Xây Dựng

#### Bước 1: Clone dự án 
**Mở cmd window và copy lệnh sau**

```bash
git clone https://github.com/CallingSun/Gaylgbt.git
```

**NOTE: Đường nhiên là nếu bạn đã được chủ dự án cho phép vào repo mới clone được còn không thì phải chịu!**
#### Bước 2: Điều Hướng đến Thư Mục Dự Án
```bash
cd C:\Users\<tên_người_dùng>\..\HotelMini 
```
Hoặc
```bash
cd D:\..\HotelMini
```
**Tuỳ thuộc vào việc bạn clone về đâu**

#### Bước 3: Tạo Thư Mục Build
```bash
mkdir build
cd build
```

#### Bước 4: Cấu Hình với CMake
```bash
cmake -S .. -B . -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
```

#### Bước 5: Xây Dựng Dự Án
```bash
cmake --build .
```

**Tệp thực thi đã biên dịch sẽ được đặt tại: `build\bin\HotelMini.exe`**

### Bước 6: Chạy Dự Án

```bash
cd "..\..\HotelMini"; .\build\bin\HotelMini.exe
```
**Hãy thay dấu .. bằng đường dẫn đến thư mục HotelMini của bạn**

### Giải Pháp Thay Thế cho Đường Dẫn Không Phải ASCII

**Lưu Ý**: Nếu đường dẫn dự án của bạn chứa các ký tự không phải ASCII (ví dụ: các ký tự tiếng Việt như "Máy tính"), MinGW g++ có thể gặp sự cố mã hóa. Sử dụng giải pháp thay thế này:

1. Sao chép dự án đến một đường dẫn tạm thời chỉ có ASCII:
   ```bash
   Copy-Item -Recurse "C:\Users\<tên_người_dùng>\OneDrive\Máy tính\HotelMini" "C:\temp\HotelMini"
   ```

2. Xây dựng tại vị trí tạm thời:
   ```bash
   cd C:\temp\HotelMini
   mkdir build
   cd build
   cmake -S .. -B . -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
   cmake --build .
   ```

3. Sao chép tệp thực thi trở lại vị trí ban đầu:
   ```bash
   Copy-Item -Force "C:\temp\HotelMini\build\bin\HotelMini.exe" "C:\Users\<tên_người_dùng>\OneDrive\Máy tính\HotelMini\build\bin\HotelMini.exe"
   ```

---

## 4. Cách Chạy Chương Trình

### Thực Thi Chương Trình
**Nhắc lại lần nữa cho nhớ cách chạy**
```bash
cd "..\..\HotelMini"; .\build\bin\HotelMini.exe
```
**NOTE: TIÊN QUYẾT PHẢI ĐÚNG ĐƯỜNG DẪN ĐẾN THƯ MỤC HOTELMINI**

### Các Tùy Chọn Menu Chính

```
=== Quan Li Hotel Mini ===
1. Quan ly khach hang      (Quản Lý Khách Hàng)
2. Quan ly nhan vien       (Quản Lý Nhân Viên)
3. Quan ly phong           (Quản Lý Phòng)
4. Quan ly hoa don         (Quản Lý Hóa Đơn)
5. Tim kiem                (Tìm Kiếm)
6. Thong ke                (Thống Kê)
0. Luu & Thoat             (Lưu & Thoát)
```

### Các Hoạt Động Menu Con

**Quản Lý Khách Hàng:**
- 1. Thêm khách hàng
- 2. Liệt kê khách hàng
- 3. Xóa khách hàng theo CCCD
- 0. Quay lại

**Quản Lý Nhân Viên:**
- 1. Thêm nhân viên
- 2. Liệt kê nhân viên
- 3. Xóa nhân viên theo CCCD
- 0. Quay lại

**Quản Lý Phòng:**
- 1. Thêm phòng
- 2. Liệt kê phòng
- 3. Xem chi tiết phòng
- 4. Xóa phòng
- 0. Quay lại

**Quản Lý Hóa Đơn:**
- 1. Tạo hóa đơn
- 2. Liệt kê hóa đơn
- 3. Xóa hóa đơn
- 0. Quay lại

**Tìm Kiếm:**
- 1. Tìm kiếm khách hàng theo tên
- 2. Tìm kiếm phòng theo mã
- 3. Tìm kiếm hóa đơn theo mã
- 0. Quay lại

**Thống Kê:**
- 1. Tổng doanh thu
- 2. Doanh thu theo khoảng ngày
- 3. Top khách hàng chi nhiều
- 0. Quay lại
---

## 5. Các Tệp Dữ Liệu

Tất cả dữ liệu được lưu trữ ở định dạng CSV (Giá Trị Được Phân Tách Bằng Dấu Phẩy) trong thư mục `data/`. Mỗi tệp được tự động tạo và cập nhật khi bạn chạy chương trình.

### customers.txt
**Định Dạng:** `CCCD,Tên,SĐT,Email,NgàySinh,ĐịaChỉ`

**Ví Dụ:**
```
012345678901,Le Quang Luyen,0912345678,kttuoij@gmail.com,1990-01-01,Hanoi
016532300860,Pham Hai Hoan,0949058119,t1win@gmail.com,20006-05-02,Ha Noi
```

### employees.txt
**Định Dạng:** `CCCD,Tên,SĐT,Email,VịTrí,Lương`

**Ví Dụ:**
```
089999999999,Tran Thi Dan,0901112222,lamo@gmail.com,Manager,1200
077777777777,Pham Thi Phuong Dung,0912223333,sktt1@gmail.com,Receptionist,800
01222031031,Pham Ba loc,11022131331,lmao@cpp.com,Manager,1000
```

### rooms.txt
**Định Dạng:** `MãPhòng,LoạiPhòng,Giá,SẵnCó`

**Ví Dụ:**
```
R101,Single,180,1
R102,Double,270,1
R203,Family,450,1
R304,Double,300,0
```

**Lưu Ý:** `SẵnCó` là `1` (có sẵn) hoặc `0` (đã đặt)

### invoices.txt
**Định Dạng:** `MãHóaĐơn,CCCDKHÁCH,MãPhòng,NgàyNhận,NgàyTrả,TổngTiền`

**Ví Dụ:**
```
INV002,023456789012,R102,2025-11-05,2025-11-07,600
INV09,016532300860,R304,2025-11-20,2025-11-25,1500
```

---

## Ghi Chú

- Tất cả các ngày đều ở định dạng **YYYY-MM-DD**
- CCCD (Căn Cước Công Dân) được sử dụng làm mã định danh duy nhất cho khách hàng và nhân viên
- Trạng thái sẵn có của phòng được quản lý tự động khi hóa đơn được tạo hoặc xóa
- Tất cả dữ liệu được lưu vào các tệp CSV khi bạn chọn "Lưu & Thoát" từ menu chính
- Hệ thống sử dụng tiếng Việt cho các lời nhắc menu và thông báo

---
## Phương Án Cải Tiến
- Do đây là bản thử nghiệm nên còn có thể cải tiến rất nhiều thứ:
+ Có thể thêm các chức năng khác như tính tiền lương của nhân viên,....
+ Vì hiện tại đây là góc nhìn của của quản lí nên có thể thêm các chức năng cho khách hàng như đặt phòng, thanh toán,.... cũng như nhân viên như chấm công,....
+ Thay vì xuất hiện luôn menu như trên có thể phân quyền cho người dùng (ví dụ là quản lý thì sẽ được toàn bộ quyền, nhân viên thì quyền sẽ thấp hơn, khách hàng thì chỉ có quyền xem thông tin của mình,....) trang đầu tiên sẽ là trang đăng nhập đăng kí thay vì như trên.
+ Thêm các tính năng tìm kiếm nâng cao hơn như tìm kiếm theo khoảng ngày,....
+ Thêm các tính năng thống kê nâng cao hơn như thống kê doanh thu theo nhân viên,....
+ Thêm các tính năng khác như kiểm tra phòng,....
+...
## Giấy Phép

Dự án này là một phần của bài tập giáo dục về hệ thống quản lý khách sạn bạn có thể thoải mái sửa đổi và cải thiện mã nguồn của dự án này.

## FROM LẤY GIÓ BẰNG TURBO WITH LOVE