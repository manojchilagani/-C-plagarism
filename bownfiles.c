#include <stdio.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <stdlib.h>

struct dictonary
{
	char commonword[9999];
	int commonwcount;
}dict[1000];

int dictmaking(char text[], struct dictonary dict[],int no)
{
	//seperating words using space as reference
	char word[no][25];
	int d,wcount=0,i=0,j=0;
	int len=strlen(text);

	for(d=0;d<len;d++)
	{
		if(text[d]!=' ')
			{
				//printf("\n%c",text[d]);
				word[i][j]=text[d];
				j++;
			}
		else
			{
				word[i][j]='\0';
				//printf("\n%s",word[i]);
				i++;
				j=0;
				wcount++;
			}
	}
	word[i][j]='\0';
	wcount++;
	// printf("\nwcount:%d",wcount);
	// printf("word[0]:%s,word[1]:%s,word[2]:%s",word[0],word[1],word[2]);
	// for(i=0;i<wcount;i++)
	// {
	// 	printf("\nword in array:%s",word[i]);
	// }
	

	//considering common words
	int l=0,m=0,n=0;
	d=0;
	int count=0;
	for(i=0;i<wcount;i++)
	{
		int flag=0;
		for(j=0;j<m;j++)
		{
			if(strcmp(word[i],dict[j].commonword)==0)
				{
					flag=1;
					count++;
					break;
				}
		}
		if(flag==0)
		{
			while(word[m][n]!='\0')
			{
				dict[m].commonword[n]=word[m][n];
				n++;
			}
			dict[m].commonword[n]='\0';
			n=0;
			d++;
		}
		m++;
	}
	// d=0;
	// for(i=0;i<m;i++)
	// {
	// 	if(strcmp(dict[i].commonword,"\0")!=0)
	// 	{
	// 		*dict[d].commonword=*dict[i].commonword;
	// 		d++;
	// 	}
	// }
	// m=d;
	
//to calculate unique word count
	for(j=0;j<m;j++)
	{
		dict[j].commonwcount=0;
		for(i=0;i<wcount;i++)
		{
			if(strcmp(word[i],dict[j].commonword)==0)
				{
					dict[j].commonwcount++;
				}
		}
	}
	// for(i=0;i<m;i++)
	// {
	// 	printf("\nword:%s",dict[i].commonword);
	// }

	return m;

}




int commonWord(int m1,struct dictonary dict1[],int m2,struct dictonary dict2[])
{

	int common=0;
	for(int i=0;i<m1;i++)
	{
		for(int j=0;j<m2;j++)
		{
			if(strcmp(dict1[i].commonword,dict2[j].commonword)==0)
				{
					//printf("\n%s %s",dict1[i].commonword,dict2[j].commonword);
					common+=(dict1[i].commonwcount)*(dict2[j].commonwcount);

				}
		}
	}
	return common;
}


int mul(int m,struct dictonary dict[])
{
	int percentage=0;
	for(int i=0;i<m;i++)
	{
		percentage+=pow((dict[i].commonwcount),2);
	}
	return percentage;
}

float calculate(int m1,struct dictonary dict1[],int m2,struct dictonary dict2[])
{
	float f1percentage=mul(m1,dict1);
	float f2percentage=mul(m2,dict2);

	int s=commonWord(m1,dict1,m2,dict2);

	float p = s*100.0/(sqrt(f1percentage*1.0)*sqrt(f2percentage*1.0));

	
	return p;

}

int words(char text[])
{
	int count=1;
	for(int i=0;i<strlen(text);i++)
		{
			if(text[i]==' ')
				{
					count++;
				}
		}
	return count;
}



void	 required(char text[])
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
	//printf("%s",text);
	
}





int main(int argc,char *argv[])
{
	fflush(stdin);
//	printf("%s",argv[1]);
	char filestr[100][30],p[3000];
	int filescount=0;
	int fcount=0;
	DIR *d;
	//scanf("%[^\n]",p);
	struct dirent *dir;
	char path[100];
	int i=0;
	while(i<strlen(argv[1]))
	{
		path[i]=*(argv[1]+i);
		i++;
	}
	printf("%s",path);
	chdir(path);
	d=opendir(path);
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
	printf(".txt files present in the folder are=%d\n",fcount);
	printf("matrix   ");
	
	for (i=0;i<fcount;i++)
	{
		printf("%15s",filestr[i]);
	}
	printf("\n");
	for (i = 0; i < fcount; ++i)
	{
		printf("**********************");
	}
	FILE *fp1,*fp2;
	int j,x,m1;
	
	char a;

	for (i=0;i<fcount;i++)
	{

		printf("\n%s    ",filestr[i]);
		
		for (j=0;j<fcount;j++)
		{
			int z1=0,z2=0,l1=0,l2=0;
			char text1[100]={'0'};
			char text2[100]={'0'};
			fp1=fopen(filestr[i],"r");
				if(fp1==NULL)
				{
					printf("error!");
					exit(1);
				}
				

			a=fgetc(fp1);
			while(a!=EOF)
			{
			if(a=='\n')
			 	{
			 		text1[z1]=' ';
			 		z1++;
			 	}
			else
				{
					text1[z1]=a;
			 		z1++;
				}
				a=fgetc(fp1);
			}

			l1=z1;

			text1[l1]='\0';
			//printf("\n%s",text1);

			fclose(fp1);
			
			fp2=fopen(filestr[j],"r");
				if(fp2==NULL)
				{
					printf("error!");
					exit(1);
				}
			
			a=fgetc(fp2);
			while(a!=EOF)
			{
				if(a=='\n')
			 	{
			 		text2[z2]=' ';
			 		z2++;
			 	}
				else
				{
					text2[z2]=a;
			 		z2++;
			 	}
				a=fgetc(fp2);
			}
			text2[z2]='\0';
			//printf("\n%s",text2);
			l2=z2;
			// printf("%d\n",l2 );
			

			fclose(fp2);

			float percentage[fcount][fcount];


			required(text1);
			required(text2);
			// printf("\ntext1:%s",text1);
			// printf("\ntext2:%s",text2);
			int n1=words(text1);
			int n2=words(text2);
			//printf("\n%d %d",n1,n2);

			struct dictonary dict1[l1];
			struct dictonary dict2[l2];

			int m1=dictmaking(text1,dict1,n1);
			int m2=dictmaking(text2,dict2,n2);
			//printf("\ncommon:%d %d",m1,m2);



			
			printf("%15f",calculate(m1,dict1,m2,dict2));
		}
	}
}

