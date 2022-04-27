#pragma once
#include <time.h>

//游戏者
struct People {
	unsigned int num;//编号
	unsigned int score;//得分
	People() = default;
	/// <summary>
	/// 构造一个新的结构
	/// </summary>
	/// <param name="num"></param>
	/// <param name="score"></param>
	People(long num, int score)
	{
		this->num = num;
		this->score = score;
	}
} ;

//堆存储结构
class Peoples {
public:
	People* datas;
	int length;
	/// <summary>
	/// 默认构造函数：不提供任何参数，因此将指针置空
	/// </summary>
	Peoples() 
	{
		datas = nullptr;
		length = -1;
	} 
	/// <summary>
	/// 使用随机数据初始化
	/// </summary>
	/// <param name="n">Peolpe类的数量</param>
	Peoples(long long n,int & seed)
	{
		if (seed == -1)
		{
			srand(time(0));
			seed = rand() % rand();//为了保证下次可复现，此处使用了种子存储
		}

		datas = (People*)malloc(sizeof(People) * n);
		if (!datas)exit(OVERFLOW);

		srand(seed);

		for (int i = 0; i < n; i++) {
			datas[i].num = i;
			int r = rand() % 1000;
			//为了防止算法上出现细微的差异，考虑到非稳定排序和排序未完成即选择产生结果的算法，
			// 这里进行了不重复值创建。
			while (isAlreadyExisted(r))	//如果已经存在
			{
				r = rand() % 1000;	//就再取一个
			};

			datas[i].score = r;
		}
		length = n;
	}
	/// <summary>
	/// 定值初始化
	/// </summary>
	/// <param name="n">Peolpe类的数量</param>
	Peoples(long long n, long value)
	{
		datas = (People*)malloc(sizeof(People) * n);
		if (!datas)exit(OVERFLOW);

		for (int i = 0; i <= n; i++) {
			datas[i].num = i;
			datas[i].score = value;
		}
		length = n;
	}
	/// <summary>
	/// 复制构造函数
	/// </summary>
	/// <param name="p2"></param>
	Peoples(const Peoples& p2)
	{
		this->datas = nullptr;
		length = p2.length;
		this->datas = (People*)malloc(sizeof(People) * length);
		if (!datas)exit(OVERFLOW);

		for (int i = 0; i <= length; i++) {
			datas[i].num = p2.datas[i].num;
			datas[i].score = p2.datas[i].score;
		}
	}
	/// <summary>
	/// 复制构造运算符
	/// </summary>
	Peoples operator=(const Peoples& p2)
	{
		length = p2.length;
		this->datas = (People*)realloc(this->datas, sizeof(People) * length);
		if (!this->datas)exit(OVERFLOW);
		for (int i = 0; i <= this->length; i++) {
			datas[i].num = p2.datas[i].num;
			datas[i].score = p2.datas[i].score;
		}
	}
	/// <summary>
	/// 打印此数据，使用10列的格式
	/// </summary>
	void print()
	{
		int n = length;
		for (int i = 0; i < n-n%10; i += 10) {
			printf("%4d,%4d %4d,%4d %4d,%4d %4d,%4d %4d,%4d %4d,%4d %4d,%4d %4d,%4d %4d,%4d %4d,%4d\n",
				this->datas[i + 0].num, this->datas[i + 0].score,
				this->datas[i + 1].num, this->datas[i + 1].score,
				this->datas[i + 2].num, this->datas[i + 2].score,
				this->datas[i + 3].num, this->datas[i + 3].score,
				this->datas[i + 4].num, this->datas[i + 4].score,
				this->datas[i + 5].num, this->datas[i + 5].score,
				this->datas[i + 6].num, this->datas[i + 6].score,
				this->datas[i + 7].num, this->datas[i + 7].score,
				this->datas[i + 8].num, this->datas[i + 8].score,
				this->datas[i + 9].num, this->datas[i + 9].score
			);
		}
		for (int i = 0; i < n % 10; i++)
		{
			printf("%4d,%4d ",
				datas[n - n % 10 + i].num, datas[n - n % 10 + i].score
			);
		}
		printf("\n");
	}
	//默认析构函数
	~Peoples()
	{
		if (datas) free(datas);
	}
private:
	/// <summary>
	/// 判定p值是否在数据中已经出现过
	/// </summary>
	bool isAlreadyExisted(int p)
	{
		for (int i = 0; i < length; i++)
		{
			if (datas[i].score == p)return true;
		}
		return false;
	}

};



