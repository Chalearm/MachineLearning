#!/bin/bash
XCEN=242
YCEN=205
echo "e 255 0 0 spPic2.txt a $XCEN $YCEN 70 0 144 48" > j.txt
sleep 3
echo "e 0 255 0 spPic2.txt a $XCEN $YCEN 70 0 48 -144" > j.txt
sleep 3
echo "e 255 0 0 spPic2.txt a $XCEN $YCEN 140 0 144 48" > j.txt
sleep 3
echo "e 0 255 0 spPic2.txt a $XCEN $YCEN 140 0 48 -144" > j.txt
sleep 3
echo "e 0 0 255 spPic2.txt a $XCEN $YCEN 150 0 144 48" > j.txt
sleep 3
echo "e 0 255 255 spPic2.txt a $XCEN $YCEN 150 0 48 -144" > j.txt
sleep 3
echo "e 0 255 255 spPic2.txt a $XCEN $YCEN 154 0 90 0" > j.txt
sleep 3
echo "e 0 0 255 spPic2.txt a $XCEN $YCEN 31 0 144 0" > j.txt
sleep 3
echo "a 0 255 255 spPic2.txt a $XCEN $YCEN 154 0 90 0" > j.txt
sleep 3
echo "b 0 255 255 spPic2.txt a $XCEN $YCEN 154 0 90 0" > j.txt
sleep 3
