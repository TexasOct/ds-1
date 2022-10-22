//
// Created by texas on 10/17/22.
//
#include "fileControl.h"
#include <utility>
#include <cstring>

using namespace std;

Node *fileEditor::_setNode(Node *ptr, string dataline) {
    Node *tmp = new Node;
    Node *swp = ptr->rear;

    tmp->data = std::move(dataline);

    ptr->rear = tmp;
    tmp->front = ptr;

    if (swp != nullptr) {
        tmp->rear = swp;
        swp->front = tmp;
    }

    ptr = tmp;
    line++;
    return ptr;
}

void fileEditor::_delNode(int l) {
    Node *tmp = _getNode(l);
    Node *swp = tmp->front;

    if (tmp->rear != nullptr) {
        swp->rear = tmp->rear;
        tmp->front = swp;
    } else {
        swp->rear = nullptr;
    }
    delete tmp;
    line--;
}

Node *fileEditor::_delNode(Node *ptr) {
    Node *tmp = ptr;
    Node *swp = tmp->front;
    ptr = ptr->rear;
    if (tmp->rear != nullptr) {
        swp->rear = tmp->rear;
        tmp->front = swp;
    } else {
        swp->rear = nullptr;
    }
    delete tmp;
    line--;
    return ptr;
}

Node *fileEditor::_getNode(int l) {
    Node *tmp = head;
    for (int i = 0; i < l; i++) {
        tmp = tmp->rear;
    }
    return tmp;
}

void fileEditor::_modifyNode(int l, string m) {
    Node *tmp = _getNode(l);
    tmp->data = std::move(m);
}

void fileEditor::_replaceData(string *str, const string &src, const string &dest) {
    size_t position;
    position = (*str).find(src);
    while (position != -1) {
        (*str).replace(position, src.length(), dest);
        position = (*str).find(src);
    }
}

void fileEditor::_delBuffer() {
    Node *tmp = head->rear;
    while (tmp->rear != nullptr) {
        tmp = _delNode(tmp);
    }
    _delNode(tmp);
}

fileEditor::fileEditor(string fileI, string fileO) {
    string buf;
    ifstream ptr;
    this->file = std::move(fileI);
    this->fileOut = std::move(fileO);
    ptr.open(this->file);
    while (getline(ptr, buf)) {
        cursor = _setNode(cursor, buf);
        pos++;
    }// 创建文件 链表
    ptr.close();
}

bool fileEditor::begin() {
    cursor = _getNode(1);
    pos = 1;
    return true;
}

bool fileEditor::end() {
    cursor = _getNode(line);
    pos = line;
    return true;
}

bool fileEditor::frontLine() {
    if (cursor->front != nullptr) {
        cursor = cursor->front;
        pos--;
        return true;
    } else {
        cout << "illegal range, please use a legal value" << endl;
        return false;
    }
}

bool fileEditor::nextLine() {
    if (cursor->rear != nullptr) {
        cursor = cursor->rear;
        pos++;
        return true;
    } else {
        cout << "illegal range, please use a legal value" << endl;
        return false;
    }
}

void fileEditor::setCursor(int num) {
    if ((num <= line) && (num >= 1)) {
        cursor = _getNode(num);
        pos = num;
    } else {
        cout << "out of range, please write a legal number" << endl;
        return;
    }
}

void fileEditor::delLine(int num) {
    if (num <= line && num >= 1) {
        if (pos > num) {
            pos--;
        } else if (pos == num && &cursor == &head) { // if cursor in head
            cursor = cursor->rear;
        } else if (pos == num && cursor->rear == nullptr) { // if cursor in tail
            pos--;
            cursor = cursor->front;
        }
        _delNode(num);
    } else {
        cout << "illegal  operate" << endl;
    }
}

void fileEditor::insertLine(int num, string str) {
    _setNode(_getNode(num), std::move(str));
}

void fileEditor::searchSubString(const string &str) const {
    Node *tmp = head->rear;
    int count = 1;
    while (tmp->rear != nullptr) {
        if (tmp->data.find(str) != string::npos) {
            cout << count << " | " << tmp->data << endl;
        }
        count++;
        tmp = tmp->rear;
    }
    if (tmp->data.find(str) != string::npos) {
        cout << count << " | " << tmp->data << endl;
    }
}

void fileEditor::replaceSubString(const string &str, const string &method) {
    Node *tmp = head->rear;
    int count = 1;
    while (tmp->rear != nullptr) {
        if (tmp->data.find(str) != string::npos) {
            _replaceData(&tmp->data, str, method);
            cout << count << " | " << tmp->data << endl;
        }
        count++;
        tmp = tmp->rear;
    }
    if (tmp->data.find(str) != string::npos) {
        _replaceData(&tmp->data, str, method);
        cout << count << " | " << tmp->data << endl;
    }
}

void fileEditor::replaceLine(int l, string str) {
    _modifyNode(l, std::move(str));
}

int fileEditor::getLineNum() const {
    return line;
}

unsigned long fileEditor::getCharNum() const {
    unsigned long sum = 0;
    Node *tmp = head->rear;
    while (tmp->rear != nullptr) {
        sum += tmp->data.length();
        tmp = tmp->rear;
    }
    sum += tmp->data.length();
    return sum;
}

void fileEditor::writeIn() const {
    ofstream ptr;
    ptr.open(fileOut);
    Node *tmp = head->rear;
    while (tmp->rear != nullptr) {
        ptr << tmp->data << endl;
        tmp = tmp->rear;
    }
    ptr << tmp->data;
    ptr.close();
}

void fileEditor::read() {
    char choose;
    cout << "Please confirm (y/n):";
    cin >> choose;
    if (choose == 'y') {
        cursor = nullptr;
        _delBuffer();
        cursor = head;
        cursor->rear = nullptr;
        pos = 0;
        string buf;
        ifstream ptr;
        ptr.open(this->file);
        while (getline(ptr, buf)) {
            cursor = _setNode(cursor, buf);
            pos++;
        }// 创建文件 链表
        ptr.close();
    }
}

void fileEditor::view() const {
    try {
        int count = 1;
        Node *tmp = head->rear;
        while (tmp->rear != nullptr) {
            cout << count++ << " | " << tmp->data;
            showCursor(count - 1);
            cout << endl;
            tmp = tmp->rear;
        }
        cout << count << " | " << tmp->data;
        showCursor(count);
        cout << endl;
    }catch(const char * e){
        cout << "Error:" << e << endl;
    }
}

void fileEditor::showCursor(int count) const {
    if (pos == count) cout << "  _";
}