/********************************************************************/
/*
      FILE      :  tcpSvrSelect.c
      Name      :   Chalearm Saelim
      Date      :   3 April 2016
      Email     :  chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose   :  Handle multiple socket connections with select and fd_set on Linux 

    Description :   In establishing the TCP server, See more detail in tcpSvr.c
                    And Select() method  

                    * According to POSIX.1-2001  
                    #include <sys/select.h>

                    - select, pselect, FD_CLR, FD_ISSET, FD_SET, FD_ZERO - synchronous I/O multiplexing

                    - Allow a program to monitor multiple file descriptors, waiting unit one or more of 
                    the file descriptors become "ready" for some class of I/O operation (e.g., input possible).

                    - select waits for events that are typically outside your program's control. In essence, by calling 
                    - select, your program says "I have nothing to do until ..., please suspend my process".

                     FD_SET 
                          a set of socket to "monitor" for some activity. There are four useful macros
                          - FD_ZERO   --- clear an fd_set
                          - FD_ISSET  --- check if a descriptor is in an fd_set
                          - FD_SET    --- add a descriptor to an fd_set 
                          - FD_CLR    --- Remove a descriptor from an fd_set

                            Example  ** select() method is able to support 3 fd sets
                                        e.g. argument at below  (&readfds,NULL (slot2),NULL(slot3),timeout )
                              
                                activity = select( max_sd + 1 , &readfds , NULL , NULL , &tv);
                                 if(activity==0 ) No event or time out 
                                 *** tv will be set to zero if tv is passed to select().
                                     
                                     
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
                                                #include <sys/select.h>
                                                #include <sys/types.h> 
                                                #include <sys/socket.h>
                                                #include <netinet/in.h>
                                                
                                                #include <fcntl.h>
      How to compile  : gcc tcpSvrSelect.c -o  a
      How to run      : ./a
*/
/*******************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <fcntl.h>
#include <netdb.h>
#define BUFFSIZE 250
#define IPLENGTH 25
#define NUMLISTEN 5
#define DEFAULT_PORT 9000
#define MAX_CLIENT 15

struct tcpServerHandle
{
    int m_sockfd;
    char m_ipStr[IPLENGTH];
    int m_port;
    int m_ret;
    int m_numListen;
};

void make_nonblocking(int fd);
int isValidIp4 (const char *str);
void verifyInetVariable(int *port,int *listenNum);
void initialTcpSvr(struct tcpServerHandle *obj,int port,const char *ip,int numListen);
void loopHandleClients(struct tcpServerHandle *obj);

int main(int argc,char **argv)
{
    struct tcpServerHandle tcpSvrSel;
    initialTcpSvr(&tcpSvrSel,9007,"",6);
    loopHandleClients(&tcpSvrSel);
    return 0;
}
void loopHandleClients(struct tcpServerHandle *obj)
{
    char buffer[BUFFSIZE];
    int clientFD[MAX_CLIENT];
    int max_sd,i,sd,valread,activity,addrlen;
    struct sockaddr_in  address;
    int ret =1;
    int new_socket;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    /*set of socket descriptors */
    fd_set readfds;
    int numListen =0;
    char *message = "Hello new client !!";
     addrlen = sizeof(address);
    memset((void*)clientFD,0,sizeof(int)*MAX_CLIENT);
    if(obj!=NULL)
    {
        numListen = obj->m_numListen;
    }
    else
    {
        ret =0;
    }
    while(ret)
    {        
        /*clear the socket set*/
        FD_ZERO(&readfds);
        /* add master socket to set */
        FD_SET(obj->m_sockfd, &readfds);
        max_sd = obj->m_sockfd;
        for ( i = 0 ; i < numListen ; i++) 
        {
            //socket descriptor
            sd = clientFD[i];
             
            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);
             
            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }
        /*wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely */
        tv.tv_sec =1;
        activity = select( max_sd + 1 , &readfds , NULL , NULL , &tv);
        printf("-------------- olkoko koko %d sec\n",tv.tv_sec);
        /* If something happened on the master socket , then its an incoming connection */
        if (FD_ISSET(obj->m_sockfd, &readfds)) 
        {
            if ((new_socket = accept( obj->m_sockfd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                obj->m_ret=0;
                ret =0;
                printf("Error new connection \n");
            }
            else
            {
                
                make_nonblocking(new_socket);
                //inform user of socket number - used in send and receive commands
             //   printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
       printf("New connection , socket fd is %d   \n" , new_socket );
        
                //send new connection greeting message            
                if( send(new_socket, message, strlen(message), 0) != strlen(message) ) 
                {
                    obj->m_ret=0;
                    ret =0;
                    printf("Error Sending \n");
                }
                else
                {
                    
                printf("5555 \n");
                }
            
            }

            if(ret==1)
            {
                printf("Welcome message sent successfully\n");
                  
                //add new socket to array of sockets
                for (i = 0; i < numListen; i++) 
                {
                    //if position is empty
                    if( clientFD[i] == 0 )
                    {
                        clientFD[i] = new_socket;
                        printf("Adding to list of sockets as %d\n" , i);
                        break;
                    }
                }
            }
            else
            {
                /* do nothing */
            }
                
        }
        
                //else its some IO operation on some other socket :)
        for (i = 0; i < numListen; i++) 
        {
            sd = clientFD[i];
              
            if (FD_ISSET( sd , &readfds)) 
            {
                /* Check if it was for closing , and also read the incoming message */
                if ((valread = read( sd , buffer, 1024)) == 0)
                {
                    /* Somebody disconnected , get his details and print */
                    printf("Connection is close \n");
                   getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                   printf("Host disconnected ,  port %d \n" ,  ntohs(address.sin_port));
                  //  printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                      
                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    clientFD[i] = 0;
                }
                else /*Echo back the message that came in*/
                {
                    //set the string terminating NULL byte on the end of the data read
                    buffer[valread] = '\0';
                    send(sd , buffer , strlen(buffer) , 0 );
                }
            }
        }
    }
   
}
void make_nonblocking(int fd)
{
    fcntl(fd, F_SETFL, O_NONBLOCK);
} 
void initialTcpSvr(struct tcpServerHandle *obj,int port,const char *ip,int numListen)
{
    struct sockaddr_in serv_addr;
    int ret =1;
    verifyInetVariable(&port,&numListen);
    if(obj!=NULL)
    { 
        /* set object variable */
        obj->m_ret =ret;
        obj->m_port = port;
        obj->m_numListen = numListen;
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
            listen(obj->m_sockfd,numListen);
            make_nonblocking(obj->m_sockfd);
            printf("Server has been established - ip :%s ,port :%d\n",obj->m_ipStr,obj->m_port);
        }
    }
    else
    {
        /* do nothing */
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