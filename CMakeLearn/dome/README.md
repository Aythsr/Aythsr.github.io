# C++ Library Project

这是一个符合Google C++风格指南的标准CMake项目。

## 项目结构

```
├── CMakeLists.txt        # 主CMake配置文件
├── include/              # 公共头文件
│   └── mylib/            # 库的头文件
├── src/                  # 源代码
├── test/                 # 测试代码
├── examples/             # 示例代码
└── cmake/                # CMake模块和配置
```

## 构建项目

```bash
# 创建构建目录
mkdir build && cd build

# 配置项目
cmake ..

# 构建项目
cmake --build .

# 运行测试
ctest
```

## 依赖

- CMake 3.20 或更高版本
- C++14 兼容的编译器
- Google Test