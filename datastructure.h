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
* 写在前面：
* 1.统一“节点”为“结点”
* 2.添加\/*ADT T*\/作为奇怪的不可选参数让他和书上看上去一致
*/

//顺序表初始化可用长度
#define LIST_INIT_SIZE 1000
//顺序表步增长度
#define LISINCREMENT 10

//表结构
//可选类，作为卖萌类放在这里，其实名义上时下述各位表的爸爸
template <typename ElemType>
class List{};
//顺序表
//使用模板以适配所有类，提高广泛性
template <typename ElemType>
class SqList : List<ElemType>
{
public:
	//构造函数空置，按照标准Init和Destroy函数应该有构造、析构函数完成。但是为了配合数据结构实验要求，此处空置
	SqList()
	{
		//InitList_Sq();
	};
	/// <summary>
	/// 初始化顺序表
	/// </summary>
	/// <returns>是否初始化成功</returns>
	Status InitList_Sq(/*SqList &L*/)
	{
		this->elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));//申请内存
		if (!elem)exit(OVERFLOW);//如果申请失败，则返回溢出错误

		this->length = 0;	//目前没有元素，因此长度为0
		this->listsize = LIST_INIT_SIZE;//顺序表长度为初始可用长度，没有扩增
		return OK;
	}
	~SqList()
	{
		//DestoryList_Sq();
	};
	/// <summary>
	/// 销毁顺序表
	/// </summary>
	/// <returns>是否销毁成功</returns>
	Status DestoryList_Sq(/*SqList &L*/)
	{
		free(this->elem);	//释放所有顺序表空间
		this->elem = nullptr;//空置指针，防止野指针错误
		this->length = 0;
		this->listsize = 0;		//由于指针已经空置，因此顺序表不再具有长度
		return OK;
	}
	/// <summary>
	/// 向当前表内插入元素
	/// </summary>
	/// <param name="i">插入到第i个元素之前</param>
	/// <param name="_class">目标元素</param>
	/// <returns></returns>
	Status ListInsert_Sq(/*SqList& L,*/int i, ElemType e)
	{
		//为节省空间，此处按照C语言习惯，从0开始存储序号
		if (i < 0 || i > this->length)return ERROR;	//健壮性：有效值判断
		if (this->length >= this->listsize)	//此处当且仅当为“=”时有效。重新分配空间
		{
			ElemType* newbase = (ElemType*)realloc(this->elem,
				(this->listsize + LISINCREMENT) * sizeof(ElemType));//使用步增空间，用于分配整块的空间
			if (!newbase)exit(OVERFLOW);
			this->elem = newbase;
			this->listsize += LISINCREMENT;
		}
		ElemType* q = &(this->elem[i - 1]);//获取第i个元素的前一个元素的地址，作为插入的上界
		for (ElemType* p = &(this->elem[this->length - 1]); //从最后一个元素开始，逆序往回调整
			p > q; --p) *(p + 1) = *p;//元素后调
		*q = e;//插入元素
		this->length++;//长度递增
		return OK;
	}
	/// <summary>
	/// 从顺序表中删除元素
	/// </summary>
	/// <param name="i">要删除的元素序号</param>
	/// <param name="_class">删除的元素拷贝到的位置</param>
	/// <returns></returns>
	Status ListDelete_Sq(/*SqList& L,*/ int i, ElemType& e)
	{
		if (i <0 || i > this.length) return ERROR;
		ElemType* p = &(this->elem[i]);//此处和书上不同，因为从0开始记录序号
		e = *p;
		ElemType* q = this->elem[this->length - 1]; //从最后一个元素开始往后
		for (++p; p <= q; ++p)*(p - 1) = *p;//移动元素
		--this->length;
		return OK;
	}
	/// <summary>
	/// 在顺序表中定位元素有数据判定函数关系的首次出现位置
	/// </summary>
	/// <param name="_class">目标查找元素</param>
	/// <param name="compare">数据元素判定函数。例如[](int a,int b){return a<b;}为比较查找</param>
	/// <returns>目标元素首次出现位置</returns>
	int LocateElem_Sq(/*SqList& L,*/ ElemType e,
		Status(*compare)(ElemType, ElemType))
	{
		int i = 0;
		ElemType p = this->elem;
		while (i <= this->length - 1 && !(*compare)(*p++, e))++i;
		if (i <= this->length) return i;//防止找出界
		else return 0;
	}
	/// <summary>
	/// 遍历顺序表
	/// </summary>
	/// <param name="visit">函数，对每个元素进行操作</param>
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
	/// 打印顺序表
	/// 注意：此函数主要适用于整形类型，其他类型可能不完备
	/// </summary>
	void PrintList_Sq()
	{
		ListTraverse_Sq([](ElemType e) {printf("%d,", e); });
	}
	/// <summary>
	/// 与Lb合并并生成Lc
	/// </summary>
	/// <param name="Lb">要与本表合并的另一表</param>
	/// <param name="Lc">结果表的存储位置</param>
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
			if (*pa <= *pb) *pc++ = *pa++;//合并的同时进行排序
			else *pc++ = *pb++;
		}
		while (pa <= pa_last) *pc++ = *pa++;//直接接到表尾
		while (pb <= pb_last)*pc++ = *pb++;
	}
	/// <summary>
	/// 返回表长
	/// </summary>
	/// <returns></returns>
	inline int ListLength_Sq(/*SqList L*/)
	{
		return this->length;
	}
	/// <summary>
	/// 返回表是否为空
	/// </summary>
	/// <returns></returns>
	inline int ListEmpty_Sq(/*SqList L*/)
	{
		//任意下述条件存在则为空：
		// 长度为0
		// 表的存储空间基址为空
		// 元素全部为空
		return (this->length == 0 || this->elem == nullptr || [=]() {//λ表达式
			for (int i = 0; i < this->length; i++)
			{
				if (this->elem[i] != NULL)return false;
			}
			return true;
			}());
	}
	ElemType* elem;	//存储空间基址
