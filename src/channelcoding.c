#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int rem(int n,FILE *packets_crc)
{
	int divisor[4];
	divisor[0]=1;
	divisor[1]=1;
	divisor[2]=0;
	divisor[3]=1;
	int dividend[10],dividend_cp[7];
	int i=0,j=0,k=0,x=0,r=0;
	x=n;
	for(i=0;i<7;i++)
	{
		r=x%10;
		x=x/10;
		dividend[6-i]=r;
		dividend_cp[6-i]=r;
	}
	//printf("%d\n",x);
	dividend[7]=0;
	dividend[8]=0;
	dividend[9]=0;
	/*
	for(i=0;i<10;i++)
	{
		printf("%d",dividend[i]);
	}
	printf("\n");
	*/
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
		
		/*		
		printf("%d  ",i);
		for(k=0;k<10;k++)
		{
			printf("%d",dividend[k]);
		}
		printf("\n");
		*/
	}
	
	/*
	for(i=0;i<10;i++)
	{
		printf("%d",dividend[i]);
	}
	printf("\n");
	*/
	int p=0;
	for(p=0;p<7;p++)
	{
		fprintf(packets_crc,"%d",dividend_cp[p]);	
	}
	
	for(p=7;p<10;p++)
	{
		fprintf(packets_crc,"%d",dividend[p]);	
	}
	fprintf(packets_crc,"\n");	
	return 0;
}



int main()
{
	FILE *inp,*inp_huffcoded,*huff_ch,*huff_ch_codes;
	inp=fopen("input.txt","r");
	inp_huffcoded=fopen("inp_huffcoded.txt","w");
	huff_ch=fopen("huff_ch.txt","r");
	huff_ch_codes=fopen("huff_ch_codes.txt","r");
	int i=0;
	long int inp_length=0;
	char arr_code[256][256];
	int ch;
	/*
	for(i=0;i<128;i++)
	{
		//arr_freq[i]=0;
		arr_code[i]=-5;
	}
	*/
	/*
	if(inp)
	{
		while((ch=getc(inp))!=EOF)	
		{
			arr_freq[ch]+=1;
		}
	}
	*/
	int index=0;
	char code[256];
	if(huff_ch)
	{
		while((index=getc(huff_ch))!=EOF)	
		{
			fscanf(huff_ch_codes,"%s",code);
			//printf("%d %s\n",index,code);
			strcpy(arr_code[index],code);
			index=getc(huff_ch);	
		}
	}

	if(inp)
	{
		//long int xyz=0;
		while((ch=getc(inp))!=EOF)
		{
			inp_length++;
			//printf("%ld %d %s\n",xyz++,ch,"Y");
			fprintf(inp_huffcoded,"%s",arr_code[ch]);			
		}
		//printf("N\n");
	}
	fclose(inp);
	fclose(inp_huffcoded);
	fclose(huff_ch);
	fclose(huff_ch_codes);
	

	FILE *inp_huffcoded1,*packets,*packets_crc;
	packets=fopen("packets.txt","w");
	packets_crc=fopen("packets_crc.txt","w");
	inp_huffcoded1=fopen("inp_huffcoded.txt","r");
	
	//char packet[7];
	int extra_bits=0,count=0,j=0;
	long int huff_length=0;
	
	if(inp_huffcoded1)
	{
		while((ch=getc(inp_huffcoded1))!=EOF)
		{
			huff_length++;
			//packet[0]=ch;
			//printf("%c",ch);
			fprintf(packets,"%c",ch);
			for(i=1;i<7;i++)
			{
				if((ch=getc(inp_huffcoded1))!=EOF)
				{
					huff_length++;
					//packet[i]=ch;
					//printf("%c",ch);
					fprintf(packets,"%c",ch);
				}
				else
				{
					extra_bits=7-i;
					for(j=i;j<7;j++)
					{
						//packet[i]='0';				
						//printf("0");						
						fprintf(packets,"0");
						
					}
					break;
				}					
			}
			//printf("\n");
			fprintf(packets,"\n");
			count++;
			if(extra_bits!=0)
				break;
			/*
			for(j=0;j<7;j++)
			{
				packet_code+=j*pow(10,6-j);				
			}
			*/
			
			//fprintf(packets,"%d",packet_code);
			//packet_code=0;			
		}
	}
	printf("%s %d\n%s %d\n","extra_bits:",extra_bits,"number_of_packets:",count);	
	printf("%s %f %s\n","input_size:",(float)inp_length/1000,"KB");
	printf("%s %f %s\n","huffman_encoded_size:",(float)huff_length/8000,"KB");
	printf("%s %f %s\n","compression:",(1-(((float)huff_length/8000)/((float)inp_length/1000)))*100,"%");
	fclose(inp_huffcoded1);
	fclose(packets);	

	int packet_code=0;
	FILE *pkt;
	pkt=fopen("packets.txt","r"); 
	if(pkt)
	{
		for(i=0;i<count;i++)
		{
			fscanf(pkt,"%d",&packet_code);
			//printf("%d\n",packet_code);
			rem(packet_code,packets_crc);							
		}			
	}
	

	fclose(packets_crc);
	fclose(pkt);
	
	return 0;
	
}
