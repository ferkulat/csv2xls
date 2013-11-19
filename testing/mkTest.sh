#!/usr/bin/bash

TEST=$1
mkdir $TEST
cp  Dummy/{*.cpp,*.h,*.sh,*.mk,*.hpp} $TEST
cd $TEST

for M in $(ls )
do
	NEWFILE=$(echo $M| sed -e"s/Dummy/$TEST/g;")
	mv $M $NEWFILE
	sed -i -e "s/Dummy/$TEST/g;s/DUMMY/$(echo $TEST|sed -e's/[a-z]/\u&/g')/g" $NEWFILE
	
done
