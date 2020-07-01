#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct database
{
	char name[30];
	long int no;
	int bill;
}database;

void printMenu();

void printHeader();

void printLine();

void addRecord(database *);

void displayRecord(database);

void dataSwap(database *,database *);

void quickSort(database *,int,int,int *,int *,int *);

int partition(database *,int,int,int *,int *);

int main(void)
{
	int choice,size,index=0,i,swaps=0,comparisons=0,calls=0;
	database *data;
	do
	{
		printMenu();
		scanf("%d",&choice);
		switch(choice)
		{
		case 1:
			printf("Enter the number of records required  : ");
			scanf("%d",&size);
			data = ( database *) malloc ( size * sizeof ( database ) );
			index=0;
			if ( data == NULL )
				return 1;
			printf("Database successfully created");
			printf("\n\n");
			break;
		case 2:
			if(data==NULL)
				printf("Please create a database first using option 1");
			else
			{
				if(index==0)
					printf("No records found");
				else
				{
					printLine();
					printf("\n");
					printHeader();
					printf("\n");
					printLine();
					for(i=0;i<index;i++)
					{
						printf("\n");
						displayRecord(data[i]);
						printf("\n");
						printLine();
					}
				}
			}
			printf("\n\n");
			break;
		case 3:
			if(data==NULL)
				printf("Please create a database first using option 1");
			else
			{
				if(index==size)
					printf("Database full");
				else
				{
					while(getchar()!='\n');
					addRecord(&data[index]);
					index ++;
					printf("Record successfully added");
				}
			}
			printf("\n\n");
			break;
		case 4:

			printf("Quick Sort for descending order of names :\n");
			quickSort(data,0,index,&swaps,&comparisons,&calls);
			printf("\n\nSummary of quick sort :\n\tSwaps = %d\n\tComparisons = %d\n\tCalls : %d",swaps,comparisons,calls);
			printf("\n\nData Successfully sorted");
			printf("\n\n");
			break;
		case 5:
			return EXIT_SUCCESS;
		default:
			while(getchar()!='\n');
			printf("Invalid input, please try again");
			printf("\n\n");
			break;
		}
	}while(1);
}


void quickSort(database *data,int LB,int UB,int *swaps,int *comparisons,int *calls)
{
	/*static int size;
	if(*calls==0)
		size=UB;*/
	int pivot=LB;
	int i;
	printf("\nCall = %d :",*(calls)+1);
	if(LB<UB)
	{
		printf("\tPivot = %s\t",data[pivot].name);
		for(i=LB;i<=UB;i++)
		{
				printf("\t%s",data[i].name);
		}
		pivot=partition(data,LB,UB,comparisons,swaps);
		(*calls)++;
		quickSort(data,LB,pivot-1,comparisons,swaps,calls);
		quickSort(data,pivot+1,UB,comparisons,swaps,calls);
	}
	else
	{
		printf(" Reached base of Recursion");
		(*calls)++;
	}
}

int partition(database *data,int LB,int UB,int *comparisons,int *swaps)
{
	int this_comparisons=0,this_swaps=0;
	int p=LB+1;
	int q=UB;
	while(q>=p)
	{
		while(strcmp(data[p].name,data[LB].name)>0)
		{
			this_comparisons++;
			(*comparisons)++;
			p++;
		}
		while(strcmp(data[q].name,data[LB].name)<0)
		{
			this_comparisons++;
			(*comparisons)++;
			q--;
		}
		if(q>p)
		{
			this_swaps++;
			(*swaps)++;
			dataSwap(&data[p],&data[q]);
		}
	}
	(*swaps)++;
	dataSwap(&data[LB],&data[q]);
	printf("\nSwaps : %d Comparisons : %d",this_swaps,this_comparisons);
	return q;
}


void printHeader()
{
	/*
		 * Input : none
		 * Utility : print header
		 * Output : none
	 */
	printf("|               Name               |   Number   | Bill |");
}

void printLine()
{
	/*
		 * Input : none
		 * Utility : Main function to drive the program
		 * Output : none
	 */
	printf("--------------------------------------------------------");
}

void printMenu()
{
	printf("Menu\n1. Create database\n2. Display database\n3. Add record\n4. Sort records using quick sort\n5. Exit\nChoice : ");
}

void addRecord(database *record)
{
	/*
		 * Input : pointer to variable of structure database
		 * Utility : input values of record
		 * Output : none
	 */
	printf("\nName : ");
	gets(record->name);
	printf("Mobile Number : ");
	scanf("%ld",&record->no);
	printf("Bill amount : ");
	scanf("%d",&record->bill);
}

void displayRecord(database record)
{
	/*
		 * Input : variable of structure database
		 * Utility : Print values of members of structure variable
		 * Output : none
	 */
	printf("| %32s | %10ld | %4d |",record.name,record.no,record.bill);
}

void dataSwap(database *record1,database *record2)
{
	database temp;
	int i;
	//Copy second record to temp
	for(i=0;record2->name[i]!='\0';i++)
		temp.name[i]=record2->name[i];
	temp.name[i]='\0';
	temp.no=record2->no;
	temp.bill=record2->bill;
	//Copy first record to second record
	for(i=0;record1->name[i]!='\0';i++)
		record2->name[i]=record1->name[i];
	record2->name[i]='\0';
	record2->no=record1->no;
	//Copy temp to first record
	for(i=0;temp.name[i]!='\0';i++)
		record1->name[i]=temp.name[i];
	record1->name[i]='\0';
	record1->no=temp.no;
	record1->bill=temp.bill;

}
