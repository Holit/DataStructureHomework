#pragma once
#include <time.h>

//��Ϸ��
struct People {
	unsigned int num;//���
	unsigned int score;//�÷�
	People() = default;
	/// <summary>
	/// ����һ���µĽṹ
	/// </summary>
	/// <param name="num"></param>
	/// <param name="score"></param>
	People(long num, int score)
	{
		this->num = num;
		this->score = score;
	}
} ;

//�Ѵ洢�ṹ
class Peoples {
public:
	People* datas;
	int length;
	/// <summary>
	/// Ĭ�Ϲ��캯�������ṩ�κβ�������˽�ָ���ÿ�
	/// </summary>
	Peoples() 
	{
		datas = nullptr;
		length = -1;
	} 
	/// <summary>
	/// ʹ��������ݳ�ʼ��
	/// </summary>
	/// <param name="n">Peolpe�������</param>
	Peoples(long long n,int & seed)
	{
		if (seed == -1)
		{
			srand(time(0));
			seed = rand() % rand();//Ϊ�˱�֤�´οɸ��֣��˴�ʹ�������Ӵ洢
		}

		datas = (People*)malloc(sizeof(People) * n);
		if (!datas)exit(OVERFLOW);

		srand(seed);

		for (int i = 0; i < n; i++) {
			datas[i].num = i;
			int r = rand() % 1000;
			//Ϊ�˷�ֹ�㷨�ϳ���ϸ΢�Ĳ��죬���ǵ����ȶ����������δ��ɼ�ѡ�����������㷨��
			// ��������˲��ظ�ֵ������
			while (isAlreadyExisted(r))	//����Ѿ�����
			{
				r = rand() % 1000;	//����ȡһ��
			};

			datas[i].score = r;
		}
		length = n;
	}
	/// <summary>
	/// ��ֵ��ʼ��
	/// </summary>
	/// <param name="n">Peolpe�������</param>
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
	/// ���ƹ��캯��
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
	/// ���ƹ��������
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
	/// ��ӡ�����ݣ�ʹ��10�еĸ�ʽ
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
	//Ĭ����������
	~Peoples()
	{
		if (datas) free(datas);
	}
private:
	/// <summary>
	/// �ж�pֵ�Ƿ����������Ѿ����ֹ�
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
/// ����˳����ҵķ���Ѱ�Ҽ���ֵ�ʹδ�ֵ
/// </summary>
void findmax_sequece(const Peoples& src, People& max, People& smax) {
	//���Ƶ����ݣ���ֹ��Ԫ��������޸�
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
/// ���������ڲ���������
/// </summary>
/// <param name="p"></param>
/// <param name="s">��ʼ������λ��</param>
/// <param name="end">����������λ��</param>
void _champion_adjust(Peoples* p, int s, int end) {
	int lchild = 2 * s;
	int rchild = 2 * s + 1;
	if (lchild >= end) {
		p->datas[s].score = 0; //sΪҶ�ӽڵ�
		return;
	}
	else if (rchild >= end) {
		p->datas[s] = p->datas[lchild];	//s������������������
		return;
	}

	if (p->datas[lchild].num == p->datas[s].num)_champion_adjust(p, lchild, end);
	else _champion_adjust(p, rchild, end);

	p->datas[s] = (p->datas[lchild].score > p->datas[rchild].score) ? p->datas[lchild] : p->datas[rchild];
	return;
}
/// <summary>
/// �����������Ҽ���ֵ�ʹμ���ֵ
/// </summary>
void findmax_champion(const Peoples& src, People& max, People& smax) {

	Peoples p = src;
	int lchild, rchild, length = 1;

	while (length < p.length) length *= 2;

	int maxsize = length * 2;

	Peoples C(maxsize,0);

	for (int i = length; i <= maxsize; i++) { 
		//�Ƚ���������Ͷ˼��������ĵ�һ��
		if (i - length <= p.length)
			C.datas[i] = p.datas[i - length];
		else {
			C.datas[i].score = -1;//��������Ϊ-1
		}
	}
	for (int i = length - 1; i > 0; i--) { 
		//�Ƚ�����������С ��Ļ�ʤ���Ͻ���
		lchild = 2 * i;
		rchild = 2 * i + 1;
		C.datas[i] = (C.datas[lchild].score > C.datas[rchild].score) ? C.datas[lchild] : C.datas[rchild];
	}

	for (int i = 1; i <= 2; i++) { //ѡ�����Ǿ�����
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
			++j;//jָ��ϴ�ĺ��ӽڵ�
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
/// �����򷨲��Ҽ���ֵ�ʹμ���ֵ
/// </summary>
void findmax_heap(const Peoples& p, People& max, People& smax) {
	Peoples H = p;

	for (int i = H.length / 2 - 1; i >= 0; i--) //��H.rchild[1..length]��Ϊ�󶥶�
		_heap_adjust(&H, i, H.length);

	for (int i = H.length - 1; i > 0; i--) {
		swap(H.datas[0] , H.datas[i]);
		//�����Ѷ��������ɱ�������
		_heap_adjust(&H, 0, i - 1);//��1..i-1���µ��ɴ󶥶�
	}
	max = H.datas[H.length - 1];
	smax = H.datas[H.length - 2];
}