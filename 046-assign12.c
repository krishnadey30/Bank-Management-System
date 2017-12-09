#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
//#include "043-assign12.c"

/*Abstract data type for User details*/
typedef struct
{
	char NAME[200],Email[50];
	char FNAME[50],Gender;
	char ADD[100];
	int pincode;
	char Minor[5];
	int Age;
	char DOB[12];
	char mob[11];
	char Actype;
	long int AcNo;
	float Curbal,rateint,opbal;
	char User[20];
	char pass[20];
}User;

/*Abstract Data Type for BINARY TREE OF USER*/
typedef struct detail
{
	User details;
	struct detail *right,*left;
}USER_DETAIL;
USER_DETAIL *roothead=NULL;


/*Abstract Data type for Address*/
typedef struct adresses
{
	int pincode;
	char Address[100];
	struct adresses *left,*right;
}ADDRESS;

ADDRESS *h=NULL;
int addconferm=1;
/*READING FROM FILE AND CREATING A BINARY SEARCH TREE BASED ON ACCOUNT NUMBER + ADDING NEW USER TO THE BINARY TREE*/
void filetolist(USER_DETAIL *temp,USER_DETAIL *new)
{
	if(roothead==NULL)							//if head pointer is NULL
	{
		roothead=new;
		return;
	}
	if(temp->details.AcNo>new->details.AcNo)	//for left sub binary tree
	{
		if(temp->left==NULL)					//if left of temp is null then assigning the new node in left of the temp
		{
			temp->left=new;
			return;
		}
		else
			filetolist(temp->left,new);			// else calling the function again
	}
	else
	{
		if(temp->right==NULL)					//if right of temp is null then assigning the new node in right of the temp
		{
			temp->right=new;
			return;
		}
		else
			filetolist(temp->right,new);		// else calling the function again
	}
}

/*checking if the generated account no doesnot exist previosly*/ 
void validating_account_no(USER_DETAIL *temp,long int acc_no)
{
	if(temp==NULL)
		return;
	if(!addconferm)
		return;
	if(temp->details.AcNo==acc_no)				// if account no found make the flag '0'
		addconferm=0;
	validating_account_no(temp->left,acc_no);	//else calling the function again i.e. traversing in preorder
	validating_account_no(temp->right,acc_no);	//-----------------      ,,       ----------------------    
}

/*Generating account number randomly*/
void Account_No(USER_DETAIL *acc,USER_DETAIL *roothead)
{
	long int x;
	LOOP:
	x=rand()%1000000000+1000000000;
	validating_account_no(roothead,x);			// validating the new account no generated so that no two user have same account no
	if(addconferm)
	{
		acc->details.AcNo=x;					// if that account no does not exist then assign it to the new user
	}
	else
		goto LOOP;								// else going back to the loop again to generate the account no randomly

}

/*reading from file and  creating a tree*/
USER_DETAIL *from_file_to_tree()
{
	FILE* fh;
	fopen_s(&fh,"userdetails.txt", "r");
	char A[500],B[15][200];
	USER_DETAIL *new_ac;
	const size_t line_size = 300;
	char* line = malloc(line_size);
	while (fgets(line, line_size, fh) != NULL) 	//reading from file line by line
	{
		strcpy(A,line);
		new_ac=(USER_DETAIL *)malloc(sizeof(USER_DETAIL));
		new_ac->left=NULL;
		new_ac->right=NULL;
		int i,j=0,k=0;
		for(i=0;i<strlen(A);i++)
		{
			if(A[i]=='$')
			{
				B[j][k++]='\0';
				k=0;
				//printf("%s\n",B[j] );
				j++;
			}
			else
			{
				B[j][k++]=A[i];
			}
			if(j==14)
			{
				break;
			}
		}
		new_ac->details.Actype=B[0][0];
		strcpy(new_ac->details.NAME,B[1]);
		new_ac->details.Gender=B[2][0];
		strcpy(new_ac->details.FNAME,B[3]);
		strcpy(new_ac->details.DOB,B[4]);
		new_ac->details.pincode=atoi(B[5]);
		strcpy(new_ac->details.ADD,B[6]);
		strcpy(new_ac->details.mob,B[7]);
		new_ac->details.Curbal=atof(B[8]);
		new_ac->details.opbal=atof(B[9]);
		strcpy(new_ac->details.User,B[10]);
		strcpy(new_ac->details.pass,B[11]);
		new_ac->details.AcNo=atoi(B[12]);
		strcpy(new_ac->details.Email,B[13]);
		filetolist(roothead,new_ac);			// for adding it the binary search tree
	}
	fclose(fh);
	return roothead;
}

