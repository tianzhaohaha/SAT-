#include"pre-SAT.h"

Status PrintClause(SAT* S)//打印子句集
{
	int i = 0;
	Node* t = NULL;
	//for (i = 1; i <= S->ClauseNum; i++)
	//{
	//	printf("%d-%d-%d-%d-%d-", i, S->list[i].s, S->list[i].VariateNum, /*S->list[i].UnsignedNum,*/ S->list[i].Sat, S->list[i].Unsat);
	//	for (t = S->list[i].first; t != NULL; t = t->next)
	//	{
	//		printf("-> %d %d ", t->VariateValue, t->Variate);
	//	}
	//	printf(" NULL \n");
	//}
	return OK;
}

Status PrintWord(SAT* S, FILE* out, int s, int time)//打印关联变量链表
{
	int i = 1, n = 2 * S->VariateNum, k = 0, x = 0;
	Word* r = NULL;
    fprintf(out, "s ");
	fprintf(out, "%d\n", s);
    fprintf(out, "v ");
	if (s != -1)
	  while (i <= n)
	  {

          k = S->relist[i].VariateValue;
		  if (k == 1 || k == -1)//输出取值为1或-1的变量对应的原变量
		  {
			x = Trab(i);//求出对应的原变量
			fprintf(out, "%d ", x);
		  }
		  if (k == -1) i += 2;
		  else i++;
	  }
    fprintf(out, "\nt ");
	fprintf(out, "%d", time);
    fprintf(out, " ms\n\n");

return OK;
}

Status PrintPuzzle(int f[][PL], int n)
{
	for (int i = 1; i <= n; i++)
	{
		printf("\n");
		for (int j = 1; j <= n; j++)
			printf("%2d ", f[i][j]);
	}
	printf("\n\n");
return OK;
}

Status PrintPuzToCNF(SAT2* S)//打印由数独归约生成的CNF子句集（文件在内部生成）
{
	int i = 0, x = 0, j = 0;
	Node* t = NULL;
	FILE* out;
	out = fopen("Puzzle.cnf", "w");
	fprintf(out, "p cnf %d %d\n", S->VariateNum, S->ClauseNum);
	for (i = 1; i <= S->ClauseNum; i++)
	{
		for (t = S->list[i].first; t != NULL; t = t->next)
		{
			j = t->Variate;
			x = Trab(j);
			fprintf(out, "%d ", x);
		}
		fprintf(out, "\n");
	}
	fclose(out);
return OK;
}

Status CopyPuzzle(int f[][PL], int b[][PL], int n)//复制数独棋盘
{
	for(int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			b[i][j] = f[i][j];
		}
return OK;
}