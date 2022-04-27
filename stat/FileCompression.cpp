
/*
* 文件压缩
* 22
* ①基本要求
* 哈夫曼编码是一种常用的数据压缩技术，对数据文件进行哈夫曼编码可大大缩短文件的传输长度，提高信道利用率及传输效率。
* 要求采用哈夫曼编码原理，统计文本文件中字符出现的词频，以词频作为权值，对文件进行哈夫曼编码以达到压缩文件的目的，
* 再用哈夫曼编码进行译码解压缩。
* -  统计待压缩的文本文件中各字符的词频，以词频为权值建立哈夫曼树，并将该哈夫曼树保存到文件 HufTree.sav 中。
* -  根据哈夫曼树（保存在 HufTree.sav 中）对每个字符进行哈夫曼编码，并将字符编码保存到 HufCode.txt 文件中。
* -  压缩：根据哈夫曼编码，将源文件进行编码得到压缩文件 CodeFile.dat。
* -  解压：将 CodeFile.sav 文件利用哈夫曼树译码解压，恢复为源文件。
* ②选做要求
* -  实现 Burrows-Wheeler 压缩算法。
* -  比较 Burrows-Wheeler 压缩算法与单纯的哈夫曼编码压缩算法的压缩效率。
* 针对不同长度的文件，统计 Burrows-Wheeler 压缩算法的执行时间。
*/
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream> 
#include <malloc.h>
#include <ctype.h>
#include <exception>
#include <string> 
#include <fstream> 
#include "HuffmanTree.h"
#include "Pair.h"
#include "defs.h"

using namespace std;

//压缩前
long long before = 0;
//压缩后
long long after = 0;

/// <summary>
/// 在Huffman树结点[1...end]中依次选出权值最小且未编入树的两个结点的序号s1、s2
/// </summary>
/// <param name="hTree">目标Huffman树</param>
/// <param name="end">终止长度</param>
/// <param name="s1"></param>
/// <param name="s2"></param>
void select(
    const HuffmanTree<int>& hTree, 
    const int end, 
    int& s1, 
    int& s2)
{
    int w1 = INT_MAX;
    int w2 = INT_MAX;
    for (int i = 1; i <= end; i++) {
        if (hTree.tree[i].parent != 0)continue;// 忽略已经加入树的结点

        if (hTree.tree[i].value < w1) {
            s2 = s1; w2 = w1;
            s1 = i; w1 = hTree.tree[i].value;
        }
        else if (hTree.tree[i].value >= w1 && hTree.tree[i].value < w2) {
            s2 = i; w2 = hTree.tree[i].value;
        }
        //else {// hTree[i].weight>=w2}
    }
}

