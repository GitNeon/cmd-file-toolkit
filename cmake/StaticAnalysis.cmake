# ============================================================
#  StaticAnalysis.cmake – clang-tidy 静态代码检查
# ============================================================

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY
            ${CLANG_TIDY_EXE}
            -header-filter="${CMAKE_SOURCE_DIR}/src/.*"
            -checks="*,
                -fuchsia-*,
                -google-*,
                -llvm-*,
                -modernize-use-trailing-return-type,
                -readability-magic-numbers"
            -warnings-as-errors="*"
        )
        message(STATUS "clang-tidy: ENABLED (${CLANG_TIDY_EXE})")
    else()
        message(WARNING "ENABLE_CLANG_TIDY=ON but clang-tidy not found")
    endif()
endif()
