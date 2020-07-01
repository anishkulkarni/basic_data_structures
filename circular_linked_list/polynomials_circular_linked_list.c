#include <stdio.h>
#include <stdlib.h> //header file inclusion

typedef struct node
{
	int c;
	int d;
	struct node *next;
}node; //Structure to define a node of a circularly linked list

void printMenu();

node *addNode(int, int);

void printPolynomial(node *, int);

node *addPolynomials(node *, node *, int, int, int *);

node *multiplyPolynomials(node *, node *, int, int, int *);

node *sort_polynomial(node *, int *);

void evaluatePolynomial(node *, int, int);

int power(int, int);

void freeList(node *);

int main(void)
{
	node *last1 = NULL, *last2 = NULL, *temp, *last_res;
	int choice, term1 = 0, term2 = 0, term_res = 0, i, degree, coefficient, var_val;
	do
	{
		printMenu();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			if (last1 != NULL)
			{
				freeList(last1);
				last1 = NULL;
			}
			last1 = (node *)malloc(sizeof(node));
			last1->c = -1;
			last1->d = -1;
			last1->next = last1;
			printf("\nEnter the number of terms in the first polynomial : ");
			scanf("%d", &term1);
			for (i = 0; i<term1; i++)
			{
				printf("\nEnter the degree of the term %d : ", i + 1);
				scanf("%d", &degree);
				printf("\nEnter the coefficient of x^%d : ", degree);
				scanf("%d", &coefficient);
				temp = addNode(degree, coefficient);
				if (last1->next == last1)
				{
					if (i == 0)
					{
						last1->d = temp->d;
						last1->c = temp->c;
						free(temp);
					}
					else
					{
						last1->next = temp;
						temp->next = last1;
						last1 = temp;
					}
				}
				else
				{
					temp->next = last1->next;
					last1->next = temp;
					last1 = temp;
				}
			}
			last1 = sort_polynomial(last1, &term1);
			printf("\n\n");
			break;
		case 2:
			if (last2 != NULL)
			{
				freeList(last2);
				last2 = NULL;
			}
			last2 = (node *)malloc(sizeof(node));
			last2->c = -1;
			last2->d = -1;
			last2->next = last2;
			printf("\nEnter the number of terms in the second polynomial : ");
			scanf("%d", &term2);
			for (i = 0; i<term2; i++)
			{
				printf("\nEnter the degree of the term %d : ", i + 1);
				scanf("%d", &degree);
				printf("\nEnter the coefficient of x^%d : ", degree);
				scanf("%d", &coefficient);
				temp = addNode(degree, coefficient);
				if (last2->next == last2)
				{
					if (i == 0)
					{
						last2->d = temp->d;
						last2->c = temp->c;
						free(temp);
					}
					else
					{
						last2->next = temp;
						temp->next = last2;
						last2 = temp;
					}
				}
				else
				{
					temp->next = last2->next;
					last2->next = temp;
					last2 = temp;
				}
			}
			last2 = sort_polynomial(last2, &term2);
			printf("\n\n");
			break;
		case 3:
			if (term1 == 0)
				printf("\nPlease input the first polynomial using the 1st menu option");
			else
			{
				printf("\nPolynomial 1 :\n\n");
				printPolynomial(last1, term1);
			}
			if (term2 == 0)
				printf("\n\nPlease input the second polynomial using the 2nd menu option");
			else
			{
				printf("\n\nPolynomial 2 :\n\n");
				printPolynomial(last2, term2);
			}
			printf("\n\n");
			break;
		case 4:
			last_res = addPolynomials(last1, last2, term1, term2, &term_res);
			last_res=sort_polynomial(last_res,&term_res);
			printf("\n");
			printPolynomial(last1, term1);
			printf("\n+\n");
			printPolynomial(last2, term2);
			printf("\n=\n");
			printPolynomial(last_res, term_res);
			printf("\n\n");
			break;
		case 5:
			last_res = multiplyPolynomials(last1, last2, term1, term2, &term_res);
			last_res=sort_polynomial(last_res,&term_res);
			printf("\n");
			printPolynomial(last1, term1);
			printf("\n*\n");
			printPolynomial(last2, term2);
			printf("\n=\n");
			printPolynomial(last_res, term_res);
			printf("\n\n");
			break;
		case 6:
			printf("\nEnter the value of x for which the polynomials are to be evaluated : ");
			scanf("%d", &var_val);
			printf("\nPolynomial 1 :\nP1(%d) = ", var_val);
			evaluatePolynomial(last1, term1, var_val);
			printf("\nPolynomial 2 :\nP2(%d) = ", var_val);
			evaluatePolynomial(last2, term2, var_val);
			printf("\n\n");
			break;
		case 7:
			if (last1 != NULL)
				freeList(last1);
			if (last2 != NULL)
				freeList(last2);
			return EXIT_SUCCESS;
			break;
		default:
			printf("Invalid choice");
			printf("\n\n");
			while (getchar() != '\n');
			break;
		}
	} while (1);
	return EXIT_SUCCESS;
}

