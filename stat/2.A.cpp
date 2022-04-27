//2.A.cpp
//
//数据结构与程序设计实验
//
//实验2 A档实验
//作者：Jerry Gao
//请联系gao1021229073@163.com反馈漏洞和bug
//
//要启用此文件，请取消下述Experiment_2_A_Enabled的注释
//注意：一次只能启用一个实验文件进行编译
//#define Experiment_2_A_Enabled
//固定编译头，勿更改
#ifdef Experiment_2_A_Enabled
	#ifndef _main_
		#define _main_ main
	#else
		#error "函数名冲突：启用了两个或以上的实验源代码文件"
	#endif
#endif // !Experiment_2_A_Enabled
#include "defs.h" 
/*
* （1）表达式求值问题
* 问题描述
* 表达式是数据运算的基本形式。人们的书写习惯是中缀式，如：
* 11+22*(7-4)/3。中缀式的计算按运算符的优先级及括号优先的原则，相同级别从
* 左到右进行计算。表达式还有后缀式（如：22 7 4 - * 3 / 11 +）和前缀式（如：+
* 11 / * 22 – 7 4 3）。后缀表达式和前缀表达式中没有括号，给计算带来方便。如
* 后缀式计算时按运算符出现的先后进行计算。本设计的主要任务是进行表达式形
* 式的转换及不同形式的表达式计算。
* ②基本要求
* -  从文件或键盘读入中缀表达式。
* -  设计操作数为多位整数，操作符为加、减、乘、除、求模的中缀表达式
* 求值算法。
* -  设计将中缀表达式转换为后缀表达式的算法。
* -  设计将中缀表达式转换为前缀表达式的算法。
* -  设计后缀表达式求值算法。
* -  设计前缀表达式求值算法。
* -  输出各种形式的表达式。
* （2）任务调度
* ①问题描述
* 多用户多任务操作系统中，多个任务同时共享计算机系统资源。为了使多个
* 任务均能够顺利执行，操作系统要按一定的原则对它们进行调度，使它们按一定
* 的次序进行。设只有一个 CPU，现有多个任务，它们需要 CPU 服务的时间已知。
* 在下列假设下，按平均等待时间最短为原则，设计算法求出任务的执行顺序。
* -  忽略任务提交的时间差，即认为各任务同时提交。
* -  各任务不同时提交。
* ②基本要求
* -  为任务列表设计数据结构和存储结构。
* -  任务输入，至少包括任务编号及所需 CPU 的服务时间，任务数不得少
* 于 5 个。
* -  如果按提交顺序执行，求出每个任务的开始执行时间、终止时间、等待
* 时间和所有任务的平均等待时间。
* -  按平均等待时间最短，设计任务调度算法，输出任务的执行序列；求出
* 每个任务的开始执行时间、终止时间、等待时间和所有任务的平均等待
* 时间；并把结果与上一时间对比。
* ③思考
* -  最短作业优先，存在“长任务饥饿”的问题，即如果动态地不断加入作
* 业，只要提交作业所需要的 CPU 服务时间比较短，则先提交的长任务
* 将一直得不到服务，如何解决该问题？

*/
#include "datastructure.h"
//此处完成表达式求值问题

#include<stdio.h>
#include<stdlib.h>
#include<cstring>

#define Status int
#define Elemtype char
#define OK 1
#define ERROR 0

#define INIT_SIZE 100
#define INCREASEMENT 10
#define MAX 100

char Mid[MAX], Post[MAX], Pre[MAX];//存储中缀，后缀，前缀表达式

typedef struct {//顺序栈
	Elemtype* base;
	Elemtype* top;
	int stacksize;
} Stack;


int InitStack(Stack& S) { //初始化栈
	S.base = (Elemtype*)malloc(sizeof(Elemtype));
	if (!S.base)
		exit(-2);
	S.top = S.base;
	S.stacksize = INIT_SIZE;
	return OK;
}
int Push(Stack& S, Elemtype e) { //压栈
	if (S.top - S.base >= S.stacksize) { //栈满动态申请
		S.base = (Elemtype*)realloc(S.base, (S.stacksize + INCREASEMENT) * sizeof(Elemtype));
		if (!S.base)
			exit(-2);
		S.top = S.base + S.stacksize;
		S.stacksize += INCREASEMENT;
	}
	*S.top++ = e;
	return OK;
}
int Pop(Stack& S, Elemtype& e) {
	if (S.top == S.base) {
		return ERROR;
	}
	e = *(S.top - 1);
	S.top--;
	return OK;
}
int Is_empty(Stack S) { //判断栈是否为空
	if (S.top == S.base)
		return 1;
	else
		return 0;
}
int GetTop(Stack S, Elemtype& e) { //获取栈顶元素
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1);
	return OK;
}

