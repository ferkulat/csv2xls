[![Build Status](https://travis-ci.org/ferkulat/csv2xls.svg?branch=master)](https://travis-ci.org/ferkulat/csv2xls)
[![Build status](https://ci.appveyor.com/api/projects/status/github/ferkulat/csv2xls?brach=master&svg=true)](https://ci.appveyor.com/project/ferkulat/csv2xls)

# csv2xls
### Description 

csv2xls (csv to xls) is a command line utility which converts csv files into one
(or more if maximum rows are exceeded) Excel(TM) file(s).
 ### Features

- split output in several files, if max line limit exceeded
- set work sheet name of xls output file
- noninteractive -> useful for automated tasks
- if you want UTF-8 support, you need to compile and link xlslib with libiconv

### Limitations

- produces only Excel(TM) 97/2000/XP/2003 files
- no cell formatting, just plain text

### Prerequisites

- libiconv: http://ftp.gnu.org/pub/gnu/libiconv/ (Optional to get UTF-8 support)
- cmake:    to build/compile
- compiler: gcc8, clang6, msvc2017

### Documentaion

- Print help:  csv2xls -h
- manual page: man csv2xls
- https://github.com/ferkulat/csv2xls/wiki

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
