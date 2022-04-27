#pragma once
#include "defs.h"

template<typename ElemType>
class Stack {};
#define STACK_INIT_SIZE 100     // ˳��ջ�洢�ռ�ĳ�ʼ������
#define STACKINCREMENT  10      // ˳��ջ�洢�ռ�ķ�������


//˳��ջ
template <typename ElemType>
class SqStack
{
public:
	ElemType* base;               // ջ��ָ��
	ElemType* top;                // ջ��ָ��
	int stacksize;                // ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
	
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
	/// ������ջ
	/// </summary>
	/// <returns>��ʼ���ɹ��򷵻�OK</returns>
	Status InitStack() {
		//����ռ�
		base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType));
		memset(base, 0, STACK_INIT_SIZE * sizeof(ElemType));
		//�Զ�̬����Ŀռ����������
		if (base == NULL) {
			exit(OVERFLOW);
		}

		top = base;
		stacksize = STACK_INIT_SIZE;

		return OK;
	}
	/// <summary>
	/// ����ջ
	/// </summary>
	/// <returns>���ٳɹ��򷵻�OK</returns>
	Status DestroyStack() {

		free(base);

		base = NULL;
		top = NULL;
		stacksize = 0;

		return OK;
	}
	/// <summary>
	/// �ÿ�(����)��ֻ������˳��ջ�д洢�����ݣ����ͷ�˳��ջ��ռ�ڴ档
	/// </summary>
	/// <returns>�ÿճɹ��򷵻�OK�����򷵻�ERROR</returns>
	Status ClearStack() {
		if (base == NULL) {
			return ERROR;
		}

		top = base;

		return OK;
	}
	/// <summary>
	/// �ж�˳��ջ���Ƿ������Ч���ݡ�
	/// </summary>
	/// <returns>˳��ջΪ���򷵻�TRUE�����򷵻�FALSE��</returns>
	Status StackEmpty() {
		if (top == base) {
			return TRUE;
		}
		return FALSE;
	}
	/// <summary>
	/// ����˳��ջ��������ЧԪ�ص�������
	/// </summary>
	/// <returns>Ԫ�ظ���</returns>
	int StackLength() {
		if (base == NULL) {
			return 0;
		}
		//�˴���ָ����мӼ����Ұ���
		return (int)(top - base) / sizeof(ElemType);
	}
	/// <summary>
	/// ����ջ��Ԫ��
	/// </summary>
	/// <param name="e">����Ԫ��</param>
	/// <returns>����ERROR����޷���ȡ��Ԫ�أ����򷵻�OK</returns>
	Status GetTop(ElemType& e) {
		if (base == NULL || top == base) {
			return ERROR;
		}

		// ����ı�ջ��Ԫ��
		e = *(top - 1);

		return OK;
	}
	/// <summary>
	/// ������ѹ��ջ��
	/// </summary>
	/// <param name="e">��ѹ�������</param>
	/// <returns>����OK�������ȷ��ջ�����������˳�</returns>
	Status Push(ElemType e) {
		if (base == NULL) {
			return ERROR;
		}

		// ջ��ʱ��׷�Ӵ洢�ռ�
		if (top - base >= stacksize) {
			//����STACKINCREMENT�ط���ռ�
			base = (ElemType*)realloc(base, (stacksize + STACKINCREMENT) * sizeof(ElemType));
			if (base == NULL) {
				exit(OVERFLOW);     // �洢����ʧ��
			}

			top = base + stacksize;
			stacksize += STACKINCREMENT;
		}

		// ��ջ�ȸ�ֵ��ջ��ָ��������
		*top = e;
		top++;

		return OK;
	}
	/// <summary>
	/// �����ݵ���ջ
	/// </summary>
	/// <param name="e">���ܵ���ջ��Ԫ��</param>
	/// <returns></returns>
	Status Pop(ElemType& e) {
		if (base == NULL) {
			return ERROR;
		}

		if (top == base) {
			return ERROR;
		}
		// ��ջջ��ָ���ȵݼ����ٸ�ֵ
		e = *(--top);

		return OK;
	}
	/// <summary>
	/// ����ջ��Ԫ��
	/// </summary>
	/// <param name="visit">���в����ı�������</param>
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

//��ʽջ
//����ʵ�֣���Ϊ����Ŀʵ�����������������Ͻ���
template <typename ElemType>
class LinkedStack : Stack<ElemType> {

};