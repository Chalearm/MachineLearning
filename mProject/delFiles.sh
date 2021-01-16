#!/bin/bash
APATH=.
SVMP=${APATH}/svmApp
SVMP2=${APATH}/jSvmApp2
SVMCP=${SVMP}/configFile
SVMDAT=${SVMCP}/dataConfig
FILERE=${APATH}/fileApp/fileReplaceApp
LIBJPATH=${APATH}/library_jui

rm ${FILERE}/main
rm ${FILERE}/Makefile
rm ${FILERE}/run.sh
rm ${APATH}/fileRename

rm ${SVMP}/build.sh
rm ${SVMP}/errPath.txt
rm ${SVMP}/main
rm ${SVMP}/Makefile
rm ${SVMP2}/run.sh
rm ${SVMP2}/main
rm ${SVMP2}/makefile
rm ${SVMCP}/main.xml
rm ${SVMDAT}/uciAbalone/test/ds_uci_Abalone_testing_set_1.xml
rm ${SVMDAT}/uciAbalone/train/ds_uci_Abalone_training_set_1.xml

rm ${SVMDAT}/uciAdult/test/ds_uci_Adult_testing_set_1.xml
rm ${SVMDAT}/uciAdult/train/ds_uci_Adult_training_set_1.xml


rm ${SVMDAT}/uciCarEval/test/ds_uci_CarEval_testing_set_1.xml
rm ${SVMDAT}/uciCarEval/train/ds_uci_CarEval_training_set_1.xml

rm ${SVMDAT}/uciLetterReg/test/ds_uci_LetterReg_testing_set_1.xml
rm ${SVMDAT}/uciLetterReg/train/ds_uci_LetterReg_training_set_1.xml


rm ${SVMDAT}/uciVehicle/test/ds_uci_Vehicle_testing_set_1.xml
rm ${SVMDAT}/uciVehicle/test/ds_uci_Vehicle_testing_set_2.xml
rm ${SVMDAT}/uciVehicle/test/ds_uci_Vehicle_testing_set_3.xml
rm ${SVMDAT}/uciVehicle/test/ds_uci_Vehicle_testing_set_4.xml
rm ${SVMDAT}/uciVehicle/test/ds_uci_Vehicle_testing_set_5.xml
rm ${SVMDAT}/uciVehicle/test/ds_uci_Vehicle_testing_set_6.xml
rm ${SVMDAT}/uciVehicle/train/ds_uci_Vehicle_training_set_1.xml
rm ${SVMDAT}/uciVehicle/train/ds_uci_Vehicle_training_set_2.xml
rm ${SVMDAT}/uciVehicle/train/ds_uci_Vehicle_training_set_3.xml
rm ${SVMDAT}/uciVehicle/train/ds_uci_Vehicle_training_set_4.xml
rm ${SVMDAT}/uciVehicle/train/ds_uci_Vehicle_training_set_5.xml
rm ${SVMDAT}/uciVehicle/train/ds_uci_Vehicle_training_set_6.xml


rm ${SVMDAT}/uciWine/test/ds_uci_Wine_testing_set_1.xml
rm ${SVMDAT}/uciWine/train/ds_uci_Wine_training_set_1.xml

rm ${LIBJPATH}/tVectPAvlT/Makefile
rm ${LIBJPATH}/tVectPAvlT/run.sh
rm ${LIBJPATH}/tVectPAvlT/main

rm ${LIBJPATH}/tVt2/makefile
rm ${LIBJPATH}/tVt2/main
rm ${LIBJPATH}/tMt2/makefile
rm ${LIBJPATH}/tMt2/main
rm ${LIBJPATH}/tMtd2/makefile
rm ${LIBJPATH}/tMtd2/main
rm ${LIBJPATH}/tsMt2AvlT/makefile
rm ${LIBJPATH}/tsMt2AvlT/main
rm ${LIBJPATH}/tsMt2AvlT/run.sh
rm ${LIBJPATH}/tPVLMt2/run.sh
rm ${LIBJPATH}/tPVLMt2/main
rm ${LIBJPATH}/tPVLMt2/makefile
rm ${LIBJPATH}/testSVM/main
rm ${LIBJPATH}/testSVM/makefile
rm ${LIBJPATH}/testSVM/run.sh
rm ${LIBJPATH}/testMatrix/main
rm ${LIBJPATH}/testVDoubleAvlTree/main
rm ${LIBJPATH}/testSMO/main
rm ${LIBJPATH}/tSMOKl1/main
rm ${LIBJPATH}/tSMOKl2/main
rm ${LIBJPATH}/tSMOWSS3/main
rm ${LIBJPATH}/tSetRv/main
rm ${LIBJPATH}/tKernelFn/main
rm ${LIBJPATH}/testMatrix/makefile
rm ${LIBJPATH}/testMatrix/run.sh
rm ${LIBJPATH}/testSMO/makefile
rm ${LIBJPATH}/testVDoubleAvlTree/makefile
rm ${LIBJPATH}/tSMOKl1/makefile
rm ${LIBJPATH}/tSMOKl2/makefile
rm ${LIBJPATH}/tSMOWSS3/makefile
rm ${LIBJPATH}/tCgGd1/makefile
rm ${LIBJPATH}/tSetRv/makefile
rm ${LIBJPATH}/tKernelFn/makefile
rm ${LIBJPATH}/testVDoubleAvlTree/run.sh
rm ${LIBJPATH}/testSMO/run.sh
rm ${LIBJPATH}/tSMOKl1/run.sh
rm ${LIBJPATH}/tSMOKl2/run.sh
rm ${LIBJPATH}/tSMOWSS3/run.sh
rm ${LIBJPATH}/tCgGd1/run.sh
rm ${LIBJPATH}/tKernelFn/run.sh
rm ${LIBJPATH}/tSetRv/run.sh
rm ./datGen/run.sh
rm ./datGen/Makefile
rm ./datGen/main


for i in `find ${SVMP2}/src/ -name *.c ! -name *_tmp.c`;do  
rm -f $i
done


