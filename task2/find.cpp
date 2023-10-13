//
// Created by Marcel Beyer on 21.09.2023.
//
#include "iostream"
#include "argparse/argparse.hpp"
#include <fnmatch.h>
#include <dirent.h>
#include <set>
#include <unistd.h>
#include <sys/stat.h>

argparse::ArgumentParser program("find_parser");
std::set<std::string> checked_path_set;

std::string current_path;
dev_t exec_dev;

void add_to_path(std::string str) {
    current_path += str;
    if(current_path.back() != '/') {
        current_path += '/';
    }
}

void remove_from_path() {
    if (current_path.back() != '/') {
        current_path.pop_back();
    }
    int beginning_of_last_entry;
    for (beginning_of_last_entry = current_path.length()-2; beginning_of_last_entry >= 0; beginning_of_last_entry--) {
        if (current_path[beginning_of_last_entry] == '/') {
            break;
        }
    }
    current_path = current_path.substr(0, beginning_of_last_entry+1);
}

bool isBrokenSymlink(std::string symlinkPath) {
    struct stat symlinkInfo;
    lstat(symlinkPath.c_str(), &symlinkInfo);

    // Check if it's a symlink and if it doesn't point to a valid target
    if (S_ISLNK(symlinkInfo.st_mode)) {
        char targetPath[1024];
        ssize_t targetLength = readlink(symlinkPath.c_str(), targetPath, sizeof(targetPath) - 1);

        if (targetLength == -1) {
            // symlink is broken
            return true;
        }

        targetPath[targetLength] = '\0';
        struct stat targetInfo;

        if (stat(targetPath, &targetInfo) == -1) {
            // symlink is broken
            return true;
        }
    }

    return false;
}

bool isSymlinkToFile(const std::string symlinkPath) {
    struct stat targetStat;
    stat(symlinkPath.c_str(), &targetStat);

    if (S_ISREG(targetStat.st_mode)) {
        // symlink points to a file
        return true;
    } else {
        return false;
    }
}

bool is_link_loop(std::string origin, std::string next) {
    chdir(next.c_str());
    // check if xdev flag is set and if current directory is on different device as execution directory return
    if(program.get<bool>("-xdev")) {
        struct stat entry_stat;
        stat(".", &entry_stat);
        if (entry_stat.st_dev != exec_dev) {
            chdir(origin.c_str());
            return false;
        }
    }

    if(!checked_path_set.insert(std::string(getcwd( nullptr, 0))).second) {
        chdir(origin.c_str());
        return true;
    } else {
        DIR *folder;
        struct dirent *entry;

        folder = opendir(".");

        while((entry= readdir(folder))) {
            std::string entry_name(entry->d_name);
            if (entry_name != "." && entry_name != "..") {
                if (entry->d_type == DT_DIR || entry->d_type == DT_LNK) {
                    if(is_link_loop(std::string(getcwd( nullptr, 0)), entry_name)) {
                        chdir(origin.c_str());
                        return true;
                    }
                }
            }
        }
        chdir(origin.c_str());
        return false;
    }
}

