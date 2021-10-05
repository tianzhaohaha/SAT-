#include"pre-SAT.h"

int JudgeClause(SAT* S, int i)//�ж�ĳ���Ӿ��Ƿ������
{
	if (S->list[i].Unsat == S->list[i].VariateNum) return false;
	if (S->list[i].Sat >= 1) return true;
	else return -1;
}

bool JudgeSATEmpty(SAT* S)//�ж������Ӿ伯�Ƿ�Ϊ��
{
	int i;
	for (i = 1; i <= S->ClauseNum; i++)
	{	
		if (S->list[i].s != 0)
			return false;
	}
	return true;
}

bool JudgeListEmpty(SAT* S)//�ж������Ӿ伯�����Ƿ���ڿ��Ӿ�
{
	int i;
	for (i = 1; i <= S->ClauseNum; i++)
	{
		
		if (S->list[i].VariateNum == S->list[i].Unsat && S->list[i].s)
			return true;
	}
return false;
}


bool JudgeSATEmpty2(SAT2* S)//�ж������Ӿ伯�Ƿ�Ϊ��gai
{
	int i;
	for (i = 1; i <= S->ClauseNum; i++)
	{
		if (S->list[i].s != 0)
			return false;
	}
	return true;
}

bool JudgeListEmpty2(SAT2* S)//�ж������Ӿ伯�����Ƿ���ڿ��Ӿ�gai
{
	int i;
	for (i = 1; i <= S->ClauseNum; i++)
	{

		if (S->list[i].VariateNum == S->list[i].Unsat && S->list[i].s)
			return true;
	}
	return false;
}
