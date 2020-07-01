#include <stdio.h>
#include <stdlib.h>

typedef struct sm
{
	int row,col,val;
}sm;

void printMenu()
{
	printf("Menu\n1. Input Matrices\n2. Convert to Sparse Matrices\n3. Add Sparse Matrices\n4. Simple Transpose\n5. Fast Transpose\n6. Display Matrix\n7. Display Sparse Matrix \n8. Exit\nChoice : ");
}

int numberOfNonZeroElements(int *mat,int r,int c)
{
	int i,j,count=0;
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
			if(*(mat+i*c+j)!=0)
				count++;
	return count;
}

sm *convertToSparse(int *mat,int r,int c,int *sr)
{
	sm *smat=NULL;
	int count,i,j,k=1;
	count=numberOfNonZeroElements(mat,r,c);
	*sr=count+1;
	smat=(sm *)malloc((*sr)*sizeof(sm));
	smat[0].row=r;
	smat[0].col=c;
	smat[0].val=count;
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			if(*(mat+i*r+j)!=0)
			{
				smat[k].row=i;
				smat[k].col=j;
				smat[k].val=*(mat+i*r+j);
				k++;
			}
		}
	}
	return smat;
}

void printSparseMatrix(sm *smat,int sr)
{
	int i;
	printf("\n------------------------");
	printf("\n| Row | Column | Value |");
	printf("\n------------------------");
	for(i=0;i<sr;i++)
	{
		printf("\n| %3d | %6d | %5d |",smat[i].row,smat[i].col,smat[i].val);
		printf("\n------------------------");
	}
}

sm *addSparseMatrix(sm smat1[], sm smat2[],int sr1,int sr2,int *sr3)
{
	sm *smat3=NULL;
	int count,i,j,k;
	count=sr1-1;
	for(i=1;i<sr2;i++)
	{
		for(j=1;j<sr1;j++)
		{
			if(smat1[i].row==smat2[j].row&&smat1[1].col==smat2[j].col)
				break;
		}
			if(j==sr1)
			count++;
	}
	(*sr3)=count+1;
	smat3=(sm *)malloc((*sr3)*sizeof(sm));
	smat3[0].row=smat1[0].row;
	smat3[0].col=smat1[0].col;
	smat3[0].val=((*sr3)-1);
	j=1;
	k=1;
	for(i=1;i<(*sr3);i++)
	{
		if(j<sr1&&k<sr2)
		{
			if(smat1[j].row==smat2[k].row && smat1[j].col==smat2[k].col)
			{
				smat3[i].row=smat1[j].row;
				smat3[i].col=smat1[j].col;
				smat3[i].val=smat1[j].val+smat2[k].val;
				j++;
				k++;
			}
			else if(smat1[j].row==smat2[k].row && smat1[j].col>smat2[k].col)
			{
				smat3[i].row=smat2[k].row;
				smat3[i].col=smat2[k].col;
				smat3[i].val=smat2[k].val;
				k++;
			}
			else if(smat1[j].row==smat2[k].row && smat1[j].col<smat2[k].col)
			{
				smat3[i].row=smat1[j].row;
				smat3[i].col=smat1[j].col;
				smat3[i].val=smat1[j].val;
				j++;
			}
			else if(smat1[j].row<smat2[k].row)
			{
				smat3[i].row=smat1[j].row;
				smat3[i].col=smat1[j].col;
				smat3[i].val=smat1[j].val;
				j++;
			}
			else if(smat1[j].row>smat2[k].row)
			{
				smat3[i].row=smat2[k].row;
				smat3[i].col=smat2[k].col;
				smat3[i].val=smat2[k].val;
				k++;
			}
		}
		else
		{
			if(j<sr1)
			{
				smat3[i].row=smat1[j].row;
				smat3[i].col=smat1[j].col;
				smat3[i].val=smat1[j].val;
				j++;
			}
			else
			{
				smat3[i].row=smat2[k].row;
				smat3[i].col=smat2[k].col;
				smat3[i].val=smat2[k].val;
				k++;
			}
		}
	}
	return smat3;
}

sm *simpleTranspose(sm *smat,int sr)
{
	int i,j,k;
	sm *smat_t;
	smat_t=(sm *)malloc(sr*sizeof(sm));
	smat_t[0].row=smat[0].col;
	smat_t[0].col=smat[0].row;
	smat_t[0].val=smat[0].val;
	if(smat_t[0].val>0)
	{
		k=1;
		for(i=0;i<smat[0].col;i++)
		{
			printf("\n\n%d",i);
			for(j=1;j<=smat[0].val;j++)
			{
				printf("\n%d",j);
				if(smat[j].col==i)
				{
					smat_t[k].row=smat[j].col;
					smat_t[k].col=smat[j].row;
					smat_t[k].val=smat[j].val;
					k++;
					printf("Element added has column %d",smat[j].col);
				}
			}
		}
	}
	return smat_t;
}

