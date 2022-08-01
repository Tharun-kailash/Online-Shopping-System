// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// #include<conio.h>
struct customer
{
    char name[30];
    char address[50];
    char phn[12];
	char pincode[7];
	char username[11];
	char pass[11];
	struct customer *link;
};

struct customer *chead = NULL;
char phn[12];
char password[15];
char uname[15];
char name[30];

// void clear()
// {
// 	system("cls");
// 	printf("\t\t\t\t\t\t### PVT Shopper Stop ###\n");
// 	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
// }
int dup_phn()
{
	struct customer *ptr=chead;
	while(ptr!=NULL)
	{
		if(!strcmp(ptr->phn,phn))
			return 1;
		ptr=ptr->link;
	}
	return 0;
}
char* phnvalidate()
{
	fflush(stdin);
	gets(phn);
	int ch;
	if(strlen(phn)!=10)
	{
		printf("\t\t\tInvalid Phone Number!!\n\t\t\tEnter Again:");
		phnvalidate();
	}
	else if(phn[0]<6)
	{
		printf("\t\t\tInvalid Phone Number!!\n\t\t\tEnter Again:");
		phnvalidate();
	}
	else if(dup_phn())
	{
		printf("\t\t\tInvalid Phone Number!!\n\t\t\tEnter Again:");
		phnvalidate();
	}
	else
		return phn;
}

struct customer* middle_customer(struct customer* s,struct customer* l)
{
	if(s==NULL) return NULL;
	
	struct customer *sl=s,*f=s->link;
	
	while(f!=l)
	{
		f=f->link;
		if(f!=l)
		{
			sl=sl->link;
			f=f->link;
		}
	}
	return sl;
}
struct customer* binarysearch_customer(char name[])
{
	struct customer* start = chead;
    struct customer* last = NULL;
 
    do
    {
        struct customer* mid = middle_customer(start, last);
        if (mid == NULL)
            return NULL;
        if (!strcmp(mid->name, name))
            return mid;
		else if (strcmp(mid->name, name)>0)
            start = mid -> link;
        else
            last = mid;
    }while (last == NULL || last != start);
    return NULL;
}
struct customer* binarysearch_customer_uname(char name[])
{
	struct customer* start = chead;
    struct customer* last = NULL;
 
    do
    {
        struct customer* mid = middle_customer(start, last);
        if (mid == NULL)
            return NULL;
        if (!strcmp(mid->username, name))
            return mid;
		else if (strcmp(mid->username, name)>0)
            start = mid -> link;
        else
            last = mid;
    }while (last == NULL || last != start);
    return NULL;
}

char* get_pwd()
{
	fflush(stdin);
	printf("\n\t\tEnter password:");
    int p=0;
    do{
        password[p]=getch();
        if(password[p]!='\r')
		{
            printf("*");
        }
        p++;
    }while(password[p-1]!='\r');
    password[p-1]='\0';

    if(strlen(password)>10)
	{
		printf("\n\t\t\tPassword Invalid!\n:");
		get_pwd();
	}
	else
    	return password;
}
char* get_username()
{
	fflush(stdin);
	gets(uname);
	if(binarysearch_customer_uname(uname))
	{
		printf("\n\t\t\tUsername Already Exists!\n\n\t\t\tEnter again:");
		get_username();
	}
	else if(strlen(uname)>10)
	{
		printf("\n\t\t\tUsername Invalid!\n\n\t\t\tEnter again:");
		get_username();
	}
	else
		return uname;
}
char* get_name()
{
	fflush(stdin);
	gets(name);
	if(binarysearch_customer(name))
	{
		printf("\n\t\t\tName Already Exists!\n\n\t\t\tEnter again:");
		get_name();
	}
	else
		return name;
}

struct customer* customer_details_input()
{
    struct customer *cus=(struct customer *)malloc(sizeof(struct customer));
	clear();
	printf("\n\t\t\t=========================================");
	printf("\n\t\t\t           Customer Sign Up");
	printf("\n\t\t\t=========================================\n\n");
	printf("\t\t\tEnter Username(Enter 0 For Back): ");
	strcpy(cus->username, get_username());
	if(cus->username[0]=='0') return NULL;
	fflush(stdin);
	strcpy(cus->pass,encrypt(cus->username,get_pwd()));
	printf("\n\n");
	
	system("pause");
	clear();
	printf("\n\t\t\t=========================================");
	printf("\n\t\t\t           Customer Profile\n");
	printf("\n\t\t\t=========================================\n\n");
    
