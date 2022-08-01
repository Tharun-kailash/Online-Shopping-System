int size = -1;
struct queue
{
	char name[30];
	char address[50];
    char phn[12];
	char pincode[7];
	double price;
};
struct queue H[100];

int parent(int i)
{

	return (i - 1) / 2;
}

int leftChild(int i)
{

	return ((2 * i) + 1);
}

int rightChild(int i)
{

	return ((2 * i) + 2);
}
void swap(struct queue *a, struct queue *b)
{
    struct queue temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
void shiftUp(int i)
{
	while (i > 0 && H[parent(i)].price < H[i].price) {

		swap(&H[parent(i)], &H[i]);
		i = parent(i);
	}
}

void shiftDown(int i)
{
	int maxIndex = i;

	int l = leftChild(i);

	if (l <= size && H[l].price > H[maxIndex].price) {
		maxIndex = l;
	}

	int r = rightChild(i);

	if (r <= size && H[r].price > H[maxIndex].price) {
		maxIndex = r;
	}

	if (i != maxIndex) {
		swap(&H[i], &H[maxIndex]);
		shiftDown(maxIndex);
	}
}

void insert_pqueue(struct customer *cus,float p)
{
	size = size + 1;
	H[size].price = p;
	strcpy(H[size].name,cus->name);
	strcpy(H[size].address,cus->address);
	strcpy(H[size].phn,cus->phn);
	strcpy(H[size].pincode,cus->pincode);
	
	shiftUp(size);
}
void insert_(struct queue ptr)
{
	size = size + 1;
	H[size].price = ptr.price;
	strcpy(H[size].name,ptr.name);
	strcpy(H[size].address,ptr.address);
	strcpy(H[size].phn,ptr.phn);
	strcpy(H[size].pincode,ptr.pincode);
	

	shiftUp(size);
}
struct queue extractMax()
{
	struct queue result = H[0];
 
	H[0] = H[size];
	size = size - 1;

	shiftDown(0);
	return result;
}



struct queue getMax()
{
	
	return H[0];
}

void _remove(int i)
{
	H[i] = getMax();
	
	shiftUp(i);

	extractMax();
}
void display_pqueue()
{
	int i=0;
	if(size==-1)
	{
		printf("\n\t\t\tQueue is Empty!!\n\n");
		return;
	}
	clear();
	printf("\n\t\t\t\t=========================================");
	printf("\n\t\t\t\t            Queue of Orders");
	printf("\n\t\t\t\t=========================================\n\n");
	printf("\n\nName\t\t    Address\t\t\t\t    Phone\t   Pincode\t  Price\n");
	printf("=======================================================================================================\n");
	while (i <= size) 
	{
		printf("%-20s%-40s%-15s%-10s\t%.2lf\n",H[i].name,H[i].address,H[i].phn,H[i].pincode,H[i].price);
		i++;
	}

}
void queue_writeinfile()
{
	FILE *f;
	f=fopen("queue_db.bin","wb");
	fwrite(&H,sizeof(struct queue),size+1,f);
	fclose(f);

}

void queue_readfromfile()
{
	FILE *f;
	struct queue temp;
	
	f=fopen("queue_db.bin","rb");
	while(fread(&temp,sizeof(struct queue),1,f))
	{
		insert_(temp);
	}
	fclose(f);
}

void ship_high_prio()
{
	if(size==-1)
	{
		printf("\n\t\t\tQueue is Empty!!\n\n");
		return;
	}
	clear();
	int ch;
	display_pqueue();
	printf("\n\t\tThe Highest Priority:\t%s",H[0].name);
	printf("\n\nPress 1 to Confirm Shippment: ");
	scanf("%d",&ch);
	if(ch==1)
	{
		struct queue ptr=extractMax();
		printf("\n\t\t\tShippment Confirmed for %s",ptr.name);
	}
	else
		printf("\n\t\t\tShippment Not Confirmed!!");
	printf("\n\n\t\tThank You!!\n\n");
}
