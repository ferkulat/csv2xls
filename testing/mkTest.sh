#!/usr/bin/bash

TEST=$1
mkdir $TEST
cp  Dummy/{*.cpp,*.h,*.sh,*.mk} $TEST
cd $TEST

for M in $(ls )
do
	NEWFILE=$(echo $M| sed -e"s/Dummy/$TEST/g")
	mv $M $NEWFILE
	sed -i -e "s/Dummy/$TEST/g" $NEWFILE
	
done
