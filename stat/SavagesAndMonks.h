#pragma once
int N, C;

#define MAXN 10000
typedef struct { //Boat
	int Monk;                //修道士的数量
	int Savage;              //野人的数量
	bool state;              //船的状态 1表示船在起始岸边 0表示在目的地
} Boat;

Boat Boatsafe[MAXN];

typedef struct Edge {
	int adjvex;              //该边所指向的顶点的位置
	struct Edge* nextedge;   //next域 指向下一条边
} Edge;

typedef struct Vnode {
	Boat data;				//顶点上的数据信息
	int  number;            //顶点编号
	int pre;				//前驱
	Edge* firstedge;        //指向第一个依附该点的边
} Vnode;

class Algraph { //graph
public:
	Vnode vertices[MAXN];
	int vexnum, edgenum;		//图当前的顶点数以及边的数量
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
		vertices[v1].firstedge = p;//实现从表头插入数据

		edgenum++;
	}
};

