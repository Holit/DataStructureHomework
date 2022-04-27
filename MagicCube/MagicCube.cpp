

/*
* （1）魔方阵
* ①问题描述
* 魔方阵是一个古老的智力问题，它要求在一个 m×m 的矩阵中填入 1～m
* 2的
* 数字（m 为奇数），使得每一行、每一列、每条对角线的累加和都相等，如图 1
* 所示。
* 15 8 1 24 17
* 16 14 7 5 23
* 22 20 13 6 4
* 3 21 19 12 10
* 9 2 25 18 11
* 图 1 五阶魔方阵示例
* ②基本要求
* -  输入魔方阵的行数 m，要求 m 为奇数，程序对所输入的 m 作简单的判
* 断，如 m 有错，能给出适当的提示信息。
* -  实现魔方阵。
* -  输出魔方阵。
* ③思考
* -  可以考虑使用其他方法生成魔方阵。任何算法都有不同的实现方法，通
* 过采用不同实现方法来重新实现算法，这要比单纯学习算法的效果好得
* 多。
* （2）本科生导师制问题
* 20
* ①问题描述
* 在高校的教学改革中，有很多学校实行了本科生导师制。一个班级的学生被
* 分给几个老师，每个老师带 n 个学生，如果该老师还带研究生，那么研究生也可
* 直接带本科生。本科生导师制问题中的数据元素具有如下形式：
* -  导师带研究生
* （老师，（（研究生 1，（本科生 1，…，本科生 m1）），（研究生 2，
* （本科生 1，…，本科生 m2））…））
* -  导师不带研究生
* （老师，（本科生 1，…，本科生 m））
* 导师的自然情况只包括姓名、职称；研究生的自然情况只包括姓名、班级；
* 本科生的自然情况只包括姓名、班级。
* ②基本要求
* 要求完成以下功能：
* -  建立：建立导师广义表。
* -  插入：将某位本科生或研究生插入到广义表的相应位置。
* -  删除：将某本科生或研究生从广义表中删除。
* -  查询：查询导师、本科生（研究生）的情况。
* -  统计：某导师带了多少个研究生和本科生。
* -  输出：将某导师所带学生情况输出。
* -  退出：程序结束。
* ③思考
* 可以考虑对程序做如下完善：
* -  可以将学生从一个导师组转到另一个导师组。
* -  可以在同一个导师组内修改本科生的研究生负责人。
* -  当研究生带本科生时，如果要删除该研究生，可根据情况，将本科生平
* 均分配给该导师的其他研究生，如果没有其他研究生，则由导师直接负
* 责。
* -  增加删除导师的功能。
* 查询时，如果待查人员是导师，除了输出本人信息外，还输出他所指导的学生信
* 息；如果待查人员是研究生，除了输出其导师和本人信息外，还输出他所负责的
* 本科生信息。

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <malloc.h>
//此问题使用数组求解，手写的二维数组未使用
//手写数组已经实现，请参考Array.h
int main(int argc, char** argv)
{
    int m = 0;      //阶数
    while (printf("请输入魔方阵的阶数:")&&scanf("%d",&m))
    {
        int x = 0, y = 0;       //操作光标的横坐标，纵坐标
        int fz = 0;         //辅助数
        int number = 1;     //当前要进数组的数字

        if (m <= 0 || m % 2 == 0) { printf("错误，请输入正奇数。"); continue; };//输入合法性判断

        int** mofang = (int**)malloc(sizeof(int*) * m); //为二维数组申请空间
        if (!mofang)exit(OVERFLOW); //申请失败即退出
        for (int i = 0; i < m; i++)
        {
            mofang[i] = (int*)malloc(sizeof(int) * m);
            if (!mofang[i])exit(OVERFLOW);
            memset(mofang[i], 0, (sizeof(int) * m));//清零
        }
        
        fz = m;
        
        x = 0;      //把1放到第一行中间，其中m/2自动取整
        y = m / 2;
        mofang[x][y] = number;
        number++;

        while (number <= m * m)//当数组填充值小于m的平方
        {
            //使用判断插入方法
            /*
            * 奇魔方（阶数n = 2 * m + 1，m =1，2，3……）规律如下：
            * 数字1位于方阵中的第一行中间一列；
            * 数字a（1 < a  ≤ n2）所在行数比a-1行数少1，若a-1的行数为1，则a的行数为n；
            * 数字a（1 < a  ≤ n2）所在列数比a-1列数大1，若a-1的列数为n，则a的列数为1；
            * 如果a-1是n的倍数，则a（1 < a  ≤ n2）的行数比a-1行数大1，列数与a-1相同。
            */
            if (x - 1 < 0)//上方出界
            {
                if (y - 1 >= 0)//左边没出界，把数插入到左边一行最下面
                {
                    for (int i = 0; i < m; i++)
                    {
                        if (mofang[fz - 1][y - 1] == 0)
                            break;
                        else fz--;
                    }
                    mofang[fz - 1][y - 1] = number;
                    number++;
                    x = fz - 1;
                    y = y - 1;
                    fz = m;
                }
                else//左边出界，把数插入到当前位置的下一行
                {
                    mofang[x + 1][y] = number;
                    number++;
                    x = x + 1;
                    fz = m;
                }
            }
            else if (y - 1 < 0)//左边出界
            {

                for (int i = 0; i < m; i++)
                {
                    if (mofang[x - 1][fz - 1] == 0)
                        break;
                    else fz--;
                }
                mofang[x - 1][fz - 1] = number;
                number++;
                x = x - 1;
                y = fz - 1;
                fz = m;
            }

            else if (mofang[x - 1][y - 1] != 0)//左上角元素不为0
            {
                mofang[x + 1][y] = number;
                number++;
                x = x + 1;
            }
            else//插入左上角
            {
                mofang[x - 1][y - 1] = number;
                x = x - 1;
                y = y - 1;
                number++;
            }
        }
        //输出结果
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                char formatting_string[64] = { 0 };
                strcat(formatting_string, "%");
                int align_width = log10(m * m) + 1; //此行可能造成算术溢出，但是在足够大的测试用例内部没有发现算术溢出
                char align_string[8] = { 0 };
                _itoa_s(align_width, align_string, 10);
                strcat(formatting_string, align_string);
                strcat(formatting_string, "d ");

                printf(formatting_string, mofang[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        for (int i = 0; i < m; i++)
        {
            free(mofang[i]);
        }
        free(mofang);
    }
}