/// <summary>
/// 初始化Huffman树并计算生成Huffman编码
/// </summary>
/// <param name="hTree">可存取的Huffman树</param>
/// <param name="datas">存储了字频和字符的有序对</param>
/// <param name="end">上述datas的长度</param>
void initHuffman(HuffmanTree<int>& hTree,
    HuffmanTree<int>::_rawdata* datas,
    const int n) //由已知的各个字符的编码完成全文的编码
{
    //首先禁止奇怪的输入，比如单字符压缩
    if (n <= 1)
    {
        printf("压缩文件长度不合法：读取了%d字节文件\n", n);
        exit(ERROR);
    }
    const int m = n * 2 - 1 + 1;//计算Huffman树结点数，包含了根节点，因此+1
    hTree.lv = m;
    hTree.lencode = n;
    hTree.tree =
        (HuffmanTree<int>::HTNode*)malloc((m + 1) * sizeof(HuffmanTree<int>::HTNode));
    if (!hTree.tree)exit(OVERFLOW);

    // 0号单元未使用，但其value域记录了原始的权值数量
    hTree.tree[0].value = n;
    hTree.tree[0].parent = -1;
    hTree.tree[0].lchild = -1;
    hTree.tree[0].rchild = -1;

    HuffmanTree<int>::_rawdata* w = datas;
    HuffmanTree<int>::HTNode* p = hTree.tree;

    int i = 0;  //设置索引
    //这里先设置索引的原因是简化for循环

    //先置空整个树，并记录权值信息（注意p应当指向索引1处，因为0号单元弃用了，而教材中错误地指向了0号单元）
    for (p = hTree.tree + 1, i = 1;
        i <= n;
        ++i, ++p, ++w) {
        (*p) = { (*w).w,0,0,0 };//列表初始化
    }

    // 后面的部分需要计算，因此空置
    for (; i <= m; ++i, ++p) { (*p) = { 0,0,0,0 }; }

    int s1 = 0;
    int s2 = 0;

    //计算生成相应的Huffman子树
    for (i = n + 1; i < m; i++)
    {
        select(hTree, i - 1, s1, s2);//查找最小的两个结点
        hTree.tree[s1].parent = i;
        hTree.tree[s2].parent = i;
        hTree.tree[i].lchild = s1;
        hTree.tree[i].rchild = s2;
        hTree.tree[i].value = hTree.tree[s1].value + hTree.tree[s2].value;
    }
    //对根节点的左右子树进行赋值，便于后期访问
    for (int i = 0; i < hTree.lv; i++)
    {
        //先存在再赋值
        if (hTree.tree[i].parent == 0 && hTree.tree[0].lchild == -1)hTree.tree[0].lchild = i;
        else if (hTree.tree[i].parent == 0 && hTree.tree[0].rchild == -1)hTree.tree[0].rchild = i;
    }

    //从叶子到根逆向求每个字符的Huffman编码
    hTree.code = (char**)malloc((n + 1) * sizeof(char*));  // n个字符串编码的头指针向量（0号单元弃用）
    if (!hTree.code)exit(OVERFLOW);
    memset(hTree.code, 0, (n + 1) * sizeof(char*));

    char* tmp = (char*)malloc(n * sizeof(char));  // 分配求编码的工作空间（每个编码长度最大为n-1）
    if (!tmp)exit(OVERFLOW);

    tmp[n - 1] = 0;

    // 逐个字符求Huffman编码
    for (int i = 1; i <= n; ++i) {
        int start = n - 1;    // 编码结束符位置

        memset(tmp, 0, n * sizeof(char));//每次求编码之前都对临时变量进行空置
        // 从叶子到根逆向求编码
        for (int c = i, f = hTree.tree[i].parent;
            f != 0;
            c = f, f = hTree.tree[f].parent) {
            if (hTree.tree[f].lchild == c) {
                tmp[--start] = '0';
            }
            else {
                tmp[--start] = '1';
            }
        }

        hTree.code[i] = (char*)malloc((n - start) * sizeof(char));  // 为第i个字符编码分配空间
        if (!hTree.code[i])exit(OVERFLOW);

        strcpy(hTree.code[i],// 从tmp复制编码串到hTree.code
            &tmp[start]
        );   //此处的下标取了部分字符串
    }

    printf("各数据的依字频生成的Huffman编码为\n");
    for (int i = 1; i <= n; i++)
    {
        printf("数据 0x%x(%c) 对应的Huffman编码为：%s\n",
            datas[i - 1].c,
            datas[i - 1].c,
            hTree.code[i]);
    }
    printf("\n");
    free(tmp);// 释放工作空间
}

