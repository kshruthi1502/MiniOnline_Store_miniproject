#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
// structures
typedef struct{
    char name[15];
    char pass[10];
    char address[30];
}user;
struct clothing{
	char name[20];
	char id;
	float price;
}t;
struct Groceries
{
	char name[20];
	char id;
	float price;
}t1;
struct CovidEssentials
{
	char name[20];
	char id;
	float price;
}t2;

// declaration
void menu();
void shop();
void hidePass(char str[]);
int checkUser(char name[]);
void signUp();
void Login(char name[], char pass[]);
void displaylistofwomenclothing(struct clothing Wdetails[100]);

void sorteddisplaylistofwomenclothing(struct clothing Wdetails[100]);
void displaylistofmenclothing(struct clothing Mdetails[100]);
void sorteddisplaylistofmenclothing(struct clothing Mdetails[100]);
void displaylistofgroceries(struct Groceries Gdetails[100]);
void sorteddisplaylistofgroceries(struct Groceries Gdetails[100]);
void displaylistofCovidEssentials(struct CovidEssentials  Coviddetails[100]);
void sorteddisplaylistofCovidEssentials(struct CovidEssentials  Coviddetails[100]);
void addedtocart();
void Billing(int flag);
void deleteincart(int position);
int searchincart(int id);
void viewcart();
void viewfinallist();

//  Global decalration
char name[15];
char pass[10];
int login=0;
char add[30];
int registeruser=0;
int static flag;
char static user_name;
int cart[50];
float total_cost[50];
int quantity[20];
int sindex;
int len;
int quanindex;

