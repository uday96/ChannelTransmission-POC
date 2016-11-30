#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int main()
{
    FILE *inp_huffcoded,*huff_ch,*huff_ch_codes,*huff_dcd;
    //inp=fopen("inp.txt","r");
    inp_huffcoded=fopen("inp_huffcoded.txt","r");
    huff_ch=fopen("huff_ch.txt","r");
    huff_ch_codes=fopen("huff_ch_codes.txt","r");
    huff_dcd=fopen("huff_decoded.txt","w");
    int i=0,ct=0;
    char arr_code[256][256];
    int ch;
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
    char* temp;
    temp = malloc( sizeof(*temp) * 256 );
    char c;
    int length=0;
    //char* empty;
    //empty = malloc( sizeof(*empty) * 256 );
    if(inp_huffcoded)
    {
        while((ch=getc(inp_huffcoded))!=EOF)
        {
            if(ch==49)
                c='1';
            else
                c='0';
            temp[ct]=c;
	    temp[ct+1]='\0';
            //printf("%s\n",temp);
            for(i=0;i<256;i++)
            {
                if(strcmp(arr_code[i],temp)==0)
                {
                    fprintf(huff_dcd,"%c",i);
                    //free(temp);
                    //strcpy(temp,empty);
		    *temp='\0';
		    length=ct+1;
                    ct=-1;
                    //printf("Y\n");
                    break;
                }
            }           
            ct++;
            //printf("%d\n",ct);
        }
    }
    fclose(inp_huffcoded);
    fclose(huff_ch);
    fclose(huff_ch_codes);
    fclose(huff_dcd);
    return 0;
}

