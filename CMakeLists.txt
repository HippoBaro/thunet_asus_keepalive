cmake_minimum_required(VERSION 3.11)
project(thunet_asus_keepalive CXX)

set(CMAKE_CXX_STANDARD 17)

option(STATIC_BIN "Compile to static binary" ON)
option(STRIP "Whether to strip the binary of unused symbols" ON)

add_subdirectory(tunet)

add_executable(thunet_asus_keepalive main.cpp)
target_link_libraries(thunet_asus_keepalive PRIVATE tunet)
if(STATIC_BIN)
    SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")
    list(REMOVE_ITEM CMAKE_CXX_IMPLICIT_LINK_LIBRARIES stdc++)
    target_link_libraries(thunet_asus_keepalive PRIVATE -static)
endif(STATIC_BIN)

target_compile_options(thunet_asus_keepalive PRIVATE
        -fno-exceptions
        -fno-rtti
        -Wall
        -Wextra
        -Os
        -s
        -fdata-sections
        -ffunction-sections
        -Wl,--gc-sections
        -fno-stack-protector
        -fomit-frame-pointer
        -fno-math-errno
        -fno-unroll-loops
        -fmerge-all-constants
        -fno-ident
        -fsingle-precision-constant
        -ffast-math
        -Wl,-z,norelro
        -Wl,--hash-style=gnu
        )

target_compile_definitions(thunet_asus_keepalive PRIVATE BOOST_NO_RTTI BOOST_NO_TYPEID BOOST_EXCEPTION_DISABLE BOOST_NO_EXCEPTIONS)

if (STRIP)
    add_custom_command(TARGET thunet_asus_keepalive POST_BUILD COMMAND
            $ENV{MIPSSTRIP} --strip-all $<TARGET_FILE:thunet_asus_keepalive>
            && upx -qq --ultra-brute $<TARGET_FILE:thunet_asus_keepalive>
            )
endif (STRIP)