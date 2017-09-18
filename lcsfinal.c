#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

float spaces(char s[])
{
	int i;
	float count=0;
	for(i=0;i<strlen(s);i++)
	{
		if (s[i]==' ')
		{
			count++;
		}
	}
	return count;
}
void fileset(char text[])
{
	for(int i=0;i<strlen(text);i++)
	{
		if((text[i]>64&&text[i]<92))
			{
				text[i]=text[i]+32;
			}
		if((text[i]>96&&text[i]<123)||(text[i]>47&&text[i]<58))
			{
				continue;
			}
		else
			{
				text[i]=' ';
			}	
	}
	int count=0;
	
	for(int i=0;i<strlen(text);i++)
	{
		if(text[i]==' ')
		{
			count++;
		}
		else
		{
			if(count>1)
			{
				for(int j=i-count+1;j<strlen(text);j++)
				{
					text[j]=text[j+count-1];			
				}
			}
			count=0;
		}
	}
	
}
int split(char s1[],char s2[])
{
	char str1[100][50]={' '};
	int i=0,row1=0;
	char *token1=strtok(s1," ");
	while (token1!=NULL)
	{
		strcpy(str1[i],token1);
		token1=strtok(NULL," ");
		i++;
		row1++;
	}
	int row2=0;
	i=0;
	char str2[100][50]={' '};
	char *token=strtok(s2," ");
	while (token!=NULL)
	{
		strcpy(str2[i],token);

		token=strtok(NULL," ");
		i++;
		row2++;
	}
	int j,count=0,finalcount=0,flag=0,temp;
	for (i=0;i<row1;i++)
	{
		temp=i;
		for(j=0;j<row2;j++)
		{
			if (strcmp(str1[i],str2[j])==0)
			{
				count+=strlen(str1[i]);
				i++;
			}
			else
			{
				count=0;
			}
			if (finalcount<count)
			{
				finalcount=count;
			}
		}
		i=temp;
		// flag=0;
		count=0;
	}
	
		return finalcount;
}
int main()
{
	char filestr[100][30];
	DIR *d;
	struct dirent *dir;
	d=opendir(".");

	int fcount=0;
	if (d)
	{
		while((dir=readdir(d))!=NULL)
		{
			int m=strlen(dir->d_name);
			if (((int)dir->d_name[m-1])==116&&((int)dir->d_name[m-2])==120&&((int)dir->d_name[m-3])==116)
			{
				strcpy(filestr[fcount],dir->d_name);
				fcount++;
			}
		}
	}
	printf("files present in the folder are=%d\n",fcount);
	printf("*matrix*  ");
	int i;
	for (i=0;i<fcount;i++)
	{
		printf(" %17s",filestr[i]);
	}
	printf("\n");
	for (int i = 0; i < fcount; ++i)
	{
		printf("*************************");
	}
	
	FILE *fp;
	int j,x,k,k1;
	char c;
	for (i=0;i<fcount;i++)
	{
		printf("\n%s ||",filestr[i]);
		char text1[100];
		char text2[100];
		for (j=0;j<fcount;j++)
		{
			fp=fopen(filestr[i],"r");
			if(fp==NULL)
			{
				printf("error!");
				exit(1);
			}
			c=fgetc(fp);
			int k=0;
			while (c!=EOF)
			{
				if(c=='\n')
			 	{
			 		text1[k]=' ';
			 		k++;
			 	}
			else
				{
					text1[k]=c;
			 		k++;
			 	}
				c=fgetc(fp);
				
			}
			text1[k]='\0';
			k=0;
			int k1=0;
			fp=fopen(filestr[j],"r");
			c=fgetc(fp);
			while (c!=EOF)
			{
					if(c=='\n')
			 	{
			 		text2[k1]=' ';
			 		k1++;
			 	}
			else
				{
					text2[k1]=c;
			 		k1++;
			 	}

				c=fgetc(fp);
				
			}
			text2[k1]='\0';
			k1=0;
			fileset(text1);
			fileset(text2);
			float l1=strlen(text1)-spaces(text1);
			float l2=strlen(text2)-spaces(text2);
			int num=split(text1,text2);
			float percentage=(num*2.0)/(l1+l2);
			printf("%15f ||",percentage*100);
		}
	}
}
