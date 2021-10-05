#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

/* Data Type Define */
#define OK 1 
#define ERROR 0
#define UNSIGN -1
#define MAXNUM 230000
//MAX_NUMָ�Ӿ伯���Ӿ��������������������
#define PL 11
//PLָ����Ŀ��ٵ�ά��
#define SET_TIME 5
//SET_TIME�ǹ涨ʱ��

typedef int Status;

typedef struct NewTable
{
	int elem;
	int state;
}NewTable;//�����������
/* End of Data Type Define */
/****************************************************************************************/
/* Data Struct Define */

typedef struct Table
{
	int  Variate;//�ñ��������ֱ�ţ�����������
	bool judge;//�ñ����Ƿ�Ϊ���߱���
	bool diverse;//�ñ����Ƿ��Ѿ���ת
}Table;//�жϱ�������״̬����Ԫ���

typedef struct Node
{
	int VariateValue;//�Ӿ������б�����ȡֵ����ʼֵ��ֵΪ-1
	int Variate;//�Ӿ�����������ڵ��еı���
	struct Node* next;//ָ����һ���Ӿ������ڵ�
} Node;//�Ӿ��������ṹ����

typedef struct Hnode
{
	int VariateNum;//�Ӿ������б�������Ŀ
	int Sat;//�Ӿ�������ȡֵΪ1�ı�������Ŀ
	int Unsat;//�Ӿ�������ȡֵΪ0�ı�������Ŀ
	/*int UnsignedNum;//�Ӿ�������û�и�ֵ�ı�������Ŀ*/
	bool s;//��ʾ�Ӿ��Ƿ�������1��ʾ���ڣ�0��ʾ����
	Node* first;//ָ���Ӿ������һ�������ָ��

} Hnode;//�Ӿ������ͷ�ڵ�ṹ����

typedef struct Word
{
	int ClauseNum;//�Ӿ����ţ���1��ʼ
	struct Word* next;//ָ����һ�����������������
} Word;//���������������ṹ����

typedef struct HWord
{
	int col30;//���������Ӿ伯֮������ϵ����ԭʼֵ,�����޸ģ�����������������жϸô��Ƿ�����Ӧ�ı�����
	int VariateValue;//��������
	Word* first, * last;//�ֱ�ָ��������������һ����������һ������
    int n=0;
} HWord; //�������������ͷ���ṹ����

typedef struct SAT {
   int ClauseNum;//��ʾ�Ӿ����Ŀ
   int VariateNum;//��ʾ��������Ŀ
   Hnode list[230000];//�Ӿ������ͷ����
   HWord relist[230000];//�������������ͷ����
   Table stack[230000];//�жϱ�������״̬����Ԫ���ջ��
   int top;//ջ��λ�ñ��
   int num;//��ջ����ջ�׵ľ��߱�������
}SAT;//����SAT�������ڽӱ������洢�ռ�

typedef struct SAT2 {
	int ClauseNum;//��ʾ�Ӿ����Ŀ
	int VariateNum;//��ʾ��������Ŀ
	Hnode list[230000];//�Ӿ������ͷ����
	HWord relist[230000];//�������������ͷ����
	Table stack[230000];//�жϱ�������״̬����Ԫ���ջ��
	int top;//ջ��λ�ñ��
	int num;//��ջ����ջ�׵ľ��߱�������
	int n;//�����Ľ���
	int puzzle[PL][PL];//���ʹ�õ�����
}SAT2;//��������SAT�洢�ռ�
/* End of Data Struct Define */
void paixu(SAT *S);
int SelectVariate4(SAT* S);

/****************************************************************************************/
/*In The File "MATH.cpp" */
int cmn(int m, int n);//��n����ѡm�������������
int Number5(int a, int b, int c, int d, int e);//�����Ӧ��5λʮ������
int Number4(int a, int b, int c, int d);//�����Ӧ��4λʮ������
int Number3(int a, int b, int c);//�����Ӧ��3λʮ������
int PW(int i, int j, int n);//����Ӷ�Ӧ�����ֵĺ���
int NW(int i, int j, int n);//����Ӷ�Ӧ�����ֵĺ���
bool has(NewTable b[], int n);//ѡ����ϵĺ���
int Verse(int x);//�����ֶ�Ӧ�������ֺ���
void Cell(SAT2* S, int x, int* i, int* j);//�����ֶ�Ӧ�ĸ�������
int Trab(int x);//��������ֵ�ԭ�����ĺ���
/* End of File "MATH.cpp" */
/****************************************************************************************/
/* SAT of CNF */
Status Iniate(SAT** S);//�������ݽṹ�Ĵ������ʼ��
Status Input(FILE* in, SAT *S);//���ļ������ڽӱ�����
Status deletel(SAT* S, int x);//ȥ������Ҫ����Ӿ�
Status deletew(SAT* S, int x);//ɾ������
int danzijuselect(SAT* S);//Ѱ�ҵ��Ӿ�
Status deletec(SAT* S);//���õ��Ӿ���򻯼��Ӿ伯
int bianliangselect(SAT* S);//������һ��֧��ֵ����������2��////////////!!!!!���Ż�
int JudgeClause(SAT* S,int i);//�ж�ĳ���Ӿ��Ƿ������
bool JudgeSATEmpty(SAT* S);//�ж������Ӿ伯�Ƿ�Ϊ��
bool JudgeListEmpty(SAT* S);//�ж������Ӿ伯�����Ƿ���ڿ��Ӿ�
Status Solve1(SAT* S, FILE* in, int* t);//����DPLL��SAT�������֧�������Ż���

