#include <iostream>
#include <sqlite3.h>

using namespace std;

int cab(void *nouser, int argc, char **val, char **colname) {
    printf("%s \n", static_cast<const char*>(nouser));
    for (int i = 0; i < argc; ++i) {
        printf("%s = %s\n", colname[i], val[i] ? val[i] : "NULL");
    }
    printf(" --------- \n");
    return 0;
}

int main() {
    sqlite3* dbptr;
    int rp = sqlite3_open("/Users/aythsr/Documents/DB_file/t1.sqlite3", &dbptr);
    if (rp) {
        printf("no : %s\n", sqlite3_errmsg(dbptr));
        return 0;
    }
    char *p; 
    char *x = "nb";
    rp = sqlite3_exec(dbptr, 
    "select * from user", cab, x, &p);
    sqlite3_close(dbptr);
    if (rp == 0) {
        printf("exec ok!\n");
    } else {
        printf("exec no! %s\n", p);
    }
    return 0;
}