#include <iostream>
#include "fileControl.h"

using namespace std;

enum option {
    help = 'h', begin_ = 'b', end_ = 'e', cursor = 'c', front = 'f', next_ = 'n',
    del = 'd', insert = 'i', Search = 'S', replace = 'r', getCharsNum='C', getLineNum = 'L',subStr='u',
    write='w', read = 'R', show = 's', quit = 'q'
};

void split() { cout << "--------------------" << endl; }
void out(string str){cout << str << endl;}

string help_info = "information:"
                   "\nbegin(b),end(e),cursorSet(c),Move to front(f),Move to next(n),"
                   "\ndelete line(d),";

int main() {

    string fileIn, fileOut;
    cout << "请输入要被读取的文件名:" << endl;
    cin >> fileIn;
    cout << "请输入要被写入的文件名:" << endl;
    cin >> fileOut;

    fileEditor file(fileIn, fileOut);

    while (1) {
        option select;
        char buf;
        out("*****************");
        out("请输入操作(h查询):");
        cin >> buf;
        cout << endl;
        string src, dest;
        select = static_cast<option>(buf);
        switch (select) {
            int num;
            case help:
                out(help_info);
                break;
            case begin_:
                if(file.begin()) out("移动到开头一行");
                break;
            case end_:
                if(file.end()) out("移动到最后一行");
                break;
            case cursor:
                out("输出想移动的位置:");
                cin >> num;
                file.setCursor(num);
                break;
            case front:
                if(file.frontLine()) out("移动到当前的上一行");
                break;
            case next_:
                if(file.nextLine()) out("移动到当前的下一行");
                break;
            case del:
                out("输入希望删除的有效行:");
                cin >> num;
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
                out("请输入要添加的字符串:");
                cin >> src;
                file.insertLine(num, src);
                break;
            case subStr:
                out("请输入被替换的子串:");
                cin >> src;
                out("请输入要替换的内容:");
                cin >> dest;
                file.replaceSubString(src, dest);
                break;
            case Search:
                out("请输入要查找的字串:");
                cin >> src;
                file.searchSubString(src);
                break;
            case replace:
                out("请输入要替换的行数:");
                cin >> num ;
                out("请输入内容:");
                cin >> src;
                file.replaceLine(num,src);
                break;
            case show:
                file.view();
                break;
            case write:
                file.writeIn();
                break;
            case read:
                file.read();
                break;
            case quit:
                out("Quit System");
                exit(0);
                break;
            default:
                out("无效的操作!");
        }
    }
    return 0;
}
