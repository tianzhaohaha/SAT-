#include"pre-SAT.h"

void welcome(int *op)
{
	int b;
	printf("\n欢迎使用本系统！\n");
	printf("-------------------------------------------------------------\n");
	printf("选择功能：\n");
	printf("0. Exit   1. SAT problem   2. Puzzle game \n");
	printf("-------------------------------------------------------------\n");
	printf("请输入: ");
	b=scanf("%d", op);
}

void after(void)
{
	char b;
	b=getchar(); 
	printf("\n按 enter 键继续：.\n");
	b=getchar();
}



int main()
{
	int op = 1, a = 0, i = 0, state = 0, level = 0, j = 0, m = 0, l = 0, time1 = 0, time2 = 0;
	double x = 0;
	FILE* in1, *in2, * out,*youhuaqian;
	SAT* S = NULL;
	SAT2* s = NULL;
	int puzzle[PL][PL];
	int puzzle2[PL][PL];
	char c[401], b[401];
	for (j = 0; j < 401; j++) {	c[j] = '\0'; b[j] = '\0'; }
	while (op)
	{
	   system("cls");
	   welcome(&op);
	   switch (op)
	   {
	   case 1://CNF的求解
	     {  
		   printf("输入文件路径！.\n");
		   a = scanf("%s", c);
		   youhuaqian=fopen("D:\\SAT\\youhuaqian.res","w");
		   in1 = fopen(c, "r");//先读取输入文件
		   in2 = fopen(c, "r");
		   strcpy(b, c);
		   l = strlen(b);
		   for (i = 1; i <= 3; i++)//修改输出文件的后缀名
		   {
			   switch (i)
			   {
			      case 1: b[l - i] = 's'; break;
				  case 2: b[l - i] = 'e'; break;
				  case 3: b[l - i] = 'r'; break;
			   }
		   }
		   out = fopen(b, "w");
		   S = (SAT*)malloc(sizeof(SAT));
             PrintClause(S);
		   state = Solve1(S, in1, &time1);//调用第一个求解器		   
		   if (state == 1) { printf("CNF 有解!\n");
               PrintWord(S, out, state, time1); }
		   else if (state == -1) 
		   { printf("文件错误，运行超时.\n");
               PrintWord(S, out, state, time1); }
		   else { printf("CNF is FALSE!\n");
               PrintWord(S, out, state, time1); }
		   fclose(in1);
		   state = Solve3(S, in2, &time2);//调用第二个求解器
             if (state == 1) { printf("CNF 有解!\n");
                 PrintWord(S, youhuaqian, state, time2); }
             else if (state == -1)
             {
                 printf("文件错误，运行超时.\n");
                 PrintWord(S, youhuaqian, state, time2);
             }
             else { printf("CNF is FALSE!\n");
                 PrintWord(S, youhuaqian, state, time2); }
		   fclose(youhuaqian);
             PrintClause(S);
		   x = (double)time2 - (double)time1;
		   x = x / (double)time2 * 100 ;
		   printf("优化率为: %lf%%\n", x);
		   fclose(out);		   
		   free(S);
		   after();
		   for (j = 0; j < 401; j++) { c[j] = '\0'; b[j] = '\0'; }
		   break; 
	     }
           case 2://二进制数独游戏
           {
               printf("请输入棋盘阶数4，6，8: ");
               a = scanf("%d", &level);
               if (level == 4 || level == 6 || level == 8)
               {
                   printf("开始1，结束0\n");
                   a = scanf("%d", &m);
                   if (!m) goto ops;
                   s = (SAT2*)malloc(sizeof(SAT2));
                   s->n = level;
                   PuzzleInnital(s);//初始化棋盘信息（直接建立子句）
                   if(level == 4)  state = LasVegas(s, 5);//拉斯维加斯算法生成终盘
                   else state = LasVegas(s, 11);
                   if (!state) goto ops;
                   CopyPuzzle(s->puzzle, puzzle, s->n);
                   CopyPuzzle(s->puzzle, puzzle2, s->n);
                   printf("有 %d 个格子.\n", level * level);
                   printf("你希望隐藏多少个格子?\n请输入: ");
                   a = scanf("%d", &i);
                   if (GenerateByDigMethod(puzzle, s->n, i))
                   {
                       printf("棋盘阶数 %d.\n", level);
                       again:
                       PrintPuzzle(puzzle, s->n);
                       if (PlayPuzzle(puzzle,puzzle2,s->n))//玩一次棋盘,错误进入else
                       {
                           printf("正确!\n ");
                           free(s);
                           after();
                           break;
                       }
                       else//错的话可以要答案
                       {
                           PrintPuzzle(s->puzzle, s->n);
                           printf("失败.\n\n");
                           printf("答案1，继续：0\n");
                           a = scanf("%d", &m);
                           if (m)  PrintPuzzle(s->puzzle, s->n);
                           printf("重试1，退出0\n");
                           scanf("%d",&m);
                           if (m)
                           {
                               system("cls");
                               printf("棋盘阶数 %d.\n", level);
                               goto again;
                           }
                           printf("退出成功");
                           free(s);
                           after();
                           break;
                       }
                   }
               }
               ops:	   printf("结束。\n");
               if (s) free(s);
               after();
               break;
           }
           case 0: //准备退出
           {
               printf("欢迎使用本系统!\n");
               after();
               break;
           }
           default: //输入不合法
           {
               printf("\n请输入正确数字!\n");
               after();
               break;
           }
       }//end of switch
    }//end of while

    return 0;
}
