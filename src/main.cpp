#include "RadixTree.h"
#include <limits> // thư viện để xóa bộ nhớ đệm cin

void printMenu() {
    cout << "\n=====================================" << endl;
    cout << "   ỨNG DỤNG TỪ ĐIỂN RADIX-TRIE" << endl;
    cout << "=====================================" << endl;
    cout << "1. Thêm từ mới" << endl;
    cout << "2. Tìm nghĩa của từ" << endl;
    cout << "3. Xem cấu trúc cây" << endl;
    cout << "4. Xóa một từ" << endl;
    cout << "0. Thoát chương trình" << endl;
    cout << "Lựa chọn của bạn: ";
}

int main() {
    system("chcp 65001"); // Hiển thị tiếng Việt
    RadixTree dictionary;

    dictionary.loadFromFile("data/dictionary.txt");

    int choice;
    string word, definition;

    while (true) {
        printMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Nhập từ tiếng Anh: ";
                cin >> word;
                cin.ignore(); 
                cout << "Nhập nghĩa của từ: ";
                getline(cin, definition);

                cout << "\n--- Đang thực hiện Thêm từ ---" << endl;
                dictionary.insert(word, definition);
                
                cout << "\n--- Cấu trúc cây sau khi THAY ĐỔI ---" << endl;
                dictionary.visualize(dictionary.getRoot(), 0);
                break;

            case 2:
                cout << "Nhập từ cần tra: ";
                cin >> word;
                cout << "Kết quả: " << dictionary.search(word) << endl;
                break;

            case 3:
                cout << "\n--- Cấu trúc Radix Tree HIỆN TẠI ---" << endl;
                dictionary.visualize(dictionary.getRoot(), 0);
                break;
            
            case 4:
                cout << "Nhập từ cần xóa: ";
                cin >> word;
                cout << "\n--- Đang thực hiện Xóa từ ---" << endl;
                dictionary.remove(word);
                
                cout << "\n--- Cấu trúc cây sau khi thay đổi ---" << endl;
                dictionary.visualize(dictionary.getRoot(), 0);
                break;
            
            case 0:
                cout << "Cảm ơn bạn đã sử dụng từ điển!" << endl;
                return 0;

            default:
                cout << "Lựa chọn không hợp lệ!" << endl;
        }
    }
    return 0;
}