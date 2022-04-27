#ifndef __FMK_DS__
#define __FMK_DS__
#pragma once
#include <exception>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>   
#include "defs.h"

/*
* д��ǰ�棺
* 1.ͳһ���ڵ㡱Ϊ����㡱
* 2.���\/*ADT T*\/��Ϊ��ֵĲ���ѡ�������������Ͽ���ȥһ��
*/

//˳����ʼ�����ó���
#define LIST_INIT_SIZE 1000
//˳���������
#define LISINCREMENT 10

//��ṹ
//��ѡ�࣬��Ϊ��������������ʵ������ʱ������λ��İְ�
template <typename ElemType>
class List{};
//˳���
//ʹ��ģ�������������࣬��߹㷺��
template <typename ElemType>
class SqList : List<ElemType>
{
public:
	//���캯�����ã����ձ�׼Init��Destroy����Ӧ���й��졢����������ɡ�����Ϊ��������ݽṹʵ��Ҫ�󣬴˴�����
	SqList()
	{
		//InitList_Sq();
	};
	/// <summary>
	/// ��ʼ��˳���
	/// </summary>
	/// <returns>�Ƿ��ʼ���ɹ�</returns>
	Status InitList_Sq(/*SqList &L*/)
	{
		this->elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));//�����ڴ�
		if (!elem)exit(OVERFLOW);//�������ʧ�ܣ��򷵻��������

		this->length = 0;	//Ŀǰû��Ԫ�أ���˳���Ϊ0
		this->listsize = LIST_INIT_SIZE;//˳�����Ϊ��ʼ���ó��ȣ�û������
		return OK;
	}
	~SqList()
	{
		//DestoryList_Sq();
	};
	/// <summary>
	/// ����˳���
	/// </summary>
	/// <returns>�Ƿ����ٳɹ�</returns>
	Status DestoryList_Sq(/*SqList &L*/)
	{
		free(this->elem);	//�ͷ�����˳���ռ�
		this->elem = nullptr;//����ָ�룬��ֹҰָ�����
		this->length = 0;
		this->listsize = 0;		//����ָ���Ѿ����ã����˳����پ��г���
		return OK;
	}
	/// <summary>
	/// ��ǰ���ڲ���Ԫ��
	/// </summary>
	/// <param name="i">���뵽��i��Ԫ��֮ǰ</param>
	/// <param name="_class">Ŀ��Ԫ��</param>
	/// <returns></returns>
	Status ListInsert_Sq(/*SqList& L,*/int i, ElemType e)
	{
		//Ϊ��ʡ�ռ䣬�˴�����C����ϰ�ߣ���0��ʼ�洢���
		if (i < 0 || i > this->length)return ERROR;	//��׳�ԣ���Чֵ�ж�
		if (this->length >= this->listsize)	//�˴����ҽ���Ϊ��=��ʱ��Ч�����·���ռ�
		{
			ElemType* newbase = (ElemType*)realloc(this->elem,
				(this->listsize + LISINCREMENT) * sizeof(ElemType));//ʹ�ò����ռ䣬���ڷ�������Ŀռ�
			if (!newbase)exit(OVERFLOW);
			this->elem = newbase;
			this->listsize += LISINCREMENT;
		}
		ElemType* q = &(this->elem[i - 1]);//��ȡ��i��Ԫ�ص�ǰһ��Ԫ�صĵ�ַ����Ϊ������Ͻ�
		for (ElemType* p = &(this->elem[this->length - 1]); //�����һ��Ԫ�ؿ�ʼ���������ص���
			p > q; --p) *(p + 1) = *p;//Ԫ�غ��
		*q = e;//����Ԫ��
		this->length++;//���ȵ���
		return OK;
	}
	/// <summary>
	/// ��˳�����ɾ��Ԫ��
	/// </summary>
	/// <param name="i">Ҫɾ����Ԫ�����</param>
	/// <param name="_class">ɾ����Ԫ�ؿ�������λ��</param>
	/// <returns></returns>
	Status ListDelete_Sq(/*SqList& L,*/ int i, ElemType& e)
	{
		if (i <0 || i > this.length) return ERROR;
		ElemType* p = &(this->elem[i]);//�˴������ϲ�ͬ����Ϊ��0��ʼ��¼���
		e = *p;
		ElemType* q = this->elem[this->length - 1]; //�����һ��Ԫ�ؿ�ʼ����
		for (++p; p <= q; ++p)*(p - 1) = *p;//�ƶ�Ԫ��
		--this->length;
		return OK;
	}
	/// <summary>
	/// ��˳����ж�λԪ���������ж�������ϵ���״γ���λ��
	/// </summary>
	/// <param name="_class">Ŀ�����Ԫ��</param>
	/// <param name="compare">����Ԫ���ж�����������[](int a,int b){return a<b;}Ϊ�Ƚϲ���</param>
	/// <returns>Ŀ��Ԫ���״γ���λ��</returns>
	int LocateElem_Sq(/*SqList& L,*/ ElemType e,
		Status(*compare)(ElemType, ElemType))
	{
		int i = 0;
		ElemType p = this->elem;
		while (i <= this->length - 1 && !(*compare)(*p++, e))++i;
		if (i <= this->length) return i;//��ֹ�ҳ���
		else return 0;
	}
	/// <summary>
	/// ����˳���
	/// </summary>
	/// <param name="visit">��������ÿ��Ԫ�ؽ��в���</param>
	void ListTraverse_Sq(/*SqList L,*/ void (*visit)(ElemType))
	{
		int i = 0;
		ElemType* p = this->elem;
		while (i < this->length - 1)
		{
			visit(*p);
			p++;
			++i;
		}
	}
	/// <summary>
	/// ��ӡ˳���
	/// ע�⣺�˺�����Ҫ�������������ͣ��������Ϳ��ܲ��걸
	/// </summary>
	void PrintList_Sq()
	{
		ListTraverse_Sq([](ElemType e) {printf("%d,", e); });
	}
	/// <summary>
	/// ��Lb�ϲ�������Lc
	/// </summary>
	/// <param name="Lb">Ҫ�뱾��ϲ�����һ��</param>
	/// <param name="Lc">�����Ĵ洢λ��</param>
	void MergeList_Sq(/*SqList La,*/ SqList Lb, SqList& Lc)
	{
		ElemType pa = this->elem;
		ElemType pb = Lb.elem;
		Lc.listsize = Lc.length = this->length + Lb.length;
		ElemType pc = Lc.elem = (ElemType*)malloc(Lc.listsize * sizeof(ElemType));
		if (!Lc.elem)exit(OVERFLOW);
		ElemType pa_last = this.elem + this.length - 1;
		ElemType pb_last = Lb.elem + Lb.length - 1;
		while (pa <= pa_last && pb <= pb_last)
		{
			if (*pa <= *pb) *pc++ = *pa++;//�ϲ���ͬʱ��������
			else *pc++ = *pb++;
		}
		while (pa <= pa_last) *pc++ = *pa++;//ֱ�ӽӵ���β
		while (pb <= pb_last)*pc++ = *pb++;
	}
	/// <summary>
	/// ���ر�
	/// </summary>
	/// <returns></returns>
	inline int ListLength_Sq(/*SqList L*/)
	{
		return this->length;
	}
	/// <summary>
	/// ���ر��Ƿ�Ϊ��
	/// </summary>
	/// <returns></returns>
	inline int ListEmpty_Sq(/*SqList L*/)
	{
		//������������������Ϊ�գ�
		// ����Ϊ0
		// ��Ĵ洢�ռ��ַΪ��
		// Ԫ��ȫ��Ϊ��
		return (this->length == 0 || this->elem == nullptr || [=]() {//�˱��ʽ
			for (int i = 0; i < this->length; i++)
			{
				if (this->elem[i] != NULL)return false;
			}
			return true;
			}());
	}
	ElemType* elem;	//�洢�ռ��ַ
