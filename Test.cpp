/*
实验题，最长公共子序列,非滚动数组方式，可以求出最长的
公共子序列 
*/


include<iostream>
include<vector>
using namespace std;
vector<char> LCS(char x[],int m,char y[],int n)
{
	vector<vector<int> > B;
	vector<char> Path;
	int i,j;
	//对辅助数组的初始化 
	for(i = 0;i <= m;++i)
	{
	}
	for(i = 0;i <= m;++i)
	{
		B[i][0] = 0;
	}
	for(i = 0;i <= n;++i)
	{
		B[0][i] = 0;
	}
	//对辅助数组的初始化完毕
	
	//动态规划的核心代码，填写一个二维数组 
	for(i = 1;i <= m;++i)
	{
		for(j = 1;j <= n;++j)
		{
			if(x[i] == y[j])
			{
				B[i][j] = B[i-1][j-1] + 1;
			}
			else if(B[i-1][j] >= B[i][j-1])
			{
				B[i][j] = B[i-1][j];
			}
			else
			{
				B[i][j] = B[i][j-1];
			}
		}
	}
	
	//找出最长公共子序列
	for(i = m,j = n;i>0 && j>0;)
	{
		if(x[i]==y[j])
		{
			i--;j--;
		}
		else if(B[i-1][j] >= B[i][j-1])
		{
			i--;
		}
		else
		{
			j--;
		}
	}
	
	return Path;
}

int main()
{
	
	vector<char> Path = LCS(x,7,y,6);
	int i;
	for(i = n-1;i >= 0;--i)
	{
		cout<<Path[i]<<" ";
	}
}
