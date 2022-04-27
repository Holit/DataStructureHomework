//4.A.cpp
//
//数据结构与程序设计实验
//
//实验4 A档实验
//作者：Jerry Gao
//请联系gao1021229073@163.com反馈漏洞和bug
//
//要启用此文件，请取消下述Experiment_4_A_Enabled的注释
//注意：一次只能启用一个实验文件进行编译
//#define Experiment_4_A_Enabled
//固定编译头，勿更改
#ifdef Experiment_4_A_Enabled
	#ifndef _main_
		#define _main_ main
	#else
		#error "函数名冲突：启用了两个或以上的实验源代码文件"
	#endif
#endif // !Experiment_4_A_Enabled
#include "defs.h" 


/*
* 文件压缩
* 22
* ①基本要求
* 哈夫曼编码是一种常用的数据压缩技术，对数据文件进行哈夫曼编码可大大
* 缩短文件的传输长度，提高信道利用率及传输效率。要求采用哈夫曼编码原理，
* 统计文本文件中字符出现的词频，以词频作为权值，对文件进行哈夫曼编码以达
* 到压缩文件的目的，再用哈夫曼编码进行译码解压缩。
* -  统计待压缩的文本文件中各字符的词频，以词频为权值建立哈夫曼树，
* 并将该哈夫曼树保存到文件 HufTree.dat 中。
* -  根据哈夫曼树（保存在 HufTree.dat 中）对每个字符进行哈夫曼编码，并
* 将字符编码保存到 HufCode.txt 文件中。
* -  压缩：根据哈夫曼编码，将源文件进行编码得到压缩文件 CodeFile.dat。
* -  解压：将 CodeFile.dat 文件利用哈夫曼树译码解压，恢复为源文件。
* ②选做要求
* -  实现 Burrows-Wheeler 压缩算法。
* -  比较 Burrows-Wheeler 压缩算法与单纯的哈夫曼编码压缩算法的压缩效
* 率。
* 针对不同长度的文件，统计 Burrows-Wheeler 压缩算法的执行时间。

*/