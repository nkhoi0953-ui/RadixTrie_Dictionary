#include "RadixTree.h"
#include <fstream>  // Thư viện đọc/ghi file
#include <sstream>  // Thư viện xử lý chuỗi

RadixTree::RadixTree() {
    root = new Node(); // Nút gốc rỗng
}

// Hàm tìm độ dài tiền tố chung giữa hai chuỗi
int getCommonPrefixLength(const string& s1, const string& s2) {
    int i = 0;
    while (i < s1.length() && i < s2.length() && s1[i] == s2[i]) {
        i++;
    }
    return i;
}

void RadixTree::insert(string word, string definition) {
    Node* curr = root;
    string remaining = word;

    while (remaining.length() > 0) {
        char firstChar = remaining[0];

        // Trường hợp 1: Không có nhánh nào bắt đầu bằng ký tự này -> Tạo mới
        if (curr->children.find(firstChar) == curr->children.end()) {
            curr->children[firstChar] = new Node(remaining);
            curr->children[firstChar]->isEndOfWord = true;
            curr->children[firstChar]->definition = definition;
            cout << "[Insert] Tao nut moi cho: " << remaining << endl;
            return;
        }

        Node* child = curr->children[firstChar];
        int commonLen = getCommonPrefixLength(remaining, child->edgeLabel);

        // Trường hợp 2: Tách nút (Split) - Tiền tố chung ngắn hơn nhãn hiện có
        if (commonLen < child->edgeLabel.length()) {
            string commonPrefix = child->edgeLabel.substr(0, commonLen);
            string oldSuffix = child->edgeLabel.substr(commonLen);
            string newSuffix = remaining.substr(commonLen);

            // Tách nút cũ thành nút trung gian
            child->edgeLabel = commonPrefix;
            Node* oldChildNode = new Node(oldSuffix);
            oldChildNode->isEndOfWord = child->isEndOfWord;
            oldChildNode->definition = child->definition;
            oldChildNode->children = child->children;

            child->children.clear();
            child->children[oldSuffix[0]] = oldChildNode;
            child->isEndOfWord = false;
            child->definition = "";

            cout << "[Split] Tách tại '" << commonPrefix << "'. Tạo nhánh cũ: '" << oldSuffix << "'";

            // Nếu còn phần dư mới thì tạo nhánh mới, nếu không thì chính nút trung gian là từ mới
            if (newSuffix.length() > 0) {
                Node* newNode = new Node(newSuffix);
                newNode->isEndOfWord = true;
                newNode->definition = definition;
                child->children[newSuffix[0]] = newNode;
                cout << " va nhánh mới: '" << newSuffix << "'" << endl;
            } else {
                child->isEndOfWord = true;
                child->definition = definition;
                cout << " (Nút trung gian la kết thúc từ)" << endl;
            }
            return;
        }

        // Trường hợp 3: Khớp hoàn toàn nhãn hiện tại, đi tiếp xuống con
        remaining = remaining.substr(commonLen);
        curr = child;
        
        if (remaining.length() == 0) {
            curr->isEndOfWord = true;
            curr->definition = definition;
            cout << "[Update] Cập nhật nghĩa cho từ: " << word << endl;
        }
    }
}



string RadixTree::search(string word) {
    Node* curr = root;
    string remaining = word;

    while (remaining.length() > 0) {
        char firstChar = remaining[0];

        // Nếu không có nhánh bắt đầu bằng ký tự này
        if (curr->children.find(firstChar) == curr->children.end()) {
            return "Không tìm thấy từ này trong từ điển!";
        }

        Node* child = curr->children[firstChar];
        
        // Kiểm tra độ dài tiền tố chung giữa từ còn lại và nhãn trên cạnh
        int commonLen = 0;
        while (commonLen < remaining.length() && 
               commonLen < child->edgeLabel.length() && 
               remaining[commonLen] == child->edgeLabel[commonLen]) {
            commonLen++;
        }

        // Nếu không khớp hoàn toàn nhãn của cạnh thì không tồn tại từ này
        if (commonLen < child->edgeLabel.length()) {
            return "Không tìm thấy từ này trong từ điển!";
        }

        // Cắt bỏ phần đã khớp và đi sâu xuống cây
        remaining = remaining.substr(commonLen);
        curr = child;
    }

    // Sau khi duyệt hết chuỗi, kiểm tra xem nút hiện tại có phải là điểm kết thúc từ không
    if (curr->isEndOfWord) {
        return curr->definition;
    }

    return "Không tìm thấy từ này trong từ điển!";
}


