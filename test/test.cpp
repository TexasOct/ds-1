#include "fileControl.h"
#include <iostream>

void split() { cout << "--------------------" << endl; }

int main() {
    string fileIn = "test.txt";
    string fileOut = "out.txt";
    fileEditor testUnit(fileIn, fileOut);
    testUnit.view();
    split();

    testUnit.begin();
    testUnit.view();
    split();

    testUnit.end();
    testUnit.view();
    split();

    testUnit.setCursor(3);
    testUnit.view();
    split();

    testUnit.nextLine();
    testUnit.view();
    split();

    testUnit.frontLine();
    testUnit.view();
    split();

    testUnit.delLine(3);
    testUnit.view();
    split();

    testUnit.insertLine(2, "testLine");
    testUnit.view();
    split();

    testUnit.searchSubString("d");
    split();

    testUnit.replaceSubString("d", "t uo");
    split();

    testUnit.replaceLine(3, "test2323");
    testUnit.view();
    split();

    cout << testUnit.getLineNum() << endl;
    split();

    cout << testUnit.getCharNum() << endl;

    testUnit.read();
    testUnit.writeIn();
    testUnit.view();
    split();
}

