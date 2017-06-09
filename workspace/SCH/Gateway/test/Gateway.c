#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define IPADDR 192.168.0.30
#define PORT 3545

char msg[BUF_SIZE] = {NULL};

int main()
{
  int sock;
  struct sockaddr_in serv_addr;
  pthread_t sock_send_thread, sock_recv_thread;

  sock=socket(PF_INET, SOCK_STREAM, 0);
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=inet_addr(IPADDR);
  serv_addr.sin_port=htons(PORT);

  if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
     error_handling("connect() error");

  pthread_create(&sock_send_thread, NULL, sock_send_msg, (void*)&sock);
  pthread_create(&sock_recv_thread, NULL, sock_recv_msg, (void*)&sock);
  pthread_join(sock_send_thread, &thread_return);
  pthread_join(sock_recv_thread, &thread_return);

  close(sock);

  return 0;
}

void *sock_send_msg(void * arg)   // send thread main
{
   int sock=*((int*)arg);
   char t_msg[BUF_SIZE] = {NULL};

   while(1)
   {
      /************************************ insert Lora Msg ****************************************/
      //printf("send_msg..............:\n");
      //fgets(msg, BUF_SIZE, stdin);

  //     write(sock,penid_btn_up,sizeof(penid_btn_up));

 //      write(sock, name_msg, BUF_SIZE);

   }
   return NULL;
}

void * recv_msg(void * arg)   // read thread main
{
   int sock=*((int*)arg);

// char *selectMSG = "Celect Mode! \n/sendfile => filetrands mode\n/recvfile => filerecv mode\n/exit => exit\n";

   while(1)
   {
      printf("recv_msg.............:\n");
      read(sock,msg,BUF_SIZE);

      printf("msg!!!!!!:\n");
      fputs(msg, stdout);
      memset(msg,'\0',sizeof(msg));
   }

   return NULL;
}

void error_handling(char *msg)
{
   fputs(msg, stderr);
   fputc('\n', stderr);
   exit(1);
}
