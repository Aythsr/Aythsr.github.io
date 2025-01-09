# 心血来潮写一个判题机

## 0.0.1  2023/7/12

脑子里一片浆糊，不知道先做什么，就随便找个点开始。毫无逻辑。\
这时候的设计是，先实现C语言实现一个程序的运行，顺便搞搞并发。\
实在没有想到如何用C语言实现一个C语言的编译运行。。。。 \
最后还是用上了`system`去调用shell去执行。直接用shell的`timeout`命令进行时限（SB的ChatGPT说`timeout`不能用小数，查了文档是可以用小数的） 

> `system` 返回的参数是 `int`，高八位是调用命令的返回值，低八位是捕获的信号量
> 在C语言中，`system`函数执行外部命令并返回命令的退出状态码。状态码通常是一个整数值，用于指示命令执行的结果。
>
> 状态码由两部分组成，高8位表示命令退出的状态，低8位表示命令退出时的信号。
> 
> 状态部分通常使用以下值：
> - 0：命令成功执行并退出。
> - 非零值：命令执行失败，具体值可能有不同的含义，可以根据具体命令的文档或相关说明进行解释。
> 
> 信号部分表示在命令退出时发送给命令进程的信号值。常见的一些信号值包括：
> - 2（SIGINT）：表示用户发出中断信号（通常是通过键盘按下Ctrl+C）。
> - 9（SIGKILL）：表示强制终止命令的信号。

顺便实现了一个多线程和外部参数定义 


## 0.0.2 2023/7/13

还是乱七八糟的代码

稍微有点框架了 \
先写了一个比对程序，比对的方式是调用 `timeout 7.0s ./a.out < ./test_data/0001/1.in | ./diffg.out ./test_data/0001/1.ans` 的方式来进行比较 \
用了一个管道，感觉会快一丢丢？ \
把原来的 `judge` 改名成了 `core`，感觉 `core` 作为一个判题核心更好，用来进行一个题的测试，然后再这个题目判定的时候开一堆的线程进行不同测试点的测试。 \
实际上有点面向对象的意思了，后面打算用C++全部重写一遍。 \
然后加了一个题目配置，在判题的时候会先读取题目的配置，然后定义一堆初始变量。 

> 小发现：管道是内存空间，并且管道后的程序是并行的，只是会等待前面的输出


## cgroup学习 2023/7/14

唉，学得太累了，网上教程都是V1的，结果我的ubunutu22.04是V2.。。。。。。


## 0.0.3 完成部分cgroup组的c语言开发 2023/7/15

完成了cgroup组的开发，就是一个 `manage_cgroup` 的代码 \
完成了对配置文件读入的开发，是一个 `read_config` 的代码

> 小发现，vscode可以自定义后缀的高亮显示，在设置-》编辑器里面修改就好了，或者在vscode右下角就可以设置渲染格式。


## 2023/7/18 发现新的C系统函数(放弃system调用bash)



这玩意比直接调用bash的效率高多了

```bash
EXEC(3) 

NAME
       execl, execlp, execle, execv, execvp, execvpe - execute a file

SYNOPSIS
       #include <unistd.h>

       extern char **environ;

       int execl(const char *pathname, const char *arg, ...
                       /* (char  *) NULL */);
       int execlp(const char *file, const char *arg, ...
                       /* (char  *) NULL */);
       int execle(const char *pathname, const char *arg, ...
                       /*, (char *) NULL, char *const envp[] */);
       int execv(const char *pathname, char *const argv[]);
       int execvp(const char *file, char *const argv[]);
       int execvpe(const char *file, char *const argv[],
                       char *const envp[]);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       execvpe(): _GNU_SOURCE

DESCRIPTION
# 大意就是，这些函数是系统级函数，可以调用程序并且加载到当前进程的空间，相当于就是在当前的进程空间下直接跳转到新程序下运行。
       The  exec()  family  of  functions replaces the current process image with a new process image.  The functions described in this manual page are layered on top of execve(2).  (See the manual page for execve(2) for further  details  about  the  re‐placement of the current process image.)

       The initial argument for these functions is the name of a file that is to be executed.

       The functions can be grouped based on the letters following the "exec" prefix.

```


```bash
System calls

NAME
       getrlimit, setrlimit, prlimit - get/set resource limits

SYNOPSIS
       #include <sys/time.h>
       #include <sys/resource.h>

       int getrlimit(int resource, struct rlimit *rlim);
       int setrlimit(int resource, const struct rlimit *rlim);

       int prlimit(pid_t pid, int resource, const struct rlimit *new_limit,
                   struct rlimit *old_limit);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       prlimit(): _GNU_SOURCE

DESCRIPTION
       The getrlimit() and setrlimit() system calls get and set resource limits.  Each resource has an associated soft and hard limit, as defined by the rlimit structure:

           struct rlimit {
               rlim_t rlim_cur;  /* Soft limit */
               rlim_t rlim_max;  /* Hard limit (ceiling for rlim_cur) */
           };

       The soft limit is the value that the kernel enforces for the corresponding resource.  The hard limit acts as a ceiling for the soft limit: an unprivileged process may set only its soft limit to a value in the range from 0 up to the hard limit, and (irreversibly) lower its hard limit.  A privileged process (under Linux: one  with  the
       
       CAP_SYS_RESOURCE capability in the initial user namespace) may make arbitrary changes to either limit value.

       The value RLIM_INFINITY denotes no limit on a resource (both in the structure returned by getrlimit() and in the structure passed to setrlimit()).


```