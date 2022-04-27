
//等待二周目修正
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

*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include "defs.h"	//必要的参数声明，包括Status的声明。
#include "Stack.h"
//前缀、中缀、后缀表达式宏
#define PREFIX_EXPRESSION 0
#define INFIX_EXPRESSION 1
#define POSTFIX_EXPRESSION 2
/// <summary>
/// 判断字符的操作符优先级
/// </summary>
/// <param name="_operator">欲判断的字符</param>
/// <param name="expType">表达式类型，包括前缀、中缀、后缀表达式，分别为PREFIX_EXPRESSION, INFIX_EXPRESSION, POSTFIX_EXPRESSION</param>
/// <returns>
/// 返回优先等级：
/// 0：#  
/// 1：)   
/// 2： + -  
/// 3：*/%   
/// 4：(
/// -1:输入字符错误
/// </returns>
int getPriority(char _operator, int expType) { 
	if (expType == PREFIX_EXPRESSION || expType == INFIX_EXPRESSION) { 
		switch (_operator) {
		//前、中缀表达式和后缀表达式的唯一区别在于括号的匹配
		case '#':return 0;
		case ')':return 1;
		case '+':
		case '-':return 2;
		case '*':
		case '/':
		case '%':return 3;
		case '(':return 4;
		default:return -1;
		}
	}
	else if (expType == POSTFIX_EXPRESSION) {
		switch (_operator) {
		case '#':return 0;
		case '(':return 1;
		case '+':
		case '-':return 2;
		case '*':
		case '/':
		case '%':return 3;
		case ')':return 4;
		default:return -1;
		}
	}
}
/// <summary>
/// 处理局部运算，此处只支持整数有限运算
/// </summary>
/// <param name="_operator">运算符</param>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns>返回运算结果，如果超出范围或者发生错误，则返回ERROR</returns>
int calc(char _operator, int a, int b) {
	if (_operator == '+') { return b + a; }
	else if (_operator == '-') { return b - a; }
	else if (_operator == '*') { return b * a; }
	else if (_operator == '/') { return b / a; }
	else if (_operator == '%') { return b % a; }
	else { return ERROR; };
}


/// <summary>
/// 中缀表达式转为前缀表达式
/// </summary>
/// <param name="Infix">中缀表达式</param>
/// <param name="Prefix">存放前缀表达式</param>
/// <param name="len">中缀表达式长度</param>
void Infix2Prefix( char Infix[],  char Prefix[], int len) {
	SqStack<char> s;
	SqStack<char> pre;

	char e1 = 0, e2 = 0;
	s.Push('#');
	pre.Push('#');
	int m, n, cnt = 0;
	for (int i = len - 1; i >= 0; i--) {
		if (Infix[i] >= '0' && Infix[i] <= '9') {
			pre.Push(Infix[i]);
		}
		else if (Infix[i] == ')')
			s.Push(Infix[i]);
		else if (Infix[i] == '(') {
			while (!s.StackEmpty()) {
				s.Pop(e1);
				if (e1 == ')') break;
				else {
					pre.Push(e1);
				}
			}
		}
		else {
			pre.Push(' ');

			m = getPriority(Infix[i], PREFIX_EXPRESSION);
			s.GetTop(e1);
			n = getPriority(e1, PREFIX_EXPRESSION);
			while (m < n) {
				s.Pop(e2);
				pre.Push(e2);
				s.GetTop(e1);
				n = getPriority(e1, PREFIX_EXPRESSION);
			}
			s.Push(Infix[i]);
		}
	}
	while (!s.StackEmpty()) 
	{
		s.Pop(e2);
		pre.Push(e2);
	}
	pre.Pop(e2);
	while (!pre.StackEmpty()) {
		pre.Pop(e2);
		if (e2 == '#') { Prefix[cnt++] = 0; }
		else { Prefix[cnt++] = e2; };
	}
}
/// <summary>
/// 中缀表达式转为后缀表达式
/// </summary>
/// <param name="Infix">中缀表达式</param>
/// <param name="Prefix">存放后缀表达式</param>
/// <param name="len">中缀表达式长度</param>
void Infix2Postfix(char Infix[], char Postfix[], int len) {
	SqStack<char> s;
	char e1, e2;
	s.Push('#');
	int cnt = 0, m, n;
	for (int i = 0; i < len; i++) {
		if (Infix[i] >= '0' && Infix[i] <= '9') {
			Postfix[cnt++] = Infix[i];

		}
		else if (Infix[i] == '(')
			s.Push(Infix[i]);
		else if (Infix[i] == ')') {
			while (!s.StackEmpty()) {
				s.Pop(e1);
				if (e1 == '(') break;
				else {
					Postfix[cnt++] = e1;

				}
			}
		}
		else {
			Postfix[cnt++] = ' ';
			m = getPriority(Infix[i], POSTFIX_EXPRESSION);
			s.GetTop(e1);
			n = getPriority(e1, POSTFIX_EXPRESSION);
			while (m <= n) {
				s.Pop(e2);
				Postfix[cnt++] = e2;

				s.GetTop(e1);
				n = getPriority(e1, POSTFIX_EXPRESSION);
			}
			s.Push(Infix[i]);
		}
	}
	while (!s.StackEmpty()) {
		s.Pop(e2);
		if (e2 == '#') { Postfix[cnt++] = 0; };
		Postfix[cnt++] = e2;
	}
}

