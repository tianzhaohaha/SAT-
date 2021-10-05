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
//MAX_NUM指子句集中子句数或文字数的最大数量
#define PL 11
//PL指数组的开辟的维数
#define SET_TIME 5
//SET_TIME是规定时间

typedef int Status;

typedef struct NewTable
{
	int elem;
	int state;
}NewTable;//用于生成组合
/* End of Data Type Define */
/****************************************************************************************/
/* Data Struct Define */

typedef struct Table
{
	int  Variate;//该变量的文字编号（无论正负）
	bool judge;//该变量是否为决策变量
	bool diverse;//该变量是否已经反转
}Table;//判断变量及其状态的三元组表

typedef struct Node
{
	int VariateValue;//子句链表中变量的取值，初始值赋值为-1
	int Variate;//子句链表中链表节点中的变量
	struct Node* next;//指向下一个子句链表表节点
} Node;//子句链表表结点结构类型

typedef struct Hnode
{
	int VariateNum;//子句链表中变量的数目
	int Sat;//子句链表中取值为1的变量的数目
	int Unsat;//子句链表中取值为0的变量的数目
	/*int UnsignedNum;//子句链表中没有赋值的变量的数目*/
	bool s;//表示子句是否被消隐，1表示存在，0表示消隐
	Node* first;//指向子句链表第一个表结点的指针

} Hnode;//子句链表表头节点结构类型

typedef struct Word
{
	int ClauseNum;//子句的序号，从1开始
	struct Word* next;//指向下一个变量关联链表表结点
} Word;//变量关联链表表结点结构类型

typedef struct HWord
{
	int col30;//该文字与子句集之间的相关系数（原始值,不做修改，在数独求解中用于判断该处是否有相应的变量）
	int VariateValue;//文字正负
	Word* first, * last;//分别指向变量关联链表第一个表结点和最后一个表结点
    int n=0;
} HWord; //变量关联链表表头结点结构类型

typedef struct SAT {
   int ClauseNum;//表示子句的数目
   int VariateNum;//表示变量的数目
   Hnode list[230000];//子句链表表头数组
   HWord relist[230000];//关联变量链表表头数组
   Table stack[230000];//判断变量及其状态的三元组表（栈）
   int top;//栈顶位置编号
   int num;//从栈顶到栈底的决策变量个数
}SAT;//整个SAT的两个邻接表及辅助存储空间

typedef struct SAT2 {
	int ClauseNum;//表示子句的数目
	int VariateNum;//表示变量的数目
	Hnode list[230000];//子句链表表头数组
	HWord relist[230000];//关联变量链表表头数组
	Table stack[230000];//判断变量及其状态的三元组表（栈）
	int top;//栈顶位置编号
	int num;//从栈顶到栈底的决策变量个数
	int n;//数独的阶数
	int puzzle[PL][PL];//求解使用的数独
}SAT2;//含数独的SAT存储空间
/* End of Data Struct Define */
void paixu(SAT *S);
int SelectVariate4(SAT* S);

/****************************************************************************************/
/*In The File "MATH.cpp" */
int cmn(int m, int n);//求n个中选m个的组合数函数
int Number5(int a, int b, int c, int d, int e);//求其对应的5位十进制数
int Number4(int a, int b, int c, int d);//求其对应的4位十进制数
int Number3(int a, int b, int c);//求其对应的3位十进制数
int PW(int i, int j, int n);//求格子对应正文字的函数
int NW(int i, int j, int n);//求格子对应负文字的函数
bool has(NewTable b[], int n);//选择组合的函数
int Verse(int x);//求文字对应的逆文字函数
void Cell(SAT2* S, int x, int* i, int* j);//求文字对应的格子坐标
int Trab(int x);//求出该文字的原变量的函数
/* End of File "MATH.cpp" */
/****************************************************************************************/
/* SAT of CNF */
Status Iniate(SAT** S);//整个数据结构的创建与初始化
Status Input(FILE* in, SAT *S);//从文件两个邻接表输入
Status deletel(SAT* S, int x);//去掉符合要求的子句
Status deletew(SAT* S, int x);//删除文字
int danzijuselect(SAT* S);//寻找单子句
Status deletec(SAT* S);//利用单子句规则化简子句集
int bianliangselect(SAT* S);//决策下一分支赋值变量（策略2）////////////!!!!!可优化
int JudgeClause(SAT* S,int i);//判断某个子句是否可满足
bool JudgeSATEmpty(SAT* S);//判断整个子句集是否为空
bool JudgeListEmpty(SAT* S);//判断整个子句集当中是否存在空子句
Status Solve1(SAT* S, FILE* in, int* t);//基于DPLL的SAT求解器主支函数（优化后）

