#include"pre-SAT.h"

Status  deletec(SAT* S)//���õ��Ӿ仯���Ӿ伯��yΪ����ĳ�ʼ����
{
	int x , i,y,j;
	Node* t;
	x = danzijuselect(S);//Ѱ�ҵ��Ӿ�
	while (x)
	{
        deletel(S, x);//ɾ�������Ӿ�����x���Ӿ�
		y = Verse(x);//��������
        deletew(S, y);//ִ�д����ֹ�����������//���DeleteList(S, x)����
		x = danzijuselect(S);//����ѡȡ����
	}
return OK;
}

Status  DeleteClause2(SAT2* S)//���õ��Ӿ仯���Ӿ伯��yΪ����ĳ�ʼ����
{
	int x, i, y, j;
	Node* t;
	x = SelectClause2(S);
	while (x)
	{
		DeleteList2(S, x);//ɾ�������Ӿ�����x���Ӿ�
		y = Verse(x);//��������
		DeleteWord2(S, y);//ִ�д����ֹ�����������
		//PrintClause2(S);
		x = SelectClause2(S);//����ѡȡ����
	}
	return OK;
}
Status deletel(SAT* S, int x)//ȥ�������Ӿ�����x���Ӿ亯����xΪ��Ӧ���Ӿ����ֱ��
{//���Ӿ������н��Ӿ�����
    int  j = 0, k = 0;
    Word* t;
    Node* r;
    t = S->relist[x].first;
    S->relist[x].VariateValue = 1;///////////////////?����������
    while (t)
    {
        j = t->ClauseNum;
        r = S->list[j].first;
        if (S->list[j].s)//�Ӿ�δ��������s=1
        {
            while (r)//��δ���������Ӿ��в���
            {
                k = r->Variate;
                if (k == x && r->VariateValue == -1)//-1Ϊδ����ֵ
                {
                    r->VariateValue = 1;
                    S->list[j].Sat++;//��ֵ��������+1
                    //S->list[j].UnsignedNum--;
                    S->list[j].s = 0;/////////�Ӿ�����?��ɾ��һ�������������Ӿ䣿
                    break;
                }
                r = r->next;//��һ������
            }
        }
        t = t->next;//��һ���Ӿ�
    }

    return OK;
}


Status DeleteList2(SAT2* S, int x)//ȥ������Ҫ����Ӿ�
{
    int  j, w, k, c, n = S->n;
    Word* t;
    Node* r;
    SAT2* s = S;
    t = S->relist[x].first;
    S->relist[x].VariateValue = 1;

    if (x <= 2 * n * n)
    {
        Cell(S, x, &k, &c);
        if (x % 2)  S->puzzle[k][c] = 1;
        else S->puzzle[k][c] = 0;
    }

    while (t)
    {
        j = t->ClauseNum;
        r = S->list[j].first;
        if (S->list[j].s)
        {
            while (r)
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
                r = r->next;
            }
        }
        t = t->next;
    }
    //PrintPuzzle(S);
    return OK;
}
Status deletew(SAT* S, int x)//ɾ�����ֺ���,x�Ƕ�Ӧ�����֣������ֹ���,���丳ֵΪ0������������ɾ����
{//�����Ӿ��������丳ֵΪ0�����ڹ�����������ɾ�����
    int  j = 0, k = 0;
    Word* t;
    Node* r;
    t = S->relist[x].first;
    S->relist[x].VariateValue = 0;/////////////////���ڹ�����������ɾ�����?
    while (t)
    {
        j = t->ClauseNum;
        if (S->list[j].s)//δ������
            for (r = S->list[j].first; r != NULL; r = r->next)
            {
                if (r->Variate == x)
                {
                    r->VariateValue = 0;
                    S->list[j].Unsat++;
                    //S->list[j].UnsignedNum--;
                    break;
                }
            }
        t = t->next;
    }

    return OK;
}

Status DeleteWord2(SAT2* S, int x)//ɾ������
{
    int  j, w, k, c, n = S->n;
    Word* t;
    Node* r;
    SAT2* s = S;
    t = S->relist[x].first;
    S->relist[x].VariateValue = 0;

    while (t)
    {
        j = t->ClauseNum;
        if (S->list[j].s)
            for (r = S->list[j].first; r != NULL; r = r->next)
            {
                if (r->Variate == x)
                {
                    r->VariateValue = 0;
                    S->list[j].Unsat++;
                    //S->list[j].UnsignedNum--;
                    break;
                }
            }
        t = t->next;
    }
    //PrintPuzzle(S);
    return OK;
}
