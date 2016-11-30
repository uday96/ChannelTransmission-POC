/*-------------------------------------------------------------------------
 *  Client.c - Client Program for sending messages to the server
 *  Version:	$Name:  $
 *  Module:	
 *
 *  Purpose:	
 *  See:	
 *
 *  Author:	Hema Murthy (hema@bhairavi.iitm.ernet.in)
 *
 *  Created:        Sat 17-Mar-2007 14:09:41
 *  Last modified:  Mon 26-Mar-2007 09:54:20 by hema
 *  $Id: Client.c,v 1.1 2007/03/26 04:26:09 hema Exp hema $
 *
 *  Bugs:	
 *
 *  Change Log:	<Date> <Author>
 *  		<Changes>
 -------------------------------------------------------------------------*/

/* 
 * Example of client using UDP protocol.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "strings.h"
#include "string.h"
#include "include/DgFunctions.h"
/*-------------------------------------------------------------------------
 *  Usage -- Prints the usage for the program
 *    Args:	
 *    Returns:	Nothing
 *    Throws:	
 *    See:	
 *    Bugs:	
 -------------------------------------------------------------------------*/
void Usage () {
  printf ("Client ServerIPAddr ServerPort ClientIPAddress ClientPort\n");
}


/*-------------------------------------------------------------------------
 *  main -- Main Program for the Client - sends 10 lines of text to server
 *    Args:	Takes as arguments ServerIP, ServerPort, ClientIP, ClientPort
 *    Returns:	Nothing
 *    Throws:	
 *    See:	Unix Network Programming: Richard Stevens - Vol I
 *    Bugs:	
 -------------------------------------------------------------------------*/
int  main (int argc, char **argv)
{
    int                   sockFd;
    int                   serverPortNumber, clientPortNumber;
    struct sockaddr_in    clientAddr,serverAddr;
    char                  *sendMsg = "Testing UDP Protocol\n";

    int                   i;
    char                  tempString[256];

    if (argc != 5) {
      Usage();
      exit(-1);
    }
    
     /* Fill in the structure "serverAddr " with the address of the 
     * server that we want to send to .
     */
    sscanf(argv[2],"%d", &serverPortNumber); 
    sscanf(argv[4],"%d", &clientPortNumber); 

    bzero(( char *) &serverAddr , sizeof (serverAddr));
    serverAddr.sin_family   = AF_INET;
    serverAddr.sin_addr.s_addr =inet_addr(argv[1]);
    serverAddr.sin_port  = htons(serverPortNumber);
  
  
    /* 
     * Open a UDP socket (an Internet datagram socket).
     */
     
    if (( sockFd = socket(AF_INET,SOCK_DGRAM ,0)) < 0) {
      printf("client : can't open datagram socket \n");
      exit(-1);
    }
    /* 
     * Bind any local address for us.
     */
   	//printf("Y1\n"); 
      printf ("Socket bound\n");    
	//printf("Y2\n");
    
    bzero(( char *) &clientAddr , sizeof (clientAddr));
    clientAddr.sin_family   = AF_INET;
    clientAddr.sin_addr.s_addr =inet_addr(argv[3]);
    clientAddr.sin_port  = htons(clientPortNumber);
  	//printf("Y3\n");
    if (bind (sockFd, (struct sockaddr *) &clientAddr ,sizeof(clientAddr)) < 0) {
      printf(" client: can't bind  local address\n");
    exit(-1);
    }
   
    sendMsg = malloc( sizeof(*sendMsg) * 256 );
    FILE *inp_pkt,*op_pkt;
    inp_pkt=fopen("packets_crc.txt","r");
    op_pkt=fopen("packets_crc_after_channel.txt","w");
    //char sendMsg[10];
    int ch;
    //int ct;
   //printf("Y4\n");
    
    if(inp_pkt)
    {
	//printf("Y5\n");
      while((ch=getc(inp_pkt))!=EOF)
		{
			//printf("Y6\n");
			//printf("%d\n",ch);
			if(ch==49){
				//printf("Y666\n");
				sendMsg[0]='1';
				}			
			else{
				//printf("Y66\n");
				sendMsg[0]='0';
				//printf("%c\n",sendMsg[0]);
				}			
			//printf("Y6\n");
			for(i=1;i<10;i++)
			{
				//printf("Y6\n");
				//printf("%d\n",ch);
				ch=getc(inp_pkt);
				if(ch==49){
					sendMsg[i]='1';
					}			
				else{
					sendMsg[i]='0';			
					}
				
			}
			//printf("Y7\n");
			if((ch=getc(inp_pkt))==EOF)
			{
				break;
			}
			//printf("Y8\n");
			i=0;
			/*
			for(ct=0;ct<10;ct++)
			{
				printf("%c",sendMsg[ct]);
			}			
			printf("\n");
			*/	
			sendMsg[10]='\0';
			strcpy(tempString,sendMsg);
			tempString[10]='\0';
			printf ("Message Sent c = %s\n", sendMsg);
			DgClient(tempString, sockFd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
		}
	DgClient("finish", sockFd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    }
    /*
    for (i = 0; i < 10; i++) {
      tempString[0] = (char) (i+48);
      tempString[1] = ' ';
      tempString[2] = '\0';
      strcat(tempString, sendMsg);
      printf ("Message Sent = %s\n", sendMsg);
     DgClient(tempString, sockFd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    }
    */
	//printf("%ld\n",number_of_transmissions);
    fclose(inp_pkt);
    fclose(op_pkt);
    close(sockFd);
    exit(0);
    return(0);
}	/*  End of main		End of main   */
      


/*-------------------------------------------------------------------------
 * $Log: Client.c,v $
 * Revision 1.1  2007/03/26 04:26:09  hema
 * Initial revision
 *
 *
 * Local Variables:
 * time-stamp-active: t
 * time-stamp-line-limit: 20
 * time-stamp-start: "Last modified:[ 	]+"
 * time-stamp-format: "%3a %02d-%3b-%:y %02H:%02M:%02S by %u"
 * time-stamp-end: "$"
 * End:
 *                        End of Client.c
 -------------------------------------------------------------------------*/