Status CopyValue(SAT* S, int x);//��ֵ
Status ReCopyValue(SAT* S, int x);//��ת��ֵ
Status InStack(SAT* S, int x, bool s);//��ջ����
Status OutStack(SAT* S);//��ջ���������ָ���ֵ��
bool EmptyStack(SAT* S);//�ж�ջ�Ƿ�Ϊ��

Status Solve3(SAT* S, FILE* in, int* t);//����DPLL��SAT�������֧�������Ż�ǰ��
int SelectVariate3(SAT* S);//������һ��֧��ֵ����������1��
/* End of CNF */
/****************************************************************************************/
/* SAT of BinaryPuzzle */
Status Iniate2(SAT2** S);//�������ݽṹ�Ĵ������ʼ��
Status PuzzleInnital(SAT2* S);//��ʼ�������������߼��������Ӿ��ϵ��
Status R1(SAT2* S, int a, int b);//����һ�����Ӿ伯
Status R2(SAT2* S, int a, int b);//����������Ӿ伯
Status R3(SAT2* S, int a);//�����������Ӿ伯

Status DeleteList2(SAT2* S, int x);//ȥ������Ҫ����Ӿ�
Status DeleteWord2(SAT2* S, int x);//ɾ������
int SelectClause2(SAT2* S);//Ѱ�ҵ��Ӿ�
Status DeleteClause2(SAT2* S);//���õ��Ӿ���򻯼��Ӿ伯
int SelectVariate2(SAT2* S);//������һ��֧��ֵ����
bool JudgeSATEmpty2(SAT2* S);//�ж������Ӿ伯�Ƿ�Ϊ��
bool JudgeListEmpty2(SAT2* S);//�ж������Ӿ伯�����Ƿ���ڿ��Ӿ�
bool Solve2(SAT2* S);//����DPLL��SAT�������֧����
Status CopyValue2(SAT2* S, int x);//��ֵ
Status ReCopyValue2(SAT2* S, int x);//��ת��ֵ
Status InStack2(SAT2* S, int x, bool s);//��ջ����
Status OutStack2(SAT2* S);//��ջ���������ָ���ֵ��
bool EmptyStack2(SAT2* S);//�ж�ջ�Ƿ�Ϊ��

bool LasVegas(SAT2* S, int t);//��˹ά��˹�㷨�����������
bool GenerateByDigMethod(int f[][PL], int n, int level);//���ϵ��¡�������˳���ڶ�
bool CheckUnique(int f[][PL], int n, int r, int c);//�ж��Ƿ���Ψһ��
bool CheckSudokuSolution(int f[][PL], int n);//�жϽ��Ƿ���ȷ��ȫ����
bool CheckSudokuSolution2(int f[][PL], int n, int i, int j, bool v);//�жϽ��Ƿ���ȷ���ֲ���
Status PlayPuzzle(int f[][PL],int puzzle2[][PL], int n);//���õ�������ˣ����
/* End of BinaryPuzzle */
/****************************************************************************************/
/* In The File "DFS.cpp" to use in BinaryPuzzle */
bool solve(int (*f)[PL], int n);//����DFS������⺯�����ڶ�ר�ã�
bool r1(int (*f)[PL], int n, int i, int j, bool v);//��֤����1�Ƿ�����
bool r2(int (*f)[PL], int n, int i, int j, bool v);//��֤����2�Ƿ�����
bool r3(int (*f)[PL], int n, int i, int j, bool v);//��֤����3�Ƿ�����
/* End of The File "DFS.cpp" to use in BinaryPuzzle */
/****************************************************************************************/
/* In The File "Print.cpp" */
Status PrintClause(SAT* S);//��ӡ�Ӿ伯
Status PrintWord(SAT* S, FILE* out, int s, int time);//��ӡ������������
Status PrintPuzzle(int f[][PL], int n);//��ӡ����
Status PrintPuzToCNF(SAT2* S);//��ӡ��������Լ���ɵ�CNF�Ӿ伯���ļ����ڲ����ɣ�
Status CopyPuzzle(int f[][PL], int b[][PL], int n);//������������
/* End of The File "Print.cpp" */
/****************************************************************************************/
/* In The File "New.cpp" */
Status ReCoverValue(SAT* S, int x);//�������ֵ�������лָ���ֵ����CNF���д���
Status ReCoverValue2(SAT2* S, int x);//�������ֵ�������лָ���ֵ�����������д���
Status NewCopyValue(SAT2* S, int i, int j, bool v);//�Ըô����и�ֵ����
Status NewReCoverValue(SAT2* S, int i, int j);//�Ըô����лָ���ֵ����
/* End of The File "New.cpp" */
/****************************************************************************************/
