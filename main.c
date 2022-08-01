#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
void clear()
{
	system("cls");
	printf("\t\t\t\t\t\t### PVT Shopper Stop ###\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}
int no_of_products=0;
#include "product.c"
#include "customer.c"
#include "p-queue.c"
#include "interface.c"


int admin_login()
{
	char name[20];
	char pass[20];
	clear();
	printf("\n\t\t============================================");
	printf("\n\t\t              Admin Portal              ");
	printf("\n\t\t============================================");
	printf("\n\n\t\tEnter the Username(Enter 0 For Back): ");
	fflush(stdin);
	gets(name);
	if(name[0]=='0') return 0;
	if (!strcmp(name, "admin"))
	{
		strcpy(pass,get_pwd());
		if(!strcmp(pass,"admin123"))
		{
			printf("\n\t\tLog in Successful\n\n");
			system("pause");
			return 1;
		}
		else
		{
			printf("\n\t\tPassword incorrect\n\n");
			system("pause");
			admin_login();
		}
	}
	else
	{
		printf("\n\t\tUsername incorrect\n\n");
		system("pause");
		admin_login();
	}

}

void admin_menu()
{
	int ch;
	int x,n;
	if(!admin_login()) return;
	do 
	{	
		clear();
		
		printf("\n\t\t============================================");
		printf("\n\t\t                Admin Portal              ");
		printf("\n\t\t============================================");
	
		printf("\n\t\t     Enter 1 - ADD a New product    ");
		printf("\n\t\t     Enter 2 - DISPLAY all Products   ");
		printf("\n\t\t     Enter 3 - MODIFY Existing Product");
		printf("\n\t\t     Enter 4 - Delete a Particular Product Item");
		printf("\n\t\t     Enter 5 - Display Payment History");
		printf("\n\t\t     Enter 6 - Display all Customer");
		printf("\n\t\t     Enter 7 - Delete a Particular Customer Item");
		printf("\n\t\t     Enter 8 - Display Queue");
		printf("\n\t\t     Enter 9 - Ship the Order(Highest Priority)");
		printf("\n\t\t     Enter 10- Display Customer Feedbacks");
		printf("\n\t\t     Enter 0 - Back");
		printf("\n\nEnter Your choice >>>");
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1:
				clear();
				printf("\n\t\t============Product Addition============\n\n");
				add_product(NULL);
				heapsort(phead,no_of_products);
				break;
			case 2:
				clear();
    			display_product();
    			break;
			case 3:
				clear();
				modify_product();
				break;
			case 4:
				delete_product();
				break;
			case 5:
				display_payment();
				break;
			case 6:
				display_customer();
				break;
			case 7:
				delete_customer();
				break;
			case 8:
				display_pqueue();
				break;
			case 9:
				ship_high_prio();
				break;
			case 10:
				clear();
				printf("\n\t\t\t=========================================");
				printf("\n\t\t\t           Customer Profile");
				printf("\n\t\t\t=========================================\n\n");
				printf("\n\t\t=========================================");
				printf("\n\t\tName\t\tFeedback\n");
				printf("\n\t\t=========================================");
				display_feedback(root);
				break;
			case 0:
				return;
			default: 
				printf("Invalid Choice");
		}
		printf("\n\n");
		system("pause");
		
	}while(1);
}

void customer_menu(struct customer* ptr)
{
    int ch;
	int x,n;
	if(ptr==NULL)
		ptr=customer_login();
		if(ptr==NULL) return;
	do 
	{	
		clear();
		printf("\n\t\t============================================");
		printf("\n\t\t              Customer Portal               ");
		printf("\n\t\t============================================");
		printf("\n\t\t     Enter 1 - My Profile");
		printf("\n\t\t     Enter 2 - Buy Products");
		printf("\n\t\t     Enter 3 - Modify My Profile");
		printf("\n\t\t     Enter 4 - Delete My Profile");
		printf("\n\t\t     Enter 5 - Give Feedback/Review");
		printf("\n\t\t     Enter 0 - Log Out");
		printf("\n\nEnter Your choice >>>");
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1:
				clear();
				printf("\n\t\t\tName: %s\n\t\t\tAddress: %s\n\t\t\tMobile: %s\n\t\t\tPincode: %s\n\n\n",ptr->name,ptr->address,ptr->phn,ptr->pincode);
				break;
			case 2:
				clear();
				search_product(ptr);
				break;
			case 3:
				modify_a_customer(ptr);
				break;
			case 4:
				if(delete_profile(ptr))
					break;
				else
					return;
			case 5:
				add_feedback(ptr->name);
				break;
			case 0:
				return;
			default: 
				printf("Invalid Choice");
		}
		system("pause");
	}while(1);
}

// void customer_main()
// {
// 	int ch;
// 	struct customer* ptr;
// 	clear();
// 	printf("\n\t\t============================================");
// 	printf("\n\t\t              Customer Portal               ");
// 	printf("\n\t\t============================================");
// 	printf("\n\t\t     Enter 1 - Sign Up");
// 	printf("\n\t\t     Enter 2 - log In");
// 	printf("\n\t\t     Enter 0 - Back");
// 	printf("\nEnter your Choice: ");
// 	scanf("%d", &ch);

// 	switch(ch)
// 	{
// 		case 1:
// 			ptr=add_customer(NULL);
// 			if (ptr==NULL)
// 				return;
// 			customer_menu(ptr);
// 			break;
// 		case 2:
// 			customer_menu(NULL);
// 			break;
// 		case 0:
// 			return;
// 		default: 
// 			printf("Invalid Choice");
// 			customer_main();
// 	}
		
// }

void menu()
{
	int ch;
	while(1)
	{
		clear();
		printf("\n\t\t============================================");
		printf("\n\t\t                Main Portal                  ");
		printf("\n\t\t============================================");
		printf("\n\t\t     Enter 1 - Customer");
		printf("\n\t\t     Enter 2 - Admin");
		printf("\n\t\t     Enter 0 - Back");
		printf("\nEnter your Choice: ");
		scanf("%d", &ch);

		switch(ch)
		{
			case 1:
				customer_menu(NULL);
				break;
			case 2:
				admin_menu();
				break;
			case 0:
				return;
			default: 
				printf("Invalid Choice");
		}
	system("pause");
	}
}

void main()
{
    readfromfile();
    cus_readfromfile();
	queue_readfromfile();
	readfeedback();
    menu();
    writeinfile();
    cus_writeinfile();
	queue_writeinfile();
	write_feedback(root);
}