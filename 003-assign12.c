#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "024-assign12.c"

USER_DETAIL *headofbst;

//If entry1(username) exists in bst then password is stored in entry2.
void searchuserintree(char entry1[], char entry2[],USER_DETAIL *root,int flag1)
{
	if(root==NULL)
		return;
	if(flag1)
		return;
	if(strcmp(entry1,root->details.User)==0)
	{
		flag1=1;
		strcpy(entry2,root->details.pass);
		
	}
	searchuserintree(entry1,entry2,root->left,flag1);
	searchuserintree(entry1,entry2,root->right,flag1);
}


//If username exists returns 1 else retuen 0.
int searchusername(char entry1[],char entry2[])
{
	char accountno[13];
	strcpy(entry2,"");
	searchuserintree(entry1,entry2,headofbst,0);
	if(strlen(entry2)>0)
		return 1;
	else
		return 0;
}


//If accountno(an) exists account balance of s is returned else 0 is returned.
int checkaccountno(long int an,long int s)
{
	FILE* fh;
	char newstring[20],string[200],bal[20];
	fopen_s(&fh,"userdetails.txt", "r");
	const size_t line_size = 300;
	char* line = malloc(line_size);
	int count=0,i=0,j=0,k=0,flag=0,flag1=0;
	while (fgets(line, line_size, fh) != NULL) 
	{
    //printf(line);
    	strcpy(string,line);
	    while(string[i]!='\0')
		{	
			if(string[i]=='$')
			{
				count++;
			}
			else if(count==8 && flag1==0)
			{
				bal[j]=string[i];
				j++;
			}
			else if(count==12)
			{
				bal[j]='\0';
				newstring[k]=string[i];
				k++;
			}
			else if(count==13)
			{
				newstring[k]='\0';
			}
			i++;
		}
		
		i=0;
		k=0;
		count=0;
		if(atoi(newstring) == s)
		{
			flag1=1;
			
			if(an==s)
				flag=1;
			
		}

		
		else if(atoi(newstring)==an || an==s)
		{
			
			flag=1;
			j=0;
			//break;
		}

		if(flag1==1 && flag == 1)
			break;
		else
			j=0;
	}
	free(line); 
	fclose(fh);

	if(flag==1)
	{
		
		return atoi(bal);
	}
	else
		return 0;
	
}


//The account number  of entry1(username) is stored in accountno.
void searchintree(char entry1[], USER_DETAIL *root, char accountno[],int flag1)
{
	if(root==NULL)
		return;
	if(flag1)
		return;
	if(strcmp(entry1,root->details.User)==0)
	{
		flag1=1;
		long int acno;
		acno=root->details.AcNo;
		itoa(acno,accountno,10);
		
	}
	searchintree(entry1,root->left,accountno,flag1);
	searchintree(entry1,root->right,accountno,flag1);
}


// Returns the accountno of entry1.
int getaccountno(char entry1[])
{
	char accountno[13];
	searchintree(entry1,headofbst,accountno,0);
	return atoi(accountno);
}

//Upadating the FILE1 with transaction details of sender,receiver,amount transferd & Timings.
void updatetransactionfiles(long int sender,long int receiver,int amount)
{
	FILE *fp1,*fp2;
	fp1=fopen("FILE1.txt","a");
	//fp2=fopen("FILE2.txt","a");
	fprintf(fp1,"%d\n",sender);
	time_t mytime;
    mytime = time(NULL);
	fprintf(fp1,ctime(&mytime));
	fprintf(fp1,"Tranfered to: %ld\tAmount transfered: %d\t\n",receiver,amount);
	fprintf(fp1,"%d\n",receiver);
	fprintf(fp1,ctime(&mytime));
	fprintf(fp1,"Tranfered from: %ld\tAmount transfered: %d\t\n",sender,amount);
	fclose(fp1);
	updatebalance(headofbst,sender,(-1*amount));
	updatebalance(headofbst,receiver,amount);
}