int Priority(char e, char type) { //返回优先等级 0：#  1：)   2： + -  3：*/%   4：(
	if (type == 'F' || type == 'M') { //F代表前缀 M代表中缀 L代表后缀
		switch (e) {
		case '#':
			return 0;
			break;
		case ')':
			return 1;
			break;
		case '+':
		case '-':
			return 2;
			break;
		case '*':
		case '/':
		case '%':
			return 3;
			break;
		case '(':
			return 4;
			break;
		default:
			printf("运算符不正确!");
			system("pause");
			return -1;
			break;
		}
	}
	else if (type == 'L') {
		switch (e) {
		case '#':
			return 0;
			break;
		case '(':
			return 1;
			break;
		case '+':
		case '-':
			return 2;
			break;
		case '*':
		case '/':
		case '%':
			return 3;
			break;
		case ')':
			return 4;
			break;
		default:
			printf("运算符不正确!");
			system("pause");
			return -1;
			break;
		}
	}
}
int Operate(char sign, int e1, int e2) {
	int result;
	if (sign == '+') {
		result = e2 + e1;
	}
	else if (sign == '-') {
		result = e2 - e1;
	}
	else if (sign == '*') {
		result = e2 * e1;
	}
	else if (sign == '/') {
		result = e2 / e1;

	}
	else if (sign == '%') {
		result = e2 % e1;

	}
	return result;
}