void find(std::string origin, std::string next) {
    chdir(next.c_str());
    // check if xdev flag is set and if current directory is on different device as execution directory return
    if(program.get<bool>("-xdev")) {
        struct stat entry_stat;
        stat(".", &entry_stat);
        if (entry_stat.st_dev != exec_dev) {
            return;
        }
    }

    DIR *folder;
    struct dirent *entry;

    folder = opendir(".");

    while((entry= readdir(folder))) {
        std::string entry_name(entry->d_name);
        if (entry_name != "." && entry_name != "..") {
            // check if type flag is set and if entry is of correct type
            bool type_match = !program.is_used("-type") || program.is_used("-type") && ( (program.get<std::string>("-type") == "d" && entry->d_type == DT_DIR) || (program.get<std::string>("-type") == "f" && entry->d_type == DT_REG) );
            // check if name flag is set and if entry name matches wildcard
            bool name_match = !program.is_used("-name") || program.is_used("-name") && (fnmatch(program.get<std::string>("-name").c_str(), entry_name.c_str(), 0) == 0);

            if (type_match && name_match) {
                // suppress printing of link if it results in a loop (this matches the GNU find behavior)
                if(program.get<bool>("-follow") && entry->d_type == DT_LNK) {
                    if(!isBrokenSymlink(entry_name)) {
                        if(!isSymlinkToFile(entry_name)) {
                            checked_path_set.clear();
                            checked_path_set.insert(std::string(getcwd( nullptr, 0)));
                            if(!is_link_loop(std::string(getcwd( nullptr, 0)), entry_name)) {
                                printf("%s%s\n", current_path.c_str(), entry_name.c_str());
                            }
                        }
                    }
                } else {
                    printf("%s%s\n", current_path.c_str(), entry_name.c_str());
                }
            }

            // check if entry is a directory and decent into it
            if (entry->d_type == DT_DIR) {
                add_to_path(entry_name);
                find(std::string(getcwd( nullptr, 0)), entry_name);
                remove_from_path();
            }

            // check if entry is a symbolic link and if follow flag is set and if entry is not a link loop
            if(program.get<bool>("-follow") && entry->d_type == DT_LNK) {
                if(!isBrokenSymlink(entry_name)) {
                    if(!isSymlinkToFile(entry_name)) {
                        checked_path_set.clear();
                        checked_path_set.insert(std::string(getcwd( nullptr, 0)));
                        if(!is_link_loop(std::string(getcwd( nullptr, 0)), entry_name)) {
                            add_to_path(entry_name);
                            find(std::string(getcwd( nullptr, 0)), entry_name.c_str());
                            remove_from_path();
                        }
                    }
                }
            }
        }
    }
    chdir(origin.c_str());
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

    // NEW IMPLEMENTATION
    std::string dir_arg = program.get<std::string>("directory");

    if (chdir(dir_arg.c_str()) != 0) {
        std::cerr << "find: " << dir_arg << ": No such file or directory" << std::endl;
        std::exit(1);
    }

    // get device id of execution directory
    struct stat exec_dir_stat;
    stat(".", &exec_dir_stat);
    exec_dev = exec_dir_stat.st_dev;

    // check if directory is absolute or relative and add to current_path
    if(dir_arg[0] == '/') {
        add_to_path(std::string(getcwd( nullptr, 0)));
    } else {
        add_to_path(dir_arg);
    }

    // get name of execution folder
    int beginning_of_folder_name;
    for (beginning_of_folder_name = current_path.length()-2; beginning_of_folder_name >= 0; beginning_of_folder_name--) {
        if (current_path[beginning_of_folder_name] == '/') {
            break;
        }
    }
    std::string folder_name = current_path.substr(beginning_of_folder_name+1, current_path.length()-beginning_of_folder_name-2);

    // remove or add trailing slash to match behaviour of GNU find
    std::string exec_folder_print;
    if ((dir_arg.back() == '/') && (current_path.back() != '/')) {
        exec_folder_print = current_path += "/";
    } else if ((dir_arg.back() != '/') && (current_path.back() == '/')) {
        exec_folder_print = current_path.substr(0, current_path.length()-1);
    } else {
        exec_folder_print = current_path;
    }

    // check if execution folder matches -name wildcard
    if (program.is_used("-type") && (program.get<std::string>("-type") == "d") || !program.is_used("-type")) {
        if (program.is_used("-name")) {
            if( fnmatch(program.get<std::string>("-name").c_str(), folder_name.c_str(), 0) == 0 ) {
                printf("%s\n", exec_folder_print.c_str());
            }
        } else {
            printf("%s\n", exec_folder_print.c_str());
        }
    }

    find(std::string(getcwd( nullptr, 0)), current_path.c_str());

    return 0;
}
