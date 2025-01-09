#include <stdio.h>

int main() {
    printf("===\n");
    int a;
    while (scanf("%d", &a) != EOF) {
        printf("==%d", a);
    }
    printf("\n");
    return 0;
}