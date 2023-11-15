//
// Created by marcel on 11/14/23.
//

#ifndef SYSPROGTASKS_FUNCTIONS_H
#define SYSPROGTASKS_FUNCTIONS_H

void ExecuteCommand(char *command, char *arguments[], char* input, char* output);

char** Split(char* a_str, char a_delim);

#endif //SYSPROGTASKS_FUNCTIONS_H