sm *fastTranspose(sm *smat,int sr)
{
	int i,j;
	sm *smat_t;
	smat_t=(sm *)malloc(sr*sizeof(sm));
	smat_t[0].row=smat[0].col;
	smat_t[0].col=smat[0].row;
	smat_t[0].val=smat[0].val;
	int *rowTerms=(int *)malloc(smat[0].col*sizeof(int));
	int *startingPos=(int *)malloc(smat[0].col*sizeof(int));
	if(smat_t[0].val>0)
	{
		for(i=0;i<smat[0].col;i++)
			rowTerms[i]=0;
		startingPos[0]=1;
		for(i=1;i<=smat_t[0].val;i++)
			rowTerms[smat[i].col]++;
		for(i=1;i<smat[0].col;i++)
			startingPos[i]=startingPos[i-1]+rowTerms[i-1];
		for(i=1;i<=smat[0].val;i++)
		{
			j=startingPos[smat[i].col]++;
			smat_t[j].row=smat[i].col;
			smat_t[j].col=smat[i].row;
			smat_t[j].val=smat[i].val;
		}
	}
	return smat_t;
}

int main(void)
{
	int choice,i,j,*mat1,*mat2,r1,c1,r2,c2,sr1,sr2,sr3;
	sm *smat1,*smat2,*smat3,*smat1t,*smat2t;
	do
	{
		printMenu();
		scanf("%d",&choice);
		switch(choice)
		{
		case 1: // Input Matrices
			printf("Enter the number of rows of the first matrix : ");
			scanf("%d",&r1);
			printf("Enter the number of columns of the first matrix : ");
			scanf("%d",&c1);
			mat1=(int *)malloc(r1*c1*sizeof(int));
			printf("Enter the elements of the first matrix :\n");
			for(i=0;i<r1;i++)
			{
				for(j=0;j<c1;j++)
				{
					printf("Element [%d][%d] : ",i,j);
					scanf("%d",(mat1+i*c1+j));
				}
			}
			printf("Enter the number of rows of the second matrix : ");
			scanf("%d",&r2);
			printf("Enter the number of columns of the second matrix : ");
			scanf("%d",&c2);
			mat2=(int *)malloc(r2*c2*sizeof(int));
			printf("Enter the elements of the second matrix :\n");
			for(i=0;i<r2;i++)
			{
				for(j=0;j<c2;j++)
				{
					printf("Element [%d][%d] : ",i,j);
					scanf("%d",(mat2+i*c2+j));
				}
			}
			printf("\n\n");
			break;
		case 2: //Convert to sparse matrix
			smat1=convertToSparse(mat1,r1,c1,&sr1);
			smat2=convertToSparse(mat2,r2,c2,&sr2);
			printf("\nMatrices successfuly converted to sparse matrices");
			printf("\n\n");
			break;
		case 3: //Addition
			if(r1==r2&&c1==c2)
			{
				smat3=addSparseMatrix(smat1,smat2,sr1,sr2,&sr3);
				printf("\nAddition is :\n");
				printSparseMatrix(smat3,sr3);
			}
			else
			{
				printf("\nAddition not possible with the given matrices");
			}
			printf("\n\n");
			break;
		case 4: //Simple Transpose
			smat1t=simpleTranspose(smat1,sr1);
			printf("\nTranspose is :\n");
			printSparseMatrix(smat1t,sr1);
			printf("\n\n");
			break;
		case 5: //Fast Transpose
			smat1t=fastTranspose(smat1,sr1);
			printf("\nTranspose is :\n");
			printSparseMatrix(smat1t,sr1);
			printf("\n\n");
			break;
		case 6: //Display Matrix
			printf("\nMatrix 1 :\n");
			for(i=0;i<r1;i++)
			{
				for(j=0;j<c1;j++)
				{
					printf("%3d",*(mat1+i*c1+j));
				}
				printf("\n");
			}
			printf("\nMatrix 2 :\n");
			for(i=0;i<r2;i++)
			{
				for(j=0;j<c2;j++)
				{
					printf("%3d",*(mat2+i*c2+j));
				}
				printf("\n");
			}
			printf("\n\n");
			break;
		case 7: //Display Sparse Matrix
			printf("\nSparse Matrix 1 :");
			printSparseMatrix(smat1,sr1);
			printf("\nSparse Matrix 2 :");
			printSparseMatrix(smat2,sr2);
			printf("\n\n");
			break;
		case 8: //exit
			return EXIT_SUCCESS;
			break;
		default:
			printf("\nInvalid choice");
			printf("\n\n");
			while(getchar()!='\n');
			break;
		}
	}while(1);
	return EXIT_SUCCESS;
}
