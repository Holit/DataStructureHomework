#pragma once

#define maxn 1005

using namespace std;

//ѧ������ 
struct _student {
	char name[20];
	int classes;		//�༶ 
	int goal[3];	//���ű��޿γɼ� 
	int all;		//�ܳɼ� 
};

//�༶����
struct _class {
	int course[3];		//�ð༶���ű��޿� 
	_student stu[10];	//�༶ѧ�� 
} classes[10];

int confilt[maxn][maxn];//��ͻ 

void showMenu() {
	system("cls");
	printf("##��ӭʹ�ñ������γ̿��Թ���ϵͳ##\n");
	printf("===============================\n\n");
	printf("\t\t1.�γ̲鿴\n");
	printf("\t\t2.���԰���\n");
	printf("\t\t3.�鿴�ɼ�\n");
	printf("\t\t4.�˳�ϵͳ\n");
	printf("\t\t��������Ӧ��ָ����Ų�����Enter������\n");
}
//���ֱܷȽϣ�����ͬ�Ƚϰ༶ 
bool cmp1(_student a, _student b) {
	if (a.all == b.all)
		return a.classes < b.classes;
	else
		return a.all > b.all;
}
//���༶���бȽϣ������ֱܷȽ� 
bool cmp2(_student a, _student b) {
	if (a.classes == b.classes)
		return a.all > b.all;
	else
		return a.classes < b.classes;
}

bool cmpp1(_student a, _student b) {//����һ�ű��޿αȽ� 
	return a.goal[0] > b.goal[0];
}
bool cmpp2(_student a, _student b) {//���ڶ��ű��޿αȽ� 
	return a.goal[1] > b.goal[1];
}
bool cmpp3(_student a, _student b) {//�������ű��޿αȽ� 
	return a.goal[2] > b.goal[2];
}

void Count() {//������Ҫ��ͳ�Ƴɼ��ֲ� 
	_student stu2[105];
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			stu2[sum++] = classes[i].stu[j];
		}
	}
	printf( "\t\t----��ѡ����\n" );
	printf( "\t\t----1.ͳ�ƿ�Ŀ�ɼ��ֲ�\n" );
	printf( "\t\t----2.ͳ���ܳɼ��ֲ�\n" );
	printf( "\t\t----3.ͳ�ư༶ĳ��Ŀ�ɼ��ֲ�\n" );
	int x;
	cin >> x;
	if (x == 1) {
		int ans[5];//0-60,60-70,70-80,80-90,90-100.
		memset(ans, 0, sizeof(ans));
		printf( "\t\t----��������Ҫѡ��ѡ��Ŀ�Ŀ\n\t");
		int y;
		cin >> y;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 3; j++) {
				if (classes[i].course[j] == y) {
					for (int k = 0; k < 10; k++) {
						int z = classes[i].stu[k].goal[j];
						if (z >= 0 && z <= 59) {
							ans[0]++;
						}
						else if (z >= 60 && z <= 69) {
							ans[1]++;
						}
						else if (z >= 70 && z <= 79) {
							ans[2]++;
						}
						else if (z >= 80 && z <= 89) {
							ans[3]++;
						}
						else {
							ans[4]++;
						}
					}
					break;
				}
			}
		}
		printf( "\t\t0-59�����ε�����Ϊ   %d\n",ans[0]);
		printf( "\t\t60-69�����ε�����Ϊ  %d\n",ans[1]);
		printf( "\t\t70-79�����ε�����Ϊ  %d\n",ans[2]);
		printf( "\t\t80-89�����ε�����Ϊ  %d\n",ans[3]);
		printf( "\t\t90-100�����ε�����Ϊ %d\n",ans[4]);
	}
	else if (x == 2) {
		int ans[4];//0-100,100-200,200-250,250-300
		memset(ans, 0, sizeof(ans));
		for (int i = 0; i < sum; i++) {
			if (stu2[i].all >= 0 && stu2[i].all < 100)
				ans[0]++;
			else if (stu2[i].all >= 100 && stu2[i].all < 200)
				ans[1]++;
			if (stu2[i].all >= 200 && stu2[i].all < 250)
				ans[2]++;
			if (stu2[i].all >= 250 && stu2[i].all <= 300)
				ans[3]++;
		}
		printf( "\t\t  0-99 �����ε�����Ϊ %d\n",ans[0] );
		printf( "\t\t100-199�����ε�����Ϊ %d\n",ans[1] );
		printf( "\t\t200-249�����ε�����Ϊ %d\n",ans[2] );
		printf( "\t\t250-300�����ε�����Ϊ %d\n",ans[3] );
	}
	else {
		int a, b;
		_student ans[10];
		int summ = 0;
		printf( "\t\t��������Ҫ��ѯ�İ༶\n\t");
		cin >> a;
		printf( "\t\t��������Ҫ��ѯ�Ŀ�Ŀ\n" );
		printf( "\t\t1.%d \n \t\t2.%d \n \t\t3.%d\t\n", 
			classes[a].course[0], 
			classes[a].course[1], 
			classes[a].course[2]);

		cin >> b;
		for (int i = 0; i < 10; i++)
			ans[summ++] = classes[a].stu[i];
		if (b == 1)
			sort(ans, ans + summ, cmpp1);
		if (b == 2)
			sort(ans, ans + summ, cmpp2);
		if (b == 3)
			sort(ans, ans + summ, cmpp3);
		for (int i = 0; i < 10; i++)
			printf( "\t\t%s %d\n",ans[i].name,ans[i].goal[b - 1]);
	}
}
void Search() {
	char name[10];
	_student stu2[105];
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			stu2[sum++] = classes[i].stu[j];
		}
	}
	printf( "\t\t��������Ҫ���ҵ�ѧ������\n\t");
	scanf("%s", name);
	for (int i = 0; i < sum; i++) {
		if (strcmp(name, stu2[i].name) == 0) {
			printf( "\t\t��Ҫ���ҵ�ѧ����ϢΪ\n\n" );
			printf( "����%s\t\n",stu2[i].name );
			printf( "�༶%d\t\n",stu2[i].classes );
			printf( "�ܷ�%d\t\n",stu2[i].all );
			printf( "ѧϰ��Ŀ%d,%d,%d\t\n",
				classes[stu2[i].classes].course[0],
				classes[stu2[i].classes].course[1],
				classes[stu2[i].classes].course[2]);
			printf( "���Ƶ÷�%d,%d,%d\t\n",
				stu2[i].goal[0],
				stu2[i].goal[1],
				stu2[i].goal[2]);
			break;
		}
	}
}
void sort1() {//���ܷ����� 
	_student stu2[105];
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			stu2[sum++] = classes[i].stu[j];
		}
	}
	sort(stu2, stu2 + sum, cmp1);
	printf( "\t\t����\t�༶\t�÷�\n");
	for (int i = 0; i < sum; i++)
		printf("\t\t%s\tB%d\t%d\n", stu2[i].name, stu2[i].classes, stu2[i].all);
}
//�༶�ڲ��ܷ����� 
void sort2() {
	_student stu2[105];
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			stu2[sum++] = classes[i].stu[j];
		}
	}
	sort(stu2, stu2 + sum, cmp2);
	printf( "\t\t����\t�༶\t�÷�\n" );
	for (int i = 0; i < sum; i++)
		printf("\t\t%s\tB%d\t%d\n", stu2[i].name, stu2[i].classes, stu2[i].all);
}

