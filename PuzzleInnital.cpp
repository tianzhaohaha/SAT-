#include"pre-SAT.h"

Status PuzzleInnital(SAT2* S)//��ʼ�������ĺ�����nΪ����
{//�ú������漰�ļ�����
	int i = 0, j = 0, k = 0;
	//i���ƴ�ѭ����j����Сѭ����k�������ڲ�ѭ������Ϊ��������;
	int a = 0, b = 0;
	//a��ʾ����һ���Ӿ������b ��ʾ��������Ӿ����
	int t, m, n = S->n;
	Node* l = NULL, * lnode = NULL;//lΪ��ָ̬�룬lnodeΪ��ָ̬��
	Word* r = NULL;
	a = 2 * (n - 2) * n * 2;
	b = cmn(n/2 + 1, n) * 2 * n * 2;

	Iniate2(&S);
    R1(S, 1, a);
    R2(S, a + 1, a + b);
    R3(S, a + b + 1);
	
	for (i = 1; i <= S->ClauseNum; i++)	if (S->list[i].first) k++;//����ͳ���Ӿ���Ŀ
	for (i = 1; i < MAXNUM; i += 2) if (S->relist[i].first || S->relist[i + 1].first) j++;//ͳ�Ʊ�Ԫ��
	S->ClauseNum = k;
	S->VariateNum = j;
	PrintPuzToCNF(S);

return OK;
}