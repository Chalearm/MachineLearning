#!/bin/bash
make clean
make CFLAGS=-g
valgrind -v --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./$1