void SetColor(int ForgC)
{
     WORD wColor;
     ///We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     ///We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        ///Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}


COORD coord = {0,0}; ///set the cordinate to 0, 0 (top-left corner of window);
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; /// X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



void hidePass(char str[])
{
    int i=0;
    char c=' ';
    while(i<=10)
    {
        str[i]=getch();
        c=str[i];
        if(c==13)break;
        else{
		printf("*");
           // printf("%c",c);
        i++;
        }
    }
    printf("\n");
    str[i]='\0';
}
int checkUser(char name[])
{
    FILE *fp=fopen("myfile13.dat","a+");
    user u[15];
    int i;
    fread(u,sizeof(user),20,fp);
    for(i=0;i<=15;i++)
    {
        if(strcmp(u[i].name,name)==0)
        {
            fclose(fp);
            return 0;
        }
        else
        {
        fclose(fp);
        return 1;
        }
    }
}

void signUp()
{
	system("cls");
	int registerchoice;
    char name[15];
    char pass[10];
    char cpass[10];
    
    int match,l;
    gotoxy(30,8);
    printf("\n\n\t\t\t Enter User Name  :\t");
    scanf("%s", name);
    if(!checkUser(name))
    {
    	gotoxy(30,10);
        printf("\n\n\n\t\t\t =============================================\n");
        printf("\n\n\n\n\t\t\t User Name already exists!\n");
        printf("\n\n\n\t\t\t To try again enter 1 else 2\n");
        printf("\n\n\n\t\t\t =============================================\n");
        int choice;
        scanf("%d", &choice);
        if(choice==1)
        {
            signUp();
        }
        else{
        	system("cls");
        	printf("\n\n\t\t\t =============================================\n");
            printf("\n\n\n\n\t\t\t Exiting\n");
            exit(1);
        }
    }
    else
    {
        printf("\n\n\t\t\t Enter password   :\t");
        hidePass(pass);
        printf("\n\n\t\t\t Confirm Password :\t");
        hidePass(cpass);
        if(strcmp(pass,cpass)==0){
            FILE *fp=fopen("myfile13.dat", "a+");
            if(fp==NULL)
            {
                printf("\n\t\t\t ERROR!\n");
                exit(1);
            }
	fflush(stdin);
	 printf("\n\n\t\t\t Enter Address    :\t");
	 scanf("%[^\n]%*c", add); 
	//puts(add);
            user u;
            strcpy(u.name,name);
            strcpy(u.pass,pass);
	    strcpy(u.address,add);
            fwrite(&u,sizeof(user),1,fp);
            fclose(fp);
            printf("\n\n\t\t\t =============================================\n");
	    registeruser=1;
	    system("cls");
            printf("\n\n\n\t\t\t\t Account created Successfully!\n");
            flag=1;
	    printf("\n\n\n\t\t\t Enter your choice \n\t\t\t 1.Do you want to shop\n\t\t\t 2.NO\n");
	    scanf("%d",&registerchoice);
	    switch(registerchoice){
		case 1:shop();
		       break;
		case 2:system("cls");
			   printf("\n\n\n\n\n\t\t\t\t\t EXITING!\n");
		       printf("\n\t\t\t\t THANK YOU! PLEASE VISIT AGAIN\n");
		       printf("********************************************************************************************\n");
		       exit(0);
	    }
        }
        else{
        	system("cls");
        	gotoxy(30,8);
			printf("\n\n\n\t\t\t =============================================\n");
            printf("\n\n\n\n\t\t\t Passwords doesn't match!\n");
            printf("\n\n\t\t\t To try again enter 1!\n\t\t\t Enter 2 to exit:\n");
            int choice;
            scanf("%d",&choice);
            if(choice==1)
            {
                signUp();
            }
            else{
                exit(1);
            }
        }

    }
}

void Login(char name[], char pass[])
{
	system("cls");
    FILE* fp=fopen("myfile13.dat","r");
    int i,l;
    user u[15];
    fread(u,sizeof(user),15,fp);
    for(i=0;i<15;i++)
    {
        if(strcmp(name,u[i].name)==0 && strcmp(pass,u[i].pass)==0){
            flag=0;
			login=1;
			gotoxy(30,8);
            printf("\n\n\n\t\t\t\t Login Successful!\n");
            printf("\n\n\n\t\t\t 1.Do you want to shop\n\t\t\t 2.No\n");
            printf("\n\n\n\t\t\t =============================================\n");
            scanf("%d",&l);
            switch(l)
            {
                case 1:shop();
                       break;
                case 2:system("cls");
                		gotoxy(30,8);
					   printf("\n\n\n\t\t\t\t Exiting!.");
		   			   printf("\n\n\t\t\t\tTHANK YOU! PLEASE VISIT AGAIN!\n");
		    		   printf("\n***************************************************************************************************\n");
                       exit(1);
                       // break;
                default:printf("\n\n\n\t\t\t\tInvalid choice try again!\n");
            }
            //break;
        }
       // break;
    }
    if(i==15)
    {
    	system("cls");
    	gotoxy(30,8);
        printf("\n\n\n\t\t\t\t NO SUCH USER FOUND!\n");
        printf("\n\n\t\t\t Choose one of the following\n");
        printf("\n\n\t\t\t 1.LOGIN\n\t\t\t 2.REGISTER\n\t\t\t 3.EXIT\n");
        int choice;
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
            	system("cls");
            	gotoxy(30,8);
                printf("\n\n\n\t\t\t Username:\t");
                scanf("%s", name);
                gotoxy(30,11);
                printf("\n\n\n\t\t\t Password:\t");
                hidePass(pass);
                Login(name,pass);
            case 2:
                signUp();
                break;
            default:
            	system("cls");
            	gotoxy(30,11);
		printf("\n\n\n\n\t\t\t\t THANK YOU! PLEASE VISIT AGAIN\n");
		printf("************************************************************************************************\n");
                printf("\n\n\t\t\t\t Exiting!\n");
                exit(1);
        }
    }
}




struct clothing Wdetails[10]={{"Jeans",1,999},
				{"Cargo pants",2,949},
				{"Jackets",3,699},{"Casual Trousers",4,799},{"A-line dress",5,899},{"Tops",6,499},
				{"Plazzo",7,799},{"Skirts",8,500},{"Salwar Suit",9,799},{"Sarees",10,3999}};
struct clothing Mdetails[10]={{"Jeans",11,887},
				{"Track Suit",12,3399},
				{"T-Shirt",13,500},{"Sweatshirt",14,899},{"Kurta",15,1099},{"Denim Jacket",16,2999},
				{"Padded Jacket",17,2099},{"Track Jacket",18,899},{"Casual Shirt",19,1399},{"Suits",20,5999}};
struct Groceries Gdetails[13]={{"Milk",21,20.0},
				{"Rice",22,200.0},
				{"Wheat",23,699},{"meat",24,800},{"grains",25,150.0},{"Curd ",26,30.0},
				{"Oils & sauces",27,799},{"Fruit bowl",28,600},{"Vegetable Bowl",29,799},{"cereals",30,399},{"Bread",31,25.0},{"Pulses",32,300},{"Condiments",33,1000}};
