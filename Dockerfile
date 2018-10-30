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
        apt-get install -y unzip wget bzip2 cmake ninja-build upx perl \
&& \
        mkdir /src \
&& \
        cd /src && \
        wget "https://toolchains.bootlin.com/downloads/releases/toolchains/mips32el/tarballs/mips32el--uclibc--stable-2018.02-2.tar.bz2" && \
        tar -jxf mips32el--uclibc--stable-2018.02-2.tar.bz2 && \
        cd mips32el--uclibc--stable-2018.02-2 && \
        mkdir /mipsel-linux-uclibc && \
        cp -r * /mipsel-linux-uclibc \
&& \
        cd /src && \
        wget "https://github.com/openssl/openssl/archive/OpenSSL_1_0_2p.zip" && \
        unzip OpenSSL_1_0_2p.zip && \
        cd openssl-OpenSSL_1_0_2p && \
        PATH=/mipsel-linux-uclibc/bin:$PATH ./Configure linux-mips32 no-asm \
            -fdata-sections -ffunction-sections \
            -Wl,--gc-sections \
            -fno-stack-protector \
            -fomit-frame-pointer \
            -fno-math-errno \
            -fno-unroll-loops \
            -fmerge-all-constants \
            -fno-ident \
            -fsingle-precision-constant \
            -ffast-math \
            -Wl,-z,norelro \
            -Wl,--hash-style=gnu --cross-compile-prefix='mipsel-linux-' -Os -s  && \
        PATH=/mipsel-linux-uclibc/bin:$PATH make CC=$MIPSCC && \
        PATH=/mipsel-linux-uclibc/bin:$PATH make install \
&& \
        cd /src && \
        wget https://dl.bintray.com/boostorg/release/1.67.0/source/boost_1_67_0.tar.bz2 && \
        tar --bzip2 -xf boost_1_67_0.tar.bz2 && \
        cd boost_1_67_0 && \
        ./bootstrap.sh && \
        echo "using gcc : : $MIPSCXX ;"  >> tools/build/src/user-config.jam && \
        ./b2 link=static runtime-link=static variant=release optimization=space --with-system --prefix=/boost install \
&& \
        apt-get remove -y cmake && \
        apt-get purge --auto-remove -y cmake \
&& \
        cd /src &&\
        wget "https://cmake.org/files/v3.12/cmake-3.12.3-Linux-x86_64.sh" && \
        chmod +x cmake-3.12.3-Linux-x86_64.sh && \
        ./cmake-3.12.3-Linux-x86_64.sh --skip-license --exclude-subdir --prefix=/usr/local \
&& \
        cd / && rm -rf /src \
&& \
        apt-get remove -y perl unzip wget bzip2 && \
        apt-get purge --auto-remove -y perl unzip wget bzip2

ENV BOOST_ROOT /boost
ENV CXX=/mipsel-linux-uclibc/bin/mipsel-linux-g++
ENV CC=/mipsel-linux-uclibc/bin/mipsel-linux-gcc

WORKDIR /home