void printMenu()
{
	printf("Menu\n1. Input first polynomial\n2. Input second polynomial\n3. Display Polinomials\n4. Add\n5. Multiply\n6. Evaluate Polynomials\n7. Exit\nChoice : ");
}

node *addNode(int degree, int coefficient)
{
	node *temp = (node *)malloc(sizeof(node));
	temp->d = degree;
	temp->c = coefficient;
	temp->next = NULL;
	return temp;
}

void printPolynomial(node *temp, int terms)
{
	int i;
	for (i = 0; i<terms; i++)
	{
		temp = temp->next;
		if (i == 0)
		{
			if (temp->d == 0)
			{
				printf("%d", temp->c);
			}
			else if (temp->d == 1)
			{
				if (temp->c == 1)
					printf("x");
				else
					printf("%dx", temp->c);
			}
			else
			{
				if (temp->c == 1)
					printf("x^%d", temp->d);
				else
					printf("%dx^%d", temp->c, temp->d);
			}
		}
		else
		{
			if (temp->d == 0)
			{
				printf(" + %d", temp->c);
			}
			else if (temp->d == 1)
			{
				if (temp->c == 1)
					printf(" + x");
				else
					printf(" + %dx", temp->c);
			}
			else
			{
				if (temp->c == 1)
					printf(" + x^%d", temp->d);
				else
					printf(" + %dx^%d", temp->c, temp->d);
			}
		}
	}
}

