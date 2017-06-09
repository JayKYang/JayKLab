
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUF_SIZE 128
#define MAX_CLNT 10
#define NAME_SIZE 20

void * handle_clnt(void * arg);
void send_msg(char * msg, int len);
void error_handling(char * msg);
void filename_arrange( char* file);
void recv_file(int *clnt_sock);
void send_file(int *clnt_sock);
void clnt_arr(int *clnt_sock);
int check_msg(char* msg);

int serv_sock, clnt_sock, i;
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
char confirm_pen=0,confirm_android=0;
char stack_buf[BUF_SIZE][BUF_SIZE];
int stack_cnt=1;
int stack_size=0;
int Mark_clnt=0;
typedef struct PPEN
{
   char ID[20];
   char state[20];
}PPEN;

struct PPEN temp_pen[10];
//char sig_pen1[BUF_SIZE];
typedef struct APEN
{
   char ID[20];
}APEN;
struct APEN sig_pen[10];
pthread_mutex_t mutx;
int main(int argc, char *argv[])
{
   //int serv_sock, clnt_sock, i;
   struct sockaddr_in serv_adr, clnt_adr;
   int clnt_adr_sz;

   pthread_t t_id;
   if(argc!=2) {
      printf("Usage : %s <port>\n", argv[0]);
      exit(1);
   }

   pthread_mutex_init(&mutx, NULL);
   serv_sock=socket(PF_INET, SOCK_STREAM, 0);

   memset(&serv_adr, 0, sizeof(serv_adr));
   serv_adr.sin_family=AF_INET;
   serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
   serv_adr.sin_port=htons(atoi(argv[1]));

   if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
      error_handling("bind() error");
   if(listen(serv_sock,5)==-1)
      error_handling("listen() error");


   while(1)
   {
      clnt_adr_sz=sizeof(clnt_adr);
      clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr,&clnt_adr_sz);

      if(clnt_cnt >= MAX_CLNT) {
         printf("CONNECT FAIL : %d \n", clnt_sock);
         write(clnt_sock, "too many users. sorry", BUF_SIZE);
         close(clnt_sock);
         continue;
      }

      pthread_mutex_lock(&mutx);
      clnt_socks[clnt_cnt++]=clnt_sock;
//      clnt_socks[clnt_cnt]=clnt_sock;
//      read(clnt_sock, clnt_name, NAME_SIZE);
//      strcpy(clnt_names[clnt_cnt++], clnt_name);
      pthread_mutex_unlock(&mutx);

      pthread_create(&t_id,NULL,handle_clnt,(void*)&clnt_sock);
      pthread_detach(t_id);
      printf("Connected client IP: %s \n",inet_ntoa(clnt_adr.sin_addr));
   }
   close(serv_sock);
   return 0;
}
void * handle_clnt(void * arg)
{
   int clnt_sock=*((int*)arg);
   int str_len=0, i;
   int z;

   char pen_clear[BUF_SIZE]={"PEN_CLEAR\r\n"};
   char sig_sendfile[BUF_SIZE] = {"FILE_SEND_CTOS\n"};
   char sig_recvfile[BUF_SIZE] = {"FILE_RECV_CTOS\n"};
   char btn_up_stoc[BUF_SIZE]={"BTN_UP_STOC\r\n"};
   char btn_down_stoc[BUF_SIZE]={"BTN_DOWN_STOC\r\n"};
   char enter[BUF_SIZE]={"\r\n"};
   char btn_normal_stoc[BUF_SIZE]={"BTN_NORMAL_STOC\r\n"};

/*   char sig_sendfile[BUF_SIZE] = {"FILE_SEND_CTOS"};
   char sig_recvfile[BUF_SIZE] = {"FILE_RECV_CTOS"};
   char btn_up_stoc[BUF_SIZE]={"BTN_UP_STOC"};
   char btn_down_stoc[BUF_SIZE]={"BTN_DOWN_STOC"};
   char btn_normal_stoc[BUF_SIZE]={"BTN_NORMAL_STOC"};
*/
   char sig_up[BUF_SIZE]={"BTN_UP>"};
   char sig_down[BUF_SIZE]={"BTN_DOWN>"};
   char sig_normal[BUF_SIZE]={"BTN_NORMAL>"};
   //char sig_pen1[BUF_SIZE];
   //char sig_pen2[BUF_SIZE]={"PEN_2"};
   char msg[BUF_SIZE] = {NULL};
   char *selectMSG = "Celect Mode! \n/sendfile => filetrans mode \n/recvfile => filerecv mode\n/exit => exit\n";
   write(clnt_sock,selectMSG,strlen(selectMSG));

   while(read(clnt_sock,msg,sizeof(msg))!=0)
   {
      printf("msg : ");
      fputs(msg,stdout);
      printf("\n\nstart!!!\n\n");
      if(check_msg(msg)==1)
      {
         printf("penid and button message received!!!\n");
         printf("%d\n",clnt_sock);

         strncpy(temp_pen[0].ID,msg,5);
         printf("pen penid : ");
         fputs(temp_pen[0].ID,stdout);
         printf("\n");

         filename_arrange(msg);
         strcpy(temp_pen[0].state,msg);
         printf("button : ");
         fputs(temp_pen[0].state,stdout);
         memset(msg,'\0',sizeof(msg));
         printf("\n");
         //-------------------------------
         printf("sig_pen[0].ID : %s\n",sig_pen[0].ID);
         confirm_pen=1;
      }
      if(check_msg(msg)==2)
      {
         printf("android penid received!!!\n ");
         printf("%d\n",clnt_sock);
         strncpy(sig_pen[0].ID,msg,5);
         memset(msg,'\0',sizeof(msg));
         for(z=0;z<clnt_cnt;z++){
            if(clnt_sock== clnt_socks[z]){
               Mark_clnt=clnt_socks[z];
                    if(stack_cnt>1){
                    write(Mark_clnt,"DOWN_EN\r\n",strlen("DOWN_EN\r\n"));
                    printf("cnt=>%d\n,Mark_clnt=>%d\n",stack_cnt,Mark_clnt);
                    }
               continue;
            }
            else{
                    strcpy(temp_pen[0].state,sig_normal);
               write(clnt_socks[z],pen_clear,strlen(pen_clear));
               printf("%d\n",clnt_socks[z]);
            }
         }
         confirm_android=1;
      }
      if(!strcmp(temp_pen[0].ID,sig_pen[0].ID) && confirm_pen==1 && confirm_android==1)
      {
         printf("penid equals tag penid.\n");
         printf("msg : ");
         fputs(msg,stdout);
         printf("\nbutton : ");
         fputs(temp_pen[0].state,stdout);
         printf("\npen penid : ");
         fputs(temp_pen[0].ID,stdout);
         printf("\nandroid penid : ");
         fputs(sig_pen[0].ID,stdout);
         printf("\n");
         if(!strcmp(msg,sig_sendfile) && strcmp(temp_pen[0].state,sig_up)!=0)
         {
         //   write(clnt_sock,selectMSG,strlen(selectMSG));
            printf("down error\n");
         }
         else if(!strcmp(msg,sig_sendfile) && !strcmp(temp_pen[0].state,sig_up))
         {
            printf("sock number:%d\n",clnt_sock);
            printf("sendfile/s_updown->1\n");
            printf("message trans\n");
            //recv_file(&clnt_sock);
            recv_file(&Mark_clnt);
         }
         else if(!strcmp(msg,sig_recvfile) && strcmp(temp_pen[0].state,sig_down)!=0)
         {
         //   write(clnt_sock,selectMSG,strlen(selectMSG));
            printf("up error\n");
         }
         else if(!strcmp(msg,sig_recvfile) && !strcmp(temp_pen[0].state,sig_down))
         {
            printf("sock number:%d\n",clnt_sock);
            printf("sendfile/s_updown->2\n");
            send_file(&Mark_clnt);
         }
         else if(!strcmp(temp_pen[0].state,sig_up))
         {
            printf("sock number:%d\n",Mark_clnt);
            printf("UP~~~~~~~~~~\n");
            write(Mark_clnt,btn_up_stoc,sizeof(btn_up_stoc));
         }
         else if(!strcmp(temp_pen[0].state,sig_down))
         {
            printf("sock number:%d\n",Mark_clnt);
            printf("DOWN~~~~~~~~~~\n");
            write(Mark_clnt,btn_down_stoc,sizeof(btn_down_stoc));
         }
         else if(!strcmp(temp_pen[0].state,sig_normal))
         {
            printf("sock number:%d\n",Mark_clnt);
            printf("NORMAL~~~~~~~~~~\n");
            write(Mark_clnt,btn_normal_stoc,sizeof(btn_normal_stoc));
         }
         else
         {
            printf("(!Notice)Chatting message transfered \n");
            send_msg(msg, str_len);
            memset(msg,'\0',BUF_SIZE);
         }
         printf("*%d*\n",clnt_sock);
      }
      else
      {
         printf("-%d-",clnt_sock);
         printf("PEN ID is different!!!!!\n");
         send_msg(msg,str_len);
      }
         }
   clnt_arr(&clnt_sock);
   close(clnt_sock);
   return NULL;
}
void recv_file(int *clnt_sock)
{
   char charbuff;
   char filename[BUF_SIZE];
   int filesize=0;
   char filesizebuf[BUF_SIZE];
   int total=0,sread,fp;
   char buf[BUF_SIZE];
   char loc[BUF_SIZE]="/home/jsw/search_server/stack/";
   char end[BUF_SIZE]="END";
   char* TM[20]={NULL};
   int filenamesize;
   int k,j;
   int i = 0;
   int s_cnt=0;
   char cc_buf;
   printf("%d\n",*clnt_sock);
   pthread_mutex_lock(&mutx);

   memset(filename,'\0',BUF_SIZE);

//   read(*clnt_sock,filename,strlen(filename));
//   read(*clnt_sock,filename,sizeof(filename));



   i = 0;
   while (1)
   {
      read(*clnt_sock,&charbuff,sizeof(char));
      if ( charbuff == '\n') {
         filename[i] = '\0';
         break;
      }
      filename[i++] = charbuff;

   }
   //filename[strlen(filename)-3]='\0';

   fputs(filename,stdout);
   printf("g\n");
   filename_arrange(filename);
   printf("h\n");
   printf("filename:%s \n",filename);
   printf("i\n");


   i = 0;
   while (1)
   {
      read(*clnt_sock,&charbuff,sizeof(char));
      if ( charbuff == '\n') {
         filesizebuf[i] = '\0';
         break;
      }
      filesizebuf[i++] = charbuff;
   }
   filesize = atoi(filesizebuf);

   //read(*clnt_sock,&cc_buf,sizeof(char));
   //read(*clnt_sock,&filesize,sizeof(filesize));
   printf("filesize:%d \n",filesize);

   for(j=0;j<sizeof(filename);j++)
   {
      stack_buf[stack_cnt][j]=filename[j];
   }

   fputs(stack_buf[stack_cnt],stdout);
   stack_cnt++;
   printf("stack_cnt:%d\n",stack_cnt);
   stack_size+=filesize;
//   fputs(filename,stdout);

   printf("%d\n",*clnt_sock);
   strcat(loc,filename);

   fp=open(loc,O_RDWR | O_CREAT,0644);

   while(total !=filesize){
      sread = read(*clnt_sock,buf,BUF_SIZE);
      //printf("s_cnt:%d\n",s_cnt);
      if(total%1000==0){
         printf("sending..... %d % \n ", (int)((total*100)/filesize) );
      }
      //printf("sread:%d\n",sread);
      //fputs(,stdout);
      total += sread;
      buf[sread]=0;
      write(fp,buf,sread);
      memset(buf,'\0',sizeof(buf));

      usleep(10);
   }
   printf("completed \n");
   printf("filesize:%d , received : %d \n",filesize,total);
   total=0;
   s_cnt=0;
   close(fp);

   pthread_mutex_unlock(&mutx);

}
void send_file(int *clnt_sock)
{
   char filename[BUF_SIZE];
   int filesize=0;
   int total=0,sread,fp;
   char buf[BUF_SIZE];
   char loc[BUF_SIZE]="/home/jsw/search_server/stack/";
   char end[BUF_SIZE]="END";
   char file_send_stoc[BUF_SIZE]={"FILE_SEND_STOC\r\n"};
   char enter[BUF_SIZE]={"\n"};
   int filenamesize;
   char x = EOF;
   int r_cnt=0;
   char ok_msg[BUF_SIZE];
   char stack_size_str[BUF_SIZE];
   char strr[15];
      /*printf("sendfile:\n");
      if(fgets(filename,sizeof(filename),stdin)==NULL)
         exit(0);
      filenamesize = strlen(filename);
      filename[filenamesize-1]=0;
      */

   printf("\n in the target!! \n");


   if(stack_cnt>1)
   {
      stack_cnt--;
      //if(read(clnt_sock
      printf("sending...........\n");

      strcat(loc,stack_buf[stack_cnt]);
      fp=open(loc,O_RDONLY);
      if(fp<0)
      {
         printf("No file\n");
//         continue;
      }

      write(*clnt_sock,file_send_stoc,sizeof(file_send_stoc));

      //*1*
      read(*clnt_sock,ok_msg,sizeof(ok_msg));
      sprintf(stack_size_str,"%d",stack_size);
      strcat(stack_size_str,enter);
      //*2*
      printf("%s\n",stack_size_str);
      write(*clnt_sock,stack_size_str,strlen(stack_size_str));

      filename_arrange(loc);

      memset(filename,'\0',sizeof(filename));


      strcpy(filename,loc);
      strcat(filename,"\n");
      //write(*clnt_sock,filename,sizeof(filename));
      write(*clnt_sock,filename,strlen(filename));

      filesize=lseek(fp,0,SEEK_END);
      sprintf(strr,"%d",filesize);
      strcat(strr,enter);
      write(*clnt_sock,strr,strlen(strr));
      lseek(fp,0,SEEK_SET);

      read(*clnt_sock,ok_msg,sizeof(ok_msg));
      printf("%s",ok_msg);
      while(total !=filesize){
         sread = read(fp,buf,BUF_SIZE);
         total += sread;
         if(total%1000==0){
         printf("sending..... %d % \n ", (int)((total*100)/filesize));
         }
         buf[sread]=0;
         write(*clnt_sock,buf,sread);
         usleep(10);
      }
      printf("completed \n");
      printf("filesize:%d , received : %d \n",filesize,total);

      total=0;

      close(fp);
      write(*clnt_sock,&x,sizeof(char));
   }
   else{
      printf("no file!!!!!!!!\n");
        stack_size=0;
        strcpy(temp_pen[0].state,"BTN_NORMAL>");
        memset(stack_size_str,'\0',sizeof(stack_size_str));
      printf("stack_cnt:%d\n",stack_cnt);
   }
}
void send_msg(char * msg, int len)   // send to all
{
   int i;
   pthread_mutex_lock(&mutx);
   for(i=0; i<clnt_cnt; i++)
      write(clnt_socks[i], msg, BUF_SIZE);
   pthread_mutex_unlock(&mutx);
}
void clnt_arr(int *clnt_sock)
{
//   int clnt_sock=*((int*)arg);

   pthread_mutex_lock(&mutx);
   for(i=0; i<clnt_cnt; i++)
   {
      if(*clnt_sock==clnt_socks[i])
      {
         while(i<(clnt_cnt-1)) {
            clnt_socks[i]=clnt_socks[i+1];
         //   strcpy(clnt_names[i],clnt_names[i+1]);
            i++;
         }
         break;
      }
   }
   clnt_cnt--;
   //*clnt_sock--;
   pthread_mutex_unlock(&mutx);

}
void error_handling(char * msg)
{
   fputs(msg, stderr);
   fputc('\n', stderr);
   exit(1);
}
int check_msg(char* msg)
{
   char* BEGIN = msg;
   char* END = msg + 20;
   char cnt_1=0,cnt_2=0;
   for(;BEGIN !=END ; BEGIN++)
   {
      if(*BEGIN == '>')
         cnt_1++;
      if(*BEGIN == '<')
         cnt_2++;
   }
   if(cnt_1==1)
      return 1;
   else if(cnt_2==1)
      return 2;
   else
      return -1;
}
void filename_arrange(char* file)
{
   char* BEGIN = file;
   char* TEMP = file ;
   char* END = file + 100;


   for( ; BEGIN != END ; BEGIN++){
      if( *BEGIN == '\0'){
         END = BEGIN;
      //   printf("END CHECK! \n");
         break;
      }
      else if(*BEGIN == '/'){
         TEMP=BEGIN;
      }
   }

   BEGIN = file;

   if(TEMP != BEGIN){
      for( ; BEGIN != END ; BEGIN++){
         *BEGIN = *(TEMP + 1);
         TEMP++;
         /*if(TEMP == END){
            END = file +127;
            BEGINE++;
            for( ;BEGINE != END ; BEGINE++){
               *BEGINE = '\0';
            }
            break;
         }*/
      }
   }

}