private:
	int length;
	int listsize;
};

//����
template <typename ElemType>
class LinkList : List<ElemType>
{
public:
	struct LNode
	{
		ElemType _class;
		struct LNode* next;
	};

	LinkList()
	{

	};
	/// <summary>
	/// ��ʼ������
	/// </summary>
	/// <returns></returns>
	Status InitList_L(/*LinkList L*/)
	{
		head = (LNode*)malloc(sizeof(LNode));
		if (!head)return OVERFLOW;
		return OK;
	}
	/// <summary>
	/// �ͷ���������
	/// </summary>
	/// <returns></returns>
	Status DestoryList_L(/*LinkList L*/)
	{
		LNode* p = head;
		LNode* q = p;
		do
		{
			q = p;
			p = p->next;
			free(q);
		} while (p->next);
		return OK;
	}
	/// <summary>
	/// �ж������Ƿ�Ϊ��
	/// </summary>
	/// <returns>����ֵ</returns>
	Status ListEmpty_L(/*LinkList L*/)
	{
		if (head->next == nullptr)return TRUE;
		return FALSE;
	}
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="visit"></param>
	/// <returns></returns>
	Status ListTraverse_L(/*LinkList L,*/ void (*visit)(ElemType))
	{
		LNode* p = head;
		do
		{
			visit(p->_class);
			p++;
		} while (p->next);
	}
	/// <summary>
	/// ��ȡ�������
	/// </summary>
	/// <returns></returns>
	int ListLength_L(/*LinkList L*/)
	{
		int len = 0;
		ListTraverse_L([&len](ElemType) {len++; });
		return len;
	}
	/// <summary>
	/// ��ӡ����
	/// </summary>
	void PrintList_L()
	{
		ListTraverse_L([](ElemType e) {printf("%d,", e->_class); });
	}
	/// <summary>
	/// �������ж�λԪ�ص��״γ���λ��
	/// </summary>
	/// <param name="_class">Ŀ�����Ԫ��</param>
	/// <returns>Ŀ��Ԫ���״γ���λ��</returns>
	LNode* LocateElem_L(/*LinkList& L,*/ ElemType e
	/*,Status(*compare)(ElemType, ElemType)*/)
	{
		LNode* p = head;
		do {
			p++;//�˴�������������أ���ͬ��p = parent ->next;
		} while ((p->next != nullptr) && (p->_class != e));
		return p;
	}
	/// <summary>
	/// ��ȡ��i��Ԫ��
	/// </summary>
	/// <param name="i"></param>
	/// <param name="_class">Ԫ�ؿ�����</param>
	/// <returns></returns>
	Status GetElem_L(/*LinkList L,*/int i, ElemType& e)
	{

		LNode* p = head->next;
		int j = 1;
		while (p && j < i)
		{
			p++; ++j;
		}
		if (!p || j > i)return ERROR;
		e = p->_class;
		return OK;
	}
	/// <summary>
	/// ����ʽ���в���Ԫ��
	/// </summary>
	/// <param name="i">����ĵ�i��Ԫ��֮ǰ</param>
	/// <param name="_class">Ҫ�����Ԫ��</param>
	/// <returns></returns>
	Status ListInsert_L(/*LinkList &L,*/int i, ElemType e)
	{
		LNode* p = head;
		int j = 0;
		while (p->next && j < i) { p = p->next; ++j; };//���ҵ�Ŀ��ڵ�
		if (!p->next || j > i - 1)return ERROR;
		LNode* s = (LNode*)malloc(sizeof(LNode));//�����µĽڵ�
		s->_class = e;
		s->next = p->next;//�ȽӺ�̣���ֹ�Ҳ���
		p->next = s;//�ٸ���ǰ��
		return OK;
	}
	/// <summary>
	/// ��������ɾ����i���ڵ�
	/// </summary>
	/// <param name="i"></param>
	/// <param name="_class">ɾ���Ľڵ�����ݿ�����</param>
	/// <returns></returns>
	Status ListDelete_L(/*LinkList &L,*/ int i, ElemType& e)
	{
		LNode* p = head;
		int j = 0;
		while (p->next && j < i - 1)
		{
			p = p->next; ++j;
		}
		if (!p->next || j > i - 1)return ERROR;
		LNode* q = p->next; p->next = q->next;
		e = q->_class; free(q);
		return OK;
	}
	/// <summary>
	/// β�巨����ͷ�ڵ㣩��˳�����������
	/// </summary>
	/// <param name="n">Ҫ�����SqList�ĸ���</param>
	/// <param name="SqList">˳���</param>
	void CreateListTH_L(/*LinkList &L,*/int n, ElemType* SqList)
	{

		LNode* p = head;
		for (int i = 0; i < n; i++)
		{
			if (p == head)
			{
				p->_class = SqList;
				p->next = nullptr;
			}
			else
			{
				LNode* NewNode = (LNode*)malloc(sizeof(LNode));
				if (NewNode == nullptr)return OVERFLOW;
				p->next = NewNode;
				NewNode->_class = *SqList;
				NewNode->next = nullptr;
				p++;
			}
			SqList++;

		}
	}
	/// <summary>
	/// β�巨������ͷ�ڵ㣩��˳�����������
	/// </summary>
	/// <param name="n">Ҫ�����SqList�ĸ���</param>
	/// <param name="SqList">˳���</param>
	void CreateListTN_L(/*LinkList &L,*/int n, ElemType* SqList)
	{
		LNode* p = head;
		p->_class = NULL;
		for (int i = 0; i < n; i++)
		{
			LNode* NewNode = (LNode*)malloc(sizeof(LNode));
			if (NewNode == nullptr)return OVERFLOW;
			p->next = NewNode;
			NewNode->_class = *SqList;
			NewNode->next = nullptr;
			p++;
			SqList++;
		}
	}
	/// <summary>
	/// ͷ�巨����ͷ�ڵ㣩��˳�����������
	/// </summary>
	/// <param name="n">Ҫ�����SqList�ĸ���</param>
	/// <param name="SqList">˳���</param>
	void CreateListHH_L(/*LinkList &L,*/int n, ElemType* SqList)
	{
		LNode* p = head;
		for (int i = 0; i < n; i++)
		{
			if (p == head)
			{
				p->_class = SqList;
				p->next = nullptr;
			}
			else
			{
				LNode* NewNode = (LNode*)malloc(sizeof(LNode));
				if (NewNode == nullptr)return OVERFLOW;
				NewNode->_class = *SqList;
				NewNode->next = (p->next == nullptr ? nullptr : (p->next->next == nullptr ? nullptr : p->next->next));;
				p->next = NewNode;
			}
			SqList++;
		}
	}
	/// <summary>
	/// ͷ�巨������ͷ�ڵ㣩��˳�����������
	/// </summary>
	/// <param name="n">Ҫ�����SqList�ĸ���</param>
	/// <param name="SqList">˳���</param>
	void CreateListHN_L(/*LinkList &L,*/int n, ElemType* SqList)
	{
		LNode* p = head;
		p->_class = NULL;
		for (int i = 0; i < n; i++)
		{
			LNode* NewNode = (LNode*)malloc(sizeof(LNode));
			if (NewNode == nullptr)return OVERFLOW;
			NewNode->_class = *SqList;
			NewNode->next = (p->next == nullptr ? nullptr : (p->next->next == nullptr ? nullptr : p->next->next));;
			p->next = NewNode;
			SqList++;
		}
	}
	LNode* head;
private:
	LNode* operator++()
	{
		return (LNode->next == nullptr ? nullptr : LNode->next);
	}
};

