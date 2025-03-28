#pragma once
#ifndef MYLIB_MYLIB_H_
#define MYLIB_MYLIB_H_

#include <string>

namespace mylib {

/**
 * @brief 示例类
 *
 * 这是一个示例类，用于展示库的基本功能。
 */
class Calculator {
 public:
  /**
   * @brief 默认构造函数
   */
  Calculator() = default;

  /**
   * @brief 析构函数
   */
  ~Calculator() = default;

  /**
   * @brief 加法运算
   *
   * @param a 第一个操作数
   * @param b 第二个操作数
   * @return 两数之和
   */
  int Add(int a, int b) const;

  /**
   * @brief 减法运算
   *
   * @param a 第一个操作数
   * @param b 第二个操作数
   * @return 两数之差
   */
  int Subtract(int a, int b) const;

  /**
   * @brief 获取库版本信息
   *
   * @return 版本信息字符串
   */
  static std::string GetVersion();
};

}  // namespace mylib

#endif  // MYLIB_MYLIB_H_