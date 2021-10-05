#include"pre-SAT.h"

Status ReCoverValue(SAT* S, int x)//仅对文字的链表进行恢复赋值（也可对CNF进行处理）
{//恢复赋值规则:无论子句是否消隐都需要遍历;若该变量的赋值不为-1,则进行恢复
	int y, j = 0;//x用于存储该文字，y用于存储其逆文字
	Word* t1, * t2;//t1是指向本文字的指针，t2是指向逆文字的指针
	Node* r;
	y = Verse(x);
	for (t1 = S->relist[x].first; t1 != NULL; t1 = t1->next)
	{
		j = t1->ClauseNum;
		for (r = S->list[j].first; r != NULL; r = r->next)
		{
			if (r->Variate == x && r->VariateValue != -1)
			{
				r->VariateValue = -1;
				if (S->relist[x].VariateValue == 1)
				{
					S->list[j].Sat--;
					S->list[j].s = 1;
				}
				else
				{
					S->list[j].Unsat--;
					//S->list[j].UnsignedNum++;
				}
				break;
			}
		}
	}

	for (t2 = S->relist[y].first; t2 != NULL; t2 = t2->next)
	{
		j = t2->ClauseNum;
		for (r = S->list[j].first; r != NULL; r = r->next)
		{
			if (r->Variate == y && r->VariateValue != -1)
			{
				r->VariateValue = -1;
				if (S->relist[y].VariateValue == 1)
				{
					S->list[j].Sat--;
					S->list[j].s = 1;
				}
				else
				{
					S->list[j].Unsat--;
					//S->list[j].UnsignedNum++;
				}
				break;
			}
		}
	}

	S->relist[x].VariateValue = -1;
	S->relist[y].VariateValue = -1;

	return OK;
}

Status ReCoverValue2(SAT2* S, int x)//仅对文字的链表进行恢复赋值（对数独进行处理）
{//恢复赋值规则:无论子句是否消隐都需要遍历;若该变量的赋值不为-1,则进行恢复
	int y, j = 0, w, k, c, n = S->n;//x用于存储该文字，y用于存储其逆文字
	Word* t1, * t2;//t1是指向本文字的指针，t2是指向逆文字的指针
	Node* r;
	y = Verse(x);

	if (x <= 2 * n * n) { Cell(S, x, &k, &c); S->puzzle[k][c] = -1; }

	for (t1 = S->relist[x].first; t1 != NULL; t1 = t1->next)
	{
		j = t1->ClauseNum;
		for (r = S->list[j].first; r != NULL; r = r->next)
		{
			if (r->Variate == x && r->VariateValue != -1)
			{
				r->VariateValue = -1;
				if (S->relist[x].VariateValue == 1)
				{
					S->list[j].Sat--;
					S->list[j].s = 1;
				}
				else
				{
					S->list[j].Unsat--;
					//S->list[j].UnsignedNum++;
				}
				break;
			}
		}
	}

	for (t2 = S->relist[y].first; t2 != NULL; t2 = t2->next)
	{
		j = t2->ClauseNum;
		for (r = S->list[j].first; r != NULL; r = r->next)
		{
			if (r->Variate == y && r->VariateValue != -1)
			{
				r->VariateValue = -1;
				if (S->relist[y].VariateValue == 1)
				{
					S->list[j].Sat--;
					S->list[j].s = 1;
				}
				else
				{
					S->list[j].Unsat--;
					//S->list[j].UnsignedNum++;
				}
				break;
			}
		}
	}

	S->relist[x].VariateValue = -1;
	S->relist[y].VariateValue = -1;

	return OK;
}

Status NewCopyValue(SAT2* S, int i, int j, bool v)//对数独中的该处进行赋值操作
{
	int a, b;//a为该文字赋值，b为其逆文字赋值
	int x, w, k, c, n = S->n, y = 0;
	bool value;
	Word* t1, * t2;//t1是指向本文字的指针，t2是指向逆文字的指针
	Node* r;

	S->puzzle[i][j] = v;
	x = ((i - 1) * n + j) * 2 - 1;
	y = Verse(x);
	S->relist[x].VariateValue = v;
	S->relist[y].VariateValue = !v;
	for (t1 = S->relist[x].first; t1 != NULL; t1 = t1->next)
	{
		j = t1->ClauseNum;
		if (S->list[j].s)
			for (r = S->list[j].first; r != NULL; r = r->next)
			{
				if (r->Variate == x && r->VariateValue == -1)
				{					
					if (v)
					{
						r->VariateValue = 1;
						S->list[j].Sat++;
						//S->list[j].UnsignedNum--;
						S->list[j].s = 0;
					}
					else
					{
						r->VariateValue = 0;
						S->list[j].Unsat++;
						//S->list[j].UnsignedNum--;
					}
					break;
				}
			}
	}

	for (t2 = S->relist[y].first; t2 != NULL; t2 = t2->next)
	{
		j = t2->ClauseNum;
		if (S->list[j].s)
		{
			for (r = S->list[j].first; r != NULL; r = r->next)
			{
				k = r->Variate;
				if (k == y && r->VariateValue == -1)
				{
					if (!v)
					{
						r->VariateValue = 1;
						S->list[j].Sat++;
						//S->list[j].UnsignedNum--;
						S->list[j].s = 0;
					}
					else
					{
						r->VariateValue = 0;
						S->list[j].Unsat++;
						//S->list[j].UnsignedNum--;
					}
					break;
				}
			}
		}
	}

	//PrintPuzzle(S);

return OK;
}

Status NewReCoverValue(SAT2* S, int i, int j)//对该处进行恢复赋值操作
{//恢复赋值规则:无论子句是否消隐都需要遍历;若该变量的赋值不为-1,则进行恢复

	int y = 0, w, k, c, n = S->n, x = 0;//x用于存储该文字，y用于存储其逆文字
	Word* t1, * t2;//t1是指向本文字的指针，t2是指向逆文字的指针
	Node* r;
	x = 2 * ((i - 1) * n + j);
	y = Verse(x);
	S->puzzle[i][j] = -1;

	for (t1 = S->relist[x].first; t1 != NULL; t1 = t1->next)
	{
		k = t1->ClauseNum;
		for (r = S->list[k].first; r != NULL; r = r->next)
		{
			if (r->Variate == x && r->VariateValue != -1)
			{
				r->VariateValue = -1;
				if (S->relist[x].VariateValue == 1)
				{
					S->list[k].Sat--;
					S->list[k].s = 1;
				}
				else
				{
					S->list[k].Unsat--;
					//S->list[j].UnsignedNum++;
				}
				break;
			}
		}
	}

	for (t2 = S->relist[y].first; t2 != NULL; t2 = t2->next)
	{
		k = t2->ClauseNum;
		for (r = S->list[j].first; r != NULL; r = r->next)
		{
			if (r->Variate == y && r->VariateValue != -1)
			{
				r->VariateValue = -1;
				if (S->relist[y].VariateValue == 1)
				{
					S->list[k].Sat--;
					S->list[k].s = 1;
				}
				else
				{
					S->list[k].Unsat--;
					//S->list[j].UnsignedNum++;
				}
				break;
			}
		}
	}

	S->relist[x].VariateValue = -1;
	S->relist[y].VariateValue = -1;

	return OK;
}
