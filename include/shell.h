//
// Created by texas on 10/24/22.
//

#ifndef DS_1_SHELL_H
#define DS_1_SHELL_H

#include <iostream>

using namespace std;

class shell {
private:
    string * argv;
    unsigned args;


public:
    shell();
    void release();
    void getCommand();
    string returnArgv(unsigned level);
    void initShell();
};


