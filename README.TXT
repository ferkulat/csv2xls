
=========== Description ===========

csv2xls is a command line utility which converts csv files into one
(or more if splitted) Excel(TM) file(s).

This software is far from being perfect but it does its job for me since months.
There is room for improvements in functionality and style.

	-= Features =-

- split output in several files, if max line limit exceeded
- set work sheet name of xls output file
- noninteractive -> useful for automated tasks

	-= Limitations =-

- produces only Excel(TM) 97/2000/XP/2003
- no cell formatting, just plain text

=========== Building ==============


	-= Prequisites =-

xlslib: http://sourceforge.net/projects/xlslib/
libcsv: http://sourceforge.net/projects/libcsv/

if you checked out from git:
	automake
	autoconf

        -= Compile =-

if you checked out from git, you will have to run
./bootstrap.sh
before

./configure
make
        -= Install =-

make install


=========== Documentaion ==============

Print help:  csv2xls -h
manual page: man csv2xls


