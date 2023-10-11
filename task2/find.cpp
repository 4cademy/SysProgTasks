//
// Created by Marcel Beyer on 21.09.2023.
//
#include "iostream"
#include "argparse/argparse.hpp"
#include <fnmatch.h>
#include <dirent.h>
#include <set>
#include <unistd.h>

argparse::ArgumentParser program("find_parser");
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

                if (program.is_used("-type")) {
                    if ((program.get<std::string>("-type") == "d" && entry->d_type == DT_DIR) || (program.get<std::string>("-type") == "f" && entry->d_type == DT_REG) ) {
                        if (program.is_used("-name")) {
                            if( fnmatch(program.get<std::string>("-name").c_str(), entry_name.c_str(), 0) == 0 ) {
                                printf("%s/%s\n", current_path.c_str(), entry_name.c_str());
                            }
                        } else {
                            printf("%s/%s\n", current_path.c_str(), entry_name.c_str());
                        }
                    }
                } else {
                    if (program.is_used("-name")) {
                        if( fnmatch(program.get<std::string>("-name").c_str(), entry_name.c_str(), 0) == 0 ) {
                            printf("%s/%s\n", current_path.c_str(), entry_name.c_str());
                        }
                    } else {
                        printf("%s/%s\n", current_path.c_str(), entry_name.c_str());
                    }
                }

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

    // check if type argument is valid "f" or "d"
    if (program.is_used("-type") && (program.get<std::string>("-type") != "d") && (program.get<std::string>("-type") != "f")) {
        std::cerr << "find: unknown argument to -type: " << program.get<std::string>("-type") << std::endl;
        std::exit(1);
    }

    // store execution directory
    exec_dir = std::string(getcwd( nullptr, 0));

    std::string path = program.get<std::string>("directory");
    // add trailing slash if not present
    if (path.back() != '/') {
        path += '/';
    }

    // get folder name
    int beginning_of_folder_name;
    for (beginning_of_folder_name = path.length()-2; beginning_of_folder_name >= 0; beginning_of_folder_name--) {
        if (path[beginning_of_folder_name] == '/') {
            break;
        }
    }
    std::string folder_name = path.substr(beginning_of_folder_name+1, path.length()-beginning_of_folder_name-2);


    if (program.is_used("-type")) {
        if (program.get<std::string>("-type") == "d") {
            if (program.is_used("-name")) {
                if( fnmatch(program.get<std::string>("-name").c_str(), folder_name.c_str(), 0) == 0 ) {
                    printf("%s\n", path.c_str());
                }
            } else {
                printf("%s\n", path.c_str());
            }
        }
    } else {
        if (program.is_used("-name")) {
            if( fnmatch(program.get<std::string>("-name").c_str(), folder_name.c_str(), 0) == 0 ) {
                printf("%s\n", path.c_str());
            }
        } else {
            printf("%s\n", path.c_str());
        }
    }
    // check if folder matches name argument


    // change directory and list entries
    chdir(path.c_str());
    list_entries(".");

    return 0;
}
