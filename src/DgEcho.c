/*-------------------------------------------------------------------------
 *  DgEcho.c - Reads a string from Client and writes it back to Client
 *  Version:	$Name:  $
 *  Module:	
 *
 *  Purpose:	
 *  See:	
 *
 *  Author:	Hema Murthy (hema@bhairavi.iitm.ernet.in)
 *
 *  Created:        Sat 17-Mar-2007 10:58:43
 *  Last modified:  Sat 17-Mar-2007 14:12:40 by hema
 *  $Id: DgEcho.c,v 1.1 2007/03/26 04:26:09 hema Exp hema $
 *
 *  Bugs:	
 *
 *  Change Log:	<Date> <Author>
 *  		<Changes>
 -------------------------------------------------------------------------*/

 
#include <stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include "string.h"
#include "stdlib.h"

#define  MAXMESG 2048


/*-------------------------------------------------------------------------
 *  DgEcho -- Reads a packet from client and sends it back to client
 *    Args:	
 *    Returns:	Nothing
 *    Throws:	
 *    See:	UNIX Network Programming - Richard Stevens: Vol I
 *    Bugs:	
 -------------------------------------------------------------------------*/


void DgEcho(int sockFd, struct sockaddr *pcliAddr, socklen_t  maxCliLen)
  {
    int n;
    long int number_transmissions=0;
    socklen_t cliLen;
  	char mesg[MAXMESG];
  	printf("entered dgecho\n");
  	for  ( ; ;)
	  {
  		cliLen = maxCliLen;
  		n = recvfrom(sockFd, mesg, MAXMESG, 0, pcliAddr, &cliLen);
		printf("received string of size %d string is:%s\n",n, mesg);
  		if (n < 0) {
		   printf("dg_echo : recvfrom error");
  		      // err_dump("dg_echo : recvfrom error");*/
  		   exit(-1);
		}	
		if(mesg[0]=='f')
		{
			printf("%s %ld\n","Number of Transmissions:",number_transmissions);
			sendto (sockFd, "Y", n, 0, pcliAddr, cliLen);
			exit(-1);				
		}
		//FILE *pkt2;
		//pkt2=fopen("packets_crc_with_error.txt","w");
		int divisor[4];
		divisor[0]=1;
		divisor[1]=1;
		divisor[2]=0;
		divisor[3]=1;
		int dividend[10];
		int i=0,j=0,k=0;
		for(i=0;i<10;i++)
		{
			if(mesg[i]=='1')
				dividend[i]=1;
			else
				dividend[i]=0;
		
		}
		i=0;
		while(i<7)
		{
			k=0;
			while(dividend[k]==0)
			{
				k++;		
			}
			i=k;
			if(i>6)
				break;
			for(j=0;j<4;j++)
			{
				if(dividend[i+j]==divisor[j])
				{
					dividend[i+j]=0;
				}
				else
				{
					dividend[i+j]=1;	
				}
			}
		
					
		}
		number_transmissions++;
		char resp[1];
		if(dividend[7]==0 && dividend[8]==0 && dividend[9]==0)
		{
			resp[0]='Y';
			//printf("%s %s %s\n",mesg,"Y","dgech");
			//fprintf(pkt2,"%s\n",mesg);
		}
		else
			resp[0]='N';

		FILE *pkt2;
		pkt2=fopen("packets_crc_after_channel.txt","a");
		
		int t=0;
		if(resp[0]=='Y')
		{
			for(t=0;t<7;t++)
			{
				//printf("%c\n",mesg[t]);
				fprintf(pkt2,"%c",mesg[t]);
			}		
			fprintf(pkt2,"\n");
		
		}
		fclose(pkt2);
		if (sendto (sockFd, resp, n, 0, pcliAddr, cliLen) != n) {
		   printf("dg_echo : sendto  error\n");
                   exit(-1);
		}
		printf("Message sent back to Client dgech:%s\n", mesg); 
	  }
    }	/*  End of DgEcho		End of DgEcho   */

	




/*-------------------------------------------------------------------------
 * $Log: DgEcho.c,v $
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
 *                        End of DgEcho.c
 -------------------------------------------------------------------------*/
