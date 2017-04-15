#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

int search(char* input,char* find)
{
	int i;
	int k;
	int j;                                   //scan all the char in the input string
	int tmp=0;                              //counter 
	for(i=0;input[i]!=NULL;i++)
		{                        
			if(input[i]==find[0])
			{
				k=i+1;                     //start at i+1
				for(j=1;find[j]!=NULL;k++,j++)
				{
					if(find[j]-'a' != input[k]-'a')
					{
						k++,j++;          //for the statement in the if
						break;
					}
			    }
				if(input[k-1]-'a' == find[j-1]-'a') tmp++;
			}
		}
		return tmp;
}

int main()
{
	clock_t tStart = clock();
	int cnt=1;
	char find[50]={NULL};
	char input[50]={NULL};
    int tmp[100000]={NULL};
    int i,j;
	
	fstream file("test3.txt",ios::in);
	if(!file);
	else
	{   
	    file>>find; 
	    tmp[0]=1;                               //The first number must be 1. 
	while(file>>input)
	{
		tmp[cnt]=search(input,find);
	    cnt++;
	}
	    file.close();
    }
    clock_t tEnd = clock();   
    fstream file2("test3out.txt",ios::out);
	file2<<tEnd-tStart<<"ms"<<endl;          //End thime - start time = execute time 

	for(i=1;i<=cnt;i++)
	    {
		    for(j=0;j<tmp[i-1];j++) file2<<i;
	    }
	    
	return 0;
} 
