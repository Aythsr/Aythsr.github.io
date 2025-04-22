# OpenMP实验

本实验中包含两个程序：矩阵乘法和正弦函数计算，每个程序都有串行和并行（OpenMP）两个版本。

## 文件列表

- `matrix_multiply.c`: 8000x8000矩阵乘法的串行和并行实现
- `sine_calculation.c`: 使用泰勒级数计算正弦函数的串行和并行实现
- `run_tests.sh`: Bash测试脚本，用于对比不同线程数下的性能并计算加速比
- `run_tests.py`: Python测试脚本，符合作业要求的实现方式
- `作业要求.md`: 实验要求文档

## 使用方法

### 编译

```bash
gcc -O2 -fopenmp matrix_multiply.c -o matrix_multiply -lm
gcc -O2 -fopenmp sine_calculation.c -o sine_calculation -lm
```

### 运行矩阵乘法

```bash
# 串行版本
./matrix_multiply 0

# 并行版本（需要设置OMP_NUM_THREADS环境变量指定线程数）
export OMP_NUM_THREADS=4  # 使用4个线程
./matrix_multiply 1
```

### 运行正弦函数计算

```bash
# 串行版本，计算sin(1.5)
./sine_calculation 0

# 并行版本，计算sin(1.5)（需要设置OMP_NUM_THREADS环境变量指定线程数）
export OMP_NUM_THREADS=4  # 使用4个线程
./sine_calculation 1
```

### 自动测试

使用Python测试脚本可以自动运行所有测试并计算加速比：

```bash
python3 run_tests.py
```

或者使用Bash测试脚本：

```bash
chmod +x run_tests.sh
./run_tests.sh
```

测试脚本会自动运行串行版本和线程数为2、4、6的并行版本，并计算加速比。 