LIBRPATH=/dirI/MyCode/mProject/library_jui/dataStruct/src

main : main.o intFixedStack.o
	gcc main.o intFixedStack.o -o main
main.o: main.c
	gcc -I${LIBRPATH} -c main.c
intFixedStack.o:${LIBRPATH}/intFixedStack.h ${LIBRPATH}/intFixedStack.c
	gcc -I${LIBRPATH} -c ${LIBRPATH}/intFixedStack.c

