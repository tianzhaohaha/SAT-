#include"pre-SAT.h"

Status PuzzleInnital(SAT2* S)//初始化数独的函数，n为阶数
{//该函数不涉及文件操作
	int i = 0, j = 0, k = 0;
	//i控制大循环，j控制小循环，k控制最内层循环（或为计数器）;
	int a = 0, b = 0;
	//a表示规则一的子句个数，b 表示规则二的子句个数
	int t, m, n = S->n;
	Node* l = NULL, * lnode = NULL;//l为动态指针，lnode为静态指针
	Word* r = NULL;
	a = 2 * (n - 2) * n * 2;
	b = cmn(n/2 + 1, n) * 2 * n * 2;

	Iniate2(&S);
    R1(S, 1, a);
    R2(S, a + 1, a + b);
    R3(S, a + b + 1);
	
	for (i = 1; i <= S->ClauseNum; i++)	if (S->list[i].first) k++;//重新统计子句数目
	for (i = 1; i < MAXNUM; i += 2) if (S->relist[i].first || S->relist[i + 1].first) j++;//统计变元数
	S->ClauseNum = k;
	S->VariateNum = j;
	PrintPuzToCNF(S);

return OK;
}