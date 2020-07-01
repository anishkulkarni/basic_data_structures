#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h> //Header file inclusion

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

void printHeader();

void printLine();

void addRecord(database *);

void dataCopy(database *,database *);

void displayRecord(database);

void dataSwap(database *,database *);

void ascendingSort(database *, int);

void descendingSort(database *,int);

void displayDatabase(database *,int);

int binarySearch(database *,int,int,long int,int);

int binarySearchIteratively(database *,int,long int);

int main(void)
{
	int choice,size,index,flag,i,pass;
	long int key;
	database *data;
	while (1)
	{
		printMenu();
		scanf("%d",&choice);
		switch (choice)
		{
			case 1: //Case to create database
				if(data!=NULL)
				{
					printf("\nPrevious records will be overwritten\n");
					free(data);
				}
				printf("Enter the number of records you want to add : ");
				scanf("%d",&size);
				data=(database *)malloc(size*sizeof(database));
				printf("\nDatabase successfully created.\n\n");
				index=0;
				break;
			case 2: //Case to display database
				printf("\n");
				if(data == NULL)
				{
					printf("Please create a database first");
				}
				else if(index==0)
				{
					printf("No records found.\n\n");
				}
				else
				{
					flag=0;
					do
					{
						printf("1. Ascending order of roll number\n2. Descending order of name\nChoice : ");
						scanf("%d",&choice);
						switch(choice)
						{
						case 1:
							ascendingSort(data,index-1);
							displayDatabase(data,index);
							printf("\n");
							flag=1;
							break;
						case 2:
							descendingSort(data,index-1);
							displayDatabase(data,index);
							flag=1;
							printf("\n");
							break;
						default:
							printf("\nPlease enter a valid choice\n\n");
							while(getchar()!='\n');
							break;
						}
					}while(flag==0);
				}
				break;
			case 3: //Case to add record
				if(data==NULL)
				{
					printf("\nPlease create a database first.\n\n");
					break;
				}
				else if(index==size)
				{
					printf("\nDatabase full\n\n");
				}
				else
				{
					while(getchar()!='\n');
					printf("\nEnter the details of the record you want to add :");
					addRecord(&data[index]);
					for(i=0;i<index;i++)
					{
						if(data[i].rollNo==data[index].rollNo)
						{
							printf("\nA record with this roll number already exists. Current record not saved\n\n");
							break;
						}
						if(data[i].mob==data[index].mob)
						{
							printf("\nA record with this mobile number already exists. Current record not saved\n\n");
							break;
						}
					}
					if(i==index)
					{
						printf("Record successfully added\n\n");
						index++;
					}
				}
				break;
			case 4: //Case to search database
				printf("\n");
				if(data==NULL)
				{
					printf("\nPlease create a database first\n\n");
				}
				else if(index==0)
				{
					printf("\nNo records exist\n\n");
				}
				else
				{
					pass=0;
					printf("Enter the roll number to search : ");
					scanf("%ld",&key);
					ascendingSort(data,index-1);
					i=binarySearch(data,index-1,0,key,pass);
					i=binarySearchIteratively(data,index-1,key);
					if(i==-1)
					{
						printf("Record not found.\n\n");
					}
					else
					{
						printf("Following record found:\n");
						printLine();
						printf("\n");
						printHeader();
						printf("\n");
						printLine();
						printf("\n");
						displayRecord(data[i]);
						printf("\n");
						printLine();
						printf("\n\n");
					}
				}
				break;
			case 5: //Case to modify record
				if(data==NULL)
					printf("Please create a database first");
				else
				{
					pass=0;
					printf("\nEnter the roll number to search : ");
					scanf("%ld",&key);
					ascendingSort(data,index-1);
					i=binarySearch(data,index-1,0,key,pass);
					if(i!=-1)
					{
						while(getchar()!='\n');
						printf("\nEnter the details of the record you want to update :");
						addRecord(&data[i]);
						printf("Record successfully updated\n\n");
					}
					else
					{
						printf("Record not found\n\n");
					}
				}
				break;
			case 6:// Case to delete record
				if(data==NULL)
					printf("Please create a database first");
				else
				{
					pass=0;
					printf("\nEnter the roll number to search : ");
					scanf("%ld",&key);
					ascendingSort(data,index-1);
					i=binarySearch(data,index-1,0,key,pass);
					if(i!=-1)
					{
						for(;i<index;i++)
							dataCopy(&data[i],&data[i+1]);
						index--;
						printf("\nRecord successfully deleted.\n\n");
					}
					else
						printf("\nRecord not found.\n\n");
				}
				break;
			case 7:
				return EXIT_SUCCESS;
				break;
		}
	}
	return EXIT_SUCCESS;
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

void addRecord(database *record)
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
	scanf("%d",&record->div);
	printf("Roll number : ");
	scanf("%ld",&record->rollNo);
	printf("Mobile number : ");
	scanf("%ld",&record->mob);
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

void displayRecord(database record)
{
	/*
		 * Input : variable of structure database
		 * Utility : Print values of members of structure variable
		 * Output : none
	 */
	printf("| %30s | %10s | %4s | %8d | %11ld | %10ld |",record.name,record.dept,record.year,record.div,record.rollNo,record.mob);
}

void dataSwap(database *record1,database *record2)
{
	database temp;
	int i;
	//Copy second record to temp
	for(i=0;record2->name[i]!='\0';i++)
		temp.name[i]=record2->name[i];
	temp.name[i]='\0';
	for(i=0;i<4;i++)
		temp.dept[i]=record2->dept[i];
	for(i=0;i<2;i++)
		temp.year[i]=record2->year[i];
	temp.div=record2->div;
	temp.rollNo=record2->rollNo;
	temp.mob=record2->mob;
	//Copy first record to second record
	for(i=0;record1->name[i]!='\0';i++)
		record2->name[i]=record1->name[i];
	record2->name[i]='\0';
	for(i=0;i<4;i++)
		record2->dept[i]=record1->dept[i];
	for(i=0;i<2;i++)
		record2->year[i]=record1->year[i];
	record2->div=record1->div;
	record2->rollNo=record1->rollNo;
	record2->mob=record1->mob;
	//Copy temp to first record
	for(i=0;temp.name[i]!='\0';i++)
		record1->name[i]=temp.name[i];
	record1->name[i]='\0';
	for(i=0;i<4;i++)
		record1->dept[i]=temp.dept[i];
	for(i=0;i<2;i++)
		record1->year[i]=temp.year[i];
	record1->div=temp.div;
	record1->rollNo=temp.rollNo;
	record1->mob=temp.mob;

}

void ascendingSort(database *data, int size)
{
	int i,j,k,comp=0,tot_comp=0,swap=0,tot_swap=0;
	printf("\nBubble sort : (ascending order of roll numbers)\n\n");
	for(k=0;k<=size;k++)
		printf("\t%ld",data[k].rollNo);
	printf("\t\tInitial");
	for(i=0;i<=size;i++)
	{
		for(j=0;j<size-i;j++)
		{
			comp++;
			if(data[j].rollNo>data[j+1].rollNo)
			{
				dataSwap(data+j,data+j+1);
				swap++;
			}
		}
		printf("\n");
		for(k=0;k<=size;k++)
			printf("\t%ld",data[k].rollNo);
		printf("\t\tPass %d",i+1);
		printf("\tComparisons : %d, Swaps : %d",comp,swap);
		tot_comp+=comp;
		tot_swap+=swap;
		if(swap==0)
			break;
		comp=0;
		swap=0;
	}
	printf("\n\nSummary of Bubble sort :\n\tPasses : %d\n\tComparisons : %d\n\tSwaps : %d\n\t",i+1,tot_comp,tot_swap);
	if(tot_comp==(size*(size+1))/2)
		printf("Worst case\n\n");
	else if(tot_comp==size)
		printf("Best case\n\n");
	else
		printf("Average case\n\n");
}

void descendingSort(database *data,int size)
{
	int i,j,k,l,comp=0,tot_comp=0,swap=0,tot_swap=0;
	printf("\nSelection sort : (descending order of names)\n\n");
	for(l=0;l<=size;l++)
		printf("\t%s",data[l].name);
	printf("\t\tInitial");
	for(i=0;i<size;i++)
	{
		k=i;
		for(j=i+1;j<=size;j++)
		{
			if(strcmp(data[j].name,data[k].name)>0)
			{
				comp++;
				k=j;
			}
		}
		if(k!=i)
		{
			dataSwap(data+k,data+i);
			swap++;
		}
		printf("\n");
		for(l=0;l<=size;l++)
			printf("\t%s",data[l].name);
		printf("\t\tPass %d",i+1);
		printf("\tComparisons : %d, Swaps : %d",comp,swap);
		tot_comp+=comp;
		comp=0;
		tot_swap+=swap;
		swap=0;
	}
	printf("\n\nSummary of Selection sort :\n\tPasses : %d\n\tComparisons : %d\n\tSwaps : %d\n\t",i-1,tot_comp,tot_swap);
	if(tot_comp>=(size-1)*(size)/2)
		printf("Worst case\n\n");
	else if(tot_comp<=size-1)
		printf("Best case\n\n");
	else
		printf("Average case\n\n");
}

void displayDatabase(database *data,int size)
{
	int i;
	printLine();
	printf("\n");
	printHeader();
	printf("\n");
	printLine();
	printf("\n");
	for(i=0;i<size;i++)
	{
		displayRecord(data[i]);
		printf("\n");
		printLine();
		printf("\n");
	}

}

int binarySearch(database *data,int UB,int LB,long int key,int pass)
{
	int i;
	static int comp;
	//const double max_comp=(log(UB-LB)/log(2));
	const double max_comp=UB-LB-1;
	pass++;
	if(pass==1)
	{
		printf("\nBinary search using recursion :\n");
		comp=0;
	}
	int MID=(UB+LB)/2;
	printf("\n");
	for(i=LB;i<=UB;i++)
		printf("% ld",data[i].rollNo);
	printf("\tCall %d, LB = %d, MID = %d, UB = %d",pass,LB,MID,UB);
	if(data[MID].rollNo==key)
	{
		printf("\n\nSummary of Binary Search\n\tIterations = %d\n\tComparisons = %d",pass,comp);
		if(comp>=max_comp)
			printf("\n\tWorst case\n\n");
		else if(comp<1)
			printf("\n\tBest case\n\n");
		else
			printf("\n\tAverage case\n\n");
		return MID;
	}
	else if(LB>=UB)
	{
		comp++;
		printf("\n\nSummary of Binary Search\n\tIterations = %d\n\tComparisons = %d",pass,comp);
		if(comp>=max_comp)
			printf("\n\tWorst case\n\n");
		else if(comp<1)
			printf("\n\tBest case\n\n");
		else
			printf("\n\tAverage case\n\n");
		return -1;
	}
	else if(key>data[MID].rollNo)
	{
		comp++;
		return binarySearch(data,UB,MID+1,key,pass);
	}
	else
	{
		return binarySearch(data,MID-1,LB,key,pass);
	}
}

int binarySearchIteratively(database *data,int size,long int key)
{
	int i,UB=size,LB=0,MID,pass=0,comp=0;
	printf("\nBinary search using iteration :\n");
	while(LB<=UB)
	{
		pass++;
		MID=(LB+UB)/2;
		printf("\n");
		for(i=LB;i<=UB;i++)
			printf(" %ld",data[i].rollNo);
		printf("\tCall %d, LB = %d, MID = %d, UB = %d",pass,LB,MID,UB);
		if(data[MID].rollNo==key)
		{
			printf("\n\nSummary of Binary Search\n\tIterations = %d\n\tComparisons = %d",pass,comp);
			if(comp>=size-1/*(log((double)size)/log((double)2))*/)
				printf("\n\tWorst case\n\n");
			else if(comp<1)
				printf("\n\tBest case\n\n");
			else
				printf("\n\tAverage case\n\n");
			return MID;
		}
		else if(data[MID].rollNo<key)
		{
			comp++;
			LB=MID+1;
		}
		else
		{
			comp++;
			UB=MID-1;
		}
	}
	printf("\n\nSummary of Binary Search\n\tIterations = %d\n\tComparisons = %d",pass,comp);
	if(comp>=size-1/*(log((double)size)/log((double)2))*/)
		printf("\n\tWorst case\n\n");
	else if(comp<1)
		printf("\n\tBest case\n\n");
	else
		printf("\n\tAverage case\n\n");
	return -1;
}
