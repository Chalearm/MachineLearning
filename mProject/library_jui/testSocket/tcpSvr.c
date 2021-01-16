/********************************************************************/
/*
      FILE        :  tcpSvr.c
      Name     :   Chalearm Saelim
      Date       :   2 April 2016
      Email      :  chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose :   To show how the TCP server work easily
                          By using socket.h 

      Description :    In establishing the TCP server, There are simple steps as the follows:
                                1.  Create a socket with the socket() system call
                                2.  Bind the socket to an address using the bind() system call. 
                                      For a server socket on the Internet, an address consists of a port number on the host machine.
                                3.  Listen for connections with the listen() system call
                                4.  Accept a connection with the accept() system call. 
                                     This call typically blocks until a client connects with the server.
                                5.  Send and receive data
                                6.  Close the connection

                 ====== Things that you take into account to create the TCP server =======
                                 - The number of Client connection    (listen)
                                 -  Type of socket (SOCK_STREAM)
                                 
                                 Variables that we keep until main is terminated.
                                 
                                  int port                       :    the port is the TCP server 
                                  int sockfd                  :    the socket of the  TCP server 
                                  int newsockfd           :    new socket file descriptor to use for communication between server and client 
 
                                 
                                 * Note :initialization part 
                                 How to set ip that we will use to create the TCP server 
                                 
                                 serv_addr.sin_addr.s_addr = inet_addr("172.20.10.2");
                                 
                                 Local variable that we use in initialization phase
                                 int clilen  <-- keep size of variable 
                                 struct sockaddr_in serv_addr, cli_addr;  <--- to describe what the TCP server is 
                 
      Dependency     :   We use the included library as below 
                                                #include <sys/types.h> 
                                                #include <sys/socket.h>
                                                #include <netinet/in.h>
      How to compile: gcc tcpSvr.c -o  a
      How to run        : ./a
*/
/*******************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <string.h>
#include <netinet/in.h>
#define BUFFSIZE 250
#define IPLENGTH 25
#define NUMLISTEN 5
#define DEFAULT_PORT 9000

struct tcpServerHandle
{
    int m_sockfd;
    int m_port;
    int m_ret;
    char m_ipStr[IPLENGTH];
    /* to handle client */
    int m_newSockfd;
    int m_numListen;
};

int isValidIp4 (const char *str);
void verifyInetVariable(int *port,int *listenNum);
void   initializationTcpServer(struct tcpServerHandle *obj,int port,const char *ip,int listenNum);
void  loopHandleClient(struct tcpServerHandle *obj);

int main(int arc,char **argv)
{
    struct tcpServerHandle tcpServ;
    initializationTcpServer(&tcpServ,9003,"127.0.0.1",3);
    loopHandleClient(&tcpServ);
    return 0;
}

