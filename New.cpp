#include"pre-SAT.h"

Status ReCoverValue(SAT* S, int x)//�������ֵ�������лָ���ֵ��Ҳ�ɶ�CNF���д���
{//�ָ���ֵ����:�����Ӿ��Ƿ���������Ҫ����;���ñ����ĸ�ֵ��Ϊ-1,����лָ�
	int y, j = 0;//x���ڴ洢�����֣�y���ڴ洢��������
	Word* t1, * t2;//t1��ָ�����ֵ�ָ�룬t2��ָ�������ֵ�ָ��
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

Status ReCoverValue2(SAT2* S, int x)//�������ֵ�������лָ���ֵ�����������д���
{//�ָ���ֵ����:�����Ӿ��Ƿ���������Ҫ����;���ñ����ĸ�ֵ��Ϊ-1,����лָ�
	int y, j = 0, w, k, c, n = S->n;//x���ڴ洢�����֣�y���ڴ洢��������
	Word* t1, * t2;//t1��ָ�����ֵ�ָ�룬t2��ָ�������ֵ�ָ��
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

Status NewCopyValue(SAT2* S, int i, int j, bool v)//�������еĸô����и�ֵ����
{
	int a, b;//aΪ�����ָ�ֵ��bΪ�������ָ�ֵ
	int x, w, k, c, n = S->n, y = 0;
	bool value;
	Word* t1, * t2;//t1��ָ�����ֵ�ָ�룬t2��ָ�������ֵ�ָ��
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

Status NewReCoverValue(SAT2* S, int i, int j)//�Ըô����лָ���ֵ����
{//�ָ���ֵ����:�����Ӿ��Ƿ���������Ҫ����;���ñ����ĸ�ֵ��Ϊ-1,����лָ�

	int y = 0, w, k, c, n = S->n, x = 0;//x���ڴ洢�����֣�y���ڴ洢��������
	Word* t1, * t2;//t1��ָ�����ֵ�ָ�룬t2��ָ�������ֵ�ָ��
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
