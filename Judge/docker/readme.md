# docker 使用ubuntu技巧 默认[root]





### 1 安装

安装docker

```bash
 # 官方的安装脚本
 curl -fsSL https://test.docker.com -o test-docker.sh
 sudo sh test-docker.sh
```

> `cat /etc/issue` 查看docker中ubuntu的版本号



安装完docker后，一般会自动创建 `docker` 用户组，我们将当前用户加入 `docker ` 用户组，可以减少权限的限制，否则每次操作都要加`sudo`（非root用户）

**使用 `gpasswd` 命令** （使用命令时对于非root用户需要root权限）

```bash
gpasswd [可选项] 组名
# 例如
gpasswd -a user_name group_name # 添加user_name用户到了group_name
gpasswd -a ${USER} docker # 添加当前用户到docker组
```

**可选项参数**：

- -a：添加用户到组；
- -d：从组删除用户；
- -A：指定管理员；
- -M：指定组成员和-A的用途差不多；
- -r：删除密码；
- -R：限制用户登入组，只有组中的成员才可以用newgrp加入该组。





### 2 ubuntu 换源


本节均为 Ubuntu 22.04 的镜像源列表。若为其他版本，将所有`focal`更改为其他版本代号即可。

常用的Ubuntu版本代号如下：

- Ubuntu 22.04：jammy
- Ubuntu 20.04：focal
- Ubuntu 18.04：bionic
- Ubuntu 16.04：xenial

> Ubuntu 通常采用“形容词+小动物”作为版本代号（默认的壁纸），在镜像源列表中只有第一个词。

此外，默认注释了代码源以提高速度，注释了预发布软件源（可能不稳定）。如有需要可以取消注释。

建议将所有常用镜像源保存在`/etc/apt`目录下，并命名为类似`source.list.aliyun`的形式，需要使用时直接复制替换`source.list`文件即可。



###### 清华

```bash
# 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-security main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-security main restricted universe multiverse

# 预发布软件源，不建议启用
# deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-proposed main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-proposed main restricted universe multiverse


```



###### 阿里

```bash
deb http://mirrors.aliyun.com/ubuntu/ jammy main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ jammy main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ jammy-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ jammy-security main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ jammy-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ jammy-updates main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ jammy-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ jammy-proposed main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ jammy-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ jammy-backports main restricted universe multiverse

```



###### 中科大

```bash
deb https://mirrors.ustc.edu.cn/ubuntu/ jammy main restricted universe multiverse
deb-src https://mirrors.ustc.edu.cn/ubuntu/ jammy main restricted universe multiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse
deb-src https://mirrors.ustc.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse
deb-src https://mirrors.ustc.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ jammy-security main restricted universe multiverse
deb-src https://mirrors.ustc.edu.cn/ubuntu/ jammy-security main restricted universe multiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ jammy-proposed main restricted universe multiverse
deb-src https://mirrors.ustc.edu.cn/ubuntu/ jammy-proposed main restricted universe multiverse


```



###### 网易163

```bash
deb http://mirrors.163.com/ubuntu/ jammy main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ jammy-security main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ jammy-updates main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ jammy-proposed main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ jammy-backports main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ jammy main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ jammy-security main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ jammy-updates main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ jammy-proposed main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ jammy-backports main restricted universe multiverse


```



### 3 bash补全



1. 安装 **bash-completion** 脚本，执行命令 `apt install bash-completion`，实际上这条命令就是在 `/etc/profile.d/` 下放置了 `bash_completion.sh` 文件，这个文件使用 `source` 执行后，当前用户就能进行补全。
2. 为了一劳永逸，我们在当前用户的 `~/.bashrc` 文件最后一行加上一句 `source /etc/profile.d/bash_completion.sh` 。即可。

> `bashrc` 文件是bash的启动脚本，每当一个用户登录时，当前用户文件夹下的 `bashrc` 脚本都会执行一遍。
>
> 所以如果用户登录之后默认使用bash，在 `bashrc` 中可以配置一些自动项，例如设置栈空间 `ulimit -s 102400` 设置 100MB 栈空间。



###### 注意：

以下这坨是 chatGPT写的，但是好像没用，我也不知道为什么，好像不会执行这个脚本？？？

