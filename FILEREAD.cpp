#include "pre-SAT.h"

Status Input(FILE* in, SAT* S)//�����ڽӱ����뺯��
{
	char s[101];
	int i = 0, j = 0, k = 0;   //i���Ӿ������в�����j�ڹ������������в�����kΪ���ݻ���
	int n = 0, a = 0, b = 0;   //n��Ϊ�����������������Ŀ��a����ͳ��ÿ���־��������
	Node* l = NULL, * lnode = NULL;//lΪ��ָ̬�룬lnodeΪ��ָ̬��
	Word* r = NULL;

	Iniate(&S);
	a = 0;
	b = fscanf(in, "%s", s);//��ַ���뵽s��
	while (b = strcmp(s, "cnf")) b = fscanf(in, "%s", s);//����ע����
	b = fscanf(in, "%d %d", &S->VariateNum, &S->ClauseNum);///////////////1

	for (i = 1; i <= S->ClauseNum; i++)  //�Ӿ�������룬ͬʱ���������������
	{
		a = 0;//�Ӿ�������
		S->list[i].first = (Node*)malloc(sizeof(Node));
		l = S->list[i].first;//lΪ��ָ̬��
		b = fscanf(in, "%d", &k);
		while (k)
		{
			a++;
			if (k > 0) //������Ϊ��
			{
				j = 2 * k - 1;////////////////?����λΪ��
				l->VariateValue = UNSIGN;//�Ӿ������б�����ȡֵ����ʼֵ��ֵΪ-1
				l->Variate = j;//�Ӿ�����������ڵ��еı���
				S->relist[j].col30++;
				S->relist[j].n++;
				if (!S->relist[j].first)//��������������δ����
				{
					S->relist[j].VariateValue = -1;////////////////����Ϊ������
					r = (Word*)malloc(sizeof(Word));//����һ�������Ӿ�����Ľ��
					r->ClauseNum = i;//�Ӿ�λ��
					r->next = NULL;
					S->relist[j].first = S->relist[j].last = r;

				}
				else//���������������Ѵ���
				{
					r = (Word*)malloc(sizeof(Word));
					r->ClauseNum = i;
					r->next = NULL;
					S->relist[j].last->next = r;//j��λ����ָ���Ӿ�λ��
					S->relist[j].last = r;
				}
			}
			else  //������Ϊ��
			{
				l->VariateValue = UNSIGN;
				j = (-k) * 2;//��������λ��
				l->Variate = j;////////////������ֵ�ع��ˣ�
				S->relist[j].col30--;
                S->relist[j].n++;
				if (!S->relist[j].first)//��������������δ����
				{
					S->relist[j].VariateValue = -1;
					r = (Word*)malloc(sizeof(Word));
					r->ClauseNum = i;
					r->next = NULL;
					S->relist[j].first = S->relist[j].last = r;
				}
				else //���������������Ѵ���
				{
					r = (Word*)malloc(sizeof(Word));
					r->ClauseNum = i;
					r->next = NULL;
					S->relist[j].last->next = r;
					S->relist[j].last = r;
				}
			}
			lnode = l;
			l->next = (Node*)malloc(sizeof(Node));
			l = l->next;
			b = fscanf(in, "%d", &k);
		}//ÿ���־��ȡ
		lnode->next = NULL;
		free(l);
		//S->list[i].UnsignedNum = a;
		S->list[i].VariateNum = a;
		S->list[i].s = 1;//δ������
	}//�����ļ�ÿ���Ӿ��ȡ
	
	
return OK;
}


Status Iniate(SAT** S)//�������ݽṹ�ĳ�ʼ��
{
    SAT* s = *S;
    int i, j, k;

    for (i = 0; i < MAXNUM; i++)
    {
        s->list[i].Sat = s->list[i].Unsat = s->list[i].VariateNum = 0;//ȡֵΪһ��ȡֵΪ0����������Ϊ0//ÿһ�Ӿ�
        //s->list[i].UnsignedNum = 0;
        s->list[i].first = NULL;//ͷָ�����
        s->list[i].s = 0;//����
        s->relist[i].VariateValue = UNSIGN;
        s->relist[i].first = s->relist[i].last = NULL;
        s->relist[i].col30 =  0;
    }
    s->ClauseNum = s->VariateNum = s->top = s->num = 0;//ջ��������Ⱦ���Ϊ0
    *S = s;

    return OK;
}

Status Iniate2(SAT2** S)//�������ݽṹ�ĳ�ʼ��
{
    SAT2* s = *S;
    int i, j, k;

    for (i = 0; i < MAXNUM; i++)
    {
        s->list[i].Sat = s->list[i].Unsat = s->list[i].VariateNum = 0;
        //s->list[i].UnsignedNum = 0;
        s->list[i].first = NULL;
        s->list[i].s = 0;
        s->relist[i].VariateValue = UNSIGN;
        s->relist[i].first = s->relist[i].last = NULL;
        s->relist[i].col30 = 0;
    }
    for (i = 0; i < PL; i++)
        for (j = 0; j < PL; j++)
            s->puzzle[i][j] = -1;
    s->ClauseNum = s->VariateNum = s->top = s->num = 0;
    *S = s;

    return OK;
}