void  initializationTcpServer(struct tcpServerHandle *obj,int port,const char *ip,int listenNum)
{
    struct sockaddr_in serv_addr;
    int ret =1;
    verifyInetVariable(&port,&listenNum);
    if(obj!=NULL)
    { 
        /* set object variable */
        obj->m_ret =ret;
        obj->m_port = port;
        obj->m_numListen = listenNum;
        memset(obj->m_ipStr,0,IPLENGTH);
        /* step set TCP server */
        /*
                set socket type
                input value in the socket address variable (set port,ip and type of communication)
                Bind the socket 
                Set listen
        */
        obj->m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        if(isValidIp4 (ip)==1 )
        { 
            serv_addr.sin_addr.s_addr = inet_addr(ip);
            memcpy(obj->m_ipStr,ip,strlen(ip));
        }
        else
        { 
            serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        }
        /*
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_addr.s_addr = inet_addr("172.20.10.2");
        */

        /* bind socket  */
        /* Now bind the host address using bind() call.*/
        if (bind(obj->m_sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("ERROR on binding\n");
            ret =0;
            obj->m_ret =0;
        }
        else
        {
            /* Now start listening for the clients, here process will
            * go in sleep mode and will wait for the incoming connection
            */
            listen(obj->m_sockfd,listenNum);
            printf("Server has been established - ip :%s ,port :%d\n",obj->m_ipStr,obj->m_port);
        }
    }
    else
    {
        /* do nothing */
    } 
}

void  loopHandleClient(struct tcpServerHandle *obj)
{
    int ret=1;
    int n=0;
    int clilen;
    unsigned char buff[BUFFSIZE];
    struct sockaddr_in  cli_addr;
    if(obj!= NULL)
    {
        ret = obj->m_ret;
        if(obj->m_ret!=0)
        {
            
            printf("waiting Client request \n");
            clilen = sizeof(cli_addr);
            /* Accept actual connection from the client */
            obj->m_newSockfd = accept(obj->m_sockfd, (struct sockaddr *)&cli_addr, &clilen);
        }
        else
        {
            obj->m_newSockfd  =-1;
        }
    
    }
    else
    {
        /* do nothing */
    }
   if (obj->m_newSockfd  < 0)
   {
       obj->m_ret =0;
        printf("ERROR on accept\n");
        ret =0;
    }
    else
    {
        /* do nothing */
    } 
    /* wiating for msg */
    if(obj->m_ret  == 1)
    {
        printf("waiting Client sends the msg \n");
    
         bzero(buff,BUFFSIZE);
         n = read(obj->m_newSockfd,buff,BUFFSIZE-1);
         if (n < 0) 
         {
             printf("error Reading form socket \n");
         }
         else
         {
             /* do nothign */
         } 
         printf("Here is the message: %s\n",buff);
         n = write(obj->m_newSockfd,"I got your message",18);
         if (n < 0) 
         {
             printf("error Writing form socket \n");
         }
         else
         {
            close(obj->m_newSockfd);
            close(obj->m_sockfd);
         }  
    }
    else
    {
        /* do nothing  */
    }
}  

void verifyInetVariable(int *port,int *listenNum)
{
    if(*port <= 0)
    {
        *port = DEFAULT_PORT;
    }
    else
    {
        /* do nothing */
    }
    if(*listenNum <=0)
    {
        *listenNum = NUMLISTEN;
    }
    else
    {
        /* do nothing */
    }
}

/*
This is a routine I wrote a while ago for an embedded system which generated various 
suspect patterns on a network. As such, it uses absolutely no fancy stuff like network 
libraries or even the standard C libraries, preferring to steer clear of all that modern stuff
 like string tokenizing and (shudder) regular expression libraries :-) To that end, it's suited to
 just about any environment you could find yourself in, and it was blindingly fast.
Although, if you're in an environment that has something like checkIp4Addess(),
 I'd suggest you use that instead. It's an indication of the stuff you sometimes have to
 put up with when doing embedded stuff (although it is a real solution).
*/
int isValidIp4 (const char *str) 
{
    int segs = 0;   /* Segment count. */
    int chcnt = 0;  /* Character count within segment. */
    int accum = 0;  /* Accumulator for segment. */

    /* Catch NULL pointer. */

    if (str == NULL)
        return 0;

    /* Process every character in string. */

    while (*str != '\0') 
    {
        /* Segment changeover. */

        if (*str == '.') 
        {
            /* Must have some digits in segment. */

            if (chcnt == 0)
                return 0;

            /* Limit number of segments. */

            if (++segs == 4)
                return 0;

            /* Reset segment values and restart loop. */

            chcnt = accum = 0;
            str++;
            continue;
        }/* Check numeric. */

        if ((*str < '0') || (*str > '9'))
            return 0;

        /* Accumulate and check segment. */

        if ((accum = accum * 10 + *str - '0') > 255)
            return 0;

        /* Advance other segment specific stuff and continue loop. */

        chcnt++;
        str++;
    }

    /* Check enough segments and enough characters in last segment. */

    if (segs != 3)
        return 0;

    if (chcnt == 0)
        return 0;

    /* Address okay. */

    return 1;
}