Status CopyValue(SAT* S, int x);//赋值
Status ReCopyValue(SAT* S, int x);//反转赋值
Status InStack(SAT* S, int x, bool s);//入栈函数
Status OutStack(SAT* S);//出栈函数（带恢复赋值）
bool EmptyStack(SAT* S);//判断栈是否为空

Status Solve3(SAT* S, FILE* in, int* t);//基于DPLL的SAT求解器主支函数（优化前）
int SelectVariate3(SAT* S);//决策下一分支赋值变量（策略1）
/* End of CNF */
/****************************************************************************************/
/* SAT of BinaryPuzzle */
Status Iniate2(SAT2** S);//整个数据结构的创建与初始化
Status PuzzleInnital(SAT2* S);//初始化数独（内在逻辑，建立子句关系）
Status R1(SAT2* S, int a, int b);//规则一创建子句集
Status R2(SAT2* S, int a, int b);//规则二创建子句集
Status R3(SAT2* S, int a);//规则三创建子句集

Status DeleteList2(SAT2* S, int x);//去掉符合要求的子句
Status DeleteWord2(SAT2* S, int x);//删除文字
int SelectClause2(SAT2* S);//寻找单子句
Status DeleteClause2(SAT2* S);//利用单子句规则化简子句集
int SelectVariate2(SAT2* S);//决策下一分支赋值变量
bool JudgeSATEmpty2(SAT2* S);//判断整个子句集是否为空
bool JudgeListEmpty2(SAT2* S);//判断整个子句集当中是否存在空子句
bool Solve2(SAT2* S);//基于DPLL的SAT求解器主支函数
Status CopyValue2(SAT2* S, int x);//赋值
Status ReCopyValue2(SAT2* S, int x);//反转赋值
Status InStack2(SAT2* S, int x, bool s);//入栈函数
Status OutStack2(SAT2* S);//出栈函数（带恢复赋值）
bool EmptyStack2(SAT2* S);//判断栈是否为空

bool LasVegas(SAT2* S, int t);//拉斯维加斯算法生成随机数独
bool GenerateByDigMethod(int f[][PL], int n, int level);//从上到下、从左到右顺序挖洞
bool CheckUnique(int f[][PL], int n, int r, int c);//判断是否有唯一解
bool CheckSudokuSolution(int f[][PL], int n);//判断解是否正确（全部）
bool CheckSudokuSolution2(int f[][PL], int n, int i, int j, bool v);//判断解是否正确（局部）
Status PlayPuzzle(int f[][PL],int puzzle2[][PL], int n);//调用的数独玩耍程序
/* End of BinaryPuzzle */
/****************************************************************************************/
/* In The File "DFS.cpp" to use in BinaryPuzzle */
bool solve(int (*f)[PL], int n);//基于DFS数独求解函数（挖洞专用）
bool r1(int (*f)[PL], int n, int i, int j, bool v);//验证规则1是否满足
bool r2(int (*f)[PL], int n, int i, int j, bool v);//验证规则2是否满足
bool r3(int (*f)[PL], int n, int i, int j, bool v);//验证规则3是否满足
/* End of The File "DFS.cpp" to use in BinaryPuzzle */
/****************************************************************************************/
/* In The File "Print.cpp" */
Status PrintClause(SAT* S);//打印子句集
Status PrintWord(SAT* S, FILE* out, int s, int time);//打印关联变量链表
Status PrintPuzzle(int f[][PL], int n);//打印棋盘
Status PrintPuzToCNF(SAT2* S);//打印由数独归约生成的CNF子句集（文件在内部生成）
Status CopyPuzzle(int f[][PL], int b[][PL], int n);//复制数独棋盘
/* End of The File "Print.cpp" */
/****************************************************************************************/
/* In The File "New.cpp" */
Status ReCoverValue(SAT* S, int x);//仅对文字的链表进行恢复赋值（对CNF进行处理）
Status ReCoverValue2(SAT2* S, int x);//仅对文字的链表进行恢复赋值（对数独进行处理）
Status NewCopyValue(SAT2* S, int i, int j, bool v);//对该处进行赋值操作
Status NewReCoverValue(SAT2* S, int i, int j);//对该处进行恢复赋值操作
/* End of The File "New.cpp" */
/****************************************************************************************/
