FROM debian:latest
MAINTAINER Hippolyte Barraud "hippolyte.barraud@gmail.com"

ENV TARGET=mipsel-linux-muslsf
ENV MIPSCXX=/mipsel-linux-uclibc/bin/mipsel-linux-g++
ENV MIPSCC=/mipsel-linux-uclibc/bin/mipsel-linux-gcc
ENV MIPSSTRIP=/mipsel-linux-uclibc/bin/mipsel-linux-strip

# Install basic build dependency and utils
# Install LibC compat for CMake
# Install cross-compiler toolchain
# Install CMake 12 (needed for Boost 1.67)
# Build and install cross-compiled Boost
# Clean everything and keep only cross-compiler toolchain, Boost and CMake.

RUN     apt-get update \
&& \
        apt-get install wget bzip2 cmake ninja upx \
&& \
        mkdir /src \
&& \
        cd /src && \
        wget "https://toolchains.bootlin.com/downloads/releases/toolchains/mips32el/tarballs/mips32el--uclibc--stable-2018.02-2.tar.bz2" && \
        tar -jxf mips32el--uclibc--stable-2018.02-1.tar.bz2 && \
        cd mips32el--uclibc--stable-2018.02-1 && \
        mkdir /mipsel-linux-uclibc && \
        cp -r * /mipsel-linux-uclibc \
&& \
        cd /src && \
        wget https://dl.bintray.com/boostorg/release/1.67.0/source/boost_1_67_0.tar.bz2 -q && \
        tar --bzip2 -xf boost_1_67_0.tar.bz2 && \
        cd boost_1_67_0 && \
        ./bootstrap.sh && \
        echo "using gcc : : $MIPSCXX ;"  >> tools/build/src/user-config.jam && \
        ./b2 link=static runtime-link=static variant=release optimization=space --with-system --prefix=/boost install \
&& \
        cd /src && \
        wget -q "https://github.com/openssl/openssl/archive/OpenSSL_1_0_2p.zip" && \
        unzip OpenSSL_1_0_2p.zip && \
        cd openssl-OpenSSL_1_0_2p && \
        PATH=/mipsel-linux-uclibc/bin:$PATH ./Configure linux-mips32 no-asm shared --cross-compile-prefix='mipsel-linux-muslsf-' && \
        PATH=/mipsel-linux-uclibc/bin:$PATH make CC=/mipsel-linux-uclibc/bin/mipsel-linux-muslsf-gcc && \
        PATH=/mipsel-linux-uclibc/bin:$PATH make install \
&& \
        cd / && rm -rf /src && \
        apk del build-dependencies && \
        rm -rf /var/cache/apk/*

ENV BOOST_ROOT /boost
ENV CXX=/mipsel-linux-uclibc/bin/mipsel-linux-g++
ENV CC=/mipsel-linux-uclibc/bin/mipsel-linux-gcc

WORKDIR /home