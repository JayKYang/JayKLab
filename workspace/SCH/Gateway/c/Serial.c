#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>
#include <pthread.h>

int LoraOpen()
void *thread_Lora_recv(void *arg)

pthread_t threads;
int main()
{
  int ret_val;

  ret_val = LoraOpen()
  if(ret_val == 1)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 0;
  }
  else if(ret_val == 2)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 0;
  }
  if(pthread_create(&threads, NULL, &thread_Lora_recv, (int*)&fd) < 0)
  {
    perror("thread create error:");
    exit(0);
  }

  return 0;

}

  printf ("\n") ;
  return 0 ;
}

int LoraOpen()
{
  int fd;

  if ((fd = serialOpen ("/dev/ttyUSB0", 115200)) < 0)
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

void *thread_Lora_recv(void *arg, int fd)
{
  while(1)
  {
    data = serialGetchar(fd);
    printf("\nPC > RPi = %c", (char)data);
    fflush(stdout);
  }
}
