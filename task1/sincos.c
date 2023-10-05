//
// Created by Marcel Beyer on 21.09.2023.
//

#include <stdio.h>
#include <math.h>
#include "sincos.h"

#define PI 3.141592654

void my_sincos(int arg) {
    for (int i = 0; i <= arg; i++) {
        double grad = 0;
        double bogen = 0;
        if (arg != 0) {
            grad = i*360/arg;
            bogen = i*2*PI/arg;
        }
        printf("%f \t %f \t %f\n", grad, sin(bogen), cos(bogen));
    }
}
