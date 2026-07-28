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

# -------------------- 全局选项 --------------------
option(BUILD_TESTS  "Build unit tests (requires GoogleTest)"  ON)
option(ENABLE_ASAN  "Enable AddressSanitizer (Debug only)"     OFF)
option(ENABLE_CLANG_TIDY "Enable clang-tidy static analysis"   OFF)