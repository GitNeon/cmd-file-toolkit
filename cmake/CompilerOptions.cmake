# ============================================================
#  CompilerOptions.cmake – 编译选项与警告等级
# ============================================================

# --- C++17 标准，禁止编译器扩展 ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- 跨平台统一输出目录 ---
# 所有编译产物放在 build/<config>/ 下，保持源码目录干净
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --- MSVC 配置 ---
add_compile_options(
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4             # 高严格警告
        /utf-8          # 源/执行字符集 UTF-8
        /EHsc           # 启用 C++ 异常
        /Zc:__cplusplus # 正确报告 C++ 标准版本宏
    >
)

# --- GCC / Clang 配置 ---
add_compile_options(
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wconversion
        -Wsign-conversion
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2
    >
)

# --- AddressSanitizer (仅 Debug) ---
if(ENABLE_ASAN AND CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_options(
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-fsanitize=address -fno-omit-frame-pointer>
        $<$<CXX_COMPILER_ID:MSVC>:/fsanitize=address>
    )
    add_link_options(
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-fsanitize=address>
    )
    message(STATUS "AddressSanitizer: ENABLED")
endif()

# --- 导出编译指令（供 IDE 使用） ---
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
