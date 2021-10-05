#include"pre-SAT.h"

Status InStack(SAT* S, int x, bool s)//入栈函数
{
	int a = S->top;
	S->stack[a].Variate = x;
	S->stack[a].judge = s;
	S->stack[a].diverse = 0;
	S->top++;
	if (s) S->num++;
	
return OK;
}

Status InStack2(SAT2* S, int x, bool s)//入栈函数，x为入栈元素，s为入栈标记状态
{
	int a = S->top;
	S->stack[a].Variate = x;
	S->stack[a].judge = s;
	S->stack[a].diverse = 0;
	S->top++;
	if (s) S->num++;

	return OK;
}

bool EmptyStack(SAT* S)//判断栈是否为“空”
{
	if (S->top == 0) return -1;//栈空
	else if (!S->num) return 0;//栈本身不空，但无需继续回溯的状态
		 else  return 1;//栈本身不空，且需要进行回溯	
}

bool EmptyStack2(SAT2* S)//判断栈是否为空gai
{
	if (S->top == 0) return -1;//栈空
	else if (!S->num) return 0;//栈本身不空，但无需继续回溯的状态
	else  return 1;//栈本身不空，且需要进行回溯	
}

Status OutStack(SAT* S)//出栈函数（带恢复赋值）
{//对于出栈之后的元素，在栈内赋值为0
    int x = 0;//x用于存储该文字，y用于存储其逆文字
    Node* t;
    Word* r1,*r2;//r1指向该文字的关联变量链表，r2指向其逆文字的关联变量链表
    while ( (S->stack[S->top-1].judge!=1 || S->stack[S->top-1].diverse!=0) && S->num>0 && S->stack[S->top - 1].Variate)
    {
        x = S->stack[S->top - 1].Variate;
        ReCoverValue(S, x);
        if (S->stack[S->top - 1].diverse == 1) S->num--;
        //printf("%d %d %d %d\n", S->top - 1, S->stack[S->top - 1].Variate, S->stack[S->top - 1].judge, S->stack[S->top - 1].diverse);
        S->stack[S->top - 1].Variate = S->stack[S->top - 1].judge = S->stack[S->top - 1].diverse = 0;
        S->top--;
    };
    //当栈顶为未翻转赋值的决策变量，且栈顶到栈底还存在决策变量时出栈

    return OK;
}


Status OutStack2(SAT2* S)//出栈函数（带恢复赋值）
{//对于出栈之后的元素，在栈内赋值为0
    int x, y, j, i = 0, n = S->n;//x用于存储该文字，y用于存储其逆文字
    int w, k, c;
    Node* t;
    Word* r1, * r2;//r1指向该文字的关联变量链表，r2指向其逆文字的关联变量链表
    while ((S->stack[S->top - 1].judge != 1 || S->stack[S->top - 1].diverse != 0) && S->num > 0 && S->stack[S->top - 1].Variate)
    {
        x = S->stack[S->top - 1].Variate;
        ReCoverValue2(S, x);//对该处进行恢复赋值的操作
        S->stack[S->top - 1].Variate = S->stack[S->top - 1].judge = S->stack[S->top - 1].diverse = 0;
        S->top--;
    };
    //当栈顶为未翻转赋值的决策变量，且栈顶到栈底还存在决策变量时出栈

    return OK;
}
