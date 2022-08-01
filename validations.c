int count(int n)
{
	int c=0;
	while(n>0)
	{
		c++;
		n=n/10;
	}
	return c;
}
struct product *getTail(struct product *cur)
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

struct product *partition(struct product *phead, struct product *end, struct product **newHead, struct product **newEnd)
{
    struct product *pivot = end;
    struct product *prev = NULL, *cur = phead, *tail = pivot;
 
    while (cur != pivot)
    {
        if (cur->ID < pivot->ID)
        {
            if ((*newHead) == NULL)
                (*newHead) = cur;
 
            prev = cur;  
            cur = cur->next;
        }
        else // If cur struct product is greater than pivot
        {
            if (prev)
                prev->next = cur->next;
            struct product *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
 
    if ((*newHead) == NULL)
        (*newHead) = pivot;
 
    (*newEnd) = tail;
 
    return pivot;
}

struct product *quickSortRecur(struct product *phead, struct product *end)
{
    if (!phead || phead == end)
        return phead;
 
    struct product *newHead = NULL, *newEnd = NULL;
 
    struct product *pivot = partition(phead, end, &newHead, &newEnd);
 
    if (newHead != pivot)
    {
        struct product *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
 
        newHead = quickSortRecur(newHead, tmp);
 
        tmp = getTail(newHead);
        tmp->next =  pivot;
    }
 
    pivot->next = quickSortRecur(pivot->next, newEnd);
 
    return newHead;
}
 
void quickSort(struct product **headRef)
{
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
    return;
}

void swap_arr(struct product* arr[],int pos1,int pos2)
{
    struct product* temp;
    temp=arr[pos1];
    arr[pos1]=arr[pos2];
    arr[pos2]=temp;
}


void maxHeapify(struct product* data[],int parent,int last_index)
{
    int left;
    int right;
    left=parent*2+1;
    right=parent*2+2;
    if(left>last_index) return;

    if(left==last_index)
    {
        if(data[left]->ID > data[parent]->ID)
            swap_arr(data,parent,left);
        return;
    }
    if(data[parent]->ID > data[left]->ID && data[parent]->ID > data[right]->ID)
        return;
    if(data[left]->ID > data[right]->ID)
    {
        swap_arr(data,parent,left);
        maxHeapify(data,left,last_index);
    }
    else
    {
        swap_arr(data,parent,right);
        maxHeapify(data,right,last_index);
    }
}
void heapsort_main(struct product* arr[],int arr_size)
{
    
    int parent;
    int last_index;
    for(last_index=arr_size-1;last_index>=0;last_index--)
    {
        for(parent=(arr_size/2)-1;parent>=0;parent--)
        {
            maxHeapify(arr,parent,last_index);
        }
        swap_arr(arr,0,last_index);
    }
}
void heapsort(struct product* ptr,int length)
{
    struct product *arr[length],*temp=ptr;
    for(int i=0;i<length;i++)
    {
        arr[i]=temp;
        temp=temp->next;
    }
    heapsort_main(arr,length);
    ptr = phead;
    while (ptr != NULL) 
    {
        phead = ptr->next;
        ptr=NULL;
        ptr = phead;
    }
    no_of_products=0;
    for(int i=0;i<length;i++)
        add_product(arr[i]);
  
}




struct product* middle(struct product* s,struct product* l)
{
	if(s==NULL) return NULL;
	
	struct product *sl=s,*f=s->next;
	
	while(f!=l)
	{
		f=f->next;
		if(f!=l)
		{
			sl=sl->next;
			f=f->next;
		}
	}
	return sl;
}

struct product* binarysearch(int id)
{
	struct product* start = phead;
    struct product* last = NULL;
 
    do
    {
        struct product* mid = middle(start, last);
        if (mid == NULL)
            return NULL;
        if (mid -> ID == id)
            return mid;
		else if (mid -> ID < id)
            start = mid -> next;
        else
            last = mid;
    }while (last == NULL || last != start);
    return NULL;
}

int idvalidate()
{
	int id;
	scanf("%d",&id);
	if(id == 0) return id;
	if(!binarysearch(id))
	{
		if(count(id)==4)
			return id;
		else
		{
			printf("\t\t\tInvalid Id!!\n\t\t\tEnter Again:");
			idvalidate();
		}
	}
	else
	{
		printf("\t\t\tDuplicate Id!!\n\t\t\tEnter Again:");
		idvalidate();
	}
}

double pricevalidate()
{
	double p;
	scanf("%lf",&p);
	if(!(p<=0))
		return p;
	else
	{
		printf("\t\t\tInvalid Price!!\n\t\t\tEnter Again:");
		pricevalidate();
	}	
}

int quanvalidate()
{
	int q;
	scanf("%d",&q);
	if(!(q<=0))
		return q;
	else
	{
		printf("\t\t\tInvalid Quantity!!\n\t\t\tEnter Again:");
		quanvalidate();
	}
}

void get_date(struct product *p)
{
	int dd,mm,yy;
    scanf("%d/%d/%d",&dd,&mm,&yy);
     
    
    if(yy>=1900 && yy<=2021)
    {
        if(yy==2021)
        {
        	if(mm>10)
        	{
        		printf("\t\t\tInvalid Date!!\n\t\t\tEnter Again:");
				get_date(p);
			}
		}
        if(mm>=1 && mm<=12)
        {
            
            if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12))
                {
                	p->mfd.day=dd;
                	p->mfd.month=mm;
                	p->mfd.year=yy;
                	return ;
                }
            else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11))
                {
                	p->mfd.day=dd;
                	p->mfd.month=mm;
                	p->mfd.year=yy;
                	return ;
                }
            else if((dd>=1 && dd<=28) && (mm==2))
                {
                	p->mfd.day=dd;
                	p->mfd.month=mm;
                	p->mfd.year=yy;
                	return ;
                }
            else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0)))
                {
                	p->mfd.day=dd;
                	p->mfd.month=mm;
                	p->mfd.year=yy;
                	return ;
                }
            else
                {
					printf("\t\t\tInvalid Date!!\n\t\t\tEnter Again:");
					get_date(p);
            	}
        }
        else
        {
            printf("\t\t\tInvalid Date!!\n\t\t\tEnter Again:");
            get_date(p);
        }
    }
    else
    {
        printf("\t\t\tInvalid Date!!\n\t\t\tEnter Again:");
        get_date(p);
    }
}

