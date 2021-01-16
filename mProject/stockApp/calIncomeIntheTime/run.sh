#!/bin/bash
pwd = `pwd`
cd /home/jui/mProject/stockApp/calIncomeIntheTime/
make
export LD_LIBRARY_PATH=/home/jui/mProject/library_jui/XMLLibrary/lib/:/home/jui/mProject/library_jui/strLibrary/lib/
./main
cd $pwd
