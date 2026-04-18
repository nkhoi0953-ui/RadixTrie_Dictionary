#ifndef RADIXTREE_H
#define RADIXTREE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct Node {
    map<char, Node*> children; 
    string edgeLabel;          
    bool isEndOfWord;          
    string definition;         

    Node(string label = "") : edgeLabel(label), isEndOfWord(false), definition("") {}
};

class RadixTree {
private:
    Node* root;

    // Hàm bổ trợ để tìm tiền tố chung giữa hai chuỗi
    int getFirstDiffIndex(const string& s1, const string& s2);

public:
    RadixTree();

    void loadFromFile(string filePath);
    
    // 3 thao tác chính
    void insert(string word, string definition);
    string search(string word);
    void remove(string word);

    // Hàm để in cấu trúc cây 
    void visualize(Node* curr, int indent);
    Node* getRoot() { return root; }
};

#endif