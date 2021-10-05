#include"pre-SAT.h"

Status R1(SAT2* S, int a, int b)//规则一创建子句集
{//n为数独阶数，a为创建子句的起始编号，b为创建子句的终止编号
    int n = S->n;
    int i = 0, j = 0, k = 0, t = (a + b) / 2, m = n / 2, s = 0;
    int wp[3], wn[3];//用作选取的数组，正文字为wp，负文字为wn
    int tp = 0, tn = 0;
    Node* l = NULL, * lnode = NULL;//l为动态指针，lnode为静态指针
    Word* r = NULL;

    for (j = 0; j < 3; j++)
    {
        if (!j) { wp[j] = 1; wn[j] = 2; }
        else { wp[j] = wp[j - 1] + 2; wn[j] = wn[j - 1] + 2; }
        tp = tn = 1;
    }

    for (i = a; i <= t; i++)//以行为主序
    {
        s = 0;
        S->list[i].first = (Node*)malloc(sizeof(Node));
        l = S->list[i].first;
        while (s < 3)
        {
            if (i % 2) k = wp[s];
            else k = wn[s];
            l->Variate = k;
            l->VariateValue = UNSIGN;
            if (!S->relist[k].first)//若关联变量链表未创建
            {
                S->relist[k].VariateValue = -1;
                r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                r->ClauseNum = i;
                r->next = NULL;
                S->relist[k].first = S->relist[k].last = r;
            }
            else//若关联变量链表已创建
            {
                r = (Word*)malloc(sizeof(Word));
                r->ClauseNum = i;
                r->next = NULL;
                S->relist[k].last->next = r;
                S->relist[k].last = r;
            }
            lnode = l;
            l->next = (Node*)malloc(sizeof(Node));
            l = l->next;
            s++;
        }
        lnode->next = NULL;
        free(l);
        //S->list[i].UnsignedNum = s;
        S->list[i].VariateNum = s;
        S->list[i].s = 1;
        if (i % 2)
        {
            if (tp < n - 2)
            {
                for (j = 0; j < 3; j++) wp[j] += 2;
                tp++;
            }
            else
            {
                for (j = 0; j < 3; j++) wp[j] += 6;
                tp=1;
            }
        }
        else
        {
            if (tn < n - 2)
            {
                for (j = 0; j < 3; j++) wn[j] += 2;
                tn++;
            }
            else
            {
                for (j = 0; j < 3; j++) wn[j] += 6;
                tn=1;
            }
        }
    }

    for (j = 0; j < 3; j++)
    {
        if (!j) { wp[j] = 1; wn[j] = 2; }
        else { wp[j] = wp[j - 1] + 2 * n; wn[j] = wn[j - 1] + 2 * n; }
        tp = tn = 1;
    }

    for (i = t+1; i <= b; i++)//以列为主序
    {
        s = 0;
        S->list[i].first = (Node*)malloc(sizeof(Node));
        l = S->list[i].first;
        while (s < 3)
        {
            if (i % 2) k = wp[s];
            else k = wn[s];
            l->Variate = k;
            l->VariateValue = UNSIGN;
            if (!S->relist[k].first)//若关联变量链表未创建
            {
                S->relist[k].VariateValue = -1;
                r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                r->ClauseNum = i;
                r->next = NULL;
                S->relist[k].first = S->relist[k].last = r;
            }
            else//若关联变量链表已创建
            {
                r = (Word*)malloc(sizeof(Word));
                r->ClauseNum = i;
                r->next = NULL;
                S->relist[k].last->next = r;
                S->relist[k].last = r;
            }
            lnode = l;
            l->next = (Node*)malloc(sizeof(Node));
            l = l->next;
            s++;
        }
        lnode->next = NULL;
        free(l);
        //S->list[i].UnsignedNum = s;
        S->list[i].VariateNum = s;
        S->list[i].s = 1;
        if (i % 2)
        {
            if (tp < n - 2)
            {
                for (j = 0; j < 3; j++) wp[j] += 2 * n;
                tp++;
            }
            else
            {
                for (j = 0; j < 3; j++) wp[j] -= ((n - 3) * n - 1) * 2;
                tp = 1;
            }
        }
        else
        {
            if (tn < n - 2)
            {
                for (j = 0; j < 3; j++) wn[j] += 2 * n;
                tn++;
            }
            else
            {
                for (j = 0; j < 3; j++) wn[j] -= ((n - 3) * n - 1) * 2;
                tn = 1;
            }
        }
    }


    return OK;
}
Status R3(SAT2* S, int a)//规则三创建子句集
{//n为数独阶数，a为创建子句的起始编号
    int n = S->n;
    int g = 0, i1 = 0, i2 = 0, j = 0, h = a, s = 0;
    int k1[2][2], k2[PL][2], t[2][2];
    int x1 = 0, x2 = 0, x3 = 0, x4 = 0, x5 = 0;
    int m = 0, m1 = 0, m2 = 0, m3 = 0;
    int p0 = 0, p1 = 0;
    int k = 0;
    Node* l = NULL, * lnode = NULL;//l为动态指针，lnode为静态指针
    Word* r = NULL;

    for (s = 1; s <= 2; s++)
    {
        for(i1 = 1; i1 < n; i1++)
            for (i2 = i1 + 1; i2 <= n; i2++)
            {
                for(j = 1; j <= n; j++)
                {
                    if (s == 1)
                    {
                        x1 = (i1 - 1) * n + j;
                        x2 = (i2 - 1) * n + j;
                    }
                    if (s == 2)
                    {
                        x1 = (j - 1) * n + i1;
                        x2 = (j - 1) * n + i2;
                    }
                    t[0][0] = 2 * x1;
                    t[0][1] = 2 * x1 - 1;
                    t[1][0] = 2 * x2;
                    t[1][1] = 2 * x2 - 1;

                    for (g = 0; g <= 1; g++)
                    {
                        x3 = Number5(s, i1, i2, j, g);
                        k1[g][0] = 2 * x3;
                        k1[g][1] = 2 * x3 - 1;
                        for (m = 0; m < 3; m++)
                        {
                            S->list[h].first = (Node*)malloc(sizeof(Node));
                            l = S->list[h].first;
                            if (m < 2)
                            {
                                k = t[m][g];
                                l->VariateValue = UNSIGN;
                                l->Variate = k;
                                if (!S->relist[k].first)//若关联变量链表未创建
                                {
                                    S->relist[k].VariateValue = -1;
                                    r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                                    r->ClauseNum = h;
                                    r->next = NULL;
                                    S->relist[k].first = S->relist[k].last = r;
                                }
                                else//若关联变量链表已创建
                                {
                                    r = (Word*)malloc(sizeof(Word));
                                    r->ClauseNum = h;
                                    r->next = NULL;
                                    S->relist[k].last->next = r;
                                    S->relist[k].last = r;
                                }
                                l->next = (Node*)malloc(sizeof(Node));
                                l = l->next;
                                k = k1[g][0];
                                l->VariateValue = UNSIGN;
                                l->Variate = k;
                                if (!S->relist[k].first)//若关联变量链表未创建
                                {
                                    S->relist[k].VariateValue = -1;
                                    r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                                    r->ClauseNum = h;
                                    r->next = NULL;
                                    S->relist[k].first = S->relist[k].last = r;
                                }
                                else//若关联变量链表已创建
                                {
                                    r = (Word*)malloc(sizeof(Word));
                                    r->ClauseNum = h;
                                    r->next = NULL;
                                    S->relist[k].last->next = r;
                                    S->relist[k].last = r;
                                }
                                l->next = NULL;
                                //S->list[h].UnsignedNum = 2;
                                S->list[h].VariateNum = 2;
                                S->list[h].s = 1;
                                h++;
                            }
                            else
                            {
                                if (g) k = t[0][0];
                                else k = t[0][1];
                                l->VariateValue = UNSIGN;
                                l->Variate = k;
                                if (!S->relist[k].first)//若关联变量链表未创建
                                {
                                    S->relist[k].VariateValue = -1;
                                    r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                                    r->ClauseNum = h;
                                    r->next = NULL;
                                    S->relist[k].first = S->relist[k].last = r;
                                }
                                else//若关联变量链表已创建
                                {
                                    r = (Word*)malloc(sizeof(Word));
                                    r->ClauseNum = h;
                                    r->next = NULL;
                                    S->relist[k].last->next = r;
                                    S->relist[k].last = r;
                                }
                                l->next = (Node*)malloc(sizeof(Node));
                                l = l->next;
                                if (g) k = t[1][0];
                                else k = t[1][1];
                                l->VariateValue = UNSIGN;
                                l->Variate = k;
                                if (!S->relist[k].first)//若关联变量链表未创建
                                {
                                    S->relist[k].VariateValue = -1;
                                    r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                                    r->ClauseNum = h;
                                    r->next = NULL;
                                    S->relist[k].first = S->relist[k].last = r;
                                }
                                else//若关联变量链表已创建
                                {
                                    r = (Word*)malloc(sizeof(Word));
                                    r->ClauseNum = h;
                                    r->next = NULL;
                                    S->relist[k].last->next = r;
                                    S->relist[k].last = r;
                                }
                                l->next = (Node*)malloc(sizeof(Node));
                                l = l->next;
                                k = k1[g][1];
                                l->VariateValue = UNSIGN;
                                l->Variate = k;
                                if (!S->relist[k].first)//若关联变量链表未创建
                                {
                                    S->relist[k].VariateValue = -1;
                                    r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                                    r->ClauseNum = h;
                                    r->next = NULL;
                                    S->relist[k].first = S->relist[k].last = r;
                                }
                                else//若关联变量链表已创建
                                {
                                    r = (Word*)malloc(sizeof(Word));
                                    r->ClauseNum = h;
                                    r->next = NULL;
                                    S->relist[k].last->next = r;
                                    S->relist[k].last = r;
                                }
                                l->next = NULL;
                                //S->list[h].UnsignedNum = 3;
                                S->list[h].VariateNum = 3;
                                S->list[h].s = 1;
                                h++;
                            }
                        }
                    }

                    x4 = Number4(s, i1, i2, j);
                    k2[j - 1][0] = 2 * x4;
                    k2[j - 1][1] = 2 * x4 - 1;

                    for (m = 0; m < 3; m++)
                    {
                        S->list[h].first = (Node*)malloc(sizeof(Node));
                        l = S->list[h].first;
                        if (m < 2)
                        {
                            k = k1[m][0];
                            l->VariateValue = UNSIGN;
                            l->Variate = k;
                            if (!S->relist[k].first)//若关联变量链表未创建
                            {
                                S->relist[k].VariateValue = -1;
                                r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                                r->ClauseNum = h;
                                r->next = NULL;
                                S->relist[k].first = S->relist[k].last = r;
                            }
                            else//若关联变量链表已创建
                            {
                                r = (Word*)malloc(sizeof(Word));
                                r->ClauseNum = h;
                                r->next = NULL;
                                S->relist[k].last->next = r;
                                S->relist[k].last = r;
                            }
                            l->next = (Node*)malloc(sizeof(Node));
                            l = l->next;
                            k = k2[j - 1][1];
                            l->VariateValue = UNSIGN;
                            l->Variate = k;
                            if (!S->relist[k].first)//若关联变量链表未创建
                            {
                                S->relist[k].VariateValue = -1;
                                r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                                r->ClauseNum = h;
                                r->next = NULL;
                                S->relist[k].first = S->relist[k].last = r;
                            }
                            else//若关联变量链表已创建
                            {
                                r = (Word*)malloc(sizeof(Word));
                                r->ClauseNum = h;
                                r->next = NULL;
                                S->relist[k].last->next = r;
                                S->relist[k].last = r;
                            }
                            l->next = NULL;
                            //S->list[h].UnsignedNum = 2;
                            S->list[h].VariateNum = 2;
                            S->list[h].s = 1;
                        }
                        else
                        {
                            k = k1[0][1];
                            l->VariateValue = UNSIGN;
                            l->Variate = k;
                            if (!S->relist[k].first)//若关联变量链表未创建
                            {
                                S->relist[k].VariateValue = -1;
                                r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                                r->ClauseNum = h;
                                r->next = NULL;
                                S->relist[k].first = S->relist[k].last = r;
                            }
                            else//若关联变量链表已创建
                            {
                                r = (Word*)malloc(sizeof(Word));
                                r->ClauseNum = h;
                                r->next = NULL;
                                S->relist[k].last->next = r;
                                S->relist[k].last = r;
                            }
                            l->next = (Node*)malloc(sizeof(Node));
                            l = l->next;
                            k = k1[1][1];
                            l->VariateValue = UNSIGN;
                            l->Variate = k;
                            if (!S->relist[k].first)//若关联变量链表未创建
                            {
                                S->relist[k].VariateValue = -1;
                                r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                                r->ClauseNum = h;
                                r->next = NULL;
                                S->relist[k].first = S->relist[k].last = r;
                            }
                            else//若关联变量链表已创建
                            {
                                r = (Word*)malloc(sizeof(Word));
                                r->ClauseNum = h;
                                r->next = NULL;
                                S->relist[k].last->next = r;
                                S->relist[k].last = r;
                            }
                            l->next = (Node*)malloc(sizeof(Node));
                            l = l->next;
                            k = k2[j - 1][0];
                            l->VariateValue = UNSIGN;
                            l->Variate = k;
                            if (!S->relist[k].first)//若关联变量链表未创建
                            {
                                S->relist[k].VariateValue = -1;
                                r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                                r->ClauseNum = h;
                                r->next = NULL;
                                S->relist[k].first = S->relist[k].last = r;
                            }
                            else//若关联变量链表已创建
                            {
                                r = (Word*)malloc(sizeof(Word));
                                r->ClauseNum = h;
                                r->next = NULL;
                                S->relist[k].last->next = r;
                                S->relist[k].last = r;
                            }
                            l->next = NULL;
                            //S->list[h].UnsignedNum = 3;
                            S->list[h].VariateNum = 3;
                            S->list[h].s = 1;
                        }
                        h++;
                    }
                }

                x5 = Number3(s, i1, i2);
                p0 = 2 * x5;
                p1 = 2 * x5 - 1;

                S->list[h].first = (Node*)malloc(sizeof(Node));
                l = S->list[h].first;
                k = p0;
                l->VariateValue = UNSIGN;
                l->Variate = k;
                if (!S->relist[k].first)//若关联变量链表未创建
                {
                    S->relist[k].VariateValue = -1;
                    r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                    r->ClauseNum = h;
                    r->next = NULL;
                    S->relist[k].first = S->relist[k].last = r;
                }
                else//若关联变量链表已创建
                {
                    r = (Word*)malloc(sizeof(Word));
                    r->ClauseNum = h;
                    r->next = NULL;
                    S->relist[k].last->next = r;
                    S->relist[k].last = r;
                }
                lnode = l;
                l->next = (Node*)malloc(sizeof(Node));
                l = l->next;
                for (m = 0; m < n; m++)
                {
                    k = k2[m][0];
                    l->VariateValue = UNSIGN;
                    l->Variate = k;
                    if (!S->relist[k].first)//若关联变量链表未创建
                    {
                        S->relist[k].VariateValue = -1;
                        r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                        r->ClauseNum = h;
                        r->next = NULL;
                        S->relist[k].first = S->relist[k].last = r;
                    }
                    else//若关联变量链表已创建
                    {
                        r = (Word*)malloc(sizeof(Word));
                        r->ClauseNum = h;
                        r->next = NULL;
                        S->relist[k].last->next = r;
                        S->relist[k].last = r;
                    }
                    lnode = l;
                    l->next = (Node*)malloc(sizeof(Node));
                    l = l->next;
                }
                lnode->next = NULL;
                free(l);
                //S->list[h].UnsignedNum = n + 1;
                S->list[h].VariateNum = n + 1;
                S->list[h].s = 1;
                h++;

                for (m = 0; m < n; m++)
                {
                    S->list[h].first = (Node*)malloc(sizeof(Node));
                    l = S->list[h].first;
                    k = p1;
                    l->VariateValue = UNSIGN;
                    l->Variate = k;
                    if (!S->relist[k].first)//若关联变量链表未创建
                    {
                        S->relist[k].VariateValue = -1;
                        r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                        r->ClauseNum = h;
                        r->next = NULL;
                        S->relist[k].first = S->relist[k].last = r;
                    }
                    else//若关联变量链表已创建
                    {
                        r = (Word*)malloc(sizeof(Word));
                        r->ClauseNum = h;
                        r->next = NULL;
                        S->relist[k].last->next = r;
                        S->relist[k].last = r;
                    }
                    l->next = (Node*)malloc(sizeof(Node));
                    l = l->next;
                    k = k2[m][1];
                    l->VariateValue = UNSIGN;
                    l->Variate = k;
                    if (!S->relist[k].first)//若关联变量链表未创建
                    {
                        S->relist[k].VariateValue = -1;
                        r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
                        r->ClauseNum = h;
                        r->next = NULL;
                        S->relist[k].first = S->relist[k].last = r;
                    }
                    else//若关联变量链表已创建
                    {
                        r = (Word*)malloc(sizeof(Word));
                        r->ClauseNum = h;
                        r->next = NULL;
                        S->relist[k].last->next = r;
                        S->relist[k].last = r;
                    }
                    //S->list[h].UnsignedNum = 2;
                    S->list[h].VariateNum = 2;
                    S->list[h].s = 1;
                    l->next = NULL;
                    h++;
                }
            }
    }

    S->ClauseNum = h + a;

    return OK;
}
Status R2(SAT2* S, int a, int b)//规则二创建子句集
{//n为数独阶数，a为创建子句的起始编号，b为创建子句的终止编号
	int n = S->n;
	int i = 0, j = 0, h = 0, k = 0, t = (a + b) / 2, s = 0, m = 0;
	NewTable wp[11], wn[11];//用于生成组合的二元组表（记录每行/列）
	Node* l = NULL, * lnode = NULL;//l为动态指针，lnode为静态指针
	Word* r = NULL;

	wp[0].state = wn[0].state = wp[0].elem = wn[0].elem = 0;

	for (j = 1; j <= n ; j++)//以行为主序
	{
		if (j == 1) {
			wp[j].elem = 1;
			wn[j].elem = 2;
		}
		else {
			wp[j].elem = wp[j - 1].elem + 2;
			wn[j].elem = wn[j - 1].elem + 2;
		}
		if (j <= n / 2 + 1) {
			wp[j].state = 1;
			wn[j].state = 1;
		}
		else {
			wp[j].state = 0;
			wn[j].state = 0;
		}
	}

	i = 0; 
    //以行为主序（正文字）
	for (h = 1; h <= n; h++)
	{
		if (h != 1)//本行无组合可更新的时候，选取到下一行进行操作
		{
			for (j = 1; j <= n; j++)
			{
				if (j == 1)  wp[j].elem += 2 * n;
				else  wp[j].elem = wp[j - 1].elem + 2;					
				if (j <= n / 2 + 1) {
					wp[j].state = 1;
				}
				else {
					wp[j].state = 0;
				}
			}
		}
		do
		{
			s = 0;
			S->list[i + a].first = (Node*)malloc(sizeof(Node));
			l = S->list[i + a].first;
			for (j = 1; j <= n; j++)//遍历二元组表以建立子句
			{
				if (wp[j].state)
				{
					k = wp[j].elem;
					l->Variate = k;
					l->VariateValue = UNSIGN;
					if (!S->relist[k].first)//若关联变量链表未创建
					{
						S->relist[k].VariateValue = -1;
						r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
						r->ClauseNum = i + a;
						r->next = NULL;
						S->relist[k].first = S->relist[k].last = r;
					}
					else//若关联变量链表已创建
					{
						r = (Word*)malloc(sizeof(Word));
						r->ClauseNum = i + a;
						r->next = NULL;
						S->relist[k].last->next = r;
						S->relist[k].last = r;
					}
					lnode = l;
					l->next = (Node*)malloc(sizeof(Node));
					l = l->next;
					s++;
				}
			}
			lnode->next = NULL;
			free(l);
			//S->list[i + a].UnsignedNum = s;
			S->list[i + a].VariateNum = s;
			S->list[i + a].s = 1;
			i++;
		} while (has(wp, n));//更新所选出的组合	  

	}

    //以行为主序（负文字）
	for (h = 1; h <= n; h++)
	{
		if (h != 1)
		{
			for (j = 1; j <= n; j++)
			{
				if (j == 1)  wn[j].elem += 2 * n;
				else  wn[j].elem = wn[j - 1].elem + 2;
				if (j <= n / 2 + 1) {
					wn[j].state = 1;
				}
				else {
					wn[j].state = 0;
				}
			}
		}
		do
		{
			s = 0;
			S->list[i + a].first = (Node*)malloc(sizeof(Node));
			l = S->list[i + a].first;
			for (j = 1; j <= n; j++)
			{
				if (wn[j].state) 
				{
					k = wn[j].elem;
					l->Variate = k;
					l->VariateValue = UNSIGN;
					if (!S->relist[k].first)//若关联变量链表未创建
					{
						S->relist[k].VariateValue = -1;
						r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
						r->ClauseNum = i + a;
						r->next = NULL;
						S->relist[k].first = S->relist[k].last = r;
					}
					else//若关联变量链表已创建
					{
						r = (Word*)malloc(sizeof(Word));
						r->ClauseNum = i + a;
						r->next = NULL;
						S->relist[k].last->next = r;
						S->relist[k].last = r;
					}
					lnode = l;
					l->next = (Node*)malloc(sizeof(Node));
					l = l->next;
					s++;
				}
			}
			lnode->next = NULL;
			free(l);
			//S->list[i + a].UnsignedNum = s;
			S->list[i + a].VariateNum = s;
			S->list[i + a].s = 1;
			i++;
		} while (has(wn, n));

	}
	
	//以列为主序
	for (j = 1; j <= n; j++)
	{
		if (j == 1) {
			wp[j].elem = 1;
			wn[j].elem = 2;
		}
		else {
			wp[j].elem = wp[j - 1].elem + 2 * n;
			wn[j].elem = wn[j - 1].elem + 2 * n;
		}
		if (j <= n / 2 + 1) {
			wp[j].state = 1;
			wn[j].state = 1;
		}
		else {
			wp[j].state = 0;
			wn[j].state = 0;
		}
	}

	//以列为主序（正文字）
	for (h = 1; h <= n; h++)
	{
		if (h != 1)
		{
			for (j = 1; j <= n; j++)
			{
				wp[j].elem += 2;
				if (j <= n / 2 + 1) {
					wp[j].state = 1;
				}
				else {
					wp[j].state = 0;
				}
			}
		}
		do
		{
			s = 0;
			S->list[i + a].first = (Node*)malloc(sizeof(Node));
			l = S->list[i + a].first;
			for (j = 1; j <= n; j++)
			{
				if (wp[j].state)
				{
					k = wp[j].elem;
					l->Variate = k;
					l->VariateValue = UNSIGN;
					if (!S->relist[k].first)//若关联变量链表未创建
					{
						S->relist[k].VariateValue = -1;
						r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
						r->ClauseNum = i + a;
						r->next = NULL;
						S->relist[k].first = S->relist[k].last = r;
					}
					else//若关联变量链表已创建
					{
						r = (Word*)malloc(sizeof(Word));
						r->ClauseNum = i + a;
						r->next = NULL;
						S->relist[k].last->next = r;
						S->relist[k].last = r;
					}
					lnode = l;
					l->next = (Node*)malloc(sizeof(Node));
					l = l->next;
					s++;
				}
			}
			lnode->next = NULL;
			free(l);
			//S->list[i + a].UnsignedNum = s;
			S->list[i + a].VariateNum = s;
			S->list[i + a].s = 1;
			i++;
		} while (has(wp, n));

	}
		
	//以列为主序（负文字）
	for (h = 1; h <= n; h++)
	{
		if (h != 1)
		{
			for (j = 1; j <= n; j++)
			{
				wn[j].elem += 2;
				if (j <= n / 2 + 1) {
					wn[j].state = 1;
				}
				else {
					wn[j].state = 0;
				}
			}
		}
		do
		{
			s = 0;
			S->list[i + a].first = (Node*)malloc(sizeof(Node));
			l = S->list[i + a].first;
			for (j = 1; j <= n; j++)
			{
				if (wn[j].state)
				{
					k = wn[j].elem;
					l->Variate = k;
					l->VariateValue = UNSIGN;
					if (!S->relist[k].first)//若关联变量链表未创建
					{
						S->relist[k].VariateValue = -1;
						r = (Word*)malloc(sizeof(Word));//创建一个关联子句链表的结点
						r->ClauseNum = i + a;
						r->next = NULL;
						S->relist[k].first = S->relist[k].last = r;
					}
					else//若关联变量链表已创建
					{
						r = (Word*)malloc(sizeof(Word));
						r->ClauseNum = i + a;
						r->next = NULL;
						S->relist[k].last->next = r;
						S->relist[k].last = r;
					}
					lnode = l;
					l->next = (Node*)malloc(sizeof(Node));
					l = l->next;
					s++;
				}
			}
			lnode->next = NULL;
			free(l);
			//S->list[i + a].UnsignedNum = s;
			S->list[i + a].VariateNum = s;
			S->list[i + a].s = 1;
			i++;
		} while (has(wn, n));

	}
	

return OK;
}



