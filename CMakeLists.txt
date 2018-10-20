cmake_minimum_required(VERSION 3.11)
project(thunet_asus_keepalive CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(CMAKE_CXX_STANDARD 17)

option(STATIC_BIN "Compile to static binary" ON)
option(STRIP "Whether to strip the binary of unused symbols" ON)

find_package(Boost 1.67 COMPONENTS system REQUIRED)
add_subdirectory(tunet)

add_executable(thunet_asus_keepalive
        main.cpp
        src/periodic_task.cpp
        src/periodic_task.hpp
        src/periodic_scheduler.cpp
        src/periodic_scheduler.hpp
        src/keepalive_task.cpp
        src/keepalive_task.hpp
        src/user_settings.cpp
        src/user_settings.hpp
        src/logger.cpp
        src/logger.hpp)

target_include_directories(thunet_asus_keepalive PRIVATE src)

target_link_libraries(thunet_asus_keepalive PRIVATE tunet Boost::system)
if(STATIC_BIN)
    SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")
    list(REMOVE_ITEM CMAKE_CXX_IMPLICIT_LINK_LIBRARIES stdc++)
    target_link_libraries(thunet_asus_keepalive PRIVATE -static)
endif(STATIC_BIN)

target_compile_options(thunet_asus_keepalive PRIVATE
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