
#ifndef __JUDGE_COMPILE__

#define __JUDGE_COMPILE__ "judge_compile of OpenJudgeCore written by ZhilinXiao"

#include "read_config.h"
#include <stdio.h>
#include <stdlib.h>

#define JUDGE_COMPILE_ARG_NUM 6

const char* __JUDGE_COMPILE_ARG__[JUDGE_COMPILE_ARG_NUM] = {
    "GUN_C",
    "GUN_CPP"
};

char __JUDGE_COMPILE_VAL__[JUDGE_COMPILE_ARG_NUM][ARGMAXLEN] = {
    "gcc",
    "g++"
};

#define GUN_C __JUDGE_COMPILE_VAL__[0]
#define GUN_CPP __JUDGE_COMPILE_VAL__[1]

char command_judge_compile[ARGMAXLEN * 10];

/**
 * 编译器核心
 * complie 字符常量，编译器种类
 * src 编译源文件
 * dst 编译目标文件
 * exargv 额外参数
*/
int compile_judge_core(const char *complie, const char *src, const char *dst, const char* exargv) {
    
    sprintf(command_judge_compile, "%s %s -o %s %s", complie, src, dst, exargv);
    printf(" --- %s\n", command_judge_compile);
    int state = system(command_judge_compile);

    if (state != 0) {
        printf("\033[31m compile error\033[0m: %s\n", src);
        return -1;
    }

    return 0;
}


#endif