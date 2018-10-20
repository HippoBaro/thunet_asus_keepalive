FROM alpine:3.8
MAINTAINER Hippolyte Barraud "hippolyte.barraud@gmail.com"

ENV TARGET=mipsel-linux-muslsf
ENV MIPSCXX=/musl-cross-make/output/bin/mipsel-linux-muslsf-g++
ENV MIPSCC=/musl-cross-make/output/bin/mipsel-linux-muslsf-gcc
ENV MIPSSTRIP=/musl-cross-make/output/bin/mipsel-linux-muslsf-strip

# Install basic build dependency and utils
# Install LibC compat for CMake
# Install cross-compiler toolchain
# Install CMake 12 (needed for Boost 1.67)
# Build and install cross-compiled Boost
# Clean everything and keep only cross-compiler toolchain, Boost and CMake.

RUN apk --update add --virtual build-dependencies \
        alpine-sdk \
        xz \
        wget \
        automake \
        autoconf \
        git \
        libtool \
        perl \
&& \
        apk add cmake ninja upx \
&& \
        git clone https://github.com/richfelker/musl-cross-make.git && \
        cd musl-cross-make && \
        make install && \
        cd .. && \
        find ./musl-cross-make -mindepth 1 -name output -prune -o -exec rm -rf {} \; ; echo done \
&& \
        mkdir /src && \
        cd /src \
&& \
        wget https://dl.bintray.com/boostorg/release/1.67.0/source/boost_1_67_0.tar.bz2 -q && \
        tar --bzip2 -xf boost_1_67_0.tar.bz2 && \
        cd boost_1_67_0 && \
        ./bootstrap.sh && \
        echo "using gcc : : $MIPSCXX ;"  >> tools/build/src/user-config.jam && \
        ./b2 link=static runtime-link=static variant=release optimization=space --with-system --prefix=/boost install \
&& \
        cd /src && \
        wget http://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.4.10.tar.gz && \
        tar zxvf linux-4.4.10.tar.gz && \
        cp -r linux-4.4.10/include/linux /usr/include/linux \
&& \
        cd /src && \
        git clone https://github.com/libressl-portable/portable.git && \
        cd portable && \
        ./autogen.sh && \
        mkdir build-ninja && \
        cd build-ninja && \
        cmake -DCMAKE_C_COMPILER=$MIPSCC -DLIBRESSL_APPS=OFF -DLIBRESSL_TESTS=OFF -DENABLE_ASM=OFF -G"Ninja" .. && \
        ninja install \
&& \
        cd / && rm -rf /src &&\
        apk del build-dependencies && \
        rm -rf /var/cache/apk/*

ENV BOOST_ROOT /boost
ENV CXX=/musl-cross-make/output/bin/mipsel-linux-muslsf-g++
ENV CC=/musl-cross-make/output/bin/mipsel-linux-muslsf-gcc

WORKDIR /home