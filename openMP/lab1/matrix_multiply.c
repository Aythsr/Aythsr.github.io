#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// 矩阵大小，根据作业要求定义为8000
#define N 8000
#define BLOCK_SIZE 16  // 缓存友好的分块大小

double A[N][N], B[N][N], C[N][N];

// 初始化矩阵
void initialize_matrices() {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = (double)rand() / RAND_MAX;
            B[i][j] = (double)rand() / RAND_MAX;
            C[i][j] = 0.0;
        }
    }
}

// 串行矩阵乘法（改进缓存利用）
void matrix_multiply_serial() {
    int i, j, k;
    
    // 使用分块策略改善缓存利用
    for (int i0 = 0; i0 < N; i0 += BLOCK_SIZE) {
        for (int j0 = 0; j0 < N; j0 += BLOCK_SIZE) {
            for (int k0 = 0; k0 < N; k0 += BLOCK_SIZE) {
                // 对每个子块执行乘法
                for (i = i0; i < i0 + BLOCK_SIZE && i < N; i++) {
                    for (j = j0; j < j0 + BLOCK_SIZE && j < N; j++) {
                        double sum = C[i][j]; // 累加到现有值
                        for (k = k0; k < k0 + BLOCK_SIZE && k < N; k++) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] = sum;
                    }
                }
            }
        }
    }
}

// OpenMP并行矩阵乘法（缓存友好版本）
void matrix_multiply_parallel() {
    // 使用最外层循环的并行化和块处理改善性能
    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic, 1) // 每个线程处理一个大块
        for (int i0 = 0; i0 < N; i0 += BLOCK_SIZE) {
            for (int j0 = 0; j0 < N; j0 += BLOCK_SIZE) {
                for (int k0 = 0; k0 < N; k0 += BLOCK_SIZE) {
                    // 对每个子块执行乘法
                    for (int i = i0; i < i0 + BLOCK_SIZE && i < N; i++) {
                        for (int j = j0; j < j0 + BLOCK_SIZE && j < N; j++) {
                            double sum = C[i][j]; // 累加到现有值
                            for (int k = k0; k < k0 + BLOCK_SIZE && k < N; k++) {
                                sum += A[i][k] * B[k][j];
                            }
                            C[i][j] = sum;
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int run_mode = 0; // 0表示串行，1表示并行
    
    if (argc > 1) {
        run_mode = atoi(argv[1]);
    }

    // 初始化随机数生成器
    srand(time(NULL));
    
    // 初始化矩阵
    initialize_matrices();
    
    if (run_mode == 0) {
        // 串行模式
        matrix_multiply_serial();
        printf("Serial matrix multiplication completed.\n");
    } else {
        // 并行模式
        matrix_multiply_parallel();
        printf("Parallel matrix multiplication completed.\n");
    }
    
    return 0;
} 