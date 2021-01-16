#!/bin/bash
APATH=/ROOTPATH/mProject
PATH_LIB=${APATH}/library_jui
function exportLib
{
 export LD_LIBRARY_PATH=${PATH_LIB}/TreeLib/lib:${PATH_LIB}/dataStruct/lib
}
function cleanBuild
{
 make clean
}
function normal_build 
{
 make
}
function g_build
{
 make CFLAGS=-g
}
case $1 in
	1)
            cleanBuild
            normal_build 
	;;
	2)
           cleanBuild
           g_build
	;;
	3)
           ./run.sh 1
           exportLib
           ./$2
	;;
	4)
           ./run.sh 2 
           exportLib
           valgrind -v --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./$2

	;;
        *)
        echo "1 -- normal build"
        echo "2 -- debug build"
        echo "3 -- normal run"
        echo "4 -- debug run"
	;;
esac

