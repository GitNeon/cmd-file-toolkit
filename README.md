# cmd-file-toolkit

> 企业级 C++17 命令行文件批量工具箱
> 练习目标：文件系统、字符串处理、STL容器、异常/错误处理、跨平台工程化、CMake构建、规范化编码

## 项目简介

**cmd-file-toolkit** 是一款基于 C++17 开发的跨平台命令行文件批量处理工具箱。 实现文件批量重命名、格式筛选转换、重复文件检测、MD5哈希校验、操作日志输出等功能。
项目面向 C++ 工程化实战练习，遵循现代C++规范，完整落地 CMake 构建、单元测试、静态代码检查、目录规范、异常安全、跨平台文件操作。

### 核心功能清单

1. **批量重命名**：前缀/后缀替换、序号自增重命名、正则匹配文件名替换
2. **文件筛选与格式转换**：按后缀过滤文件，支持简单文本编码转换占位扩展
3. **重复文件查找**：基于MD5哈希识别内容完全一致的重复文件
4. **MD5 校验工具**：单文件/目录批量计算MD5，生成校验清单
5. **运行日志系统**：控制台彩色日志 + 文件持久化日志，分级输出（DEBUG/INFO/WARN/ERROR）
6. **通用基础能力**：递归目录遍历、路径解析、命令行参数解析、统一异常处理

### 技术训练重点

- C++17 `std::filesystem` 跨平台目录、文件操作
- STL：`std::vector` / `std::unordered_map` / `std::string_view` / 容器算法
- 字符串处理、正则表达式 `std::regex`
- RAII、异常安全、错误码与异常双路径错误处理
- 命令行参数解析
- 哈希算法集成（MD5）
- CMake 现代工程组织、模块化拆分
- 跨平台兼容（Windows / Linux / macOS）

---

## 一、技术选型

### 基础标准

- **C++ 标准：C++17**
- 构建工具：CMake ≥ 3.18
- 编译器：
    - Windows: MSVC 2019+ / MinGW-w64
    - Linux: GCC9+
    - macOS: Clang 12+

### 依赖

#### 内置标准库（无第三方编译依赖）

1. `<filesystem>` 文件系统
2. `<fstream>` 文件读写
3. `<string> <string_view>` 字符串
4. `<vector> <unordered_map> <map>` 容器
5. `<regex>` 正则表达式
6. `<chrono>` 时间戳
7. `<stdexcept>` 标准异常

#### 内置第三方源码依赖（header-only，放入 `thirdparty/`）

> 不引入重型库，便于练习编译与源码集成

