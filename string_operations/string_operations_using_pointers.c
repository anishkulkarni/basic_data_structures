#include<stdio.h>
#include<stdlib.h> //Header files inclusion

#define SIZE 20 //Macro definition

void printMenu();

int getChoice();

void inputString(char *);

int lengthOfString(char *);

void displayString(char *);

int isPalindrome(char *,int);

int areEqualStrings(char *, char *, int, int);

void copyString(char *, char *);

void displayReverseString(char *,int);

int isSubStr(char *, int, char *, int);

int main()
{
	/*
		 * Input : none
		 * Utility : Main function to drive the program
		 * Output : Success or failure of program
	 */
	int choice, len1=0, len2=0, lenSubStr=0;
	char *str1=NULL, *str2=NULL, *str3=NULL, *subStr=NULL,temp[20];
	while (1)
	{
		printMenu();
		choice = getChoice();
		switch (choice)
		{
		case 1:
			while(getchar()!='\n');
			printf("\nEnter string 1 : ");
			inputString(temp);
			len1 = lengthOfString(temp);
			str1=(char *)malloc(len1*sizeof(char)+1);
			copyString(str1,temp);
			printf("Enter string 2 : ");
			inputString(temp);
			len2 = lengthOfString(temp);
			str1=(char *)malloc(len2*sizeof(char)+1);
		//copyString(str2,temp);
			printf("\n\n");
			break;
		case 2:
			printf("\nString 1 : ");
			displayString(str1);
			printf("\nString 2 : ");
			displayString(str2);
			printf("\n\n");
			break;
		case 3:
			printf("\nString 1 : ");
			displayString(str1);
			printf("\nLength of string 1 : %d",len1);
			printf("\nString 2 : ");
			displayString(str2);
			printf("\nLength of string 2 : %d", len2);
			printf("\n\n");
			break;
		case 4:
			printf("\nString 1 : ");
			displayString(str1);
			if (isPalindrome(str1, len1))
				printf("\nString 1 is palindrome");
			else
				printf("\nString 1 is not palindrome");
			printf("\nString 2 : ");
			displayString(str2);
			if(isPalindrome(str2, len2))
				printf("\nString 2 is palindrome");
			else
				printf("\nString 2 is not palindrome");
			printf("\n\n");
			break;
		case 5:
			printf("\nString 1 : ");
			displayString(str1);
			printf("\nString 2 : ");
			displayString(str2);
			if (areEqualStrings(str1, str2, len1, len2))
				printf("\nThe strings are equal");
			else
				printf("\nThe strings are not equal");
			printf("\n\n");
			break;
		case 6:
			str3=(char *)malloc(len1 *sizeof(char));
			printf("\nBefore copying : ");
			printf("\nString 1 : ");
			displayString(str1);
			printf("\nString 3 : ");
			displayString(str3);
			copyString(str1, str3);
			printf("\nAfter copying : ");
			printf("\nString 1 : ");
			displayString(str1);
			printf("\nString 3 : ");
			displayString(str3);
			free(str3);
			printf("\n\n");
			break;
		case 7:
			str3=(char *)malloc(len2 *sizeof(char));
			printf("\nBefore copying : ");
			printf("\nString 2 : ");
			displayString(str2);
			printf("\nString 3 : ");
			displayString(str3);
			copyString(str2, str3);
			printf("\nAfter copying : ");
			printf("\nString 2 : ");
			displayString(str2);
			printf("\nString 3 : ");
			displayString(str3);
			printf("\n\n");
			free(str3);
			break;
		case 8:
			printf("\nBefore reversing : ");
			printf("\nString 1 : ");
			displayString(str1);
			printf("\nString 2 : ");
			displayString(str2);
			printf("\nAfter reversing : ");
			printf("\nString 1 : ");
			displayReverseString(str1,len1);
			printf("\nString 2 : ");
			displayReverseString(str2,len2);
			printf("\n\n");
			break;
		case 9:
			printf("\nEnter the string to be checked for substring : ");
			while(getchar()!='\n');
			inputString(temp);
			lenSubStr = lengthOfString(temp);
			subStr=(char *)malloc(lenSubStr *sizeof(char));
			printf("\nString 1 : ");
			displayString(str1);
			printf("\nString 2 : ");
			displayString(str2);
			printf("\nThe given sub-string \"%s\" is present %d times in \"%s\"",subStr,isSubStr(str1,len1,subStr,lenSubStr),str1);
			printf("\nThe given sub-string \"%s\" is present %d times in \"%s\"",subStr,isSubStr(str2,len2,subStr,lenSubStr),str2);
			printf("\n\n");
			free(subStr);
			break;
		case 10:
			return 0;
			free(str1);
			free(str2);
			break;
		default:
			printf("Please input a valid choice.\n\n");
			while(getchar()!='\n');
			break;
		}
	}
	return 0;
}

