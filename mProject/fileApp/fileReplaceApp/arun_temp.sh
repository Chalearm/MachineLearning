#!/bin/bash
APATH=/ROOTPATH/mProject
PATH_LIB=${APATH}/library_jui

function copyLib
{
    cp -r ${PATH_LIB}/$1/lib/*.* ${PATH_LIB}/$1/libUse/

}
function copyLibAll
{
    copyLib replaceFileLib
    copyLib TreeLib
    copyLib XMLLibrary
    copyLib dataStruct
    copyLib strLibrary

}
function exportLib
{
 export LD_LIBRARY_PATH=${PATH_LIB}/replaceFileLib/lib:${PATH_LIB}/TreeLib/lib:${PATH_LIB}/XMLLibrary/lib:${PATH_LIB}/dataStruct/lib:${PATH_LIB}/strLibrary/lib
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
            copyLibAll
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
        echo "1 -- normal build"
        echo "2 -- debug build"
        echo "3 -- normal run"
        echo "4 -- debug run"
	echo "5 -- normal run"
	;;
esac

