//
// Created by Marcel Beyer on 11/01/23.
//

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <fcntl.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "parse.tab.h"
#include <iostream>
#include <csignal>
#include <sys/wait.h>

#define Log(x) std::cout << x << std::endl;

extern int parse_string(const char* in); // Declare the function from parse.y

struct {
    std::vector<char*> arguments;
    std::string input;
    std::string output;
} typedef command;

std::vector<command> command_list;

int main ()
{
    char *line;
    while (true) {
        line = readline (std::filesystem::current_path().append("$ ").c_str());
        if (!line) break;
        parse_string(line); // Call the lexer with the input line
        free (line);
    }
    return 0;
}

void new_command(char* name){
    command_list.push_back(command());
    command_list.back().arguments = std::vector<char*>();
    command_list.back().arguments.push_back(name);
    command_list.back().input = "";
    command_list.back().output = "";
}

void add_argument(char* arg){
    command_list.back().arguments.push_back(arg);
}

void set_input(char* input){
    command_list.back().input = input;
}

void set_output(char* output){
    command_list.back().output = output;
}

void print_commands(){
    for (auto & command : command_list) {
        for (auto & argument : command.arguments) {
            std::cout << argument << " ";
        }
        std::cout << "< " << command.input << " ";
        std::cout << "> " << command.output << std::endl;
    }
}

void connectOutput(int pipeFD[2]){
    close(pipeFD[0]); // No need to read
    close(STDOUT_FILENO);
    dup2(pipeFD[1], STDOUT_FILENO);
}

void connectInput(int pipeFD[2]) {
    close(pipeFD[1]); // No not need to write;
    close(STDIN_FILENO);
    dup2(pipeFD[0], STDIN_FILENO);
}

void executeFromList(int index) {
    command_list[index].arguments.push_back(nullptr);
    if (execvp(command_list[index].arguments[0], command_list[index].arguments.data()) == -1) {
        std::cerr << "Error executing" << std::endl;
        exit(-1);
    } else {
        exit(0);
    }
}

void execute(bool background){
    print_commands();

    // execute single command




    int fd;

    pid_t pid = fork();

    if (pid == 0) { // fork out from shell
        int pipeFD[2];
        if (pipe(pipeFD) == -1) {   // Create pipe
            std::cerr << "Error creating pipe." << std::endl;
            exit(-1);
        } else {
            pid_t pid2 = fork();
            if (pid2 == 0) { // child aka. writer
                connectOutput(pipeFD);
                executeFromList(0);

            } else if (pid2 > 0) { // parent aka. reader
                wait(nullptr);
                connectInput(pipeFD);
                executeFromList(1);
            }
            exit(0);
        }
    } else if (pid > 0) {
        wait(nullptr);  // Shell waits for child to finish
    }

    command_list.clear();
}