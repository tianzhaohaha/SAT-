#include"pre-SAT.h"

void question(int* m);//��һ�¡��Ƿ�Ҫ�������Ƿ���Ҫ��ʾ��ǰ��д������Ƿ���Ҫ��ʾ������ʾ��
bool select(int* i, int* j, int *v);//�����������ѡ����
bool FullPuzzleOrnot(int f[][PL], int n);//�鿴�����Ƿ��Ѿ�����

Status PlayPuzzle(int f[][PL],int puzzle2[][PL], int n)//���õ�������ˣ����
{
	int p[PL][PL];//����Ϸ����Ϸ����
	int i = 0, j = 0, k = 0, m = 0, a = 0, b = 0, v = 0;
	CopyPuzzle(f, p, n);//���������Ա�֤��Ϸ����	
	
begin:	while (!FullPuzzleOrnot(p, n))
	    {
		    if (select(&i, &j, &v))
			    if (p[i][j] == -1) p[i][j] = v;
			    else { printf("�Ƿ�����!\n");  goto begin; }
		    else { printf("�Ƿ�����!\n"); goto begin;	}
		    question(&m);
			switch (m)
			{
			   case 1:  PrintPuzzle(p, n);  break;
			   case 2:  return ERROR; break;
			   case 0:  break;
			   default:  printf("�Ƿ�����!\n");  question(&m); break;
			}
	     }
       
      if(puzzle2[i][j]==p[i][j]) return OK;
	  else return ERROR;

}

void question(int* m)//��һ�¡��Ƿ�Ҫ�������Ƿ���Ҫ��ʾ��ǰ��д������Ƿ���Ҫ��ʾ������ʾ��
{
	int t;
	printf("1.�����2.�𰸣�0.����\n");
	t = scanf("%d", m);
}

bool select(int* i, int* j, int* v)//�����������ѡ����
{
	printf("�������У�������ֵ.\n");
	int a = scanf("%d%d%d", i, j, v);
	if (*v == 1 || *v == 0) return true;
	else return false;
}

bool FullPuzzleOrnot(int f[][PL], int n)//�鿴�����Ƿ��Ѿ�����
{
	for(int i=1;i<=n;i++)
		for (int j = 1; j <= n; j++)
			if (f[i][j] == -1) return false;		
return true;
}



