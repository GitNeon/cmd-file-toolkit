# ============================================================
#  QuickDigest5 - 轻量级 MD5 哈希计算库
#  作为 cmd-file-toolkit 的第三方静态库引入
#  原始仓库: https://github.com/nthnn/QuickDigest5
#  许可协议: GPL-3.0
# ============================================================
cmake_minimum_required(VERSION 3.24)
project(QuickDigest5
        VERSION 1.0.0
        DESCRIPTION "QuickDigest5 is a lightweight C++ library for computing MD5 hashes of strings and files."
        LANGUAGES CXX
)

# -------------------------------------------
# 静态库目标
# -------------------------------------------
# 将头文件一并加入源列表，使其在 IDE（Visual Studio / CLion）的文件树中可见
add_library(QuickDigest5 STATIC
        include/quickdigest5.hpp
        src/quickdigest5.cpp
)

# -------------------------------------------
# 头文件搜索路径
# -------------------------------------------
# PUBLIC 意味着任何链接 QuickDigest5 的目标都会自动继承此路径
target_include_directories(QuickDigest5
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# -------------------------------------------
# C++ 标准要求
# -------------------------------------------
# 使用 target 级别设置，避免 set(CMAKE_CXX_STANDARD ...) 向上污染父作用域
# PUBLIC 确保使用者（如主程序）也会按 C++17 编译要求构建
target_compile_features(QuickDigest5 PUBLIC cxx_std_17)

# 补充设置：严格遵循标准，禁止编译器私有扩展
set_target_properties(QuickDigest5 PROPERTIES
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

# -------------------------------------------
# 示例程序（可选编译，由顶层 BUILD_EXAMPLES 选项控制）
# -------------------------------------------
if (BUILD_EXAMPLES)
    add_executable(QuickDigest5Example
            examples/simple_example.cpp
    )
    target_link_libraries(QuickDigest5Example PRIVATE QuickDigest5)
endif ()