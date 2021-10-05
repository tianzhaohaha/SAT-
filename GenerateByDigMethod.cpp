#include"pre-SAT.h"

bool GenerateByDigMethod(int f[][PL], int n, int level)//从上到下、从左到右顺序挖洞
{//level为空格个数
	int i = 0, j = 0;

	//S->top = 0;//将栈顶指针进行初始化，以便进行恢复操作
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
		{
			if (!level) goto end;
			if (CheckUnique(f, n, i, j)) //判断是否有唯一解
			{				
				f[i][j] = -1;//挖去该格
				level--;
				PrintPuzzle(f, n);
			}			
		}

	if (level) printf("解不唯一！\n");
	else printf("解唯一！");

end: return true;
}
