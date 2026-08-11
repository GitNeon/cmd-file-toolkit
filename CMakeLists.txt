# ============================================================
#  cmd-file-toolkit - 命令行文件批量工具箱
#  C++17 / CMake >= 3.24 / 跨平台
# ============================================================
cmake_minimum_required(VERSION 3.24)
project(cmd-file-toolkit
        VERSION 1.0.0
        DESCRIPTION "Enterprise C++17 CLI file batch processing toolkit"
        LANGUAGES CXX
)

# -------------------------------------------
# C++ 标准配置
# -------------------------------------------
# 在 GCC/Clang 中，这通常会转化为添加编译选项 -std=c++17；
# 在 MSVC 中，会设置为 /std:c++17
set(CMAKE_CXX_STANDARD 17)
# 必须使用 C++17 标准构建，否则报错阻止构建
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 禁止使用编译器私有的、非标准的语言特性，确保可移植性
set(CMAKE_CXX_EXTENSIONS OFF)

# 为 clangd 等语言服务器生成 compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------------------------------
# 引入通用编译选项
# -------------------------------------------
include(${PROJECT_SOURCE_DIR}/cmake/CompilerOptions.cmake)
# 静态分析（可选，按需开启）
include(${PROJECT_SOURCE_DIR}/cmake/StaticAnalysis.cmake)

# -------------------------------------------
# 自定义构建选项
# -------------------------------------------
option(BUILD_TESTS "Build tests" OFF)
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)
option(BUILD_EXAMPLES "Build third-party library examples" OFF)

# -------------------------------------------
# 收集本项目的源代码
# -------------------------------------------
file(GLOB SRC_SOURCES
        src/main.cpp
        src/common/*.cpp
        src/fs/*.cpp
        src/logger/*.cpp
        src/md5/*.cpp
        src/task/*.cpp
        src/ui/*.cpp
)

file(GLOB SRC_HEADERS
        src/common/*.h
        src/fs/*.h
        src/logger/*.h
        src/md5/*.h
        src/task/*.h
        src/ui/*.h
)

list(LENGTH SRC_SOURCES SRC_COUNT)
list(LENGTH SRC_HEADERS HDR_COUNT)

# ============================================================
# 构建信息输出
# ============================================================
message(STATUS "")
message(STATUS "========== Project: ${PROJECT_NAME} v${PROJECT_VERSION} ==========")
message(STATUS "Description   : ${PROJECT_DESCRIPTION}")
message(STATUS "C++ Standard  : C++${CMAKE_CXX_STANDARD} (required=${CMAKE_CXX_STANDARD_REQUIRED})")

message(STATUS "---------- Platform / Compiler ----------")
message(STATUS "System        : ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "Generator     : ${CMAKE_GENERATOR}")
message(STATUS "Compiler      : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build Type    : ${CMAKE_BUILD_TYPE}")

message(STATUS "---------- Directories ----------")
message(STATUS "Source Dir    : ${PROJECT_SOURCE_DIR}")
message(STATUS "Binary Dir    : ${PROJECT_BINARY_DIR}")

message(STATUS "---------- Options ----------")
message(STATUS "BUILD_TESTS   : ${BUILD_TESTS}")
message(STATUS "ENABLE_ASAN   : ${ENABLE_ASAN}")
message(STATUS "BUILD_EXAMPLES: ${BUILD_EXAMPLES}")

message(STATUS "---------- Sources ----------")
message(STATUS "Source files  : ${SRC_COUNT}")
message(STATUS "Header files  : ${HDR_COUNT}")
message(STATUS "============================================================")
message(STATUS "")

# -------------------------------------------
# 第三方库：QuickDigest5（MD5 哈希计算）
# -------------------------------------------
add_subdirectory(thirdparty/QuickDigest5)

# -------------------------------------------
# 生成可执行主程序
# -------------------------------------------
add_executable(${PROJECT_NAME} ${SRC_SOURCES} ${SRC_HEADERS})

# 为主程序添加头文件搜索路径（推荐 target_ 级别命令替代全局 include_directories）
target_include_directories(${PROJECT_NAME} PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        # thirdparty 预留给今后可能添加的纯头文件第三方库（QuickDigest5 已通过
        # target_link_libraries 自动引入了其 PUBLIC 的 include 路径，无需重复）
        ${PROJECT_SOURCE_DIR}/thirdparty
)

# 链接第三方库
target_link_libraries(${PROJECT_NAME} PRIVATE
        QuickDigest5
)

# MSVC 额外设置：添加 /utf-8 确保源码和执行字符集一致（中文路径/输出兼容）
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif ()
