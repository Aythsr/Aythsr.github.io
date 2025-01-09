#include <stdio.h>
#include "read_config.h"
#include "judge_compile.h"
#include "manage_cgroup.h"
#include <unistd.h>

#define CORE_ARG_NUM 3

const char *__JUDGE_CORE_ARG__[CORE_ARG_NUM] = {
    "data_num",
    "time_limt",
    "memory_limt"
};

int __JUDGE_CORE_VAL__[CORE_ARG_NUM] = {
    0,
    0,
    0
};

#define data_num __JUDGE_CORE_VAL__[0]
#define time_limt __JUDGE_CORE_VAL__[1]
#define memory_limt __JUDGE_CORE_VAL__[2]


const char *codesrc = "/home/aurora/learn-C-and-CPP/Judge/0.0.3/judge_data/0001/user_code/test_ac.c";
const char *outdst = "/home/aurora/learn-C-and-CPP/Judge/0.0.3/judge_data/0001/user_tmp_exec/test_ac.out";

char command_core[ARGMAXLEN * 10];

int go_to_test(int testid) {
    sprintf(command_core, 
    "timeout %.fs cgexec -g memory:/%s/%s %s < %s/%d.in | %s %s/%d.ans", 
    time_limt / 1000.0,
    JUDGE_NAME,
    "test",
    "/home/aurora/learn-C-and-CPP/Judge/0.0.3/judge_data/0001/user_tmp_exec/test_ac.out",
    "/home/aurora/learn-C-and-CPP/Judge/0.0.3/judge_data/0001/test_data",
    testid,
    "/home/aurora/learn-C-and-CPP/Judge/0.0.2/diffg.out",
    "/home/aurora/learn-C-and-CPP/Judge/0.0.3/judge_dat
    a/0001/test_data",
    testid);
    printf("%s\n", command_core);
    int state = system("command_core");
    return state;
}

int main(int argc, char const *argv[]) {

    read_config_int("/home/aurora/learn-C-and-CPP/Judge/0.0.3/judge_data/0001/test.config",
    __JUDGE_CORE_ARG__,
    __JUDGE_CORE_VAL__,
    CORE_ARG_NUM);
    for (int i = 0; i < CORE_ARG_NUM; ++i) {
        printf("%s %d\n", __JUDGE_CORE_ARG__[i], __JUDGE_CORE_VAL__[i]);
    }
    compile_judge_core(GUN_C, codesrc, outdst, "");
    cgroup_init("");
    cgroup_create("test", memory_limt, MEMORY_MB);

    for (int i = 0; i < data_num; ++i) {
        int a = go_to_test(i);
        printf("#%d: %d\n", i, a);
    }

    cgroup_del("test");
    cgroup_clear();
    return 0;
}