// Transfering amount.
void Transaction(char entry1[],USER_DETAIL *root)
{
	printf("Fill the following details\n\n");
	printf("Enter recipients Account No.\n");
	long  int an,a,s,x;
	char accountno[15];
	s=getaccountno(entry1);
	printf("sender:-------- %d\n",s);

	
	while(1<2)
	{
		scanf("%ld",&an);
		if(checkaccountno(an,s) > 0)
		{
			break;
		}
		else
		{
			printf("Invalid Account No. Please try again.\n");
		}
	}
	printf("available balance in your account: %d\n",checkaccountno(an,s));
	printf("Enter the amount to be transfered.\n");
	while(1<2)
	{
		scanf("%d",&a);
		if(a<=checkaccountno(an,s))
		{
			break;
		}
		else
		{
			printf("Trying to transfer more than available balance in your account. Try again.\n");
		}
	}
	updatetransactionfiles(s,an,a);
	
}

// Check if the date, year & month matching with the date, year & month in string.
int checkdate(char Month[],int date,int year,char string[])
{
	
	int count=0,i=0,j=0,k=0,l=0,flag=0,flag1=0;
	char fmonth[7],fyear[6],fdate[4];
    		
	while(string[i]!='\0')
	{
	    if(string[i]==' ')
	    {
	    	count++;
	    }
		else if(count==1)
		{
			fmonth[j]=string[i];
			j++;
		}
		else if(count==2)
		{
			fmonth[j]='\0';
			fdate[k]=string[i];
			k++;
		}
		else if(count==4)
		{
			fdate[k]='\0';
			fyear[l]=string[i];
			l++;
		}
		i++;
	}
	fyear[l]='\0';
			
	//printf("%s: fmonth %d %d\n",fmonth,atoi(fdate),atoi(fyear));
	if(strcmp(Month,fmonth)==0 && atoi(fdate)==date && atoi(fyear)==year)
		return 1;
	else
	{
		//printf("No transactions on entered date\n");
		return 0;
	}
}

// Searching transactions on given date.
void searchbydate(char entry1[])
{
	printf("Enter Date (Format:Month date year)\n");
	char Month[20],string[200];
	int date,year;
	scanf("%s %d%d",&Month,&date,&year);
	printf("\n----------------------------------------------------------------------\n");
	long int s;
	FILE* fh;
	fopen_s(&fh,"FILE1.txt", "r");
	const size_t line_size = 300;
	char* line = malloc(line_size);
	int flag=0,flag1=0,flag2=0;
	//	printf("-------%d\n",entry1);
	s=getaccountno(entry1);
	while (fgets(line, line_size, fh) != NULL) 
	{
		strcpy(string,line);
		if(atoi(line)==s)
		{

			flag=1;
			
		}
		else if(flag == 1 && checkdate(Month,date,year,string))
		{
			printf("\n");
	    	printf(line);
	    	flag=0;
	    	flag1=1;
	    	flag2=1;
		}
		else if(flag1 == 1)
		{
	    	printf(line);
	    	printf("\n----------------------------------------------------------------------\n");
	    	flag1=0;
	    	flag=0;
		}

	}
	if(flag2==0)
	{
		printf("Sorry:))  No transactions are available on that date.\n");
	}
	
	fclose(fh);

}


//printing transation history of entry1(username).
void Transactionhistory(char entry1[])
{
	printf("1.All transactions.\n");
	printf("2.Search transaction by date.\n");
	int d;
	scanf("%d",&d);
	if(d==1)
	{
		printf("\n----------------------------------------------------------------------\n");
		long int s;
	
		s=getaccountno(entry1);
		LLIST *headll,*temp;
		headll=(LLIST *)malloc(sizeof(LLIST));
		headll->next=NULL;
		headll = createlinkedlist(headll);
		temp=headll;
		temp=temp->next;
		while(temp!=NULL)
		{
			if(temp->accountno == s)
			{
				printf("%d\n%s%s",temp->accountno,temp->string1,temp->string2);
				printf("\n--------------------------------------------------------------------------------\n");
			}
			temp=temp->next;
		}
	}
	else
	{
		searchbydate(entry1);
	}
}

