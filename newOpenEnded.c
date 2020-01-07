/*
Our program does not save data at each operation
we can also code for saving it after each operation by using fnSave() function every where
*/

/*-------------------DONE USING 2D ARRAY (ARRAY OF POINTERS)------------------------------
Our fnLoad() function is needs to be modified.
As we are saving pointer address in every node then all the nodes will have same content that is the one it points to at last
*/

/*
Our password function needs modification.
It should first check it the string length or both is same.
this can be done at the time we change password by saving length inside the
or else we can built the password function such that it always is of certain length
*/

/*dynamic pointer problem ---------done using arrays-----------
feedback of bigger length not saving on file
*/

/*--------------------DONE getchar wasn't used------------------------------
feedback enteres infinite loop
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<conio.h>


#define SUNDAYDISCOUNT 10
#define NEWUSERDISCOUNT 15

#define SUNMAXDIS 1000
#define NEWMAXDIS 5000

struct node   //structure for linklistt
{
	int info;
	int pur_Amt;
	char *name;
	long int phn;
	struct node* link;
};

typedef struct node *NODEPTR; //renaming pointer

int fnPassword(char passWord[]); //to check password is correct or not
void fnSetPassword(); //to set new password

NODEPTR fnManageDatabase(NODEPTR); //function to manage database
NODEPTR fn_FAddRec(NODEPTR); //function to add members
void fnAddProducts(void);  //function to add products

void fnSave(NODEPTR);  //function to save all data into a file
NODEPTR fnLoad(NODEPTR, char *, long int, int); //loads all data from file to linklist

NODEPTR fnGetNode(); //allocate a node
NODEPTR fn_DelRec(NODEPTR); //deleting a node

//sale functions
NODEPTR fnSale(NODEPTR);

NODEPTR fnSundayPurchase(NODEPTR);			//Billing for sundays
NODEPTR fnNormalDayPurchase(NODEPTR);		//Billing for normal days
void fnNormalPurchase(void);				//Billing for non member coustomers

NODEPTR fnAddAmt(NODEPTR, long int, int);	//Adding amount of different items brought

int displayBrand(void);						//Displays all the brands in the shop

int appleProduct(void);						//Displays apple products
int samsungProduct(void);					//Displays Samsung products
int xaomiProduct(void);						//Displays Xaomi products
int nokiaProduct(void);						//Displays Nokia products
int asusProduct(void);						//Displays Asus products
int acerProduct(void);						//Displays Acer products
int hpProduct(void);						//Dispolays HP products
int dellProduct(void);						//Displays Dell products

int fnAddAppleProduct(void);				//To add Apple products
int fnAddSamsungProduct(void);				//To add Samsung products
int fnAddXaomiProduct(void);				//To add Xaomi products
int fnAddNokiaProduct(void);				//To add Nokia products
int fnAddAsusProduct(void);					//To add Asus products
int fnAddAcerProduct(void);					//To add Acer products
int fnAddHpProduct(void);					//To add HP products
int fnAddDellProduct(void);					//To add Dell products


int fnInputAmt(void);						//To input amount of products not to be included in database

bool fnMatch(NODEPTR, long int);			//Checks is the number (Member) is in databse

void fnFeedBack(void);						//Feedback function
void fnSuggestion(void);					//function to enter suggestions
void fnOutOfStock(void);					//To include outofstock items
void fnGreviences(void);					//To take greviences of coustomers
NODEPTR fnDistributeCoupons(NODEPTR);

//main function starts here
int main()
{
	char password[9];

    for(;;)
    {
    	printf("\nEnter the password\n");
    	//scanf("%s",password);
        char t;
        int p;
        for(p=0;p<9;p++)
        {

            t=getch();
            password[p]=t;
            printf("*");
        }
        password[p]='\0';

    	if(fnPassword(password) == 1) //function call to check password
    		break; //out of for loop if password is correct
    	printf("\npassword is incorrect please try again\n");
	}


    if(fnPassword(password) == 1)
    {
		FILE *fp; //file pointer to load data into linklist from file and perform operations on linklist

		NODEPTR head = fnGetNode();
		head->link=NULL;
		head->info=0;

		char *cname;
		char cName[1000][30];
		int i = 0;
		long int phn;
		int pur_Amt;

		cname=(char *)malloc(sizeof(char));

		fp = fopen("Hunny1.txt", "r");
		if(fp != NULL)   //if file is empty, return head without adding content into it

		printf("\n\t\t\tLIST OF MEMBERS\n\n\n");
		while(fscanf(fp, "%s%ld%d", cName[i], &phn, &pur_Amt) != EOF)
		{
	        head = fnLoad(head, cName[i], phn, pur_Amt); //loading contents of file into link list
	        i++;
		}

	    int choice;
		char u_choice;
		int day;

		while(1)
		{
			printf("\n\n\n\t1.Sale\n\t2.Manage Database");
			printf("\n\t3.Change Password\n\t4.Distribute coupouns\n");
			printf("\n\t5.Save and Exit\n\n\n");

			printf("\nEnter choice:\t");
			scanf("%d",&choice);

			switch(choice)
			{

				case 1: head = fnSale(head);
						break;

				case 2: head = fnManageDatabase(head);
						break;

				case 3: fnSetPassword();
						break;

				case 4:head=fnDistributeCoupons(head);
                        printf("\nperson with highest purchase is:%s\n",head->name);
                        break;
				case 5: fnSave(head);
						exit(0);

				default: printf("Invalid input. Please try again\n");

			}
		}
    }
    return 0;
}


int fnPassword(char passWord[]) //function to check correctness of password
{
	FILE *fp;  //file pointer pointing to contents of password file
	int i = 0;
	char ch;

	fp = fopen("fpassword.txt", "r");	//fp points to file containing password

	if(fp == NULL)
	{
		printf("\nFailed to check\n\n");
		return 999;
	}

	ch = fgetc(fp);

	while( ch != EOF)
	{
		if((passWord[i++] != ch))
		{
			fclose(fp);
            return 0;
		}
		ch = fgetc(fp);
	}

	fclose(fp);

	return 1;
}



NODEPTR fnGetNode()
{
	NODEPTR newNode;
	newNode=(NODEPTR)malloc(sizeof(struct node));
	if(newNode==NULL)
	{
		printf("\nFailed to allocate memory");
		exit(0);
	}
	return newNode;
}


void fnSetPassword()
{
	FILE *fp;
	char oldPassword[20], newPassword[20];
	int i = 0;

	printf("Enter the last password\n");
	scanf("%s", oldPassword);

	if(fnPassword(oldPassword) == 1)
	{
		printf("\nEnter the new password\n");
		scanf("%s", newPassword);

		if(!strcmp(oldPassword, newPassword))
		{
			printf("\nYou have entered the old password and the password has not been changed\n");
			return;
		}

		fp = fopen("fpassword.txt","w");

		if(fp == NULL)
		{
			printf("Failed to change password\n\n\n");
			return;
		}



		while(newPassword[i] != '\0')
			fputc(newPassword[i++], fp);

		fclose(fp);

	}
	else if(fnPassword(oldPassword) == 0)
        printf("\nThe system failed to check your password\n");
	else
        printf("\nYou entered the wrong password\n\n");
}

NODEPTR fnManageDatabase(NODEPTR head)
{
	int iChoice;
	char password[20];

	printf("\n\n\n\t1.AddRecord\n\t2.Delete Record\n\t3.Add Products\n\t4.Check suggestions\n\t");
	printf("5.Check Out of Stock products\n\t6.Back to main menu\n\n\n");

	printf("Enter your choice\n");
	scanf("%d", &iChoice);

	switch(iChoice)
	{
		case 1: printf("Enter the password to add record\n");
				scanf("%s", password);

				if(fnPassword(password))
					head = fn_FAddRec(head);
				else
					printf("\nWrong password. Cannot add member\n");
				break;

		case 2: printf("Enter the password to add record\n");
				scanf("%s", password);
				if(fnPassword(password))
					head = fn_DelRec(head);
				else
					printf("\nWrong password. a you cannot delete member\n");
				break;

		case 3:	fnAddProducts();
				break;

		case 4:
				break;

		case 5:
				break;

		case 6: break;


		default: printf("\nInvalid Choice. Try again\n");
	}

	return head;
}
void fnAddProducts(void)
{
	int brand, bill;
	int loop = 0;

	printf("\n\n");



	while(!loop)
	{
		brand = displayBrand();
		switch(brand)
		{
			case 1: bill = fnAddAppleProduct();
					break;
			case 2: bill = fnAddSamsungProduct();
					break;
			case 3: bill = fnAddXaomiProduct();
					break;
			case 4: bill = fnAddNokiaProduct();
					break;
			case 5: bill = fnAddAsusProduct();
					break;
			case 6: bill = fnAddAcerProduct();
					break;
			case 7: bill = fnAddHpProduct();
					break;
			case 8: bill = fnAddDellProduct();
					break;
			default: printf("\nWrong entry. Please try again\n");
		}
		printf("\nEnter 0 to add more products\n");
		scanf("%d", &loop);
	}
}



NODEPTR fn_FAddRec(NODEPTR head)
{
	NODEPTR first = head->link;
	NODEPTR prev = NULL, cur = first;
	NODEPTR temp = fnGetNode();

	int totalAmt = 0;
	int brand;
	int iChoice;
	int bill = 0;

	temp->name = (char *)malloc(sizeof(char));
	temp->link = NULL;

	char *cname;
	cname = (char *)malloc(sizeof(char));

	int c = 0;
	char cphn[11];

	printf("\n\tEnter name:\t");
	scanf("%s", cname);

	printf("\n\tEnter phn no:\t");

	label1:
	scanf("%s", cphn);

	if(strlen(cphn) != 10)
	{
		printf("\n\tPlease enter valid phone no:\t");
		goto label1;
	}

	if(fnMatch(head, atoi(cphn)))
	{
		printf("\nThe person is already a member\n");
		return head;
	}

	temp->phn = atoi(cphn);
	strcpy(temp->name, cname);

	printf("\n1.Add Item\n2.Create bill\n");
	scanf("%d", &iChoice);

	while(iChoice == 1)
	{
		brand = displayBrand();             //include this to be included

		switch(brand)
		{
			case 1: bill = appleProduct();
					break;
			case 2: bill = samsungProduct();
					break;
			case 3: bill = xaomiProduct();
					break;
			case 4: bill = nokiaProduct();
					break;
			case 5: bill = asusProduct();
					break;
			case 6: bill = acerProduct();
					break;
			case 7: bill = hpProduct();
					break;
			case 8: bill = dellProduct();
					break;
			default: printf("\nWrong entry. Please try again\n");
		}

		totalAmt += bill;

		printf("\n1.Add Item\n2.Create bill\n");
		scanf("%d", &iChoice);
	}

	if(((int)(totalAmt - totalAmt * NEWUSERDISCOUNT / 100)) < NEWMAXDIS)
		temp->pur_Amt = (int)(totalAmt - totalAmt * NEWUSERDISCOUNT / 100);
	else
		temp->pur_Amt = totalAmt - NEWMAXDIS;

	printf("\n\tAs your account is created");
	printf("\n\t\tYou get 15%% Discount");
	printf("\n\t\tYour bill is %d", temp->pur_Amt);

	if(first == NULL)
	{
		head->link = temp;
		head->info++;

		printf("\nRecord number %d is successfully created", head->info);

		return head;
	}

	if((strcmp(first->name, cname)) >= 0)
	{
		head->link = temp;
		temp->link = first;
		head->info++;

		printf("\n %d record is successfully created", head->info);

		return head;
	}

	cur = first;

	while(cur != NULL && strcmp(first->name, cname) < 0)
	{
		prev = cur;
		cur = cur->link;
	}

	head->info++;
	prev->link = temp;
	temp->link = cur;

	printf("\n%d record is successfully created\n\n",head->info);

	return head;
}




NODEPTR fn_DelRec(NODEPTR head)
{
	NODEPTR first = head->link;
    FILE *fp;

	fp=fopen("Hunny1.txt","r");

	long int phn;

	NODEPTR temp = NULL;  //can be done without using temp
	NODEPTR cur = first, prev = NULL;

	printf("\nEnter ph. No. of member to be delete:\t");
	scanf("%ld",&phn);

	if(first->link == NULL &&  phn == first->phn)
	{
		printf("\n%s record is deleted",first->name);

		head->link = NULL;
		free(first);

		return head;
	}

	while(cur != NULL && phn != cur->phn)
	{
		prev = cur;
		cur = cur->link;
	}

	if(cur == NULL)
	{
		printf("\nNo account with phn. No. %ld was found", phn);
		return head;
	}

	printf("\n%s record is deleted", cur->name);

	// prev->link = cur->link;

	// free(cur);

	temp = cur;
	prev->link = temp->link;

	free(temp);

	return head;
}



void fnSave(NODEPTR head)
{
	FILE *fp;
	NODEPTR first = head->link;
	char ch;
	int i;

	fp = fopen("Hunny1.txt", "w");

	if(fp == NULL)
	{
		printf("\nFailed to save the file. All data has been lost");

		for(i = 0; i <= 99999999; i++)
			for(i = 0; i <= 99999999; i++);

		exit(0);
	}


//how to delete contents of a file using c. it might be required here

	/*if(first == NULL) //not needed
	{
		fclose(fp);
		exit(0);
	}
	*/

	while(first != NULL)
	{
		fprintf(fp,"\n%s\t\t%ld\t\t%d", first->name, first->phn, first->pur_Amt);
		first = first->link;
	}

	fclose(fp);
	exit(0);
}


