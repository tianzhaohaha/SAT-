#include"pre-SAT.h"

int cmn(int m, int n)//��n����ѡm�������������
{
	int i = 0, j = 0, x = 1, y = 1, r = 0;
	if (m > n / 2) m = n - m;
	for (i = n; i > n - m; i--)
		x = x * i;
	for (j = 1; j <= m; j++)
		y = y * j;
	r = x / y;

return r;
}

int Number5(int a, int b, int c, int d, int e)//�����Ӧ��5λʮ������
{
	int x;
	x = 10000 * a + 1000 * b + 100 * c + 10 * d + e;

	return x;
}

int Number4(int a, int b, int c, int d)//�����Ӧ��4λʮ������
{
	int x;
	x = 1000 * a + 100 * b + 10 * c + d;

	return x;
}

int Number3(int a, int b, int c)//�����Ӧ��3λʮ������
{
	int x;
	x = 100 * a + 10 * b + c;

	return x;
}

int PW(int i, int j, int n)//����Ӷ�Ӧ�����ֵĺ���
{
	int x,k;
	x = (i - 1) * n + j;
	k = 2 * x - 1;

	return k;
}

int NW(int i, int j, int n)//����Ӷ�Ӧ�����ֵĺ���
{
	int x, k;
	x = (i - 1) * n + j;
	k = 2 * x ;

	return k;
}

bool has(NewTable b[], int n)//ѡ����ϵĺ���
{
	int flag = 0, ct = 0;
	for (int i = 1; i < n; i++)
		if (b[i].state == 1 && b[i + 1].state == 0)
		{
			b[i].state = 0, b[i + 1].state = 1;
			flag = i;
			break;
		}
	if (!flag) return 0;
	else
	{
		for (int k = flag - 1; k >= 1; k--)
			if (b[k].state) ct++;
		for (int i = 1; i <= ct; i++)
			b[i].state = 1;
		for (int i = ct + 1; i < flag; i++)
			b[i].state = 0;
		return 1;
	}
}

int Verse(int x)//�����ֶ�Ӧ�������ֺ���
{
	int y = 0;
	if (x % 2) y = x + 1;
	else y = x - 1;
	return y;
}

void Cell(SAT2 *S, int x, int* i, int* j)//�����ֶ�Ӧ�ĸ�������
{
	int w, n = S->n, y1 = 0, y2 = 0;//y��Ϊ��ʱ��������
	w = (x + 1) / 2;
	if (x <= 2 * n * n)
	{
       *i = w / n + 1;
	   *j = w % n;
	   if (!(*j)) { *j = n; *i = w / n; }
	}
	
}

int Trab(int x)//��������ֵ�ԭ�����ĺ���
{//s==0���������������CNF����ȡֵ��s==1��������������CNF
	int y = 0;
	if (x % 2) y = (x + 1) / 2;
	else y = -(x / 2);

return y;
}
