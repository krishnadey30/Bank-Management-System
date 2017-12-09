#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "043-assign12.c"

/* linked list transaction details */
typedef struct llist
{
	long int accountno;
	char string1[100],string2[100];
	struct llist *next;
}LLIST;

int whiledelete=5;
USER_DETAIL *p;
USER_DETAIL *headfordel;

//creating stacks  using linked list 
LLIST *createlinkedlist(LLIST *llhead)
{

	FILE* fh;
	fopen_s(&fh,"FILE1.txt", "r");
	const size_t line_size = 300;
	char* line = malloc(line_size);
	int flag=0,flag1=0;
	LLIST *temp,*temp1,*temp2;
	char string[100];
	temp1=llhead;
	
	while (fgets(line, line_size, fh) != NULL) 			// scanning each line from file 
	{
		strcpy(string,line);
		if(strlen(line)==11)							//for storing account no
		{
			flag=1;	
			//temp=(LLIST *)malloc(sizeof(LLIST));
			llhead->accountno=atoi(line);	
		}
		else if(flag == 1)								//for storing the properties of transaction type
		{
			strcpy(llhead->string1,line);
			flag=0;
	    	flag1=1;
		}
		else if(flag1 == 1)			
		{
	    	strcpy(llhead->string2,line);
	    	temp1=(LLIST *)malloc(sizeof(LLIST));		//dynamic memory allocation 
	    	temp1->next=llhead;
	    	llhead=temp1;
	    	//temp1=temp;
	    	flag1=0;									// making flag and flag1 '0'
	    	flag=0;
		}

	}
	
	fclose(fh);											// closing transaction file
	return llhead;										// returing the head pointer of linked list
}



/* deletion of nodes with given account no*/
LLIST* del(LLIST *t,long int n)
{
	int i,c=1;
	long int e;
	e=n;
	LLIST *in,*temp;
	in=t;
	temp=t;
	int fl=0;

	while(in!=NULL)										//traversing till the end of stack
	{
		if(in->accountno==e && c!=1)			
		{
			for(i=1;i<c-1;i++)
			{
				temp=temp->next;
			}
			temp->next=in->next;						// deleting the node
			

		}
		else if(in->accountno==e && c==1)
		{
			t=in->next;
		}
		in=in->next;
		c++;

	}
return t;
}


long int min(USER_DETAIL *root)							//  This function is used to find  and return the minimum value from right subtree of a binary search tree.
{
	if(root->left==NULL)
		return root->details.AcNo;
	else 
		min(root->left);
}


void deletefromfile1(int accountno)						// for deleting in linked list and printing in transaction file
{
		
		LLIST *head,*temp;
		head=(LLIST *)malloc(sizeof(LLIST));
		head->next=NULL;
		head = createlinkedlist(head);					// calling function to create bthe stack
		temp=del(head,accountno);						// calling the function to delete the nodes with specific account no
		temp=temp->next;
		FILE *fp1;
		fp1=fopen("FILE1.txt","w");
		while(temp!=NULL)
		{
			fprintf(fp1,"%d\n%s%s",temp->accountno,temp->string1,temp->string2);		// printing in the transaction file
			temp=temp->next;
		}
		fclose(fp1);
}


//DELETION FROM BINARY SEARCH TREE
void delete1(USER_DETAIL *root,long int n)
{	
	USER_DETAIL *t;
	int k;
	if(root->details.AcNo!=n)
	{
		if(root->details.AcNo>n)
		{	
			p=root;
			whiledelete=0;
			delete1(root->left,n);					//TRAVERSING LEFT
		}
		else if(root->details.AcNo<n)
		{
			p=root;
			whiledelete=1;
			delete1(root->right,n);					//TRAVERSING RIGHT
		}
	}
	if(root->details.AcNo==n)
	{	
		if(root->left==NULL&&root->right==NULL)		//deletion of node having no childs:
		{
			if(whiledelete==0)		
				p->left=NULL;
			else if(whiledelete==1)
				p->right=NULL;
			else if(whiledelete==5)					//if head is being deleted
				headfordel=NULL;
		}
		else if(root->left==NULL&&root->right!=NULL)		//deletion of node having one child:
		{
			//printf("1\n");
			if(whiledelete==0)
				p->left=root->right;
			else if(whiledelete==1)
				p->right=root->right;
			else if(whiledelete==5)							//if head is being deleted
			{
				//printf("2\n");
				headfordel=root->right;
			}
		}
		else if(root->left!=NULL && root->right==NULL)		//deletion of node having one child:
		{
			if(whiledelete==0)
				p->left=root->left;
			else if(whiledelete==1)
				p->right=root->left;
			else if(whiledelete==5)							//if head is being deleted
				headfordel=root->left;
		}
		else if(root->left!=NULL &&root->right!=NULL)		//deletion of node having two childs:
		{
			t=root;
			k=min(root->right);
			whiledelete=1;
			p=t;
			delete1(root->right,k);
			t->details.AcNo=k;
		}
	}
}

USER_DETAIL *delete(USER_DETAIL *temp,long int n)	//This function calls the delete function of binary search tree, having the head pointer and the data to be deleted as parameters.
{
	headfordel=temp;
	//printf("%p\n",headfordel );
	delete1(headfordel,n);
	//printf("%p\n",headfordel );
	return headfordel;
}