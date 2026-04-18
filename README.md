📘 Radix Tree Dictionary (English - Vietnamese)

Ứng dụng từ điển Anh - Việt được xây dựng dựa trên cấu trúc dữ liệu Radix Tree (Compressed Trie). Dự án tập trung vào việc tối ưu hóa bộ nhớ và hiệu năng tìm kiếm thông qua kỹ thuật nén cạnh (edge compression).

✨ Features
🚀 Memory Optimization
Giảm số lượng node bằng cách nén các chuỗi node chỉ có một con thành một cạnh duy nhất.
⚙️ Core Operations
Insert: Tự động xử lý node splitting khi có tiền tố chung.
Remove: Tự động node merging để duy trì cấu trúc tối ưu.
Search: Độ phức tạp O(k) với k là độ dài từ khóa.
📂 Data Management
Tự động load dữ liệu từ data/dictionary.txt.

Định dạng đơn giản:

word|meaning
🌳 Visualization
Hiển thị cấu trúc cây trực tiếp trên console.
Giúp dễ dàng debug và theo dõi dữ liệu.
📁 Project Structure
RadixTrie_Dictionary/
├── data/
│   └── dictionary.txt      # Dictionary data (word|meaning)
├── src/
│   ├── main.cpp            # CLI & user interaction
│   ├── RadixTree.h         # Data structure definition
│   └── RadixTree.cpp       # Implementation (Split/Merge/Search)
├── README.md
└── .gitignore
🚀 Getting Started
🔧 Requirements
C++ compiler (GCC / MinGW)
C++11 or higher
▶️ Build & Run
# Compile
g++ src/main.cpp src/RadixTree.cpp -o dictionary

# Run (Windows)
dictionary.exe

# Run (Linux/macOS)
./dictionary
🛠 Core Algorithms
1. Node Splitting

Khi chèn một từ mới có tiền tố chung một phần với node hiện tại:

Tách cạnh hiện tại thành:
Một node trung gian (common prefix)
Hai nhánh con riêng biệt

➡️ Đảm bảo mỗi cạnh luôn biểu diễn tiền tố chung dài nhất.

2. Node Merging

Khi xóa một từ:

Nếu node trung gian chỉ còn 1 node con
Thực hiện gộp node với node con

➡️ Giảm chiều cao cây và tiết kiệm bộ nhớ.