[TOC]

# C++三方库基准测试

对 C++ 三方库进行基准测试



## 1. 环境

- `Visual Studio 2022`

- `CMake3.15`



## 2. 下载及编译

使用 `google/benchmark` 作为测试工具，所以需要下载 `submodule`。

```
git clone --recursive git@github.com:august295/benchmark_3rdparty.git
```

工程使用 `CMake` 构建。运行以 `test` 目录下对应测试项目作为启动项即可。

### 2.1. Visual Studio 2022

```cmd
cmake -B"build" -G"Visual Studio 17 2022"
```






# 参考

