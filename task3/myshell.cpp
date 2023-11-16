//
// Created by Marcel Beyer on 11/01/23.
//

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include "readline/readline.h"
#include "readline/history.h"
#include "parse.tab.h"

extern int parse_string(const char* in); // Declare the function from parse.y

struct {
    std::string name;
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
        printf ("Parsing: %s\n", line);
        parse_string(line); // Call the function with the input line
        free (line);
    }
    return 0;
}

void new_command(char* name){
    command_list.push_back(command());
    command_list.back().name = name;
    command_list.back().arguments = std::vector<char*>();
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

void execute(){
    printf("Executing...\n");
}