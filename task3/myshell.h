//
// Created by marcel on 11/16/23.
//

#ifndef SYSPROGTASKS_MYSHELL_H
#define SYSPROGTASKS_MYSHELL_H


#include <stdbool.h>

int main();

void execute(bool background);

void new_command(char* name);

void add_argument(char* arg);

void set_input(char* input);

void set_output(char* output);

#endif //SYSPROGTASKS_MYSHELL_H
