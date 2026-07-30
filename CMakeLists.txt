# ============================================================
#  cmd-file-toolkit - 命令行文件批量工具箱
#  C++17 / CMake >= 3.18 / 跨平台
# ============================================================
cmake_minimum_required(VERSION 3.18)
project(cmd-file-toolkit
        VERSION 1.0.0
        DESCRIPTION "Enterprise C++17 CLI file batch processing toolkit"
        LANGUAGES CXX
)

# C++标准配置
# 在 GCC/Clang 中，这通常会转化为添加编译选项 -std=c++17；在 MSVC 中，会设置为 /std:c++17
set(CMAKE_CXX_STANDARD 17)
# 必须使用C++ 17标准构建，否则报错阻止构建
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 禁止使用编译器私有的、非标准的语言特性，确保可移植性
set(CMAKE_CXX_EXTENSIONS OFF)

# 引入通用编译选项
include(${PROJECT_SOURCE_DIR}/cmake/CompilerOptions.cmake)
# 静态分析（可选，按需开启）
include(${PROJECT_SOURCE_DIR}/cmake/StaticAnalysis.cmake)

# 全局头文件搜索路径
include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/thirdparty
)

# 自定义选项
option(BUILD_TESTS "Build tests" OFF)
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)

# 收集源代码
file(GLOB_RECURSE SRC_SOURCES
        src/main.cpp
        src/common/*.cpp
        src/ui/*.cpp
        src/fs/*.cpp
        src/logger/*.cpp
        src/md5/*.cpp
        src/task/*.cpp
)

# 收集文件头
file(GLOB_RECURSE SRC_HEADERS
        src/common/*.h
        src/ui/*.h
        src/fs/*.h
        src/logger/*.h
        src/md5/*.h
        src/task/*.h
)

# ============================================================
# 构建信息输出
# ============================================================
message(STATUS "")
message(STATUS "========== Project: ${PROJECT_NAME} v${PROJECT_VERSION} ==========")
message(STATUS "Description  : ${PROJECT_DESCRIPTION}")
message(STATUS "C++ Standard : C++${CMAKE_CXX_STANDARD} (required=${CMAKE_CXX_STANDARD_REQUIRED})")

message(STATUS "---------- Platform / Compiler ----------")
message(STATUS "System       : ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "Generator    : ${CMAKE_GENERATOR}")
message(STATUS "Compiler     : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build Type   : ${CMAKE_BUILD_TYPE}")

message(STATUS "---------- Directories ----------")
message(STATUS "Source Dir   : ${PROJECT_SOURCE_DIR}")
message(STATUS "Binary Dir   : ${PROJECT_BINARY_DIR}")

message(STATUS "---------- Options ----------")
message(STATUS "BUILD_TESTS  : ${BUILD_TESTS}")
message(STATUS "ENABLE_ASAN  : ${ENABLE_ASAN}")

list(LENGTH SRC_SOURCES SRC_COUNT)
list(LENGTH SRC_HEADERS HDR_COUNT)
message(STATUS "---------- Sources ----------")
message(STATUS "Source files : ${SRC_COUNT}")
message(STATUS "Header files : ${HDR_COUNT}")
message(STATUS "============================================================")
message(STATUS "")

# 生成可执行主程序
add_executable(${PROJECT_NAME} ${SRC_SOURCES} ${SRC_HEADERS})
