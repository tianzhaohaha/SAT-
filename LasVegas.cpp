#include"pre-SAT.h"

bool LasVegas(SAT2* S, int t)//拉斯维加斯算法生成随机数独
{
	int n = S->n;
	int i = 0, j = 0, k = 0;
	for(i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			S->puzzle[i][j] = -1;
	
	while (t > 0)
	{
		i = rand() % n;
		j = rand() % n;
		//printf("%d %d\n", i, j);
		if ( i > 0 && i <= n && j > 0 && j <= n && S->puzzle[i][j] == -1)
		{
			k = (rand() % 10 + 1) % 2;
			//printf("%d\n", k);
			if (r1(S->puzzle, n, i, j, k) && r2(S->puzzle, n, i, j, k) && r3(S->puzzle, n, i, j, k))
			{
				//printf("%d\n", x);
				NewCopyValue(S, i, j, k);
				//PrintClause2(S);
				t--;
			}
		}
		//printf("%d\n", t);
	}
	//PrintClause2(S);
	if (Solve2(S)) return true;
	else return false;
}



