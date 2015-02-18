#!/bin/bash
# if you want to cross compile it for windows,
# you will have to type following lines
# maybe with some changes for your specific paths

  export LDFLAGS='-static'
  export LIBS='-lstdc++ -liconv'
  export CXXFLAGS=''
  export CFLAGS=''
./configure --host=i686-w64-mingw32 --target=i686-w64-mingw32 --prefix=/usr/i686-w64-mingw32 --libdir=/usr/i686-w64-mingw32/lib --includedir=/usr/i686-w64-mingw32/include --disable-shared --enable-static --disable-tests
#  ./configure --host=i486-mingw32 --build=i686-linux --prefix=/usr/i486-mingw32
  make
