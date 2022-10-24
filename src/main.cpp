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
        switch (select) {
            int num;
            cinReset();
            case help:
                out(help_info);
                break;
            case begin_:
                if (file.begin()) outl("移动到开头一行");
                break;
            case end_:
                if (file.end()) outl("移动到最后一行");
                break;
            case cursor:
                out("输出想移动的位置:");
                cin >> num;
                if(cin.fail()) break;
                file.setCursor(num);
                break;
            case front:
                if (file.frontLine()) outl("移动到当前的上一行");
                break;
            case next_:
                if (file.nextLine()) outl("移动到当前的下一行");
                break;
            case del:
                out("输入希望删除的有效行:");
                cin >> num;
                if (cin.fail()) break;
                file.delLine(num);
                break;
            case getLineNum:
                cout << "当前有" << file.getLineNum() << "行" << endl;
                break;
            case getCharsNum:
                cout << "当前有" << file.getCharNum() << "个字符" << endl;
                break;
            case insert:
                out("请输入插入位置(输入的数+1为插入后位置，行首输0):");
                cin >> num;
                if (cin.fail()) break;
                cin.get();
                out("请输入要添加的字符串:");
                getline(cin, src);
                file.insertLine(num, src);
                break;
            case subStr:
                cin.get();
                out("请输入被替换的子串:");
                getline(cin, src);
                out("请输入要替换的内容:");
                getline(cin, dest);
                file.replaceSubString(src, dest);
                break;
            case Search:
                out("请输入要查找的字串:");
                getline(cin, src);
                file.searchSubString(src);
                break;
            case replace:
                out("请输入要替换的行数:");
                cin >> num;
                if (cin.fail()) break;
                cin.get();
                out("请输入内容:");
                getline(cin, src);
                file.replaceLine(num, src);
                break;
            case show:
                file.view();
                break;
            case write:
                file.writeIn();
                outl("写入了文件");
                break;
            case read:
                file.read();
                outl("读取了文件");
                break;
            case quit:
                out("Quit System");
                exit(0);
                break;
            default:
                outl("无效的操作!");
                break;
        }
    }
    return 0;
}
