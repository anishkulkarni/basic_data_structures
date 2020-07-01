#include <stdio.h>
#include <stdlib.h> //header file inclusion

#define MAX_NAME 30 //Macro definition

typedef struct database
{
	char name[MAX_NAME];
	long int rollNo;
	char year[2];
	int div;
	char dept[4];
	long int mob;
}database;// structure to hold contents of database

void printMenu();

void getChoice(int *);

void initializeDatabase(database *,int);

database *createDatabase(int);

void displayDatabase(database);

void addRecord(database *);

int searchDatabase(database *,int);

void modifyRecord(database);

void printHeader();

void printLine();

int searchForRecord(database, char *);

void dataCopy(database *,database *);

int main(void)
{
	/*
		 * Input : none
		 * Utility : Main function to drive the program
		 * Output : Success or failure of program
	 */
	int i,index=0,size=0;
	database *data=NULL;
	char name[MAX_NAME];
	int choice;
	while (1)
	{
		printMenu();
		getChoice(&choice);
		if(choice==1 || choice==2 || choice==3 || choice==4 || choice==5 || choice==6 || choice==7)
		{
			switch (choice)
			{
			case 1:
				printf("Enter the number of records you want to add : ");
				scanf("%d",&size);
				data=(database *)malloc(size*sizeof(database));
				//initializeDatabase(data,size);
				printf("\nDatabase successfully created.\n\n");
				index=0;
				break;
			case 2:
				printf("\n");
				if(index==0)
				{
					printf("No records found.\n\n");
				}
				else
				{
					printLine();
					printf("\n");
					printHeader();
					printf("\n");
					printLine();
					printf("\n");
					for(i=0;i<index;i++)
					{
						displayDatabase(data[i]);
						printf("\n");
						printLine();
						printf("\n");
					}
					printf("\n");
				}
				break;
			case 3:
				if(data==NULL)
				{
					printf("\nPlease create a database first.\n\n");
					break;
				}
				printf("\n");
				while(getchar()!='\n');
				if(index==size+1)
				{
					printf("\nDatabase full.\nDelete some records to continue.\n\n");
					break;
				}
				addRecord(&data[index]);
				for(i=0;i<index;i++)
				{
					if(data[i].rollNo==data[index].rollNo)
					{
						printf("\nA record with this roll number already exists.\n\n");
						break;
					}
					if(data[i].mob==data[index].mob)
					{
						printf("\nA record with this mobile number already exists.\n\n");
						break;
					}
				}
				if(i!=index)
					break;
				else
				{
					printf("Record successfully added\n\n");
					index++;
					break;
				}
			case 4:
				printf("\n");
				i=searchDatabase(data,index);
				printf("\n");
				if(i!=-1&&i!=-2)
				{
					printLine();
					printf("\n");
					printHeader();
					printf("\n");
					printLine();
					printf("\n");
					displayDatabase(data[i]);
					printf("\n");
					printLine();
					printf("\n\n");
				}
				else if(i==-2)
					while(getchar()!='\n');
				else
					printf("Record not found.\n\n");
				break;
			case 5:
				printf("\n");
				i=searchDatabase(data,index);
				if(i!=-1&&i!=-2)
				{
					printf("\n");
					while(getchar()!='\n');
					addRecord(&data[i]);
					printf("Record successfully updated\n\n");
				}
				else if(i==-2)
					while(getchar()!='\n');
				else
				{
					printf("\n");
					printf("Previous record not found. Please add new record.");
					while(getchar()!='\n');
					addRecord(&data[index]);
					index ++;
					printf("Record successfully added\n\n");
				}
				break;
			case 6:
				printf("\n");
				i=searchDatabase(data,index);
				if(i!=-1&&i!=-2)
				{
					for(;i<index;i++)
						dataCopy(&data[i],&data[i+1]);
					index--;
					printf("\nRecord successfully deleted.\n\n");
				}
				else if(i==-2)
					while(getchar()!='\n');
				else
					printf("\nRecord not found.\n\n");
				break;
			case 7:
				return EXIT_SUCCESS;
				break;
			}
		}
		else
		{
			printf("\nPlease enter a valid choice.\n\n");
			while(getchar()!='\n');
		}
	}
	return EXIT_SUCCESS;
}