1. md5 哈希实现（单头文件 MD5 实现）
2. [cxxopts](https://github.com/jarro2783/cxxopts)：命令行参数解析（header-only）

> 原则：尽量减少动态库依赖，最终产物为 **静态链接可执行文件**，开箱即用。

### 禁止引入

- Boost、Qt、OpenCV等大型框架；专注标准C++基础能力训练

---

## 二、项目目录结构（企业规范）

```
cmd-file-toolkit/
├── .github/                # CI配置（可选拓展，持续集成）
├── cmake/                  # CMake工具链、公共模块
│   ├── CompilerOptions.cmake   # 编译选项、警告等级
│   ├── StaticAnalysis.cmake    # 静态检查配置 clang-tidy / cppcheck
│   └── UnitTest.cmake          # 单元测试封装宏
├── thirdparty/             # 头文件第三方库（header-only）
│   ├── cxxopts/
│   └── md5/
├── src/                    # 业务源码，核心模块
│   ├── main.cpp            # 程序入口，命令行分发
│   ├── fs/                 # 文件系统基础封装
│   │   ├── file_scanner.h   # 目录遍历、文件过滤
│   │   └── file_scanner.cpp
│   ├── logger/             # 日志模块
│   │   ├── logger.h
│   │   └── logger.cpp
│   ├── md5/                # MD5哈希封装
│   │   ├── md5_helper.h
│   │   └── md5_helper.cpp
│   ├── task/               # 各个业务任务实现
│   │   ├── rename_task.h    # 批量重命名
│   │   ├── duplicate_task.h # 查找重复文件
│   │   └── convert_task.h   # 文件格式处理
│   └── common/             # 通用工具、类型定义、错误码
│       ├── types.h
│       ├── error_code.h
│       └── string_util.cpp
├── tests/                  # 单元测试
│   ├── CMakeLists.txt
│   ├── test_string_util.cpp
│   ├── test_file_scanner.cpp
│   └── test_md5.cpp
├── assets/                 # 资源（测试用样本文件、模板）
├── build/                  # 编译输出目录（gitignore）
│   ├── dev-debug/
│   └── prod-release/
├── scripts/                # 辅助脚本：编译、格式化、运行测试
│   ├── build.sh
│   └── build.bat
├── .clang-format           # 代码格式化规范
├── .clang-tidy             # 静态代码检查规则
├── .gitignore              # git忽略文件
├── CMakeLists.txt          # 根CMake构建脚本
├── CMakePresets.json       # CMake预设（Debug/Release跨平台配置）
└── README.md               # 项目文档（本文件）
```

### 分层设计原则

1. **common**：底层工具函数，无业务依赖
2. **fs / logger / md5**：基础能力模块（基础设施层）
3. **task**：业务任务逻辑（应用层）
4. **cli**：命令行参数解析，调度不同任务
5. **main.cpp**：仅负责初始化 + 参数分发，禁止写复杂业务代码

> 目标：低耦合，模块单向依赖，便于单独编写单元测试。

---

## 三、构建系统：CMake 方案

### 构建模式

- 支持 **Out-of-source 外部构建**，所有产物统一放在 `build/`，源码目录保持干净
- 区分 `Debug / Release` 编译模式
- 支持：启用警告、地址消毒（ASAN）、静态分析开关

### CMake 主要能力规划

1. 设置 C++17 标准，禁止编译器扩展
2. 统一编译警告（高严格级别）
    - MSVC: `/W4`
    - GCC/Clang: `-Wall -Wextra -Wpedantic`
3. 可选开启 ASAN 内存检测（Debug模式）
4. 集成 `clang-tidy` 静态检查
5. 自动引入 thirdparty header-only 库
6. 封装单元测试目标（使用 GoogleTest）
7. 区分目标：主程序 `cmd-file-toolkit` + `unit_test` 测试程序

> 配套提供 `CMakePresets.json` 统一管理所有编译配置，避免手写复杂参数。

---

## 四、代码规范 & 静态检查

### 编码规范

1. 使用 `.clang-format` 统一格式化代码
    - 缩进：4空格
    - 命名规范：
        - 类名：大驼峰 `FileScanner`
        - 函数/变量：小驼峰 `scanDirectory()`
        - 常量/枚举：全大写下划线 `MAX_FILE_SIZE`
        - 头文件保护宏 `CMD_TOOLKIT_FS_FILE_SCANNER_H_`
2. 头文件原则：
    - 优先使用前置声明 `class X;`，减少`#include`
    - 头文件只放声明，实现放`.cpp`
    - 禁止头文件全局using namespace
3. 内存与异常规范
    - 优先智能指针 `std::unique_ptr`，尽量避免裸指针
    - 使用异常 + 错误码双层处理文件IO失败、权限不足、路径不存在
    - 文件操作保证RAII，自动关闭流

### 静态代码分析

启用两套检查：

1. **clang-tidy**：现代C++最佳实践检测（`.clang-tidy` 配置）
2. **cppcheck**：可选脚本一键扫描 禁止提交存在严重警告、内存风险代码。

### Git 提交规范

```
feat: 新增批量重命名任务
fix: 修复中文路径std::filesystem windows兼容问题
refactor: 抽离字符串工具函数
test: 增加MD5单元测试
docs: 更新README工程结构
```

---

## 五、测试方案
---

## 七、部署与输出产物

Release编译产出：

- Windows：`cmd-file-toolkit.exe`
- Linux/macOS：`cmd-file-toolkit`

产物为 **单一可执行程序**，无需额外动态库，可直接复制使用。 支持输出日志文件、md5校验清单文本，方便CI/脚本二次调用。

---

## 八、拓展路线（后续迭代方向）

> 基础版本完成后可选拓展练习

1. 支持异步并发扫描目录（std::thread / std::async）
2. 支持大文件分段MD5，优化超大文件性能
3. 增加文件删除、移动、复制批量操作
4. 导出JSON/CSV格式扫描报告
5. CI自动编译多平台二进制包
6. 增加交互式模式

## 九、快速上手步骤

本项目通过 `CMakePresets.json` 提供三套预设配置，覆盖开发、发布与 CI 场景。

### 通用前置步骤

```bash
# 1. 克隆并进入项目目录
git clone <repo-url> && cd cmd-file-toolkit
```

### 预设一：开发调试（dev-debug）

> Debug 构建，启用地址消毒器 (ASAN)、未定义行为消毒器 (USAN) 和单元测试。

```bash
# 2. 配置（使用 dev-debug 预设）
cmake --preset dev-debug

# 3. 编译（使用 dev-build 预设，4 并行任务）
cmake --build --preset dev-build

# 4. 运行程序
./build/dev-debug/cmd-file-toolkit --help

# 5. 运行单元测试（使用 dev-test 预设）
ctest --preset dev-test
```

### 预设二：生产发布（prod-release）

> Release 构建，`-O2 -DNDEBUG` 优化，关闭测试和消毒器。

```bash
# 2. 配置（使用 prod-release 预设）
cmake --preset prod-release

# 3. 编译（使用 prod-build 预设，4 并行任务）
cmake --build --preset prod-build

# 4. 运行程序
./build/prod-release/cmd-file-toolkit --help
```

### 预设三：CI 静态分析（ci-analysis）

> 继承 prod-release，额外开启单元测试和 cppcheck 静态检查。

```bash
# 2. 配置（使用 ci-analysis 预设）
cmake --preset ci-analysis

# 3. 编译
cmake --build build/ci-analysis

# 4. 运行单元测试
ctest --test-dir build/ci-analysis
```

### 构建产物速查

| 预设         | 构建目录              | 可执行文件路径                          |
|--------------|-----------------------|-----------------------------------------|
| dev-debug    | `build/dev-debug/`    | `./build/dev-debug/cmd-file-toolkit`    |
| prod-release | `build/prod-release/` | `./build/prod-release/cmd-file-toolkit` |
| ci-analysis  | `build/ci-analysis/`  | `./build/ci-analysis/cmd-file-toolkit`  |

