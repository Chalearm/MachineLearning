/********************************************************************/
/*
      FILE     :  tcpClient.c
      Name     :   Chalearm Saelim
      Date     :   3 April 2016
      Email    :  chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose  :   To show how the TCP client work easily
                          By using socket.h 

      Description :    In connect the TCP server, There are simple steps as the follows:
                                1.  Create a socket with the socket() system call
                                2.  Connect the socket to the address of the server using the connect() system call
                                3.  Send and receive data. There are a number of ways to do this, but the simplest is 
                                     to use the read() and write() system calls.

                 ====== Things that you take into account to create the TCP server =======

                                 
                                 Variables that we keep until main is terminated.
                                 
                                  int port                       :    the port is  to connect to the TCP server 
                                  int sockfd                  :    the socket of the  TCP client 
                                 
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
      How to compile:  gcc tcpClient.c -o  b
      How to run    :  ./b 
*/
/*******************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#define BUFFSIZE 250
#define IPLENGTH 25
#define DEFAULT_PORT 9000
#define IP_ADDR "127.0.0.1"
struct tcpClientHandle
{
    int m_sockfd; 
    int m_port; 
    char m_ipStr[IPLENGTH];
    int m_ret;
};


int isValidIp4 (const char *str);
int verifyInetVariable(int *port,const char *ip);
void initializationClientSocket(struct tcpClientHandle *obj,const char *ip,int port);
void  loopHandleServer(struct tcpClientHandle *obj);

int main(int argc,char **argv)
{
    struct tcpClientHandle clnSck;
    initializationClientSocket(&clnSck,"",9003);
    loopHandleServer(&clnSck);
    return 0;
}

void initializationClientSocket(struct tcpClientHandle *obj,const char *ip,int port)
{
    struct sockaddr_in serv_addr;
    char *ipAddr =IP_ADDR;
    int ret =0;
    if((obj!=NULL))
    {
        obj->m_ret  =1;
        ret= 1;
        obj->m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
        memset(obj->m_ipStr,0,IPLENGTH);
        if (obj->m_sockfd < 0) 
        {
            printf("Error to open socket \n");
            obj->m_ret =0;
            ret =0;
        }
        else
        {
            /* do nothing */
        }
        memset((void *) &serv_addr, 0,sizeof(serv_addr));
        serv_addr.sin_family = AF_INET; 
        serv_addr.sin_port = htons(port);
        if(verifyInetVariable(&port,ip)==1)
        {
            serv_addr.sin_addr.s_addr = inet_addr(ip);
            memcpy(obj->m_ipStr,ip,strlen(ip));
        }
        else
        {
            serv_addr.sin_addr.s_addr = inet_addr(ipAddr);
            memcpy(obj->m_ipStr,ipAddr,strlen(ipAddr));
        }
        obj->m_port = port;
    }
    else
    {
        /* do nothing */
    }
    if(ret==1)
    {
        ret = connect(obj->m_sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    }
    else
    {
        /* do nothing */
    }
    if(ret <0 )
    {
        printf("Error to connect the TCP server  \n");
        obj->m_ret = 0;
    }
    else
    {
        printf("Begin to talk with Server -- ip: %s , port : %d\n",obj->m_ipStr,obj->m_port);
    }
}
void  loopHandleServer(struct tcpClientHandle *obj)
{
    unsigned char buff[BUFFSIZE];
    int n=0;
    int ret=1;
    memset(buff,0,BUFFSIZE);
    if(obj!=NULL)
    { 
        ret = obj->m_ret;
    }
    else
    {
        /* do nothing */
    }
    if(ret==1)
    {
        fgets(buff,BUFFSIZE-1,stdin);
        n = write(obj->m_sockfd,buff,strlen(buff));
        if (n < 0) 
        {
             printf("ERROR writing to socket\n");
        }
         memset(buff,0,BUFFSIZE);
        n = read(obj->m_sockfd,buff,BUFFSIZE-1);
        if (n < 0) 
        {
             printf("ERROR reading from socket\n");
        }
        else
        {
            close(obj->m_sockfd);
            printf("%s\n",buff);
        }
    }
    else
    {
        /* do nothing */
    }
}

int verifyInetVariable(int *port,const char *ip)
{
    if(*port <= 0)
    {
        *port = DEFAULT_PORT;
    }
    else
    {
        /* do nothing */
    }
    return isValidIp4 (ip);
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