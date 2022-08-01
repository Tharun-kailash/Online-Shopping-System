// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// #include<conio.h>
// void clear()
// {
// 	system("cls");
// 	printf("\t\t\t\t\t\t### PVT Shopper Stop ###\n");
// 	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
// }
// #include "product.c"
// #include "customer.c"

struct cart
{
    struct product *pro;
    struct cart *next;
};
char _time[30];

char* get_time()
{
	time_t t;
	struct tm *l;
	t=time(NULL);
	l=localtime(&t);
	strcpy(_time,asctime(l));
	return _time;
}

struct payment
{
    char name[30];
    char phn[12];
    double amount;
    char time[30];
};

void display_payment()
{
	FILE *f;
	f=fopen("payment_db.bin","rb");
	struct payment *ptr=(struct payment*)malloc(sizeof(struct payment));
    clear();
    printf("\n\t\t============================================");
	printf("\n\t\t             Customer Payments               ");
	printf("\n\t\t============================================");
	printf("\n\nName\t\t\tPhone\t\t\tAmount\t\tPurchased Date/Time\n");
	printf("\n=====================================================================================\n");
	while(fread(ptr,sizeof(struct payment),1,f))
	{
		printf("\n%-20s\t%-20s\t%f\t%s",ptr->name,ptr->phn,ptr->amount,ptr->time);
	}
	printf("\n=====================================================================================\n");
	fclose(f);
}

void buy_invoice(struct product *pro,struct customer *cus,double p,int q)
{
    clear();
    FILE *f;
    f=fopen("payment_db.bin","ab");
    struct payment *ptr=(struct payment*)malloc(sizeof(struct payment));
    strcpy(ptr->time,get_time());
    printf("\n\t\t============================================");
	printf("\n\t\t                  Invoice              ");
	printf("\n\t\t============================================");
    printf("\n\n\t\tProduct Name\t\tQuantity\tPrice\n");
	printf("\n\t\t============================================");
    printf("\n\t\t%s\t\t%d\t\t%.2f",pro->name,q,pro->price);
	printf("\n\t\t============================================");
    printf("\n\t\t                                   Total: %.2f",p);
    printf("\n\t\t                         Delivery Charge: 50");
    p+=50;
    printf("\n\t\t                             Grand Total: %.2f",p);
	printf("\n\t\t============================================");
    printf("\n\t\tTime: %s",ptr->time);
    printf("\n\t\tShipping Address:\n");
    printf("\n\t\t%s\n\t\t%s\n\t\t\n\t\tPhn:%s\n\t\tPin:%s",cus->name,cus->address,cus->phn,cus->pincode);
    
    strcpy(ptr->name,cus->name);
    strcpy(ptr->phn,cus->phn);
    ptr->amount=p;
    insert_pqueue(cus,p);
    fwrite(ptr, sizeof(struct payment),1,f);
    fclose(f);
    printf("\n\t\t\tThank You For Shopping\n\n\n");
    // system("pause");
}

void buy_product(struct product *pro,struct customer *cus)
{
    int q,ch;
    double p=0;
    printf("Enter the Qunantity you want to Buy: ");
    scanf("%d",&q);
    while(q<=0)
    {
        printf("\n\t\tInvalid Qunantity\n\t\tEnter Again: ");
        scanf("%d",&q);
    }
    if(q<pro->quantity)
    {
        pro->quantity-=q;
    }
    else if (q>pro->quantity)
    {
        printf("\n\t\tOops, There is a Shortage of Product\n\t\tDo you mind buying %d of this product",pro->quantity);
        printf("\nPress 1 to Proceed: ");
        scanf("%d",&ch);
        if(ch!=1)
            return;
        q=pro->quantity;
        pro->quantity = 0;
    }    
    p=q*pro->price;
    printf("\n\n");
    printf("%s\n\n",cus->name);
    system("pause");
    buy_invoice(pro,cus,p,q);
}

void view_product(struct product *pro,struct customer *cus)
{
    clear();
    int ch;
    printf("\t\t\tProduct Details");
    printf("\n\t\t\t===============\n\n");
    printf("\n\t\tName: %s\n",pro->name);
    printf("\n\t\tBrand: %s\n",pro->brand);
    printf("\n\t\tDescription: %s\n",pro->desc);
    printf("\n\t\tPrice: %.2f\n",pro->price);
    printf("\n\t\tManufacture Date: %d/%d/%d\n",pro->mfd.day,pro->mfd.month,pro->mfd.year);
    if(pro->quantity>0)
    {
        printf("\n\t\t1.Buy Now\n\t\t0.Back");
        printf("\n\n\tEnter your Choice: ");
        scanf("%d",&ch);
        if(ch==1)
            buy_product(pro,cus);
        else if(ch==0)
            return;
        else
        {
            printf("\n\t\tInvalid Choice");
            view_product(pro,cus);
        }
    }
    else
    {
        printf("\n\t\tOops! Out of Stock\n");
    }
}

void search_product(struct customer *cus)
{
    int c=0,id;
	struct product *p=phead;
	
    clear();
	printf("\n\t\tProducts in Store:");
    printf("\n\t\tSN ID\tProduct Name\n");
    printf("\n\t\t==================\n");
    while(p!=NULL)
	{
		printf("\t\t%d. %d\t%-10s\n",++c,p->ID,p->name); 
        p=p->next;
	}
	printf("\n\t\t==================\n");
	printf("\nTotal products in our store is : %d\n\n\n",c);
    printf("Enter the ID of the product To View(Enter 0 For Back): ");
    scanf("%d",&id);
    if(id==0)
        return;
    p=binarysearch(id);
    if(p)
        view_product(p,cus);
    else
    {
        printf("\n\t\tProduct Not Found\n\n ");
    search_product(cus);
    }
    // system("pause");
}

// void main()
// {
//     readfromfile();
//     struct customer* ptr;
//     ptr=customer_login();
//     search_product(ptr);
// }