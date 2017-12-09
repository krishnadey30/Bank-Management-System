#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "046-assign12.c"
USER_DETAIL *headforupdate;
// all functions are follows inorder traversal.
//update balance ------------------------------------------------------------------
void updatebalance(USER_DETAIL *user,long int n,float balance)
{
	USER_DETAIL *temp;
	temp=user;
	if(temp==NULL)
	{
		return;
	}
	if(temp->details.AcNo==n)
	{
		temp->details.Curbal=temp->details.Curbal+balance;
	}
	updatebalance(temp->left,n,balance);
	updatebalance(temp->right,n,balance);
}
//updating address ----------------------------------------------------------------
void address(USER_DETAIL *user,long int n,char y4[],int pin)
{
	USER_DETAIL *temp;
	temp=user;
	if(temp==NULL)
	{
		return;
	}
	if(temp->details.AcNo==n)
	{
		temp->details.pincode=pin;
		strcpy(temp->details.ADD,y4);
		printf("address is updated\n");
	}
	address(temp->left,n,y4,pin);
	address(temp->right,n,y4,pin);
}
//updating email-id ---------------------------------------------------------------
void emailid(USER_DETAIL *user,long int n,char y3[])
{
	USER_DETAIL *temp;
	temp=user;
	if(temp==NULL)
	{
		return;
	}
	if(temp->details.AcNo==n)
	{
		strcpy(temp->details.Email,y3);
		printf("email-id is updated\n");
	}
	emailid(temp->left,n,y3);
	emailid(temp->right,n,y3);	
}
//updating mobile number-----------------------------------------------------------
void mobilenumber(USER_DETAIL *user,long int n,char x3[])
{
	USER_DETAIL *temp;
	temp=user;
	if(temp==NULL)
	{
		return;
	}
	if(temp->details.AcNo==n)
	{
		strcpy(temp->details.mob,x3);
		printf("mobile number is updated\n");
	}
	mobilenumber(temp->left,n,x3);
	mobilenumber(temp->right,n,x3);
}
//updating password ---------------------------------------------------------------
// task 1 checking password
int x1=0;
void checkpass(USER_DETAIL *user,long int n,char x[])
{
	USER_DETAIL *temp;
	temp=user;
	if(temp==NULL)
		return;
	if(strcmp(temp->details.pass,x)==0)
	{
		x1=1;
	}
	checkpass(temp->left,n,x);
	checkpass(temp->right,n,x);
}
// task 2 updating password
void password(USER_DETAIL *user,long int n,char y[])
{
	USER_DETAIL *temp;
	temp=user;
	if(temp==NULL)
	{
		return;
	}
	if(temp->details.AcNo==n)
	{
		strcpy(temp->details.pass,y);
		printf("password is updated\n");
	}
	password(temp->left,n,y);
	password(temp->right,n,y);
}
//updating username -----------------------------------------------------------------
// task 1 checking username
int x2=1;
void checkusername(USER_DETAIL *user,char y2[])
{
	USER_DETAIL *temp;
	temp=user;
	if(temp==NULL)
		return;
	if(strcmp(temp->details.User,y2)==0)
	{
		x2=0;
	}
	checkusername(temp->left,y2);
	checkusername(temp->right,y2);
}
// task 2 updating username
void username(USER_DETAIL *user,long int n,char y2[])
{
	USER_DETAIL *temp;
	temp=user;
	if(temp==NULL)
	{
		return;
	}
	if(temp->details.AcNo==n)
	{
		strcpy(temp->details.User,y2);
		printf("username is updated\n");
	}
	username(temp->left,n,y2);
	username(temp->right,n,y2);

}
//---------------------------------------------------------------------------------
void updation(USER_DETAIL *user,long int n)
{
	headforupdate=user;
	int number,c,c1,c3,o,pin;
	char x[15],y[15],y1[15],y2[15],y3[40],y4[100];
	// format of updation :
	printf("------------------------------updation form---------------------------\n");
	printf("1.username \n");
	printf("2.password \n");
	printf("3.mobile number \n");
	printf("4.email-id \n");
	printf("5.address \n");
	printf("----------------------------------------------------------------------\n");

	// username 
	printf("enter your option :");
	scanf("%d",&number);
	//------------------------------------------------------------------------------//
	if(number==1)//username
	{
		loop:
		printf("Change your username \n");
		printf("enter your new username :");
		scanf("%s",y2);
		checkusername(headforupdate,y2);
		if(x2==1)
		{
			username(headforupdate,n,y2);  // we are passing account number and headforupdate .
		}	
		else
		{
			printf("This username already exits.\nPlease try again.\n");
			goto loop;
		}
	}
	//------------------------------------------------------------------------------//
	if(number==2)//password
	{
		loop2:
		printf("change your password \n"); // we are checking password is correct or not . 
		printf("enter your old password :");
		//scanf("%s",x);
		char c,d,e,passwordc[20],password1[20],password2[20];
		int pos = 0,pos1=0,pos2=0;;
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
		checkpass(headforupdate,n,passwordc);
		if(x1==1)
		{
			printf("\nenter your new password :");
			//scanf("%s",y);
			while(1)
		    {
		    	if(d<0)
		    		d=0;
		        d = getch();
		        if (d == 13)
		         break;
		        if( isprint(d) )
		        {
		        	password1[ pos1++ ] = d;
		            printf("%c", '*');
		        }
		        else if( d == 8 && pos1)
		        {
		            password1[ pos1-- ] = '\0';
		            printf("%s", "\b \b");
		        }
		    }
		    password1[pos1]=0;
			printf("\nconfirm your new password :");
			//scanf("%s",y1);
			while(1)
		    {
		    	if(e<0)
		    		e=0;
		        e = getch();
		        if (e == 13)
		         break;
		        if( isprint(e) )
		        {
		        	password2[ pos2++ ] = e;
		            printf("%c", '*');
		        }
		        else if( e == 8 && pos2)
		        {
		            password2[ pos2-- ] = '\0';
		            printf("%s", "\b \b");
		        }
		    }
		    password2[pos2]=0;
			if(strcmp(password1,password2)==0)
			{
				printf("\n");
				password(headforupdate,n,password1);
			}
		}
		else
		{
			printf("\ninvlid password\n");
			printf(" Press 1 to continue \n press any key to exit \n");
			scanf("%d",&c1);
			if(c1==1)
			{
				goto loop2;
			}
		}
	}
	//------------------------------------------------------------------------------//
	if(number==3)// mobile number
	{
		char x3[12];
		loop1:
		printf("change your mobile number \n");
		printf("enter your new mobile number :");
		scanf("%s",x3);
		if(strlen(x3)==10)
		{
			mobilenumber(headforupdate,n,x3);
		}
		else
		{
			printf("invlid number\n");
			printf(" Press 1 to continue \n press any key to exit \n");
			scanf("%d",&c);
			if(c==1)
			{
				goto loop1;
			}
		}
	}
	//------------------------------------------------------------------------------//
	if(number==4)//email-id
	{
		loop3:
		printf("change your email-id \n");
		printf("enter your new email-id :");
		scanf("%s",y3);
		o=validating_email(y3);
		if(o==1)
		{
			emailid(headforupdate,n,y3);
		}
		else
		{
			printf("invalid email-id\n");
			printf(" Press 1 to continue \n press any key to exit \n");
			scanf("%d",&c3);
			if(c3==1)
			{
				goto loop3;
			}
		}
	}
	//-------------------------------------------------------------------------------//
	if(number==5)// address
	{
		printf("change your address \n");
		printf("Enter your new pincode :\n");
		scanf("%d",&pin);
		printf("enter your new address :");
		scanf("%s",y4);
		address(headforupdate,n,y4,pin);
	}
	//-------------------------------------------------------------------------------//
}