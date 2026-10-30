set -e
make
TERM=xterm-1003 ./spel -no_bug -s 1
#TERM=xterm-1003 ./spel -s 1