// Money depositing.
void Deposit(char entry1[])
{
	printf("Enter the amount to be deposited.\n");
	long  int amount,s;
	s=getaccountno(entry1);
	scanf("%ld",&amount);
	FILE *fp1;
	fp1=fopen("FILE1.txt","a");
	//fp2=fopen("FILE2.txt","a");
	fprintf(fp1,"%d\n",s);
	
	time_t mytime;
    mytime = time(NULL);
	fprintf(fp1,ctime(&mytime));
	fprintf(fp1,"Self Deposited \tAmount deposited: %d\t\n",amount);
	fclose(fp1);
	updatebalance(headofbst,s,amount);  // s: account no
	printf("Deposited successfully\n");
}

// Amount withdrawing.
void Withdrawl(char entry1[])
{
	printf("Withdrawl amount.\n");
	long  int a,s;
	s=getaccountno(entry1);
	printf("Available Balance : %d\n",checkaccountno(s,s));
	while(1<2)
	{
		scanf("%d",&a);
		
		if(a<=checkaccountno(s,s))
		{
			break;
		}
		else
		{
			printf("Trying to withdraw more than available balance in your account. Try again.\n");
		}
	}
	FILE *fp1;
	fp1=fopen("FILE1.txt","a");
	fprintf(fp1,"%d\n",s);
	
	time_t mytime;
    mytime = time(NULL);
	fprintf(fp1,ctime(&mytime));
	fprintf(fp1,"Withdrawn  \tAmount withdrawn: %d\t\n",a);
	fclose(fp1);
	updatebalance(headofbst,s,(-1*a)); //s: account no and a: amount
	printf("Withdrawn successfully\n");
}

// If user is already existing then asks for futher process.
USER_DETAIL *EXISTING_USER(USER_DETAIL *headtemp)
{
	headofbst=headtemp;
	char entry1[20],entry2[20],passwordc[20];
	
		while(1<2)
		{
			printf("Username:\n");
			scanf("%s",entry1);
			strcpy(entry2,entry1);
			if(searchusername(entry1,entry2)==1)
			{
				break;
			}
			else
			{
				printf("Invalid Username. Please try again.\n");
			}
		}

		while(1<2)
		{
			printf("Password:\n");
			//scanf("%s",passwordc);
			char c;
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
		        	passwordc[ pos++ ] = c;
		            printf("%c", '*');
		        }
		        else if( c == 8 && pos)
		        {
		            passwordc[ pos-- ] = '\0';
		            printf("%s", "\b \b");
		        }
		    }
		    passwordc[pos]=0;
			if(strcmp(passwordc,entry2)==0)
			{
				printf("\n");
				break;
			}
			else
			{
				printf("\nPassword doesn't match.\n");
			}
		}
	
	
	printf("1.Update your account\n");
	printf("2.Delete your account\n");
	printf("3.Money Transaction\n");
	printf("4.Transaction history\n");
	printf("5.Deposit\n");
	printf("6.Withdrawl\n");
	printf("7.Check Available balance\n");
	int d;
	scanf("%d",&d);
	if(d==1)
	{
		updation(headofbst,getaccountno(entry1));
		//strcpy(check,"11");
		
	}
	if(d==2)
	{
		headofbst=delete(headofbst,getaccountno(entry1));
		//writingtofile();
		deletefromfile1(getaccountno(entry1));
		//strcpy(check,"01");
		headtemp=headofbst;
	}
	if(d==3)
	{
		Transaction(entry1,headofbst);
		//strcpy(check,"11");
	}
	
	if(d==4)
	{
		Transactionhistory(entry1);
		//strcpy(check,"11");
	}
	if(d==5)
	{
		Deposit(entry1);
		//strcpy(check,"11");
	}
	if(d==6)
	{
		Withdrawl(entry1);
		//strcpy(check,"11");
	}
	if(d==7)
	{
		long  int s;
		s=getaccountno(entry1);
		printf("%d: accountno\n",s);
		printf("Available balance in your account: %d\n",checkaccountno(s,s));
		
		//strcpy(check,"11");
	}
	
return headtemp;
}