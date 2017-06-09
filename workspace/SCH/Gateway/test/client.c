
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUF_SIZE 128
#define NAME_SIZE 20
#define MAXLINE 127

void * send_msg(void * arg);
void * recv_msg(void * arg);
void recv_file(int *sock);
void send_file(int *sock);
void error_handling(char * msg);


char name[NAME_SIZE]= {NULL};
char msg[BUF_SIZE] = {NULL};

char buf[MAXLINE+1];
pthread_mutex_t mutx;

int s_updown;

int main(int argc, char *argv[])
{
   int sock;
   struct sockaddr_in serv_addr;
   pthread_t snd_thread, rcv_thread;
   void * thread_return;
   if(argc!=4) {
      printf("Usage : %s <IP> <port> <name>\n", argv[0]);
      exit(1);
    }

   sprintf(name, "%s", argv[3]);
   sock=socket(PF_INET, SOCK_STREAM, 0);

   memset(&serv_addr, 0, sizeof(serv_addr));
   serv_addr.sin_family=AF_INET;
   serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
   serv_addr.sin_port=htons(atoi(argv[2]));

   if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
      error_handling("connect() error");

   //pthread_mutex_lock(&mutx);

   pthread_create(&snd_thread, NULL, send_msg, (void*)&sock);
   pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);
   pthread_join(snd_thread, &thread_return);
   pthread_join(rcv_thread, &thread_return);

   //pthread_mutex_unlock(&mutx);
   close(sock);
   return 0;
}

void * send_msg(void * arg)   // send thread main
{
   int sock=*((int*)arg);
   char name_msg[NAME_SIZE+BUF_SIZE] = {NULL};
   char t_msg[BUF_SIZE] = {NULL};
   char t_name_msg[BUF_SIZE] = {NULL};
   char penid_btn_up[BUF_SIZE] = {"PEN_1/BTN_UP>"};
   char penid_btn_down[BUF_SIZE] = {"PEN_1/BTN_DOWN>"};
   char penid_btn_normal[BUF_SIZE] = {"PEN_1/BTN_NORMAL>"};
   const char test_ok_c[BUF_SIZE]={"TEST_OK_C"};
   while(1)
   {
      printf("send_msg..............:\n");
      fgets(msg, BUF_SIZE, stdin);


      if(!strcmp(msg,"/exit\n"))
      {
         close(sock);
         exit(0);
      }
      else if(!strcmp(msg,"/UP\n"))
      {
         write(sock,penid_btn_up,sizeof(penid_btn_up));
      }
      else if(!strcmp(msg,"/DOWN\n"))
      {
         write(sock,penid_btn_down,sizeof(penid_btn_down));
      }
      else if(!strcmp(msg,"/NORMAL\n"))
      {
         write(sock,penid_btn_normal,sizeof(penid_btn_normal));
      }
      else if(!strcmp(msg,"/OK\n")){
         write(sock,test_ok_c,sizeof(test_ok_c));
      }
      else
      {
         strcpy(t_msg, "\n");
         sprintf(t_name_msg,"[%s] %s", name, t_msg);
         sprintf(name_msg,"[%s] %s", name, msg);
         if(strcmp(name_msg, t_name_msg) != 0)
            write(sock, name_msg, BUF_SIZE);
      }
   }
   return NULL;
}

void * recv_msg(void * arg)   // read thread main
{
   int sock=*((int*)arg);
   char name_msg[BUF_SIZE] = {NULL};
   char file_msg[BUF_SIZE] = {NULL};
   const char signal_send[BUF_SIZE] = {"FILE_SEND_STOC"};
   const char signal_recv[BUF_SIZE] = {"FILE_RECV_STOC"};
   const char signal_up[BUF_SIZE]={"BTN_UP_STOC"};
   const char signal_down[BUF_SIZE]={"BTN_DOWN_STOC"};
   const char signal_normal[BUF_SIZE]={"NORMAL_STOC"};
   const char test[BUF_SIZE]={"TEST_OK_S"};
//   char *selectMSG = "Celect Mode! \n/sendfile => filetrands mode\n/recvfile => filerecv mode\n/exit => exit\n";

   while(1)
   {
      printf("recv_msg.............:\n");
      read(sock, name_msg,BUF_SIZE);

/*      if(!strcmp(name_msg,selectMSG))
      {
         fputs(name_msg,stdout);
      }
*/
/*      else if(!strcmp(name_msg, signal_recv))
      {
         //s_updown=1;
      }
      else if(!strcmp(name_msg, signal_send))
      {
      }
      else if(!strcmp(name_msg,signal_up))
      {

         s_updown=1;
         printf("UUU%d\n",s_updown);
      }
      else if(!strcmp(name_msg,signal_down))
      {
         s_updown=2;
         printf("DDD%d\n",s_updown);
      }
      else if(!strcmp(name_msg,signal_normal))
      {
         printf("NNN%d\n",s_updown);
         fputs(name_msg,stdout);
      }
*/   //   else
   //   {

      //if(!strcmp(name_msg,test)){
         printf("msg!!!!!!:\n");
         fputs(name_msg, stdout);
         memset(msg,'\0',sizeof(msg));
   //   }
   //   }
   }
   return NULL;
}

void error_handling(char *msg)
{
   fputs(msg, stderr);
   fputc('\n', stderr);
   exit(1);
}
