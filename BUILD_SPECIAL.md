### Build for windows on linux

Assuming the host platform is "arch linux".

install from [AUR](https://aur.archlinux.org/):
1. mingw-w64-gcc-base
2. mingw-w64-gcc
3. mingw-w64-libiconv

After that you will have following tool chains available:

- /usr/i686-w64-mingw32
- /usr/x86_64-w64-mingw32


    git checkout https://github.com/ferkulat/csv2xls.git
    cd csv2xls
    mkdir build
    cd build
    cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/modules/Toolchain-mingw.cmake ..
    cmake --build .

This builds with tool chain 'i686-w64-mingw32'. If you want to build with another tool chain, you need to change it in file 'Toolchain-mingw.cmake'