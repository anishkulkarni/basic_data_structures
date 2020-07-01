#include <stdio.h>
#include <stdlib.h> //header file inclusion

#define MAX_NAME 30 //Macro definition

typedef struct database
{
	char name[MAX_NAME];
	long int rollNo;
	char year[2];
	int division;
	char dept[4];
	long int mob;
}database;// structure to hold contents of database

void displayRecord(database);

void printMenu();

void printHeader();

void printLine();

void getRecord(database *);

void displayDatabase();

void addRecord();

void searchDatabase(char *);

void deleteRecord(char *name);

void modifyRecord(char *);

int main(void)
{
	/*
	 	 * Input : none
	 	 * Utility : Main function to drive the program
	 	 * Output : Success or failure of program
	*/
	char name[MAX_NAME];
	int choice;
	while(1)
	{
		printMenu();
		scanf("%d",&choice);
		switch(choice)
		{
		case 1: //Case to display database
			displayDatabase();
			printf("\n\n");
			break;
		case 2: //Case to add record
			while(getchar()!='\n');
			printf("\nEnter the details of the record you want to add :");
			addRecord();
			printf("\n\n");
			break;
		case 3: //Case to search for record
			while(getchar()!='\n');
			printf("\nEnter the name you want to search : ");
			gets(name);
			searchDatabase(name);
			printf("\n\n");
			break;
		case 4: //Case to modify record
			while(getchar()!='\n');
			printf("\nEnter the name you want to modify : ");
			gets(name);
			modifyRecord(name);
			printf("\n\n");
			break;
		case 5: //Case to delete record
			while(getchar()!='\n');
			printf("\nEnter the name you want to delete : ");
			gets(name);
			deleteRecord(name);
			printf("\n\n");
			break;
		case 6: //Case to exit
			return EXIT_SUCCESS;
		default:
			printf("\nPlease enter a valid choice.\n\n");
			while(getchar()!='\n');
			break;
		}
	}
}

void modifyRecord(char *name)
{
	/*
		 * Input : none
		 * Utility : To print the menu of the program
		 * Output : none
	 */
	FILE *fpRead,*fpWrite;
	database data,temp;
	int flag;
	long int pos;
	fpRead=fopen("Database.txt","r");
	if(fpRead!=NULL)
	{
		while(!feof(fpRead))
		{
			fscanf(fpRead,"%s %ld %s %s %d %ld\n",data.name,&data.rollNo,data.dept,data.year,&data.division,&data.mob);
			if(!strcmp(name,data.name))
			{
				pos=ftell(fpRead);
				break;
			}
		}
		if(!feof(fpRead))
		{
			do
			{
				flag=0;
				printf("\nEnter the details of the record to modify.");
				getRecord(&data);
				if((data.mob/10000000000!=0)||(data.mob<1000000000))
				{
					printf("\nInvalid mobile number.");
					while(getchar()!='\n');
					flag=1;
				}
				else
				{
					rewind(fpRead);
					while(!feof(fpRead))
					{
						fscanf(fpRead,"%s %ld %s %s %d %ld\n",temp.name,&temp.rollNo,temp.dept,temp.year,&temp.division,&temp.mob);
						if(ftell(fpRead)!=pos)
						{
							if(data.mob==temp.mob)
							{
								if(data.rollNo==temp.rollNo)
									printf("\nRecord with this roll number already exists.");
								printf("\nRecord with this mobile number already exists.");
								while(getchar()!='\n');
								flag=1;
								break;
							}
							else if(data.rollNo==temp.rollNo)
							{
								printf("\nRecord with this roll number already exists.");
								while(getchar()!='\n');
								flag=1;
								break;
							}
						}
					}
				}
			}while(flag==1);
			rewind(fpRead);
			fpWrite=fopen("temp.txt","w");
			while(!feof(fpRead))
			{
				fscanf(fpRead,"%s %ld %s %s %d %ld\n",temp.name,&temp.rollNo,temp.dept,temp.year,&temp.division,&temp.mob);
				if(ftell(fpRead)!=pos)
					fprintf(fpWrite,"%s %ld %s %s %d %ld\n",temp.name,temp.rollNo,temp.dept,temp.year,temp.division,temp.mob);
				else
					fprintf(fpWrite,"%s %ld %s %s %d %ld\n",data.name,data.rollNo,data.dept,data.year,data.division,data.mob);
			}
			fclose(fpWrite);
			remove("Database.txt");
			rename("temp.txt","Database.txt");
			printf("\nRecord successfully modified.");
		}
		else
		{
			printf("\nRecord not found.");
		}
		fclose(fpRead);
	}
	else
	{
		printf("\nData not found");
	}
}

