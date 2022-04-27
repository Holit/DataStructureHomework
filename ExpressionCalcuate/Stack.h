#pragma once
#include "defs.h"

template<typename ElemType>
class Stack {};
#define STACK_INIT_SIZE 100     // 顺序栈存储空间的初始分配量
#define STACKINCREMENT  10      // 顺序栈存储空间的分配增量


//顺序栈
template <typename ElemType>
class SqStack
{
public:
	ElemType* base;               // 栈底指针
	ElemType* top;                // 栈顶指针
	int stacksize;                // 当前已分配的存储空间，以元素为单位
	
	SqStack()
	{
		InitStack();
	}
	~SqStack()
	{
		ClearStack();
		DestroyStack();
	}
	/// <summary>
	/// 创建新栈
	/// </summary>
	/// <returns>初始化成功则返回OK</returns>
	Status InitStack() {
		//申请空间
		base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType));
		memset(base, 0, STACK_INIT_SIZE * sizeof(ElemType));
		//对动态申请的空间进行溢出检查
		if (base == NULL) {
			exit(OVERFLOW);
		}

		top = base;
		stacksize = STACK_INIT_SIZE;

		return OK;
	}
	/// <summary>
	/// 销毁栈
	/// </summary>
	/// <returns>销毁成功则返回OK</returns>
	Status DestroyStack() {

		free(base);

		base = NULL;
		top = NULL;
		stacksize = 0;

		return OK;
	}
	/// <summary>
	/// 置空(内容)，只是清理顺序栈中存储的数据，不释放顺序栈所占内存。
	/// </summary>
	/// <returns>置空成功则返回OK，否则返回ERROR</returns>
	Status ClearStack() {
		if (base == NULL) {
			return ERROR;
		}

		top = base;

		return OK;
	}
	/// <summary>
	/// 判断顺序栈中是否包含有效数据。
	/// </summary>
	/// <returns>顺序栈为空则返回TRUE，否则返回FALSE。</returns>
	Status StackEmpty() {
		if (top == base) {
			return TRUE;
		}
		return FALSE;
	}
	/// <summary>
	/// 返回顺序栈包含的有效元素的数量。
	/// </summary>
	/// <returns>元素个数</returns>
	int StackLength() {
		if (base == NULL) {
			return 0;
		}
		//此处对指针进行加减并且按照
		return (int)(top - base) / sizeof(ElemType);
	}
	/// <summary>
	/// 返回栈顶元素
	/// </summary>
	/// <param name="e">接收元素</param>
	/// <returns>返回ERROR如果无法获取此元素，否则返回OK</returns>
	Status GetTop(ElemType& e) {
		if (base == NULL || top == base) {
			return ERROR;
		}

		// 不会改变栈中元素
		e = *(top - 1);

		return OK;
	}
	/// <summary>
	/// 将数据压入栈内
	/// </summary>
	/// <param name="e">欲压入的数据</param>
	/// <returns>返回OK，如果正确入栈。如果溢出将退出</returns>
	Status Push(ElemType e) {
		if (base == NULL) {
			return ERROR;
		}

		// 栈满时，追加存储空间
		if (top - base >= stacksize) {
			//按照STACKINCREMENT重分配空间
			base = (ElemType*)realloc(base, (stacksize + STACKINCREMENT) * sizeof(ElemType));
			if (base == NULL) {
				exit(OVERFLOW);     // 存储分配失败
			}

			top = base + stacksize;
			stacksize += STACKINCREMENT;
		}

		// 进栈先赋值，栈顶指针再自增
		*top = e;
		top++;

		return OK;
	}
	/// <summary>
	/// 将数据弹出栈
	/// </summary>
	/// <param name="e">接受弹出栈的元素</param>
	/// <returns></returns>
	Status Pop(ElemType& e) {
		if (base == NULL) {
			return ERROR;
		}

		if (top == base) {
			return ERROR;
		}
		// 出栈栈顶指针先递减，再赋值
		e = *(--top);

		return OK;
	}
	/// <summary>
	/// 遍历栈内元素
	/// </summary>
	/// <param name="visit">带有参数的遍历函数</param>
	/// <returns></returns>
	Status StackTraverse(void(*visit)(ElemType)) {
		ElemType* p = base;

		if (base == NULL) {
			return ERROR;
		}

		while (p < top) {
			visit(*p++);
		}
		return OK;
	}
};

//链式栈
//懒得实现，作为二周目实现条件（这条不能上交）
template <typename ElemType>
class LinkedStack : Stack<ElemType> {

};