NODEPTR fnLoad(NODEPTR head, char *cname, long int phn, int pur_Amt)
{
    NODEPTR cur, temp = fnGetNode();

    temp->name = cname;
	temp->phn = phn;
	temp->pur_Amt = pur_Amt;

    printf("\n%s\n", cname);

    temp->link = NULL;


    cur = head;

    if(cur->link == NULL)
    {
        head->link = temp;
        head->info = 1;
        return head;
    }

    while(cur->link != NULL)
        cur = cur->link;

    cur->link = temp;

	head->info++;



	return head;
}
NODEPTR fnSale(NODEPTR head)
{
	int iChoice;
	char password[20];

	while(1)
	{
		printf("\n\nWhich day is it\n");
		printf("1.SUNDAY\n2.Festival\n3.Normal day\n4.Back to main menu\n5.Add Member\n\n");
		scanf("%d", &iChoice);

		switch(iChoice)
		{
			case 1:

			case 2: head = fnSundayPurchase(head);
					break;

			case 3: head = fnNormalDayPurchase(head);
					break;

			case 4: return head;

			case 5: printf("\nEnter the password\n");
    				scanf("%s", password);

					if(fnPassword(password))
						head = fn_FAddRec(head);
					else
						printf("\nWrong password. Cannot add member\n");
					break;

			default:printf("\nInvalid choice. Try again\n");
		}
	}

	return head; //return;
}