void printMenu()
{
	/*
		 * Input : none
		 * Utility : Function to print menu of the program
		 * Output : none
	*/
	printf("Menu\n1. Input strings\n2. Display strings\n3. Display length of strings\n4. Palindrome\n5. Compare strings\n6. Copy string 1 to another string\n7. Copy string 2 to another string\n8. Reverse the strings\n9. Find a substring in the given strings\n10. Exit\nPlease chose an appropriate choice : ");
}

int getChoice()
{
	/*
	 	* Input : none
		* Utility : Function to get the choice of the user
		* Output : none
	*/
	int choice;
	scanf("%d",&choice);
	return choice;
}

void inputString(char *str)
{
	/*
		* Input : Pointer to string
		* Utility : Input string
		* Output : none
	 */
	gets(str);
}

int lengthOfString(char *str)
{
	/*
		* Input : Pointer to the string
		* Utility : Compute length of the string
		* Output : Length of the string
	*/
	int i;
	for (i = 0; str[i] != '\0'; i++);
	return i;
}

void displayString(char *str)
{
	/*
		* Input : Pointer to the string
		* Utility : Display string
		* Output : none
	*/
	printf("%s", str);
}

int isPalindrome(char *str,int len)
{
	/*
		* Input : Pointer to string, length of string
		* Utility : Check if string is palindrome
		* Output : 1 if string is palindrome 0 if not
	*/
	int i;
	for (i = 0; i < (len - 1) / 2; i++)
	{
		if (*(str+i) != *(str+(len - i - 1)))
			break;
	}
	if (i == (len - 1) / 2)
		return 1;
	else
		return 0;
}

int areEqualStrings(char *str1, char *str2, int len1, int len2)
{
	/*
		* Input : Pointers to 2 strings, lengths of both strings
		* Utility : Compare strings
		* Output : 1 if strings are equal 0 otherwise
	*/
	int i;
	if (len1 != len2)
		return 0;
	else
	{
		for (i = 0; i < len1; i++)
			if (*(str1+i) != *(str2+i))
				break;
		if (i == len1)
			return 1;
		else
			return 0;
	}
}

void copyString(char *str1, char *str2)
{
	/*
		* Input : Pointers to source and target strings
		* Utility : Copy source string to target string
		* Output : none
	*/
	int i;
	for (i = 0; *(str1+i) != '\0'; i++)
		*(str2+i) = *(str1+i);
	*(str2+i) = *(str1+i);
}

void displayReverseString(char *str,int len)
{
	/*
		* Input : Pointer to string, length of string
		* Utility : Display reverse string
		* Output : none
	*/
	int i;
	for (i = len-1; i >= 0; i--)
		printf("%c", *(str+i));
}

int isSubStr(char *str, int len, char *subStr, int lenSubStr)
{
	/*
		* Input : Pointers to string and substring and their lengths
		* Utility : To count appearances of substring in string
		* Output : Count of appearances of substring in string
	*/
	int i,j,count=0;
	if (lenSubStr > len)
		return 0;
	else
	{
		for (i = 0; i <= (len - lenSubStr); i++)
		{
			for (j = 0; j < lenSubStr; j++)
				if (*(subStr+j) != *(str+i + j))
					break;
			if(j==lenSubStr)
				count++;
		}
		return count;
	}
}
