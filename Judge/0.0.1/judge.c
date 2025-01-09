#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int JUDGE_TOT = 2;
// #define JUDGE_TOT 8

#define TEST_RUN 1
#define TEST_AC 2
#define TEST_WA 3
#define TEST_TME 4

typedef struct timespec Timespec;


struct testinfo
{
    int testid;
    char *path;
    Timespec st, ed;
    pthread_t tid;
    int state;
    double time_limt, run_time; 
    /* data */
};
struct testinfo* info;
pthread_t chk;

void delay_milliseconds(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

void* test_function(void* arg) {
    struct testinfo* info = (struct testinfo*)arg;
    info->tid = pthread_self();
    clock_gettime(CLOCK_MONOTONIC, &(info->st));
    
    int rest = system("timeout 2.5 ./test > 1.txt");

    clock_gettime(CLOCK_MONOTONIC, &(info->ed));

    info->run_time = (info->ed.tv_sec - info->st.tv_sec) * 1000.0 + (info->ed.tv_nsec - info->st.tv_nsec) / 1000000.0;
    printf("Test#\033[031m%d\033[0m:\n", info->testid);
    printf("    Run time:\033[033m%.4lf\033[0m\n", info->run_time);
    if (info->time_limt > info->run_time)
        printf("    Run Result:\033[032m%s\033[0m\n", "AC");
    else printf("    Run Result:\033[031m%s\033[0m\n", "WA");
    info->state = TEST_AC;
    return NULL;
}

#define ARGNAME(x) #x
#define argnum 100
char arg[argnum];

/**
 * 从配置文件中导入信息
 * JUDGE_TOT 判题核心数量
 * 
*/

void init_peoperties() {
    FILE *fp = fopen("./judge.properties", "r");
    while (fscanf(fp, "%s", arg) != EOF) {
        // printf("%s", arg);
        // printf("%s --- %s === %d \n", arg, ARGNAME(JUDGE_TOT), strcmp(arg, ARGNAME(JUDGE_TOT)));
        if (strcmp(arg, ARGNAME(JUDGE_TOT)) == 0) {
            fscanf(fp, "%d", &JUDGE_TOT);
            printf("%-10s : %-3d\n", ARGNAME(JUDGE_TOT), JUDGE_TOT);
        } else {
            fgets(arg, argnum, fp);
            // printf(" === %s\n ==== \n", arg);
        }
    }
    fclose(fp);
}

int main() {
    init_peoperties();
    // return 0;

    Timespec sst, eed;
    clock_gettime(CLOCK_MONOTONIC, &sst);
    info = (struct testinfo*)malloc(sizeof(struct testinfo) * JUDGE_TOT);

    for (int i = 0; i < JUDGE_TOT; ++i) {
        info[i].testid = i;
        info[i].path = "/home/";
        info[i].state = TEST_RUN;
        info[i].time_limt = 2500.0;
        pthread_create(&info[i].tid, NULL, test_function, (void*)&info[i]);
        pthread_join(info[i].tid, NULL);
        printf("%d : %ld\n", i, info[i].tid);
    }
    
    // for (int i = 0; i < JUDGE_TOT; ++i) {
    //     pthread_join(info[i].tid, NULL);
    // }

    clock_gettime(CLOCK_MONOTONIC, &eed);
    printf(" ------------- \n");
    printf("all time: %lf\n", (eed.tv_sec - sst.tv_sec) * 1000.0 + (eed.tv_nsec - sst.tv_nsec) / 1000000.0);
    free(info);
    return 0;
}
