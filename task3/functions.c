//
// Created by Marcel Beyer on 11/14/23.
//

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include "functions.h"

void ExecuteCommand(char *command, char *arguments[], char* input, char* output) {
    int fd;
    pid_t pid = fork();
    if (pid == 0) {

        if(strcmp(input, "") != 0) {
            // Redirect stdin to file
            close(STDIN_FILENO);
            fd = open(input, O_RDONLY);
            if (STDIN_FILENO != fd) {
                dup2(fd, STDIN_FILENO);
            }
        }

        if(strcmp(output, "") != 0) {
            // Redirect stdout to file
            close(STDOUT_FILENO);
            fd = open(output, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU | S_IRGRP | S_IROTH);
            if (STDOUT_FILENO != fd) {
                dup2(fd, STDOUT_FILENO);
            }
        }

        execvp(command, arguments);
        exit(0);
    } else {
        waitpid(pid, NULL, 0);
    }
}


// https://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c
char ** Split(char * a_str, const char a_delim) {
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
        knows where the list of returned strings ends. */
    count++;

    result = (char**)malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}