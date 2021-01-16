#!/bin/bash
TARGET=main
CUR_PATH=/ROOTPATH/mProject
LIB_PATH=${CUR_PATH}/library_jui
SVM_PATH=${CUR_PATH}/svmApp/lib
READXML_PATH=${LIB_PATH}/XMLLibrary/lib
STR_PATH=${LIB_PATH}/strLibrary/lib
TRE_PATH=${LIB_PATH}/TreeLib/lib
DATS_PATH=${LIB_PATH}/dataStruct/lib

clean_buildFile() 
{
    make clean
}
make_file()
{
    make
}
export_sharedLib()
{
    export LD_LIBRARY_PATH=${SVM_PATH}:${TRE_PATH}:${DATS_PATH}:${READXML_PATH}:${STR_PATH}
}
debug_mode()
{
    make CFLAGS=-g
}
super_debug_mode()
{
    make CFLAGS="-g -O0"
}
runTarget()
{
    ./${TARGET}
}
runTestMem()
{
    valgrind -v --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./${TARGET}
}

case $1 in
    0)
        clear
        echo "Help"
        echo "1. build all files"
        echo "2. clean and do 1."
        echo "3. rebuild,run test memory"
        echo "4. rebuild,run test memory2"
        echo "5. build debug mode"
	echo "6. rus test memory"
    ;;
    1)
        clear
        make_file
    ;;
    2)
        clean_buildFile
        clear
        make_file
    ;;
    3)
        export_sharedLib
        clean_buildFile
        clear
        debug_mode
        runTestMem
    ;;     
    4)
        export_sharedLib
        clean_buildFile
        clear
        super_debug_mode
        runTestMem
    ;;     
    5)
        clean_buildFile
        clear
        debug_mode
    ;;     
    6)
        export_sharedLib
        runTestMem
    ;;     
    *)
        clean_buildFile
        make_file
        clear
        export_sharedLib
        runTarget

esac


