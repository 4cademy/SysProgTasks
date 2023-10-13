//
// Created by Marcel Beyer on 21.09.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "sincos.h"

int main(int argc, char *argv[]) {

    if (argc > 2) {
        printf("Error: Too many arguments\n");
        return 1;
    } else if  (argc < 2){
        printf("Error: No arguments\n");
        return 1;
    } else {
        bool arg_is_int = true;
        int length = strlen (argv[1]);
        for(int i; i<length; i++){
            if(!isdigit(argv[1][i])){
                arg_is_int = false;
            }
        }
        if (atoi(argv[1]) < 0) {
            printf("Error: Argument is not a positive Integer\n");
            return 1;
        } else if (!arg_is_int) {
            printf("Error: Argument is not an Integer\n");
            return 1;
        } else {
            my_sincos(atoi(argv[1]));
        }
    }

        return 0;
}
