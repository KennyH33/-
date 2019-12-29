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
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int result[9999999][9];//������ɵ������վ� 
int sudoku[9][9];//�������� 
void makesudoku(int num)
{
	memset(result,0,sizeof(result));
	int curnum=0;//���Ѿ����ɵ��������� 
	int i,j;
	int firstline[9]={2,3,4,5,6,7,8,9,1};//���������ĵ�һ�У���һ����λ(0+1)%9+1=2 
	int initmove[9]={0,3,6,1,4,7,2,5,8};//�ֱ������ƶ�0,3,6,1,4,7,2,5,8λ
	int swap[9]={0,1,2,3,4,5,6,7,8};//�����к������õ����� 
	do
	{
		for(i=0;i<9;i++)
		{
			for(j=0;j<9;j++)
			{
				sudoku[i][j]=firstline[(j+initmove[i])%9];//������һ�е��ƶ����ɻ�����������Ϊ��һ�������ܶ������Ե�һ�е�ȫ���й�8����
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
							result[i+9*curnum][j]=sudoku[swap[i]][j];//��2,3�н�������4,5,6�н�������7,8,9�н���
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
	ofstream OpenFile("sudoku.txt");
	if(OpenFile.fail())
	{
		printf("���������ļ�ʧ��\n");
		return;	
	}
	int n,i,j;
	for(n=0;n<num;n++)
	{	
		for(i=0;i<9;i++)
		{
			for(j=0;j<9;j++)
			{	
				OpenFile<<(result[n*9+i][j]);
				if(j==8)
				{
					OpenFile<<("\n");
				}
				else 
				{
					OpenFile<<(" ");
				}
			}
		}
		OpenFile<<("\n");
	}
	printf("sudoku.txt�ѳɹ�����");
}
void solve()
{
	return;
}
int main(int argc, char** argv) 
{
if(argc<3)
	{	
		printf("��������\n");
		return 0; 
	}
	if(argc>3)
	{
		printf("��������\n");
		return 0; 
	}
	if(strcmp(argv[1],"-c")==0)
	{
		int n=atoi(argv[2]);
		if(n<=0)
		{
			printf("����������������1��\n");
			return 0;
		}
		if(n>1000000)
		{
			printf("�����������ܶ���1000000��\n");
		}
		makesudoku(n);
		makesudokutofile(n); 
		return 0;
	}
	if(strcmp(argv[1],"-s")==0)
	{
			
		solve()	;
	}
		return 0;

}
