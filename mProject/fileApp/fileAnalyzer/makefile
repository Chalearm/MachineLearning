main1: main1.o simRexical.o
	gcc main1.o simRexical.o -o main1
main1.o: main1.c
	gcc -c main1.c
simRexical.o: simRexical.h simRexical.c
	gcc -c simRexical.c

clean:
	rm main1.o simRexical.o