/*checking address from the given pin code*/
void Address(int pin,USER_DETAIL *acc,ADDRESS *temp)
{
	int a;
	if(temp==NULL)
		return;
	if(addconferm!=1)
		return;
	Address(pin,acc,temp->left);				//traversing in post order and checking the address for the given pin code
	Address(pin,acc,temp->right);
	if(temp->pincode==pin && addconferm==1)
	{
		printf("Is '%s' your address\n",temp->Address );
		printf("press '1' to conferm\npress '2' to check for another\npress '3' to enter by yourself\npress '4' enter another pincode\n");
		scanf("%d",&a);
		switch (a)
		{
			case 1:								// if confermed add that address in user details
				strcpy(acc->details.ADD,temp->Address);
				acc->details.pincode=pin;
				addconferm=0;
				break;
			case 2:								// if user want to check another address with same pin code
				break;
			case 3:
				addconferm=3;					// if user want to enter the address by themself 
				break;
			case 4:
				addconferm=4;					// if user want to check for another pin code
				break;
		}

	}
}

/*to check if that username doesnot exist previously*/
void validating_username(USER_DETAIL *temp,char user_name[])
{
	if(temp==NULL)
		return;
	if(!addconferm)
		return;
	if(strcmp(temp->details.User,user_name)==0)			//if username found making flag '0' so that program can ask to enter different username
		addconferm=0;
	validating_username(temp->left,user_name);			// traversing in pre-order traversal
	validating_username(temp->right,user_name);
}

/*Asking for username*/
void Username(USER_DETAIL *acc,USER_DETAIL *roothead)
{
	char x[13];
	LOOP:
	printf("Enter Username \n");
	scanf("%s",x);
	addconferm=1;
	validating_username(roothead,x);					// for validating username
	if(addconferm)										// if username not found then conferm the username
	{
		strcpy(acc->details.User,x);
	}
	else												// username previously existed
	{
		printf("Username exists.Please try another Username\n");
		goto LOOP;
	}
}

/*to take password*/
void passwordhide(USER_DETAIL *acc)					
{
	printf("Enter password\n");
	char c,buffer[15];
    int pos = 0;
    while(1)
    {
    	if(c<0)
    		c=0;
        c = getch();
        if (c == 13)
         break;
        if( isprint(c) )
        {
        	buffer[ pos++ ] = c;
            printf("%c", '*');
        }
        else if( c == 8 && pos)
        {
            buffer[ pos-- ] = '\0';
            printf("%s", "\b \b");
        }
    }
    buffer[pos]=0;
    strcpy(acc->details.pass,buffer);
}

/*Creating Address Tree*/
void createadresstree(ADDRESS *temp,ADDRESS *new)
{
	if(h==NULL)
	{
		h=new;
		//printf("%s\n",roothead->Address );
		return;
	}
	if(temp->pincode>new->pincode)
	{
		if(temp->left==NULL)
		{
			temp->left=new;
			return;
		}
		else
			createadresstree(temp->left,new);
	}
	else
	{
		if(temp->right==NULL)
		{
			temp->right=new;
			return;
		}
		else
			createadresstree(temp->right,new);
	}
}

/*scaning pincode and address*/
ADDRESS *addressinlist()
{
	FILE *pin,*add;
	char Add[100],Pin[10];
	ADDRESS *new;
	pin=fopen("PINCODE.txt","r");
	add=fopen("ADDRESS.txt","r");
	while(fscanf(pin,"%s",Pin)!=EOF)
	{
		if(atoi(Pin) && strlen(Pin)==6 && fscanf(add,"%[^\n]\n",Add)!=EOF )
		{
			new=(ADDRESS *)malloc(sizeof(ADDRESS));
			new->pincode=atoi(Pin);
			strcpy(new->Address,Add);
			new->left=NULL;
			new->right=NULL;
			createadresstree(h,new);
		}
	}
	return h;
}


/*for validating email id*/
int validating_email(char A[])
{
	int i,isat=-1,isdot=-1;
	for(i=0;i<strlen(A);i++)
	{
		if((A[0])>='0' && A[0] <='9')
			return 0;
		if((A[i]=='@' && A[i+1]=='.')|| (A[i]=='.' && A[i+1]=='.')|| (A[i]=='.' && A[i+1]=='@')  )
			return 0;
		if(A[i]=='@')
			isat=1;
		if(A[i]=='.')
			isdot=1;
	}
	if(isdot==-1 || isat==-1)
		return 0;
	return 1;
}

