/*		
		DS PROJECT -->> Bank Management System
-----------------------------------------------
	Name: Krishna Kumar Dey			201601046
	Name: Vishakha Khurangale		201601043
	Name: Dharani Devi Akurathi		201601003
	Name: Preethi Hena				201601024
	Last Update: Monday Apr 17 16:16:51 IST 2017
-----------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "003-assign12.c"


USER_DETAIL *headforbst=NULL;

ADDRESS *hforadd=NULL;
int main(int argc, char const *argv[])
{
	time_t t;
	srand((unsigned)time(&t));
	hforadd=addressinlist();
	headforbst=from_file_to_tree();
	printf("\t\t\tHello!!!\n\t\t\tWelcome to IIIT BANK\n\n");
	char pcheck[4];
	strcpy(pcheck,"00");
	int d;
	LOOP:
	
		printf("1. NEW USER\n");
		printf("2. EXISTING USER\n");
	
		scanf("%d",&d);
		if(d == 1)
		{
			headforbst=NEW_USER(headforbst);
				
		}
		else
		{
			headforbst=EXISTING_USER(headforbst);
		}
	
	writingtofile(headforbst);
	LOOP1:
			printf("DO YOU WISH TO CONTINUE\nPRESS '1' TO CONTINUE\nPRESS '2' TO EXIT\n");
			scanf("%d",&d);
			if(d==1)
				goto LOOP;
			else if(d!=2 && d!=1)
			{
				printf("Wrong Input\n");
				goto LOOP1;
			}
	return 0;
}