bool fnMatch(NODEPTR head, long int phNo)
{
	NODEPTR first = head->link;

	NODEPTR cur = first;

	if(first == NULL)
	{
		printf("\nNo members yet. Add frist member\n");
		return false;
	}

	if(first->link == NULL &&  phNo == first->phn)
	{
		printf("\nMember name is %s\n", first->name);
		return true;
	}

	while(cur != NULL && phNo != cur->phn)
	{
		cur = cur->link;
	}

	if(cur == NULL)
	{
		printf("\nNo account with phn. No. %ld was found", phNo);
		return false;
	}

	return true;
}


NODEPTR fnSundayPurchase(NODEPTR head)
{
	int phNo;
	int choice;
	int totalAmt = 0;
	int brand;
	int iChoice;
	int bill = 0;

	NODEPTR temp = fnGetNode();

	while(1)
	{
		printf("\n\n1.Billing\n2.Back and select the day again\n\n");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1: printf("\nEnter the phone number\n");
					scanf("%ld", &phNo);

					///*
					//check if this code is right. introduce a function to check if the entered number is correct
					while(!((int)(phNo)/100000000 >= 1 || (int)(phNo)/1000000000 != 0 && (int)(phNo)/10000000000 == 0))
					{
						printf("\n\tPlease enter valid phone no:\t");
						printf("\nEnter a valid phone number\n");
						scanf("%ld", &phNo);
					}
					//*/
					if(!fnMatch(head, phNo))
					{
						printf("\nNot a member. Proceeding for normal billing\n");
						fnNormalPurchase();
						break;
					}

					printf("\n1.Add Item\n2.Create bill\n");
					scanf("%d", &iChoice);

					while(iChoice == 1)
					{
						brand = displayBrand();             //include this to be included

						switch(brand)
						{
							case 1: bill = appleProduct();
									break;
							case 2: bill = samsungProduct();
									break;
							case 3: bill = xaomiProduct();
									break;
							case 4: bill = nokiaProduct();
									break;
							case 5: bill = asusProduct();
									break;
							case 6: bill = acerProduct();
									break;
							case 7: bill = hpProduct();
									break;
							case 8: bill = dellProduct();
									break;
							default: printf("\nWrong entry. Please try again\n");
						}

						totalAmt += bill;

						printf("\n1.Add Item\n2.Create bill\n");
						scanf("%d", &iChoice);
					}

					if((int)(totalAmt - totalAmt * SUNDAYDISCOUNT / 100) < SUNMAXDIS)
						temp->pur_Amt = (int)(totalAmt - totalAmt * SUNDAYDISCOUNT / 100);
					else
						temp->pur_Amt = totalAmt - SUNMAXDIS;
					printf("The total billed amount is %d\n", temp->pur_Amt);

					head = fnAddAmt(head, phNo, totalAmt);

					fnFeedBack();
					break;

			case 2: return head;

			default:printf("\nInvalid Choice. Please try again\n");
		}
	}

	return head;
}


