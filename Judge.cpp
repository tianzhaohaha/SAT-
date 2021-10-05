#include"pre-SAT.h"

int JudgeClause(SAT* S, int i)//判断某个子句是否可满足
{
	if (S->list[i].Unsat == S->list[i].VariateNum) return false;
	if (S->list[i].Sat >= 1) return true;
	else return -1;
}

bool JudgeSATEmpty(SAT* S)//判断整个子句集是否为空
{
	int i;
	for (i = 1; i <= S->ClauseNum; i++)
	{	
		if (S->list[i].s != 0)
			return false;
	}
	return true;
}

bool JudgeListEmpty(SAT* S)//判断整个子句集当中是否存在空子句
{
	int i;
	for (i = 1; i <= S->ClauseNum; i++)
	{
		
		if (S->list[i].VariateNum == S->list[i].Unsat && S->list[i].s)
			return true;
	}
return false;
}


bool JudgeSATEmpty2(SAT2* S)//判断整个子句集是否为空gai
{
	int i;
	for (i = 1; i <= S->ClauseNum; i++)
	{
		if (S->list[i].s != 0)
			return false;
	}
	return true;
}

bool JudgeListEmpty2(SAT2* S)//判断整个子句集当中是否存在空子句gai
{
	int i;
	for (i = 1; i <= S->ClauseNum; i++)
	{

		if (S->list[i].VariateNum == S->list[i].Unsat && S->list[i].s)
			return true;
	}
	return false;
}
