#pragma once
//树基类
template <typename ElemType>
class Tree {};
//顺序Huffman树类
template <typename ElemType>
class HuffmanTree : public Tree<ElemType>
{
public:
    struct _rawdata
    {
        unsigned char c;        //字符
        long w;                 //权
    };

    // Huffman树结点定义，双亲存储结构
    struct HTNode {
        ElemType value;     // 权值，此处拓展为存储在此结点上的值
        ElemType parent;    // 父节点
        ElemType lchild;    // 左孩子位置
        ElemType rchild;    // 右孩子位置
    };

    HTNode* tree;   //Huffman树根节点指针
    char** code;    //Huffman编码
    long lv;        //结点总数
    long lencode;   //编码的长度
    HuffmanTree()
    {
        //构造函数
        this->tree = nullptr;
        this->code = nullptr;
        lv = 0;
        lencode = 0;
    }
    ~HuffmanTree()
    {
        //析构函数
        if(!this->tree)
        {
            free(tree); //释放树所占用的顺序空间
        }
        if (!this->code)
        {
            for (int i = 0; i < lencode; i++)   //循环释放编码空间
            {
                if (this->code[i])free(this->code[i]);
            }
            free(this->code);

        }
    }
};