void deleteRecord(char *name)
{
	/*
	 	 * Input : Character pointer pointing to the input name
	 	 * Utility : Delete the record containing the given name
	 	 * Output : Success or failure
	*/
	FILE *fpRead,*fpWrite;
	database data;
	int flag=0;
	fpRead=fopen("Database.txt","r");
	if(fpRead!=NULL)
	{
		fpWrite=fopen("temp.txt","w");
		while(!feof(fpRead))
		{
			fscanf(fpRead,"%s %ld %s %s %d %ld\n",data.name,&data.rollNo,data.dept,data.year,&data.division,&data.mob);
			if(strcmp(name,data.name))
				fprintf(fpWrite,"%s %ld %s %s %d %ld\n",data.name,data.rollNo,data.dept,data.year,data.division,data.mob);
			else
				flag=1;
		}
		remove("Database.txt");
		rename("temp.txt","Database.txt");
		fclose(fpRead);
		fclose(fpWrite);
		if(flag==1)
			printf("\n\nRecord successfully deleted.");
		else
			printf("\n\nRecord not found");
	}
	else
	{
		printf("\nData not found");
	}
}

void searchDatabase(char *name)
{
	/*
		 * Input : Character pointer pointing to the input name
		 * Utility : Search if a record containing the given name exists in the database
		 * Output : Return the structure variable containing the record if found successfully
	 */
	FILE *fpRead;
	int flag;
	database data;
	flag=0;
	fpRead=fopen("Database.txt","r");
	if(fpRead!=NULL)
	{
		while(!feof(fpRead))
		{
			fscanf(fpRead,"%s %ld %s %s %d %ld\n",data.name,&data.rollNo,data.dept,data.year,&data.division,&data.mob);
			if(!strcmp(name,data.name))
			{

				printf("\n\nFollowing Record found\n\n");
				printLine();
				printf("\n");
				printHeader();
				printf("\n");
				printLine();
				printf("\n");
				displayRecord(data);
				printf("\n");
				printLine();
				flag=1;
			}
		}
		if(flag==0)
			printf("\nRecord not found");
	}
	else
		printf("Data not found");
	fclose(fpRead);
}

void addRecord()
{
	/*
		 * Input : One record of database
		 * Utility : Add the input record to the database
		 * Output : none
	 */
	FILE *fpRead,*fpWrite;
	database data,temp;
	getRecord(&data);
	fpWrite=fopen("Database.txt","a");
	fpRead=fopen("Database.txt","r");
	if(fpRead!=NULL)
	{
		while(!feof(fpRead))
		{
			fscanf(fpRead,"%s %ld %s %s %d %ld\n",temp.name,&temp.rollNo,temp.dept,temp.year,&temp.division,&temp.mob);
			if(data.mob==temp.mob)
			{
				if(data.rollNo==temp.rollNo)
					printf("\nRecord with this roll number already exists.");
				printf("\nRecord with this mobile number already exists.");
				break;
			}
			if(data.rollNo==temp.rollNo)
			{
				printf("\nRecord with this roll number already exists.");
				break;
			}
		}
		if(feof(fpRead))
		{
			if((data.mob/10000000000!=0)||(data.mob<1000000000))
				printf("\nInvalid mobile number.");
			else
			{
				fprintf(fpWrite,"%s %ld %s %s %d %ld\n",data.name,data.rollNo,data.dept,data.year,data.division,data.mob);
				printf("\nRecord successfully added");
			}
		}
		fclose(fpRead);
		fclose(fpWrite);
	}
}

void displayDatabase()
{
	/*
		 * Input : none
		 * Utility : Function to display the entire database
		 * Output : none
	 */
	FILE *fpRead;
	database data;
	fpRead=fopen("Database.txt","r");
	if(fpRead!=NULL)
	{
		if(!feof(fpRead))
		{
			fscanf(fpRead,"%s %ld %s %s %d %ld\n",data.name,&data.rollNo,data.dept,data.year,&data.division,&data.mob);
			printLine();
			printf("\n");
			printHeader();
			printf("\n");
			printLine();
			printf("\n");
			displayRecord(data);
			printf("\n");
			printLine();
			while(!feof(fpRead))
			{
				fscanf(fpRead,"%s %ld %s %s %d %ld\n",data.name,&data.rollNo,data.dept,data.year,&data.division,&data.mob);
				printf("\n");
				displayRecord(data);
				printf("\n");
				printLine();
			}
		}
		else
			printf("\nRecord not found");
		fclose(fpRead);
	}
	else
	{
		printf("\nData not found");
	}
}

void getRecord(database *record)
{
	/*
		 * Input : pointer to variable of structure database
		 * Utility : input values of record
		 * Output : none
	 */
	printf("\nName : ");
	gets(record->name);
	printf("Department : ");
	scanf("%s",record->dept);
	printf("Year : ");
	scanf("%s",record->year);
	printf("Division : ");
	scanf("%d",&record->division);
	printf("Roll number : ");
	scanf("%ld",&record->rollNo);
	printf("Mobile number : ");
	scanf("%ld",&record->mob);
}

void displayRecord(database record)
{
	/*
		 * Input : variable of structure database
		 * Utility : Print values of members of structure variable
		 * Output : none
	 */
	printf("| %30s | %10s | %4s | %8d | %11ld | %10ld |",record.name,record.dept,record.year,record.division,record.rollNo,record.mob);
}

void printMenu()
{
	/*
		 * Input : none
		 * Utility : To print the menu of the program
		 * Output : none
	 */
	printf("Menu\n1. Display database\n2. Add record\n3. Search record\n4. Modify Record\n5. Delete Record\n6. Exit\nChoice : ");
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
