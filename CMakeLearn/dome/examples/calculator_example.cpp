// Copyright 2023 MyLib Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "mylib/mylib.h"

#include <iostream>

int main() {
  // 创建Calculator实例
  mylib::Calculator calculator;
  
  // 使用Add方法
  int sum = calculator.Add(5, 3);
  std::cout << "5 + 3 = " << sum << std::endl;
  
  // 使用Subtract方法
  int difference = calculator.Subtract(10, 4);
  std::cout << "10 - 4 = " << difference << std::endl;
  
  // 获取库版本
  std::cout << "MyLib版本: " << mylib::Calculator::GetVersion() << std::endl;
  
  return 0;
}