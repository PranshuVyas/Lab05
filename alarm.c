#include <stdio.h>
#include "ifttt.h"
#include <time.h>
#include <wiringPi.h>
int main(int argc, char *argv[])
{
/*
  ifttt("https://maker.ifttt.com/trigger/button_pressed/with/key/56-YpOKO17vOh-gimC2xK1qRAhRdzXXXX", "my1", "my 2", "my 33333");
*/

int ALARM_OFF = 1;
int ALARM_ARMING = 0;
int ALARM_ARMED = 0;
int ALARM_TRIGGERED = 0;
int ALARM_SOUNDING = 0;
int eventCount;
double time1,time2,time3,time4;
wiringPiSetup () ;
pinMode (1, OUTPUT); /* green */
pinMode (2, OUTPUT); /* red */
pinMode (4, OUTPUT); /* buzz */
pinMode (3, INPUT); /* button */
pinMode (0, INPUT); /* irtester */


while(1) {
	while(ALARM_OFF) {
	
	printf("off\n");
	digitalWrite(2, HIGH);
	digitalWrite(1, LOW);
	digitalWrite(4, LOW);
	delay(1000);
		if(!digitalRead(3)) {
		ALARM_ARMING = 1;
		ALARM_OFF = 0;
		digitalWrite(2, LOW);
		}
	}

time1 = time(NULL);

	while(ALARM_ARMING){
	printf("arming\n");
	digitalWrite(2, HIGH); delay(1000);
	digitalWrite(2, LOW); delay(1000);
	time2 = time(NULL);
		if((time2-time1)>=10) {
		ALARM_ARMING = 0;
		ALARM_ARMED = 1;
		digitalWrite(1,HIGH);
		}
	}
while(ALARM_ARMED){
printf("armed\n");
	if(!digitalRead(3)){
	ALARM_ARMED = 0;
	ALARM_OFF = 1;
	}
	if(ALARM_ARMED){
		if(digitalRead(0)){
		ALARM_ARMED = 0;
		ALARM_TRIGGERED = 1;
		}
	}
}
time3 = time(NULL);

while(ALARM_TRIGGERED){
printf("triggered\n");
digitalWrite(1, HIGH);
digitalWrite(2, HIGH); delay(1000);
digitalWrite(1, LOW);
digitalWrite(2, LOW); delay(1000);
time4 = time(NULL);
	if((time4-time3)>= 10) {
	ALARM_SOUNDING = 1;
	ALARM_TRIGGERED = 0;
	}
	if(!digitalRead(3)){
	ALARM_TRIGGERED = 0;
	ALARM_OFF = 1;
	}
}

eventCount = 1;
while(ALARM_SOUNDING) {
printf("sounding\n");
digitalWrite(1, HIGH);
digitalWrite(2, HIGH);
digitalWrite(4, HIGH); delay(2000);
digitalWrite(1, LOW);
digitalWrite(2, LOW);
digitalWrite(4, LOW); delay(2000);
if(eventCount){
  printf("Trying to connect to server\n");
  ifttt("https://maker.ifttt.com/trigger/alarm_triggered/with/key/nwcUZyfI71f61Zxa99rUvoAyMt7ch43R3hQRgkY1m5C", "my1", "my 2", "my 33333");
  eventCount = 0;
}
if(!digitalRead(3)){
ALARM_SOUNDING = 0;
ALARM_OFF = 1;
}
}
}
  return 0;
}
