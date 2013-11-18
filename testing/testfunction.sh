TEST="${0%.*}"
TEST="${TEST##*/}"

if [ -e $(pwd)/../${TEST}.exe ]
  then DRIVER="wine"
       EXT=".exe"
fi

$DRIVER $(pwd)/${TEST}${EXT} -v  2> /dev/null
