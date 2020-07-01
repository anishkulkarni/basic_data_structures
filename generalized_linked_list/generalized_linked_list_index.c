#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

typedef enum type { name, link }type;

typedef union data
{
	char name[20];
	struct node *down_link;
}data;

typedef struct node
{
	type node_type;
	data node_data;
	struct node *next;
}node;

node *create_list(node *, char str[]);

void display_list(node *);

node *add_node()
{
	node *temp = (node *)malloc(sizeof(node));
	temp->node_data.down_link = NULL;
	temp->next = NULL;
	return temp;
}

int main()
{
	node *head = NULL;
	char str[200];
	printf("Enter the index : ");
	fgets(str, 199, stdin);
	head = create_list(head, str);
	display_list(head);
}

node *create_list(node *head, char str[])
{
	int i = 0, j = 0, open = 0, close = 0;
	node *temp;
	for (i = 0; str[i] != '\0';)
	{
		if (str[i] == '{' && i == 0)
		{
			head = add_node();
			temp = head;
		}
		else
		{
			temp->next = add_node();
			temp = temp->next;
		}
		i++;
		j = 0;
		while (str[i] != ','&&str[i] != '{'&&str[i] != '}')
		{
			temp->node_data.name[j] = str[i];
			i++;
			j++;
		}
		temp->node_data.name[j] = '\0';
		temp->node_type = name;
		if (str[i] == '{')
		{
			open++;
			temp->next = add_node();
			temp = temp->next;
			temp->node_type = link;
			temp->node_data.down_link = create_list(temp->node_data.down_link, &str[i]);
			while (open != close)
			{
				i++;
				if (str[i] == '{')
					open++;
				else if (str[i] == '}')
					close++;
			}
			i++;
		}
		if (str[i] == '}')
			return head;
	}
}

void display_list(node *head)
{
	static int depth = 0;
	depth++;
	int i;
	if (head == NULL)
	{
		if (depth == 1)
			printf("list is empty");
		else
			printf("sublist is empty");
	}
	else
	{
		while (head != NULL)
		{
			if (head->node_type == name)
			{
				printf("\n");
				for (i = 1; i < depth; i++)
					printf("\t");
				printf("%s", head->node_data.name);
			}
			else
				display_list(head->node_data.down_link);
			head = head->next;
		}
	}
	depth--;
}