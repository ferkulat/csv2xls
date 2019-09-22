master: [![Build Status](https://travis-ci.org/ferkulat/csv2xls.svg?branch=master)](https://travis-ci.org/ferkulat/csv2xls)
[![Build status](https://ci.appveyor.com/api/projects/status/github/ferkulat/csv2xls?brach=master&svg=true)](https://ci.appveyor.com/project/ferkulat/csv2xls)

devel: [![Build Status](https://travis-ci.org/ferkulat/csv2xls.svg?branch=devel)](https://travis-ci.org/ferkulat/csv2xls)
[![Build status](https://ci.appveyor.com/api/projects/status/github/ferkulat/csv2xls?brach=devel&svg=true)](https://ci.appveyor.com/project/ferkulat/csv2xls)


# csv2xls
### Description 

csv2xls (csv to xls) is a command line utility which converts csv files into one
(or more if maximum rows are exceeded) Excel(TM) file(s).

 ### Features

- split output in several files, if max line limit exceeded
- set work sheet name of xls output file
- noninteractive -> useful for automated tasks

### Limitations

- produces only Excel(TM) 97/2000/XP/2003 files
- no cell formatting, just plain text

### Prerequisites

- libiconv:   http://ftp.gnu.org/pub/gnu/libiconv/ (Optional to get UTF-8 support)
- compiler: gcc8, clang6, msvc2019
- cmake-3.14

### Building
    git checkout https://github.com/ferkulat/csv2xls.git
    cd csv2xls
    mkdir build
    cd build
    cmake ..
    cmake --build .
For other build targets, please have a look at [BUILD_SPECIAL.md](BUILD_SPECIAL.md)
### Documentaion

- Print help:  csv2xls -h

### How to contribute

This software is far from being perfect but it does its job for me since months.
There is room for improvements in functionality and style.
You are invited to contribute in any way you want.

### Issues
If you think you found a bug or miss a feature, please report an issue.
Or try to fix it and send me pull requests or patches.

### In General
Fork this project and let us collaborate.
If you have an advise, I will listen to you and maybe follow :).
