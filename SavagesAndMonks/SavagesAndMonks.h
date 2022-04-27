#pragma once
int N, C;

#define MAXN 10000
typedef struct { //Boat
	int Monk;                //�޵�ʿ������
	int Savage;              //Ұ�˵�����
	bool state;              //����״̬ 1��ʾ������ʼ���� 0��ʾ��Ŀ�ĵ�
} Boat;

Boat Boatsafe[MAXN];

typedef struct Edge {
	int adjvex;              //�ñ���ָ��Ķ����λ��
	struct Edge* nextedge;   //next�� ָ����һ����
} Edge;

typedef struct Vnode {
	Boat data;				//�����ϵ�������Ϣ
	int  number;            //������
	int pre;				//ǰ��
	Edge* firstedge;        //ָ���һ�������õ�ı�
} Vnode;

class Algraph { //graph
public:
	Vnode vertices[MAXN];
	int vexnum, edgenum;		//ͼ��ǰ�Ķ������Լ��ߵ�����
	Algraph()
	{
		vexnum = 0;
		edgenum = 0;

		for (int i = 0; i < MAXN; i++) {
			vertices[i].number = i;
			vertices[i].firstedge = NULL;
			vertices[i].data.state = -1;
			vertices[i].pre = -1;
		}
	}
	void insert(/*Algraph* G,*/ int i, Boat vertex) {
		vertices[i].data.Monk = vertex.Monk;
		vertices[i].data.Savage = vertex.Savage;
		vertices[i].data.state = vertex.state;
		vexnum++;
	}
	void insertEdge(/*Algraph* G,*/ int v1, int v2) {
		Edge* p;
		p = (Edge*)malloc(sizeof(Edge));
		p->adjvex = v2;

		p->nextedge = vertices[v1].firstedge;
		vertices[v1].firstedge = p;//ʵ�ִӱ�ͷ��������

		edgenum++;
	}
};

