#include <stdio.h>
#include <stdlib.h>
#include<math.h> 
#include<string.h>
#define MAX_TREE_HT 256


struct MinHeapNode
{
    char data;  
    unsigned freq;
    struct MinHeapNode *left, *right;
};
 
struct MinHeap
{
    unsigned size;    // Current size of min heap
    unsigned capacity;   // capacity of min heap
    struct MinHeapNode **array;  // Array of minheap node pointers
};
 
struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp =
          (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}
 
struct MinHeap* createMinHeap(unsigned capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0;  
    minHeap->capacity = capacity;
    minHeap->array =
     (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
      smallest = right;
 
    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
 
int isSizeOne(struct MinHeap* minHeap)
{
    return (minHeap->size == 1);
}
 
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}
 
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1)/2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1)/2];
        i = (i - 1)/2;
    }
    minHeap->array[i] = minHeapNode;
}
 
void buildMinHeap(struct MinHeap* minHeap)
{
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}
 
void printArr(int arr[], int n, FILE* op,FILE* codes)
{
    int i;
    for (i = 0; i < n; ++i)
    {
	printf("%d", arr[i]);
	fprintf(op,"%d", arr[i]);
	fprintf(codes,"%d", arr[i]);
    }
    printf("\n");
    fprintf(op,"\n");
    fprintf(codes,"\n");
}
 
int isLeaf(struct MinHeapNode* root)
{
    return !(root->left) && !(root->right) ;
}
 
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{
    struct MinHeap* minHeap = createMinHeap(size);
    int i;
    for (i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;
 
    // Step 1: Create a min heap of capacity equal to size.  Initially, there are
    // modes equal to size.
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
 
    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap))
    {
        // Step 2: Extract the two minimum freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);
 
        // Step 3:  Create a new internal node with frequency equal to the
        // sum of the two nodes frequencies. Make the two extracted node as
        // left and right children of this new node. Add this node to the min heap
        // '$' is a special value for internal nodes, not used
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
 
    // Step 4: The remaining node is the root node and the tree is complete.
    return extractMin(minHeap);
}
 
void printCodes(struct MinHeapNode* root, int arr[], int top, FILE* op, FILE* characters, FILE* codes)
{
    // Assign 0 to left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1,op, characters,codes);
    }
 
    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1,op, characters,codes);
    }
 
    if (isLeaf(root))
    {
        printf("%c: ", root->data);
	fprintf(op,"%c: ", root->data);
	fprintf(characters,"%c\n", root->data);
        printArr(arr, top, op, codes);
    }
}
 
void HuffmanCodes(char data[], int freq[], int size, FILE* op, FILE* characters, FILE* codes)
{
   struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
 
   int arr[MAX_TREE_HT], top = 0;
   printCodes(root, arr, top, op, characters,codes);
}

int main()
{
	int arr_freq[256];
	float arr_prob[256];
	int i,ch;
	for(i=0;i<256;i++)
	{
		arr_freq[i]=0;
		arr_prob[i]=0;
	}
	
	FILE *ip,*op,*characters,*codes;
	ip=fopen("input.txt","r");
	//ip=fopen(argv[1],"r");
	op=fopen("huff_codebook.txt","w");
	characters=fopen("huff_ch.txt","w");
	codes=fopen("huff_ch_codes.txt","w");  

	if(ip)
	{
		long int xyz=0;
		while((ch=getc(ip))!=EOF)	
		{	//printf("%ld\n",xyz++);
			arr_freq[ch]+=1;
		}
		//printf("YYY\n");
		fclose(ip);
	}
	int p_sum=0;
	for(i=0;i<256;i++)
	{
		p_sum+=arr_freq[i];
	}
	for(i=0;i<256;i++)
	{
		arr_prob[i]=arr_freq[i]/((float)p_sum);
	}
	float l2=log(2);
	//printf("%f\n",l2);
	float H=0,x;
	for(i=0;i<256;i++)
	{
		if(arr_prob[i]!=0)
		{
			x=(1.0/arr_prob[i]);
			H+=(arr_prob[i])*(log(x))/l2;
			//printf("%f %f\n",x,H);	
		}
	}	
		
	int rep=0;
	for(i=0;i<256;i++)
	{
		if(arr_freq[i]!=0)
			rep+=1;
	}	
	char data[rep];
	int freq[rep];
	int j=0;
	for(i=0;i<256;i++)
	{
		if(arr_freq[i]!=0)
		{
			data[j]=i;
			freq[j]=arr_freq[i];
			j++;		
		}
	}
	/*
	printf("%d\n",rep);
	for (i = 0; i < rep; ++i)
        	printf("%c %d\n",data[i],freq[i]);	
	printf("\n");
	*/

    int size = sizeof(data)/sizeof(data[0]);
    printf("\n");
    printf("%s\n","Huffman Codebook:");
    HuffmanCodes(data, freq, size,op,characters,codes);
    fclose(op);
    fclose(characters);
    fclose(codes);


	FILE *huff_ch1,*huff_ch_codes1;
	huff_ch1=fopen("huff_ch.txt","r");
	huff_ch_codes1=fopen("huff_ch_codes.txt","r");
	int ch1;
	int index1=0;
	char code[256];
	float l1=0;
	if(huff_ch1)
	{
		while((index1=getc(huff_ch1))!=EOF)	
		{
			fscanf(huff_ch_codes1,"%s",code);
			l1+=arr_prob[index1]*strlen(code);
			index1=getc(huff_ch1);	
		}
	}
	printf("\n");
	printf("%s %f\n","Entropy:",H);
	printf("%s %f\n","Avg word length:",l1);
	printf("%s %f %s\n","Efficiency:",(H/l1)*100,"%");
	fclose(huff_ch1);
	fclose(huff_ch_codes1);

    return 0;
}
