#include"pre-SAT.h"

int bianliangselect(SAT* S)//决策下一分支赋值变量（选择第一行第一个）
{
	SAT* s = S;
	int i = 0, j = 0, k = 0, n = 0, x = 0, m = 0, p = 0;
	Node* t = NULL;
	Word* r = NULL;
    
	for (i = 1; i <= S->ClauseNum; i++)
	{
		if(S->list[i].s)
			for (t = S->list[i].first; t != NULL; t = t->next)
			{
				if (t->VariateValue == -1)
				{
					x = t->Variate;
					InStack(S, x, 1);//以决策变量入栈
					//printf("%d is Selected in clause %d !\n", x, i);
					return x;
				}
			}
	}

return x;
}


int SelectVariate2(SAT2* S)//决策下一分支赋值变量gai
{
	SAT2* s = S;
	int i = 0, j = 0, k = 0, n = 0, x = 0, m = 0, p = 0;
	Node* t = NULL;
	Word* r = NULL;

	for (i = 1; i <= S->ClauseNum; i++)
	{
		if (S->list[i].s)
			for (t = S->list[i].first; t != NULL; t = t->next)
			{
				if (t->VariateValue == -1)
				{
					x = t->Variate;
					InStack2(S, x, 1);//以决策变量入栈
					//printf("%d is Selected in clause %d !\n", x, i);
					return x;
				}
			}
	}

	return x;

}

int SelectVariate3(SAT* S)//决策下一分支赋值变量（选择第一个未赋值变量）
{
	SAT* s = S;
	int i = 0, j = 0, k = 0, n = 2 * S->VariateNum, x = 0, m = 0, p = 0;
	Node* t = NULL;
	Word* r = NULL;

	for (i = 1; i <= n; i+=2)
	{
		if (S->relist[i].VariateValue == -1)
		{
			x = i;
			InStack(S, x, 1);//以决策变量入栈
			return x;
		}
			
	}

}

int danzijuselect(SAT* S)//寻找单子句，返回单子句的编号
{
    int i = 0, x = 0;
    Node* t = NULL, * r = NULL;
    for (i = 1; i <= S->ClauseNum; i++)
        if (S->list[i].s && (S->list[i].VariateNum - 1) == S->list[i].Unsat)//只剩下一个可赋值的变量
        {
            for (t = S->list[i].first; t != NULL; t = t->next)
            {
                if (t->VariateValue == -1)// 此变量未赋值
                {
                    x = t->Variate;
                    InStack(S, x, 0);//以非决策变量入栈
                    //printf("\n%d Selected in Clause %d!\n", x, i);
                    return x;
                }
            }
        }

    return false;
}

int SelectClause2(SAT2* S)//寻找单子句，返回单子句的编号
{
    int i = 0, x = 0;
    Node* t = NULL, * r = NULL;
    for (i = 1; i <= S->ClauseNum; i++)
        if (S->list[i].s && (S->list[i].VariateNum - 1) == S->list[i].Unsat)
        {
            for (t = S->list[i].first; t != NULL; t = t->next)
            {
                if (t->VariateValue == -1)
                {
                    x = t->Variate;
                    InStack2(S, x, 0);//以非决策变量入栈
                    //printf("\n%d Selected in Clause %d!\n", x, i);
                    return x;
                }
            }
        }

    return false;
}