>`/etc/profile.d` 是 Ubuntu 系统中一个特定的文件夹，用于存储系统全局的 shell 脚本配置文件。
>
>当用户登录到 Ubuntu 的时候，系统会自动执行 `/etc/profile` 脚本文件来设置环境变量和执行其他一些全局的配置。然而，直接修改 `/etc/profile` 文件可能会导致一些问题，尤其是当系统升级时可能会被重写。
>
>为了解决这个问题，Ubuntu 使用了 `/etc/profile.d` 目录。**该目录下的所有脚本都会在用户登录时被执行**，以实现自定义的全局配置。每个脚本文件都会单独执行，并且按照文件名顺序执行，通常以 `.sh` 结尾。
>
>通过将自定义的配置脚本放置在 `/etc/profile.d` 目录下，你可以确保它们会在用户登录时被执行，而且不会影响系统的其他配置文件。这样就可以方便地添加、修改或删除全局的环境变量和其他系统配置。



#### 4 安装编译环境

1. `g++` ：`apt install g++`
2. `python3`：`apt install python3`
3. `jdk8`：`apt-get install openjdk-8-jdk`

> 查看当前java版本：`java -version`
>
> 查看已安装的的java：`sudo update-alternatives --list java`
>
> 查看java优先级：`update-alternatives --display java`
>
> 切换jdk版本：`sudo update-alternatives --config java`




### 5 docker 容器制造

docker仓库：https://hub.docker.com/

`docker login` ：登录，**用户名用小写！！！！！** 不然不能登录，会一直报账号密码错误

`docker logout` ：退出

`docker commit -m="has update" -a="runoob" e218edb10161 runoob/ubuntu:v2` 创造一个镜像

> 各个参数说明：
>
> - **-m:** 提交的描述信息
> - **-a:** 指定镜像作者
> - **e218edb10161：**容器 ID，或者你用容器名称也行
> - **runoob/ubuntu:v2:** 指定要创建的目标镜像名

`docker push` 推送自己的镜像到云端

> ```bash
> Usage:  docker push [OPTIONS] NAME[:TAG]
> 
> Upload an image to a registry
> 
> Aliases:
>   docker image push, docker push
> 
> Options:
>   -a, --all-tags                Push all tags of an image to the repository
>       --disable-content-trust   Skip image signing (default true)
>   -q, --quiet                   Suppress verbose output
> ```



##### 镜像（images）

`docker pull ubuntu:20.04`：拉取一个镜像

`docker images`：列出本地所有镜像

`docker image rm ubuntu:20.04` 或 `docker rmi ubuntu:20.04`：删除镜像ubuntu:20.04

`docker [container] commit CONTAINER IMAGE_NAME:TAG`：创建某个container的镜像

`docker save -o ubuntu_20_04.tar ubuntu:20.04`：将镜像ubuntu:20.04导出到本地文件ubuntu_20_04.tar中

`docker load -i ubuntu_20_04.tar`：将镜像ubuntu:20.04从本地文件ubuntu_20_04.tar中加载出来



##### 容器(container)

`docker [container] create -it ubuntu:20.04`：利用镜像ubuntu:20.04创建一个容器。

`docker ps -a`：查看本地的所有容器

`docker [container] start CONTAINER`：启动容器

`docker [container] stop CONTAINER`：停止容器

`docker [container] restart CONTAINER`：重启容器

`docker [contaienr] run -itd ubuntu:20.04`：创建并启动一个容器

`docker [container] attach CONTAINER`：进入容器

先按`Ctrl-p`，再按`Ctrl-q`可以挂起容器

`docker [container] exec CONTAINER COMMAND`：在容器中执行命令

`docker [container] rm CONTAINER`：删除容器

`docker container prune`：删除所有已停止的容器

`docker export -o xxx.tar CONTAINER`：将容器CONTAINER导出到本地文件xxx.tar中

`docker import xxx.tar image_name:tag`：将本地文件xxx.tar导入成镜像，并将镜像命名为image_name:tag

`docker export/import`与`docker save/load`的区别：

> * `export/import`会丢弃历史记录和元数据信息，仅保存容器当时的快照状态
>
> * `save/load`会保存完整记录，体积更大

`docker top CONTAINER`：查看某个容器内的所有进程

`docker stats`：查看所有容器的统计信息，包括CPU、内存、存储、网络等信息

`docker cp xxx CONTAINER:xxx 或 docker cp CONTAINER:xxx xxx`：在本地和容器间复制文件

`docker rename CONTAINER1 CONTAINER2`：重命名容器

`docker update CONTAINER --memory 500MB`：修改容器限制



