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
char inputsudoku[99999999];
char outputsudoku[99999999];
int result[9999999][9];//������ɵ������վ� 
class sudoku
{
private:
	int sudoku[9][9];//�������� 
public:
	void makesudoku(int num);
	void makesudokutofile(int num);
	bool isright(int k, int row, int column, int num);
	bool dfs(int k, int row, int column);
	void solvesudoku(string filepath);
};
void sudoku::makesudokutofile(int num)
{
	ofstream WriteFile("sudoku.txt");
	if (WriteFile.fail())
	{
		printf("���������ļ�ʧ��\n");
		return;
	}
	int n, i, j;//n��9*9����ĸ�����i�Ǿ�����,j�Ǿ����� 
	int p = 0;
	for (n = 0; n < num; n++)
	{
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				outputsudoku[p]=result[n * 9 + i][j]+'0';//��int�Ͷ�ά����ת����char���ַ��� 
				p++;
				if(j==8&&n==num-1&&i==8)
				{
					break;
				}
				if (j == 8)
				{
					outputsudoku[p]='\n';//��������һ����Ҫ���� 
					p++;
				}
				else
				{
					outputsudoku[p]=' ';//������֮����Ҫ�ո� 
					p++;
				}
			}
		}
		if(n!=num-1)
		{
			outputsudoku[p]='\n';//9*9����֮����Ҫ���� 
			p++;
		}
	}
	WriteFile << outputsudoku;
	printf("sudoku.txt�ѳɹ�����");
}
void sudoku::makesudoku(int num)
{
	memset(result, 0, sizeof(result));
	int curnum = 0;//���Ѿ����ɵ��������� 
	int i, j;
	int firstline[9] = { 2,3,4,5,6,7,8,9,1 };//���������ĵ�һ�У���һ����λ(0+1)%9+1=2 
	int initmove[9] = { 0,3,6,1,4,7,2,5,8 };//�ֱ������ƶ�0,3,6,1,4,7,2,5,8λ
	int swap[9] = { 0,1,2,3,4,5,6,7,8 };//�����к������õ����� 
	do
	{
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				sudoku[i][j] = firstline[(j + initmove[i]) % 9];//������һ�е��ƶ����ɻ�����������Ϊ��һ�������ܶ������Ե�һ�е�ȫ���й�8����
			}
		}
		do
		{
			do
			{
				do
				{
					for (i = 0; i < 9; i++)
					{
						for (j = 0; j < 9; j++)
						{
							result[i + 9 * curnum][j] = sudoku[swap[i]][j];//��2,3�н�������4,5,6�н�������7,8,9�н���
						}
					}
					curnum++;
					if (curnum == num)
					{
						return;
					}
				} while (next_permutation(swap + 1, swap + 3));
			} while (next_permutation(swap + 3, swap + 6));
		} while (next_permutation(swap + 6, swap + 9));
	} while (next_permutation(firstline + 1, firstline + 9));
}
bool sudoku::isright(int k, int row, int column, int num)
{
	int i, j;
	for (i = 0; i < 9; i++)//��ͬһ����������ͬ���� 
	{
		if (result[k * 9 + i][column] == num)
		{
			return false;
		}
	}
	for (j = 0; j < 9; j++)//��ͬһ����������ͬ���� 
	{
		if (result[k * 9 + row][j] == num)
		{
			return false;
		}
	}
	for (i = row / 3 * 3; i <= row / 3 * 3 + 2; i++)//��3*3С������������ͬ���� 
	{
		for (j = column / 3 * 3; j <= column / 3 * 3 + 2; j++)
		{
			if (result[k * 9 + i][j] == num)
			{
				return false;
			}
		}
	}
	return true;
}
bool sudoku::dfs(int k, int row, int column)
{
	int num;
	if (column == 9)
	{
		if (row == 8)
		{
			return true;//�������ھ��е�ʮ��ʱ�������� 
		}
		row++;// ������뵽��һ�� 
		column = 0;
	}
	if (result[k * 9 + row][column] != 0)
	{
		return dfs(k, row, column + 1);//����0ֱ������ 
	}
	for (num = 1; num <= 9; num++)//��1-9������ 
	{
		if (isright(k, row, column, num) == true)
		{
			result[k * 9 + row][column] = num; //����������������� 
			if (dfs(k, row, column + 1))
			{
				return true;//������涼û�г�ͻ���������������� 
			}
		}
	}
	result[k * 9 + row][column] = 0;//����޽��򷵻�false 
	return false;
}
void sudoku::solvesudoku(string filepath)
{
	int i = 0, j = 0, temp = 0, n = 0, k = 0;
	ifstream ReadFile;
	ReadFile.open(filepath.c_str());
	if (ReadFile.is_open() == FALSE)
	{
		printf("��ȡ�����ļ�ʧ�ܣ���������ļ�·���Ƿ���ȷ\n");
	}
	while (!ReadFile.eof())
	{
		ReadFile >> inputsudoku[n];
		n++;
	}
	n = n / 9;//��ʱn�����ж����� 
	memset(result, 0, sizeof(result));
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < 9; j++)
		{
			result[i][j] = inputsudoku[temp] - '0';//��char���ַ���תΪint��ά���鷽����� 
			temp++;
		}
	}
	n = n / 9;//��ʱn�����ж��ٸ�9*9���� 
	for (k = 0; k < n; k++)
	{
		dfs(k, 0, 0);//����n��dfs���� 
	}
	makesudokutofile(n);
	return;
}
int main(int argc, char** argv)
{
	sudoku sudo;
	if (argc < 3)
	{
		printf("��������\n");
		return 0;
	}
	if (argc > 3)
	{
		printf("��������\n");
		return 0;
	}
	if (strcmp(argv[1], "-c") == 0)//�����վ� 
	{
		int n = atoi(argv[2]);
		if (n <= 0)
		{
			printf("����������������1��\n");
			return 0;
		}
		if (n > 1000000)
		{
			printf("�����������ܶ���1000000��\n");
			return 0;
		}
		sudo.makesudoku(n);
		sudo.makesudokutofile(n);
		return 0;
	}
	if (strcmp(argv[1], "-s") == 0)//������ 
	{
		sudo.solvesudoku(argv[2]);
	}
	return 0;

}
