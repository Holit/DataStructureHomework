/*
* （1）查找最高分与次高分
* ①问题描述
* 有512 人参与玩某游戏，从1~512 给每个人分配一个编号，每个人的游戏得分在0~999 之间，
* 现要用不同方法查找出游戏参与者的最高分和次高分。要求：
* . 自行产生512 个的随机整数作为所有游戏参与者的得分。
* . 输出所有游戏参与者（用编号表示）及其得分。
* . 用顺序查找方法查找出其中取得最高分和次高分者及其分数，并输出。
* . 锦标赛法查找出其中取得最高分和次高分者及其分数，并输出。
* . 通过无序序列建堆和堆调整得到取得最高分者和次高分者及其分数，并输出。
* . 比较不同方法的查找效率和各自的特点。
* 
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

#include "defs.h"
#include "ScoreSearching.h"
#include <windows.h>	//用于调用高精度计时器
using namespace  std;
/// <summary>
/// 参与游戏的人数，此值可以变更
/// </summary>
const int n = 512;

int main(int argc, char ** argv) 
{
	//指定或者获取随机数发生器的种子，方便于复现结果。
	//如果此seed设置为-1，则构造函数将按照时间生成一个随机种子。
	int seed = 46;
	Peoples p1(n,seed);
	printf("当前产生的随机数据的种子为:%d\n\n", seed);

	//高精度计时相关
	LARGE_INTEGER freq;
	LARGE_INTEGER start_t, stop_t;
	double exe_time;
	//获取当前操作系统速度
	QueryPerformanceFrequency(&freq);

	printf("各选手及其对应数据如下:\n\n----------------------------\n");
	for (int i = 0; i < 10; i++)printf("选手,分数 ");
	printf("\n");
	p1.print();

	//用于存储找到的第一、第二名
	People m1, m2;

	//调用高精度计时器对算法进行时间评估
	QueryPerformanceCounter(&start_t);
	findmax_sequece(p1,m1,m2);	//利用顺序方法进行查找
	QueryPerformanceCounter(&stop_t);
	exe_time = 1e3 * (stop_t.QuadPart - start_t.QuadPart) / freq.QuadPart;
	
	printf("顺序比较的结果：\n");
	printf("本次比赛最高分是 %4d 号，得分%4d\n", m1.num, m1.score);
	printf("本次比赛次高分是 %4d 号，得分%4d\n", m2.num, m2.score);
	printf("顺序法所用时间：%f ms\n\n", exe_time);

	QueryPerformanceCounter(&start_t);
	findmax_champion(p1, m1, m2);
	QueryPerformanceCounter(&stop_t);
	exe_time = 1e3 * (stop_t.QuadPart - start_t.QuadPart) / freq.QuadPart;

	printf("锦标赛法的结果：\n");
	printf("本次比赛最高分是 %4d 号，得分%4d\n", m1.num, m1.score);
	printf("本次比赛次高分是 %4d 号，得分%4d\n", m2.num, m2.score);
	printf("锦标赛法所用时间：%f ms\n\n", exe_time);

	QueryPerformanceCounter(&start_t);
	findmax_heap(p1,m1,m2);
	QueryPerformanceCounter(&stop_t);
	exe_time = 1e3 * (stop_t.QuadPart - start_t.QuadPart) / freq.QuadPart;

	printf("堆排序的结果：\n");
	printf("本次比赛最高分是 %4d 号，得分%4d\n", m1.num, m1.score);
	printf("本次比赛次高分是 %4d 号，得分%4d\n", m2.num, m2.score);
	printf("堆排序所用时间： %f ms\n\n", exe_time);


	return 0;
}