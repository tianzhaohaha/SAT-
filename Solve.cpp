#include"pre-SAT.h"

Status Solve1(SAT* S, FILE* in, int *t)//基于DPLL的SAT求解器（优化后）
{
	int x, flag = 1;
	int i;
	int t1 = 0, t2 = 0;
	Input(in,S);
    t1 = clock();
	while (S->top != 0 || flag != 0)//当栈不为空时执行DPLL过程
	{
		//printf("Solve OK!\n");
        deletec(S);
		if (JudgeSATEmpty(S))
		{			
			//PrintClause(S);
			t2 = clock();
			*t = t2 - t1;
			printf("\n耗费时间： %dms.\n", t2 - t1);
			return true;
		}//子句集为空时认定可满足
		else if (JudgeListEmpty(S))//子句集不为空，且存在空子句
		{
			if (EmptyStack(S) == 0 || EmptyStack(S) == -1)//栈状态为0或-1，即无法回溯
			{
				//PrintClause(S);
				t2 = clock();
				*t = t2 - t1;
				printf("\n耗费时间： %dms.\n", t2 - t1);
				return false;
			}//整个SAT不可满足
			if (EmptyStack(S) == 1)//栈状态为1，即仍可回溯
			{
				//printf("OutStack START!\n");
				OutStack(S);//执行出栈操作
				//printf("OutStack END!\n");
				if (S->top)
				{
					ReCoverValue(S, S->stack[S->top - 1].Variate);//恢复栈顶元素赋值
					ReCopyValue(S, S->stack[S->top - 1].Variate);//执行反转赋值操作
					S->stack[S->top - 1].diverse = 1;//表示该变量的正负文字均已反转赋值
				}
				else
				{
					//PrintClause(S);
					t2 = clock();
					*t = t2 - t1;
					printf("\n耗费时间： %dms.\n", t2 - t1);
					return false;
				}
			}
		}
		     else//子句集不为空，且不存在空子句
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


bool Solve2(SAT2* S)//基于DPLL与SAT求解数独函数
{
	int x, flag = 1;
	int i;
	while (S->top != 0 || flag != 0)//当栈不为空时执行DPLL过程
	{
		//PrintClause2(S);
		DeleteClause2(S);
		//PrintClause2(S);
		if (JudgeSATEmpty2(S))
		{
			//PrintPuzzle(S);
			//printf("\nSAT is TRUE!\n");
			return true;
		}//子句集为空时认定可满足
		else if (JudgeListEmpty2(S))//子句集不为空，且存在空子句
		{

			if (EmptyStack2(S) == 0 || EmptyStack2(S) == -1)//栈状态为0或-1，即无法回溯
			{
				//printf("\nSAT is FALSE!\n");
				return false;
			}//整个SAT不可满足
			if (EmptyStack2(S) == 1)//栈状态为1，即仍可回溯
			{
				OutStack2(S);//执行出栈操作
				if (S->top)
				{
					ReCopyValue2(S, S->stack[S->top - 1].Variate);//执行反转赋值操作
					S->stack[S->top - 1].diverse = 1;//表示该变量的正负文字均已反转赋值
				}
				else
				{
					//printf("\nSAT is FALSE!\n");
					return false;
				}
			}
		}
		else//子句集不为空，且不存在空子句
		{
			x = SelectVariate2(S);
			CopyValue2(S, x);
		}
		flag = 0;

	}
}


Status Solve3(SAT* S, FILE* in, int* t)//基于DPLL的SAT求解器主支函数（优化前）
{
	int x, flag = 1;
	int i;
	int t1 = 0, t2 = 0;
	t1 = clock();
	Input(in, S);
	while (S->top != 0 || flag != 0)//当栈不为空时执行DPLL过程
	{
		//printf("Solve OK!\n");
        deletec(S);
		if (JudgeSATEmpty(S))
		{
			//PrintClause(S);
			t2 = clock();
			*t = t2 - t1;
			printf("\n耗费时间： %dms.\n", t2 - t1);
			return true;
		}//子句集为空时认定可满足
		else if (JudgeListEmpty(S))//子句集不为空，且存在空子句
		{
			if (EmptyStack(S) == 0 || EmptyStack(S) == -1)//栈状态为0或-1，即无法回溯
			{
				//PrintClause(S);
				t2 = clock();
				*t = t2 - t1;
				printf("\n耗费时间： %dms.\n", t2 - t1);
				return false;
			}//整个SAT不可满足
			if (EmptyStack(S) == 1)//栈状态为1，即仍可回溯
			{
				//printf("OutStack START!\n");
				OutStack(S);//执行出栈操作
				//printf("OutStack END!\n");
				if (S->top)
				{
					ReCoverValue(S, S->stack[S->top - 1].Variate);//恢复栈顶元素赋值
					ReCopyValue(S, S->stack[S->top - 1].Variate);//执行反转赋值操作
					S->stack[S->top - 1].diverse = 1;//表示该变量的正负文字均已反转赋值
				}
				else
				{
					//PrintClause(S);
					t2 = clock();
					*t = t2 - t1;
					printf("\n耗费时间 %dms.\n", t2 - t1);
					return false;
				}
			}
		}
		else//子句集不为空，且不存在空子句
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


