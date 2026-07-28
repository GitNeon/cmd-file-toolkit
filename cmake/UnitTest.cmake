# ============================================================
#  UnitTest.cmake – GoogleTest 集成
# ============================================================

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
    GIT_SHALLOW    TRUE
)

# 避免 GoogleTest 安装到系统
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# 启用 CTest
enable_testing()
include(GoogleTest)

# 封装函数：快速添加单元测试
#   用法: add_unit_test(test_name source1.cpp source2.cpp ...)
function(add_unit_test TEST_NAME)
    add_executable(${TEST_NAME} ${ARGN})
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
    target_link_libraries(${TEST_NAME} PRIVATE
        GTest::gtest_main
        GTest::gmock_main
        # 按需链接业务库，示例:
        # toolkit_common
    )
    gtest_discover_tests(${TEST_NAME}
        DISCOVERY_TIMEOUT 30
    )
endfunction()
