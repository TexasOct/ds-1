//
// Created by texas on 10/17/22.
//
#ifndef DS_1_FILECONTROL_H
#define DS_1_FILECONTROL_H

#include <iostream>
#include <fstream>

using namespace std;


struct Node {
    string data;
    struct Node *front{};
    struct Node *rear{};
};

class fileEditor {
private:
    string file;
    string fileOut;
    int line = 0;
    unsigned pos = 0;
    Node *head = new Node;
    Node *cursor = head;
    bool nullSignal = true;
// 子模块
    Node *_getNode(int lineNum); // 获取节点
    Node *_setNode(Node *ptr, string line); // 设置节点
    void _delNode(int lineNum); // 删除节点
    Node *_delNode(Node *ptr); // 删除节点，并返回cursor
    void _modifyNode(int lineNum, string modify); // 修改节点字段
    static void _replaceData(string * str, const string& src, const string& dest);
    void _delBuffer();

public:// 对外实现
    explicit fileEditor(string fileIn, string fileOut); //构造函数
    ~fileEditor() = default;;
    bool begin();//移动 cursor 到行首
    bool end();//移动 cursor 到行尾
    bool setCursor(int num);//移动 cursor 到指定位置
    bool frontLine();// 移动 cursor 到前一行
    bool nextLine();// 移动 cursor 到下一行
    void delLine(int num);// 删除某一行
    void insertLine(int num, string strings);// 在某个节点前加一行
    void searchSubString(const string &subString) const;// 寻找字串所在的行
    void replaceSubString(const string &subString, const string &methodString);// 替换所有字串
    void replaceLine(int lineNum, string String);// 替换行字段
    int getLineNum() const; // 获取总行数
    unsigned long getCharNum() const; // 获取字符总数
    bool writeIn() const; // 写入到写入文件
    bool read(); // 再次读取该文件，执行覆写
    void view() const;// 查看当前文件
    void showCursor(int count) const;
};

#endif //DS_1_FILECONTROL_H