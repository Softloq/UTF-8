cmake_minimum_required(VERSION 3.16)
project(Softloq-UTF-8 VERSION 1.0.0 LANGUAGES CXX)

# ==============================================================================
# Option Flags
# ==============================================================================
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CMakeOptions)

# ==============================================================================
# Configurations
# ==============================================================================
include(CMakeConfigs)

# ==============================================================================
# Libraries
# ==============================================================================
if(SOFTLOQ_UTF_8_BUILD_STATIC)
    set(LIBRARY_BUILD_TYPE STATIC)
else()
    set(LIBRARY_BUILD_TYPE SHARED)
endif()

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.c")

add_library(softloq-utf-8 ${LIBRARY_BUILD_TYPE} ${SOURCE_FILES})
add_library(Softloq::UTF-8 ALIAS softloq-utf-8)

target_include_directories(softloq-utf-8 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_precompile_headers(softloq-utf-8 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/softloq/utf-8/pch/pch.hpp")

if(SOFTLOQ_UTF_8_BUILD_STATIC)
    target_compile_definitions(softloq-utf-8 PUBLIC SOFTLOQ_UTF_8_STATIC)
else()
    target_compile_definitions(softloq-utf-8 PRIVATE SOFTLOQ_UTF_8_EXPORTS)
    target_compile_definitions(softloq-utf-8 INTERFACE_COMPILE_OPTIONS SOFTLOQ_UTF_8_IMPORTS)
    set_target_properties(softloq-utf-8 PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
    )
endif()

target_compile_definitions(softloq-utf-8 PRIVATE
    $<$<CONFIG:Debug>:SOFTLOQ_UTF_8_BUILD_DEBUG=1>
    $<$<CONFIG:Devel>:SOFTLOQ_UTF_8_BUILD_DEVEL=1>
    $<$<CONFIG:Release>:SOFTLOQ_UTF_8_BUILD_RELEASE=1>
)

# ==============================================================================
# Tests
# ==============================================================================
if(SOFTLOQ_UTF_8_BUILD_TESTING)
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
    add_subdirectory(docs)
endif()