struct CovidEssentials Coviddetails[10]={{"Mask",34,20},
				{"Sanitizers",35,50},
				{"Face sheild",36,500},{"Hand Gloves",37,200},{"Head Cover",38,400},{"First Aid supplies",39,1000},
				{"Hand Wash",40,300},{"Soaps",41,50},{" Vaporiser",42,250},{"Disinfect Spray",43,1000}};								

void displaylistofwomenclothing(struct clothing Wdetails[100])
{
	SetColor(14);
	system("cls");	
	int i;
	gotoxy(25,8);
	printf("\n\t---------------------------------------------------------------------------------\n");
	printf("\tS.No\t|\t\tName\t\t|\tID\t|\tPrice\t\n");
		for(i=0;i<10;i++)
		{
		      printf("%12d%25s%21d%19.2f \n",i+1,Wdetails[i].name,Wdetails[i].id,Wdetails[i].price);
		}
	printf("\t---------------------------------------------------------------------------------\n");
}

void sorteddisplaylistofwomenclothing(struct clothing Wdetails[100])
{
	SetColor(14);
	system("cls");
	int i,j,k;
	for(i=0;i<10;i++)
    {
        for(j=0;j<9;j++)
        {
            if(Wdetails[j].price>Wdetails[j+1].price)
            {
                t=Wdetails[j];
                Wdetails[j]=Wdetails[j+1];
                Wdetails[j+1]=t;
            }
        }
    }
    gotoxy(25,8);
	printf("\n\t---------------------------------------------------------------------------------\n");
	printf("\tS.No\t|\t\tName\t\t|\tID\t|\tPrice\t\n");
		for(k=0;k<10;k++)
		{
		      printf("%12d%25s%21d%19.2f \n",k+1,Wdetails[k].name,Wdetails[k].id,Wdetails[k].price);
		}
	printf("\t---------------------------------------------------------------------------------\n");	
}
void displaylistofmenclothing(struct clothing Mdetails[100])
{
	SetColor(14);
	system("cls");	
	int i;
	gotoxy(25,8);
	printf("\n\t---------------------------------------------------------------------------------\n");
	printf("\tS.No\t|\t\tName\t\t|\tID\t|\tPrice\t\n");
	for(i=0;i<10;i++)
	{
		printf("%12d%25s%21d%19.2f \n",i+1,Mdetails[i].name,Mdetails[i].id,Mdetails[i].price);
	}
	printf("\t---------------------------------------------------------------------------------\n");
}
void sorteddisplaylistofmenclothing(struct clothing Mdetails[100])
{
	SetColor(14);
	system("cls");
	int i,j,k;
	for(i=0;i<10;i++)
    {
        for(j=0;j<9;j++)
        {
            if(Mdetails[j].price>Mdetails[j+1].price)
            {
                t=Mdetails[j];
                Mdetails[j]=Mdetails[j+1];
                Mdetails[j+1]=t;
            }
        }
    }
    gotoxy(25,8);
    printf("\n\t------------------------------------------------------------------------------------\n");
	printf("\tS.No\t|\t\tName\t\t|\tID\t|\tPrice\t\n");
	for(k=0;k<10;k++)
	{
		printf("%12d%25s%21d%19.2f \n",k+1,Mdetails[k].name,Mdetails[k].id,Mdetails[k].price);
	}
	printf("\t--------------------------------------------------------------------------------\n");
}
void displaylistofgroceries(struct Groceries Gdetails[100])
{
	SetColor(14);
	system("cls");	
	int i;
	gotoxy(25,8);
	printf("\n\t--------------------------------------------------------------------------------\n");
	printf("\tS.No\t|\t\tName\t\t|\tID\t|\tPrice\t\n");
	for(i=0;i<13;i++)
	{
		printf("%12d%25s%21d%19.2f \n",i+1,Gdetails[i].name,Gdetails[i].id,Gdetails[i].price);

	}printf("\t------------------------------------------------------------------------------\n");
}
void sorteddisplaylistofgroceries(struct Groceries Gdetails[100])
{		
	SetColor(14);
	system("cls");
	int i,j,k;
	for(i=0;i<13;i++)
    {
        for(j=0;j<12;j++)
        {
            if(Gdetails[j].price>Gdetails[j+1].price)
            {
                t1=Gdetails[j];
                Gdetails[j]=Gdetails[j+1];
                Gdetails[j+1]=t1;
            }
        }
    }
    gotoxy(25,8);
    printf("\n\t-----------------------------------------------------------------------------------\n");
	printf("\tS.No\t|\t\tName\t\t|\tID\t|\tPrice\t\n");
	for(k=0;k<13;k++)
	{
		printf("%12d%25s%21d%19.2f \n",k+1,Gdetails[k].name,Gdetails[k].id,Gdetails[k].price);

	}printf("\t-----------------------------------------------------------------------------\n");
}

