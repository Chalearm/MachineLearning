#!/bin/bash

for i in `pwd | find -name *.so`;do  
rm -rf $i 
done
for i in `pwd | find -name *.o`;do  
rm -rf $i 
done
for i in `pwd | find -name ".fuse*"`;do  
rm -rf $i 
done
