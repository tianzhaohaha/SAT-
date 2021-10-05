#include"pre-SAT.h"

Status ReCopyValue(SAT* S, int x)////反转赋值
{//反转赋值规则：对该文字的赋值为1;其逆文字的赋值为0;且假定之前的值已经恢复
	int j = 0, y = 0, k = 0;
	Word* t1, * t2;//t1是指向本文字的指针，t2是指向逆文字的指针
	Node* r;

	y = Verse(x);
	S->relist[x].VariateValue = 1;
	S->relist[y].VariateValue = 0;

	for (t1 = S->relist[x].first; t1 != NULL; t1 = t1->next)
	{
		j = t1->ClauseNum;
		if (S->list[j].s)
		{
			for (r = S->list[j].first; r != NULL; r = r->next)
			{
				k = r->Variate;
				if (k == x && r->VariateValue == -1)
				{
					r->VariateValue = 1;
					S->list[j].Sat++;
					//S->list[j].UnsignedNum--;
					S->list[j].s = 0;
					break;
				}
			}
			
		}
	}

	for (t2 = S->relist[y].first; t2 != NULL; t2 = t2->next)
	{
		j = t2->ClauseNum;
		if (S->list[j].s)
			for (r = S->list[j].first; r != NULL; r = r->next)
			{
				if (r->Variate == y && r->VariateValue == -1)
				{
					r->VariateValue = 0;
					S->list[j].Unsat++;
					//S->list[j].UnsignedNum--;
					break;
				}
			}
	}

	return OK;
}


Status ReCopyValue2(SAT2* S, int x)//反转赋值
{//反转赋值规则：对该文字的赋值为1;其逆文字的赋值为0;且假定之前的值已经恢复
	int a, b;//a为该文字赋值，b为其逆文字赋值
	int j, w, c, k, n = S->n, y = 0;
	Word* t1, * t2;//t1是指向本文字的指针，t2是指向逆文字的指针
	Node* r;

	if (x <= 2 * n * n)
	{
		Cell(S, x, &k, &c);
		if (x % 2)  S->puzzle[k][c] = 1;
		else S->puzzle[k][c] = 0;
	}

	y = Verse(x);
	S->relist[x].VariateValue = 1;
	S->relist[y].VariateValue = 0;

	for (t1 = S->relist[x].first; t1 != NULL; t1 = t1->next)
	{
		j = t1->ClauseNum;
		if (S->list[j].s)
		{
			for (r = S->list[j].first; r != NULL; r = r->next)
			{
				k = r->Variate;
				if (k == x && r->VariateValue == -1)
				{
					r->VariateValue = 1;
					S->list[j].Sat++;
					//S->list[j].UnsignedNum--;
					S->list[j].s = 0;
					break;
				}
			}

		}
	}

	for (t2 = S->relist[y].first; t2 != NULL; t2 = t2->next)
	{
		j = t2->ClauseNum;
		if (S->list[j].s)
			for (r = S->list[j].first; r != NULL; r = r->next)
			{
				if (r->Variate == y && r->VariateValue == -1)
				{
					r->VariateValue = 0;
					S->list[j].Unsat++;
					//S->list[j].UnsignedNum--;
					break;
				}
			}
	}

	return OK;
}
