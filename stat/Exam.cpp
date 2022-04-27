/*
考试日程安排与成绩统计
问题描述
* 现要安排考试的考表（即考试日程表），假设共有10 个班的学生，要安排10 门必修课程的考试，必修课程是
以班级来确定的，每个班各有3门必修课，因此各班的考试科目是不相同的；安排考表的原则是：相同课程采用统
一的试卷，因此同一门课程的考试必须在相同时间进行，同一个班所修的科目必须安排在不同的时间进行考试，以
避免考试时间的冲突。并要求全部考试的日程尽可能短。
* 要求对考试结果做统计和排序。假设分别以编号0,1,2,3,4,5,6,7,8,9 代表10 门要考试的课程，
以B1，B2，B3，B4，B5，B6，B7，B8，B9，B10 代表10 个班，每个人的信息包括学号、姓名、班级、各门考试课程成绩、
三门课程总成绩，每个班的学生人数自行设定。要求设计一个简单的考试成绩的查询统计系统实现以下功能：

* 显示学生考试情况
* 按考试总分从高到底输出全体学生的信息。
* 按照从B1 到B10 的班级顺序，分班级按照考试总分从高到底的顺序输出各班学生的信息。
* 输出指定班的学生考试成绩信息。
* 统计学生考试成绩
* 按总成绩统计出90 分以上、80~89 分、70~79 分、60~69 分、60 分以下各分数段的人数，并按总分从高到低分段输出。
* 根据指定的某们课程的成绩，统计出上述各分数段的人数，并按分数从高到低分段输出。
* 统计并输出指定班级中总成绩或某一门课成绩的各分数段人数和每个人具体的信息。
* 查找学生成绩
* 查找总分或某一门课程成绩的指定分数段的人数及学生的详细信息。
* 查找指定班级中总分或某一门课程成绩属于某分数段的学生详细信息。
* 查找指定学生（例如给定学号）的具体信息，包括：姓名、班级、各科分数、总分数等。
*/
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<vector>

#include "defs.h"
#include "Exam.h"


int main() {
	printf("##欢迎使用本科生课程考试管理系统##\n");
	printf("===============================\n\n");
	printf("初始化：导入数据，请稍候...\n");
	importNameData();
	importCourseData();
	importScoreData();

	clear();
	int n;
	int x;
	
	showMenu();
	printf(">");
	while (cin >> n) {
		switch (n) {
		case 1:GetCourse();break;
		case 2:Solve();break;
		case 3:
			printf("\t\t请选择功能");
			printf("---1.所有学生按总分排序\n");
			printf("---2.按照班级排序再按总分排序\n");
			printf("---3.统计成绩\n");
			printf("---4.查找成绩\n");
			printf(">");
			cin >> x;
			switch (x) {
			case 1:
				sort1();
				break;
			case 2:
				sort2();
				break;
			case 3:
				Count();
				break;
			case 4:
				Search();
				break;
			}
			break;
		case 4:exit(0);
		}
		system("pause");
		showMenu();
		printf(">");
	}
	return 0;
}
