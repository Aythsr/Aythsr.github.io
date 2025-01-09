## 一些库函数

### 时间类

#### C程序库获取时间

##### 系统时间 `int clock_gettime (clockid_t __clock_id, struct timespec *__tp)` [线程安全]

```c

#include<time.h>
int clock_gettime (clockid_t __clock_id, struct timespec *__tp) \\ 获取程序时间

/**
 * __clock_id : 检索和设置的__clock_id指定的时钟时间。
 *   CLOCK_REALTIME:系统实时时间,随系统实时时间改变而改变,即从UTC1970-1-1 0:0:0开始计时,中间时刻如果系统时间被用户改成其他,则对应的时间相应改变。
 *   CLOCK_MONOTONIC:从系统启动这一刻起开始计时,不受系统时间被用户改变的影响。
 *   CLOCK_PROCESS_CPUTIME_ID:本进程到当前代码系统CPU花费的时间。
 *   CLOCK_THREAD_CPUTIME_ID:本线程到当前代码系统CPU花费的时间。 
*/
// 时间变量结构体
struct timespec {
	__kernel_old_time_t	tv_sec;		/* seconds 秒*/
	long			tv_nsec;	/* nanoseconds 纳秒！纳秒！纳秒*/
};

```

##### 进程时间 `clock_t clock(void);` [线程安全]
```c

#include <time.h>

clock_t clock(void);

clock() // 获取的是当前进程的CPU时间
CLOCKS_PER_SEC // 常量,一秒的CPU时间的常量。

int st = clock();
/**
 * 执行代码片段
*/
int ed = clock();

float t = 1.0 * (ed - st) / CLOCKS_PER_SEC; // 代码片段执行的CPU时间，单位为秒

```

#### C程序库休眠类

##### 纳秒级 `int nanosleep(const struct timespec *req, struct timespec *rem);` [线程安全]

```c

#include <time.h>

int nanosleep(const struct timespec *req, struct timespec *rem);

req： struct timespec类型指针，设置休眠的时间
rem： 若remain不为NULL，那么指针指向的缓冲区返回剩余的休眠时间


```

##### 微秒级 `int usleep(useconds_t usec);` [线程安全]

```c


#include <unistd.h>

int usleep(useconds_t usec); // 休眠微妙级的时间

// 以下是usleep的实现
// 在手册中说 The type useconds_t is an unsigned integer type capable of holding integers in the range [0,1000000]
// 但是好像其实用大于1000000的数字也没关系，只要在unsigned integer以内就行


#include <time.h>
#include <unistd.h>

int
usleep (useconds_t useconds)
{
  struct timespec ts = { .tv_sec = (long int) (useconds / 1000000),
			 .tv_nsec = (long int) (useconds % 1000000) * 1000ul };

  /* Note the usleep() is a cancellation point.  But since we call
     nanosleep() which itself is a cancellation point we do not have
     to do anything here.  */
  return __nanosleep (&ts, NULL);
}

```

##### 秒级 `unsigned int sleep(unsigned int seconds);` [线程安全]

```c

#include <unistd.h>
unsigned int sleep(unsigned int seconds); // 休眠秒级的时间

```