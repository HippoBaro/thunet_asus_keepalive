docker run -v `pwd`:/home --tty --rm hippobaro/asuswrt-musl-crosscompile:latest sh -c "mkdir build ; cd build && cmake -DOPENSSL_ROOT_DIR=/usr/local/ssl/ -DCMAKE_TOOLCHAIN_FILE=../ASUS-RT-AC51U-toolchain.cmake -DSTRIP=ON -GNinja .. && ninja"