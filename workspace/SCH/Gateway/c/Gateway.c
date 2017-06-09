#include <stdio.h>
#include <pthread.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <errno.h>

int main()
{
  int fd;

  if ((fd = serialOpen("/dev/ttyUSB0", 115200)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 2 ;
  }



  return 0;
}
