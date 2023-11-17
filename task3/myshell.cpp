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

void execute(bool background){
    print_commands();

    pid_t pid = fork();
    if (pid == 0) {
        if(!command_list[0].input.empty()){
            // Redirect stdin to file
            close(STDIN_FILENO);
            int fd = open(command_list[0].input.c_str(), O_RDONLY);
            if (STDIN_FILENO != fd) {
                dup2(fd, STDIN_FILENO);
            }
        }
        std::cout << "Here: " << std::endl;
        std::cout << command_list[0].arguments[0] << std::endl;
        std::cout << command_list[0].arguments.data() << std::endl;

        if(execvp(command_list[0].arguments[0], command_list[0].arguments.data()) == -1){
            std::cout << "Error executing" << std::endl;
        }
        exit(0);
    } else if (pid > 0){
        wait(nullptr);
    }

    command_list.clear();
}