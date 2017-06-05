#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>


int main()
{
	unsigned char d[4]="ddd";
	int fd=serialOpen("/dev/ttyAMA0",9600);

	while(1)
	{
		int data = serialGetchar(fd);
		printf("\nData = %c",(char)data);
		serialPutchar(fd,*d);
		serialPuts(fd,"\n");
		fflush(stdout);
	}
	return 0;
}

	