NODEPTR fnNormalDayPurchase(NODEPTR head)
{
	int phNo;
	int bill;
	int iChoice;
	int choice;
	int brand;
	int totalAmt;

	while(1)
	{
		printf("\n\n1.Billing\n2.Back and select the day again\n\n");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:	printf("\nEnter the phone number\n");
					scanf("%ld", &phNo);

					if(!fnMatch(head, phNo))
					{
						printf("\nNot a member. Proceeding for normal billing\n");
						fnNormalPurchase();
						break;
					}


					printf("\n1.Add Item\n2.Create bill\n");
					scanf("%d", &iChoice);

					while(iChoice == 1)
					{
						brand = displayBrand();

						switch(brand)
						{
							case 1: bill = appleProduct();
									break;
							case 2: bill = samsungProduct();
									break;
							case 3: bill = xaomiProduct();
									break;
							case 4: bill = nokiaProduct();
									break;
							case 5: bill = asusProduct();
									break;
							case 6: bill = acerProduct();
									break;
							case 7: bill = hpProduct();
									break;
							case 8: bill = dellProduct();
									break;
							default: printf("\nWrong entry. Please try again\n");
						}

						totalAmt += bill;

						printf("\n1.Add Item\n2.Create bill\n");
						scanf("%d", &iChoice);
					}

					printf("\nTotal billed amount is Rs%d\n", totalAmt);

					head = fnAddAmt(head, phNo, totalAmt);

					fnFeedBack();
					return head;

			case 2: return head;

			default:printf("\nInvalid Choice. Please try again\n");
		}
	}

	return head;

}


void fnNormalPurchase(void)
{
	int totalAmt = 0;
	int brand;
	int iChoice;
	int bill = 0;

	printf("\n1.Add Item\n2.Create bill\n");

	scanf("%d", &iChoice);
	while(iChoice == 1)
	{
		brand = displayBrand();

		switch(brand)
		{
			case 1: bill = appleProduct();
					break;
			case 2: bill = samsungProduct();
					break;
			case 3: bill = xaomiProduct();
					break;
			case 4: bill = nokiaProduct();
					break;
			case 5: bill = asusProduct();
					break;
			case 6: bill = acerProduct();
					break;
			case 7: bill = hpProduct();
					break;
			case 8: bill = dellProduct();
					break;
			default: printf("\nWrong entry. Please try again\n");
		}

		totalAmt += bill;

		printf("\n1.Add Item\n2.Create bill\n");
		scanf("%d", &iChoice);
	}


	printf("\nTotal amount to be paid is Rs%d\n", totalAmt);

	fnFeedBack();

}




NODEPTR fnAddAmt(NODEPTR head, long int phn, int  bill)
{
	NODEPTR cur = head->link;

	while(cur != NULL && phn != cur->phn)
	{
		cur = cur->link;
	}

	if(cur == NULL)
	{
		printf("\nCounld not add money of this purchase. Sorry for the inconvinence\n");
		return head;
	}

	cur->pur_Amt = cur->pur_Amt + bill; //cur->pur_Amt += bill;

	//printf("Total shoped value till now is %d", cur->pur_Amt);

	return head;
}


int displayBrand(void)
{
	int brand;

	printf("\nChoose the Brand\n");

	printf("\n\t1.Apple\n\t2.Samsung\n\t3.Xaomi\n\t4.Nokia");
	printf("\n\t5.Asus\n\t6.Acer\n\t7.HP\n\t8.Dell\n\n");
	//printf("\n9.Done billing\n");

	scanf("%d", &brand);

	return brand;
}


int appleProduct()
{
	int iChoice;
	FILE *fp;
	int iNo;
	char product[200];
	int iPrice;
	int select;
	int i = 0;

	fp = fopen("appleProduct.txt", "r");

	if(fp == NULL)
	{
		printf("\nThe pdoduct file of apple no longer exites\n");
		return 0;
	}


	printf("\nItem No.\t\tName\tPrice\n");
	while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
	{
		printf("%d\t%s\t%d", iNo, product, iPrice);
		printf("\n");
		i++;
	}

	if(i == 0)
	{
		printf("\nNo product found. Add the product.\n");
		return (fnAddAppleProduct());
	}

	printf("\npress 999 to go back\n");
	printf("\nChoose pruduct from above or enter 0 to add product\n");
	//lable2:
	scanf("%d", &select);
	while(1)
	{

		if(select == 999)
        {
           fclose(fp);
			return 0;
        }

        if(select == 0)
        {
            fclose(fp);
            return (fnAddAppleProduct());
        }


		fseek(fp, 0l, SEEK_SET);
		while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
			if(iNo == select)
            {
                fclose(fp);
                return iPrice;
            }


			printf("\nWrong choice. Try again.\n");
			//goto lable2;
			scanf("%d", &select);

	 }



}

