/**
 * 读取配置文件程序源码
 * 
 * 使用该文件读取配置时，请确保你的配置文件是如下格式
 * <key>: <value>
 * 
 * 0. <key>,<value>均无空格，如果需要携带空格，空格用^代替。
 * 1. <key>必须是每行的第一个字符串，代表配置的名称
 * 2. <key>后冒号可带可不带，主要是为了限制配置文件格式好看。如果你要带一个字符，只能带冒号
 * 3. <val>为冒号后第一个字符串，代表配置的值。
 * 4. 每一行只有前两个字符串有意义，后面的均无意义，你可以随便写
 * 5. 如果每行的第一个字符是#，会直接跳过这行
 * 
*/
#ifndef __READ_CONFIG__

#define __READ_CONFIG__ "read_config of OpenJudgeCore written by ZhilinXiao"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARGMAXLEN 333

/**
 * 用来读取文件配置
 * filename 代表文件名称，字符指针指向一个字符串
 * argname 代表变量名，字符指针数组，存储可能的配置名称
 * argval 代表配置的变量的值存储的位置
 * num 可能存在的数量
*/

void replace_space(char *s) {
    while (*s != 0) {
        if (*s == '^') *s = ' ';
        s++;
    }
}

int read_config_int(const char *filename, const char **argname, int *argval, int num) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("打开文件失败!!!");
        return -1;
    }
    int pos;
    char *p = (char*) malloc(ARGMAXLEN);
    while (fscanf(fp, "%s", p) != EOF) {
        if (*p != '#') {
            pos = strlen(p) - 1;
            if (p[pos] == ':') p[pos] = 0;
            for (int i = 0; i < num; ++i) {
                if (strcmp(p, argname[i]) == 0) {
                    fscanf(fp, "%d", &argval[i]);
                    break;
                }
            }
        }
        /**
         * 读取掉这一行多余的内容
        */
        while (fscanf(fp, "%c", p) != EOF && *p != '\n');
    }
    free(p);
    fclose(fp);
    return 0;
}


/**
 * 用来读取文件配置
 * filename 代表文件名称，字符指针指向一个字符串
 * argname 代表变量名，字符指针数组，存储可能的配置名称
 * argval 代表配置的变量的值存储的位置
 * num 可能存在的数量
*/
int read_config_char(const char *filename, const char **argname, char argval[][ARGMAXLEN], int num) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("打开文件失败");
        return -1;
    }
    int pos;
    char *p = (char*) malloc(ARGMAXLEN);

    while (fscanf(fp, "%s", p) != EOF) {
        if (*p != '#') {
            pos = strlen(p) - 1;
            if (p[pos] == ':') p[pos] = 0;
            for (int i = 0; i < num; ++i) {
                if (strcmp(p, argname[i]) == 0) {
                    fscanf(fp, "%s", argval[i]);
                    replace_space(argval[i]);
                    break;
                }
            }
        }
        /**
         * 读取掉这一行多余的内容
        */
        while (fscanf(fp, "%c", p) != EOF && *p != '\n');
    }

    free(p);
    fclose(fp);
    return 0;
}

#endif