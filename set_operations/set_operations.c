#include <stdio.h> // Header files inclusion
#include <stdlib.h>
#define MAX_SIZE 10 //Maximum size of array representing set

void inputSet(int *array, int *size)
{
	/*
		 * Input : Base address of array and pointer pointing to the size of the array.
		 * Function : To input elements entered by user into the array passed as a parameter while preventing repetition.
		 * Output : NONE
	 */
	int i,j;
	printf("\nEnter the number of elements in the set : ");
	scanf("%d",size);
	printf("\nEnter the elements of the set\n");
	for(i=0;i<*size;i++)
	{
		printf("Element %d = ",i+1);
		scanf("%d",array+i);
		for(j=0;j<i;j++)
		{
			if(array[i]==array[j])
			{
				i--;
				printf("Element already entered at position = %d. Please input distinct values.\n",j+1);
				break;
			}
		}
	}
	*(array+*size)='\0';
}

void printSet(int *array, int *size)
{
	/*
		 * Input : Base address of array and pointer pointing to the size of the array.
		 * Function : To output elements of the set passed as the parameter array.
		 * Output : NONE
	*/
	int i;
	printf("{ ");
	for(i=0;i<*size;i++)
	{
		if(i+1==*size)
			printf("%d ",*(array+i));
		else
			printf("%d, ",*(array+i));
	}
	printf("}");
}

void printMenu()
{
	/*
		 * Input : NONE.
		 * Function : To print the specified menu.
		 * Output : NONE
	*/
	printf("\nMenu\n1. Input Sets\n2. Display sets\n3. Union\n4. Intersection\n5. Difference\n6. Symmetric Difference\n7. Exit");
}

int Union(int *A,int *B,int *sizeA,int *sizeB,int *result)
{
	/*
		 * Input : Base addresses of 2 arrays containing sets, pointers pointing to the sizes of the arrays and the base address of the array to contain the resultant set.
		 * Function : To carry out union of the two input sets.
		 * Output : Size of the resultant array.
	*/
	int i,j,index=0;
	for(i=0;i<*sizeA;i++)
	{
		result[index]=A[i];
		index++;
	}
	for(i=0;i<*sizeB;i++)
	{
		for(j=0;j<*sizeA;j++)
		{
			if(B[i]==A[j])
			{
				break;
			}
		}
		if(j==*sizeA)
		{
		result[index]=B[i];
		index++;
		}
	}
	result[index]='\0';
	return index;
}

int intersection(int *A,int *B,int *sizeA,int *sizeB,int *result)
{
	/*
		* Input : Base addresses of 2 arrays containing sets, pointers pointing to the sizes of the arrays and the base address of the array to contain the resultant set.
		* Function : To carry out intersection of the two input sets.
		* Output : Size of the resultant array.
	*/
	int i,j,index=0;
	for(i=0;i<*sizeA;i++)
	{
		for(j=0;j<*sizeB;j++)
		{
			if(A[i]==B[j])
			{
				result[index]=A[i];
				index++;
				break;
			}
		}
	}
	result[index]='\0';
	return index;
}

int difference(int *A,int *B,int *sizeA,int *sizeB,int *result)
{
	/*
		* Input : Base addresses of 2 arrays containing sets, pointers pointing to the sizes of the arrays and the base address of the array to contain the resultant set.
		* Function : To carry out difference of the two input sets (first input set - second input set).
		* Output : Size of the resultant array.
	*/
	int i,j,index=0;
	for(i=0;i<*sizeA;i++)
	{
		for(j=0;j<*sizeB;j++)
		{
			if(A[i]==B[j])
				break;
		}
		if(j==*sizeB)
		{
			result[index]=A[i];
			index++;
		}
	}
	result[index]='\0';
	return index;
}

int main()
{
	/*
			* Input : NONE
			* Function : To drive the program to carry out various set operations.
			* Output : EXIT_SUCCESS
	*/
	int A[MAX_SIZE],B[MAX_SIZE],result[2*MAX_SIZE]={'\0'},sizeA,sizeB,sizeR,choice,R1[2*MAX_SIZE],sizeR1,R2[2*MAX_SIZE],sizeR2; //Variable declaration
	while(1)//loop to
	{
		printMenu();
		printf("\nEnter your choice: ");
		scanf("%d",&choice);
		switch (choice)
		{
		case 1: // Choice to input sets.
			printf("\nFirst set : ");
			inputSet(A,&sizeA);
			printf("\nSecond set : ");
			inputSet(B,&sizeB);
			break;
		case 2: // Choice to display sets.
			printf("\nFirst set : ");
			printSet(A,&sizeA);
			printf("\nSecond set : ");
			printSet(B,&sizeB);
			printf("\n");
			break;
		case 3: // Choice to carry out union of input sets.
			printf("\nFirst set : ");
			printSet(A,&sizeA);
			printf("\nSecond set : ");
			printSet(B,&sizeB);
			sizeR=Union(A,B,&sizeA,&sizeB,result);
			printf("\nFirst set union Second set = ");
			printSet(result,&sizeR);
			printf("\n");
			break;
		case 4: // Choice to carry out intersection of input sets.
			printf("\nFirst set : ");
			printSet(A,&sizeA);
			printf("\nSecond set : ");
			printSet(B,&sizeB);
			sizeR=intersection(A,B,&sizeA,&sizeB,result);
			printf("\nFirst set intersection Second set = ");
			printSet(result,&sizeR);
			printf("\n");
			break;
		case 5: // Choice to difference out union of input sets.
			printf("\nFirst set : ");
			printSet(A,&sizeA);
			printf("\nSecond set : ");
			printSet(B,&sizeB);
			sizeR=difference(A,B,&sizeA,&sizeB,result);
			printf("\nFirst set - Second set = ");
			printSet(result,&sizeR);
			sizeR=difference(B,A,&sizeB,&sizeA,result);
			printf("\nSecond set - First set = ");
			printSet(result,&sizeR);
			printf("\n");
			break;
		case 6: // Choice to carry out symmetric difference of input sets.
			printf("\nFirst set : ");
			printSet(A,&sizeA);
			printf("\nSecond set : ");
			printSet(B,&sizeB);
			sizeR1=difference(A,B,&sizeA,&sizeB,R1);
			sizeR2=difference(B,A,&sizeB,&sizeA,R2);
			sizeR=Union(R1,R2,&sizeR1,&sizeR2,result);
			printf("\nFirst set symmetric difference Second set = ");
			printSet(result,&sizeR);
			printf("\n");
			break;
		case 7: // Case to exit program.
			printf("Thank you for using this program.");
			exit(0);
		default: // Case to handle invalid choices.
			printf("Invalid input. Please try again.");
		}
	}
	return EXIT_SUCCESS;
}