//���ظ�����,��ѡģ�飺�˴��ѽ���
/*
template<class element>
class Set
{
public:
	struct Node
	{
		element _class;
		Node* next;
	};

	Set()
	{
		//����ʵ������
		throw std::logic_error("�޷�����δʵ�ֵĴ���");

		head = (Node*)malloc(sizeof Node);
		if (!head)return OVERFLOW;
		head->_class = 0;
		head->next = nullptr;
		compare = [](element a, element b) {return a < b; };
	}
	~Set()
	{
		Node* parent = head;
		Node* q = parent;
		do
		{
			q = parent;
			parent = parent->next;
			free(q);
		} while (parent != nullptr && parent->next);
	}
	Set(element* arr, size_t len, int (*compare)(element a, element b) = [](element a, element b) {return a < b; })
	{
		//if (compare != nullptr) this->compare = compare;
		//else
		//{
		//	static auto le = [](element a, element b)->int {return a < b; };
		//	compare = &le;
		//}
		head = (Node*)malloc(sizeof Node);
		if (!head)throw OVERFLOW;
		head->_class = 0;
		head->next = nullptr;
		for (int i = 0; i < len; i++)
		{
			if (LocateElement(*arr) == nullptr)
			{
				Node* last = head;
				Traverse([&](Node* n) ->void {
					if (this->compare(n->_class, *arr))
						last = n;
					});
				DirectInsertElement(*arr, last);
			}
			arr++;
		}
	}
	Status Traverse(std::function<void(element& e)> visit)
	{
		Node* parent = head->next;
		while (parent != nullptr)
		{
			visit(parent->_class);
			parent = (parent->next == nullptr ? nullptr : parent->next);
		}
		return OK;
	}
	Status Traverse(void (*visit)(element& e))
	{
		Node* parent = head->next;
		while (parent != nullptr)
		{
			visit(parent->_class);
			parent = parent->next;
		}
		return OK;
	}

	Status Traverse(std::function<void(Node* e)> visit)
	{
		Node* parent = head->next;
		while (parent != nullptr)
		{
			visit(parent);
			parent = parent->next;
		}
		return OK;
	}
	Status Traverse(void (*visit)(Node* n))
	{
		Node* parent = head->next;
		while (parent != nullptr)
		{
			visit(parent);
			parent = parent->next;
		}
		return OK;
	}
	Node* LocateElement(element e)
	{
		Node* ret = nullptr;

		Traverse([e, &ret](Node* find) {
			if (find->_class == e) { ret = find; };
			});
		return ret;
	}
	Status InsertElement(element e)
	{

	}


	Set operator*(Set b)
	{
		Set res = new Set;
		this->Traverse([b](element e) {
			if (b.LocateElement(e))
			{
				res.InsertElement(e);
			}
			});
	};
	Set operator+(Set b)
	{

	}
	Set operator-(Set b)
	{

	}
	Node* head;
	int (*compare)(element a, element b);

private:
	Status InsertElement(element e, Node* after)
	{
		Node* pos = LocateElement(after->_class);
		if (pos == nullptr)return INFEASIBLE;
		DirectInsertElement(e, pos);
	}
	Status DirectInsertElement(element e, Node* after)
	{
		Node* insert = (Node*)malloc(sizeof(Node));
		if (!insert) return OVERFLOW;
		insert->_class = e;
		insert->next = after->next;
		after->next = insert;
		return OK;
	}
};
*/



