#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include "readline/readline.h"
#include "readline/history.h"
#include "parse.tab.h"

int main ()
{
    char *line;
    while (true) {
        line = readline (std::filesystem::current_path().append("$ ").c_str());
        if (!line) break;
        printf ("Parsing: %s\n", line);
        free (line);
    }
    return 0;
}