/// <summary>
/// 按照顺序查找的方法寻找极大值和次大值
/// </summary>
void findmax_sequece(const Peoples& src, People& max, People& smax) {
	//复制的数据，防止对元数据造成修改
	Peoples e = src;

	max.score = 0;
	smax.score =0;

	for (int i = 0; i < e.length; i++) {

		if (max.score < e.datas[i].score) {
			smax = max;
			max.num = e.datas[i].num;
			max.score = e.datas[i].score;
		}
		else if (smax.score < e.datas[i].score) {
			smax.num = e.datas[i].num;
			smax.score = e.datas[i].score;
		}
	}
}

/// <summary>
/// 锦标赛法内部调整函数
/// </summary>
/// <param name="p"></param>
/// <param name="s">开始调整的位置</param>
/// <param name="end">结束调整的位置</param>
void _champion_adjust(Peoples* p, int s, int end) {
	int lchild = 2 * s;
	int rchild = 2 * s + 1;
	if (lchild >= end) {
		p->datas[s].score = 0; //s为叶子节点
		return;
	}
	else if (rchild >= end) {
		p->datas[s] = p->datas[lchild];	//s有左子树，无右子树
		return;
	}

	if (p->datas[lchild].num == p->datas[s].num)_champion_adjust(p, lchild, end);
	else _champion_adjust(p, rchild, end);

	p->datas[s] = (p->datas[lchild].score > p->datas[rchild].score) ? p->datas[lchild] : p->datas[rchild];
	return;
}
/// <summary>
/// 锦标赛法查找极大值和次极大值
/// </summary>
void findmax_champion(const Peoples& src, People& max, People& smax) {

	Peoples p = src;
	int lchild, rchild, length = 1;

	while (length < p.length) length *= 2;

	int maxsize = length * 2;

	Peoples C(maxsize,0);

	for (int i = length; i <= maxsize; i++) { 
		//先建立树的最低端即锦标赛的第一轮
		if (i - length <= p.length)
			C.datas[i] = p.datas[i - length];
		else {
			C.datas[i].score = -1;//不存在置为-1
		}
	}
	for (int i = length - 1; i > 0; i--) { 
		//比较左右子树大小 大的获胜向上晋级
		lchild = 2 * i;
		rchild = 2 * i + 1;
		C.datas[i] = (C.datas[lchild].score > C.datas[rchild].score) ? C.datas[lchild] : C.datas[rchild];
	}

	for (int i = 1; i <= 2; i++) { //选出冠亚军即可
		p.datas[i] = C.datas[1];
		_champion_adjust(&C, 1, maxsize);
	}
	max = p.datas[1];
	smax = p.datas[2];
}


void _heap_adjust(Peoples* H, int s, int m) {
	People rc = H->datas[s];
	int j;
	for (j = 2 * s; j < m; j *= 2)
	{
		if (j < m && (H->datas[j].score < H->datas[j + 1].score))
		{
			++j;//j指向较大的孩子节点
		}
		if (!(rc.score < H->datas[j].score))
		{
			break;
		}
		H->datas[s] = H->datas[j];
		s = j;
	}
	H->datas[s] = rc;
}
void swap(People& p1, People& p2) { People t = p2; p2 = p1; p1 = t; };

/// <summary>
/// 堆排序法查找极大值和次极大值
/// </summary>
void findmax_heap(const Peoples& p, People& max, People& smax) {
	Peoples H = p;

	for (int i = H.length / 2 - 1; i >= 0; i--) //把H.rchild[1..length]建为大顶堆
		_heap_adjust(&H, i, H.length);

	for (int i = H.length - 1; i > 0; i--) {
		swap(H.datas[0] , H.datas[i]);
		//交换堆顶到最后完成本次排序
		_heap_adjust(&H, 0, i - 1);//将1..i-1重新调成大顶堆
	}
	max = H.datas[H.length - 1];
	smax = H.datas[H.length - 2];
}