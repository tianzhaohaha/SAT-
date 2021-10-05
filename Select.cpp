#include"pre-SAT.h"

int bianliangselect(SAT* S)//������һ��֧��ֵ������ѡ���һ�е�һ����
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
					InStack(S, x, 1);//�Ծ��߱�����ջ
					//printf("%d is Selected in clause %d !\n", x, i);
					return x;
				}
			}
	}

return x;
}


int SelectVariate2(SAT2* S)//������һ��֧��ֵ����gai
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
					InStack2(S, x, 1);//�Ծ��߱�����ջ
					//printf("%d is Selected in clause %d !\n", x, i);
					return x;
				}
			}
	}

	return x;

}

int SelectVariate3(SAT* S)//������һ��֧��ֵ������ѡ���һ��δ��ֵ������
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
			InStack(S, x, 1);//�Ծ��߱�����ջ
			return x;
		}
			
	}

}

int danzijuselect(SAT* S)//Ѱ�ҵ��Ӿ䣬���ص��Ӿ�ı��
{
    int i = 0, x = 0;
    Node* t = NULL, * r = NULL;
    for (i = 1; i <= S->ClauseNum; i++)
        if (S->list[i].s && (S->list[i].VariateNum - 1) == S->list[i].Unsat)//ֻʣ��һ���ɸ�ֵ�ı���
        {
            for (t = S->list[i].first; t != NULL; t = t->next)
            {
                if (t->VariateValue == -1)// �˱���δ��ֵ
                {
                    x = t->Variate;
                    InStack(S, x, 0);//�ԷǾ��߱�����ջ
                    //printf("\n%d Selected in Clause %d!\n", x, i);
                    return x;
                }
            }
        }

    return false;
}

int SelectClause2(SAT2* S)//Ѱ�ҵ��Ӿ䣬���ص��Ӿ�ı��
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
                    InStack2(S, x, 0);//�ԷǾ��߱�����ջ
                    //printf("\n%d Selected in Clause %d!\n", x, i);
                    return x;
                }
            }
        }

    return false;
}