#!/bin/bash
# if you want to cross compile it for windows,
# you will have to type following lines
# maybe with some changes for your specific paths

  LDFLAGS=''
  CXXFLAGS=''
  CFLAGS=''
  ./configure --host=i486-mingw32 --build=i686-linux --prefix=/usr/i486-mingw32
  make check
