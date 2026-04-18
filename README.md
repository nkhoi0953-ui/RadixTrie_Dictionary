📘 Radix Tree Dictionary (English - Vietnamese)
Dự án này là một ứng dụng từ điển Anh - Việt được xây dựng dựa trên cấu trúc dữ liệu Radix Tree. Đây là một phiên bản nâng cao của cấu trúc Trie thông thường, tập trung vào việc tối ưu hóa không gian bộ nhớ thông qua cơ chế Nén cạnh (Edge Compression).
✨ Tính năng nổi bật
Tối ưu hóa bộ nhớ: Nén các nút chỉ có một con vào một cạnh duy nhất, giảm thiểu số lượng nút trên cây.
Thao tác nâng cao:
    Thêm từ (Insert): Tự động xử lý logic Split Node khi gặp tiền tố chung.
    Xóa từ (Remove): Tự động xử lý logic Merge Node để duy trì tính chất nén của cây.
    Tra cứu (Search): Tốc độ tìm kiếm tối ưu $O(k)$ với $k$ là độ dài của từ.
Quản lý dữ liệu:
    Nạp dữ liệu tự động từ file data/dictionary.txt khi khởi động.
    Hỗ trợ định dạng nghĩa của từ trên một dòng đơn giản, dễ quản lý.
Trực quan hóa (Visualization): Hiển thị cấu trúc phân cấp của cây ngay trên Console để theo dõi sự thay đổi dữ liệu.
📂 Cấu trúc dự án
RadixTrie_Dictionary/
├── data/
│   └── dictionary.txt    # File chứa dữ liệu từ điển (từ|nghĩa)
├── src/
│   ├── main.cpp          # Xử lý Menu và tương tác người dùng
│   ├── RadixTree.h       # Khai báo cấu trúc Node và lớp RadixTree
│   └── RadixTree.cpp     # Hiện thực hóa các giải thuật Split/Merge/Search
├── README.md             # Tài liệu hướng dẫn dự án
└── .gitignore            # Loại bỏ các file thực thi khi đẩy lên GitHub
🚀 Hướng dẫn biên dịch và chạy
Yêu cầu hệ thống
    Trình biên dịch C++ (GCC/MinGW) hỗ trợ chuẩn C++11 trở lên.
Các bước thực hiện
    Mở Terminal (hoặc Command Prompt) tại thư mục gốc của dự án.
    Biên dịch mã nguồn:
        g++ src/main.cpp src/RadixTree.cpp -o dictionary
Chạy ứng dụng:
    Windows: .\dictionary.exe
    Linux/macOS: ./dictionary
🛠 Giải thuật then chốt
1. Cơ chế Tách nút (Node Splitting)Khi chèn một từ mới có tiền tố chung một phần với nhãn hiện tại, hệ thống sẽ thực hiện chia tách cạnh cũ thành một nút trung gian và hai nhánh con mới. Điều này đảm bảo mỗi cạnh luôn đại diện cho tiền tố chung dài nhất có thể.
2. Cơ chế Gộp nút (Node Merging)Khi một từ bị xóa và để lại một nút trung gian chỉ còn duy nhất một con, hệ thống sẽ tự động gộp nhãn của nút đó với nút con của nó để rút gọn chiều cao của cây và tiết kiệm bộ nhớ.