#include <error.h>
#include <string.h>
#include <wiringPi.h>
#include <WiringSerial.h>

int handle;

int SerialOpen()
{

	if((handle  = serialOpen("/dev/ttyUSB0", 115200)) < 0)
	{
		fprintf(stderr, "Unable to open serial device : %s\n", strerror(errno));
		return 1;
	}
	return 0;
}

void uart_ch(char ch)
{
	serialPutchar(handle,ch);
	close(handle);
}

void uart_str(char *str)
{
	while(*str) uart_ch(*str++);
}

