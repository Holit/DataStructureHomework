#pragma once
#include "defs.h"
#include <malloc.h>

//顺序表初始化可用长度
#define LIST_INIT_SIZE 1000
//顺序表步增长度
#define LISINCREMENT 10

//表结构
//可选类，作为卖萌类放在这里，其实名义上时下述各位表的爸爸
template <typename ElemType>
class List {};
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