node *addPolynomials(node *last1, node *last2, int term1, int term2, int *term_res)
{
	node *last_add = (node *)malloc(sizeof(node));
	last_add->next = last_add;
	node *temp1 = last1->next, *temp2 = last2->next, *temp = NULL;
	int i = 0, j = 0, k = 0;
	while (i<term1 && j<term2)
	{
		if (temp1->d == temp2->d)
		{
			temp = addNode(temp1->d, temp1->c + temp2->c);
			if (last_add->next == last_add)
			{
				if (k == 0)
				{
					last_add->d = temp->d;
					last_add->c = temp->c;
					free(temp);
				}
				else
				{
					last_add->next = temp;
					temp->next = last_add;
					last_add = temp;
				}
			}
			else
			{
				temp->next = last_add->next;
				last_add->next = temp;
				last_add = temp;
			}
			k++;
			i++;
			j++;
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		else if ((temp1->d)>(temp2->d))
		{
			temp = addNode(temp1->d, temp1->c);
			if (last_add->next == last_add)
			{
				if (k == 0)
				{
					last_add->d = temp->d;
					last_add->c = temp->c;
					free(temp);
				}
				else
				{
					last_add->next = temp;
					temp->next = last_add;
					last_add = temp;
				}
			}
			else
			{
				temp->next = last_add->next;
				last_add->next = temp;
				last_add = temp;
			}
			k++;
			i++;
			temp1 = temp1->next;
		}
		else
		{
			temp = addNode(temp2->d, temp2->c);
			if (last_add->next == last_add)
			{
				if (k == 0)
				{
					last_add->d = temp->d;
					last_add->c = temp->c;
					free(temp);
				}
				else
				{
					last_add->next = temp;
					temp->next = last_add;
					last_add = temp;
				}
			}
			else
			{
				temp->next = last_add->next;
				last_add->next = temp;
				last_add = temp;
			}
			k++;
			j++;
			temp2 = temp2->next;
		}
	}
	while (i<term1)
	{
		temp = addNode(temp1->d, temp1->c);
		if (last_add->next == last_add)
		{
			if (k == 0)
			{
				last_add->d = temp->d;
				last_add->c = temp->c;
				free(temp);
			}
			else
			{
				last_add->next = temp;
				temp->next = last_add;
				last_add = temp;
			}
		}
		else
		{
			temp->next = last_add->next;
			last_add->next = temp;
			last_add = temp;
		}
		k++;
		i++;
		temp1 = temp1->next;
	}
	while (j<term2)
	{
		temp = addNode(temp2->d, temp2->c);
		if (last_add->next == last_add)
		{
			if (k == 0)
			{
				last_add->d = temp->d;
				last_add->c = temp->c;
				free(temp);
			}
			else
			{
				last_add->next = temp;
				temp->next = last_add;
				last_add = temp;
			}
		}
		else
		{
			temp->next = last_add->next;
			last_add->next = temp;
			last_add = temp;
		}
		k++;
		j++;
		temp2 = temp2->next;
	}
	*term_res = k;
	return last_add;
}

node *multiplyPolynomials(node *last1, node *last2, int term1, int term2, int *term_res)
{
	node *last_mul = (node *)malloc(sizeof(node));
	last_mul->next = last_mul;
	node *temp1 = last1->next, *temp2 = last2->next, *temp = NULL;
	int i = 0, j = 0, k = 0, l = 0;
	while (i<term1)
	{
		temp2 = last2->next;
		j = 0;
		while (j<term2)
		{
			if (k == 0)
			{
				temp = addNode((temp1->d) + (temp2->d), (temp1->c)*(temp2->c));
				k++;
				last_mul->d = temp->d;
				last_mul->c = temp->c;
				free(temp);
			}
			else
			{
				temp = last_mul->next;
				for (l = 0; l<k; l++)
				{
					if (temp->d == ((temp1->d) + (temp2->d)))
					{
						temp->c += (temp1->c)*(temp2->c);
						break;
					}
					temp = temp->next;
				}
				if (l == k)
				{
					temp = addNode((temp1->d) + (temp2->d), (temp1->c)*(temp2->c));
					k++;
					if (last_mul->next == last_mul)
					{
						last_mul->next = temp;
						temp->next = last_mul;
						last_mul = temp;
					}
					else
					{
						temp->next = last_mul->next;
						last_mul->next = temp;
						last_mul = temp;
					}
				}
			}
			temp2 = temp2->next;
			j++;
		}
		temp1 = temp1->next;
		i++;
	}
	*term_res = k;
	printf("Number of terms is %d", k);
	return last_mul;
}

node *sort_polynomial(node *last, int *term)
{
	if (last->next != last)
	{
		node *temp = last->next;
		node *temp2 = last->next;
		int co, de;
		int i = 0, j = 0;
		for (i = 0; i<(*term); i++) //sorts the given polynomial using bubble sort
		{
			temp = last->next;
			for (j = 0; j<(*term) - 1; j++)
			{
				if ((temp->d)<(temp->next->d))
				{
					co = temp->c;
					de = temp->d;
					temp->c = temp->next->c;
					temp->d = temp->next->d;
					temp->next->c = co;
					temp->next->d = de;
				}
				temp = temp->next;
			}
		} // for loop for bubble sort ends here
		temp = last;
		do // Removes terms with zero co-efficients
		{
			if (temp->next->c == 0)
			{
				if (last == temp->next)
					last = temp;
				temp2 = temp->next;
				temp->next = temp->next->next;
				free(temp2);
				(*term)--;
			}
			else
				temp = temp->next;
		} while (temp != last); //for loop to remove terms with zero degree ends here
		temp = last->next;
		do //Adds terms with same degree together
		{
			temp2 = temp->next;
			if (temp2->d == temp->d)
			{
				if (last == temp2)
					last = temp;
				temp->c += temp2->c;
				temp->next = temp2->next;
				free(temp2);
				(*term)--;
			}
			else
				temp = temp->next;
		} while (temp != last); // for loop for combination of equal degree terms ends here

	}
	return last;
}

void evaluatePolynomial(node *last, int term, int var_val)
{
	node *temp = last->next;
	int i, sum = 0;
	for (i = 0; i<term; i++)
	{
		printf("(%d)*(%d)^(%d)", temp->c, var_val, temp->d);
		if (i<term - 1)
			printf(" + ");
		sum += temp->c*power(var_val, temp->d);
		temp = temp->next;
	}
	printf(" = %d", sum);
}

int power(int var_val, int degree)
{
	int sum = 1, i;
	for (i = 0; i<degree; i++)
		sum *= var_val;
	return sum;
}

void freeList(node *last)
{
	node *temp = last->next;
	node *temp2;
	while (temp != last)
	{
		temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
	free(last);
}