database *createDatabase(int size)
{
	printf("Reached in function create database");
	database *data;
	data=(database *)malloc(size*sizeof(database));
	return data;
}

void printMenu()
{
	/*
		 * Input : none
		 * Utility : To print the menu of the program
		 * Output : none
	 */
	printf("Menu\n1. Create database\n2. Display database\n3. Add record\n4. Search record\n5. Modify Record\n6. Delete Record\n7. Exit\nChoice : ");
}

void getChoice(int *choice)
{
	/*
		 * Input : none
		 * Utility : to get choice of the user
		 * Output : choice of user
	 */
	scanf("%d",choice);
}

void initializeDatabase(database data[],int size)
{
	/*
		 * Input : Array of structure variables
		 * Utility : Initialize all variables
		 * Output : none
	 */
	int i;
	for(i=0;i<size;i++)
	{
		data[i].name[0]='\0';
		data[i].rollNo=0;
		data[i].year[0]='\0';
		data[i].div=0;
		data[i].dept[0]='\0';
	}
}

void displayDatabase(database record)
{
	/*
		 * Input : variable of structure database
		 * Utility : Print values of members of structure variable
		 * Output : none
	 */
	printf("| %30s | %10s | %4s | %8d | %11ld | %10ld |",record.name,record.dept,record.year,record.div,record.rollNo,record.mob);
}

void addRecord(database *record)
{
	/*
		 * Input : pointer to variable of structure database
		 * Utility : input values of record
		 * Output : none
	 */
	printf("\nEnter the details of the record you want to add :");
	printf("\nName : ");
	gets(record->name);
	printf("Department : ");
	scanf("%s",record->dept);
	printf("Year : ");
	scanf("%s",record->year);
	printf("Division : ");
	scanf("%d",&record->div);
	printf("Roll number : ");
	scanf("%ld",&record->rollNo);
	printf("Mobile number : ");
	scanf("%ld",&record->mob);
}

int searchDatabase(database *data,int count)
{
	/*
		 * Input : array of structure database variables, position of latest record
		 * Utility : Search for required record
		 * Output : Position of record found
	 */
	int i,j,choice,index=0;
	long int rollNumber;
	char name[MAX_NAME];
	printf("Which field do you want to search by?\n1. Name\n2. Roll Number\nResponse : ");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:
		printf("Enter the name you want to search : ");
		scanf("%s",name);
		for(i=0;i<=count;i++)
		{
			for(j=0;name[j]!='\0';j++)
			{
				if(name[j]!=data[i].name[j])
					break;
			}
			if(name[j]=='\0')
				break;
		}
		if(i==count+1)
			return -1;
		else
			return i;
		break;
	case 2:
		printf("Enter the roll number you want to search : ");
		scanf("%ld",&rollNumber);
		for(i=0;i<=count;i++)
		{
			if(data[i].rollNo==rollNumber)
				break;
		}
		if(i==count+1)
			return -1;
		else
			return i;
		break;
	default:
		printf("\nPlease enter a valid choice.\n");
		return -2;
	}
}

void dataCopy(database *record1,database *record2)
{
	/*
		 * Input : pointers to structure database variables of source and terget
		 * Utility : copy values from source to target
		 * Output : none
	 */
	int i;
	for(i=0;record2->name[i]!='\0';i++)
		record1->name[i]=record2->name[i];
	for(i=0;i<4;i++)
		record1->dept[i]=record2->dept[i];
	for(i=0;i<2;i++)
		record1->year[i]=record2->year[i];
	record1->div=record2->div;
	record1->rollNo=record2->rollNo;
	record1->mob=record2->mob;
}

void printHeader()
{
	/*
		 * Input : none
		 * Utility : print header
		 * Output : none
	 */
	printf("|              Name              | Department | Year | Division | Roll Number |   Mobile   |");
}

void printLine()
{
	/*
		 * Input : none
		 * Utility : Main function to drive the program
		 * Output : none
	 */
	printf("--------------------------------------------------------------------------------------------");
}
