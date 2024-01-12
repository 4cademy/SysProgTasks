//
// Created by Marcel Beyer on 11/14/23.
//

#include <unistd.h>
#include <vector>
#include <iostream>
#include <csignal>
#include <map>

std::map<std::string, std::vector<char*>> aliases;


void shell_pwd(){
    char* pwd = get_current_dir_name();
    std::cout << pwd << std::endl;
    free(pwd);
}

void shell_cd(const std::vector<char*>& args){
    if (args.size() > 1) {
        if (chdir(args[1]) == -1) {
            std::cout << "No such file or directory" << std::endl;
        }
    } else {
        std::cout << "No directory specified" << std::endl;
    }
}

void shell_kill(const std::vector<char *> &args) {
    if (args.size() == 3) {
        if (kill(atoi(args[2]), atoi(args[1])) == -1) {
            std::cout << "Error killing process." << std::endl;
        }
    } else {
        std::cout << "Specify as follows: kill <signo> <pid> " << std::endl;
    }
}

void shell_alias(const std::vector<char *> &args) {
    if (args.size() >= 3) {
        aliases[args[1]] = std::vector<char*>(args.begin() + 2, args.end());
    } else {
        std::cout << "Specify alias as follows: alias <name> <command> " << std::endl;
    }
    for (auto const& [key, val] : aliases) {
        std::cout << key << " = ";
        for (auto const& arg : val) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;
    }
}

void shell_unalias(const std::vector<char*> &args){
    if (args.size() >= 2) {
        aliases.erase(args[1]);
    } else {
        std::cout << "Specify unalias as follows: unalias <name> " << std::endl;
    }
    for (auto const& [key, val] : aliases) {
        std::cout << key << " = ";
        for (auto const& arg : val) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<char*> get_command(char* name){
    std::vector<char*> command;
    command.push_back(name);

    while (aliases.find(name) != aliases.end()) {
        std::vector<char*> alias = aliases[name];
        name = alias[0];

        std::vector new_command = std::vector<char*>(alias.begin(), alias.end());
        new_command.insert(new_command.end(), command.begin() + 1, command.end());
        command = new_command;
    }

    return command;
}