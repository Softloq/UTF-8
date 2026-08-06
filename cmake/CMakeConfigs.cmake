include_guard(GLOBAL)

# ==============================================================================
# C++ Standard
# ==============================================================================
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ==============================================================================
# Build-Type Handling (Debug / Devel / Release)
# ==============================================================================
if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Devel;Release" CACHE STRING "Available build configurations" FORCE)
else()
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
    endif()
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Devel Release)
endif()

# Devel mirrors an optimized build that keeps debug information, similar to RelWithDebInfo.
set(CMAKE_CXX_FLAGS_DEVEL "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}" CACHE STRING "C++ flags for the Devel configuration")
set(CMAKE_EXE_LINKER_FLAGS_DEVEL "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}" CACHE STRING "Executable linker flags for the Devel configuration")
set(CMAKE_SHARED_LINKER_FLAGS_DEVEL "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO}" CACHE STRING "Shared library linker flags for the Devel configuration")
mark_as_advanced(CMAKE_CXX_FLAGS_DEVEL CMAKE_EXE_LINKER_FLAGS_DEVEL CMAKE_SHARED_LINKER_FLAGS_DEVEL)

# ==============================================================================
# Output Directories
# ==============================================================================
set(PROJECT_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}")

foreach(SOFTLOQ_UTF_8_OUTPUT_CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER "${SOFTLOQ_UTF_8_OUTPUT_CONFIG}" SOFTLOQ_UTF_8_OUTPUT_CONFIG_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${SOFTLOQ_UTF_8_OUTPUT_CONFIG_UPPER} "${PROJECT_OUTPUT_DIRECTORY}/${SOFTLOQ_UTF_8_OUTPUT_CONFIG}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${SOFTLOQ_UTF_8_OUTPUT_CONFIG_UPPER} "${PROJECT_OUTPUT_DIRECTORY}/${SOFTLOQ_UTF_8_OUTPUT_CONFIG}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${SOFTLOQ_UTF_8_OUTPUT_CONFIG_UPPER} "${PROJECT_OUTPUT_DIRECTORY}/${SOFTLOQ_UTF_8_OUTPUT_CONFIG}")
endforeach()
unset(SOFTLOQ_UTF_8_OUTPUT_CONFIG)
unset(SOFTLOQ_UTF_8_OUTPUT_CONFIG_UPPER)

# ==============================================================================
# Platform & Compiler Detection
# ==============================================================================
if(WIN32)
    set(SOFTLOQ_UTF_8_PLATFORM_WINDOWS ON)
elseif(APPLE)
    set(SOFTLOQ_UTF_8_PLATFORM_MACOS ON)
elseif(UNIX)
    set(SOFTLOQ_UTF_8_PLATFORM_LINUX ON)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(SOFTLOQ_UTF_8_COMPILER_MSVC ON)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(SOFTLOQ_UTF_8_COMPILER_CLANG ON)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(SOFTLOQ_UTF_8_COMPILER_GCC ON)
endif()
