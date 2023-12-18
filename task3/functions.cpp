//
// Created by Marcel Beyer on 11/14/23.
//

#include <unistd.h>
#include <vector>
#include <iostream>
#include <csignal>

void shell_pwd(){
    char* pwd = get_current_dir_name();
    std::cout << pwd << std::endl;
    free(pwd);
}

void shell_cd(const std::vector<char*>& args){
    if (args.size() > 1) {
        if (chdir(args[1]) == -1) {
            std::cout << "Error changing directory." << std::endl;
        }
    } else {
        std::cout << "No directory specified." << std::endl;
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