int fnAddAppleProduct()
{
	FILE *fp;
	char addName[200];
	int addNo;
	int addPrice;
	int chkNo;
	int flag = 0;


	fp = fopen("appleProduct.txt", "r");
	fseek(fp, 0l, SEEK_END);

	int size = ftell(fp);

    fseek(fp, 0l, SEEK_SET);

	if(!size)
	{
		printf("Enter the product ID\n");
		scanf("%d",&addNo);
	}
	else
	{
		while(flag == 0)
		{
		    fseek(fp, 0l, SEEK_SET);

			printf("Enter the product ID\n");
			scanf("%d",&addNo);

			while(fscanf(fp, "%d%s%d", &chkNo, addName, &addPrice) != EOF)
			{

				if(chkNo == addNo)
				{
					printf("%s already exits with product id %d\n", addName, addNo);
					flag = 0;
					break;
				}
				else
					flag = 1;
			}
		}
	}


	fclose(fp);

	printf("Enter the name of product\n");
	scanf("%s", addName); getchar();
	printf("Enter the price of the %s product\n", addName);
	scanf("%d", &addPrice);

	fp = fopen("appleProduct.txt", "a");

	fprintf(fp,"%d\t%s\t%d\n", addNo, addName, addPrice);

	fclose(fp);

	return addPrice;
}


int samsungProduct()
{
	int iChoice;
	FILE *fp;
	int iNo;
	char product[200];
	int iPrice;
	int select;
	int i = 0;

	fp = fopen("samsungProduct.txt", "r");

	if(fp == NULL)
	{
		printf("\nThe pdoduct file of samsung no longer exites\n");
		return 0;
	}

	printf("\nItem No.\t\tName\tPrice\n");
	while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
	{
		printf("%d\t%s\t%d", iNo, product, iPrice);
		printf("\n");
		i++;
	}

	if(i == 0)
	{
		printf("\nNo product found. Add the product.\n");
		return (fnAddSamsungProduct());
	}

	printf("\npress 999 to go back\n");
	printf("\nChoose pruduct from above or enter 0 to add product\n");
	//lable2:
	scanf("%d", &select);
	while(1)
	{

		if(select == 999)
        {

            fclose(fp);
			return 0;
        }
        if(select == 0)
        {
            fclose(fp);
            return (fnAddSamsungProduct());
        }


		fseek(fp, 0l, SEEK_SET);
		while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
			if(iNo == select)
            {
                fclose(fp);
                return iPrice;
            }


			printf("\nWrong choice. Try again.\n");
			//goto lable2;
			scanf("%d", &select);

	 }


}

int fnAddSamsungProduct()
{
	FILE *fp;
	char addName[200];
	int addNo;
	int addPrice;

	int chkNo;
	int flag = 0;
	int i = 0;

	fp = fopen("samsungProduct.txt", "r");

	fseek(fp, 0l, SEEK_END);

	int size = ftell(fp);

    fseek(fp, 0l, SEEK_SET);

	if(!size)
	{
		printf("Enter the product ID\n");
		scanf("%d",&addNo);
	}
	else
	{
		while(flag == 0)
		{
		    fseek(fp, 0l, SEEK_SET);

			printf("Enter the product ID\n");
			scanf("%d",&addNo);

			while(fscanf(fp, "%d%s%d", &chkNo, addName, &addPrice) != EOF)
			{

				if(chkNo == addNo)
				{
					printf("%s already exits with product id %d\n", addName, addNo);
					flag = 0;
					break;
				}
				else
					flag = 1;
			}
		}
	}

	fclose(fp);

	printf("Enter the name of product\n");
	scanf("%s", addName);
	printf("Enter the price of the %s product\n", addName);
	scanf("%d", &addPrice);


	fp = fopen("samsungProduct.txt", "a");

	fprintf(fp,"%d\t%s\t%d\n", addNo, addName, addPrice);

	fclose(fp);

	return addPrice;
}

int xaomiProduct()
{
	int iChoice;
	FILE *fp;
	int iNo;
	char product[200];
	int iPrice;
	int select;
	int i = 0;

	fp = fopen("xaomiProduct.txt", "r");

	if(fp == NULL)
	{
		printf("\nThe pdoduct file of xaomi no longer exites\n");
		return 0;
	}

	printf("\nItem No.\t\tName\tPrice\n");
	while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
	{
		printf("%d\t%s\t%d", iNo, product, iPrice);
		printf("\n");
		i++;
	}

	if(i == 0)
	{
		printf("\nNo product found. Add the product.\n");
		return (fnAddXaomiProduct());
	}

	printf("\npress 999 to go back\n");
	printf("\nChoose pruduct from above or enter 0 to add product\n");
	//lable2:
	scanf("%d", &select);
	while(1)
	{

		if(select == 999)
        {
            fclose(fp);
			return 0;
        }

        if(select == 0)
        {
            fclose(fp);
            return (fnAddXaomiProduct());

        }

		fseek(fp, 0l, SEEK_SET);
		while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
			if(iNo == select)
            {
                fclose(fp);
                return iPrice;
            }


			printf("\nWrong choice. Try again.\n");
			//goto lable2;
			scanf("%d",&select);

	 }


}

int fnAddXaomiProduct(void)
{
	FILE *fp;
	char addName[200];
	int addNo;
	int addPrice;
	int flag = 0;
	int i = 0;
    int chkNo;

	fp = fopen("xaomiProduct.txt", "r");

	fseek(fp, 0l, SEEK_END);

    int size = ftell(fp);

    fseek(fp, 0l, SEEK_SET);

	if(!size)
	{
		printf("Enter the product ID\n");
		scanf("%d",&addNo);
	}
	else
	{
		while(flag == 0)
		{
		    fseek(fp, 0l, SEEK_SET);

			printf("Enter the product ID\n");
			scanf("%d",&addNo);

			while(fscanf(fp, "%d%s%d", &chkNo, addName, &addPrice) != EOF)
			{

				if(chkNo == addNo)
				{
					printf("%s already exits with product id %d\n", addName, addNo);
					flag = 0;
					break;
				}
				else
					flag = 1;
			}
		}
	}

	fclose(fp);

	printf("Enter the name of product\n");
	scanf("%s", addName);
	printf("Enter the price of the %s product\n", addName);
	scanf("%d", &addPrice);


	fp = fopen("xaomiProduct.txt", "a");

	fprintf(fp,"%d\t%s\t%d\n", addNo, addName, addPrice);

	fclose(fp);

	return addPrice;
}

