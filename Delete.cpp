#include"pre-SAT.h"

Status  deletec(SAT* S)//利用单子句化简子句集，y为传入的初始参量
{
	int x , i,y,j;
	Node* t;
	x = danzijuselect(S);//寻找单子句
	while (x)
	{
        deletel(S, x);//删除含单子句文字x的子句
		y = Verse(x);//求逆文字
        deletew(S, y);//执行纯文字规则消除变量//配合DeleteList(S, x)进行
		x = danzijuselect(S);//重新选取变量
	}
return OK;
}

Status  DeleteClause2(SAT2* S)//利用单子句化简子句集，y为传入的初始参量
{
	int x, i, y, j;
	Node* t;
	x = SelectClause2(S);
	while (x)
	{
		DeleteList2(S, x);//删除含单子句文字x的子句
		y = Verse(x);//求逆文字
		DeleteWord2(S, y);//执行纯文字规则消除变量
		//PrintClause2(S);
		x = SelectClause2(S);//重新选取变量
	}
	return OK;
}
Status deletel(SAT* S, int x)//去掉含单子句文字x的子句函数，x为对应单子句文字编号
{//在子句链表中将子句消隐
    int  j = 0, k = 0;
    Word* t;
    Node* r;
    t = S->relist[x].first;
    S->relist[x].VariateValue = 1;///////////////////?文字正负？
    while (t)
    {
        j = t->ClauseNum;
        r = S->list[j].first;
        if (S->list[j].s)//子句未被消隐，s=1
        {
            while (r)//在未被消隐的子句中查找
            {
                k = r->Variate;
                if (k == x && r->VariateValue == -1)//-1为未被赋值
                {
                    r->VariateValue = 1;
                    S->list[j].Sat++;//赋值变量个数+1
                    //S->list[j].UnsignedNum--;
                    S->list[j].s = 0;/////////子句消隐?仅删除一个就消隐整个子句？
                    break;
                }
                r = r->next;//下一个文字
            }
        }
        t = t->next;//下一个子句
    }

    return OK;
}


Status DeleteList2(SAT2* S, int x)//去掉符合要求的子句
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
Status deletew(SAT* S, int x)//删除文字函数,x是对应的文字（纯文字规则）,将其赋值为0，关联链表里删除？
{//对于子句链表，将其赋值为0；对于关联变量链表，删掉结点
    int  j = 0, k = 0;
    Word* t;
    Node* r;
    t = S->relist[x].first;
    S->relist[x].VariateValue = 0;/////////////////对于关联变量链表，删掉结点?
    while (t)
    {
        j = t->ClauseNum;
        if (S->list[j].s)//未被消隐
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

Status DeleteWord2(SAT2* S, int x)//删除文字
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
