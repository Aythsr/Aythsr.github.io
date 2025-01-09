#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR 10000

char usr_buff[MAX_CHAR], std_buff[MAX_CHAR];
char *usr_op = 0, *std_op = 0;
int usr_size = 0, std_size = 0;
FILE *stdfp;

int usr_read_buff() {
    if (usr_size == 0) {
        usr_size = fread(usr_buff, sizeof(char), MAX_CHAR, stdin);
        usr_op = usr_buff;
    }
    if (usr_size <= 0) {
        return 0;
    } else {
        return 1;
    }
}

int std_read_buff() {
    if (std_size == 0) {
        std_size = fread(std_buff, sizeof(char), MAX_CHAR, stdfp);
        std_op = std_buff;
    }
    if (std_size <= 0) {
        return 0;
    } else {
        return 1;
    }
}

char usr_next_char() {
    if (usr_size <= 0 && usr_read_buff() == 0) {
        return -1;
    } 
    usr_size--;
    return *(usr_op++);
}

char std_next_char() {
    if (std_size <= 0 && std_read_buff() == 0) {
        return -1;
    } 
    std_size--;
    return *(std_op++);
}

#define WA \
    exit(1)
    // printf("Rerult: \033[31m Wrong Answer \033[0m \n");
    

#define AC \
    exit(0)
    // printf("Rerult: \033[32m Accepted \033[0m \n");
    

#define FILE_ERRER \
    perror("\033[31m 没有对比输出文件 \033[0m"); \
    exit(-1)

int main(int argc, char const *argv[])
{
    // printf("%s\n", argv[1]);
    stdfp = fopen(argv[1], "r");
    if (stdfp == NULL) {
        FILE_ERRER;
    }
    char in_usr, in_std;
    do {
        in_std = std_next_char();
        in_usr = usr_next_char();
        // printf("%d %d ==== \n", (int)in_std, (int)in_usr);
        if (in_std != in_usr) {
            fclose(stdfp);
            WA;
        }
    } while (in_std != -1 && in_usr != -1);
    fclose(stdfp);
    AC;
    return 0;
}