private:
	int length;
	int listsize;
};

//链表
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
	/// 初始化链表
	/// </summary>
	/// <returns></returns>
	Status InitList_L(/*LinkList L*/)
	{
		head = (LNode*)malloc(sizeof(LNode));
		if (!head)return OVERFLOW;
		return OK;
	}
	/// <summary>
	/// 释放整个链表
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
	/// 判断链表是否为空
	/// </summary>
	/// <returns>布尔值</returns>
	Status ListEmpty_L(/*LinkList L*/)
	{
		if (head->next == nullptr)return TRUE;
		return FALSE;
	}
	/// <summary>
	/// 遍历链表
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
	/// 获取链表深度
	/// </summary>
	/// <returns></returns>
	int ListLength_L(/*LinkList L*/)
	{
		int len = 0;
		ListTraverse_L([&len](ElemType) {len++; });
		return len;
	}
	/// <summary>
	/// 打印链表
	/// </summary>
	void PrintList_L()
	{
		ListTraverse_L([](ElemType e) {printf("%d,", e->_class); });
	}
	/// <summary>
	/// 在链表中定位元素的首次出现位置
	/// </summary>
	/// <param name="_class">目标查找元素</param>
	/// <returns>目标元素首次出现位置</returns>
	LNode* LocateElem_L(/*LinkList& L,*/ ElemType e
	/*,Status(*compare)(ElemType, ElemType)*/)
	{
		LNode* p = head;
		do {
			p++;//此处做了运算符重载，等同于p = parent ->next;
		} while ((p->next != nullptr) && (p->_class != e));
		return p;
	}
	/// <summary>
	/// 获取第i个元素
	/// </summary>
	/// <param name="i"></param>
	/// <param name="_class">元素拷贝到</param>
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
	/// 向链式表中插入元素
	/// </summary>
	/// <param name="i">插入的第i个元素之前</param>
	/// <param name="_class">要插入的元素</param>
	/// <returns></returns>
	Status ListInsert_L(/*LinkList &L,*/int i, ElemType e)
	{
		LNode* p = head;
		int j = 0;
		while (p->next && j < i) { p = p->next; ++j; };//先找到目标节点
		if (!p->next || j > i - 1)return ERROR;
		LNode* s = (LNode*)malloc(sizeof(LNode));//生成新的节点
		s->_class = e;
		s->next = p->next;//先接后继，防止找不到
		p->next = s;//再更改前驱
		return OK;
	}
	/// <summary>
	/// 在链表中删除第i个节点
	/// </summary>
	/// <param name="i"></param>
	/// <param name="_class">删除的节点的数据拷贝到</param>
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
	/// 尾插法（带头节点）从顺序表生成链表
	/// </summary>
	/// <param name="n">要插入的SqList的个数</param>
	/// <param name="SqList">顺序表</param>
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
	/// 尾插法（不带头节点）从顺序表生成链表
	/// </summary>
	/// <param name="n">要插入的SqList的个数</param>
	/// <param name="SqList">顺序表</param>
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
	/// 头插法（带头节点）从顺序表生成链表
	/// </summary>
	/// <param name="n">要插入的SqList的个数</param>
	/// <param name="SqList">顺序表</param>
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
	/// 头插法（不带头节点）从顺序表生成链表
	/// </summary>
	/// <param name="n">要插入的SqList的个数</param>
	/// <param name="SqList">顺序表</param>
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

