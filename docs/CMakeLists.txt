cmake_minimum_required(VERSION 3.16)
project(Softloq-UTF-8-Docs VERSION 1.0.0 LANGUAGES CXX)

find_package(Doxygen REQUIRED)

set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_LATEX NO)
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(DOXYGEN_FILE_PATTERNS "*.h" "*.hpp" "*.dox")
set(DOXYGEN_STRIP_FROM_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../include")

doxygen_add_docs(docs
    "${CMAKE_CURRENT_SOURCE_DIR}/doxs"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
    COMMENT "Generating Softloq UTF-8 documentation from docs/doxs and include"
)
