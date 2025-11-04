
# Gaylgbt
=======
1. Phát biểu bài toán và lý do chọn

-Phát biểu bài toán: Xây dựng một hệ thống phần mềm quản lý cho một “Khách sạn mini” (Hotel Mini) cho phép quản lý thông tin: khách hàng, phòng, nhân viên, và hóa đơn. Hệ thống phải hỗ trợ thao tác thêm/sửa/xóa/danh sách, tìm kiếm, lưu/đọc dữ liệu từ file và thống kê doanh thu.
-Lý do chọn: Khách sạn nhỏ/nhà nghỉ/nhà trọ là một bài toán điển hình cho OOP: có nhiều thực thể (khách hàng, phòng, nhân viên, hóa đơn) tương tác với nhau; cần lưu trữ bền vững; có nghiệp vụ (đặt phòng, thanh toán, thống kê) phù hợp để thể hiện kế thừa, đóng gói, đa hình, và xử lý file — phù hợp là đề tài tiểu luận môn “Lập trình nâng cao với C++”.

1.5.Mục đích của chương trình

Cung cấp công cụ console đơn giản, trực quan để quản lý mọi nghiệp vụ cơ bản của khách sạn mini.

Luyện tập và minh họa các khái niệm OOP trong C++: lớp, kế thừa, đa hình, nạp chồng toán tử, friend function.

Thực hiện lưu trữ dữ liệu bằng file để đảm bảo tính bền vững (persistent storage).

Hỗ trợ chức năng tìm kiếm và thống kê doanh thu để đánh giá hoạt động kinh doanh.

2.Phân tích mô tả chức năng 

*Chức năng chính:

-Quản lý phòng: Thêm/sửa/xóa/phân loại (đơn, đôi), thay đổi trạng thái (trống/đang thuê), hiển thị danh sách.

-Quản lý khách hàng: Thêm/sửa/xóa, lưu trữ thông tin cá nhân, xem lịch sử thuê.

-Quản lý nhân viên: Thêm/sửa/xóa, phân quyền (nếu cần mở rộng).

-Quản lý hóa đơn: Tạo hóa đơn khi khách thuê/phòng trả, lưu thông tin ngày giờ, tổng tiền.

-Tìm kiếm: Tìm phòng theo số/phân loại/trạng thái; tìm khách theo ID/tên; tìm hóa đơn theo ID/ngày.

-Thống kê doanh thu: Tổng doanh thu, doanh thu theo khoảng thời gian, doanh thu theo phòng, top khách hàng theo chi tiêu.

-File I/O: Lưu/đọc dữ liệu (rooms.txt, customers.txt, employees.txt, invoices.txt) theo định dạng text CSV dễ đọc.

-Giao diện: Menu console dễ thao tác.

*Yêu cầu kỹ thuật

-Áp dụng lập trình hướng đối tượng: lớp, đối tượng, đóng gói.

-Sử dụng kế thừa và đa hình (ví dụ Person là lớp cha, Customer và Employee là lớp con).

-Nạp chồng toán tử << / >> cho nhập xuất thuận tiện; nạp chồng toán tử so sánh để sắp xếp hoặc kiểm tra bằng.

-Sử dụng friend function khi cần truy cập trực tiếp thành viên private cho việc so sánh/ghi file.

-File I/O: đọc/ghi file text, kiểm tra tồn tại file, xử lý ngoại lệ cơ bản.

*Kiểm thử: cung cấp một số tình huống kiểm thử mẫu (thêm dữ liệu, tạo hóa đơn, thống kê).

3.Xác định các lớp và cấu trúc dữ liệu 

*Các lớp chính:

-Person (abstract/base)

+Thuộc tính: id, name, phone, email

+Phương thức ảo: virtual void display() const

-Customer : public Person

+Thuộc tính bổ sung: dateOfBirth, address

+Lưu lịch sử (list invoice ids) nếu muốn mở rộng

-Employee : public Person

+Thuộc tính bổ sung: position, salary

-Room

+Thuộc tính: roomNumber (string), roomType (enum: Single/Double/Family...), pricePerNight (double), isAvailable (bool)

+Phương thức: đổi trạng thái, hiển thị

-Invoice

+Thuộc tính: invoiceID, customerID, roomNumber, dateFrom (string), dateTo (string), totalAmount (double)

+Phương thức: tính tổng tiền từ ngày đến ngày (dựa trên price per night)

-HotelManager (quản lý dữ liệu tại runtime)

+Thuộc tính: vector<Customer> customers, vector<Employee> employees, vector<Room> rooms, vector<Invoice> invoices

+Phương thức: load/save file, add/edit/delete cho từng loại, tìm kiếm, thống kê
>>>>>>> cf23735 (Code lan 1)
