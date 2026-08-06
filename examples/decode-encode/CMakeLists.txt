add_executable(softloq-utf-8-decode-encode decode-encode.cpp)

target_link_libraries(softloq-utf-8-decode-encode PRIVATE softloq-utf-8)

if(NOT SOFTLOQ_UTF_8_BUILD_STATIC)
    target_compile_definitions(softloq-utf-8-decode-encode PRIVATE SOFTLOQ_UTF_8_IMPORTS)
endif()
