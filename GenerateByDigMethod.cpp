#include"pre-SAT.h"

bool GenerateByDigMethod(int f[][PL], int n, int level)//���ϵ��¡�������˳���ڶ�
{//levelΪ�ո����
	int i = 0, j = 0;

	//S->top = 0;//��ջ��ָ����г�ʼ�����Ա���лָ�����
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
		{
			if (!level) goto end;
			if (CheckUnique(f, n, i, j)) //�ж��Ƿ���Ψһ��
			{				
				f[i][j] = -1;//��ȥ�ø�
				level--;
				PrintPuzzle(f, n);
			}			
		}

	if (level) printf("�ⲻΨһ��\n");
	else printf("��Ψһ��");

end: return true;
}