	printf("\t\t\tEnter Your Name\n\t\t\t(Enter 0 to Back): ");
    fflush(stdin);
    strcpy(cus->name,get_name());
    if(cus->name[0]=='0') return NULL;

    printf("\t\t\tEnter Your Address: ");
    fflush(stdin);
    gets(cus->address);

    printf("\t\t\tEnter Your Mobile Number: ");
    fflush(stdin);
    strcpy(cus->phn,phnvalidate());

    printf("\t\t\tEnter Your Pincode: ");
    fflush(stdin);
    gets(cus->pincode);
    
    return cus;
}
struct customer* add_customer(struct customer *ptr)
{
    struct customer *p=chead;

    if(ptr==NULL)
	    ptr=customer_details_input();
	if(ptr==NULL) return NULL;

	if(chead==NULL)
	{
		ptr->link=chead;
		chead=ptr;
	}
	else
	{
		while(p->link!=NULL)
    	{
			p=p->link;
        }
        p->link=ptr;
        ptr->link=NULL;
	}	
	return ptr;
}

void cus_writeinfile()
{
	FILE *f;
	struct customer *p=chead;
	f=fopen("customer_db.bin","wb");
	while(p!=NULL)
	{
		fwrite(p,sizeof(struct customer),1,f);
		p=p->link;
	}
	fclose(f);
}
void cus_readfromfile()
{
	FILE *f;
	struct customer *temp=(struct customer*)malloc(sizeof(struct customer));
	f=fopen("customer_db.bin","rb");
	while(fread(temp,sizeof(struct customer),1,f))
	{
		add_customer(temp);	
		temp=(struct customer*)malloc(sizeof(struct customer));
	}
	fclose(f);
}

void display_customer()
{  
	clear();
	printf("\n\t\t\t\t=========================================");
	printf("\n\t\t\t\t               Customers");
	printf("\n\t\t\t\t=========================================\n\n");
	struct customer *ptr = chead;
	if (ptr==NULL)
	printf("No Customer is There\n");
	else
	{
	
	printf("\n\nName\t\t    Address\t\t\t\t    Phone\t   Pincode\n");
	printf("=======================================================================================================\n");
		while( ptr !=NULL)
		{
			printf("%-20s%-40s%-15s%-10s\n",ptr->name,ptr->address,ptr->phn,ptr->pincode);
			// printf("Username: %s\tPassword: %s\n",ptr->username,ptr->pass);
			ptr= ptr->link;  
		}
	}
	printf("\n\n");
}

void display_profile()
{
	clear();
	printf("\n\t\t\t\t=========================================");
	printf("\n\t\t\t\t         Profile of a Customer");
	printf("\n\t\t\t\t=========================================\n\n");
	char name[30];
	fflush(stdin);
	printf("\n\t\t\tEnter Your Name: ");
	gets(name);
	struct customer * ptr;
	ptr=binarysearch_customer(name);
	if(ptr)
	{
		printf("\n\t\t\tName: %s\n\t\t\tAddress: %s\n\t\t\tMobile: %s\n\t\t\tPincode: %s\n\n\n",ptr->name,ptr->address,ptr->phn,ptr->pincode);
	}
	else printf("Customer Not found\n\n");
}

struct customer* modify_a_customer(struct customer *cur)
{
	int ch;
	while(1)
	{
		clear();
		printf("\n\t\t=========================================");
		printf("\n\t\t              Modify Menu                ");
		printf("\n\t\t=========================================\n\n");
		
		printf("\n\t\t1. Name\n\t\t2. Username\n\t\t3. Password\n\t\t4. Address\n\t\t5. Mobile Number\n\t\t6. Pin Code\n\t\t0. Exit");
		printf("\n\nEnter your Choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("\nOld Name : %s\n\n",cur->name);
				printf("Enter new Name:");
				fflush(stdin);
				strcpy(cur->name,get_name());
				break;
			case 2:
				printf("\nOld UserName : %s\n\n",cur->username);
				printf("Enter new UserName:");
				fflush(stdin);
				strcpy(cur->username, get_username());
				break;
			case 3:
				printf("\nOld PassWord : %s\n\n",cur->pass);
				printf("Enter new PassWord:");
				fflush(stdin);
				strcpy(cur->pass,encrypt(cur->username,get_pwd()));
				break;
			case 4:
				printf("\nOld Address : %s\n\n",cur->address);
				printf("Enter new Brand:");
				fflush(stdin);
				gets(cur->address);
				break;
			case 5:
				printf("\nOld Mobile Numnber : %s\n\n",cur->phn);
				printf("Enter new Price:");
				fflush(stdin);
				strcpy(cur->phn,phnvalidate());
				break;
			case 6:
				printf("\nOld Pincode : %s\n\n",cur->pincode);
				printf("Enter new Quantity:");
				fflush(stdin);
				gets(cur->pincode);
				break;
			case 0:
				return cur;
		}
		printf("\n\n");
		system("pause");
	}
}