//非重复集合,可选模块：此处已禁用
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
		//存在实现问题
		throw std::logic_error("无法启动未实现的代码");

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
#define STACK_INIT_SIZE 100     // 顺序栈存储空间的初始分配量
#define STACKINCREMENT  10      // 顺序栈存储空间的分配增量


//顺序栈
template <typename ElemType>
class SqStack : Stack<ElemType>
{
public:
	ElemType* base;               // 栈底指针
	ElemType* top;                // 栈顶指针
	int stacksize;                // 当前已分配的存储空间，以元素为单位

	/// <summary>
	/// 创建新栈
	/// </summary>
	/// <returns>初始化成功则返回OK</returns>
	Status InitStack() {
		//申请空间
		base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType));
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
	/// <returns>顺序栈为空则返回TRUE，否则返回FALSE。出现矛盾时抛出异常</returns>
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
	/// 返回顺序栈包含的有效元素的数量。
	/// </summary>
	/// <returns>元素个数</returns>
	int StackLength() {
		if (base == NULL) {
			return 0;
		}
		//此处对指针进行加减并且按照
		return (int)(top - base)/sizeof(ElemType);
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
		if (this.top - this.base >= this.stacksize) {
			//按照STACKINCREMENT重分配空间
			this.base = (ElemType*)realloc(this.base, (this.stacksize + STACKINCREMENT) * sizeof(ElemType));
			if (this.base == NULL) {
				exit(OVERFLOW);     // 存储分配失败
			}

			this.top = this.base + this.stacksize;
			this.stacksize += STACKINCREMENT;
		}

		// 进栈先赋值，栈顶指针再自增
		*(top++) = e;

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

		if (top ==base) {
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

//链表栈
//懒得实现，作为二周目实现条件（这条不能上交）
template <typename ElemType>
class LinkStack : Stack<ElemType> {

};

#define MAX_TREE_SIZE 1024       // 二叉树的最大结点数

//树结构
//可选类，作为卖萌类放在这里，其实名义上时下述各位树的爸爸
template <typename ElemType>
class Tree {};
//顺序二叉树结构
//由于顺序二叉树涉及到从文件创建二叉树，需要规定数据存取方式，为简化，此处假定二叉树数据类型为char
class SqBiTree : Tree<char>
{
	typedef char ElemType;
public:
	ElemType tree[MAX_TREE_SIZE];
	/// <summary>
	/// 构造空二叉树
	/// </summary>
	/// <returns>返回OK</returns>
	Status InitBiTree() {
		// 使用空填充二叉树的顺序结构
		memset(tree, 0, sizeof(tree));

		return OK;
	}
	/// <summary>
	/// （未用）释放二叉树所占内存。
	///  此函数将返回ERROR：二叉树顺序结构无法被销毁
	/// </summary>
	/// <returns>ERROR</returns>
	Status DestroyBiTree() {
		// 二叉树的顺序存储结构无法销毁
		return ERROR;
	}
	/// <summary>
	/// 置空二叉树
	/// </summary>
	/// <returns>返回OK</returns>
	Status ClearBiTree() {
		// 使用空字符填充二叉树的顺序结构
		memset(tree, 0, sizeof(tree));

		return OK;
	}
	/// <summary>
	/// 使用前序序列创建二叉树
	/// </summary>
	/// <returns>返回OK，打开文件失败时返回ERROR</returns>
	Status CreateBiTree() {
		printf("请输入二叉树的先序序列，使用^代替无子结点，：");
		CreateTree(0);
		return OK;
	}
	/// <summary>
	/// 依赖于字符串判断二叉树是否为空。
	/// </summary>
	/// <returns>当且仅当所有结点数据全部为字符'\0'时认为树空</returns>
	Status BiTreeEmpty() {
		bool isEmpty = false;
		for (int i = 0; i < MAX_TREE_SIZE; i++)
		{
			isEmpty &= tree[i] == 0;
		}
		return isEmpty;
	}
	/// <summary>
	/// 返回二叉树的深度
	/// </summary>
	/// <returns></returns>
	int BiTreeDepth() {
		return TreeDepth(0);
	}
	/// <summary>
	/// 获取结点e的值
	/// </summary>
	/// <param name="e"></param>
	/// <returns></returns>
	ElemType Value( ElemType e) {
		int index;

		// 遇到空树则无需继续计算
		if (BiTreeEmpty()) {
			return '\0';
		}

		// 获取结点e的索引
		index = LocateNode(e, 0);

		// 如果没有找到元素e
		if (index == -1) {
			return '\0';
		}
		else {
			return tree[index];
		}
	}
	/// <summary>
	/// 向二叉树中赋值
	/// </summary>
	/// <param name="e">要赋值的元素</param>
	/// <param name="value">赋值</param>
	/// <returns>成功返回OK，树为空或者找不到元素返回ERROR</returns>
	Status Assign(ElemType e, ElemType value) {
		int index;

		// 遇到空树则无需继续计算
		if (BiTreeEmpty()) {
			return ERROR;
		}

		// 获取结点e的索引
		index = LocateNode( e, 0);

		// 如果没有找到元素e
		if (index == -1) {
			return ERROR;
		}
		else {
			// 进行赋值
			tree[index] = value;
			return OK;
		}
	}
	/// <summary>
	/// 返回树的根
	/// </summary>
	/// <returns></returns>
	ElemType Root() {
		// 遇到空树则无需继续计算
		if (BiTreeEmpty()) {
			return '\0';
		}

		return tree[0];
	}
	/// <summary>
	/// 返回某节点的父节点
	/// </summary>
	/// <param name="e"></param>
	/// <returns></returns>
	ElemType Parent( ElemType e) {
		int index;

		// 遇到空树则无需继续计算
		if (BiTreeEmpty()) {
			return '\0';
		}

		// 获取结点e的索引
		index = LocateNode(e, 0);

		// 如果没有找到元素e
		if (index == -1) {
			return '\0';

			// 如果e是根结点
		}
		else if (index == 0) {
			return '\0';
		}
		else {
			// 返回父结点
			return tree[(index - 1) / 2];
		}
	}
	/// <summary>
	/// 返回二叉树结点的左孩子
	/// </summary>
	/// <param name="e"></param>
	/// <returns></returns>
	ElemType LeftChild(ElemType e) {
		int index;

		// 遇到空树则无需继续计算
		if (BiTreeEmpty()) {
			return '\0';
		}

		// 获取结点e的索引
		index = LocateNode(e, 0);

		// 如果没有找到元素e
		if (index == -1) {
			return '\0';
		}
		else {
			// 返回左孩子
			return tree[2 * index + 1];
		}
	}
	/// <summary>
	/// 返回二叉树结点的有孩子
	/// </summary>
	/// <param name="e"></param>
	/// <returns></returns>
	ElemType RightChild(ElemType e) {
		int index;

		// 遇到空树则无需继续计算
		if (BiTreeEmpty()) {
			return '\0';
		}

		// 获取结点e的索引
		index = LocateNode( e, 0);

		// 如果没有找到元素e
		if (index == -1) {
			return '\0';
		}
		else {
			// 返回右孩子
			return tree[2 * index + 2];
		}
	}
	/// <summary>
	/// 返回某节点的左兄弟结点
	/// </summary>
	/// <param name="e"></param>
	/// <returns></returns>
	ElemType LeftSibling(ElemType e) {
		int index, p;

		// 遇到空树则无需继续计算
		if (BiTreeEmpty()) {
			return '\0';
		}

		// 获取结点e的索引
		index = LocateNode(e, 0);

		// 如果没有找到元素e
		if (index == -1) {
			return '\0';

			// 如果e是根结点
		}
		else if (index == 0) {
			return '\0';
		}
		else {
			// 获取父结点的索引
			p = (index - 1) / 2;

			// 如果结点e是右孩子，则返回其左兄弟
			if (tree[2 * p + 2] == e) {
				return tree[2 * p + 1];
			}
			else {
				return '\0';
			}
		}
	}
	/// <summary>
	/// 返回二叉树某结点的右兄弟
	/// </summary>
	/// <param name="e"></param>
	/// <returns></returns>
	ElemType RightSibling( ElemType e) {
		int index, p;

		// 遇到空树则无需继续计算
		if (BiTreeEmpty()) {
			return '\0';
		}

		// 获取结点e的索引
		index = LocateNode( e, 0);

		// 如果没有找到元素e
		if (index == -1) {
			return '\0';

			// 如果e是根结点
		}
		else if (index == 0) {
			return '\0';
		}
		else {
			// 获取父结点的索引
			p = (index - 1) / 2;

			// 如果结点e是左孩子，则返回其右兄弟
			if (tree[2 * p + 1] == e) {
				return tree[2 * p + 2];
			}
			else {
				return '\0';
			}
		}
	}
	/// <summary>
	/// 已知c为与T不相交的非空二叉树，且c的右子树为空，将c插入为T中结点p的子树，将p结点原有的左子树/右子树嫁接为二叉树c的右子树。
	/// </summary>
	/// <param name="parent">要删除的子树结点</param>
	/// <param name="LR">根据LR的取值(SQBITREE_LEFT(RIGHT)_SUB_TREE)，将c插入为T中结点p的左子树/右子树</param>
	/// <param name="c"></param>
	/// <returns></returns>
#define SQBITREE_LEFT_SUB_TREE 0
#define SQBITREE_RIGHT_SUB_TREE 1
	Status InsertChild(ElemType p, int LR, SqBiTree c) {
		int index;

		// 如果待插入的树为空树则无需继续计算
		if (BiTreeEmpty()) {
			return ERROR;
		}

		// 获取结点p的索引
		index = LocateNode(p, 0);

		// 如果p结点不存在，则返回错误提示
		if (index == -1) {
			return ERROR;
		}

		// 将c插入为p的左子树
		if (LR == 0) {
			// 如果p处存在左子树
			if (tree[2 * index + 1] != '\0') {
				// 将p的左子树插入为c的右子树
				Transfer(*this , 2 * index + 1, c, 2);
			}

			Transfer(c, 0, *this , 2 * index + 1);

			// 将c插入为p的右子树
		}
		else {
			// 如果p处存在右子树
			if (tree[2 * index + 2] != '\0') {
				// 将p的右子树插入为c的右子树
				Transfer(*this, 2 * index + 2, c, 2);
			}

			Transfer(c, 0, *this, 2 * index + 2);
		}

		return OK;
	}
	/// <summary>
	/// 删除某子树
	/// </summary>
	/// <param name="parent">要删除的子树结点</param>
	/// <param name="LR">左子树还是右子树</param>
	/// <returns></returns>
	Status DeleteChild(ElemType p, int LR) {
		int index;

		// 如果待删除的树为空树则无需继续计算
		if (BiTreeEmpty()) {
			return ERROR;
		}

		// 获取结点p的索引
		index = LocateNode( p, 0);

		// 如果待删除结点不存在，则返回错误提示
		if (index == -1) {
			return ERROR;
		}

		// 如果需要删除p的左子树
		if (LR == 0) {
			Delete( 2 * index + 1);

			// 如果需要删除p的右子树
		}
		else {
			Delete(2 * index + 2);
		}

		return OK;
	}
	/// <summary>
	/// 先序遍历
	/// </summary>
	/// <param name="Visit"></param>
	/// <returns></returns>
	Status PreOrderTraverse(Status(*Visit)(ElemType)) {

		Status status = PreTraverse(Visit, 0);
		printf("\n");

		return status;
	}
	/// <summary>
	/// 中序遍历
	/// </summary>
	/// <param name="Visit"></param>
	/// <returns></returns>
	Status InOrderTraverse(Status(*Visit)(ElemType)) {
		Status status = InTraverse(Visit, 0);
		printf("\n");

		return status;
	}
	/// <summary>
	/// 后序遍历
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
	/// 层序遍历
	/// </summary>
	/// <param name="T"></param>
	/// <param name="Visit"></param>
	/// <returns></returns>
	Status LevelOrderTraverse(Status(*Visit)(ElemType)) {
		int i;
		int deep;
		int len;

		// 二叉树层数
		deep = BiTreeDepth();
		if (deep == 0) {
			return OK;
		}

		// 二叉树元素数量（最大值）
		len = (int)pow(2, deep) - 1;

		for (i = 0; i < len; i++) {
			if (tree[i] != '\0') {
				if (!Visit(tree[i])) {
					// 如果遇到访问错误，会即时返回
					return ERROR;
				}
			}
		}

		printf("\n");

		return OK;
	}
private:
	/// <summary>
	/// 创建二叉树
	/// </summary>
	/// <param name="i">创建索引位置</param>
	void CreateTree(int i) {
		char ch;
		scanf("%c", &ch);

		if (ch == '^') {
			tree[i] = '\0';
		}
		else {
			tree[i] = ch;
			CreateTree(2 * i + 1); // 创建左子树
			CreateTree(2 * i + 2); // 创建右子树
		}
	}
	/// <summary>
	/// 获取树的深度
	/// </summary>
	/// <param name="i">叶子节点索引</param>
	/// <returns></returns>
	int TreeDepth( int i) {
		int ld, rd;     // 记录左右子树的深度

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
	/// 返回二叉树结点e的索引号，i是结点p的索引号
	/// </summary>
	/// <param name="e">要搜索的二叉树结点</param>
	/// <param name="i">结点p的索引</param>
	/// <returns>返回索引，否则返回-1</returns>
	int LocateNode(ElemType e, int i) {
		int cl, cr;

		// 已经越界
		if (i >= MAX_TREE_SIZE) {
			return -1;
		}

		// e的值不合规
		if (e == '\0') {
			return -1;
		}

		// 找到了元素e
		if (tree[i] == e) {
			return i;
		}

		// 在左子树中查找
		cl = LocateNode( e, 2 * i + 1);
		if (cl != -1) {
			return cl;
		}

		// 在右子树中查找
		cr = LocateNode( e, 2 * i + 2);
		if (cr != -1) {
			return cr;
		}

		return -1;
	}
	/// <summary>
	/// 摘下二叉树T中的子树i，将其插入为二叉树R的子树j
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
	/// 删除二叉树T中的子树i
	/// </summary>
	void Delete(int i) {
		if (tree[i] != '\0') {
			tree[i] = '\0';
			Delete(2 * i + 1);
			Delete(2 * i + 2);
		}
	}
	/// <summary>
	/// 先序遍历
	/// </summary>
	/// <param name="Visit">遍历函数</param>
	/// <param name="i"></param>
	/// <returns></returns>
	Status PreTraverse(Status(*Visit)(ElemType), int i) {
		// 越界
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

			// 遇到空树则无需继续计算
		}
		else {
			return OK;
		}
	}	
	/// <summary>
	/// 中序遍历
	/// </summary>
	/// <param name="Visit">遍历函数</param>
	/// <param name="i"></param>
	/// <returns></returns>
	Status InTraverse( Status(*Visit)(ElemType), int i) {
		// 越界
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

			// 遇到空树则无需继续计算
		}
		else {
			return OK;
		}
	}	
	/// <summary>
	/// 后序遍历
	/// </summary>
	/// <param name="Visit">遍历函数</param>
	/// <param name="i"></param>
	/// <returns></returns>
	Status PostTraverse(Status(*Visit)(ElemType), int i) {
		// 越界
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

			// 遇到空树则无需继续计算
		}
		else {
			return OK;
		}
	}
};

//二叉树
//同上
class BiTree : Tree<char>
{
	typedef char ElemType;
	struct BiTNode {
		ElemType _class;             // 结点元素
		struct BiTNode* lchild;     // 左孩子指针
		struct BiTNode* rchild;     // 右孩子指针
	};

	BiTNode* T;	//二叉树的头节点
	/// <summary>
	/// 构造空二叉树。
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

//有序对
template<typename T1, typename T2> 
class Pair {
public:
	T1 first;
	T2 second;
	Pair(T1& first, T2& second) :first(first), second(second) {}
	Pair() {}

};
#endif