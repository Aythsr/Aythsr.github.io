# sqlite3 C/C++ api学习笔记

链接：[菜鸟教程](https://www.runoob.com/sqlite/sqlite-c-cpp.html)

常用的就只有三个函数：

- `int sqlite3_open(const char *filename, sqlite3 **ppDB)`
> `filename`: 代表数据库文件的路径。
>
> 如果 filename 参数是 NULL 或':memory:'，那么 `sqlite3_open()` 将会在 RAM 中创建一个内存数据库，这只会在 session 的有效时间内持续。
>
> `ppDB` 为一个指向 sqlite Obj 指针的指针，用来存储sqlite Object。 
>
> 返回值为 SQLITE_OK(0) 时，表示打开文件成功。否则代表失败，此时，可以用 `const char *sqlite3_errmsg(sqlite3*)` 函数输出失败原因。
>
> 

- `int sqlite3_exec(sqlite3*, const char *sql, sqlite_callback, void *data, char **errmsg)`
> 第一个参数，代表一个sql连接。\
> 第二个参数，代表需要执行的sql语句。\
> 第三个参数，是一个回调函数。\
> 第四个参数，供给第三个参数使用。\
> 第五个参数，代表错误信息。\
> 关于回调函数： `int (*callback)(void*,int,char**,char**)` 
>
> > 当执行一个查询后，对于每一行的结果，都会调用一次回调函数。\
> > 第一个参数来源于`sqlite3_exec`的第四个参数，第二个参数代表查询的行的列数，第三个参数代表每一列的值，第四个参数代表每一列的列名。

- `int sqlite3_close(sqlite3*)`
> 关闭一个sqlite连接，并且销毁sqlite对象。\
> 返回值为 SQLITE_OK(0) 时，表示关闭文件成功，否则失败。

实验代码：

```cpp
#include <iostream>
#include <sqlite3.h>

using namespace std;

int cab(void *nouser, int argc, char **val, char **colname) {
    printf("%s \n", static_cast<const char*>(nouser));
    for (int i = 0; i < argc; ++i) {
        printf("%s = %s\n", colname[i], val[i] ? val[i] : "NULL");
    }
    printf(" --------- \n");
    return 0;
}

int main() {
    sqlite3* dbptr;
    int rp = sqlite3_open("/Users/aythsr/Documents/DB_file/t1.sqlite3", &dbptr);
    if (rp) {
        printf("no : %s\n", sqlite3_errmsg(dbptr));
        return 0;
    }
    char *p; 
    char *x = "nb";
    rp = sqlite3_exec(dbptr, 
    "select * from user", cab, x, &p);
    sqlite3_close(dbptr);
    if (rp == 0) {
        printf("exec ok!\n");
    } else {
        printf("exec no! %s\n", p);
    }
    return 0;
}
```

编译命令需要带上链接库：`sqlite3`，即：`g++ dome.cpp -l sqlite3`。


sqlite支持多线程？

### Sqlite 支持多线程操作

需要在创建的时候指定特点的flag

```cpp
#ifndef __TOOL_SQLITE3__

#define __TOOL_SQLITE3__


#include <sqlite3.h>
#include <assert.h>
#include <stdio.h>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::pair;

class tool_sqlite
{
private:
    sqlite3 *conn;
    static const char * const creat_sql;
    char *buf;
public:
    char *errmsg;
    /**
     * 创建表，若存在则不创建
     * is_mutes 指定是否是支持多线程
     */
    tool_sqlite(const char* filename, bool is_mutex = true);
    ~tool_sqlite();
    /**
     * 插入数据
     */
    bool insert(const char *name, const char *passwd);
    /**
     * 检查数据是否正确
     */
    bool check(const char *name, const char *passwd);
    using Pair = pair<string, string>;
    /**
     * 获取所有的值
     */
    vector<Pair> get_all();
};

tool_sqlite::tool_sqlite(const char* filename, bool is_mutex) {
    int flag = SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE;
    if (is_mutex) flag |= SQLITE_OPEN_NOMUTEX;
    int rp = sqlite3_open_v2(filename, &conn, flag, nullptr);
    assert(rp == SQLITE_OK);
    rp = sqlite3_exec(conn, creat_sql, nullptr, nullptr, &errmsg);
    if (rp != SQLITE_OK) {
        perror(errmsg);
    }
    assert(rp == SQLITE_OK);
    buf = new char[1024];
}

tool_sqlite::~tool_sqlite() {
    sqlite3_close(conn);
    delete[] buf;
}

bool tool_sqlite::insert(const char *name, const char *passwd)
{
    sprintf(buf, "insert into Xuser (user, passwd) values ('%s', '%s');", name, passwd);
    int rp = sqlite3_exec(conn, buf, nullptr, nullptr, &errmsg);
    return rp == SQLITE_OK;
}

#include <string.h>

bool tool_sqlite::check(const char *name, const char *passwd)
{
    sprintf(buf, "select passwd from Xuser where user='%s';", name);
    struct tmp_str
    {
        bool is_exit;
        const char *passwd;
    }tmp;
    tmp.is_exit = false;
    tmp.passwd = passwd;
    auto call_back = [](void *is_exit, int argc, char **val, char **colname) -> int {
        tmp_str *p = (tmp_str*)(is_exit);
        for (int i = 0; i < argc; ++i) {
            if (strcmp(val[i], p->passwd) == 0) {
                p->is_exit = true;
            }
        }
        return 0;
    };
    int rp = sqlite3_exec(conn, buf, call_back, (void*)(&tmp), &errmsg);
    return tmp.is_exit;
}

inline vector<tool_sqlite::Pair> tool_sqlite::get_all()
{
    vector<Pair> res;
    sprintf(buf, "select user, passwd from Xuser;");
    auto call_back = [](void *res, int argc, char **val, char **) -> int {
        vector<Pair>* p = (vector<Pair>*)res;
        p->push_back(std::make_pair(string(val[0]), string(val[1])));
        return 0;
    };
    int rp = sqlite3_exec(conn, buf, call_back, (void*)(&res), &errmsg);
    return res;
}

const char * const tool_sqlite::creat_sql = "create table if not exists Xuser (\
user text primary key not null,\
passwd text not null\
)";

#endif
```

