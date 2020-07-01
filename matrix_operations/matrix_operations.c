#include <stdio.h>
#include <stdlib.h>
#define MAX_ROW 10
#define MAX_COL 10

void printMenu()
{
	printf("Menu\n1. Input matrices\n2. Display matrices\n3. Transpose\n4. Addition\n5. Multiplication\n6. Find saddle point\n7. Exit\nPlease enter your choice : ");
}

void getChoice(int *choice)
{
	scanf("%d", choice);
}

void inputMatrix(int A[MAX_ROW][MAX_COL], int B[MAX_ROW][MAX_COL], int R[MAX_ROW][MAX_COL], int *rowA, int *colA, int *rowB, int *colB, int *rowR, int *colR)
{
	int i, j;
	printf("\nEnter the number of rows and columns of matrix A\nRows = ");
	scanf("%d", rowA);
	printf("Columns = ");
	scanf("%d", colA);
	printf("Enter the elements of matrix A:\n");
	for (i = 0; i<*rowA; i++)
	{
		for (j = 0; j<*colA; j++)
		{
			printf("A[%d][%d] = ", i + 1, j + 1);
			scanf("%d", &A[i][j]);
		}
	}
	printf("\nEnter the number of rows and columns of matrix B\nRows = ");
	scanf("%d", rowB);
	printf("Columns = ");
	scanf("%d", colB);
	printf("Enter the elements of matrix B:\n");
	for (i = 0; i<*rowB; i++)
	{
		for (j = 0; j<*colB; j++)
		{
			printf("B[%d][%d] = ", i + 1, j + 1);
			scanf("%d", &B[i][j]);
		}
	}
}

void printMatrix(int A[MAX_ROW][MAX_COL], int rowA, int colA)
{
	int i, j, k;
	for (k = 0; k<=(colA * 5 + colA); k++)
		printf("=");
	printf("\n");
	for (i = 0; i<rowA; i++)
	{
		for (j = 0; j<colA; j++)
		{
			printf("| %3d ", A[i][j]);
		}
		printf("|\n");
		for (k = 0; k<=(colA * 5 + colA); k++)
			printf("=");
		printf("\n");
	}
}

void transpose(int A[MAX_ROW][MAX_COL], int rowA, int colA, int R[MAX_ROW][MAX_COL], int *rowR, int *colR)
{
	int i, j;
	*rowR = colA;
	*colR = rowA;
	for (i = 0; i<rowA; i++)
	{
		for (j = 0; j<colA; j++)
		{
			R[j][i] = A[i][j];
		}
	}
}

int addMatrices(int A[MAX_ROW][MAX_COL], int B[MAX_ROW][MAX_COL], int R[MAX_ROW][MAX_COL], int rowA, int colA, int rowB, int colB, int *rowR, int *colR)
{
	int i, j;
	if (rowA != rowB || colA != colB)
	{
		printf("Please enter matrices with equal sizes\n");
		return 1;
	}
	else
	{
		*rowR = rowA;
		*colR = colA;
		for (i = 0; i<rowA; i++)
		{
			for (j = 0; j<colA; j++)
			{
				R[i][j] = A[i][j] + B[i][j];
			}
		}
		return 0;
	}
}

