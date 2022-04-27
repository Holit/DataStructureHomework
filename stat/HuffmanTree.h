#pragma once
//������
template <typename ElemType>
class Tree {};
//˳��Huffman����
template <typename ElemType>
class HuffmanTree : public Tree<ElemType>
{
public:
    struct _rawdata
    {
        unsigned char c;        //�ַ�
        long w;                 //Ȩ
    };

    // Huffman����㶨�壬˫�״洢�ṹ
    struct HTNode {
        ElemType value;     // Ȩֵ���˴���չΪ�洢�ڴ˽���ϵ�ֵ
        ElemType parent;    // ���ڵ�
        ElemType lchild;    // ����λ��
        ElemType rchild;    // �Һ���λ��
    };

    HTNode* tree;   //Huffman�����ڵ�ָ��
    char** code;    //Huffman����
    long lv;        //�������
    long lencode;   //����ĳ���
    HuffmanTree()
    {
        //���캯��
        this->tree = nullptr;
        this->code = nullptr;
        lv = 0;
        lencode = 0;
    }
    ~HuffmanTree()
    {
        //��������
        if(!this->tree)
        {
            free(tree); //�ͷ�����ռ�õ�˳��ռ�
        }
        if (!this->code)
        {
            for (int i = 0; i < lencode; i++)   //ѭ���ͷű���ռ�
            {
                if (this->code[i])free(this->code[i]);
            }
            free(this->code);

        }
    }
};