void displaylistofCovidEssentials(struct CovidEssentials  Coviddetails[100])
{
	SetColor(14);
	system("cls");
	
	int i;
	gotoxy(25,8);
	printf("\n\t------------------------------------------------------------------------------\n");
	printf("\tS.No\t|\t\tName\t\t|\tID\t|\tPrice\t\n");
	for(i=0;i<10;i++)
	{
		printf("%12d%25s%21d%19.2f \n",i+1,Coviddetails[i].name,Coviddetails[i].id,Coviddetails[i].price);
	}
	printf("\t-------------------------------------------------------------------------------\n");
}

void sorteddisplaylistofCovidEssentials(struct CovidEssentials  Coviddetails[100])
{
	SetColor(14);
	system("cls");
	int i,j,k;
	for(i=0;i<10;i++)
    {
        for(j=0;j<9;j++)
        {
            if(Coviddetails[j].price>Coviddetails[j+1].price)
            {
                t2=Coviddetails[j];
                Coviddetails[j]=Coviddetails[j+1];
                Coviddetails[j+1]=t2;
            }
        }
    }
    gotoxy(25,8);
    printf("\n\t----------------------------------------------------------------------------------\n");
	printf("\tS.No\t|\t\tName\t\t|\tID\t|\tPrice\t\n");
	for(k=0;k<10;k++)
	{
		printf("%12d%25s%21d%19.2f \n",k+1,Coviddetails[k].name,Coviddetails[k].id,Coviddetails[k].price);
	}
	printf("\t------------------------------------------------------------------------------\n");
    
}

void menu()
{
	system("cls");
	SetColor(14);
	int n;
	printf("\n");
	gotoxy(25,8);
    printf("\n	  -----------------------------------------------------------------------     \n");
    printf("	|  1			 CLOTHING					 |    \n");
 printf("        |  2                	GROCERIES                             		 |    \n");
 printf("        |  3                    COVID ESSENTIALS                                 |    \n");
    printf("	  ------------------------------------------------------------------------    \n");
	SetColor(12);
	
}
void addedtocart()
{
	int i;
	printf("Added to cart \n");
	for(i=0;i<sindex;i++)
	{
		
		printf("%3d",cart[i]);

	}
}

