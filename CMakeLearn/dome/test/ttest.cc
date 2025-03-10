#include <iostream>

int main(int argc, char **argv) {
    if (argc != 2) {
        return 99;
    }
    int a = atoi(argv[1]);
    return a;
}