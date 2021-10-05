#include "pre-SAT.h"

Status Input(FILE* in, SAT* S)//两个邻接表输入函数
{
	char s[101];
	int i = 0, j = 0, k = 0;   //i在子句链表中操作，j在关联变量链表中操作，k为数据缓存
	int n = 0, a = 0, b = 0;   //n作为关联变量链表的总数目，a用来统计每个字句的文字数
	Node* l = NULL, * lnode = NULL;//l为动态指针，lnode为静态指针
	Word* r = NULL;

	Iniate(&S);
	a = 0;
	b = fscanf(in, "%s", s);//地址输入到s里
	while (b = strcmp(s, "cnf")) b = fscanf(in, "%s", s);//消除注释行
	b = fscanf(in, "%d %d", &S->VariateNum, &S->ClauseNum);///////////////1

	for (i = 1; i <= S->ClauseNum; i++)  //子句链表读入，同时键入关联变量链表
	{
		a = 0;//子句文字数
		S->list[i].first = (Node*)malloc(sizeof(Node));
		l = S->list[i].first;//l为动态指针
		b = fscanf(in, "%d", &k);
		while (k)
		{
			a++;
			if (k > 0) //若文字为正
			{
				j = 2 * k - 1;////////////////?奇数位为正
				l->VariateValue = UNSIGN;//子句链表中变量的取值，初始值赋值为-1
				l->Variate = j;//子句链表中链表节点中的变量
				S->relist[j].col30++;
				S->relist[j].n++;
				if (!S->relist[j].first)//若关联变量链表未创建
				{
					S->relist[j].VariateValue = -1;////////////////文字为负？？
					r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
					r->ClauseNum = i;//子句位置
					r->next = NULL;
					S->relist[j].first = S->relist[j].last = r;

				}
				else//若关联变量链表已创建
				{
					r = (Word*)malloc(sizeof(Word));
					r->ClauseNum = i;
					r->next = NULL;
					S->relist[j].last->next = r;//j号位文字指向子句位置
					S->relist[j].last = r;
				}
			}
			else  //若文字为负
			{
				l->VariateValue = UNSIGN;
				j = (-k) * 2;//关联链表位置
				l->Variate = j;////////////将正负值重构了？
				S->relist[j].col30--;
                S->relist[j].n++;
				if (!S->relist[j].first)//若关联变量链表未创建
				{
					S->relist[j].VariateValue = -1;
					r = (Word*)malloc(sizeof(Word));
					r->ClauseNum = i;
					r->next = NULL;
					S->relist[j].first = S->relist[j].last = r;
				}
				else //若关联变量链表已创建
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
		}//每个字句读取
		lnode->next = NULL;
		free(l);
		//S->list[i].UnsignedNum = a;
		S->list[i].VariateNum = a;
		S->list[i].s = 1;//未被消隐
	}//整个文件每行子句读取
	
	
return OK;
}


Status Iniate(SAT** S)//整个数据结构的初始化
{
    SAT* s = *S;
    int i, j, k;

    for (i = 0; i < MAXNUM; i++)
    {
        s->list[i].Sat = s->list[i].Unsat = s->list[i].VariateNum = 0;//取值为一与取值为0变量个数设为0//每一子句
        //s->list[i].UnsignedNum = 0;
        s->list[i].first = NULL;//头指针设空
        s->list[i].s = 0;//消隐
        s->relist[i].VariateValue = UNSIGN;
        s->relist[i].first = s->relist[i].last = NULL;
        s->relist[i].col30 =  0;
    }
    s->ClauseNum = s->VariateNum = s->top = s->num = 0;//栈与变量数等均设为0
    *S = s;

    return OK;
}

Status Iniate2(SAT2** S)//整个数据结构的初始化
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