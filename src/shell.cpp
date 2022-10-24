//
// Created by texas on 10/24/22.
//

#include <sstream>
#include <string>
#include <iostream>
#include "shell.h"

shell::shell() {
   initShell();
}

void shell::initShell(){
    args = 0;
    argv = nullptr;
}
void shell::release(){
    delete argv;
    argv = nullptr;
    args = 0;
}

void shell::getCommand() {
    argv = new string[11];
    string buffer;
    istringstream buf;
    int count = 0;
    buf.str("test");
    getline(cin, buffer);
    buf.str(buffer);
    while(getline(buf, argv[count++], ' ') && count <= 10);
}

string shell::returnArgv(unsigned level){
    return argv[0];
}




