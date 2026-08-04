cmake_minimum_required(VERSION 3.16)
project(Softloq-UTF-8 VERSION 1.0.0 LANGUAGES CXX)

include(cmake/CMakeOptions.cmake)
include(cmake/CMakeConfigs.cmake)

# ==============================================================================
# Build Library
# ==============================================================================
if(SOFTLOQ_UTF_8_BUILD_STATIC)
    set(LIBRARY_BUILD_TYPE STATIC)
else()
    set(LIBRARY_BUILD_TYPE SHARED)
endif()

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.c")

add_library(softloq-utf-8 ${LIBRARY_BUILD_TYPE} ${SOURCE_FILES})

target_include_directories(softloq-utf-8 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# ==============================================================================
# Tests
# ==============================================================================
if(SOFTLOQ_UTF_8_BUILD_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

# ==============================================================================
# Examples
# ==============================================================================
if(SOFTLOQ_UTF_8_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# ==============================================================================
# Documentation
# ==============================================================================
if(SOFTLOQ_UTF_8_BUILD_DOCS)
    find_package(Doxygen REQUIRED)

    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_LATEX NO)
endif()

# ==============================================================================
# Benchmarks
# ==============================================================================
if(SOFTLOQ_UTF_8_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()
