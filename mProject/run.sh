#!/bin/bash
APATH=.
PATH_LIB=${APATH}/library_jui
function exportLib
{
 export LD_LIBRARY_PATH=${PATH_LIB}/replaceFileLib/libUse:${PATH_LIB}/TreeLib/libUse:${PATH_LIB}/XMLLibrary/libUse:${PATH_LIB}/dataStruct/libUse:${PATH_LIB}/strLibrary/libUse
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
	5)
           exportLib
           ./$2
	;;

        *)
	 ./run.sh 5 fileRename
         chmod -R 777 *
	;;
esac

