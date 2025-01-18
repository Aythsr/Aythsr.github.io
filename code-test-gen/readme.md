## xzl的出数据模板框架  `bash` 环境

### `ST_pack` 是标准的单题模板框架

### `extract.sh` 脚本是对一个比赛进行压缩提取，只提取出数据和std

#### 目录结构
```` cpp

----content-----
 |             |
 |             -------ST_pack2
 |             |
 |             -------ST_pack1---
 |                              |
 |                              -------base.sh 一些全局参数，基本不用改
 ------extract.sh               |
                                -------getdata.sh 调整参数，利用data.cpp 生成in文件，调整一下输入data的参数即可
                                |
                                -------exec.sh 生成ans文件，基本不用改
                                |
                                -------data.cpp 自己调整，数据生成器
                                |
                                -------std.cpp  自己调整
                                |
                                -------makefile 主要是更新编译std
                                |
                                -------xe.sh 用来执行测试std的，简化编译命令
                                |
                                --------test 测试点文件夹
                                         |
                                         -------*.in
                                         |
                                         -------*.ans


       
````

### 压缩后文件格式

###### 命令：`./extract.sh src_dir`
 例如 `./extract src_dir` ，会将`src_dir` 文件夹下内容提取出来，并且压缩为 `src_dir.zip` 文件

```` cpp

content.zip
      |
      ---------data/
      |           | 
      |           --------problem1_data.zip
      |           |                 |
      |           |                 ----------- *.in
      |           |                 |  
      |           |                 ----------- *.ans
      |           | 
      |           --------problem2_data.zip   
      |
      |
      |
      ---------std/
                 |
                 ----------problem1_std.cpp
                 |
                 ----------problem2_std.cpp
````