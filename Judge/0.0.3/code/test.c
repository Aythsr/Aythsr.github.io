#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = system("cgexec -g memory:/ sudo -u aurora timeout 3s /home/aurora/learn-C-and-CPP/Judge/0.0.3/judge_data/0001/user_tmp_exec/test_ac.out < /home/aurora/learn-C-and-CPP/Judge/0.0.3/judge_data/0001/test_data/0.in | /home/aurora/learn-C-and-CPP/Judge/0.0.2/diffg.out /home/aurora/learn-C-and-CPP/Judge/0.0.3/judge_data/0001/test_data/0.ans");
    // int a = system("sudo -u judge01 echo ${USER}");
    
    printf("%d\n", a);
    return 0;
}
