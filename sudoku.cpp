#include <iostream>
#include <string> 
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <fstream>
#include <istream>
#include <algorithm>
#include <vector> 
#include <string.h>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int result[9999999][9];//结果生成的数独终局 
char inputsudoku[99999999];
int sudoku[9][9];//基本数独 
void makesudoku(int num)
{
	memset(result,0,sizeof(result));
	int curnum=0;//现已经生成的数独个数 
	int i,j;
	int firstline[9]={2,3,4,5,6,7,8,9,1};//基本数独的第一行，第一个数位(0+1)%9+1=2 
	int initmove[9]={0,3,6,1,4,7,2,5,8};//分别向左移动0,3,6,1,4,7,2,5,8位
	int swap[9]={0,1,2,3,4,5,6,7,8};//交换行和列所用的数组 
	do
	{
		for(i=0;i<9;i++)
		{
			for(j=0;j<9;j++)
			{
				sudoku[i][j]=firstline[(j+initmove[i])%9];//依靠第一行的移动生成基本数独，因为第一个数不能动，所以第一行的全排列共8！个
			}
		}
		do
		{
			do
			{
				do
				{
					for(i=0;i<9;i++)
					{
						for(j=0;j<9;j++)
						{
							result[i+9*curnum][j]=sudoku[swap[i]][j];//第2,3行交换，第4,5,6行交换，第7,8,9行交换
						}
					}	
					curnum++;
					if(curnum==num)
					{
						return;
					}	
				}while(next_permutation(swap+1,swap+3));
			}while(next_permutation(swap+3,swap+6));
		}while(next_permutation(swap+6,swap+9));
	}while(next_permutation(firstline+1,firstline+9));
}
void makesudokutofile(int num)
{	
	ofstream WriteFile("sudoku.txt");
	if(WriteFile.fail())
	{
		printf("创建数独文件失败\n");
		return;	
	}
	int n,i,j;
	for(n=0;n<num;n++)
	{	
		for(i=0;i<9;i++)
		{
			for(j=0;j<9;j++)
			{	
				WriteFile<<(result[n*9+i][j]);
				if(j==8)
				{
					WriteFile<<("\n");
				}
				else 
				{
					WriteFile<<(" ");
				}
			}
		}
		WriteFile<<("\n");
	}
	printf("sudoku.txt已成功生成");
}
bool isright(int k,int row, int column,int num)
{	int i,j;
	for(i=0;i<9;i++)
	{
		if(result[k*9+i][column]==num)
		{
			return false;
		}
	}
	for(j=0;j<9;j++)
	{
		if(result[k*9+row][j]==num)
		{
			return false;
		}
	}
	for(i=row/3*3;i<=row/3*3+2;i++)
	{
		for(j=column/3*3;j<=column/3*3+2;j++)
		{
			if(result[k*9+i][j]==num)
			{
				return false;
			}
		}
	}
	return true;
}
bool dfs(int k,int row ,int column)
{	int num;
	if(column==9)
	{
		if(row==8)
		{
			return true;
		}
		row++;
		column=0;
	}
	if(result[k*9+row][column]!=0)
	{
		return dfs(k,row,column+1);
	}
	for(num=1;num<=9;num++)
	{
		if(isright(k,row,column,num)==true)
		{
			result[k*9+row][column]=num;
			if(dfs(k,row,column+1))
			{
				return true;
			}
		}
	}
	result[k*9+row][column]=0;
	return false;
}
void solvesudoku(string filepath)
{	int i=0,j=0,temp=0,n=0,k=0;
	ifstream ReadFile;
	ReadFile.open(filepath.c_str());
	if(ReadFile.is_open()==FALSE)
	{	
		printf("读取数独文件失败，请检查你的文件路径是否正确\n");	
	} 
	while(!ReadFile.eof())
	{
		ReadFile>>inputsudoku[n];
		n++;
	}
	n=n/9;
	memset(result,0,sizeof(result));
	for (i=0;i<n;i++)
	{
		for(j=0;j<9;j++)
		{
			result[i][j]=inputsudoku[temp]-'0';
			temp++;
		}
	}
	n=n/9;
	for(k=0;k<n;k++)
	{
		dfs(k,0,0);
	}
	makesudokutofile(n);
	return;
}
int main(int argc, char** argv) 
{	
if(argc<3)
	{	
		printf("参数过少\n");
		return 0; 
	}
	if(argc>3)
	{
		printf("参数过多\n");
		return 0; 
	}
	if(strcmp(argv[1],"-c")==0)
	{
		int n=atoi(argv[2]);
		if(n<=0)
		{
			printf("数独个数不能少于1个\n");
			return 0;
		}
		if(n>1000000)
		{
			printf("数独个数不能多于1000000个\n");
		}
		makesudoku(n);
		makesudokutofile(n); 
		return 0;
	}
	if(strcmp(argv[1],"-s")==0)
	{	
		solvesudoku(argv[2]);
	}
		return 0;

}