/*function to create a new user account*/
USER_DETAIL *NEW_USER(USER_DETAIL *temp)
{
	roothead=temp;
	USER_DETAIL *new_ac;
	int t,pin;
	new_ac=(USER_DETAIL *)malloc(sizeof(USER_DETAIL));
	new_ac->left=NULL;
	new_ac->right=NULL;
	char A[20];
	printf("Please enter the details to Create a New Bank Account\n\n");
	LOOP:
	printf("\tWhat Type of Account You want to open\n\t1.) Current \n\t2.) Saving\n\t3.) Fixed\n");
	scanf("%d",&t);
	switch(t)
	{
		case 1: printf("YOU HAVE SELECTED TO CREATE A CUREENT ACCOUNT\n");
				new_ac->details.Actype='C';
				new_ac->details.rateint=8.26;
				break;
		case 2: printf("YOU HAVE SELECTED TO CREATE A SAVING ACCOUNT\n");
				new_ac->details.Actype='S';
				new_ac->details.rateint=6.05;
				break;	
		case 3: printf("YOU HAVE SELECTED TO CREATE A FIXED ACCOUNT\n");
				new_ac->details.Actype='F';
				new_ac->details.rateint=4.90;
				break;
		default:
				printf("WRONG INPUT\n");
				goto LOOP;
	}
	printf("Enter Your Name\n");
	getchar();
	scanf("%[^\n]s",new_ac->details.NAME);
	LOOP1:
	printf("Are You a\n 	1.) Male \n 	2.) Female\n 	3.) Others\n");
	scanf("%d",&t);
	switch(t)
	{
		case 1:
				new_ac->details.Gender='M';
				break;
		case 2: 
				new_ac->details.Gender='F';
				break;
		case 3: 
				new_ac->details.Gender='O';
				break;
		default:
				printf("WRONG INPUT\n");
				goto LOOP1;
	}
	printf("Enter Your Father's Name\n");
	getchar();
	scanf("%[^\n]s",new_ac->details.FNAME);
	printf("Enter Your Date of Birth(DD/MM/YYYY)\n");
	scanf("%s",new_ac->details.DOB);
	LOOP2:
	printf("Enter Your pincode\n");
	scanf("%d",&pin);
	addconferm=1;
	Address(pin,new_ac,h);
	if(addconferm==4)
	{
		goto LOOP2;
	}
	if(addconferm==3)
	{
		printf("Enter Your pincode\n");
		scanf("%d",&new_ac->details.pincode);
		printf("Enter Your Address\n" );
		getchar();
		scanf("%[^\n]s",new_ac->details.ADD);
	}
	if(addconferm==1)
	{
		printf("Sorry, unable to find address with same pin code\n");
		printf("Want To search for another Pin Code\nPress 1 to search\nPress any other key to enter address by self\n");
		scanf("%d",&pin);
		if(pin==1)
			goto LOOP2;
		else
		{
			printf("Enter Your pincode\n");
			scanf("%d",&new_ac->details.pincode);
			printf("Enter Your Address\n" );
			getchar();
			scanf("%[^\n]s",new_ac->details.ADD);
		}
	}
	Loop3:
	printf("Enter Your 10 digit Mobile Number\n");
	scanf("%s",A);
	if(strlen(A)!=10)
	{
		printf("Invalid Phone No\n");
		goto Loop3;
	}
	else
		strcpy(new_ac->details.mob,A);
	LOOP4:
	printf("Enter Your Email\n");
	scanf("%s",A);
	if(validating_email(A))
		strcpy(new_ac->details.Email,A);
	else
	{
		printf("Invalid Email Address\n");
		goto LOOP4;
	}
	printf("Enter Your OPENING Balance\n");
	scanf("%f",&new_ac->details.opbal);
	new_ac->details.Curbal=new_ac->details.opbal;
	Username(new_ac,roothead);
	addconferm=1;
	passwordhide(new_ac);
	Account_No(new_ac,roothead);
	addconferm=1;
	filetolist(roothead,new_ac);
	printf("\n");
	if(new_ac->details.Gender=='M')
		printf("Thankyou MR. %s for connecting with us\n", new_ac->details.NAME);
	else if(new_ac->details.Gender=='F')
		printf("Thankyou MISS. %s for connecting with us\n", new_ac->details.NAME);
	else
		printf("Thankyou %s for connecting with us\n", new_ac->details.NAME);
	printf("Your Account Number is '%d' \n",new_ac->details.AcNo );
	//roothead=EXISTING_USER(roothead,"11");
	return roothead;
}


/*re-writting the whole tree to file*/
void from_tree_to_file(FILE *pas,USER_DETAIL *new_ac)
{
	if(new_ac==NULL)
		return;
	fprintf(pas,"%c$%s$%c$%s$%s$%d$%s$%s$%0.2f$%0.2f$%s$%s$%d$%s$\n",new_ac->details.Actype,new_ac->details.NAME,new_ac->details.Gender,new_ac->details.FNAME,new_ac->details.DOB,new_ac->details.pincode,new_ac->details.ADD,new_ac->details.mob,new_ac->details.Curbal,new_ac->details.opbal,new_ac->details.User,new_ac->details.pass,new_ac->details.AcNo,new_ac->details.Email);
	from_tree_to_file(pas,new_ac->left);
	from_tree_to_file(pas,new_ac->right);
}


void writingtofile(USER_DETAIL *temp)
{
	FILE *pas;
	roothead=temp;
	pas=fopen("userdetails.txt","w");
	from_tree_to_file(pas,roothead);
	fclose(pas);
}