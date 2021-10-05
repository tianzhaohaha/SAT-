#include"pre-SAT.h"

void question(int* m);//问一下“是否还要继续、是否需要显示当前填写情况、是否需要提示”的提示语
bool select(int* i, int* j, int *v);//数独填入项的选择函数
bool FullPuzzleOrnot(int f[][PL], int n);//查看数组是否已经填满

Status PlayPuzzle(int f[][PL],int puzzle2[][PL], int n)//调用的数独玩耍程序
{
	int p[PL][PL];//本游戏的游戏棋盘
	int i = 0, j = 0, k = 0, m = 0, a = 0, b = 0, v = 0;
	CopyPuzzle(f, p, n);//复制棋盘以保证游戏进行	
	
begin:	while (!FullPuzzleOrnot(p, n))
	    {
		    if (select(&i, &j, &v))
			    if (p[i][j] == -1) p[i][j] = v;
			    else { printf("非法输入!\n");  goto begin; }
		    else { printf("非法输入!\n"); goto begin;	}
		    question(&m);
			switch (m)
			{
			   case 1:  PrintPuzzle(p, n);  break;
			   case 2:  return ERROR; break;
			   case 0:  break;
			   default:  printf("非法输入!\n");  question(&m); break;
			}
	     }
       
      if(puzzle2[i][j]==p[i][j]) return OK;
	  else return ERROR;

}

void question(int* m)//问一下“是否还要继续、是否需要显示当前填写情况、是否需要提示”的提示语
{
	int t;
	printf("1.输出；2.答案；0.继续\n");
	t = scanf("%d", m);
}

bool select(int* i, int* j, int* v)//数独填入项的选择函数
{
	printf("请输入行，列与数值.\n");
	int a = scanf("%d%d%d", i, j, v);
	if (*v == 1 || *v == 0) return true;
	else return false;
}

bool FullPuzzleOrnot(int f[][PL], int n)//查看数组是否已经填满
{
	for(int i=1;i<=n;i++)
		for (int j = 1; j <= n; j++)
			if (f[i][j] == -1) return false;		
return true;
}