int nokiaProduct()
{
	int iChoice;
	FILE *fp;
	int iNo;
	char product[200];
	int iPrice;
	int select;
	int i = 0;

	fp = fopen("nokiaProduct.txt", "r");

	if(fp == NULL)
	{
		printf("\nThe pdoduct file of nokia no longer exites\n");
		return 0;
	}

	printf("\nItem No.\t\tName\tPrice\n");
	while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
	{
		printf("%d\t%s\t%d", iNo, product, iPrice);
		printf("\n");
		i++;
	}

	if(i == 0)
	{
		printf("\nNo product found. Add the product.\n");
		return (fnAddNokiaProduct());
	}

	printf("\npress 999 to go back\n");
	printf("\nChoose pruduct from above or enter 0 to add product\n");
	//lable2:
	scanf("%d", &select);
	while(1)
	{

		if(select == 999)
        {

            fclose(fp);
			return 0;
        }
        if(select == 0)
        {
            fclose(fp);
            return (fnAddNokiaProduct());
        }


		fseek(fp, 0l, SEEK_SET);
		while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
			if(iNo == select)
            {
                fclose(fp);
                return iPrice;
            }


			printf("\nWrong choice. Try again.\n");
			//goto lable2;
			scanf("%d", &select);

	 }


}

int fnAddNokiaProduct(void)
{
	FILE *fp;
	char addName[200];
	int addNo;
	int addPrice;
	int flag = 0;
    int chkNo;
    int i = 0;

	fp = fopen("nokiaProduct.txt", "r");

	fseek(fp, 0l, SEEK_END);

	int size = ftell(fp);

    fseek(fp, 0l, SEEK_SET);

	if(!size)
	{
		printf("Enter the product ID\n");
		scanf("%d",&addNo);
	}
	else
	{
		while(flag == 0)
		{
		    fseek(fp, 0l, SEEK_SET);

			printf("Enter the product ID\n");
			scanf("%d",&addNo);

			while(fscanf(fp, "%d%s%d", &chkNo, addName, &addPrice) != EOF)
			{

				if(chkNo == addNo)
				{
					printf("%s already exits with product id %d\n", addName, addNo);
					flag = 0;
					break;
				}
				else
					flag = 1;
			}
		}
	}

	fclose(fp);

	printf("Enter the name of product\n");
	scanf("%s", addName);
	printf("Enter the price of the %s product\n", addName);
	scanf("%d", &addPrice);

	fp = fopen("nokiaProduct.txt", "a");

	fprintf(fp,"%d\t%s\t%d\n", addNo, addName, addPrice);

	fclose(fp);

	return addPrice;
}

int asusProduct()
{
	int iChoice;
	FILE *fp;
	int iNo;
	char product[200];
	int iPrice;
	int select;
	int i = 0;

	fp = fopen("asusProduct.txt", "r");

	if(fp == NULL)
	{
		printf("\nThe pdoduct file of asus no longer exites\n");
		return 0;
	}

	printf("\nItem No.\t\tName\tPrice\n");
	while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
	{
		printf("%d\t%s\t%d", iNo, product, iPrice);
		printf("\n");
		i++;
	}

	if(i == 0)
	{
		printf("\nNo product found. Add the product.\n");
		return (fnAddAsusProduct());
	}

	printf("\npress 999 to go back\n");
	printf("\nChoose pruduct from above or enter 0 to add product\n");
	//lable2:
	scanf("%d", &select);
	while(1)
	{

		if(select == 999)
        {
            fclose(fp);
			return 0;

        }

        if(select == 0)
        {
            fclose(fp);
            return (fnAddAsusProduct());
        }


		fseek(fp, 0l, SEEK_SET);
		while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
			if(iNo == select)
            {
                fclose(fp);
                return iPrice;
            }


			printf("\nWrong choice. Try again.\n");
			//goto lable2;
			scanf("%d", &select);

	 }


}

int fnAddAsusProduct(void)
{
	FILE *fp;
	char addName[200];
	int addNo;
	int addPrice;
	int flag = 0;
    int chkNo;
    int i = 0;

	fp = fopen("asusProduct.txt", "r");

	fseek(fp, 0l, SEEK_END);

	int size = ftell(fp);

    fseek(fp, 0l, SEEK_SET);

	if(!size)
	{
		printf("Enter the product ID\n");
		scanf("%d",&addNo);
	}
	else
	{
		while(flag == 0)
		{
		    fseek(fp, 0l, SEEK_SET);

			printf("Enter the product ID\n");
			scanf("%d",&addNo);

			while(fscanf(fp, "%d%s%d", &chkNo, addName, &addPrice) != EOF)
			{

				if(chkNo == addNo)
				{
					printf("%s already exits with product id %d\n", addName, addNo);
					flag = 0;
					break;
				}
				else
					flag = 1;
			}
		}
	}

	fclose(fp);

	printf("Enter the name of product\n");
	scanf("%s", addName);
	printf("Enter the price of the %s product\n", addName);
	scanf("%d", &addPrice);


	fp = fopen("asusProduct.txt", "a");

	fprintf(fp,"%d\t%s\t%d\n", addNo, addName, addPrice);

	fclose(fp);

	return addPrice;
}

