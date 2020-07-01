#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int value;
	struct node *next;
}node;

void printMenu();

node *insertNode(int);

void deleteNode(node *);

void reverse(node *);

void display(node *);

void printReverse(node *);

int main(void)
{
	int choice,numberOfElements=0,i,data,pos;
	node *head=(node *)malloc(sizeof(node));
	node *temp,*temp_after;
	head->value=0;
	head->next=NULL;
	do
	{
		printMenu();
		scanf("%d",&choice);
		switch(choice)
		{
		case 1: //Insert at beginning
			printf("\nEnter the element to be inserted : ");
			scanf("%d",&data);
			temp=head->next;
			head->next=insertNode(data);
			head->next->next=temp;
			numberOfElements++;
			printf("\nElement successfully inserted at the beginning\n\n");
			break;
		case 2: //Insert at last
			printf("\nEnter the element to be inserted : ");
			scanf("%d",&data);
			temp=head;
			while(temp->next!=NULL)
				temp=temp->next;
			temp->next=insertNode(data);
			numberOfElements++;
			printf("\nElement successfully inserted at the end\n\n");
			break;
		//Insert at middle
			/*printf("Enter the element to be inserted : ");
			scanf("%d",&data);
			temp=head;
			for(i=0;i<numberOfElements/2;i++)
				temp=temp->next;
			temp_after=temp->next;
			temp->next=insertNode(data);
			temp->next->next=temp_after;
			numberOfElements++;
			printf("\nElement successfully inserted in the middle\n\n");
			break;*/
		case 3://inset at middle
			printf("\nEnter the position where element is to be inserted : ");
			scanf("%d",&pos);
			if(pos>numberOfElements+1||pos<1)
				printf("\nThe linked list has %d elements and hence cannot access position %d\n\n",numberOfElements,pos);
			else if(pos==0)
				pos++;
			else
			{
				printf("\nEnter the data to be inserted : ");
				scanf("%d",&data);
				temp=head;
				for(i=1;i<pos;i++)
				{
					temp=temp->next;
				}
				temp_after=temp->next;
				temp->next=insertNode(data);
				temp->next->next=temp_after;
				numberOfElements++;
				printf("\nElement successfully inserted at position : %d\n\n",pos);
			}
			break;
		case 4: //Reverse
			reverse(head);
			printf("\nList successfully reversed\n\n");
			break;
		case 5: //Display
			if(head->next==NULL)
				printf("\nLinked List is empty\n\n");
			else
			{
				printf("\nFollowing are the contents of the list :\n\n");
				display(head);
				printf("\n\n");
			}
			break;
		case 6://display in reverse order
			printf("\nFollowing is the linked list in the reverse order :\n\n");
			printReverse(head->next);
			printf("\n\nThe original list remains intact\n\n");
			break;
		case 7: //Delete
			printf("\nEnter the element to be deleted : ");
			scanf("%d",&data);
			temp=head;
			while(temp->next!=NULL)
			{
				if(temp->next->value==data)
					break;
				temp=temp->next;
			}
			if(temp->next->value==data)
			{
				deleteNode(temp);
				printf("\nElement successfully deleted\n\n");
				numberOfElements--;
			}
			else
			{
				printf("\nGiven element does not exist\n\n");
			}
			break;
		case 8://exit
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

void display(node *head)
{
	node *temp=head;
	while(temp->next!=NULL)
	{
		temp=temp->next;
		printf("\t%d",temp->value);
	}
}

void reverse(node *head)
{
	node *temp_after,*temp_before,*temp;
	temp_after=head->next;
	temp=NULL;
	while(temp_after!=NULL)
	{
		temp_before=temp;
		temp=temp_after;
		temp_after=temp_after->next;
		temp->next=temp_before;
	}
	head->next=temp;
}

void printMenu()
{
	printf("Menu\n1. Insert at first\n2. Insert at last\n3. Insert at middle\n4. Reverse\n5. Display in same order\n6. Display in reverse order\n7. Delete\n8. Exit\nChoice : ");
}

node *insertNode(int data)
{
	node *here = (node *)malloc(sizeof(node));
	here -> next = NULL;
	here -> value = data;
	return here;
}

void deleteNode(node *afterThis)
{
	node *temp = afterThis->next;
	afterThis->next=temp->next;
	free(temp);
}

void printReverse(node* head)
{
    if (head == NULL)
       return;
    printReverse(head->next);
    printf("\t%d", head->value);
}
