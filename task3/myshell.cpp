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

void outputToFile(const std::string& path){
    int fd = open(path.c_str(), O_CREAT | O_TRUNC | O_WRONLY);
    if(fd == -1){
        std::cerr << "Error opening output file." << std::endl;
        exit(-1);
    } else {
        close(STDOUT_FILENO);
        if (STDOUT_FILENO != fd) {
            dup2(fd, STDOUT_FILENO);
        }
    }
}

void inputFromFile(const std::string& path){
    int fd = open(path.c_str(), O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error opening input file." << std::endl;
        exit(-1);
    } else {
        close(STDIN_FILENO);
        if (STDIN_FILENO != fd) {
            dup2(fd, STDIN_FILENO);
        }
    }
}

void outputToPipe(int pipeFD[2]){
    close(pipeFD[0]); // No need to read
    close(STDOUT_FILENO);
    dup2(pipeFD[1], STDOUT_FILENO);
}

void inputFromPipe(int pipeFD[2]) {
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

void forkNext(int index, int pipeFD_prev[2] = nullptr){
    // If index is 0, then we are at the last command -> we can just execute it
    if (index == 0) {
        if (pipeFD_prev != nullptr) {
            outputToPipe(pipeFD_prev);
            executeFromList(index);
        } else {
            executeFromList(index);
        }
        exit(0);
    } else {    // If index is not 0, then we create a pipe and fork out
        int pipeFD[2];
        if (pipe(pipeFD) == -1) {   // Create pipe
            std::cerr << "Error creating pipe." << std::endl;
            exit(-1);
        }  else {
            pid_t pid = fork();
            if (pid == 0) { // child
                forkNext(index - 1, pipeFD);
            } else if (pid > 0) {
                wait(nullptr);  // Wait for the child to finish
                inputFromPipe(pipeFD);
                executeFromList(index);
            }
            exit(0);
        }
    }
}

void execute(bool background){
    print_commands();
    pid_t pid = fork();
    if (pid == 0) {
        forkNext(int(command_list.size() - 1));
    } else if (pid > 0) {
        if (!background) {
            wait(nullptr);
        }
    }

#if 0
    // execute single command
    if (command_list.size() == 1) {
        forkNext(0);
    } else if (command_list.size() > 1) {   // execute pipeline
        pid_t pid = fork();
        if (pid == 0) { // fork out from shell
            int pipeFD[2];
            if (pipe(pipeFD) == -1) {   // Create pipe
                std::cerr << "Error creating pipe." << std::endl;
                exit(-1);
            } else {
                pid_t pid2 = fork();
                if (pid2 == 0) { // child aka. writer
                    outputToPipe(pipeFD);
                    executeFromList(0);

                } else if (pid2 > 0) { // parent aka. reader
                    wait(nullptr);
                    inputFromPipe(pipeFD);
                    executeFromList(1);
                }
                exit(0);
            }
        } else if (pid > 0) {
            wait(nullptr);  // Shell waits for child to finish
        }
    } else {
        std::cerr << "No commands to execute." << std::endl;
    }
#endif

    command_list.clear();
}