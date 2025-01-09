#include "../manage_cgroup.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    cgroup_init();
    // cgroup_del("xzl");
    // cgroup_clear();
    sleep(20);
    cgroup_clear();    
    return 0;
}