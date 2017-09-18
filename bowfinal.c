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
	//seperating words using space
	char word[no][25];
	int d;
	int len=strlen(text);
	int wcount=0;
	int i=0,j=0;
	for(d=0;d<len;d++)
	{
		if(text[d]!=' ')
			{
				word[i][j]=text[d];
				j++;
			}
		else
			{
				word[i][j]='\0';
				i++;
				j=0;
				wcount++;
			}
	}
	word[i][j]='\0';
	wcount++;
	// print words
	for(int k=0;k<wcount;k++)
	 {
	 printf("%s ",word[k]);
	 }
	 printf("\n");
	//to isolate unique words
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
			n=0;
			d++;
		}
		m++;
	}
	d=0;
	for(i=0;i<m;i++)
	{
		if(strcmp(dict[i].commonword,"\0")!=0)
		{
			*dict[d].commonword=*dict[i].commonword;
			d++;
		}
	}
	m=d;
//to calculate unique word count
	for(j=0;j<m;j++)
	{
		dict[j].commonwcount=0;
		for(i=0;i<wcount;i++)
		{
			if(strcmp(word[i],dict[j].commonword)==0){dict[j].commonwcount++;}
		}
	}

	return m;

}
int commonWords(int m1,struct dictonary dict1[],int m2,struct dictonary dict2[]){
	//to calculate number of common words
	int common=0;
	for(int i=0;i<m1;i++)
	{
		for(int j=0;j<m2;j++)
		{
			if(strcmp(dict1[i].commonword,dict2[j].commonword)==0)
				{
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


float calculate(int m1,struct dictonary dict1[],int m2,struct dictonary dict2[]){
	//percentage calclulation of no of common words in both the comparision files
	float f1percentage=mul(m1,dict1);
	float f2percentage=mul(m2,dict2);

	int s=commonWords(m1,dict1,m2,dict2);

	float p = s*100.0/(sqrt(f1percentage*1.0)*sqrt(f2percentage*1.0));
	return p;

}


void fileset(char text[])
{
	for(int i=0;i<strlen(text);i++)
	{
		// converting every small case alphabet to upper case letter
		if((text[i]>64&&text[i]<92))
			{
				text[i]=text[i]+32;
			}
		//replacing symbols,unknown characters with spaces" "
		if((text[i]>96&&text[i]<123)||(text[i]>47&&text[i]<58))
			{
				continue;
			}
		else
			{
				text[i]=' ';
			}	
	}
	
	// removing excess spaces and shifting the index values
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


int words(char text[])
{
	// calcuating number of word present in the file
	int count=0;
	for(int i=0;i<strlen(text);i++)
		{
			if(text[i]==' ')
				{
					count++;
				}
		}
	return count;


}
int main()
{
	printf("Plagiarism check by Bag Of Words technique\n");
		long lSize1;
		char text1[1000];
		char a;
		int z;
		FILE *fp1;
		// to open file we use fopen
		fp1=fopen("F:\\msit\\c&java cspp2\\project\\final\\file1.txt","r");
		if(fp1==NULL)
			{
			// if the file is empty
				printf("error!");
				exit(1);
			}	
		//to read a file fgetc is used
		a=fgetc(fp1);
		z=0;
		while(a!=EOF)
		{
			//considering the "n" no of lines in one single line 
			if(a=='\n')
			 	{
			 		text1[z]=' ';
			 		z++;
			 	}
			else
				{
					text1[z]=a;
			 		z++;
			 	}
			a=fgetc(fp1);
	 	}
	 	lSize1=z;
		fclose(fp1);
		struct dictonary dict1[lSize1];
		fileset (text1);
		int n1=words(text1);
		int m1=dictmaking(text1,dict1,n1);



		long lSize2;
		char text2[1000];
		FILE *fp2;
		fp2=fopen("F:\\msit\\c&java cspp2\\project\\final\\file2.txt","r");
		if(fp2==NULL)
			{
				printf("error!");
				exit(1);
			}
			a=fgetc(fp2);
			z=0;
		while(a!=EOF)
		{
			if(a=='\n')
			 	{
			 		text2[z]=' ';
			 		z++;
			 	}
			else
				{
					text2[z]=a;
			 		z++;
			 	}
			a=fgetc(fp2);
			}
			lSize2=z;
			// printf("lsize2=%ld\n",lSize2 );
		fclose(fp2);
		struct dictonary dict2[lSize2];
		fileset(text2);
		int no2=words(text2);
		int m2=dictmaking(text2,dict2,no2);
		printf("%.2f",calculate(m1,dict1,m2,dict2));

}