char enpass[30];

char* encrypt(char *user,char *pass)
{
    int len=strlen(user),i;
    for(i=0;i<strlen(pass);i++)
    {
        enpass[i]=pass[i]-len;
    }
    enpass[i]='\0';    
    return enpass;
}

struct feedback 
{
    int key;
    char feedback[100];
    char name[30];
    struct feedback *left;
    struct feedback *right;
    int height;
};

struct feedback *root = NULL;
int max(int a, int b);


int height(struct feedback *N) 
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) 
{
    return (a > b) ? a : b;
}


struct feedback *newfeedback(char* fd, char* name,int key) 
{
    struct feedback *node = (struct feedback *)malloc(sizeof(struct feedback));
    node->key = key;
    strcpy(node->feedback,fd);
    strcpy(node->name,name);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}


struct feedback *rightRotate(struct feedback *y) 
{
    struct feedback *x = y->left;
    struct feedback *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}


struct feedback *leftRotate(struct feedback *x) 
{
    struct feedback *y = x->right;
    struct feedback *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}


int getBalance(struct feedback *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


struct feedback *insertfeedback(struct feedback *node,char* fd,char* name, int key) 
{
  
    if (node == NULL)
        return (newfeedback(fd,name,key));

    if (key < node->key)
        node->left = insertfeedback(node->left,fd,name, key);
    else if (key > node->key)
        node->right = insertfeedback(node->right,fd,name, key);
    else
        return node;

    
    
    node->height = 1 + max(height(node->left),
                height(node->right));

    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

struct feedback *minValuefeedback(struct feedback *node) 
{
    struct feedback *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}


struct feedback *deletefeedback(struct feedback *root, int key) 
{
  
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deletefeedback(root->left, key);

    else if (key > root->key)
        root->right = deletefeedback(root->right, key);

    else {
        if ((root->left == NULL) || (root->right == NULL)) {
        struct feedback *temp = root->left ? root->left : root->right;

        if (temp == NULL) {
            temp = root;
            root = NULL;
        } else
            *root = *temp;
        free(temp);
        } else {
        struct feedback *temp = minValuefeedback(root->right);

        root->key = temp->key;

        root->right = deletefeedback(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    
    
    root->height = 1 + max(height(root->left),
                height(root->right));

    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


void display_feedback(struct feedback *root) 
{
    if (root != NULL) {
        display_feedback(root->left);
        printf("\n\t\t%s\t%s ", root->name,root->feedback);
        display_feedback(root->right);
    }
}

void add_feedback(char* name)
{
    char *feedBack;
    printf("Enter your Feedback: ");
    feedBack=(char*)malloc(100*sizeof(char));
    fflush(stdin);
    gets(feedBack);
    root = insertfeedback(root, feedBack,name,strlen(feedBack));
    feedBack=NULL;
}
void _add_feedback(char* name,char* fd)
{
    root = insertfeedback(root, fd,name,strlen(fd));
}
struct stack
{
    struct feedback* ptr;
    struct stack* link;
};
 
struct stack* top;
 
void push(struct feedback* ptr)
{
     
    struct stack* temp;
    temp = (struct stack*)malloc(sizeof(struct stack));
 
 
    temp->ptr = ptr;
 
    temp->link = top;
 
    top = temp;
}
 
int isEmpty()
{
    return top == NULL;
}
 
struct feedback* peek()
{
     
    if (!isEmpty())
        return top->ptr;
    else
        exit(1);
}
 
void pop()
{
    struct stack* temp;
 
    if (top == NULL)
    {
        ;
    }
    else
    {
         
        temp = top;
 
        top = top->link;
 
        temp->link = NULL;
 
        free(temp);
    }
}
 

void writefeedback(struct feedback* p)
{
    FILE *f;
	f=fopen("feedback_DB.bin","wb");
	fwrite(p,sizeof(struct feedback),1,f);
	fclose(f);
}
void write_feedback()
{
    FILE *f;
	f=fopen("feedback_DB.bin","wb");
	
	
    struct stack* s;
	struct feedback *curr;
    curr=root;
	while(curr!=NULL || top!=NULL)
	{
		while(curr!=NULL)
		{
			push(curr);
			curr=curr->left;
		}
		curr=peek();
		pop();
		fwrite(curr,sizeof(struct feedback),1,f);
		curr=curr->right;
	}
    fclose(f);
}
void readfeedback()
{
	FILE *f;
	struct feedback *temp=(struct feedback*)malloc(sizeof(struct feedback));
	f=fopen("feedback_DB.bin","rb");
	while(fread(temp,sizeof(struct feedback),1,f))
	{
        _add_feedback(temp->name,temp->feedback);
        printf("%s-%s",temp->name,temp->feedback);
		temp=(struct feedback*)malloc(sizeof(struct feedback));
	}
	fclose(f);
}