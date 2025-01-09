#include <stdio.h>
#include "../judge_compile.h"


int main() {
    int a = compile_judge_core(GUN_C, "/home/aurora/learn-C-and-CPP/Judge/0.0.3/code/test.c", 
    "/home/aurora/learn-C-and-CPP/Judge/0.0.3/code/test.out", "-O2");
    printf("%d\n", a);
}