#include"pre-SAT.h"

void welcome(int *op)
{
	int b;
	printf("\n��ӭʹ�ñ�ϵͳ��\n");
	printf("-------------------------------------------------------------\n");
	printf("ѡ���ܣ�\n");
	printf("0. Exit   1. SAT problem   2. Puzzle game \n");
	printf("-------------------------------------------------------------\n");
	printf("������: ");
	b=scanf("%d", op);
}

void after(void)
{
	char b;
	b=getchar(); 
	printf("\n�� enter ��������.\n");
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
	   case 1://CNF�����
	     {  
		   printf("�����ļ�·����.\n");
		   a = scanf("%s", c);
		   youhuaqian=fopen("D:\\SAT\\youhuaqian.res","w");
		   in1 = fopen(c, "r");//�ȶ�ȡ�����ļ�
		   in2 = fopen(c, "r");
		   strcpy(b, c);
		   l = strlen(b);
		   for (i = 1; i <= 3; i++)//�޸�����ļ��ĺ�׺��
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
		   state = Solve1(S, in1, &time1);//���õ�һ�������		   
		   if (state == 1) { printf("CNF �н�!\n");
               PrintWord(S, out, state, time1); }
		   else if (state == -1) 
		   { printf("�ļ��������г�ʱ.\n");
               PrintWord(S, out, state, time1); }
		   else { printf("CNF is FALSE!\n");
               PrintWord(S, out, state, time1); }
		   fclose(in1);
		   state = Solve3(S, in2, &time2);//���õڶ��������
             if (state == 1) { printf("CNF �н�!\n");
                 PrintWord(S, youhuaqian, state, time2); }
             else if (state == -1)
             {
                 printf("�ļ��������г�ʱ.\n");
                 PrintWord(S, youhuaqian, state, time2);
             }
             else { printf("CNF is FALSE!\n");
                 PrintWord(S, youhuaqian, state, time2); }
		   fclose(youhuaqian);
             PrintClause(S);
		   x = (double)time2 - (double)time1;
		   x = x / (double)time2 * 100 ;
		   printf("�Ż���Ϊ: %lf%%\n", x);
		   fclose(out);		   
		   free(S);
		   after();
		   for (j = 0; j < 401; j++) { c[j] = '\0'; b[j] = '\0'; }
		   break; 
	     }
           case 2://������������Ϸ
           {
               printf("���������̽���4��6��8: ");
               a = scanf("%d", &level);
               if (level == 4 || level == 6 || level == 8)
               {
                   printf("��ʼ1������0\n");
                   a = scanf("%d", &m);
                   if (!m) goto ops;
                   s = (SAT2*)malloc(sizeof(SAT2));
                   s->n = level;
                   PuzzleInnital(s);//��ʼ��������Ϣ��ֱ�ӽ����Ӿ䣩
                   if(level == 4)  state = LasVegas(s, 5);//��˹ά��˹�㷨��������
                   else state = LasVegas(s, 11);
                   if (!state) goto ops;
                   CopyPuzzle(s->puzzle, puzzle, s->n);
                   CopyPuzzle(s->puzzle, puzzle2, s->n);
                   printf("�� %d ������.\n", level * level);
                   printf("��ϣ�����ض��ٸ�����?\n������: ");
                   a = scanf("%d", &i);
                   if (GenerateByDigMethod(puzzle, s->n, i))
                   {
                       printf("���̽��� %d.\n", level);
                       again:
                       PrintPuzzle(puzzle, s->n);
                       if (PlayPuzzle(puzzle,puzzle2,s->n))//��һ������,�������else
                       {
                           printf("��ȷ!\n ");
                           free(s);
                           after();
                           break;
                       }
                       else//��Ļ�����Ҫ��
                       {
                           PrintPuzzle(s->puzzle, s->n);
                           printf("ʧ��.\n\n");
                           printf("��1��������0\n");
                           a = scanf("%d", &m);
                           if (m)  PrintPuzzle(s->puzzle, s->n);
                           printf("����1���˳�0\n");
                           scanf("%d",&m);
                           if (m)
                           {
                               system("cls");
                               printf("���̽��� %d.\n", level);
                               goto again;
                           }
                           printf("�˳��ɹ�");
                           free(s);
                           after();
                           break;
                       }
                   }
               }
               ops:	   printf("������\n");
               if (s) free(s);
               after();
               break;
           }
           case 0: //׼���˳�
           {
               printf("��ӭʹ�ñ�ϵͳ!\n");
               after();
               break;
           }
           default: //���벻�Ϸ�
           {
               printf("\n��������ȷ����!\n");
               after();
               break;
           }
       }//end of switch
    }//end of while

    return 0;
}
