#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	char value;
	struct node *next;
	struct node *previous;
}node;

void print_menu();

node *add_node(char);

void print_reverse(node *);

int main()
{
	int choice, i;
	node *head = NULL;
	node *temp = NULL;
	node*temp2 = NULL;
	char c;
	do
	{
		print_menu();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: //Case to input string
			while (getchar() != '\n');
			printf("\nEnter the string to input : ");
			while ((c = getchar()) != '\n')
			{
				temp = add_node(c);
				if (head == NULL)
				{
					head = temp;
					head->next = NULL;
					head->previous = NULL;
				}
				else
				{
					temp = head;
					while (temp->next != NULL)
						temp = temp->next;
					temp->next = add_node(c);
					temp->next->previous = temp;
				}
			}
			printf("\n");
			break;
		case 2: //Case for forward display
			printf("\nString in forward order is : ");
			temp = head;
			while (temp != NULL)
			{
				printf("%c", temp->value);
				temp = temp->next;
			}
			printf("\n\n");
			break;
		case 3: //Case for reverse display
			printf("\nString in reverse order is : ");
			print_reverse(head);
			printf("\n\n");
			break;
		case 4: //Case for inserting character
			while (getchar() != '\n');
			printf("\nEnter the position where you wnat to add a character : ");
			scanf("%d", &choice);
			while (getchar() != '\n');
			printf("\nEnter the character to be added : ");
			scanf("%c", &c);
			if (choice == 0)
				choice++;
			if (choice == 1)
			{
				temp2 = add_node(c);
				temp2->next = head;
				head->previous = temp2;
				head = temp2;
				printf("\nCharacter %c added at specified location\n", c);
			}
			else
			{
				temp = head;
				while (choice>1)
				{
					temp = temp->next;
					choice--;
					if (temp->next == NULL)
						break;
				}
				if (choice>2)
				{
					printf("\nInvalid position entered\n");
				}
				else if (temp->next == NULL)
				{
					temp->next = add_node(c);
					temp->next->previous = temp;
					printf("\nCharacter %c added at specified location\n", c);
				}
				else
				{
					temp2 = add_node(c);
					temp2->previous = temp->previous;
					temp->previous->next = temp2;
					temp->previous = temp2;
					temp2->next = temp;
					printf("\nCharacter %c added at specified location\n", c);
				}
			}
			printf("\n");
			break;
		case 5: //Case to delete element
			while (getchar() != '\n');
			printf("\nEnter the element to be deleted : ");
			scanf("%c", &c);
			temp = head;
			while (temp != NULL)
			{
				if (temp->value == c)
				{
					if (temp == head)
					{
						head = head->next;
						free(temp);
						printf("\nElement successfully deleted");
						break;
					}
					else if (temp->next == NULL)
					{
						temp->previous->next = NULL;
						free(temp);
						printf("\nElement successfully deleted");
						break;
					}
					else
					{
						temp->previous->next = temp->next;
						temp->next->previous = temp->previous;
						free(temp);
						printf("\nElement successfully deleted");
						break;
					}
				}
				else
					temp = temp->next;
			}
			if (temp == NULL)
				printf("\nGiven element not found");
			printf("\n\n");
			break;
		case 6: //Case to exit
			temp2 = head;
			while (temp != NULL)
			{
				temp = temp2->next;
				free(temp2);
			}
			printf("\nSuccessfully exited the program");
			return EXIT_SUCCESS;
			break;
		default: //default case
			printf("Invalid choice");
			printf("\n\n");
			while (getchar() != '\n');
			break;
		}
	} while (1);
	return EXIT_SUCCESS;
}

void print_menu()
{
	printf("Menu\n1. Input String\n2. Display String in forward order\n3. Display string in reverse order\n4. Insert character\n5. Delete character\n6. Exit\nChoice : ");
}

node *add_node(char c)
{
	node *temp = (node *)malloc(sizeof(node));
	temp->value = c;
	temp->next = NULL;
	temp->previous = NULL;
	return temp;
}

void print_reverse(node *head)
{
	if (head->next == NULL)
		printf("%c", head->value);
	else
	{
		print_reverse(head->next);
		printf("%c", head->value);
	}
}