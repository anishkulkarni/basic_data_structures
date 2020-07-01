#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[])
{
	if(!strcmp(argv[1],"TYPE"))
	{
		if(argc!=3)
		{
			printf("Invalid argument/s\nPlease use the following format :\nTYPE <filename>\n");
			exit(1);
		}
		else
		{
			char c;
			FILE *fp;
			fp=fopen((argv[2]),"r");
			if(fp!=NULL)
			{
				while((c=fgetc(fp))!=EOF)
				putchar(c);
			}
			else
			{
				printf("Source file not found");
				exit(1);
			}
			printf("\n");
			fclose(fp);
		}
	}
	else if(!strcmp(argv[1],"COPY"))
	{
		if(argc!=4)
		{
			printf("Invalid argument/s\nPlease use the following format :\nCOPY <source filename> <destination filename>\n");
			exit(1);
		}
		else
		{
			char c;
			FILE *fpSource,*fpTarget;
			fpSource=fopen((argv[2]),"r");
			if(fpSource==NULL)
			{
				printf("Source file does not exist.\n");
				exit(0);
			}
			fpTarget=fopen((argv[3]),"w");
			while((c=fgetc(fpSource))!=EOF)
			fputc(c,fpTarget);
			printf("File successfully copied\n");
			fclose(fpSource);
			fclose(fpTarget);
			return EXIT_SUCCESS;
		}
	}
	else
	{
		printf("Invalid argument/s\nPlease use the following format :\nTYPE <filename>\nOR\nCOPY <source filename> <destination filename>\n");
		exit(1);
	}
	return EXIT_SUCCESS;
}
