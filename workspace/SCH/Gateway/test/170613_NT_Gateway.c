/*1.Check Socket Communication --> OK
  2.Add Lora Source
  3.Check Lora Communication
  4.Check running Thread
  5. Serial -> TCP / TCP -> Serial
  */

#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>
//#include <sys/types.h>
//#include <fcntl.h>
//#include <sys/stat.h>

#define BUF_SIZE 1024
#define IP_ADDR "192.168.0.8"
#define PORT 3545

char msg[BUF_SIZE] = {};

void *sock_send_msg(void *arg);
void *sock_recv_msg(void *arg);
void error_handling(char *msg);

int main()
{
	printf("main\n");
	int sock;
	struct sockaddr_in serv_addr;
	pthread_t sock_send_thread, sock_recv_thread;
	
	void * thread_return;

	sock=socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(IP_ADDR);
	serv_addr.sin_port=htons(PORT);

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
		error_handling("connect() error");
	
	printf("main2\n");
	pthread_create(&sock_recv_thread, NULL, sock_recv_msg, (void*)&sock);
	pthread_create(&sock_send_thread, NULL, sock_send_msg, (void*)&sock);
	pthread_join(sock_recv_thread, &thread_return);
	pthread_join(sock_send_thread, &thread_return);

	close(sock);

	return 0;
}

void *sock_send_msg(void *arg)
{
	int sock=*((int*)arg);

	printf("send start\n");
	char t_msg[BUF_SIZE]={};// = {"101123123213"};


	while(1)
	{
		printf("send while\n");
		scanf("%s",t_msg);
		write(sock,t_msg,sizeof(t_msg));
		
		/*insert Lora Msg*/

		//write(sock,msg,BUF_SIZE);
	}
	return NULL;
}

void *sock_recv_msg(void *arg)
{
	printf("recv start\n");
	int sock=*((int*)arg);

	while(1)
	{
		printf("recv while\n");
		read(sock,msg,BUF_SIZE);
		printf("%s\n",msg);
	//	fputs(msg,stdout);
		memset(msg, '\0',sizeof(msg));
	}

	return NULL;
}

void error_handling(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