void del1_cus()
{
	struct customer *temp;
	temp=chead;
	chead=chead->link;
	free(temp);
}

void del2_cus()
{
	struct customer *prev,*temp;
	temp=chead;
	while(temp->link!=0)
	{
		prev=temp;
		temp=temp->link;
	}
	if(temp==chead)
		chead=0;
	else
		prev->link=0;
	free(temp);
}

void delete_customer()
{
	clear();
	display_customer();
	int ch;
	char name[30];
	struct customer *cur,*pre;
	if(chead==NULL)
	{
		printf("List is empty");
		return;
	}
	printf("Enter name to delete that customer(Enter 0 For Back): ");
	fflush(stdin);
	gets(name);

	if(name[0]=='0') return;
	cur=binarysearch_customer(name);
	if(!cur)
	{
		printf("%s is Not found\n\n",cur->name);
		delete_customer();
	}
	printf("\n\t\tAre you Sure To Delete %s (Press 1):",cur->name);
	scanf("%d",&ch);
	if(ch==0)
		return;
	if(!strcmp(cur->name,chead->name))
	{
		del1_cus();
		return;
	}
	else if(cur->link==NULL)
	{
		del2_cus();
		return;
	}
	
	else
	{
		struct customer* temp=chead;
		while(strcmp(temp->name,cur->name))
		{
			pre=temp;
			temp=temp->link;
		}
		pre->link=cur->link;
		free(cur);
	}
}

int delete_profile(struct customer* cur)
{
	struct customer *pre;
	int ch;
	printf("\n\t\tAre you Sure To Delete %s (Press 1):",cur->name);
	scanf("%d",&ch);
	if(ch==0)
		return 1;
	if(!strcmp(cur->name,chead->name))
	{
		del1_cus();
		return 0;
	}
	else if(cur->link==NULL)
	{
		del2_cus();
		return 0;
	}
	
	else
	{
		struct customer* temp=chead;
		while(strcmp(temp->name,cur->name))
		{
			pre=temp;
			temp=temp->link;
		}
		pre->link=cur->link;
		free(cur);
	}
	return 0;
}

struct customer* customer_login()
{
	char name[30],pass[30],_pass[30];
	int ch;
	struct customer *ptr;
	printf("\n\t\t============================================");
	printf("\n\t\t           	   Login Page                ");
	printf("\n\t\t============================================");
	while(1) 
	{
		printf("\n\n\t\tUser-ID:");
		fflush(stdin);
		gets(name);
		if(name[0]=='0') return NULL;
		ptr=binarysearch_customer_uname(name);
		
		if(ptr)
		{
			strcpy(pass,get_pwd());
			strcpy(_pass,encrypt(ptr->username,pass));
			if(!strcmp(ptr->pass,_pass))
			{
				printf("\n\t\tLog in successfull\n\n");
				system("pause");
				return ptr;
			}
			else
				printf("\n\t\tPassword Wrong\n\t\tLogin failed");
		}
		else
			{
				printf("\n\t\tUser not found\n\nPress 1 to continue Sign Up: ");
				scanf("%d",&ch);
				if(ch==1)
					ptr=add_customer(NULL);
					if(ptr==NULL) return NULL;
				else
					return NULL;
			}
	}
	
}

// void main()
// {
//     cus_readfromfile();
//     // add_customer(NULL);
//     display_customer();
//     // delete_customer();
//     // display_customer();
// 	// struct customer *cus = binarysearch_customer("Vignaraj");
// 	// printf("\nFound:%s\n",cus->name);
//     struct customer * ptr;
// 	ptr=customer_login();
// 	printf("\n\t\tName: %s\n\t\tAddress: %s\n\t\tMobile: %s\n\t\tPincode: %s\n\n\n",ptr->name,ptr->address,ptr->phn,ptr->pincode);
// 	cus_writeinfile();
// }