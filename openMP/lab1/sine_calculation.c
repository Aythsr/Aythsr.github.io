#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define PI 3.14159265358979323846
#define TERMS 10000000 // 泰勒级数项数

// 预计算阶乘，避免重复计算
double factorial_values[TERMS * 2 + 1];

// 初始化阶乘数组
void initialize_factorials() {
    factorial_values[0] = 1.0;
    factorial_values[1] = 1.0;
    for (int i = 2; i <= TERMS * 2; i++) {
        factorial_values[i] = factorial_values[i-1] * i;
    }
}

// 获取阶乘值（使用预计算的阶乘表）
double factorial(int n) {
   
   return factorial_values[n];
}

// 串行计算sin(x)，使用泰勒级数
double calculate_sine_serial(double x) {
    // 将x归一化到[-PI, PI]区间
    x = fmod(x, 2 * PI);
    if (x > PI) {
        x -= 2 * PI;
    } else if (x < -PI) {
        x += 2 * PI;
    }
    printf("%.2f\n",x);
    double result = 0.0;
    double x_pow = x; // x^1
    int sign = 1;
    
    for (int i = 0; i < TERMS; i++) {
        int n = 2 * i + 1;
        double term = sign * x_pow / factorial(n);
        result += term;
        
        // 提前终止条件
        // if (fabs(term) < 1e-15) {
        //     break;
        // }
        
        // 为下一次迭代准备
        sign = -sign;
        x_pow *= x * x; // 更新为 x^(2i+3)
    }
    
    return result;
}

// OpenMP并行计算sin(x)，使用泰勒级数
double calculate_sine_parallel(double x) {
    // 将x归一化到[-PI, PI]区间
    x = fmod(x, 2 * PI);
    if (x > PI) {
        x -= 2 * PI;
    } else if (x < -PI) {
        x += 2 * PI;
    }
    
    double result = 0.0;
    int chunk_size = 1000; // 调整块大小以平衡负载
    
    // 使用reduction避免critical段
    #pragma omp parallel for reduction(+:result) schedule(dynamic, chunk_size)
    for (int i = 0; i < TERMS; i++) {
        int n = 2 * i + 1;
        double x_pow = pow(x, n); // 计算x的n次方
        double term = ((i % 2 == 0) ? 1.0 : -1.0) * x_pow / factorial(n);

        
        result += term;
    }
    
    return result;
}

int main(int argc, char* argv[]) {
    int run_mode = 0; // 0表示串行，1表示并行
    double x = PI / 4; // 默认计算sin(π/4)
    
    if (argc > 1) {
        run_mode = atoi(argv[1]);
    }
    
    if (argc > 2) {
        x = atof(argv[2]);
    }
    
    // 初始化阶乘表
    initialize_factorials();
    
    double sine_value;
    
    if (run_mode == 0) {
        // 串行模式
        sine_value = calculate_sine_serial(x);
        printf("Serial sine calculation: sin(%f) = %f\n", x, sine_value);
    } else {
        // 并行模式
        sine_value = calculate_sine_parallel(x);
        printf("Parallel sine calculation: sin(%f) = %f\n", x, sine_value);
    }
    
    // 与标准库函数比较
    printf("Math library sin(%f) = %f\n", x, sin(x));
    
    return 0;
} 