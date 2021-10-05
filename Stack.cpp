#include"pre-SAT.h"

Status InStack(SAT* S, int x, bool s)//��ջ����
{
	int a = S->top;
	S->stack[a].Variate = x;
	S->stack[a].judge = s;
	S->stack[a].diverse = 0;
	S->top++;
	if (s) S->num++;
	
return OK;
}

Status InStack2(SAT2* S, int x, bool s)//��ջ������xΪ��ջԪ�أ�sΪ��ջ���״̬
{
	int a = S->top;
	S->stack[a].Variate = x;
	S->stack[a].judge = s;
	S->stack[a].diverse = 0;
	S->top++;
	if (s) S->num++;

	return OK;
}

bool EmptyStack(SAT* S)//�ж�ջ�Ƿ�Ϊ���ա�
{
	if (S->top == 0) return -1;//ջ��
	else if (!S->num) return 0;//ջ�����գ�������������ݵ�״̬
		 else  return 1;//ջ�����գ�����Ҫ���л���	
}

bool EmptyStack2(SAT2* S)//�ж�ջ�Ƿ�Ϊ��gai
{
	if (S->top == 0) return -1;//ջ��
	else if (!S->num) return 0;//ջ�����գ�������������ݵ�״̬
	else  return 1;//ջ�����գ�����Ҫ���л���	
}

Status OutStack(SAT* S)//��ջ���������ָ���ֵ��
{//���ڳ�ջ֮���Ԫ�أ���ջ�ڸ�ֵΪ0
    int x = 0;//x���ڴ洢�����֣�y���ڴ洢��������
    Node* t;
    Word* r1,*r2;//r1ָ������ֵĹ�����������r2ָ���������ֵĹ�����������
    while ( (S->stack[S->top-1].judge!=1 || S->stack[S->top-1].diverse!=0) && S->num>0 && S->stack[S->top - 1].Variate)
    {
        x = S->stack[S->top - 1].Variate;
        ReCoverValue(S, x);
        if (S->stack[S->top - 1].diverse == 1) S->num--;
        //printf("%d %d %d %d\n", S->top - 1, S->stack[S->top - 1].Variate, S->stack[S->top - 1].judge, S->stack[S->top - 1].diverse);
        S->stack[S->top - 1].Variate = S->stack[S->top - 1].judge = S->stack[S->top - 1].diverse = 0;
        S->top--;
    };
    //��ջ��Ϊδ��ת��ֵ�ľ��߱�������ջ����ջ�׻����ھ��߱���ʱ��ջ

    return OK;
}


Status OutStack2(SAT2* S)//��ջ���������ָ���ֵ��
{//���ڳ�ջ֮���Ԫ�أ���ջ�ڸ�ֵΪ0
    int x, y, j, i = 0, n = S->n;//x���ڴ洢�����֣�y���ڴ洢��������
    int w, k, c;
    Node* t;
    Word* r1, * r2;//r1ָ������ֵĹ�����������r2ָ���������ֵĹ�����������
    while ((S->stack[S->top - 1].judge != 1 || S->stack[S->top - 1].diverse != 0) && S->num > 0 && S->stack[S->top - 1].Variate)
    {
        x = S->stack[S->top - 1].Variate;
        ReCoverValue2(S, x);//�Ըô����лָ���ֵ�Ĳ���
        S->stack[S->top - 1].Variate = S->stack[S->top - 1].judge = S->stack[S->top - 1].diverse = 0;
        S->top--;
    };
    //��ջ��Ϊδ��ת��ֵ�ľ��߱�������ջ����ջ�׻����ھ��߱���ʱ��ջ

    return OK;
}