/// <summary>
/// 处理中缀表达式
/// </summary>
/// <param name="Infix">要处理的表达式</param>
/// <param name="len">表达式长度</param>
/// <returns>结果</returns>
int Infix(char Infix[], int len) {
	printf("%s", Infix);
	//Stack OPTR, OPND, middle;//middle用来处理多位数 
	char result = 0, e = 0, e1 = 0, e2 = 0;
	int digit_num, ans = 0;
	SqStack<char> OPTR;
	SqStack<char> OPND;
	SqStack<char> middle;

	OPTR.Push('#');
	int m, n;
	for (int i = 0; i < len; i++) {
		if (Infix[i] == ' ')
		{
			continue;
		}
		if (Infix[i] >= '0' && Infix[i] <= '9') {
			middle.Push(Infix[i]);
			if (Infix[i + 1] >= '0' && Infix[i + 1] <= '9')
				continue;
			digit_num = 1;
			result = 0;
			while (!middle.StackEmpty()) {   //多位数的处理 
				middle.Pop(e1);

				result += (e1 - '0') * digit_num;
				digit_num = digit_num * 10;
			}
			OPND.Push(result);
		}
		else {
			m = getPriority(Infix[i], INFIX_EXPRESSION);
			OPTR.GetTop(e1);
			n = getPriority(e1, INFIX_EXPRESSION);
			if (n == 4) {
				OPTR.Push(Infix[i]);
				continue;
			}
			while (m <= n) {
				OPTR.Pop(e);
				if (e == '(' && Infix[i] == ')') break;
				else if (e == '+' || e == '-' || e == '*' || e == '/' || e == '%') {
					OPND.Pop(e1);
					OPND.Pop(e2);
					ans = calc(e, e1, e2);
					OPND.Push(ans);
				}
				OPTR.GetTop(e1);
				n = getPriority(e1, INFIX_EXPRESSION);
			}
			if (Infix[i] != ')')
				OPTR.Push(Infix[i]);
		}
	}
	while (!OPTR.StackEmpty()) {
		OPTR.GetTop(e);
		if (e == '#') break;
		else {
			OPTR.Pop(e1);
			OPND.Pop(e1);
			OPND.Pop(e2);
			ans = calc(e, e1, e2);
			OPND.Push(ans);
		}
	}
	OPND.Pop(e);

	return e;
}
/// <summary>
/// 处理前缀表达式
/// </summary>
/// <param name="Prefix">前缀表达式</param>
/// <param name="len">表达式长度</param>
/// <returns></returns>
int Prefix(char Prefix[], int len) {
	SqStack<char> s, pre;

	char result = 0, e, e1, e2;
	int digit_num, ans = 0;
	s.InitStack();
	pre.InitStack();
	int i = 0;
	for (i = len + 20; i >= 0; i--) { //转前缀时中间加了空格
		if (Prefix[i] >= '0' && Prefix[i] <= '9') {
			pre.Push(Prefix[i]);
			if (Prefix[i - 1] >= '0' && Prefix[i - 1] <= '9') continue;
			result = 0;
			digit_num = 1;
			while (!pre.StackEmpty()) { //并转换位数
				pre.Pop(e1);
				result += (e1 - '0') * digit_num;
				digit_num = digit_num * 10;
			}
			s.Push(result);
		}
		else if (Prefix[i] == '+' || Prefix[i] == '-' || Prefix[i] == '*' || Prefix[i] == '/' || Prefix[i] == '%') {
			s.Pop(e2);
			s.Pop(e1);
			ans = calc(Prefix[i], e1, e2);//计算结果并压回栈中 
			s.Push(ans);
		}
	}
	s.Pop(e);
	return e;
}
/// <summary>
/// 处理后缀表达式
/// </summary>
/// <param name="Prefix">后缀表达式</param>
/// <param name="len">表达式长度</param>
/// <returns></returns>
int Postfix(char Postfix[], int len) {
	SqStack<char> s, post;
	int ans = 0;
	char result = 0, e, e1, e2;
	int digit_num;
	s.InitStack();
	post.InitStack();

	for (int i = 0; i < len + 3; i++) {
		if (Postfix[i] >= '0' && Postfix[i] <= '9') {
			digit_num = 1;
			post.Push(Postfix[i]);
			if (Postfix[i + 1] >= '0' && Postfix[i + 1] <= '9') continue;
			result = 0;
			while (!post.StackEmpty()) {
				post.Pop(e1);
				result += (e1 - '0') * digit_num;
				digit_num = digit_num * 10;
			}
			s.Push(result);
		}
		else if (Postfix[i] == '+' || Postfix[i] == '-' || Postfix[i] == '*' || Postfix[i] == '/' || Postfix[i] == '%') {
			s.Pop(e1);
			s.Pop(e2);
			ans = calc(Postfix[i], e1, e2);
			s.Push(ans);
		}
	}
	s.Pop(e);
	return e;
}

#define n 100		//最大表达式长度

char Mid[n] = { 0 };
char  Post[n] = { 0 };
char Pre[n] = { 0 };//存储中缀，后缀，前缀表达式

int main(int argc, char **argv) {
	int i = 0, len = 0;
	printf("请输入合理的中缀表达式：");
	if(!scanf("%[^\n]", Mid))return ERROR;	//读取到换行符，发生错误则退出
	len = strlen(Mid);

	int e = Infix(Mid, len);
	printf("\n中缀的结果为:%d", e);

	Infix2Prefix(Mid, Pre, len);
	printf("\n前缀表达式为:%s",Pre);

	e = Prefix(Pre, len);

	printf("\n前缀的结果为:%d", e);
	Infix2Postfix(Mid, Post, len);

	printf("\n后缀表达式为:%s",Post);

	e= Postfix(Post, len);
	printf("\n后缀的结果为:%d", e);

	return 0;
}
