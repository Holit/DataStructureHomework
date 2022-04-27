#pragma once
#include "defs.h"
#include <malloc.h>

//˳����ʼ�����ó���
#define LIST_INIT_SIZE 1000
//˳���������
#define LISINCREMENT 10

//��ṹ
//��ѡ�࣬��Ϊ��������������ʵ������ʱ������λ��İְ�
template <typename ElemType>
class List {};
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