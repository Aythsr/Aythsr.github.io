#ifndef __READ_CONFIG__
#define __READ_CONFIG__ "Written by ZhilinXiao"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARGNAME(x) #x
#define argnum 100
#define PATH_LEN 400
#define CORE_CONFIG "./core.config"

char arg[argnum];
char PROBLEM_PATH[PATH_LEN];
char tmp_path[PATH_LEN];
int JUDGE_TOT = 2;
int time_limt = 1000;
int data_num = 0;
char exec[PATH_LEN];


/**
 * 拼接字符串。。。。
*/

void to_get_timeout() {
    strcpy(exec, "timeout ");
    char a[20] = {0}, op = 0;
    int p = time_limt;
    while (p > 0) {
        a[++op] = p % 10 + '0';
        if (op == 3) a[++op] = '.';
        p /= 10;
    }
    while (op < 3) {
        a[++op] = '0';
        if (op == 3) a[++op] = '.';
    }
    if (op == 4) a[++op] = '0';
    a[0] = 's';
    int len = strlen(exec);
    for (int i = op; i >= 0; --i) exec[len ++] = a[i];
    strcat(exec, " ./a.out");
}

/**
 * 从配置文件中导入信息
 * JUDGE_TOT 判题核心数量
 * PROBLEM_PATH 数据基础路径
*/
void init_config(char *problem_id) {
    printf("%s: \033[35m%s\033[0m\n", ARGNAME(problem_id), problem_id);
    FILE *fp = fopen(CORE_CONFIG, "r");
    while (fscanf(fp, "%s", arg) != EOF) {
        // printf("%s", arg);
        // printf("%s --- %s === %d \n", arg, ARGNAME(JUDGE_TOT), strcmp(arg, ARGNAME(JUDGE_TOT)));
        if (strcmp(arg, ARGNAME(JUDGE_TOT)) == 0) {
            /**
             * 读取判题核心数量配置，默认是2
            */
            fscanf(fp, "%d", &JUDGE_TOT);
            printf("%s: \033[35m%-3d\033[0m\n", ARGNAME(JUDGE_TOT), JUDGE_TOT);

        } else if (strcmp(arg, ARGNAME(PROBLEM_PATH)) == 0) {
            /**
             * 读取需要judge的题的路径
             * 由两部分组成：
             * [1] 基础路径，即题目存放路径，配置组成
             * [2] 题号，由程序参数指定
             * 也就是说整个路径应该是 基础路径/题号
            */
            fscanf(fp, "%s",PROBLEM_PATH);
            int len = strlen(PROBLEM_PATH);
            for (; *problem_id != '\0'; problem_id ++) {
                PROBLEM_PATH[len ++] = *problem_id;
            }
            printf("problem path: \033[35m%s\033[0m\n", PROBLEM_PATH);
        } else {
            fgets(arg, argnum, fp);
            // printf(" === %s\n ==== \n", arg);
        }
    }
    fclose(fp);


    strcpy(tmp_path, PROBLEM_PATH);
    strcat(tmp_path, "/test-config");
    // printf("%s\n", tmp_path);
    fp = fopen(tmp_path, "r");
    if (fp == NULL) {
        perror("题目不存在");
        exit(99);
    }
    while (fscanf(fp, "%s", arg) != EOF) {
        
        if (strcmp(arg, ARGNAME(time_limt)) == 0) {
            /**
             * 读取判题的时间限制，默认是1000ms
            */
            fscanf(fp, "%d", &time_limt);
            printf("%s: \033[35m%d\033[0m\n", ARGNAME(time_limt), time_limt);

        } else if (strcmp(arg, ARGNAME(data_num)) == 0) {
            /**
             * 读取判题测试数据数量
            */
            fscanf(fp, "%d", &data_num);
            printf("%s: \033[35m%d\033[0m\n", ARGNAME(data_num), data_num);

        } else {
            fgets(arg, argnum, fp);
            // printf(" === %s\n ==== \n", arg);
        }
    }

    to_get_timeout();
    printf("%s\n", exec);
}

#endif