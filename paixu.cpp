#include"pre-SAT.h"

extern int AA[220002];
extern int BB[220002];
extern int selection;
void paixu(SAT *S)
{
    extern int AA[220002];
    extern int BB[220002];
    extern int selection;
    int i=1,j=1,max,maxpos;
    while(i<S->VariateNum)
    {
        AA[i]=S->relist[i].n;
    }
    i=1;
    max=AA[1],maxpos=1;
    for(i=S->VariateNum;i>0;i--) {
        for (j = 1; j<=i; j++) {
            if (AA[j] >= max) {
                max = AA[j];
                maxpos = j;
            }
        }
        BB[i]=maxpos;
        AA[maxpos]=0;
        max=AA[1];
        maxpos=1;
    }

}


int SelectVariate4(SAT* S)
{
    extern int AA[220002];
    extern int BB[220002];
    extern int selection;
    Node* t = NULL;
    Word * r = NULL;
    int x=0;
    paixu(S);
    t=S->list[S->relist[BB[selection]].first->ClauseNum].first;
    while(selection<=S->VariateNum) {
        while (t != NULL) {
            if (t->VariateValue == -1 && t->Variate == BB[selection]) {
                x = t->Variate;
                InStack(S, x, 1);//以决策变量入栈
                //printf("%d is Selected in clause %d !\n", x, i);
                return x;
            }
            t = t->next;
        }
        selection++;
        t=S->list[S->relist[BB[selection]].first->ClauseNum].first;
    }
    return x;
}
