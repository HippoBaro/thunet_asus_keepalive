cmake_minimum_required(VERSION 3.11)
project(tunet CXX)

set(CMAKE_CXX_STANDARD 17)

option(STATIC_BIN "Compile to static binary" ON)

set(Boost_USE_STATIC_LIBS STATIC_BIN)
set(Boost_USE_STATIC_RUNTIME STATIC_BIN)
find_package(Boost 1.67 COMPONENTS system REQUIRED)
find_package(Threads)

if (STATIC_BIN)
    SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")
    list(REMOVE_ITEM CMAKE_CXX_IMPLICIT_LINK_LIBRARIES stdc++)
endif (STATIC_BIN)

add_library(tunet
        include/tunet.hpp
        src/json/gason.cpp
        src/payloads/challenge_response.cpp
        include/payloads/challenge_response.hpp
        src/payloads/login_request.cpp
        include/payloads/login_request.hpp
        src/crypto/hmac.hpp
        src/crypto/md5.hpp
        src/crypto/md5.cpp
        src/crypto/sha1.cpp
        src/crypto/sha1.hpp
        src/crypto/crypto_utils.cpp
        src/crypto/crypto_utils.hpp
        src/crypto/base64.cpp
        src/crypto/base64.hpp
        src/crypto/charset.cpp
        src/crypto/charset.hpp
        src/keepalive.cpp
        include/error_code.hpp
        src/errr_code.cpp
        src/payloads/challenge_request.cpp
        include/payloads/challenge_request.hpp
        src/payloads/login_response.cpp
        include/payloads/login_response.hpp
        src/json_object.cpp
        include/json_object.hpp src/payloads/status_response.cpp include/payloads/status_response.hpp)

target_include_directories(tunet
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

target_compile_options(tunet PRIVATE
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

target_compile_definitions(tunet PUBLIC BOOST_NO_RTTI BOOST_NO_TYPEID BOOST_EXCEPTION_DISABLE BOOST_NO_EXCEPTIONS)

target_link_libraries(tunet PUBLIC Boost::system)

if(STATIC_BIN)
    target_compile_options(tunet PRIVATE -Wl,--gc-sections)
    target_link_libraries(tunet PRIVATE -static)
endif(STATIC_BIN)

if (STRIP)
    add_custom_command(TARGET tunet POST_BUILD COMMAND
            $ENV{MIPSSTRIP} --strip-unneeded $<TARGET_FILE:tunet>
            )
endif (STRIP)


