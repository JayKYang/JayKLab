/*_Serial_test.cpp - SerialProtocol library - demo
  Copyright (c) 2014 NicoHood.  All right reserved.
  Program to test serial communication

  Compile with:
  sudo gcc -o Pi_Serial_Test.o Pi_Serial_Test.cpp -lwiringPi -DRaspberryPi -pedantic -Wall
  sudo ./Pi_Serial_Test.o
 */

// just that the Arduino IDE doesnt compile these files.
#ifdef RaspberryPi 

//include system librarys
#include <stdio.h> //for printf
#include <stdint.h> //uint8_t definitions
#include <stdlib.h> //for exit(int);
#include <string.h> //for errno
#include <errno.h> //error output

//wiring Pi
#include <wiringPi.h>
#include <wiringSerial.h>

// Find Serial device on Raspberry with ~ls /dev/tty*
// ARDUINO_UNO "/dev/ttyACM0"
// FTDI_PROGRAMMER "/dev/ttyUSB0"
// HARDWARE_UART "/dev/ttyAMA0"
char device[]= "/dev/ttyACM0";
char device2[]= "/dev/ttyUSB0";

// filedescriptor
int fd;
int fd2;

unsigned long baud = 9600;
unsigned long baud2 = 115200;
unsigned long time=0;
char newChar;
//prototypes
int main(void);
void loop(void);
void setup(void);

void setup(){

	printf("%s \n", "Raspberry Startup!");
	fflush(stdout);

	//get filedescriptor

	if ((fd = serialOpen (device, baud)) < 0){
		fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
		exit(1); //error
	}
	if ((fd2 = serialOpen (device2, baud2)) < 0){
		fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
		exit(1); //error
	}


	//setup GPIO in wiringPi mode
	if (wiringPiSetup () == -1){
		fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
		exit(1); //error
	}

}

void loop(){
	// Pong every 3 seconds
	if(millis()-time>=3000){
		serialPuts (fd, "Pong!\n");
		// you can also write data from 0-255
		// 65 is in ASCII 'A'
		serialPutchar (fd, 65);
		time=millis();
	}

	// read signal
	if(serialDataAvail (fd2)){
		char comm = serialGetchar(fd2);//Server->Cal
		printf("SERVER->CAL(%c)\n",comm);
	
		if(comm=='a'){
			serialPutchar(fd,'a');//Cal->DMM	
		//	printf("(2)");
			comm='\0';
			do
			{
				newChar = serialGetchar (fd);//DMM->Cal
				//if(newChar != '\0')
				//{
					printf("CAL->Server(%c)\n", newChar);
					serialPutchar(fd2,newChar);//Cal->Server
					fflush(stdout);
			//	}
			//	else
			//	{	
			//		break;
			//	}
			}while(newChar !='\n');
		}
	}
}

// main function for normal c++ programs on Raspberry
int main(){
	setup();
	while(1) loop();
	return 0;
}

#endif //#ifdef RaspberryPi

