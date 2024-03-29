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
#include "functions.h"
#include <string.h>


extern int parse_string(const char* in); // Declare the function from parse.y

struct {
    std::vector<char*> arguments;
    std::string input;
    std::string output;
} typedef command;

std::vector<command> command_list;

void handle_sigchld(int sig) {
    while (waitpid(-1, 0, WNOHANG) > 0) {
        // This loop will reap all zombie processes
    }
}

int main ()
{
    signal(SIGCHLD, handle_sigchld);
    char *line;
    using_history();
    while (true) {
        line = readline (std::filesystem::current_path().append("$ ").c_str());
        if (!line) break;
        add_history(line);
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

void print_to_terminal(const char* message) {
    int fd = open("/dev/tty", O_WRONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    write(fd, message, strlen(message));
    close(fd);
}

void executeFromList(int index) {
    if (strcmp(command_list[index].arguments[0], "pwd") == 0) {
        shell_pwd();
        exit(0);
    } else if (strcmp(command_list[index].arguments[0], "cd") == 0) {
        shell_cd(command_list[index].arguments);
        exit(0);
    } else if (strcmp(command_list[0].arguments[0], "kill") == 0) {
        shell_kill(command_list[0].arguments);
        exit(0);
    } else if (strcmp(command_list[0].arguments[0], "alias") == 0) {
        shell_alias(command_list[0].arguments);
        exit(0);
    } else if (strcmp(command_list[0].arguments[0], "unalias") == 0) {
        shell_unalias(command_list[0].arguments);
        exit(0);
    } else {
        command_list[index].arguments.push_back(nullptr);
        std::string text = "\nExecuting  " + std::to_string(index);
        // print_to_terminal(text.c_str());
        if (execvp(command_list[index].arguments[0], command_list[index].arguments.data()) == -1) {
            std::cerr << strerror(errno) << std::endl;
            exit(-1);
        } else {
            exit(0);
        }
    }
}

void forkNext(int index, int pipeFD_prev[2] = nullptr){
    // If index is 0, then we are at the first command -> we can just execute it
    if (index == 0) {
        if (pipeFD_prev != nullptr) {
            if (!command_list[index].input.empty()) {
                inputFromFile(command_list[index].input);
            }
            outputToPipe(pipeFD_prev);
        } else if (!command_list[index].output.empty()){
            outputToFile(command_list[index].output);
        }
        executeFromList(index);
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
                if (pipeFD_prev != nullptr) {
                    outputToPipe(pipeFD_prev);
                } else if (!command_list[index].output.empty()){
                    outputToFile(command_list[index].output);
                }
                executeFromList(index);
            }
            exit(0);
        }
    }
}

void execute(bool background){
    // print_commands();

    for (auto & cmd : command_list) {
        char* name = cmd.arguments[0];
        std::vector<char*> rest = std::vector<char*>(cmd.arguments.begin() + 1, cmd.arguments.end());
        std::vector<char*> resolved = get_command(name);

        cmd.arguments.clear();
        cmd.arguments.insert(cmd.arguments.end(), resolved.begin(), resolved.end());
        cmd.arguments.insert(cmd.arguments.end(), rest.begin(), rest.end());
    }
    // std::cout << "After aliasing: " << std::endl;
    // print_commands();

    if (strcmp(command_list[0].arguments[0], "cd") == 0) {
        shell_cd(command_list[0].arguments);
    } else if (strcmp(command_list[0].arguments[0], "kill") == 0) {
        shell_kill(command_list[0].arguments);
    } else if (strcmp(command_list[0].arguments[0], "alias") == 0) {
        shell_alias(command_list[0].arguments);
    } else if (strcmp(command_list[0].arguments[0], "unalias") == 0) {
        shell_unalias(command_list[0].arguments);
    } else {
        pid_t pid = fork();
        if (pid == 0) {
            forkNext(int(command_list.size() - 1));
        } else if (pid > 0) {
            if (!background) {
                wait(nullptr);
            }
        }
    }

    command_list.clear();
}