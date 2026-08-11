# 统一编译器警告配置
if (MSVC)
    add_compile_options(/W4)          # 最高等级警告, MSVC 推荐使用的警告级别（Level 4）
    add_compile_options(/utf-8)       # 将编译器的源码字符集和执行字符集都设置为 UTF-8
    add_compile_options(/wd4251)      # 屏蔽部分STL导出警告（可选）
else ()
    # GCC / Clang
    add_compile_options(-Wall -Wextra -Wpedantic) # -Wall开启编译器开发者认为“最常用/最重要”的警告 -Wextra: 开启 -Wall 没有包含的额外警告
    # -Wpedantic: 严格要求代码符合 ISO C/C++ 标准标准，如果有编译器扩展语法（如 GCC 特有的语法）会报警告。这有助于保证代码的可移植性
    add_compile_options(-Wconversion) # 开启隐式类型转换的警告
endif ()

# Address Sanitizer 内存检测开关 (Debug模式启用)
# 这部分代码用于在开发调试阶段检测内存错误（如越界访问、内存泄漏等）
# 如果你想启用 ASAN 进行调试，在构建项目时需要加上参数：cmake -B build -DENABLE_ASAN=ON

# 定义了一个名为 ENABLE_ASAN 的选项，默认是 OFF（关闭）
option(ENABLE_ASAN "Enable address sanitizer" OFF)

# 只有在开启了 ASAN 且 不是 使用 MSVC 编译器时才执行
if (ENABLE_ASAN AND NOT MSVC)
    if (MINGW)
        message(WARNING "AddressSanitizer is not supported on MinGW, skipping ENABLE_ASAN")
    else ()
        message(STATUS "Enable Address Sanitizer")
        add_compile_options(-fsanitize=address -g)
        add_link_options(-fsanitize=address)
    endif ()
endif ()