#include"pre-SAT.h"

Status Solve1(SAT* S, FILE* in, int *t)//����DPLL��SAT��������Ż���
{
	int x, flag = 1;
	int i;
	int t1 = 0, t2 = 0;
	Input(in,S);
    t1 = clock();
	while (S->top != 0 || flag != 0)//��ջ��Ϊ��ʱִ��DPLL����
	{
		//printf("Solve OK!\n");
        deletec(S);
		if (JudgeSATEmpty(S))
		{			
			//PrintClause(S);
			t2 = clock();
			*t = t2 - t1;
			printf("\n�ķ�ʱ�䣺 %dms.\n", t2 - t1);
			return true;
		}//�Ӿ伯Ϊ��ʱ�϶�������
		else if (JudgeListEmpty(S))//�Ӿ伯��Ϊ�գ��Ҵ��ڿ��Ӿ�
		{
			if (EmptyStack(S) == 0 || EmptyStack(S) == -1)//ջ״̬Ϊ0��-1�����޷�����
			{
				//PrintClause(S);
				t2 = clock();
				*t = t2 - t1;
				printf("\n�ķ�ʱ�䣺 %dms.\n", t2 - t1);
				return false;
			}//����SAT��������
			if (EmptyStack(S) == 1)//ջ״̬Ϊ1�����Կɻ���
			{
				//printf("OutStack START!\n");
				OutStack(S);//ִ�г�ջ����
				//printf("OutStack END!\n");
				if (S->top)
				{
					ReCoverValue(S, S->stack[S->top - 1].Variate);//�ָ�ջ��Ԫ�ظ�ֵ
					ReCopyValue(S, S->stack[S->top - 1].Variate);//ִ�з�ת��ֵ����
					S->stack[S->top - 1].diverse = 1;//��ʾ�ñ������������־��ѷ�ת��ֵ
				}
				else
				{
					//PrintClause(S);
					t2 = clock();
					*t = t2 - t1;
					printf("\n�ķ�ʱ�䣺 %dms.\n", t2 - t1);
					return false;
				}
			}
		}
		     else//�Ӿ伯��Ϊ�գ��Ҳ����ڿ��Ӿ�
		     {
			   x = bianliangselect(S);
			   CopyValue(S, x);
		     }
		flag = 0;
		t2 = clock();
		*t = t2 - t1;
		if ((t2 - t1) / 2000 > SET_TIME) return -1; 
	}

}


bool Solve2(SAT2* S)//����DPLL��SAT�����������
{
	int x, flag = 1;
	int i;
	while (S->top != 0 || flag != 0)//��ջ��Ϊ��ʱִ��DPLL����
	{
		//PrintClause2(S);
		DeleteClause2(S);
		//PrintClause2(S);
		if (JudgeSATEmpty2(S))
		{
			//PrintPuzzle(S);
			//printf("\nSAT is TRUE!\n");
			return true;
		}//�Ӿ伯Ϊ��ʱ�϶�������
		else if (JudgeListEmpty2(S))//�Ӿ伯��Ϊ�գ��Ҵ��ڿ��Ӿ�
		{

			if (EmptyStack2(S) == 0 || EmptyStack2(S) == -1)//ջ״̬Ϊ0��-1�����޷�����
			{
				//printf("\nSAT is FALSE!\n");
				return false;
			}//����SAT��������
			if (EmptyStack2(S) == 1)//ջ״̬Ϊ1�����Կɻ���
			{
				OutStack2(S);//ִ�г�ջ����
				if (S->top)
				{
					ReCopyValue2(S, S->stack[S->top - 1].Variate);//ִ�з�ת��ֵ����
					S->stack[S->top - 1].diverse = 1;//��ʾ�ñ������������־��ѷ�ת��ֵ
				}
				else
				{
					//printf("\nSAT is FALSE!\n");
					return false;
				}
			}
		}
		else//�Ӿ伯��Ϊ�գ��Ҳ����ڿ��Ӿ�
		{
			x = SelectVariate2(S);
			CopyValue2(S, x);
		}
		flag = 0;

	}
}


Status Solve3(SAT* S, FILE* in, int* t)//����DPLL��SAT�������֧�������Ż�ǰ��
{
	int x, flag = 1;
	int i;
	int t1 = 0, t2 = 0;
	t1 = clock();
	Input(in, S);
	while (S->top != 0 || flag != 0)//��ջ��Ϊ��ʱִ��DPLL����
	{
		//printf("Solve OK!\n");
        deletec(S);
		if (JudgeSATEmpty(S))
		{
			//PrintClause(S);
			t2 = clock();
			*t = t2 - t1;
			printf("\n�ķ�ʱ�䣺 %dms.\n", t2 - t1);
			return true;
		}//�Ӿ伯Ϊ��ʱ�϶�������
		else if (JudgeListEmpty(S))//�Ӿ伯��Ϊ�գ��Ҵ��ڿ��Ӿ�
		{
			if (EmptyStack(S) == 0 || EmptyStack(S) == -1)//ջ״̬Ϊ0��-1�����޷�����
			{
				//PrintClause(S);
				t2 = clock();
				*t = t2 - t1;
				printf("\n�ķ�ʱ�䣺 %dms.\n", t2 - t1);
				return false;
			}//����SAT��������
			if (EmptyStack(S) == 1)//ջ״̬Ϊ1�����Կɻ���
			{
				//printf("OutStack START!\n");
				OutStack(S);//ִ�г�ջ����
				//printf("OutStack END!\n");
				if (S->top)
				{
					ReCoverValue(S, S->stack[S->top - 1].Variate);//�ָ�ջ��Ԫ�ظ�ֵ
					ReCopyValue(S, S->stack[S->top - 1].Variate);//ִ�з�ת��ֵ����
					S->stack[S->top - 1].diverse = 1;//��ʾ�ñ������������־��ѷ�ת��ֵ
				}
				else
				{
					//PrintClause(S);
					t2 = clock();
					*t = t2 - t1;
					printf("\n�ķ�ʱ�� %dms.\n", t2 - t1);
					return false;
				}
			}
		}
		else//�Ӿ伯��Ϊ�գ��Ҳ����ڿ��Ӿ�
		{
			x = SelectVariate3(S);
			CopyValue(S, x);
		}
		flag = 0;
		t2 = clock();
		*t = t2 - t1;
		if ((t2 - t1) / 2000 > SET_TIME) return -1;
	}

}


