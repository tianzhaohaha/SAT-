#include"pre-SAT.h"

Status CopyValue(SAT* S, int x)//��ֵ����x���������ָ�ֵ
{//��ֵ���򣺱�ѡ�еı�����ֵΪ0���������ָ�ֵΪ1
	int j = 0, y = 0, k = 0;
	Word* t1, * t2;//t1��ָ�����ֵ�ָ�룬t2��ָ�������ֵ�ָ��
	Node* r;
	//if (!x) return ERROR;
	y = Verse(x);
	S->relist[x].VariateValue = 0;
	S->relist[y].VariateValue = 1;
	for (t1 = S->relist[x].first; t1 != NULL; t1 = t1->next)
	{
		j = t1->ClauseNum;
		if (S->list[j].s)
			for (r = S->list[j].first; r != NULL; r = r->next)
			{
				if (r->Variate == x && r->VariateValue == -1)
				{
					r->VariateValue = 0;
					S->list[j].Unsat++;
					//S->list[j].UnsignedNum--;
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
					r->VariateValue = 1;
					S->list[j].Sat++;
					//S->list[j].UnsignedNum--;
					S->list[j].s = 0;
					break;
				}
			}			
		}
	}

	//printf("%d CopyValue Successfully!\n", x);

	return OK;
}

Status CopyValue2(SAT2* S, int x)//��ֵ��������⣩
{//��ֵ���򣺱����ָ�0�������ָ�1
	int a, b;//aΪ�����ָ�ֵ��bΪ�������ָ�ֵ
	int j, w, k, c, n = S->n, y = 0;
	bool value;
	Word* t1, * t2;//t1��ָ�����ֵ�ָ�룬t2��ָ�������ֵ�ָ��
	Node* r;
	
	if (x <= 2 * n * n)
	{
		Cell(S, x, &k, &c);
		if (x % 2)  S->puzzle[k][c] = 0;
		else S->puzzle[k][c] = 1;
	}

	y = Verse(x);
	S->relist[x].VariateValue = 0;
	S->relist[y].VariateValue = 1;
	for (t1 = S->relist[x].first; t1 != NULL; t1 = t1->next)
	{
		j = t1->ClauseNum;
		if (S->list[j].s)
			for (r = S->list[j].first; r != NULL; r = r->next)
			{
				if (r->Variate == x && r->VariateValue == -1)
				{
					r->VariateValue = 0;
					S->list[j].Unsat++;
					//S->list[j].UnsignedNum--;
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
					r->VariateValue = 1;
					S->list[j].Sat++;
					//S->list[j].UnsignedNum--;
					S->list[j].s = 0;					
					break;
				}
			}
		}
	}

	//PrintPuzzle(S);

	return OK;
}
