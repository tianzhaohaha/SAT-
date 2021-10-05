#include"pre-SAT.h"

typedef struct stack
{
	int line;//该位置的行号
	int row;//该位置元素的列号
	int value;//该位置的赋值
}stack;//用于DPLL求解数独时使用的堆栈（三元组表）

Status push(stack s[], int *p, int i, int j, int v);//入栈函数
Status pop(stack s[], int* p);//出栈函数

bool solve(int (*f)[PL], int n)//用DPLL数独求解函数（挖洞专用）
{//试探赋值的规则：先0后1	
	stack st[PL * PL + 1];
	int stp = 0, flag = 1;//stp栈顶指针，flag表示是否已经有一次入栈
	int i = 1, j = 1;//初始化入栈单元的坐标
	
	while (i <= n)//当格子没有全部遍历到的时候执行DPLL过程
	{		
		if (f[i][j] == -1)//本格未填
		{
			push(st, &stp, i, j, 0);//入栈
			flag = 0;
			f[i][j] = 0;
			while (!CheckSudokuSolution(f, n))
			{
				f[st[stp - 1].line][st[stp - 1].row] = 1;
				st[stp - 1].value = 1;
				if (CheckSudokuSolution(f, n)) break;
				while (st[stp - 1].value == 1)
				{
					f[st[stp - 1].line][st[stp - 1].row] = -1;
					pop(st, &stp);
					if (!stp) return false;					
				}//小循环结束				
			}//中循环结束		    
		}
		if (!flag) 
			if (j == n) { i++; j = 1; }
			else { j++; }
		else 
			if (j == n) { i = st[stp - 1].line + 1; j = 1; }
			else { j = st[stp - 1].row + 1; }
	}//大循环结束
	if (!stp)return false;
	else return true;
}


Status push(stack s[], int* p, int i, int j, int v)//入栈函数
{
	int a = *p;
	s[a].line = i;
	s[a].row = j;
	s[a].value = v;
	(*p)++;

return OK;
}

Status pop(stack s[], int* p)//出栈函数
{
	int a = *p;
	s[a].line = 0;
	s[a].row = 0;
	s[a].value = -1;
	(*p)--;

return OK;
}


bool r1(int (*f)[PL], int n, int i, int j, bool v)//验证规则1是否满足
{
	f[i][j] = v;
	if(j > 2 && j <= n)
	  if (f[i][j - 2] != -1 && f[i][j - 1] != -1 && f[i][j] != -1)
		if (f[i][j - 2] == f[i][j - 1] == f[i][j])
			return false;

	if (j > 1 && j <= n - 1)
		if (f[i][j - 1] != -1 && f[i][j] != -1 && f[i][j + 1] != -1)
			if (f[i][j - 1] == f[i][j] == f[i][j + 1])
				return false;

	if (j <= n - 2)
		if (f[i][j] != -1 && f[i][j + 1] != -1 && f[i][j + 2] != -1)
			if (f[i][j] == f[i][j + 1] == f[i][j + 2])
				return false;

	if (i > 2 && i <= n)
		if (f[i - 2][j] != -1 && f[i-1][j] != -1 && f[i][j] != -1)
			if (f[i - 2][j] == f[i - 1][j] == f[i][j])
				return false;

	if (i > 1 && i <= n - 1)
		if (f[i - 1][j] != -1 && f[i][j] != -1 && f[i + 1][j] != -1)
			if (f[i - 1][j] == f[i][j] == f[i + 1][j])
				return false;

	if (i <= n - 2)
		if (f[i][j] != -1 && f[i + 1][j] != -1 && f[i + 2][j] != -1)
			if (f[i][j] == f[i + 1][j] == f[i + 2][j])
				return false;

return true;
}

bool r2(int (*f)[PL], int n, int i, int j, bool v)//验证规则2是否满足
{
	f[i][j] = v;
	int a = 0, d = 0, s = 1;
	for(int c=1;c<=n;c++)
		if (f[i][c] != -1)
		{
			if (f[i][c]) a++;
			else d++;
		}
		else {
			s = 0;
			f;
			break;
		}
	if (!s) return true;
	else if (a != d) return false;

	s = 1;
	a = d = 0;
	for (int c = 1; c <= n; c++)
		if (f[c][j] != -1)
		{
			if (f[c][j]) a++;
			else d++;
		}
		else {
			s = 0;
			break;
		}
	if (!s) return true;
	else if (a != d) return false;
}

bool r3(int (*f)[PL], int n, int i, int j, bool v)//验证规则3是否满足
{
	f[i][j] = v;
	int a = 0,s = 0;
	for (int c = 1; c <= n; c++)
		if (c != i)
		{
			for (int d = 1; d <= n; d++)
				if (f[i][d] != -1 && f[c][d] != -1)
				   if (f[i][d] == f[c][d]) s++;
			if (s == n) return false;
		}

	for (int d = 1; d <= n; d++)
		if (d != j)
		{
			for (int c = 1; c <= n; c++)
				if (f[c][j] != -1 && f[c][d] != -1)
					if (f[c][j] == f[c][d]) s++;
			if (s == n) return false;
		}

return true;
}