void multiplyMatrices(int A[MAX_ROW][MAX_COL], int B[MAX_ROW][MAX_COL], int R[MAX_ROW][MAX_COL], int rowA, int colA, int rowB, int colB, int *rowR, int *colR)
{
	int i, j, k;
	*rowR = rowA;
	*colR = colB;
	for (i = 0; i<*rowR; i++)
	{
		for (j = 0; j<*colR; j++)
		{
			R[i][j] = 0;
			for (k = 0; k<colA; k++)
			{
				R[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

void saddlePoint(int A[MAX_ROW][MAX_COL], int rowA, int colA)
{

	int i, j, k, l, index = 0, saddlePoint, saddlePointCol=0,saddlePointrow=0,saddlePointRow[MAX_ROW*MAX_COL],saddlePointColumn[MAX_COL*MAX_ROW],saddlePoints[MAX_ROW*MAX_COL];

	for (i = 0; i < rowA; i++)
	{
		saddlePoint = A[i][0];
		saddlePointrow=i;
		saddlePointCol=0;
		for (j = 0; j < colA; j++)
		{
			if (A[i][j] < saddlePoint)
			{
				saddlePoint = A[i][j];
				saddlePointCol = j;
				saddlePointrow = i;
			}
		}
		for (k = 0; k<rowA; k++)
		{
			if (A[k][saddlePointCol] > saddlePoint)
				break;
		}
		if (k == rowA)
		{
			saddlePoints[index] = saddlePoint;
			saddlePointRow[index]=saddlePointrow;
			saddlePointColumn[index]=saddlePointCol;
			index++;
		}
	}
	for (i = 0; i < rowA; i++)
	{
		saddlePoint = A[i][0];
		saddlePointrow=i;
		saddlePointCol=0;
		for (j = 0; j < colA; j++)
		{
			if (A[i][j] > saddlePoint)
			{
				saddlePoint = A[i][j];
				saddlePointCol = j;
				saddlePointrow = i;

			}
		}
		for (k = 0; k<rowA; k++)
		{
			if (A[k][saddlePointCol] < saddlePoint)
				break;
		}
		if (k == rowA)
		{
			for(l=0;l<=index;l++)
			{
				if(saddlePointRow[l]==saddlePointrow && saddlePointColumn[l]==saddlePointCol)
				{
					break;
				}
			}
			if(l==index+1)
			{
				saddlePoints[index] = saddlePoint;
				saddlePointRow[index]=saddlePointrow;
				saddlePointColumn[index]=saddlePointCol;
				index++;
			}
		}
	}
	printf("======================\n");
	printf("|  Position  | Value |\n");
	printf("======================");
	for(l=0;l<index;l++)
	{
		printf("\n| [%3d][%3d] | %5d |",saddlePointRow[l]+1,saddlePointColumn[l]+1,saddlePoints[l]);
	}
	printf("\n======================");
}

int main(void)
{
	int i, A[MAX_ROW][MAX_COL]={0}, B[MAX_ROW][MAX_COL]={0}, R[MAX_ROW][MAX_COL]={0}, choice, rowA=MAX_ROW, colA=MAX_COL, rowB=MAX_ROW, colB=MAX_COL, rowR=MAX_ROW, colR=MAX_COL, err;
	while (1)
	{
		printMenu();
		getChoice(&choice);
		switch (choice)
		{
		case 1:
			inputMatrix(A, B, R, &rowA, &colA, &rowB, &colB, &rowR, &colR);
			break;
		case 2:
			printf("\nA = \n");
			printMatrix(A, rowA, colA);
			printf("\nB = \n");
			printMatrix(B, rowB, colB);
			printf("\n\n");
			break;
		case 3:
			printf("\nA = \n");
			printMatrix(A, rowA, colA);
			transpose(A, rowA, colA, R, &rowR, &colR);
			printf("\nTranspose of A = \n");
			printMatrix(R, rowR, colR);
			printf("\nB = \n");
			printMatrix(B, rowB, colB);
			transpose(B, rowB, colB, R, &rowR, &colR);
			printf("\nTranspose of B = \n");
			printMatrix(R, rowR, colR);
			printf("\n\n");
			break;
		case 4:
			if(colA!=colB && rowA!=rowB)
			{
				printf("\nInvalid input for matrix addition rows and columns of first matrix and second matrix are not equal.\n\n");
				break;
			}
			addMatrices(A, B, R, rowA, colA, rowB, colB, &rowR, &colR);
			printf("\nA = \n");
			printMatrix(A, rowA, colA);
			printf("\nB = \n");
			printMatrix(B, rowB, colB);
			printf("\nA + B = \n");
			printMatrix(R, rowR, colR);
			printf("\n\n");
			break;
		case 5:
			if(colA!=rowB)
			{
				printf("\nMatrix dimensions invalid for multiplication. Columns of first matrix and rows of second matrix are unequal.\n\n");
				break;
			}
			else
			{
				multiplyMatrices(A, B, R, rowA, colA, rowB, colB, &rowR, &colR);
				printf("\nA = \n");
				printMatrix(A, rowA, colA);
				printf("\nB = \n");
				printMatrix(B, rowB, colB);
				printf("\nA * B = \n");
				printMatrix(R, rowR, colR);
				printf("\n\n");
				break;
			}
		case 6:
			printf("\nA = \n");
			printMatrix(A, rowA, colA);
			printf("\nSaddle points are : \n");
			saddlePoint(A, rowA, colA);
			printf("\nB = \n");
			printMatrix(B, rowB, colB);
			printf("\nSaddle points are : \n");
			saddlePoint(B, rowB, colB);
			printf("\n\n");
			break;
		case 7:
			exit(0);
			break;
		default:
			printf("Please enter a valid choice.");
			printf("\n\n");
			break;
		}
	}
	return EXIT_SUCCESS;
}
