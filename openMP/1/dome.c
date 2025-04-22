#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int main(int argc, char **argv) {
    int tn = 4;
    if (argc > 1){
        tn = atoi(argv[1]);
    }
    omp_set_num_threads(tn);

    double *A = (double*)malloc(N * N * sizeof(double));
    double *B = (double*)malloc(N * N * sizeof(double));
    double *C = (double*)malloc(N * N * sizeof(double));
    
    // 初始化矩阵
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = 1.0;
            B[i * N + j] = 2.0;
            C[i * N + j] = 0.0;
        }
    }

    double start_time = omp_get_wtime();
    
    // 矩阵乘法计算
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }

    double end_time = omp_get_wtime();
    printf("计算时间: %f 秒\n", end_time - start_time);

    // 验证结果（只打印一个元素作为示例）
    printf("C[0][0] = %f\n", C[0]);

    free(A);
    free(B);
    free(C);
    return 0;
}