#include"pre-SAT.h"

bool CheckUnique(int f[][PL], int n, int r, int c)//判断是否有唯一解
{//r是行号，c是列号
	if (r == 1 && c == 1) return true;
	bool v;
	int p[PL][PL];
	int x = 0, i = 0, j = 0;
	v = !f[r][c];	

	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			p[i][j] = f[i][j];//数据备份用于反证

	p[r][c] = v;//对该处的赋值反转，进行反证
	if (solve(p, n)) return false;
	else return true;

}

bool CheckSudokuSolution(int f[][PL], int n)//判断解是否正确
{
	int i = 0, j = 0;
	int a = 0, b = 0, d = 0, s = 0;
	//a用于统计1的个数，b用于统计-1的个数，d用于统计0的个数，s用于统计相同元素的个数

//验证规则一
	{
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n - 2; j++)
			{
				if (f[i][j] != -1 && f[i][j + 1] != -1 && f[i][j + 2] != -1)
					if (f[i][j] == f[i][j + 1] && f[i][j] == f[i][j + 2] && f[i][j + 1] == f[i][j + 2])
						return false;
			}
		for (j = 1; j <= n; j++)
			for (i = 1; i <= n - 2; i++)
			{
				if (f[i][j] != -1 && f[i + 1][j] != -1 && f[i + 2][j] != -1)
					if (f[i][j] == f[i + 1][j] && f[i][j] == f[i + 2][j] && f[i + 1][j] == f[i + 2][j])
						return false;
			}
	}
	//验证规则一结束

	//验证规则二
	{
		for (i = 1; i <= n; i++)//控制行
		{
			a = b = d = 0;
			for (int c = 1; c <= n; c++)//行内遍历
			{
				if (f[i][c] != -1)
				{
					if (f[i][c]) a++;
					else d++;
				}
				else b++;
			}
			if (a > n / 2 || d > n / 2) return false;
		}

		for (i = 1; i <= n; i++)//控制列
		{
			a = b = d = 0;
			for (int c = 1; c <= n; c++)//列内遍历
			{
				if (f[c][i] != -1)
				{
					if (f[c][i]) a++;
					else d++;
				}
				else b++;
			}
			if (a > n / 2 || d > n / 2) return false;
		}
	}
	//验证规则二结束

	//验证规则三
	{
		for (i = 1; i <= n - 1; i++)//第一个选取行
		{
			s = 0;
			for (int c = i + 1; c <= n; c++)//第二个选取行
				{
					for (int d = 1; d <= n; d++)//行内遍历
						if (f[i][d] != -1 && f[c][d] != -1)
							if (f[i][d] == f[c][d]) s++;
					if (s == n) return false;
				}
		}

		for (j = 1; j <= n - 1; j++)//第一个选择列
		{
			s = 0;
			for (int d = j+1; d <= n; d++)//第二个选择列
				{
					for (int c = 1; c <= n; c++)//列内遍历
						if (f[c][j] != -1 && f[c][d] != -1)
							if (f[c][j] == f[c][d]) s++;
					if (s == n) return false;
				}
		}
	}
	//验证规则三结束

return true;
}

bool CheckSudokuSolution2(int f[][PL], int n, int x, int y, bool v)//判断解是否正确（局部）
{
	f[x][y] = v;
	int i = 0, j = 0;
	int a = 0, b = 0, d = 0, s = 0;
	//a用于统计1的个数，b用于统计-1的个数，d用于统计0的个数，s用于统计相同元素的个数

//验证规则一
	{
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n - 2; j++)
			{
				if (f[i][j] != -1 && f[i][j + 1] != -1 && f[i][j + 2] != -1)
					if (f[i][j] == f[i][j + 1] && f[i][j] == f[i][j + 2] && f[i][j + 1] == f[i][j + 2])
						return false;
			}
		for (i = 1; i <= n - 2; i++)
			for (j = 1; j <= n; j++)
			{
				if (f[i][j] != -1 && f[i + 1][j] != -1 && f[i + 2][j] != -1)
					if (f[i][j] == f[i + 1][j] && f[i][j] == f[i + 2][j] && f[i + 1][j] == f[i + 2][j])
						return false;
			}
	}
//验证规则一结束

//验证规则二
	{
		for (i = 1; i <= n; i++)
		{
			a = b = d = 0;
			for (int c = 1; c <= n; c++)
			{
				if (f[i][c] != -1)
				{
					if (f[i][c]) a++;
					else d++;
				}
				else b++;
			}
			if (a > n / 2  || d > n / 2 ) return false;
		}

		for (i = 1; i <= n; i++)
		{
			a = b = d = 0;
			for (int c = 1; c <= n; c++)
			{
				if (f[c][i] != -1)
				{
					if (f[c][i]) a++;
					else d++;
				}
				else b++;
			}
			if (a > n / 2  || d > n / 2 ) return false;
		}
	}
//验证规则二结束

//验证规则三
	{
		for (i = 1; i <= n; i++)
		{
			s = 0;
			for (int c = 1; c <= n; c++)
				if (c != i)
				{
					for (int d = 1; d <= n; d++)
						if (f[i][d] != -1 && f[c][d] != -1)
							if (f[i][d] == f[c][d]) s++;
					if (s == n) return false;
				}
		}

		for (j = 1; j <= n; j++)
		{
			s = 0;
			for (int d = 1; d <= n; d++)
				if (d != j)
				{
					for (int c = 1; c <= n; c++)
						if (f[c][j] != -1 && f[c][d] != -1)
							if (f[c][j] == f[c][d]) s++;
					if (s == n) return false;
				}
		}
	}
//验证规则三结束

	return true;
}