void MidCount(char Mid[], int len) {
	Stack OPTR, OPND, middle;//middle用来处理多位数 
	char result = 0, e, e1, e2;
	int digit_num, ans = 0;
	InitStack(OPTR);
	InitStack(OPND);
	InitStack(middle);
	Push(OPTR, '#');
	int m, n;
	for (int i = 0; i < len; i++) {
		if (Mid[i] >= '0' && Mid[i] <= '9') {
			Push(middle, Mid[i]);
			if (Mid[i + 1] >= '0' && Mid[i + 1] <= '9')
				continue;
			digit_num = 1;
			result = 0;
			while (!Is_empty(middle)) {   //多位数的处理 
				Pop(middle, e1);
				result += (e1 - '0') * digit_num;
				digit_num = digit_num * 10;
			}
			Push(OPND, result);
		}
		else {
			m = Priority(Mid[i], 'M');
			GetTop(OPTR, e1);
			n = Priority(e1, 'M');
			if (n == 4) {
				Push(OPTR, Mid[i]);
				continue;
			}
			while (m <= n) {
				Pop(OPTR, e);
				if (e == '(' && Mid[i] == ')') break;
				else if (e == '+' || e == '-' || e == '*' || e == '/' || e == '%') {
					Pop(OPND, e1);
					Pop(OPND, e2);
					ans = Operate(e, e1, e2);
					Push(OPND, ans);
				}
				GetTop(OPTR, e1);
				n = Priority(e1, 'M');
			}
			if (Mid[i] != ')')
				Push(OPTR, Mid[i]);
		}
	}
	while (!Is_empty(OPTR)) {
		GetTop(OPTR, e);
		if (e == '#') break;
		else {
			Pop(OPTR, e);
			Pop(OPND, e1);
			Pop(OPND, e2);
			ans = Operate(e, e1, e2);
			Push(OPND, ans);
		}
	}
	Pop(OPND, e);
	printf("\n中缀的结果为:%d", e);
}
void TransferPre(char Mid[], char Pre[], int len) {
	Stack s, pre;
	char e1, e2;
	InitStack(s);
	InitStack(pre);
	Push(s, '#');
	Push(pre, '#');
	int m, n, cnt = 0;
	for (int i = len - 1; i >= 0; i--) {
		if (Mid[i] >= '0' && Mid[i] <= '9') {
			Push(pre, Mid[i]);
		}
		else if (Mid[i] == ')')
			Push(s, Mid[i]);
		else if (Mid[i] == '(') {
			while (!Is_empty(s)) {
				Pop(s, e1);
				if (e1 == ')') break;
				else {
					Push(pre, e1);
				}
			}
		}
		else {
			Push(pre, ' ');

			m = Priority(Mid[i], 'F');
			GetTop(s, e1);
			n = Priority(e1, 'F');
			while (m < n) {
				Pop(s, e2);
				Push(pre, e2);
				GetTop(s, e1);
				n = Priority(e1, 'F');
			}
			Push(s, Mid[i]);
		}
	}
	while (!Is_empty(s)) {

		Pop(s, e2);
		Push(pre, e2);
	}
	Pop(pre, e2);
	while (!Is_empty(pre)) {
		Pop(pre, e2);
		Pre[cnt++] = e2;
	}
}
void TransferPost(char Mid[], char Post[], int  len) {
	Stack s;
	char e1, e2;
	InitStack(s);
	Push(s, '#');
	int cnt = 0, m, n;
	for (int i = 0; i < len; i++) {
		if (Mid[i] >= '0' && Mid[i] <= '9') {
			Post[cnt++] = Mid[i];

		}
		else if (Mid[i] == '(')
			Push(s, Mid[i]);
		else if (Mid[i] == ')') {
			while (!Is_empty(s)) {
				Pop(s, e1);
				if (e1 == '(') break;
				else {
					Post[cnt++] = e1;

				}
			}
		}
		else {
			Post[cnt++] = ' ';
			m = Priority(Mid[i], 'L');
			GetTop(s, e1);
			n = Priority(e1, 'L');
			while (m <= n) {
				Pop(s, e2);
				Post[cnt++] = e2;

				GetTop(s, e1);
				n = Priority(e1, 'L');
			}
			Push(s, Mid[i]);
		}
	}
	while (!Is_empty(s)) {
		Pop(s, e2);
		Post[cnt++] = e2;
	}
}
void PreCount(char Pre[], int len) {
	Stack s, pre;
	char result = 0, e, e1, e2;
	int digit_num, ans = 0;
	InitStack(s);
	InitStack(pre);
	int i = 0;
	for (i = len + 20; i >= 0; i--) { //转前缀时中间加了空格
		if (Pre[i] >= '0' && Pre[i] <= '9') {
			Push(pre, Pre[i]);
			if (Pre[i - 1] >= '0' && Pre[i - 1] <= '9') continue;
			result = 0;
			digit_num = 1;
			while (!Is_empty(pre)) { //并转换位数
				Pop(pre, e1);
				result += (e1 - '0') * digit_num;
				digit_num = digit_num * 10;
			}
			Push(s, result);
		}
		else if (Pre[i] == '+' || Pre[i] == '-' || Pre[i] == '*' || Pre[i] == '/' || Pre[i] == '%') {
			Pop(s, e2);//取出一对数字
			Pop(s, e1);
			ans = Operate(Pre[i], e1, e2);//计算结果并压回栈中 
			Push(s, ans);
		}
	}
	Pop(s, e);//最终计算结果
	printf("\n前缀的结果为:%d", e);
}
void PostCount(char Post[], int len) {
	Stack s, post;
	int ans = 0;
	char result = 0, e, e1, e2;
	int digit_num;
	InitStack(s);
	InitStack(post);

	for (int i = 0; i < len + 3; i++) {
		if (Post[i] >= '0' && Post[i] <= '9') {
			digit_num = 1;
			Push(post, Post[i]);
			if (Post[i + 1] >= '0' && Post[i + 1] <= '9') continue;
			result = 0;
			while (!Is_empty(post)) {
				Pop(post, e1);
				result += (e1 - '0') * digit_num;
				digit_num = digit_num * 10;
			}
			Push(s, result);
		}
		else if (Post[i] == '+' || Post[i] == '-' || Post[i] == '*' || Post[i] == '/' || Post[i] == '%') {
			Pop(s, e1);
			Pop(s, e2);
			ans = Operate(Post[i], e1, e2);
			Push(s, ans);
		}
	}
	Pop(s, e);
	printf("\n后缀的结果为:%d", e);
}



int main() {
	int i = 0, len = 0;
	printf("请输入合理的中缀表达式：");
	scanf("%s", Mid);
	for (i = 0; i < MAX; i++) {
		if (Mid[i] == 0)
			break;
		len++;
	}
	MidCount(Mid, len);
	TransferPre(Mid, Pre, len);
	printf("\n前缀表达式为:");
	for (i = 0;; i++) {
		if (Pre[i] == '#') break;
		printf("%c", Pre[i]);
	}
	PreCount(Pre, len);
	TransferPost(Mid, Post, len);
	printf("\n后缀表达式为:");
	for (i = 0;; i++) {
		if (Post[i] == '#') break;
		printf("%c", Post[i]);
	}
	PostCount(Post, len);
	return 0;
}
