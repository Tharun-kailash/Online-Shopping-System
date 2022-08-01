struct data
{
	int day;
	int month;
	int year;
};
struct product
{
	int ID;
	char name[50];
	char brand[50];
	double price;
	int quantity;
	struct data mfd;
	char desc[500];
    struct product* next;
};

struct product *phead=NULL;
void add_product(struct product*);
#include "validations.c"

void display_product();

struct product * product_details_input()
{
   struct product * t=(struct product*)malloc(sizeof(struct product));

	printf("\t\t\tEnter product ID\n\t\t\t(Enter 0 for Back): ");
	t->ID=idvalidate();
	if(t->ID==0) return NULL;

	printf("\t\t\tEnter product Name: ");
	fflush(stdin);
	gets(t->name);
	
	printf("\t\t\tEnter product Brand: ");
	fflush(stdin);
	gets(t->brand);
	
	printf("\t\t\tEnter product price: ");
	t->price=pricevalidate();
	
	printf("\t\t\tEnter product quantity: ");
	t->quantity=quanvalidate();
	
	printf("\t\t\tEnter product MFD: ");
	get_date(t);
	
	printf("\t\t\tEnter product Description: ");
	fflush(stdin);
	gets(t->desc);
    return t;
}

void add_product(struct product *t)
{
	struct product *p=phead;

    if(t==NULL)
	    t=product_details_input();
	if(t==NULL) return;

	if(phead==NULL)
	{
		t->next=phead;
		phead=t;
	}
	else
	{
		while(p->next!=NULL)
    	{
			p=p->next;
        }
        p->next=t;
        t->next=NULL;
	}	
	no_of_products++;
}

void writeinfile()
{
	FILE *f;
	struct product *p=phead;
	f=fopen("products_DB.bin","wb");
	while(p!=NULL)
	{
		fwrite(p,sizeof(struct product),1,f);
		p=p->next;
	}
	fclose(f);
}

void readfromfile()
{
	FILE *f;
	struct product *temp=(struct product*)malloc(sizeof(struct product));
	f=fopen("products_DB.bin","rb");
	while(fread(temp,sizeof(struct product),1,f))
	{
		add_product(temp);	
		temp=(struct product*)malloc(sizeof(struct product));
	}
	fclose(f);
}

void del1()
{
	struct product *temp;
	temp=phead;
	phead=phead->next;
	free(temp);
}

void del2()
{
	struct product *prev,*temp;
	temp=phead;
	while(temp->next!=0)
	{
		prev=temp;
		temp=temp->next;
	}
	if(temp==phead)
		phead=0;
	else
		prev->next=0;
	free(temp);
}

void delete_product()
{
	clear();
	display_product();
	int id,ch;
	struct product *cur,*pre;
	if(phead==NULL)
	{
		printf("List is empty");
		return;
	}
	printf("Enter ID to delete that product(Enter 0 For Back): ");
	scanf("%d",&id);
	if(id==0) return;
	cur=binarysearch(id);
	if(!cur)
	{
		printf("%d is Not found\n\n",id);
		delete_product();
	}
	printf("\n\t\tAre you Sure To Delete %s (Press 1):",cur->name);
	scanf("%d",&ch);
	if(ch==0)
		return;
	if(id==phead->ID)
	{
		del1();
		return;
	}
	else if(cur->next==NULL)
	{
		del2();
		return;
	}
	
	else
	{
		struct product* temp=phead;
		while(temp->ID!=id)
		{
			pre=temp;
			temp=temp->next;
		}
		pre->next=cur->next;
		free(cur);
	}
}

struct product* modify_a_product(struct product *cur)
{
	int ch;
	while(1)
	{
		clear();
		printf("\n\t\t=========================================");
		printf("\n\t\t              Modify Menu                ");
		printf("\n\t\t=========================================\n\n");
		
		printf("\n\t\t1. Name\n\t\t2. Brand\n\t\t3. Price\n\t\t4. Quantity\n\t\t5. MFD\n\t\t6.Description\n\t\t0. Exit");
		printf("\n\nEnter your Choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("\nOld Name : %s\n\n",cur->name);
				printf("Enter new Name:");
				fflush(stdin);
				gets(cur->name);
				break;
			case 2:
				printf("\nOld Brand : %s\n\n",cur->brand);
				printf("Enter new Brand:");
				fflush(stdin);
				gets(cur->brand);
				break;
			case 3:
				printf("\nOld Price : %f\n\n",cur->price);
				printf("Enter new Price:");
				cur->price=pricevalidate();
				break;
			case 4:
				printf("\nOld Quantity : %d\n\n",cur->quantity);
				printf("Enter new Quantity:");
				cur->quantity=quanvalidate();
				break;
			case 5:
				printf("\nOld MFD : %d/%d/%d\n\n",cur->mfd.day,cur->mfd.month,cur->mfd.year);
				printf("Enter new MFD:");
				get_date(cur);
				break;
			case 6:
				printf("\nOld Description : %s\n\n",cur->desc);
				printf("Enter new Description:");
				fflush(stdin);
				gets(cur->desc);
				break;
			case 0:
				return cur;
		}
		system("pause");
	}
}

void modify_product()
{
	clear();
	int id;
	double pre;        //    pre for price
	char pName[50];
	int nid; int nq;     //   pName for new name
	if (phead == NULL)
	{
	    printf("List is empty");
    }
    else
	{    
	    display_product();
		printf("\n\nEnter ID to modify product(Enter 0 For Back): ");
		scanf("%d",&id);
		if(id == 0)
			return;
		struct product *cur;

	    cur=binarysearch(id);
		if(cur)
    	{
			cur=modify_a_product(cur);
		}
	    else
    	{
			printf("%d is Not found\n\n",id);
			system("pause");
			modify_product();
		}
	}
}

void display_product()
{

	struct product *p=phead;
	printf("\n\t\t\t\t=========================================");
	printf("\n\t\t\t\t                Products                 ");
	printf("\n\t\t\t\t=========================================\n\n");

	printf("\t  ===========================================================================================\n");
	printf("\t\tID\tProduct Name\tBrand\t\tPrice(Rs.)\tQuantity\tMFD\n");
	printf("\t  ===========================================================================================\n");
	while(p!=NULL)
	{
		if(p->quantity>0)
			printf("\t\t%d\t%-10s\t%-10s\t%8.2f\t%d\t\t%d/%d/%d\n",p->ID,p->name,p->brand,p->price,p->quantity,p->mfd.day,p->mfd.month,p->mfd.year); //    call   check func and pass quantity
		else
			printf("\t\t%d\t%-10s\t%-10s\t%8.2f\tOut Of Stock!\t%d/%d/%d\n",p->ID,p->name,p->brand,p->price,p->mfd.day,p->mfd.month,p->mfd.year); //    call   check func and pass quantity
		p=p->next;
		
	}
	printf("\t  ===========================================================================================\n");
	printf("\nTotal products in our store is : %d\n\n\n",no_of_products);

}

// void main()
// {
// 	readfromfile();
//     product_menu();
// 	writeinfile();
// }