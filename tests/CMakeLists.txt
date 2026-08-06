cmake_minimum_required(VERSION 3.16)
project(Softloq-UTF-8-Tests VERSION 1.0.0 LANGUAGES CXX)

include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCE_FILES "*.cpp")

add_executable(softloq-utf-8-tests ${TEST_SOURCE_FILES})

target_link_libraries(softloq-utf-8-tests
    PRIVATE
        GTest::gtest_main
        softloq-utf-8
)

if(NOT SOFTLOQ_UTF_8_BUILD_STATIC)
    target_compile_definitions(softloq-utf-8-tests PRIVATE SOFTLOQ_UTF_8_IMPORTS)
endif()

include(GoogleTest)
gtest_discover_tests(softloq-utf-8-tests)
