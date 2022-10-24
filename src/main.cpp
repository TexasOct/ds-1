#include <iostream>
#include "fileControl.h"

using namespace std;

enum option {
    help = 'h', begin_ = 'b', end_ = 'e', cursor = 'c', front = 'f', next_ = 'n',
    del = 'd', insert = 'i', Search = 'S', replace = 'r', getCharsNum = 'C',
    getLineNum = 'L',subStr = 'u',write = 'w', read = 'R', show = 's', quit = 'q'
};

void split() { cout << "--------------------" << endl; }

void out(string str) { cout << str; }

void outl(string str) { cout << str << endl; }

void cinReset() {
    string buf;
    cin.clear();
    getline(cin, buf);
}

const string help_info = "information:"
                         "\n 1.begin(b)\n 2.end(e)\n 3.cursorSet(c)\n 4.Move to front(f)\n 5.Move to next(n)\n"
                         " 6.delete line(d)\n 7.insert(i)\n 8.Search sub string(S)\n 9.replace line(r)\n "
                         "10.get total chars num(C)\n 11.get total lines num(L)\n 12.replace sub string(u)\n"
                         " 13.write into output file(w)\n 14.read from input file(R)\n 15.view the input file(s)\n"
                         " 16.quit system (q)\n";

int main() {
    string fileIn, fileOut;
    cout << "请输入要被读取的文件名:";
    getline(cin, fileIn);
    cout << "请输入要被写入的文件名:";
    getline(cin, fileOut);

    fileEditor file(fileIn, fileOut);
    while (1) {
        option select;
        string buf;
        if(cin.fail()) {
            outl("违规输入！请回车重新输入指令:");
            cinReset();
        }
        out("$ ");
        cin >> buf;
        string src, dest;
        select = static_cast<option>(buf[0]);
    }
    return 0;
}
