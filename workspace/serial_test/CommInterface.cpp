#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <pthread.h>

using namespace std;

#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyAMA0"
#define _POSIX_SOURECE 1
#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE

void *t_CommRecv(void *data)
{
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();

	char* thread_name = (char*)data;
	int i = 0;

	while(i<3)
	{
		printf("[%s] pid:%u, tid:%x --- %d \n",thread_name, (unsigned int)pid, (unsigned int)tid, i);
		i++;
		sleep(1);
	}
}

int main()
{
	int fd,c,res;
	struct termios oldtio, newtio;
	char buf[255];

	fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY );
	if (fd <0) {perror(MODEMDEVICE); exit(-1);}

	tcgetattr(fd,&oldtio); /* 현재 설정을 oldtio에 저장 */

	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;

        /* set input mode (non-canonical, no echo,...) */
        newtio.c_lflag = 0;
        newtio.c_cc[VTIME]    = 0;   /* 문자 사이의 timer를 disable */
        newtio.c_cc[VMIN]     = 5;   /* 최소 5 문자 받을 때까진 blocking */

        tcflush(fd, TCIFLUSH);
        tcsetattr(fd,TCSANOW,&newtio);

        while (STOP==FALSE) {       /* loop for input */
        res = read(fd,buf,255);   /* 최소 5 문자를 받으면 리턴 */
        buf[res]=0;               /* '\0' 종료 문자열(printf를 하기 위해) */
        printf(":%s:%d\n", buf, res);

        if (buf[0]=='z') STOP=TRUE;
        }
        tcsetattr(fd,TCSANOW,&oldtio);
}