void RadixTree::remove(string word) {
    if (word.empty()) return;

    // Cấu trúc để lưu lại lộ trình đi xuống, phục vụ việc gộp nút sau khi xóa
    struct PathNode {
        Node* node;
        char firstChar;
    };
    vector<PathNode> path;
    Node* curr = root;
    string remaining = word;

    //Tìm nút chứa từ cần xóa
    while (remaining.length() > 0) {
        char firstChar = remaining[0];
        if (curr->children.find(firstChar) == curr->children.end()) {
            cout << "[Lỗi] Không tìm thấy từ '" << word << "' để xóa." << endl;
            return;
        }

        Node* child = curr->children[firstChar];
        int commonLen = getCommonPrefixLength(remaining, child->edgeLabel);

        if (commonLen < child->edgeLabel.length()) {
            cout << "[Lỗi] Không tìm thấy từ '" << word << "' để xóa." << endl;
            return;
        }

        path.push_back({curr, firstChar});
        remaining = remaining.substr(commonLen);
        curr = child;
    }

    if (!curr->isEndOfWord) {
        cout << "[Lỗi] Từ '" << word << "' không tồn tại chính xác." << endl;
        return;
    }

    //Bỏ đánh dấu kết thúc từ
    curr->isEndOfWord = false;
    curr->definition = "";
    cout << "[Xóa] Đã bỏ đánh dấu kết thúc từ cho '" << word << "'." << endl;

    //Thu dọn và Gộp nút 
    // Nếu nút vừa xóa không có con, ta xóa hẳn nút đó khỏi cha
    if (curr->children.empty()) {
        Node* parent = path.back().node;
        char charInParent = path.back().firstChar;
        delete parent->children[charInParent];
        parent->children.erase(charInParent);
        cout << "[Dọn dẹp] Đã xóa nút lá không còn sử dụng." << endl;

        // Sau khi xóa nút lá, kiểm tra xem nút cha có cần gộp không
        if (parent != root && !parent->isEndOfWord && parent->children.size() == 1) {
            auto it = parent->children.begin();
            Node* loneChild = it->second;
            
            parent->edgeLabel += loneChild->edgeLabel;
            parent->isEndOfWord = loneChild->isEndOfWord;
            parent->definition = loneChild->definition;
            parent->children = loneChild->children;
            
            delete loneChild;
            cout << "[Merge] Đã gộp nút cha với nút con duy nhất còn lại." << endl;
        }
    } 
    // Nếu nút vừa xóa vẫn còn con, kiểm tra xem nó có trở thành nút trung gian chỉ có 1 con không
    else if (curr->children.size() == 1) {
        auto it = curr->children.begin();
        Node* loneChild = it->second;
        
        curr->edgeLabel += loneChild->edgeLabel;
        curr->isEndOfWord = loneChild->isEndOfWord;
        curr->definition = loneChild->definition;
        curr->children = loneChild->children;
        
        delete loneChild;
        cout << "[Merge] Nút hiện tại chỉ còn 1 con, đã thực hiện gộp cạnh." << endl;
    }
}



void RadixTree::visualize(Node* curr, int indent) {
    if (!curr) return;
    
    // Tạo khoảng trống để phân cấp cây
    for (int i = 0; i < indent; i++) cout << "  ";
    
    if (curr == root) {
        cout << "[ROOT]" << endl;
    } else {
        cout << "|--" << curr->edgeLabel;
        if (curr->isEndOfWord) cout << " (*)"; // Đánh dấu nếu là từ hoàn chỉnh
        cout << endl;
    }

    // Duyệt qua tất cả các con
    for (auto const& [firstChar, childNode] : curr->children) {
        visualize(childNode, indent + 1);
    }
}


void RadixTree::loadFromFile(string filePath) {
    ifstream file(filePath);

    if (!file.is_open()) {
        cout << "[!] Không tìm thấy file: " << filePath << ". Bắt đầu với cây rỗng." << endl;
        return;
    }

    string line;
    int count = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string word, definition;

        if (getline(ss, word, '|') && getline(ss, definition)) {
            // Gọi hàm insert của Class này
            this->insert(word, definition);
            count++;
        }
    }
    cout << "[Thông báo] Đã nạp thành công " << count << " từ vào Radix Tree." << endl;
    file.close();
}