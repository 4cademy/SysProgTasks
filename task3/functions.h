//
// Created by marcel on 11/14/23.
//
#include <vector>


#ifndef SYSPROGTASKS_FUNCTIONS_H
#define SYSPROGTASKS_FUNCTIONS_H

void shell_pwd();

void shell_cd(const std::vector<char*>& args);

void shell_kill(const std::vector<char*>& args);

void shell_alias(const std::vector<char *> &args);

void shell_unalias(const std::vector<char *> &args);

char* get_command(char* name);

#endif //SYSPROGTASKS_FUNCTIONS_H
