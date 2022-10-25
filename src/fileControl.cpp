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
    if(nullSignal) return;
    Node *tmp = head->rear;
    while (tmp != nullptr) {
        tmp = _delNode(tmp);
    }
    _delNode(tmp);
}


fileEditor::fileEditor(string fileI, string fileO) {
    string buf;
    fstream ptr;
    file = std::move(fileI);
    fileOut = std::move(fileO);
    ptr.open(file, fstream::out);

    while (getline(ptr, buf)) {
        cursor = _setNode(cursor, buf);
        pos++;
    }// 创建文件 链表
    if(pos == 0) nullSignal = true;
    ptr.close();
}

bool fileEditor::begin() {
    if (nullSignal) return false;
    cursor = _getNode(1);
    pos = 1;
    return true;
}

bool fileEditor::end() {
    if (nullSignal) return false;
    cursor = _getNode(line);
    pos = line;
    return true;
}

bool fileEditor::frontLine() {
    if (nullSignal) return false;
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
    if (nullSignal) return false;
    if (cursor->rear != nullptr) {
        cursor = cursor->rear;
        pos++;
        return true;
    } else {
        cout << "illegal range, please use a legal value" << endl;
        return false;
    }
}

bool fileEditor::setCursor(int num) {
    if (nullSignal) return false;
    if ((num <= line) && (num >= 1)) {
        cursor = _getNode(num);
        pos = num;
        return true;
    } else {
        cout << "out of range, please write a legal number" << endl;
        return false;
    }
}

void fileEditor::delLine(int num) {
    if (nullSignal) return;
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
        if (line == 0) nullSignal = true;
    } else {
        cout << "illegal range" << endl;
    }
}

void fileEditor::insertLine(int num, string str) {
    if (num <= line + 1 && num >= 0) {
        _setNode(_getNode(num), std::move(str));
        if(pos == 0){
            nullSignal = false;
            begin();
        }
    } else {
        cout << "illegal operate" << endl;
    }
}

void fileEditor::searchSubString(const string &str) const {
    if (nullSignal) {cout << "file is empty!"; return;}
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
    if (nullSignal) {cout << "file is empty!"; return;}
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
    if (nullSignal) {cout << "file is empty!"; return;}
    _modifyNode(l, std::move(str));
}

int fileEditor::getLineNum() const {
    if (nullSignal) return 0;
    return line;
}

unsigned long fileEditor::getCharNum() const {
    if (nullSignal) return 0;
    unsigned long sum = 0;
    Node *tmp = head->rear;
    while (tmp->rear != nullptr) {
        sum += tmp->data.length();
        tmp = tmp->rear;
    }
    sum += tmp->data.length();
    return sum;
}

bool fileEditor::writeIn() const {
    ofstream ptr;
    ptr.open(fileOut);
    if (nullSignal) { cout << "Empty stack" << endl;
        return false; }
    Node *tmp = head->rear;
    while (tmp->rear != nullptr) {
        ptr << tmp->data << endl;
        tmp = tmp->rear;
    }
    ptr << tmp->data;
    ptr.close();
    return true;
}

bool fileEditor::read() {
    char choose;
    cout << "Please confirm (y/n):";
    cin.get(choose);
    cin.get();
    if (choose == 'y') {
        if (!nullSignal){
            cursor = nullptr;
            _delBuffer();
        }
        cursor = head;
        cursor->rear = nullptr;
        nullSignal - true;
        pos = 0;
        string buf;
        ifstream ptr;
        ptr.open(file);
        while (getline(ptr, buf)) {
            cursor = _setNode(cursor, buf);
            pos++;
        }// 创建文件 链表
        if (pos > 0) nullSignal = false;
        ptr.close();
        return true;
    }
}

void fileEditor::view() const {
    try {
        int count = 1;
        Node *tmp = head->rear;
        if(nullSignal){
            cout << "file is null" << endl;
            return;
        }
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