template<typename ElemType>
class Stack{};
#define STACK_INIT_SIZE 100     // ˳��ջ�洢�ռ�ĳ�ʼ������
#define STACKINCREMENT  10      // ˳��ջ�洢�ռ�ķ�������


//˳��ջ
template <typename ElemType>
class SqStack : Stack<ElemType>
{
public:
	ElemType* base;               // ջ��ָ��
	ElemType* top;                // ջ��ָ��
	int stacksize;                // ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ

	/// <summary>
	/// ������ջ
	/// </summary>
	/// <returns>��ʼ���ɹ��򷵻�OK</returns>
	Status InitStack() {
		//����ռ�
		base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType));
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
	/// <returns>˳��ջΪ���򷵻�TRUE�����򷵻�FALSE������ì��ʱ�׳��쳣</returns>
	Status StackEmpty() {
		if (top == base) {
			return TRUE;
		}
		else {
			if (stacksize != 0) throw ERROR;
			return FALSE;
		}
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
		return (int)(top - base)/sizeof(ElemType);
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
		if (this.top - this.base >= this.stacksize) {
			//����STACKINCREMENT�ط���ռ�
			this.base = (ElemType*)realloc(this.base, (this.stacksize + STACKINCREMENT) * sizeof(ElemType));
			if (this.base == NULL) {
				exit(OVERFLOW);     // �洢����ʧ��
			}

			this.top = this.base + this.stacksize;
			this.stacksize += STACKINCREMENT;
		}

		// ��ջ�ȸ�ֵ��ջ��ָ��������
		*(top++) = e;

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

		if (top ==base) {
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

//����ջ
//����ʵ�֣���Ϊ����Ŀʵ�����������������Ͻ���
template <typename ElemType>
class LinkStack : Stack<ElemType> {

};

#define MAX_TREE_SIZE 1024       // ���������������

//���ṹ
//��ѡ�࣬��Ϊ��������������ʵ������ʱ������λ���İְ�
template <typename ElemType>
class Tree {};
//˳��������ṹ
//����˳��������漰�����ļ���������������Ҫ�涨���ݴ�ȡ��ʽ��Ϊ�򻯣��˴��ٶ���������������Ϊchar
class SqBiTree : Tree<char>
{
	typedef char ElemType;
public:
	ElemType tree[MAX_TREE_SIZE];
	/// <summary>
	/// ����ն�����
	/// </summary>
	/// <returns>����OK</returns>
	Status InitBiTree() {
		// ʹ�ÿ�����������˳��ṹ
		memset(tree, 0, sizeof(tree));

		return OK;
	}
	/// <summary>
	/// ��δ�ã��ͷŶ�������ռ�ڴ档
	///  �˺���������ERROR��������˳��ṹ�޷�������
	/// </summary>
	/// <returns>ERROR</returns>
	Status DestroyBiTree() {
		// ��������˳��洢�ṹ�޷�����
		return ERROR;
	}
	/// <summary>
	/// �ÿն�����
	/// </summary>
	/// <returns>����OK</returns>
	Status ClearBiTree() {
		// ʹ�ÿ��ַ�����������˳��ṹ
		memset(tree, 0, sizeof(tree));

		return OK;
	}
	/// <summary>
	/// ʹ��ǰ�����д���������
	/// </summary>
	/// <returns>����OK�����ļ�ʧ��ʱ����ERROR</returns>
	Status CreateBiTree() {
		printf("��������������������У�ʹ��^�������ӽ�㣬��");
		CreateTree(0);
		return OK;
	}
	/// <summary>
	/// �������ַ����ж϶������Ƿ�Ϊ�ա�
	/// </summary>
	/// <returns>���ҽ������н������ȫ��Ϊ�ַ�'\0'ʱ��Ϊ����</returns>
	Status BiTreeEmpty() {
		bool isEmpty = false;
		for (int i = 0; i < MAX_TREE_SIZE; i++)
		{
			isEmpty &= tree[i] == 0;
		}
		return isEmpty;
	}
	/// <summary>
	/// ���ض����������
	/// </summary>
	/// <returns></returns>
	int BiTreeDepth() {
		return TreeDepth(0);
	}
	/// <summary>
	/// ��ȡ���e��ֵ
	/// </summary>
	/// <param name="e"></param>
	/// <returns></returns>
	ElemType Value( ElemType e) {
		int index;

		// ���������������������
		if (BiTreeEmpty()) {
			return '\0';
		}

		// ��ȡ���e������
		index = LocateNode(e, 0);

		// ���û���ҵ�Ԫ��e
		if (index == -1) {
			return '\0';
		}
		else {
			return tree[index];
		}
	}
	/// <summary>
	/// ��������и�ֵ
	/// </summary>
	/// <param name="e">Ҫ��ֵ��Ԫ��</param>
	/// <param name="value">��ֵ</param>
	/// <returns>�ɹ�����OK����Ϊ�ջ����Ҳ���Ԫ�ط���ERROR</returns>
	Status Assign(ElemType e, ElemType value) {
		int index;

		// ���������������������
		if (BiTreeEmpty()) {
			return ERROR;
		}

		// ��ȡ���e������
		index = LocateNode( e, 0);

		// ���û���ҵ�Ԫ��e
		if (index == -1) {
			return ERROR;
		}
		else {
			// ���и�ֵ
			tree[index] = value;
			return OK;
		}
	}
	/// <summary>
	/// �������ĸ�
	/// </summary>
	/// <returns></returns>
	ElemType Root() {
		// ���������������������
		if (BiTreeEmpty()) {
			return '\0';
		}

		return tree[0];
	}
	/// <summary>
	/// ����ĳ�ڵ�ĸ��ڵ�
	/// </summary>
	/// <param name="e"></param>
	/// <returns></returns>
	ElemType Parent( ElemType e) {
		int index;

		// ���������������������
		if (BiTreeEmpty()) {
			return '\0';
		}

		// ��ȡ���e������
		index = LocateNode(e, 0);

		// ���û���ҵ�Ԫ��e
		if (index == -1) {
			return '\0';

			// ���e�Ǹ����
		}
		else if (index == 0) {
			return '\0';
		}
		else {
			// ���ظ����
			return tree[(index - 1) / 2];
		}
	}
	/// <summary>
	/// ���ض�������������
	/// </summary>
	/// <param name="e"></param>
	/// <returns></returns>
	ElemType LeftChild(ElemType e) {
		int index;

		// ���������������������
		if (BiTreeEmpty()) {
			return '\0';
		}

		// ��ȡ���e������
		index = LocateNode(e, 0);

		// ���û���ҵ�Ԫ��e
		if (index == -1) {
			return '\0';
		}
		else {
			// ��������
			return tree[2 * index + 1];
		}
	}
	/// <summary>
	/// ���ض����������к���
	/// </summary>
	/// <param name="e"></param>
	/// <returns></returns>
	ElemType RightChild(ElemType e) {
		int index;

		// ���������������������
		if (BiTreeEmpty()) {
			return '\0';
		}

		// ��ȡ���e������
		index = LocateNode( e, 0);

		// ���û���ҵ�Ԫ��e
		if (index == -1) {
			return '\0';
		}
		else {
			// �����Һ���
			return tree[2 * index + 2];
		}
	}
	/// <summary>
	/// ����ĳ�ڵ�����ֵܽ��
	/// </summary>
	/// <param name="e"></param>
	/// <returns></returns>
	ElemType LeftSibling(ElemType e) {
		int index, p;

		// ���������������������
		if (BiTreeEmpty()) {
			return '\0';
		}

		// ��ȡ���e������
		index = LocateNode(e, 0);

		// ���û���ҵ�Ԫ��e
		if (index == -1) {
			return '\0';

			// ���e�Ǹ����
		}
		else if (index == 0) {
			return '\0';
		}
		else {
			// ��ȡ����������
			p = (index - 1) / 2;

			// ������e���Һ��ӣ��򷵻������ֵ�
			if (tree[2 * p + 2] == e) {
				return tree[2 * p + 1];
			}
			else {
				return '\0';
			}
		}
	}
	/// <summary>
	/// ���ض�����ĳ�������ֵ�
	/// </summary>
	/// <param name="e"></param>
	/// <returns></returns>
	ElemType RightSibling( ElemType e) {
		int index, p;

		// ���������������������
		if (BiTreeEmpty()) {
			return '\0';
		}

		// ��ȡ���e������
		index = LocateNode( e, 0);

		// ���û���ҵ�Ԫ��e
		if (index == -1) {
			return '\0';

			// ���e�Ǹ����
		}
		else if (index == 0) {
			return '\0';
		}
		else {
			// ��ȡ����������
			p = (index - 1) / 2;

			// ������e�����ӣ��򷵻������ֵ�
			if (tree[2 * p + 1] == e) {
				return tree[2 * p + 2];
			}
			else {
				return '\0';
			}
		}
	}
	/// <summary>
	/// ��֪cΪ��T���ཻ�ķǿն���������c��������Ϊ�գ���c����ΪT�н��p����������p���ԭ�е�������/�������޽�Ϊ������c����������
	/// </summary>
	/// <param name="parent">Ҫɾ�����������</param>
	/// <param name="LR">����LR��ȡֵ(SQBITREE_LEFT(RIGHT)_SUB_TREE)����c����ΪT�н��p��������/������</param>
	/// <param name="c"></param>
	/// <returns></returns>
#define SQBITREE_LEFT_SUB_TREE 0
#define SQBITREE_RIGHT_SUB_TREE 1
	Status InsertChild(ElemType p, int LR, SqBiTree c) {
		int index;

		// ������������Ϊ�����������������
		if (BiTreeEmpty()) {
			return ERROR;
		}

		// ��ȡ���p������
		index = LocateNode(p, 0);

		// ���p��㲻���ڣ��򷵻ش�����ʾ
		if (index == -1) {
			return ERROR;
		}

		// ��c����Ϊp��������
		if (LR == 0) {
			// ���p������������
			if (tree[2 * index + 1] != '\0') {
				// ��p������������Ϊc��������
				Transfer(*this , 2 * index + 1, c, 2);
			}

			Transfer(c, 0, *this , 2 * index + 1);

			// ��c����Ϊp��������
		}
		else {
			// ���p������������
			if (tree[2 * index + 2] != '\0') {
				// ��p������������Ϊc��������
				Transfer(*this, 2 * index + 2, c, 2);
			}

			Transfer(c, 0, *this, 2 * index + 2);
		}

		return OK;
	}
	/// <summary>
	/// ɾ��ĳ����
	/// </summary>
	/// <param name="parent">Ҫɾ�����������</param>
	/// <param name="LR">����������������</param>
	/// <returns></returns>
	Status DeleteChild(ElemType p, int LR) {
		int index;

		// �����ɾ������Ϊ�����������������
		if (BiTreeEmpty()) {
			return ERROR;
		}

		// ��ȡ���p������
		index = LocateNode( p, 0);

		// �����ɾ����㲻���ڣ��򷵻ش�����ʾ
		if (index == -1) {
			return ERROR;
		}

		// �����Ҫɾ��p��������
		if (LR == 0) {
			Delete( 2 * index + 1);

			// �����Ҫɾ��p��������
		}
		else {
			Delete(2 * index + 2);
		}

		return OK;
	}
	/// <summary>
	/// �������
	/// </summary>
	/// <param name="Visit"></param>
	/// <returns></returns>
	Status PreOrderTraverse(Status(*Visit)(ElemType)) {

		Status status = PreTraverse(Visit, 0);
		printf("\n");

		return status;
	}
	/// <summary>
	/// �������
	/// </summary>
	/// <param name="Visit"></param>
	/// <returns></returns>
	Status InOrderTraverse(Status(*Visit)(ElemType)) {
		Status status = InTraverse(Visit, 0);
		printf("\n");

		return status;
	}
	/// <summary>
	/// �������
	/// </summary>
	/// <param name="Visit"></param>
	/// <returns></returns>
	Status PostOrderTraverse(Status(*Visit)(ElemType)) {
		Status status;

		status = PostTraverse(Visit, 0);
		printf("\n");

		return status;
	}
	/// <summary>
	/// �������
	/// </summary>
	/// <param name="T"></param>
	/// <param name="Visit"></param>
	/// <returns></returns>
	Status LevelOrderTraverse(Status(*Visit)(ElemType)) {
		int i;
		int deep;
		int len;

		// ����������
		deep = BiTreeDepth();
		if (deep == 0) {
			return OK;
		}

		// ������Ԫ�����������ֵ��
		len = (int)pow(2, deep) - 1;

		for (i = 0; i < len; i++) {
			if (tree[i] != '\0') {
				if (!Visit(tree[i])) {
					// ����������ʴ��󣬻ἴʱ����
					return ERROR;
				}
			}
		}

		printf("\n");

		return OK;
	}
private:
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="i">��������λ��</param>
	void CreateTree(int i) {
		char ch;
		scanf("%c", &ch);

		if (ch == '^') {
			tree[i] = '\0';
		}
		else {
			tree[i] = ch;
			CreateTree(2 * i + 1); // ����������
			CreateTree(2 * i + 2); // ����������
		}
	}
	/// <summary>
	/// ��ȡ�������
	/// </summary>
	/// <param name="i">Ҷ�ӽڵ�����</param>
	/// <returns></returns>
	int TreeDepth( int i) {
		int ld, rd;     // ��¼�������������

		if (tree[i] == '\0') {
			return 0;
		}
		else {
			ld = TreeDepth( 2 * i + 1);
			rd = TreeDepth( 2 * i + 2);

			return (ld >= rd ? ld : rd) + 1;
		}
	}
	/// <summary>
	/// ���ض��������e�������ţ�i�ǽ��p��������
	/// </summary>
	/// <param name="e">Ҫ�����Ķ��������</param>
	/// <param name="i">���p������</param>
	/// <returns>�������������򷵻�-1</returns>
	int LocateNode(ElemType e, int i) {
		int cl, cr;

		// �Ѿ�Խ��
		if (i >= MAX_TREE_SIZE) {
			return -1;
		}

		// e��ֵ���Ϲ�
		if (e == '\0') {
			return -1;
		}

		// �ҵ���Ԫ��e
		if (tree[i] == e) {
			return i;
		}

		// ���������в���
		cl = LocateNode( e, 2 * i + 1);
		if (cl != -1) {
			return cl;
		}

		// ���������в���
		cr = LocateNode( e, 2 * i + 2);
		if (cr != -1) {
			return cr;
		}

		return -1;
	}
	/// <summary>
	/// ժ�¶�����T�е�����i���������Ϊ������R������j
	/// </summary>
	void Transfer(SqBiTree T, int i, SqBiTree R, int j) {
		T.tree[j] = R.tree[i];

		if (T.tree[i] != '\0') {
			Transfer(T, 2 * i + 1, R, 2 * j + 1);
			Transfer(T, 2 * i + 2, R, 2 * j + 2);
			T.tree[i] = '\0';
		}
	}
	/// <summary>
	/// ɾ��������T�е�����i
	/// </summary>
	void Delete(int i) {
		if (tree[i] != '\0') {
			tree[i] = '\0';
			Delete(2 * i + 1);
			Delete(2 * i + 2);
		}
	}
	/// <summary>
	/// �������
	/// </summary>
	/// <param name="Visit">��������</param>
	/// <param name="i"></param>
	/// <returns></returns>
	Status PreTraverse(Status(*Visit)(ElemType), int i) {
		// Խ��
		if (i >= MAX_TREE_SIZE) {
			return ERROR;
		}

		if (tree[i]) {
			if (Visit(tree[i])) {
				if (PreTraverse(Visit, 2 * i + 1)) {
					if (PreTraverse(Visit, 2 * i + 2)) {
						return OK;
					}
				}
			}

			return ERROR;

			// ���������������������
		}
		else {
			return OK;
		}
	}	
	/// <summary>
	/// �������
	/// </summary>
	/// <param name="Visit">��������</param>
	/// <param name="i"></param>
	/// <returns></returns>
	Status InTraverse( Status(*Visit)(ElemType), int i) {
		// Խ��
		if (i >= MAX_TREE_SIZE) {
			return ERROR;
		}

		if (tree[i]) {
			if (InTraverse( Visit, 2 * i + 1)) {
				if (Visit(tree[i])) {
					if (InTraverse( Visit, 2 * i + 2)) {
						return OK;
					}
				}

			}

			return ERROR;

			// ���������������������
		}
		else {
			return OK;
		}
	}	
	/// <summary>
	/// �������
	/// </summary>
	/// <param name="Visit">��������</param>
	/// <param name="i"></param>
	/// <returns></returns>
	Status PostTraverse(Status(*Visit)(ElemType), int i) {
		// Խ��
		if (i >= MAX_TREE_SIZE) {
			return ERROR;
		}

		if (tree[i]) {
			if (PostTraverse(Visit, 2 * i + 1)) {
				if (PostTraverse(Visit, 2 * i + 2)) {
					if (Visit(tree[i])) {
						return OK;
					}

				}
			}

			return ERROR;

			// ���������������������
		}
		else {
			return OK;
		}
	}
};

//������
//ͬ��
class BiTree : Tree<char>
{
	typedef char ElemType;
	struct BiTNode {
		ElemType _class;             // ���Ԫ��
		struct BiTNode* lchild;     // ����ָ��
		struct BiTNode* rchild;     // �Һ���ָ��
	};

	BiTNode* T;	//��������ͷ�ڵ�
	/// <summary>
	/// ����ն�������
	/// </summary>
	/// <returns></returns>
	Status InitBiTree() {
		if (T == NULL) {
			return ERROR;
		}

		T = NULL;
		return OK;
	}

};

//�����
template<typename T1, typename T2> 
class Pair {
public:
	T1 first;
	T2 second;
	Pair(T1& first, T2& second) :first(first), second(second) {}
	Pair() {}

};
#endif