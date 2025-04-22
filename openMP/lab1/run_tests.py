#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import subprocess
import re
import time
import matplotlib.pyplot as plt
import matplotlib as mpl


def compile_programs():
    """编译程序"""
    print("编译程序...")
    
    # 编译矩阵乘法程序
    subprocess.run(["gcc-14", "-fopenmp", "matrix_multiply.c", "-o", "matrix_multiply", "-lm"])
    
    # 编译正弦函数计算程序
    subprocess.run(["gcc-14", "-fopenmp", "sine_calculation.c", "-o", "sine_calculation", "-lm"])
    
    print("编译完成\n")

def run_command_with_time(command):
    """运行命令并记录时间"""
    # 构建shell命令，使用time命令并将输出重定向
    shell_command = f"/usr/bin/time -p {' '.join(command)} 2>&1"
    
    # 通过shell执行命令
    process = subprocess.Popen(shell_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
    stdout, stderr = process.communicate()
    
    # 合并输出
    output = stdout

    # 从输出中提取时间
    time_match = re.search(r'real\s+(\d+\.\d+)', output)
    
    if time_match:
        time_in_seconds = float(time_match.group(1))
        # 移除时间信息行，获取程序原始输出
        program_output = re.sub(r'real\s+\d+\.\d+\s*user\s+\d+\.\d+\s*sys\s+\d+\.\d+\s*', '', output).strip()
        return time_in_seconds, program_output
    else:
        return None, output

def run_matrix_tests():
    """运行矩阵乘法测试"""
    print("===============================================")
    print("矩阵乘法测试 (8000 x 8000)")
    print("===============================================")
    
    results = {"线程数": [], "执行时间(秒)": [], "加速比": []}
    
    # 运行串行版本
    print("运行串行版本...")
    serial_time, _ = run_command_with_time(["./matrix_multiply", "0"])
    
    if serial_time is None:
        print("无法获取串行版本运行时间")
        return
    
    print(f"串行执行时间: {serial_time:.2f}秒\n")
    
    # 添加串行版本的结果
    results["线程数"].append(1)
    results["执行时间(秒)"].append(serial_time)
    results["加速比"].append(1.0)
    
    # 测试不同的线程数
    for threads in [2, 4, 6]:
        print(f"运行并行版本 ({threads} 线程)...")
        
        # 设置OpenMP线程数
        os.environ["OMP_NUM_THREADS"] = str(threads)
        
        # 运行并行版本
        parallel_time, _ = run_command_with_time(["./matrix_multiply", "1"])
        
        if parallel_time is None:
            print(f"无法获取 {threads} 线程并行版本运行时间")
            continue
        
        # 计算加速比
        speedup = serial_time / parallel_time
        
        # 记录结果
        results["线程数"].append(threads)
        results["执行时间(秒)"].append(parallel_time)
        results["加速比"].append(speedup)
        
        print(f"并行执行时间 ({threads} 线程): {parallel_time:.2f}秒")
        print(f"加速比: {speedup:.2f}\n")
    
    return results

def run_sine_tests():
    """运行正弦函数计算测试"""
    print("===============================================")
    print("正弦函数计算测试")
    print("===============================================")
    
    results = {"线程数": [], "执行时间(秒)": [], "加速比": []}
    
    # 测试参数
    x_value = 1.5
    
    # 运行串行版本
    print("运行串行版本...")
    serial_time, output = run_command_with_time(["./sine_calculation", "0"])
    
    if serial_time is None:
        print("无法获取串行版本运行时间")
        return
    
    print(f"串行执行时间: {serial_time:.2f}秒")
    print(output)
    
    # 添加串行版本的结果
    results["线程数"].append(1)
    results["执行时间(秒)"].append(serial_time)
    results["加速比"].append(1.0)
    
    # 测试不同的线程数
    for threads in [2, 4, 6]:
        print(f"运行并行版本 ({threads} 线程)...")
        
        # 设置OpenMP线程数
        os.environ["OMP_NUM_THREADS"] = str(threads)
        
        # 运行并行版本
        parallel_time, output = run_command_with_time(["./sine_calculation", "1"])
        
        if parallel_time is None:
            print(f"无法获取 {threads} 线程并行版本运行时间")
            continue
        
        # 计算加速比
        speedup = serial_time / parallel_time
        
        # 记录结果
        results["线程数"].append(threads)
        results["执行时间(秒)"].append(parallel_time)
        results["加速比"].append(speedup)
        
        print(f"并行执行时间 ({threads} 线程): {parallel_time:.2f}秒")
        print(f"加速比: {speedup:.2f}")
        print(output)
    
    return results

def save_results_to_file(matrix_results, sine_results):
    """将测试结果保存到文件"""
    with open("test_results.txt", "w") as f:
        f.write("===============================================\n")
        f.write("矩阵乘法测试结果 (8000 x 8000)\n")
        f.write("===============================================\n")
        f.write("线程数\t执行时间(秒)\t加速比\n")
        
        for i in range(len(matrix_results["线程数"])):
            f.write(f"{matrix_results['线程数'][i]}\t{matrix_results['执行时间(秒)'][i]:.2f}\t{matrix_results['加速比'][i]:.2f}\n")
        
        f.write("\n===============================================\n")
        f.write("正弦函数计算测试结果\n")
        f.write("===============================================\n")
        f.write("线程数\t执行时间(秒)\t加速比\n")
        
        for i in range(len(sine_results["线程数"])):
            f.write(f"{sine_results['线程数'][i]}\t{sine_results['执行时间(秒)'][i]:.2f}\t{sine_results['加速比'][i]:.2f}\n")

def plot_results(matrix_results, sine_results):
    # 尝试使用英文标签重新绘图
    try:
        # 创建一个2x2的图表布局
        fig, axs = plt.subplots(2, 2, figsize=(15, 10))
        
        # 矩阵乘法执行时间
        axs[0, 0].plot(matrix_results["线程数"], matrix_results["执行时间(秒)"], 'o-')
        axs[0, 0].set_title('Matrix Multiplication Time')
        axs[0, 0].set_xlabel('Number of Threads')
        axs[0, 0].set_ylabel('Execution Time (s)')
        axs[0, 0].grid(True)
        
        # 矩阵乘法加速比
        axs[0, 1].plot(matrix_results["线程数"], matrix_results["加速比"], 'o-')
        axs[0, 1].set_title('Matrix Multiplication Speedup')
        axs[0, 1].set_xlabel('Number of Threads')
        axs[0, 1].set_ylabel('Speedup')
        axs[0, 1].grid(True)
        
        # 正弦计算执行时间
        axs[1, 0].plot(sine_results["线程数"], sine_results["执行时间(秒)"], 'o-')
        axs[1, 0].set_title('Sine Calculation Time')
        axs[1, 0].set_xlabel('Number of Threads')
        axs[1, 0].set_ylabel('Execution Time (s)')
        axs[1, 0].grid(True)
        
        # 正弦计算加速比
        axs[1, 1].plot(sine_results["线程数"], sine_results["加速比"], 'o-')
        axs[1, 1].set_title('Sine Calculation Speedup')
        axs[1, 1].set_xlabel('Number of Threads')
        axs[1, 1].set_ylabel('Speedup')
        axs[1, 1].grid(True)
        
        plt.tight_layout()
        plt.savefig('performance_results_en.png')
        print("使用英文标签的图表已保存为 'performance_results_en.png'")
    except Exception as e2:
        print(f"使用英文标签绘图也失败: {e2}")
        print("请确保已安装matplotlib库")

def main():
    """主函数"""
    compile_programs()
    
    # 运行测试并收集结果
    matrix_results = run_matrix_tests()
    sine_results = run_sine_tests()
    

    if matrix_results and sine_results:
        save_results_to_file(matrix_results, sine_results)
        try:
            plot_results(matrix_results, sine_results)
        except ImportError:
            print("警告: 无法导入matplotlib，跳过图表生成")


if __name__ == "__main__":
    main() 