void importNameData() {//��ȡѧ������ 
	FILE* fp;
	fp = fopen("name.txt", "r+");
	if (!fp)
	{
		printf("�޷���ȡѧ�������ļ� : name.txt�ļ�������\n");
		system("pause");
		exit(-1);
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			fscanf(fp, "%s", classes[i].stu[j].name);
			classes[i].stu[j].classes = i + 1;
		}
	}
	fclose(fp);
}

void importCourseData() {//���ļ��ж���γ̰��ţ�����ͬһ��������ſλ����ͻ��ӵ����� 
	int x, y, z;
	FILE* fp;
	fp = fopen("schedule.txt", "r+");	
	if (!fp)
	{
		printf("�޷���ȡ�γ������ļ� : schedule.txt �ļ�������\n");
		system("pause");
		exit(-1);
	}
	for (int i = 0; i < 10; i++) {
		fscanf(fp, "%d,%d,%d", &x, &y, &z);
		classes[i].course[0] = x;
		classes[i].course[1] = y;
		classes[i].course[2] = z;
		confilt[x][y] = 1;
		confilt[y][x] = 1;
		confilt[x][z] = 1;
		confilt[z][x] = 1;
		confilt[y][z] = 1;
		confilt[z][y] = 1;
	}
	fclose(fp);
	return;
}
void importScoreData() {
	FILE* fp;
	fp = fopen("score.txt", "r+");
	if (!fp)
	{
		printf("�޷���ȡ�ɼ��ļ� : score.txt �ļ�������\n");
		system("pause");
		exit(-1);
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 10; k++) {
				fscanf(fp, "%d", &classes[i].stu[k].goal[j]);
				classes[i].stu[k].all += classes[i].stu[k].goal[j];
			}
		}
	}
	fclose(fp);
}
void GetCourse() {
	printf( "\t\t����������ѡ��Ĺ���\n" );
	printf( "\t\t      1.�鿴ָ���༶�γ̱�-----------\n" );
	printf( "\t\t      2.�鿴���а༶�γ̱�-----------\n\t");
	int n;
	cin >> n;
	if (n == 1) {
		int x;
		printf( "\t\t��������Ҫ��ѯ�İ༶\n\t");
		cin >> x;
		printf( "�ð༶�Ŀγ�Ϊ");
		for (int i = 0; i < 3; i++)printf("%d,", classes[x - 1].course[i]);
		printf("\n");
	}
	else {
		for (int i = 0; i < 10; i++) {
			printf( "B%d��Ŀγ�Ϊ",i + 1);
			for (int j = 0; j < 3; j++)printf("%d,", classes[i].course[i]);
			printf("\n");
		}
	}
	return;
}

int sum_;
vector<int> v[10];//���շ��� 
int b[10];//���Կ�Ŀ 

void clear() {
	sum_ = 0;
	memset(classes, 0, sizeof(classes));
	memset(b, 0, sizeof(b));
	memset(confilt, 0, sizeof(confilt));
}

void Solve() {//�����ͻ 
	queue<int> q;
	int flag = 0;
	int flag2 = 0;
	memset(b, 0, sizeof(b));
	for (int i = 0; i < 10; i++) {
		q.push(i);
	}
	while (!q.empty()) {

		int x = q.front();
		if (b[x] != flag) {//ÿ�ֱ����꣬��֮ǰ��ͻ������һ��ʱ����� 
			flag = !flag;
			sum_++;
		}
		q.pop();
		b[x] = !b[x];
		flag2 = 0;
		for (int i = 0; i < v[sum_].size(); i++) {
			if (confilt[v[sum_][i]][x] == 1) {
				flag2 = 1;
				break;
			}
		}
		if (flag2 == 1)//���԰��ų�ͻѹ������������ 
			q.push(x);
		else {
			v[sum_].push_back(x);
		}
	}
	for (int i = 0; i < sum_+1; i++) {
		printf( "\t\t��%d��ʱ��ο�\n\t\t",i + 1);
		for (int j = 0; j < v[i].size(); j++)
			printf("%d,",v[i][j]);
	}
	return;
}