/// <summary>
/// 生成连贯的Huffman编码文件，并将连贯的编码保存到buffer中
/// </summary>
/// <param name="hTree">只读的Huffman树</param>
/// <param name="end">Huffman树中有效数据的长度</param>
/// <param name="buffer">Huffman字符串的存储位置</param>
/// <param name="Text">源文件字符串</param>
/// <param name="len">字符串长度</param>
/// <param name="match">字符串内部含有的字符数组，定长256.当不存在字符时存储为0</param>
void encrypt(const HuffmanTree<int> hTree,
    const int n,
    char*& buffer,
    const char* Text,
    const int len,
    const int* match)
{
    printf("\n尝试编码Huffman文件...\n");
    //printf("\n生成下述文章的Huffman编码\n%s\n", Text);
    buffer = (char*)malloc((len * n + 1) * sizeof(char));//初始化字符数组
    if (!buffer)exit(OVERFLOW);
    memset(buffer, 0, (len * n + 1) * sizeof(char));

    for (int i = 0; i < len; i++)
    {
        if (match[Text[i]] != 0)
        {
            //按照全文进行匹配并填入对应的Huffman编码
            strcat(buffer, hTree.code[match[Text[i]]]);
        }
    }

    //printf("\n生成的全文Huffman编码为：\n%s\n", buffer);

    //进行压缩

    FILE* fOut = fopen("CodeFile.dat", "wb");//2进制写入文件
    int Hufflength = 0;//压缩长度
    int num = 0;
    unsigned char saveChar = 0;
    for (unsigned int i = 0; i < strlen(buffer); i++)
    {
        //saveChar || = (code[i]-'0');
        //printf("%c",code[i]);
        //用来保存二进制文件，因为char类型是1个字节，所以每8位储存一次 ,而且用unsigned无符号型，避免符号位干扰
        saveChar = ((buffer[i]) | saveChar);//让saveChar和编码中的每一位进行或操作
        num++;
        if (num == 8)
        {
            fwrite(&saveChar, sizeof(char), 1, fOut);//每8位写入一次文件
            Hufflength++;
            saveChar = 0;//重新置0
            num = 0;
        }
        else {
            saveChar = saveChar << 1; //每做完一步，左移一位
        }
    }
    //}
    //printf("t=%d",t);
    //最后不到8位，移到最左端
    if (num != 8)
    {
        saveChar = saveChar << (7 - num);//移到最左端
        fwrite(&saveChar, sizeof(char), 1, fOut);
        Hufflength++;
    }
    after = Hufflength;
    printf("成功向文件CodeFile.dat写入了%d字节\n", Hufflength);
    //printf("%d",Hufflength);
    fclose(fOut);
}
//根据哈夫曼编码解压缩,主要思想是根据编码遍历哈夫曼树
long long decrypt(
    char*& Code,
    HuffmanTree<int>& hTree,
    HuffmanTree<int>::_rawdata* datas,
    char *& Text)
{
    printf("\n尝试解码Huffman文件...\n");
    printf("接收了%d字节Huffman二进制数据，尝试进行解码：\n",strlen(Code));
    std::string res;
    long long index = 0;
    long long currentlength = 4;

    for (int i = 0; Code[i] != '\0'; i++)//遍历哈夫曼编码
    {
        int m = hTree.lv - 1, ok = 1;
        while (1)
        {
            if (Code[i] == '0')
            {
                m = hTree.tree[m].lchild;
                if (hTree.tree[m].lchild == 0)
                {
                    printf("%c", datas[m - 1].c);
                    res.push_back(datas[m - 1].c);

                    break;
                }
            }
            else if (Code[i] == '1')
            {
                m = hTree.tree[m].rchild;
                if (hTree.tree[m].rchild == 0)
                {
                    printf("%c", datas[m - 1].c);
                    res.push_back(datas[m - 1].c);
                    ok = 0;
                }
            }
            if (!ok)
                break;
            i++;
        }
    }
    Text = (char*)malloc(sizeof(char) * res.length());
    memcpy(Text, res.c_str(), sizeof(char) * res.length());
    printf("成功向rawfile.txt解压%lld字节文件\n", res.length());
    return res.length();
}
void saveHuffmanTree(const HuffmanTree<int>& hTree)
{
    //由于此处存储的是类，因此此处使用了C++语法
    ofstream sav;
    sav.open("Huffman.dat", ios::binary);
    //缓存的类型是 unsigned char *，需要类型转换
    sav.write((char*)&hTree, sizeof(hTree));  //winServer为类对象
    sav.close();
}
void readHuffmanTree(HuffmanTree<int>& hTree, const char* path)
{
    ifstream read;
    read.open(path, ios::binary);
    if (!read.is_open())
    {
        printf("无法读取Huffman文件：%s\n", path);
        return;
    }
    //二进制打开，缺省为文本，ios::out,ios::in,文本输入输出用<<,>>    
    read.read((char*)&hTree, sizeof(hTree));
    long long num = read.gcount(); //获取读到文件的大小
    printf("成功读取了%lld字节Huffman文件\n", num);
    read.close();
}
int main(int argc, char** argv)
{
    FILE* fInput = nullptr;

    printf("请输入需要压缩的文件路径：");
    char path[128] = { 0 };              //将路径字符串置空
SCANF:if (!scanf("%[^\n]", &path))goto SCANF;         //读取直到换行符，出错就一直读取
    if (path[127] != 0)exit(OVERFLOW);      //如果已经超出了路径文件的最末尾位，则判定为路径溢出，此时后续数据值出现风险，退出

    fInput = fopen(path, "r");     //从路径打开文件
    if (!fInput)
    {
        printf("路径不正确，打开文件失败\n");
        exit(INFEASIBLE);
    }
    fseek(fInput, 0L, SEEK_END);    //获取文件大小
    unsigned long len = ftell(fInput);
    before = len;
    char* buffer = (char*)malloc(sizeof(char) * (len + 1));
    if (!buffer)exit(OVERFLOW);
    memset(buffer, 0, sizeof(char) * (len + 1));

    fseek(fInput, 0L, SEEK_SET);
    fread(buffer, sizeof(char), len, fInput);
    buffer[len] = 0;
    fclose(fInput);

    //字频数组，此处考虑了所有字符，包括空格、控制字符和EOF
    HuffmanTree<int>::_rawdata datas[256];
    //有效数据总量，即datas的长度
    int valid = 0;

    //初始化字频数组
    for (int i = 0; i < 256; i++)
    {
        datas[i].c = i;
        datas[i].w = -1;        //未出现的字符设为-1
    }
    //统计所有字符出现的频率
    for (unsigned long i = 0; i < len; i++)
    {
        if (datas[buffer[i]].w == -1)
        {
            datas[buffer[i]].w = 1;
            valid++;
        }
        else
        {
            datas[buffer[i]].w++;
        }
    }
    //有效字频数组，即不包含文章中未出现的符号
    HuffmanTree<int>::_rawdata* validdatas =
        (HuffmanTree<int>::_rawdata*)
        malloc(sizeof(HuffmanTree<int>::_rawdata) * (valid));
    if (!validdatas)exit(OVERFLOW);
    //字符存在标记数组，使用256*4字节内存进行线性随即查找提高速度
    int match[256] = { 0 };
    //顺序标记索引
    int n = 0;
    //生成有效字频数组，标记字符存在。
    for (int i = 0; i < 256; i++)
    {
        if (datas[i].w != -1)
        {
            validdatas[n].c = datas[i].c;
            validdatas[n].w = datas[i].w;
            match[i] = ++n;
        }
    }
    //用于存储文章最终的编码
    char* code = nullptr;

    //生成Huffman树
    HuffmanTree<int> huffman;

    //建树函数，附带完成每一个字符对应的编码
    initHuffman(huffman, validdatas, valid);

    //#define _SAVING_OPTION_ENABLED_
#ifdef _SAVING_OPTION_ENABLED_
#pragma comment("链表缺陷警告：已经启动了异步过程，该过程可能会导致内存访问错误");
    /*
    * 链表缺陷警告：
    * 此处的存取其实是虚假的存取，也就是其读取和写入都在一个应用程序和其框架下完成，因此由于强制转换的存在，可以
    *  将其存储的地址数据转换到对应的正确地址空间。实际应用中由于DEP的存在和链表结构的自身缺陷，此处的read函数将
    *  读取一个错误的地址进入程序，此时将会引发C0000005异常。
    * 要解决这个问题，需要进行深遍历保存，但是这已经超出了本题目所要求的内容
    * 此处的存取仅作为演示。
    */
    //将Huffman树保存
    //假装存储了树
    saveHuffmanTree(huffman);
    //创建拷贝树
    HuffmanTree<int> dupTree;
    //从文件读取并写入拷贝树
    readHuffmanTree(dupTree, "Huffman.dat");
#endif
    encrypt(huffman, valid, code, buffer, len, match);     //由已知的各个字符的编码完成全文的编码
    char* decrypted = nullptr;
    long long c = decrypt(code, huffman, validdatas,decrypted);   //由全文的编码，用已经建立的哈弗曼树完成解码
    
    FILE* fOut = fopen("rawfile.txt", "w");//写入文件
    fwrite(decrypted, sizeof(char), c,fOut);
    fclose(fOut);

    free(buffer);

    double compress_rate = (double)after / (double)before * 100;
    printf("\n压缩率为%3lf%%\n",compress_rate);
    return 0;
}