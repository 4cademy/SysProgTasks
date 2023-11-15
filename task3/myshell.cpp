//
// Created by Marcel Beyer on 11/01/23.
//

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include "readline/readline.h"
#include "readline/history.h"
#include "parse.tab.h"

extern int parse_string(const char* in); // Declare the function from parse.y

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