void Billing(int flag)
{
	SetColor(14);
	system("cls");
	struct Customerinfo
	{
		char address[100];
		char number[10];
	}customer;
	//int s;
	//s=m;
	gotoxy(25,8);
	printf("\n\t---------------------------------------------------------------------------------------------------\n");
	printf("                                             BILL                                  \n");
	printf("\tS.no\t|\t\tName\t\t|\tID\t|\tQuantity\tPrice\tSubTotal\n");
	int i,j,sno=1;
	int costindex=0;
	int forquan=0;
	int q=0;
	for(i=0;i<sindex;i++)
	{
		if(cart[i]>=1 && cart[i]<=10)
		{
			for(j=0;j<10;j++)
			{
				if(cart[i]==Wdetails[j].id)
				{
					q=quantity[forquan++];
					printf("%12d%25s%21d%16d%19.2f%11.2f \n",sno,Wdetails[j].name,Wdetails[j].id,q,Wdetails[j].price,q*Wdetails[j].price);
					total_cost[costindex++]=Wdetails[j].price;
					sno++;	
				}
			}

		}
		else if(cart[i]>=11 &&cart[i]<=20)
		{
			for(j=0;j<10;j++)
			{
				if(cart[i]==Mdetails[j].id)
				{
					q=quantity[forquan++];
					printf("%12d%25s%21d%16d%19.2f%11.2f \n",sno,Mdetails[j].name,Mdetails[j].id,q,Mdetails[j].price,q*Mdetails[j].price);
					total_cost[costindex++]=Mdetails[j].price;
					sno++;
				}
			}
					
		}
		else if(cart[i]>=21 && cart[i]<=33)
		{
			for(j=0;j<13;j++)
			{
				if(cart[i]==Gdetails[j].id)
				{
					q=quantity[forquan++];
					printf("%12d%25s%21d%16d%19.2f%11.2f \n",sno,Gdetails[j].name,Gdetails[j].id,q,Gdetails[j].price,q*Gdetails[j].price);
					total_cost[costindex++]=Gdetails[j].price;
					sno++;
				}
			}
		}
		else
		{
			for(j=0;j<10;j++)
			{
				if(cart[i]==Coviddetails[j].id)
				{
					q=quantity[forquan++];
					printf("%12d%25s%21d%16d%19.2f%11.2f \n",sno,Coviddetails[j].name,Coviddetails[j].id,q,Coviddetails[j].price,q*Coviddetails[j].price);
					total_cost[costindex++]=Coviddetails[j].price;
					sno++;
				}
			}
		}

	}
	int k;
	float discount;
	float discounted_price;
	float bill=0;
	for(k=0;k<len;k++)
	{
		bill=bill+total_cost[k]*quantity[k];
	}
	//printf("%f",bill);
	printf("\t\t\t\t\n       YOUR TOTAL BILL IS                                                             		: %.2f\n",bill);
	if(registeruser!=1)
	{
		discount=(10*bill)/100;
		discounted_price=(bill-discount);
		printf("\t\n		YOUR TOTAL BILL AFTER DISCOUNT IS\t\t\t\t\t\t: %.2f\n",discounted_price);
	}
	printf("\t---------------------------------------------------------------------------------------------------\n");
	FILE *fptr;
	int n;
	char c;
	printf("\n\t\t\t 1.Confirm Order\n\t\t\t 2.Go back to main menu:");
	printf("\n\n\t\t\t Enter Your Choice  :     \t\t");
	scanf("%d",&n);
	if(n==1)
	{
		/*fptr=fopen("Info_customer.dat","wb");
		if(fptr==NULL)
		{
			printf("bh");
		}
		fflush(stdin);
		printf("\n\t\t\t Enter Your Full Address :\t\t");
		gets(customer.address);
	    printf("\n\t\t\t Enter Your Mobile Number:\t\t");
		gets(customer.number);
		fwrite(&customer,sizeof(customer),1,fptr);
		fclose(fptr);*/
		FILE* fp=fopen("myfile13.dat","r");
		user u[15];
    		fread(u,sizeof(user),15,fp);
	if(login==1)
	{
   	 	for(i=0;i<15;i++)
   	 	{
       	 		if(strcmp(name,u[i].name)==0 && strcmp(pass,u[i].pass)==0)
			{
				printf("\n\n\t\t\tYour order will be delivered to \n");
				//printf("%s",u[i].name);
				//printf("%s",u[i].pass);
				
				printf("\n\n\t\t\t%s",u[i].address);
				printf("\n\n\n\n\t\t\t\t\t Your Order is Confirmed\n");
			}
		}
	}
	else
	{
		printf("\n\n\t\t\tYour order will be delivered to \n");
		printf("\n\t\t\t%s\n",add);
	}
	SetColor(12);	
	
}

	
}
void deleteincart(int position)
{
	int i;
	for(i=position; i<sindex-1; i++)
        {
            cart[i] = cart[i + 1];
        }

        
        sindex--;
	
}
void deleteinquantity(int position)
{
	int i;
	for(i=position;i<quanindex-1;i++)
	{
		quantity[i]=quantity[i+1];
	}
	quanindex--;
}
int searchincart(int id)
{
	int i;
	for(i=0;i<sindex;i++)
	{
		if(cart[i]==id)
			return i;

	}
	return -1;
}
void viewcart()
{
	SetColor(14);
	system("cls");
	gotoxy(25,8);
	printf("\n\t---------------------------------------------------------------------------------------------------\n");
	printf("                                             CART                                                  \n");
	printf("\tS.no\t|\t\tName\t\t|\tID\t|\tQuantity\tPrice\t\n");
	int i,j,sno=1;
	int costindex=0;
	int forquan=0;
	for(i=0;i<sindex;i++)
	{
		if(cart[i]>=1 && cart[i]<=10)
		{
			for(j=0;j<10;j++)
			{
				if(cart[i]==Wdetails[j].id)
				{
					printf("%12d%25s%21d%16d%19.2f \n",sno,Wdetails[j].name,Wdetails[j].id,quantity[forquan++],Wdetails[j].price);
					total_cost[costindex++]=Wdetails[j].price;
					sno++;
				}
			}

		}
		else if(cart[i]>=11 &&cart[i]<=20)
		{
			for(j=0;j<10;j++)
			{
				if(cart[i]==Mdetails[j].id)
				{
					printf("%12d%25s%21d%16d%19.2f \n",sno,Mdetails[j].name,Mdetails[j].id,quantity[forquan++],Mdetails[j].price);
					total_cost[costindex++]=Mdetails[j].price;
					sno++;
				}
			}
					
		}
		else if(cart[i]>=21 && cart[i]<=33)
		{
			for(j=0;j<13;j++)
			{
				if(cart[i]==Gdetails[j].id)
				{
					printf("%12d%25s%21d%16d%19.2f \n",sno,Gdetails[j].name,Gdetails[j].id,quantity[forquan++],Gdetails[j].price);
					total_cost[costindex++]=Gdetails[j].price;
					sno++;
				}
			}
		}
		else
		{
			for(j=0;j<10;j++)
			{
				if(cart[i]==Coviddetails[j].id)
				{
					printf("%12d%25s%21d%16d%19.2f \n",sno,Coviddetails[j].name,Coviddetails[j].id,quantity[forquan++],Coviddetails[j].price);
					total_cost[costindex++]=Coviddetails[j].price;
					sno++;
				}
			}
		}

	}
	printf("\t---------------------------------------------------------------------------------------------------\n");
	int ch,ele,newquan;
	do{
	printf("\n\t\t\t1.Do you want to remove any item\n\t\t\t2.Modify quantity\n\t\t\t3.No\n");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
		printf("\t\t\tEnter Item no\n");
		scanf("%d",&ele);
		int pos=searchincart(ele);
		if(pos!=-1)
		{
			deleteincart(pos);
			deleteinquantity(pos);
			printf("\t\t\tItem deleted\n");
		}
		else
			printf("\t\t\tItem not added to cart\n");
	   			break;
		case 2:
			printf("\n\t\t\tEnter Item id\n");
			scanf("%d",&ele);
			if(searchincart(ele)!=-1)
			{
			printf("\t\t\tEnter new quantity\n");	
			scanf("%d",&newquan);
			quantity[searchincart(ele)]=newquan;	
			printf("\t\t\tQuantity Modified!\n");
			}
			else
				printf("\t\t\tItem not added to cart\n");
				break;
		deafult:printf("\t\t\t\tInvalid choice!try again\n");
		
			

		}
	}while(ch!=3);
	printf("\t---------------------------------------------------------------------------------------------------\n");
	SetColor(12);
	len=sno-1;
}
void viewfinallist()
{
	SetColor(14);
	system("cls");
	gotoxy(25,8);
	printf("\n\t---------------------------------------------------------------------------------------------------\n");
	printf("                                             FINAL LIST                                  \n");
	printf("\tS.no\t|\t\tName\t\t|\tID\t|\tQuantity\tPrice\t\n");
	int i,j,sno=1;
	int costindex=0;
	int forquan=0;
	for(i=0;i<sindex;i++)
	{
		if(cart[i]>=1 && cart[i]<=10)
		{
			for(j=0;j<10;j++)
			{
				if(cart[i]==Wdetails[j].id)
				{
					printf("%12d%25s%21d%16d%19.2f \n",sno,Wdetails[j].name,Wdetails[j].id,quantity[forquan++],Wdetails[j].price);
					total_cost[costindex++]=Wdetails[j].price;
					sno++;
				}
			}

		}
		else if(cart[i]>=11 &&cart[i]<=20)
		{
			for(j=0;j<10;j++)
			{
				if(cart[i]==Mdetails[j].id)
				{
					printf("%12d%25s%21d%16d%19.2f \n",sno,Mdetails[j].name,Mdetails[j].id,quantity[forquan++],Mdetails[j].price);
					total_cost[costindex++]=Mdetails[j].price;
					sno++;
				}
			}
					
		}
		else if(cart[i]>=21 && cart[i]<=33)
		{
			for(j=0;j<13;j++)
			{
				if(cart[i]==Gdetails[j].id)
				{
					printf("%12d%25s%21d%16d%19.2f \n",sno,Gdetails[j].name,Gdetails[j].id,quantity[forquan++],Gdetails[j].price);
					total_cost[costindex++]=Gdetails[j].price;
					sno++;
				}
			}
		}
		else
		{
			for(j=0;j<10;j++)
			{
				if(cart[i]==Coviddetails[j].id)
				{
					printf("%12d%25s%21d%16d%19.2f \n",sno,Coviddetails[j].name,Coviddetails[j].id,quantity[forquan++],Coviddetails[j].price);
					total_cost[costindex++]=Coviddetails[j].price;
					sno++;
				}
			}
		}

	}
	printf("\t---------------------------------------------------------------------------------------------------\n");
	SetColor(12);
	len=sno-1;
}
void shop()
{
	system("cls");
	char ch;
	int num,n,op,itemnum,rating;
	SetColor(12);
	while(1){
       printf("\n\t\t\t \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
	printf("\n\t\t\t\t---------------------------------");
	printf("\n\t\t\t\t|\t1.VIEW CATEGORIES       |\n");
	printf("\n\t\t\t\t|\t2.START SHOPPING        |\n");
	printf("\n\t\t\t\t|\t3.VIEW CART             |\n");
	printf("\n\t\t\t\t|\t4.VIEW FINAL LIST       |\n");
	printf("\n\t\t\t\t|\t5.VIEW BILL             | \n");
	//printf("\n\t\t\t\t|\t6.RATING                |\n");
	printf("\n\t\t\t\t|\t6.EXIT                  |  \n");
	printf("\t\t\t\t---------------------------------\n");	
	printf("\n\t\t\t \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");	
	SetColor(12);
	scanf("%d",&n);
		switch(n)
		{
			case 1:system("cls");	
				menu();
			break;
				system("cls");

			case 2:system("cls");
				do{
				gotoxy(25,8);
				SetColor(14);
				printf("\n\t\t-------------------------------------------------------------- \t\n");
				printf("\n\t\t|\t ENTER CATEGORY YOU WANT TO ADD TO CART :\t\t|\n");
				printf("\t\t|\t\t 1.CLOTHING\t\t\t\t\t|\n\t\t|\t\t 2.GROCERIES\t\t\t\t\t|\n\t\t|\t\t 3.COVID ESSENTIALS\t\t\t\t|\n\t\t|\t\t 4.GOBACK\t\t\t\t\t|");
				printf("\n");
				printf("\n\t\t -------------------------------------------------------------- \t\n");
			       		scanf("%d",&num);
				SetColor(14);
				
			       switch(num)
			       {
				       case 1:system("cls");
				       		  gotoxy(25,8);
					   		  printf("\n\n\n\t\t\t\t 1.MEN'S CLOTHING\n\t\t\t\t 2.WOMEN'S CLOTHING");
				       		  printf("\n\t\t\t\t Choose Your Option :\t");
				       		  scanf(" %d",&op);
				       		  if(op==1)
				       		  {
							  printf("\n\t\t\t DO YOU WANT TO FILTER BY PRICE IF YES ENTER y\n");
							  scanf(" %c",&ch);
							  if(ch=='y'|| ch=='Y'){
				       		  		printf("\t\t\t\t FILTERED - LOW TO HIGH\n");
				       		    		sorteddisplaylistofmenclothing(Mdetails);
							  }
							  else
							  {
								  displaylistofmenclothing(Mdetails);
							  }
					      		printf("\t\t\t Enter item ID :\t");
					            	scanf("%d",&cart[sindex++]);
							printf("\n\t\t\t Enter quantity :\t");
							scanf("%d",&quantity[quanindex++]);
							printf("\n\t\t\t\t ADDED TO CART!\n");
							system("cls");
					         	break;
							  }
						  else
						  {
							  printf("\n\t\t\t DO YOU WANTER TO FILTER BY PRICE IF YES ENTER y\n");
							  scanf(" %c",&ch);
							  if(ch=='y')
							  {	printf("\t\t\t\t FILTERED - LOW TO HIGH\n");
		
					            		sorteddisplaylistofwomenclothing(Wdetails);
							  }
							  else
								  displaylistofwomenclothing(Wdetails);
					            	printf("\t\t\t Enter item ID :\t");
						      	scanf(" %d",&cart[sindex++]);
							printf("\n\t\t\t Enter quantity :\t");
							scanf("%d",&quantity[quanindex++]);
							printf("\n\t\t\t\t ADDED TO CART!\n");
							system("cls");
						      	break;	
						  }
				       case 2://displaylistofgroceries(Gdetails);
					      printf("\t\t\t DO YOU WANT TO FILTER BY PRICE IF YES ENTER y \n");
					      scanf(" %c",&ch);
					      if(ch=='y'){
						      printf("\t\t\t\t FILTERED - LOW TO HIGH\n");
						      sorteddisplaylistofgroceries(Gdetails);
					      }
					      else
						      displaylistofgroceries(Gdetails);
					          printf("\t\t\t Enter item ID :\t");
					          scanf("%d",&cart[sindex++]);
						  printf("\n\t\t\t Enter quantity :\t");
						  scanf("%d",&quantity[quanindex++]);
						  printf("\n\t\t\t\t ADDED TO CART!\n");
						  system("cls");
					          break;
				       case 3:	printf("\t\t\t DO YOU WANT TO FILTER BY PRICE IF YES ENTER y\n");
						scanf(" %c",&ch);
						if(ch=='y')
						{
							printf("\t\t\t\t FILTERED - LOW TO HIGH\n");
						 // displaylistofCovidEssentials(Coviddetails);
					          sorteddisplaylistofCovidEssentials(Coviddetails);
						}
						else
							displaylistofCovidEssentials(Coviddetails);

					          printf("\t\t\t Enter item ID :\t");
					          scanf("%d",&cart[sindex++]);
						  printf("\n\t\t\t Enter quantity :\t");
						  scanf("%d",&quantity[quanindex++]);
						  printf("\n\t\t\t\t ADDED TO CART!\n");
						  system("cls");
							break;
			             default:printf("\t\t\t\t\n");
		
									
					
					
			       }
			       }while(num!=4);
				SetColor(12);
			       break;

			case 3:viewcart();
				break;
			case 4:viewfinallist();
			       break;
			case 5:Billing(flag);
			       break;
			/*case 6:printf("\t\t\t\t Rate us from 1 to 5\n");
			       scanf("%d",&rating);
			       break;*/

			case 6:system("cls");
					gotoxy(30,8);
				   printf("\n\n\t\t\t ==========================================\n");
			       printf("\n\t\t\t\tRate us from 1 to 5 :\t");
			       scanf("%d",&rating);
			       system("cls");
				   printf("\n\n\n\t\t\t\t EXITING!");
			       printf("\n\n\t\t\t THANK YOU! PLEASE VISIT AGAIN\n");
			       printf("*******************************************************************************************************\n");
			       exit(0);
			       break;
			default:printf("\t\t\t\tInvalid choice try again!\n");
			  
		}
	}
}
int main()
{
	//drawRectangle();
    gotoxy(30,8);
    SetColor(35);
    printf("\n\t\t\t \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO XYZ STORE \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
    printf("\n\t\t\t\t\tChoose one of the following: \n");
    printf("\t\t\t\t\t1.LOGIN\n \t\t\t\t\t2.REGISTER\n \t\t\t\t\t3.EXIT\n");
    printf("\n\t\t\t \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
    int choice;
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:system("cls");
        		SetColor(12);
        		gotoxy(30,8);
				printf("\n\t\t\t Username:\t");
				SetColor(14);
            	scanf("%s", name);
            	SetColor(12);
            	gotoxy(30,11);
            	printf("\n\t\t\t Password:\t");
            	SetColor(14);
            	hidePass(pass);
            	printf("\n\t\t\t =============================================\n");
            Login(name,pass);
            break;
        case 2:
            signUp();
            break;
	case 3:
			system("cls");
            printf("\n\n\n\n\t\t\t\t\t Exiting!\n");
	    printf("\n\t\t\t\t THANK YOU! PLEASE VISIT AGAIN\n");
	    printf("**************************************************************************************************************************\n");
            exit(1);
	default:printf("\t\t\t\tInvalid choice try again!\n");
    }
	
	
					      
                                         return 0;
}