int acerProduct()
{
	int iChoice;
	FILE *fp;
	int iNo;
	char product[200];
	int iPrice;
	int select;
	int i = 0;

	fp = fopen("acerProduct.txt", "r");

	if(fp == NULL)
	{
		printf("\nThe pdoduct file of acer no longer exites\n");
		return 0;
	}

	printf("\nItem No.\t\tName\tPrice\n");
	while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
	{
		printf("%d\t%s\t%d", iNo, product, iPrice);
		printf("\n");
		i++;
	}

	if(i == 0)
	{
		printf("\nNo product found. Add the product.\n");
		return (fnAddAcerProduct());
	}

	printf("\npress 999 to go back\n");
	printf("\nChoose pruduct from above or enter 0 to add product\n");
	//lable2:
	scanf("%d", &select);
	while(1)
	{

		if(select == 999)
        {
            fclose(fp);
			return 0;
        }

        if(select == 0)
        {
            fclose(fp);
            return (fnAddAcerProduct());
        }


		fseek(fp, 0l, SEEK_SET);
		while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
			if(iNo == select)
            {
                fclose(fp);
                return iPrice;

            }


			printf("\nWrong choice. Try again.\n");
			//goto lable2;
			scanf("%d", &select);

	 }


}

int fnAddAcerProduct(void)
{
	FILE *fp;
	char addName[200];
	int addNo;
	int addPrice;
	int flag = 0;
    int chkNo;
    int i = 0;

	fp = fopen("acerProduct.txt", "r");

	fseek(fp, 0l, SEEK_END);

	int size = ftell(fp);

    fseek(fp, 0l, SEEK_SET);

	if(!size)
	{
		printf("Enter the product ID\n");
		scanf("%d",&addNo);
	}
	else
	{
		while(flag == 0)
		{
		    fseek(fp, 0l, SEEK_SET);

			printf("Enter the product ID\n");
			scanf("%d",&addNo);

			while(fscanf(fp, "%d%s%d", &chkNo, addName, &addPrice) != EOF)
			{

				if(chkNo == addNo)
				{
					printf("%s already exits with product id %d\n", addName, addNo);
					flag = 0;
					break;
				}
				else
					flag = 1;
			}
		}
	}

	fclose(fp);

	printf("Enter the name of product\n");
	scanf("%s", addName);
	printf("Enter the price of the %s product\n", addName);
	scanf("%d", &addPrice);


	fp = fopen("acerProduct.txt", "a");

	fprintf(fp,"%d\t%s\t%d\n", addNo, addName, addPrice);

	fclose(fp);

	return addPrice;
}

int hpProduct()
{
	int iChoice;
	FILE *fp;
	int iNo;
	char product[200];
	int iPrice;
	int select;
	int i = 0;

	fp = fopen("hpProduct.txt", "r");

	if(fp == NULL)
	{
		printf("\nThe pdoduct file of HP no longer exites\n");
		return 0;
	}

	printf("\nItem No.\t\tName\tPrice\n");
	while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
	{
		printf("%d\t%s\t%d", iNo, product, iPrice);
		printf("\n");
		i++;
	}

	if(i == 0)
	{
		printf("\nNo product found. Add the product.\n");
		return (fnAddHpProduct());
	}

	printf("\npress 999 to go back\n");
	printf("\nChoose pruduct from above or enter 0 to add product\n");
	//lable2:
	scanf("%d", &select);
	while(1)
	{

		if(select == 999)
		{
            fclose(fp);
			return 0;
		}

        if(select == 0)
        {
           fclose(fp);
           return (fnAddHpProduct());

        }

		fseek(fp, 0l, SEEK_SET);
		while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
        {
            if(iNo == select)
            {
                fclose(fp);
                return iPrice;
            }


        }


			printf("\nWrong choice. Try again.\n");
			//goto lable2;
			scanf("%d", &select);
		}


}

int fnAddHpProduct(void)
{
	FILE *fp;
	char addName[200];
	int addNo;
	int addPrice;
	int flag = 0;
    int chkNo;
    int i = 0;

	fp = fopen("hpProduct.txt", "r");

	fseek(fp, 0l, SEEK_END);

	int size = ftell(fp);

    fseek(fp, 0l, SEEK_SET);

	if(!size)
	{
		printf("Enter the product ID\n");
		scanf("%d",&addNo);
	}
	else
	{
		while(flag == 0)
		{
		    fseek(fp, 0l, SEEK_SET);

			printf("Enter the product ID\n");
			scanf("%d",&addNo);

			while(fscanf(fp, "%d%s%d", &chkNo, addName, &addPrice) != EOF)
			{

				if(chkNo == addNo)
				{
					printf("%s already exits with product id %d\n", addName, addNo);
					flag = 0;
					break;
				}
				else
					flag = 1;
			}
		}
	}

	fclose(fp);

	printf("Enter the name of product\n");
	scanf("%s", addName);
	printf("Enter the price of the %s product\n", addName);
	scanf("%d", &addPrice);

	fp = fopen("hpProduct.txt", "a");

	fprintf(fp,"%d\t%s\t%d\n", addNo, addName, addPrice);

	fclose(fp);

	return addPrice;
}

int dellProduct()
{
	int iChoice;
	FILE *fp;
	int iNo;
	char product[200];
	int iPrice;
	int select;
	int i = 0;

	fp = fopen("dellProduct.txt", "r");

	if(fp == NULL)
	{
		printf("\nThe pdoduct file of dell no longer exites\n");
		return 0;
	}

	printf("\nItem No.\t\tName\tPrice\n");
	while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
	{
		printf("%d\t%s\t%d", iNo, product, iPrice);
		printf("\n");
		i++;
	}

	if(i == 0)
	{
		printf("\nNo product found. Add the product.\n");
		return (fnAddDellProduct());
	}

	printf("\npress 999 to go back\n");
	printf("\nChoose pruduct from above or enter 0 to add product\n");
	//lable2:
	scanf("%d", &select);
	while(1)
	{

		if(select == 999)
        {
            fclose(fp);
            return 0;
        }

        if(select == 0)
        {

            fclose(fp);
            return (fnAddDellProduct());
        }


		fseek(fp, 0l, SEEK_SET);
		while(fscanf(fp,"%d%s%d", &iNo, product, &iPrice) != EOF)
			if(iNo == select)
            {

                fclose(fp);
                return iPrice;
            }


			printf("\nWrong choice. Try again.\n");
			//goto lable2;
			scanf("%d", &select);

	 }


}

