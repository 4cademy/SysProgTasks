//
// Created by Marcel Beyer on 21.09.2023.
//
#include "iostream"
#include "argparse/argparse.hpp"
#include <dirent.h>
#include <set>
#include <unistd.h>
#include <string>

std::string exec_dir;
std::set<int> checked_entry_set;

void list_entries(std::string path) {
    DIR *folder;
    struct dirent *entry;

    folder = opendir(path.c_str());

    while( (entry=readdir(folder))) {
        if(checked_entry_set.insert(entry->d_ino).second){
            std::string entry_name(entry->d_name);
            if (entry_name != "." && entry_name != "..") {
                std::string current_path(getcwd( nullptr, 0));
                current_path.erase(0, exec_dir.length()+1);
                printf("%s/%s\n", current_path.c_str() , entry_name.c_str());
                if (entry->d_type == DT_DIR) {
                    chdir(entry_name.c_str());
                    list_entries(".");
                    chdir("..");
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("find_parser");
    program.add_argument("directory").default_value(".").required();
    program.add_argument("-name");
    program.add_argument("-type");
    program.add_argument("-follow")
            .default_value(false)
            .implicit_value(true);
    program.add_argument("-xdev")
            .default_value(false)
            .implicit_value(true);

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    // store execution directory
    exec_dir = std::string(getcwd( nullptr, 0));

    std::string path = program.get<std::string>("directory");
    // add trailing slash if not present
    if (path.back() != '/') {
        path += '/';
    }
    printf("%s\n", path.c_str());
    chdir(path.c_str());
    list_entries(".");

    return 0;
}
