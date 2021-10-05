#include"pre-SAT.h"

bool CheckUnique(int f[][PL], int n, int r, int c)//�ж��Ƿ���Ψһ��
{//r���кţ�c���к�
	if (r == 1 && c == 1) return true;
	bool v;
	int p[PL][PL];
	int x = 0, i = 0, j = 0;
	v = !f[r][c];	

	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			p[i][j] = f[i][j];//���ݱ������ڷ�֤

	p[r][c] = v;//�Ըô��ĸ�ֵ��ת�����з�֤
	if (solve(p, n)) return false;
	else return true;

}

bool CheckSudokuSolution(int f[][PL], int n)//�жϽ��Ƿ���ȷ
{
	int i = 0, j = 0;
	int a = 0, b = 0, d = 0, s = 0;
	//a����ͳ��1�ĸ�����b����ͳ��-1�ĸ�����d����ͳ��0�ĸ�����s����ͳ����ͬԪ�صĸ���

//��֤����һ
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
	//��֤����һ����

	//��֤�����
	{
		for (i = 1; i <= n; i++)//������
		{
			a = b = d = 0;
			for (int c = 1; c <= n; c++)//���ڱ���
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

		for (i = 1; i <= n; i++)//������
		{
			a = b = d = 0;
			for (int c = 1; c <= n; c++)//���ڱ���
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
	//��֤���������

	//��֤������
	{
		for (i = 1; i <= n - 1; i++)//��һ��ѡȡ��
		{
			s = 0;
			for (int c = i + 1; c <= n; c++)//�ڶ���ѡȡ��
				{
					for (int d = 1; d <= n; d++)//���ڱ���
						if (f[i][d] != -1 && f[c][d] != -1)
							if (f[i][d] == f[c][d]) s++;
					if (s == n) return false;
				}
		}

		for (j = 1; j <= n - 1; j++)//��һ��ѡ����
		{
			s = 0;
			for (int d = j+1; d <= n; d++)//�ڶ���ѡ����
				{
					for (int c = 1; c <= n; c++)//���ڱ���
						if (f[c][j] != -1 && f[c][d] != -1)
							if (f[c][j] == f[c][d]) s++;
					if (s == n) return false;
				}
		}
	}
	//��֤����������

return true;
}

bool CheckSudokuSolution2(int f[][PL], int n, int x, int y, bool v)//�жϽ��Ƿ���ȷ���ֲ���
{
	f[x][y] = v;
	int i = 0, j = 0;
	int a = 0, b = 0, d = 0, s = 0;
	//a����ͳ��1�ĸ�����b����ͳ��-1�ĸ�����d����ͳ��0�ĸ�����s����ͳ����ͬԪ�صĸ���

//��֤����һ
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
//��֤����һ����

//��֤�����
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
//��֤���������

//��֤������
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
//��֤����������

	return true;
}
