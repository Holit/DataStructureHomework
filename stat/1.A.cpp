//1.A.cpp
//
//数据结构与程序设计实验
//
//实验1 A档实验
//作者：Jerry Gao
//请联系gao1021229073@163.com反馈漏洞和bug
//
//要启用此文件，请取消下述Experiment_1_A_Enabled的注释
//注意：一次只能启用一个实验文件进行编译
//#define Experiment_1_A_Enabled
//固定编译头，勿更改
#ifdef Experiment_1_A_Enabled
#ifndef _main_
#define _main_ main
#else
#error "函数名冲突：启用了两个或以上的实验源代码文件"
#endif
#endif // !Experiment_1_A_Enabled
#include "defs.h" 

/*
* 约瑟夫环问题
（1）问题描述
设有编号为 1,2,…,n 的 n（n＞0）个人围成一个圈，每个人持有一个密码 m。从第一个人开始报数，报到 m 时停止报数，
报 m 的人出圈，再从他的下一个人起重新报数，报到 m 时停止报数，报 m 的出圈，……，如此下去，直到所有人全部出圈为止。
当任意给定 n 和 m 后，设计算法求 n 个人出圈的次序。
（2）基本要求
-  建立模型，确定存储结构。
-  对任意 n 个人，密码为 m，实现约瑟夫环问题。
-  出圈的顺序可以依次输出，也可以用一个数组存储。
（3）思考：
-  采用顺序存储结构如何实现约瑟夫环问题？
-  如果每个人持有的密码不同，应如何实现约瑟夫环问题？
*/

#include <iostream>
#include <algorithm>
#include <vector>		//顺序表STL支持
#include <functional>
//#include <list>		//双向链表STL支持不支持循环链表，因此自建循环链表类

using namespace std;

//此开关用于空置约瑟夫环的实现形式，如果存在此开关则使用链表类型实现约瑟夫环类。
//#define LinkArray

#ifdef LinkArray

//此算法已经通过洛谷OJ评测
/*Accepted
#1 2ms/492.00KB
#2 3ms/480.00KB
#3 3ms/628.00KB
#4 2ms/636.00KB
*/
class JosephRing
{
public:
	JosephRing(long len, long code)		//约瑟夫环类
	{
		this->len = len;		
		this->code = code;
		ring = (node*)malloc(sizeof(node));	//申请相对应的空间
		if (!ring) throw OVERFLOW;//鲁棒性

		ring->data = 1;	//由于插入结点的一些固有问题，此处要进行第一个元素的赋值
		ring->next = ring;//创建指针循环

		for (long i = len - 1; i > 0; i--)	//生成环
		{
			node* addition = (node*)malloc(sizeof(node));	//创建第一个环节点
			if (!addition)throw OVERFLOW;
			addition->next = ring->next;	//将环节点插入到头节点之后，使用头插法，因此此处的for循环是倒序循环
			ring->next = addition;
			addition->data = i + 1;		//为了提高可读性和教材统一，此处使用多一个计数
		}
		//printList();
	};
	~JosephRing()
	{			//释放此结构
		//由于此程序运算完成就结束，此处不设计循环释放过程
		//同时因为一般而言使用solve之后都会删除所有结点，所以不设析构函数
		//free(ring);
	}
	void solve(void(*fun)(long&))
	{
		long loop = 0;	//循环计数器
		node* op = ring;	//创建操作节点指针，用于读写各节点
		do
		{
			if (loop == code - 1)//如果命中密码
			{
				fun(op->data);	//按照函数操作节点的数据，例如输出
				op = _delete(op);	//使用内置函数删除此节点，此处必须进行赋值，否则会产生空指针错误
									//此delete里包含了len--操作
				//printList();
				op = op->next;//下移节点操作指针
				loop = 0;//循环计数器归零
			}
			else
			{
				op = op->next;
				loop++;
			}
		} while (len != 0);//当长度不为0时一直循环到长度尾0
	}
private:
	struct node
	{
		node* next;
		long data;
	};
	void printList()		//测试函数，用于打印整个链表（当作单向链表打印）
	{
		printf("\n");
		node* op = ring;
		for (int i = 0; i < len; i++)
		{
			printf("%ld,", op->data);
			op = op->next;
		}
	}
	node* _delete(node* Where)
	{
		//bool isFound = false;
		node* op = ring;
		do
		{
			op = op->next;
		} while (op->next != Where);//先找到要删除的节点位置
		/*
		* if(Where == op) isFound = true;
		* else{return nullptr;};
		*/
		//由于在此类中，此函数的调用只会发生在solve函数中。也就是Where一定存在，因此不赘述找不到的结果
		op->next = op->next->next;//先将要删除的节点从链表内解下
		if (Where == ring)//如果是头节点就移动头节点，头节点不能删除
		{
			ring = op;
		}
		free(Where);//释放删除的节点空间
		len--;//长度减一
		return op;
	}
	node* ring;
	long len;
	long code;

};
int solve()
{
	unsigned long m = 0, n = 0;
	printf("对任意 n 个人，密码为 m，实现约瑟夫环问题。\n输入n =");
	if (scanf("%ld", &n) == -1) return -1;//如果输入错误或是不满足输入的条件，就退出
											//scanf的返回值由输入的符合数决定
	printf("m =");
	if (scanf("%ld", &m) == -1) return -1;
	JosephRing question(n, m);
	printf("出列顺序为\n");
	question.solve([](long& e)->void {printf("%d,", e); });//使用lambda表达式生成伪函数，以此进行输出
	return 0;
}
#endif // !

#ifndef LinkArray
//此算法已经通过洛谷OJ评测
/*Accepted
#1 2ms/488.00KB
#2 2ms/508.00KB
#3 2ms/636.00KB
#4 2ms/624.00KB
*/
int solve()
{
	unsigned long m = 0, n = 0;
	printf("对任意 n 个人，密码为 m，实现约瑟夫环问题。\n输入n =");
	if (scanf("%ld", &n) == -1) return -1;
	printf("m =");
	if (scanf("%ld", &m) == -1) return -1;

	vector<long> vec;
	for (long i = 0; i < n; i++)	//生成环
	{
		vec.push_back(i + 1);
	}

	printf("出列次序依次为：\n");
	long lRemain = n;	//还剩多少人
	long lOut = 0;		//外层循环索引
	long lIn = 1;		//内存循环索引
	do   //外层一直循环
	{
		if (lOut >= n)lOut = 0;	//如果发现已经到表尾，就将外层循环索引置为
		if (vec.at(lOut) != -2) //如果已经出列就标记为-2，否则进行计数
		{
			if (lIn == m)	//如果命中
			{
				printf(" #%d, ", vec.at(lOut));	//出列
				vec.at(lOut) = -2;		//标记
				lIn = 0;	//内层循环置0
				lRemain--;
			}
			lIn++;
		}
		lOut++;
	} while (lRemain != 0);
	return 0;
}

#endif // !LinkArray

//此行表明了最终实现的函数形式，请注释掉此行并且注释其他main函数防止符号重用
// 已通过调试
//int _main_(int argc, char** argv){return solve();}