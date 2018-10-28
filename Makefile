CC=gcc
CFLAGS=-lWarn -pedantic

alarm: alarm.o libmyifttt.a
	cc alarm.o -L. -lmyifttt -lcurl -lwiringPi -o alarm

iralarm: iralarm.o 
	cc iralarm.o -lwiringPi -o iralarm

blink: blink.o 
	cc blink.o -lwiringPi -o blink

button: button.o 
	cc button.o -lwiringPi -o button

libmyifttt.a:	ifttt.o
	ar -rcs libmyifttt.a ifttt.o

ifttt.o: 	ifttt.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

alarm.o:	alarm.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

all:	alarm tester irtester blink button

clean:
	rm tester irtester *.o
