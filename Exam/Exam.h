#pragma once

#define maxn 1005

using namespace std;

//学生类型 
struct _student {
	char name[20];
	int classes;		//班级 
	int goal[3];	//三门必修课成绩 
	int all;		//总成绩 
};

//班级类型
struct _class {
	int course[3];		//该班级三门必修课 
	_student stu[10];	//班级学生 
} classes[10];

int confilt[maxn][maxn];//冲突 

void showMenu() {
	system("cls");
	printf("##欢迎使用本科生课程考试管理系统##\n");
	printf("===============================\n\n");
	printf("\t\t1.课程查看\n");
	printf("\t\t2.考试安排\n");
	printf("\t\t3.查看成绩\n");
	printf("\t\t4.退出系统\n");
	printf("\t\t请输入相应的指令序号并按下Enter键继续\n");
}
//按总分比较，若相同比较班级 
bool cmp1(_student a, _student b) {
	if (a.all == b.all)
		return a.classes < b.classes;
	else
		return a.all > b.all;
}
//按班级进行比较，班内总分比较 
bool cmp2(_student a, _student b) {
	if (a.classes == b.classes)
		return a.all > b.all;
	else
		return a.classes < b.classes;
}

bool cmpp1(_student a, _student b) {//按第一门必修课比较 
	return a.goal[0] > b.goal[0];
}
bool cmpp2(_student a, _student b) {//按第二门必修课比较 
	return a.goal[1] > b.goal[1];
}
bool cmpp3(_student a, _student b) {//按第三门必修课比较 
	return a.goal[2] > b.goal[2];
}

void Count() {//按各种要求统计成绩分布 
	_student stu2[105];
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			stu2[sum++] = classes[i].stu[j];
		}
	}
	printf( "\t\t----请选择功能\n" );
	printf( "\t\t----1.统计科目成绩分布\n" );
	printf( "\t\t----2.统计总成绩分布\n" );
	printf( "\t\t----3.统计班级某科目成绩分布\n" );
	int x;
	cin >> x;
	if (x == 1) {
		int ans[5];//0-60,60-70,70-80,80-90,90-100.
		memset(ans, 0, sizeof(ans));
		printf( "\t\t----请输入您要选择选择的科目\n\t");
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
		printf( "\t\t0-59分数段的人数为   %d\n",ans[0]);
		printf( "\t\t60-69分数段的人数为  %d\n",ans[1]);
		printf( "\t\t70-79分数段的人数为  %d\n",ans[2]);
		printf( "\t\t80-89分数段的人数为  %d\n",ans[3]);
		printf( "\t\t90-100分数段的人数为 %d\n",ans[4]);
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
		printf( "\t\t  0-99 分数段的人数为 %d\n",ans[0] );
		printf( "\t\t100-199分数段的人数为 %d\n",ans[1] );
		printf( "\t\t200-249分数段的人数为 %d\n",ans[2] );
		printf( "\t\t250-300分数段的人数为 %d\n",ans[3] );
	}
	else {
		int a, b;
		_student ans[10];
		int summ = 0;
		printf( "\t\t请输入你要查询的班级\n\t");
		cin >> a;
		printf( "\t\t请输入你要查询的科目\n" );
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
	printf( "\t\t请输入你要查找的学生姓名\n\t");
	scanf("%s", name);
	for (int i = 0; i < sum; i++) {
		if (strcmp(name, stu2[i].name) == 0) {
			printf( "\t\t您要查找的学生信息为\n\n" );
			printf( "姓名%s\t\n",stu2[i].name );
			printf( "班级%d\t\n",stu2[i].classes );
			printf( "总分%d\t\n",stu2[i].all );
			printf( "学习科目%d,%d,%d\t\n",
				classes[stu2[i].classes].course[0],
				classes[stu2[i].classes].course[1],
				classes[stu2[i].classes].course[2]);
			printf( "各科得分%d,%d,%d\t\n",
				stu2[i].goal[0],
				stu2[i].goal[1],
				stu2[i].goal[2]);
			break;
		}
	}
}
void sort1() {//按总分排序 
	_student stu2[105];
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			stu2[sum++] = classes[i].stu[j];
		}
	}
	sort(stu2, stu2 + sum, cmp1);
	printf( "\t\t姓名\t班级\t得分\n");
	for (int i = 0; i < sum; i++)
		printf("\t\t%s\tB%d\t%d\n", stu2[i].name, stu2[i].classes, stu2[i].all);
}
//班级内部总分排序 
void sort2() {
	_student stu2[105];
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			stu2[sum++] = classes[i].stu[j];
		}
	}
	sort(stu2, stu2 + sum, cmp2);
	printf( "\t\t姓名\t班级\t得分\n" );
	for (int i = 0; i < sum; i++)
		printf("\t\t%s\tB%d\t%d\n", stu2[i].name, stu2[i].classes, stu2[i].all);
}

void importNameData() {//读取学生名字 
	FILE* fp;
	fp = fopen("name.txt", "r+");
	if (!fp)
	{
		printf("无法读取学生名字文件 : name.txt文件不存在\n");
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

void importCourseData() {//从文件中读入课程安排，并将同一个班的三门课互相冲突添加到序列 
	int x, y, z;
	FILE* fp;
	fp = fopen("schedule.txt", "r+");	
	if (!fp)
	{
		printf("无法读取课程名字文件 : schedule.txt 文件不存在\n");
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
		printf("无法读取成绩文件 : score.txt 文件不存在\n");
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
	printf( "\t\t请输入您想选择的功能\n" );
	printf( "\t\t      1.查看指定班级课程表-----------\n" );
	printf( "\t\t      2.查看所有班级课程表-----------\n\t");
	int n;
	cin >> n;
	if (n == 1) {
		int x;
		printf( "\t\t请输入您要查询的班级\n\t");
		cin >> x;
		printf( "该班级的课程为");
		for (int i = 0; i < 3; i++)printf("%d,", classes[x - 1].course[i]);
		printf("\n");
	}
	else {
		for (int i = 0; i < 10; i++) {
			printf( "B%d班的课程为",i + 1);
			for (int j = 0; j < 3; j++)printf("%d,", classes[i].course[i]);
			printf("\n");
		}
	}
	return;
}

int sum_;
vector<int> v[10];//最终方案 
int b[10];//考试科目 

void clear() {
	sum_ = 0;
	memset(classes, 0, sizeof(classes));
	memset(b, 0, sizeof(b));
	memset(confilt, 0, sizeof(confilt));
}

void Solve() {//处理冲突 
	queue<int> q;
	int flag = 0;
	int flag2 = 0;
	memset(b, 0, sizeof(b));
	for (int i = 0; i < 10; i++) {
		q.push(i);
	}
	while (!q.empty()) {

		int x = q.front();
		if (b[x] != flag) {//每轮遍历完，将之前冲突的往下一个时间段排 
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
		if (flag2 == 1)//考试安排冲突压入队列最后在排 
			q.push(x);
		else {
			v[sum_].push_back(x);
		}
	}
	for (int i = 0; i < sum_+1; i++) {
		printf( "\t\t第%d个时间段考\n\t\t",i + 1);
		for (int j = 0; j < v[i].size(); j++)
			printf("%d,",v[i][j]);
	}
	return;
}


