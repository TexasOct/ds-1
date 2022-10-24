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
                   "\n b - Move cursor to first line\n e - Move cursor to the last line\n c - Set cursor to the expect line\n f - Move to front\n n - Move to next"
                   "\n d - delete line\n i - insert\n S - Search sub string\n r - replace line"
                   "\n C - get total chars num\n L - get total lines num\n u - replace sub string"
                   "\n w - write into output file\n R - read from input file\n s - view the input file"
                   "\n q - quit system \n";

int main() {
    string fileIn, fileOut;
    cout << "Enter the input file name:";
    getline(cin, fileIn);
    cout << "Enter the output file name:";
    getline(cin, fileOut);

    fileEditor file(fileIn, fileOut);
    while (1) {
        option select;
        string buf;
        if(cin.fail()) {
            outl("illegal entries！Enter to retry:");
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
                if (file.begin()) outl("Move to the first line");
                break;
            case end_:
                if (file.end()) outl("Move to the last line");
                break;
            case cursor:
                out("Enter the line which you want to move:");
                cin >> num;
                if(cin.fail()) break;
                file.setCursor(num);
                break;
            case front:
                if (file.frontLine()) outl("Move to the front line");
                break;
            case next_:
                if (file.nextLine()) outl("Move to the rear line");
                break;
            case del:
                out("Enter the line you want to delete with a legal value:");
                cin >> num;
                if (cin.fail()) break;
                file.delLine(num);
                break;
            case getLineNum:
                cout << "Threre have" << file.getLineNum() << "lines" << endl;
                break;
            case getCharsNum:
                cout << "There have" << file.getCharNum() << "chars" << endl;
                break;
            case insert:
                out("Input the position you want to insert(it will insert in x + 1, enter 0 insert to first line):");
                cin >> num;
                if (cin.fail()) break;
                cin.get();
                out("Enter the string you want to add:");
                getline(cin, src);
                file.insertLine(num, src);
                break;
            case subStr:
                cin.get();
                out("Enter the src substring:");
                getline(cin, src);
                out("Enter the dest substring:");
                getline(cin, dest);
                file.replaceSubString(src, dest);
                break;
            case Search:
                out("Enter the target string:");
                getline(cin, src);
                file.searchSubString(src);
                break;
            case replace:
                out("Enter the line you want to replace:");
                cin >> num;
                if (cin.fail()) break;
                cin.get();
                out("Enter the string:");
                getline(cin, src);
                file.replaceLine(num, src);
                break;
            case show:
                file.view();
                break;
            case write:
                file.writeIn();
                outl("Write into the output file");
                break;
            case read:
                file.read();
                outl("Reread the input file");
                break;
            case quit:
                out("Quit System");
                exit(0);
                break;
            default:
                outl("illegal operation!");
                break;
        }
    }
    return 0;
}
