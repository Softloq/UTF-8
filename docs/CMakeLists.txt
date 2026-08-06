cmake_minimum_required(VERSION 3.16)
project(Softloq-UTF-8-Docs VERSION 1.0.0 LANGUAGES CXX)

find_package(Doxygen REQUIRED)

set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_LATEX NO)