int fnAddDellProduct(void)
{
	FILE *fp;
	char addName[200];
	int addNo;
	int addPrice;
	int flag = 0;
    int chkNo;
    int i = 0;

	fp = fopen("dellProduct.txt", "r");

	fseek(fp, 0l, SEEK_END);

	int size = ftell(fp);

    fseek(fp, 0l, SEEK_SET);

	if(!size)
	{
		printf("Enter the product ID\n");
		scanf("%d",&addNo);
	}
	else
	{
		while(flag == 0)
		{
		    fseek(fp, 0l, SEEK_SET);

			printf("Enter the product ID\n");
			scanf("%d",&addNo);

			while(fscanf(fp, "%d%s%d", &chkNo, addName, &addPrice) != EOF)
			{

				if(chkNo == addNo)
				{
					printf("%s already exits with product id %d\n", addName, addNo);
					flag = 0;
					break;
				}
				else
					flag = 1;
			}
		}
	}

	fclose(fp);

	printf("Enter the name of product\n");
	scanf("%s", addName);
	printf("Enter the price of the %s product\n", addName);
	scanf("%d", &addPrice);

	fp = fopen("dellProduct.txt", "a");

	fprintf(fp,"%d\t%s\t%d\n", addNo, addName, addPrice);

	fclose(fp);

	return addPrice;
}

int fnInputAmt(void)
{
	int bill;

	printf("\nEnter the amount\n");
	scanf("%d", &bill);

	return bill;
}

void fnFeedBack(void)
{
	int iChoice;

	printf("\n1.Suggestion\n2.Something you didn't find\n3.Greviences\n4.Not Intrested\n");
	scanf("%d", &iChoice);

	switch(iChoice)
	{
		case 1: fnSuggestion();
				break;

		case 2:	fnOutOfStock();
				break;

		case 3: fnGreviences();
				break;

		case 4: return;

		default:printf("\nWrong choice. Please try again\n");
	}
}

void fnSuggestion(void)
{
	int i=0;      //file pointing to suggestions.txt
	int slen=0;
	FILE *fp;
	char suggestions[1000];

	fp=fopen("suggestion.txt","a");
	//char *suggestions;

	//suggestions=(char *)malloc(sizeof(char));

	if(fp==NULL)
	{
		printf("\nFile cannot be opened in FnSuggestion");
		exit(0);
	}

	printf("\n\tPlease give your suggestions  (end with '#'):\n\t");
	scanf("%[^#]s",suggestions);

	slen=strlen(suggestions);

//	printf("\nString length is :%d",slen);
	while(i<(strlen(suggestions)-1))
	{
		if(suggestions[i]==' ')
		{
			suggestions[i]='_';
		}
		else if(suggestions[i]=='\0'||suggestions[0]!=10||isblank(suggestions[i]))
		{
			suggestions[i]='.';
		}
		i++;
	}

	suggestions[i] = '\0';
    fprintf(fp,"%s",suggestions);
	printf("\nThank you for your visit\nVISIT AGAIN\t\t\n");
	fclose(fp);

	getchar();
}

void fnOutOfStock(void)
{
	int i=0;      //file pointing to outofstock.txt
	int slen=0;
	char outofstock[1000];
	FILE *fp;
	//fp=fopen("outofstock.txt","a");
	//char *outofstock;

	fp=fopen("outofstock.txt","a");

	//outofstock=(char *)malloc(sizeof(char));

	if(fp==NULL)
	{
		printf("\nFile cannot be opened in FnOutofstock");
		exit(0);
	}

	printf("\n\tPlease give names of products that are outofstock  (end with '#'):\n\t");
	scanf("%[^#]s",outofstock);

	slen=strlen(outofstock);

//	printf("\nString length is :%d",slen);
	while(i<(strlen(outofstock)-1))
	{
		if(outofstock[i]==' ')
		{
			outofstock[i]='_';
		}
		else if(outofstock[i]=='\0'||outofstock[0]!=10||isblank(outofstock[i]))
		{
			outofstock[i]='.';
		}
		i++;
	}


	printf("\n%s",outofstock);
	fprintf(fp,"%s",outofstock);
	fclose(fp);

	getchar();
}

void fnGreviences(void)
{
	int i=0;      //file pointing to greviences.txt
	int slen=0;
	char greviences[1000];
	FILE *fp;
	//fp=fopen("greviences.txt","a");
	//char *greviences;

	fp=fopen("greviences.txt","a");

	//greviences=(char *)malloc(sizeof(char));

	if(fp==NULL)
	{
		printf("\nFile cannot be opened in fnGreviences");
		exit(0);
	}

	printf("\n\tPlease put in your greviences  (end with '#'):\n\t");
	scanf("%[^#]s",greviences);

	slen=strlen(greviences);

//	printf("\nString length is :%d",slen);
	while(i<(strlen(greviences)-1))
	{
		if(greviences[i]==' ')
		{
			greviences[i]='_';
		}
		else if(greviences[i]=='\0'||greviences[0]!=10||isblank(greviences[i]))
		{
			greviences[i]='.';
		}
		i++;
	}


	printf("\n%s",greviences);
	fprintf(fp,"%s",greviences);
	fclose(fp);

	getchar();
}
NODEPTR fnDistributeCoupons(NODEPTR head)
{
    NODEPTR first=head->link;
    if(first==NULL)
    {
        printf("\nNo members to distribute coupons\n");
        return NULL;
    }
    NODEPTR cur,prev,temp=NULL;
    cur=first;
    prev=NULL;
    while(cur->link!=NULL)
    {
        if((cur->pur_Amt)>(prev->pur_Amt))
        {
            temp=cur;
        }
        else if((prev->pur_Amt)>(cur->pur_Amt))
        {
            temp=prev;
        }
        else
        {
            prev=cur;
            cur=cur->link;
        }
    }
    return temp;
}
