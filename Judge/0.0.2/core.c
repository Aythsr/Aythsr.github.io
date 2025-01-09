#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "read_config.h"

// #define JUDGE_TOT 8

#define TEST_RUNNING 0
#define TEST_AC 1
#define TEST_WA 2
#define TEST_TLE 3



typedef struct timespec Timespec;

struct testinfo
{
    int testid;
    char path[PATH_LEN];
    char res[20];
    Timespec st, ed;
    pthread_t tid;
    int state;
    int run_time;
    int return_val;
    pthread_mutex_t Mutex;
    /* data */
};
struct testinfo* info;
pthread_t chk;

void set_state(struct testinfo* x, int val) {
    pthread_mutex_lock(&info->Mutex);
    info->state = val;
    pthread_mutex_unlock(&info->Mutex);
}

int get_state(struct testinfo* x) {
    pthread_mutex_lock(&info->Mutex);
    int res = info->state;
    pthread_mutex_unlock(&info->Mutex);
    return res;
}

void delay_milliseconds(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

void to_get_res(struct testinfo* info) {
    if (info->run_time > time_limt) {
        set_state(info, TEST_TLE);
        strcpy(info->res, "TLE");
    } else if (info->return_val == 0) {
        set_state(info, TEST_AC);
        strcpy(info->res, "\033[32mAC\033[0m");
    } else if (info->return_val == 1) {
        set_state(info, TEST_WA);
        strcpy(info->res, "WA");
    } else {
        set_state(info, -1);
    }
    printf("Test # %d\n", info->testid);
    printf("    return val: %d\n", info->return_val);
    printf("    run_time: \033[33m%dms\033[0m\n", info->run_time); 
    printf("    path: %s\n", info->path);
    printf("    result: %s\n", info->res);
   
    
}

void* test_function(void* arg) {
    struct testinfo* info = (struct testinfo*)arg;
    info->tid = pthread_self();
    clock_gettime(CLOCK_MONOTONIC, &(info->st));
    char* command = (char *)calloc(200, sizeof(char));
    strcpy(command, exec);
    strcat(command, " < ");
    strcat(command, info->path);
    // strcat(command, ".in > ./tmp.txt ");
    strcat(command, ".in | ./diffg.out ");
    strcat(command, info->path);
    strcat(command, ".ans");
    // int rest = system("timeout 7.0s ./a.out < ./test_data/0001/1.in | ./diffg.out ./test_data/0001/1.ans");
    int rest = system(command);

    clock_gettime(CLOCK_MONOTONIC, &(info->ed));
    info->run_time = (int)((info->ed.tv_sec - info->st.tv_sec) * 1000.0 + (info->ed.tv_nsec - info->st.tv_nsec) / 1000000.0 + 0.5);
    info->return_val = rest >> 8;
    to_get_res(info);
    return NULL;
}

void to_get_path(char *path, int id) {
    strcpy(path, PROBLEM_PATH);
    int len = strlen(path);
    char s[10], op = 0;
    path[len ++] = '/';
    if (id == 0) s[++op] = 0;
    while (id > 0) s[++op] = id % 10, id /= 10;
    for (int i = op; i > 0; --i) {
        path[len ++] = (s[i] + '0');
    }
    path[len] = 0;
    printf("%s\n", path);
}

int main(int argc, char* argv[]) {
    init_config(argv[1]);
    // return 0;
    
    Timespec sst, eed;
    clock_gettime(CLOCK_MONOTONIC, &sst);
    info = (struct testinfo*)malloc(sizeof(struct testinfo) * JUDGE_TOT);

    for (int i = 0; i < JUDGE_TOT; ++i) {
        info[i].testid = i;
        to_get_path(info[i].path, i);
        pthread_mutex_init(&info[i].Mutex, NULL);
        set_state(&info[i], TEST_RUNNING);
        pthread_create(&info[i].tid, NULL, test_function, (void*)&info[i]);
    }
    
    for (int i = 0; i < JUDGE_TOT; ++i) {
        pthread_join(info[i].tid, NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &eed);
    printf(" ------------- \n");
    printf("all time: %.4lfms\n", (eed.tv_sec - sst.tv_sec) * 1000.0 + (eed.tv_nsec - sst.tv_nsec) / 1000000.0);
    free(info);
    return 0;
}
