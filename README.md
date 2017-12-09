# Bank Management System

> *Banking Management System is a simple database project in C. It is done using file handling mechanism in C. The record of the customer can be added, updated, searched and deleted. It is simple project made using console application of C. This means, no graphics component are added. The main target user of this project are the C beginners who want to make the project in C and especially those who are interested in File handling. This projects is complete package to learn how to use file as database.*

#### Group Name

```return sleep;```

#### Group No 

```P36```

## GROUP MEMBERS

NAME | ROLL NO	| WORK
:---------------------------- | ----------------------- | --------------------------------
*[Krishna Kumar Dey](https://github.com/krishnadey30)* | 201601046 | Creating bst for users, Main function, Creating bst for address, Registration of new user.
*[Vishakha Khurangale](https://github.com/vishakhakhurangale)* | 201601043 | Updating the details of the user such as username, password, address, email id, mobile no, update balance.
*[Dharani Devi Akurathi](https://github.com/Dharni0607)* | 201601003 | performing transaction , printing transaction history , Updating transaction file.
*[Preethi Hena](https://github.com/preethihena)* | 201601024 | Deleting account of user, deleting transaction details, creating linked list of transaction.

## DATA STRUCTURE USED 

> Binary Search Tree is used for the data creation because it will be efficient in terms of space and complexity to search records. Also Linked list is used to delete an Account.

## Requirements

* [C](https://gcc.gnu.org/install/binaries.html)  

## Getting Started

To clone and run this application, you'll need Git,gcc installed on your computer.  From your command line:

### Clone this repository
```
$ git clone https://github.com/krishnadey30/Bank-Management-System.git
```

### Go into the repository
```
$ cd Bank-Management-System
```

### Run the app
```
$ gcc p36-main().c
```
___
### ```Task 1:```

#### Customer Registration (Account Number, Name, Age,etc.,) 
- _void filetolist(USER_DETAIL *temp,USER_DETAIL *new)_

   - this function add nodes in a binary search tree of user details
   - tree is made based on account No of the user

- _void validating_account_no(USER_DETAIL *temp,long int acc_no)_

	- this function validate that the account no given is prevoiusly present or not
	- mainly used while creating account by new user to allocate different account no to different users.
	- it is traversing via pre-order traversal
	- if account no found make the flag '0'

- _void Account_No(USER_DETAIL *acc,USER_DETAIL *roothead)_

	- for Generating account number randomly
	- calls the 'validating_account_no()' to validate the new account no generated so that no two user have same account no
	- if that account no does not exist then assign it to the new user
	- else going back to the loop again to generate the account no randomly

- _USER_DETAIL *from_file_to_tree()_
	- reading from file and  creating a tree
	- reading from file line by line
	- calls 'filetolist()' for adding it the binary search tree

- _void Address(int pin,USER_DETAIL *acc,ADDRESS *temp)_
	- checking address from the given pin code
	- traversing in post order and checking the address for the given pin code
	- 4 options are given:
		1. to conferm
			- if confermed the add that address in user details
		2. to check for another
			- if user want to check another address with same pin code
		3. to enter by yourself
			- if user want to enter the address by themself 
		4. to enter another pincode
			- if user want to check for another pin code

- _void validating_username(USER_DETAIL *temp,char user_name[])_
	- to check if that username doesnot exist previously
	- if username found making flag '0' so that program can ask to enter different username
	- traversing in pre-order traversal

- _void Username(USER_DETAIL *acc,USER_DETAIL *roothead)_
	- Asking for username
	- calling 'validating_username()' for validating username
	- if username not found then conferm the username
	- else ask for another username

- _void passwordhide(USER_DETAIL *acc)_
	- to take password and print * in place of password

- _void createadresstree(ADDRESS *temp,ADDRESS *new)_
	- Creating Address Tree
	- binary search tree by pincode

- _ADDRESS *addressinlist()_
	- scaning pincode and address from file
	- calling 'createadresstree()' to add the address in binary tree
	- returns the address for root

- _int validating_email(char A[])_
	- for validating email address
	- retruns 1 if correct else 0

- _USER_DETAIL *NEW_USER(USER_DETAIL *temp)_
	- function to create a new user account
	- will ask the user for
		- Account_type
			- Saving
			- Current
			- Fixed	
		- Name
		- Gender
			- Male
			- Female
			- Others
		- Father's Name
		- DOB(DD/MM/YYYY)
		- Pincode
			- call the 'Address()' function to know the address of that pincode
		- Mobile No
			- validate the Mobile No
		- Email_Id
			- call the 'validating_email()' to validate the email id
		- Opening balance
		- Userame
			- call the 'Username()' to get a valid username
		- password
			- call the 	'passwordhide()' to get password in hidden form
		- account_no
			- calls 'Account_No()' to get a valid account no
	- call 'filetolist()' to add the new user in binary search tree
	- return root pointer of binary search tree

- _void from_tree_to_file(FILE *pas,USER_DETAIL *new_ac)_
	- re-writting the whole tree to file
	- pre-oreder traversal of bst

- _void writingtofile(USER_DETAIL *temp)_
	- call the 'from_tree_to_file()' to re-write the whole tree to file
___

### ```Task 2:```
#### Account Updation 
#### Email update 
#### Mobile number update(eg. Customer wants update email)

- _void updation(USER_DETAIL *user,long int n)
	- This is main updating function where all options can be updated.
		1. username 
		2. password
		3. mobile number
		4. email-id
		5. address 
			- *user is a pointer to head of binary search tree consisting of userdetails.

- _void checkusername(USER_DETAIL *user,char y2[])_
	- While updating username , this function is checking whether entered username is exists or not.
	- 'y2' is username.

- _void username(USER_DETAIL *user,long int n,char y2[])_
	- This function is updating the username.
	- 'y2' is username.

- _void checkpass(USER_DETAIL *user,long int n,char x[])_
	- While updating password , this function is checking whether entered password is exists or not.
	- 'n' is account number. 'x' is password string.

- _void password(USER_DETAIL *user,long int n,char y[])_
	- This function is updating the password.
	- 'n' is account number. 'y' is password string.
- _void mobilenumber(USER_DETAIL *user,long int n,char x3[])_
	- This function is updating the mobile number.
	- 'n' is account number. 'x3' is mobile number string.
- _void emailid(USER_DETAIL *user,long int n,char y3[])_
	- This function is updating the email-id.
	- 'n' is account number. 'y3' is email-id string.

- _void address(USER_DETAIL *user,long int n,char y4[])_
	- This function is updating address .
	- 'n' is account number. 'y4' is address string.
		
- _void updatebalance(USER_DETAIL *user,long int n,float balance)_
	- This is function to update the money into account during transaction. 
	- 'n' is account number. 'balance' is a amouont which transacted during transaction.

___

### ```Task 3:```
#### Transaction history 
#### Searching (eg. search database to find all customers with name “ABCD”.)

- _void EXISTING_USER();_
	- If entered Username and Password exist in the userfile asks user for any transactions or updations.
	- As per the option selected by user it calls respective functions.

- _int searchusername(char entry1[],char entry2[]);_
	- entry1 is the username of user.
	- entry2 is for storing password of user.

- _void searchuserintree(char entry1[], char entry2[],USER_DETAIL *root,int flag1);_
	- Here username is searched in binary search tree.
	- If entry1(username) exists in bst then password is stored.

- _void Transaction(char entry1[],USER_DETAIL *root);_
	- entry1 is username of user. 
	- here user can tranfer amount to any account based on his/her account details(accountno). 

- _void updatetransactionfiles(long int sender,long int receiver,int amount);_
	- FILE1 is updated with new transactions with details like sender(accountno), receiver(accountno), amount transfered, and Time(date and timings).

- _int getaccountno(char entry1[]);_
	- This function returns the accountno of entry1.

- _void searchintree(char entry1[], USER_DETAIL *root, char accountno[],int flag1);_
	- This function searches entry1(username) in BST and stores the accountno of entry1.

- _int checkaccountno(int an,int s);_
	- If accountno(an) exists in userfile it returns available balance of s(user) else it return 0.

- _void Transactionhistory(char entry1[]);_
	- Asks the user to selects one of given options. If option 1 is selected then it displays all Transaction history of the user.
	- (Using linkedlist) if the account no of user matches it displays details.
	- If 2nd option is selected 'searchbydate' function is called.

- _LLIST *createlinkedlist(LLIST *head);_
	- Input is taken from FILE1(Transaction history file). Head has 4 parts 1.accountno, 2.string1, 3.string2, 4.next
	- Accountno is stored in accountno, date is stored in string1 ,transaction details are stored in string2.

- _void searchbydate(char entry1[]);_
	- Here user can search transactions on particular date.
	- This function searches for accountno and date in FILE1(Transaction history file), If matches then displays details.

- _int checkdate(char Month[],int date,int year,char string[])_
	- Checks if the date matches with the date in the string.
	- If matches return 1 else retuen 0.

- _void Deposit(char entry1[]);_
	- This function is used to deposit amount in users account.

- _void Withdrawl(char entry1[]);_
	- This function is used to withdraw amount in users account.


___
### ```Task 4:```
#### Deletion  (eg. Removing account by providing the account number) 

- _void delete1(USER_DETAIL *root,long int n);_
	- It needs 2 parameters head pointer and the data to be deleted.
	- deletion involves 3 parts:
		- deletion of node having no childs:
			- We keep traversing and storing the parent node when node to be deleted is found,we cut the link of - - - _this node with the parent node._
	- deletion of node having one child:
		- We store node which is before parent node in 'p' every time and when the node to be deleted is found,we cut the link of the present node  and join it to 'p'.
	- deletion of node having two childs:
		- We keep traversing  and if the node to be deleted is found store it ,find the minimum element in right sub tree and now again delete the node with minimum element by recursive call of deletion function.
		- Later replace the present node data with the minimum data.
	 	- We call the function recursively for traversing.

- _long int min(USER_DETAIL *root);_
	- This function is used to find  and return the minimum value from right subtree of a binary search tree.

- _void delete(USER_DETAIL *temp,long int n);_
	- This function calls the delete function of binary search tree, having the head pointer and the data to be deleted as parameters.

- _LLIST *createlinkedlist(LLIST *llhead)_
	- creating stacks  using linked list 
	- start reading from file and keep creating the stack till end of file

- _LLIST* del(LLIST *t,long int n)_
	- deletion of nodes with given account no



___
