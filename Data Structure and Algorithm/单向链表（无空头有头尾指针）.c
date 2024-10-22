#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

//! 链表和动态数组一样，只需要一个指针名字装着头节点地址即可，不需要每增加一个节点，就起一个新的名字
//! 都是利用malloc申请内存，然后指针指向这个内存地址，最后再释放掉
//! 区别是，动态数组是连续的内存空间，链表是离散的内存空间，malloc申请空间返回的地址强转类型也不同，链表一定是结构体类型，动态数组按需转换
//! 有空头节点，数据增删皆在空头后面进行
//! 动态记录尾指针，优点是末尾增加新节点时无需再从头轮询得到尾指针，提高代码执行效率
//  函数内改变指针需要二级指针
//! void函数中的return;起退出函数作用

//! 除了DeleteFirstNodeByData函数会返回找到节点的前一个节点，其他函数都正常返回目标节点

//* 定义一个单链表节点结构体 */
typedef struct Node
{
    char Data[20];//! 20个看得见的字符，不包含'\0'
    //! 这里不小心写入了超过数组个数的字符串，造成数组越界，此时程序会莫名卡住

    //TODO 报错：ISO C++ forbids converting a string constant to 'char*'
    //TODO 原因：在C语言中，字符串常量（比如 "Add Same" 和 "First Modified"）实际上是指向字符数组首元素的指针，它们的类型是 const char*。当你尝试将其作为参数传递给char* 类型参数时，编译器会报错，因为这是不安全的——字符串常量是不应该被修改的
    //TODO 解决方法：1、如果函数不需要修改传入的字符串，可以将参数类型改为 const char*
    //TODO 需要修改：2、二次处理：在栈上定义字符数组，并使用 strcpy 函数来复制字符串常量到这些数组中，函数中传入这些数组
    struct Node *pNext;
}LLNode;

void AddToHead(LLNode ** pHead, LLNode ** pEnd, const char Data[]);//* 在开头增加新节点
void AddToEnd(LLNode ** pHead, LLNode ** pEnd, const char Data[]);//* 在末尾增加新节点
void AddSomeNodeToEnd(LLNode ** pHead, LLNode ** pEnd, unsigned int Number, const char Data[]);//* 在尾部增加多个相同内容的节点
void InsertNodeByIndex(LLNode ** pHead, LLNode ** pEnd, unsigned int Index, const char Data[]);//* 通过下标插入节点

void DeleteHead(LLNode ** pHead, LLNode ** pEnd);//* 删除头节点
void DeleteEnd(LLNode ** pHead, LLNode ** pEnd);//* 删除尾节点
void DeleteNodeByIndex(LLNode ** pHead, LLNode ** pEnd, unsigned int Index);//* 通过下标删除节点
LLNode * DeleteFirstNodeByData(LLNode ** pHead, LLNode ** pEnd, const char Data[]);//* 通过数值删除第一个节点
void DeleteAllNodeByData(LLNode ** pHead, LLNode ** pEnd, const char Data[]);//* 通过数值删除所有节点

void ChangeFirstDataByData(LLNode * pHead, const char OldData[], const char NewData[]);//* 修改指定数值的第一个节点的数
void ChangeAllDataByData(LLNode * pHead, const char OldData[], const char NewData[]);//* 修改指定数值的全部节点的数值

int GetNodeCount(LLNode * pHead);//* 统计链表节点数量
LLNode * FindNodeByIndex(LLNode * pHead, unsigned int Index);//* 通过下标查找节点
LLNode * FindFirstNodeByData(LLNode * pHead, const char Data[]);//* 通过数值查找节点

void SwapByData(LLNode * pHead, const char Data1[], const char Data2[]);//* 交换两个节点的数据
void SwapByIndex(LLNode * pHead, unsigned int Index1, unsigned int Index2);//* 通过下标交换节点数据
void ReverseListByData(LLNode * pHead, LLNode * pEnd);//* 翻转链表
void ReverseListByHelpSpace(LLNode ** pHead, LLNode ** pEnd);//* 翻转链表（辅助空间）

void FreeList(LLNode ** pHead, LLNode ** pEnd);//* 释放链表空间，头尾指针清零
void ShowList_Data(LLNode *  pHead);//* 打印链表

int main(void)
{
    LLNode * pHead = NULL;
    LLNode * pEnd = NULL;

    //* 增加节点
    AddToEnd(&pHead, &pEnd, "3");
    AddToHead(&pHead, &pEnd, "2");
    AddToEnd(&pHead, &pEnd, "4");
    AddToEnd(&pHead, &pEnd, "5");
    AddToHead(&pHead, &pEnd, "1");
    //* 增加多个节点
    AddSomeNodeToEnd(&pHead, &pEnd, 5, "6");
    //* 在指定下标插入节点
    InsertNodeByIndex(&pHead, &pEnd, 6, "Insert7");
    InsertNodeByIndex(&pHead, &pEnd, 8, "Insert8");
    //! 显示链表---增
    ShowList_Data(pHead);

    //* 删除头节点
    DeleteHead(&pHead, &pEnd);
    //* 删除尾节点
    DeleteEnd(&pHead, &pEnd);
    //* 删除指定下标节点
    DeleteNodeByIndex(&pHead, &pEnd, 3);
    //* 删除指定数值节点
    DeleteFirstNodeByData(&pHead, &pEnd, "Insert7");
    //* 删除指定数值的所有节点
    DeleteAllNodeByData(&pHead, &pEnd, "6");
    //! 显示链表---删
    ShowList_Data(pHead);

    //* 增加多个节点
    AddSomeNodeToEnd(&pHead, &pEnd, 5, "9");
    //* 修改节点数值
    ChangeFirstDataByData(pHead, "9", "9 Modified");
    //* 修改节点数值（全部）
    ChangeAllDataByData(pHead, "9", "9 All Modified");
    //! 显示链表---改
    ShowList_Data(pHead);

    //* 根据下标查找节点
    LLNode * pTemp_Index = FindNodeByIndex(pHead, 2);
    if (pTemp_Index == NULL) 
        printf("Node at index 2 not found.\n");
    //* 根据数值查找节点
    LLNode * pTemp_Data = FindFirstNodeByData(pHead, "1");
    if (pTemp_Data == NULL) 
        printf("Node with data '1' not found.\n");
    //! 显示结果---查
 
    //* 交换两个节点数据
    SwapByData(pHead, "9 Modified", "9 All Modified");
    //* 翻转链表
    ReverseListByData(pHead, pEnd);
    //* 翻转链表（辅助空间）
    ReverseListByHelpSpace(&pHead, &pEnd);
    //! 显示链表---换
    ShowList_Data(pHead);

    //释放链表
    FreeList(&pHead, &pEnd);

    return 0;
}

void AddToHead(LLNode ** pHead, LLNode ** pEnd, const char Data[])//* 在开头增加新节点
{
    //创建节点
    LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if(pNewNode != NULL)
    {
        //节点成员赋值
        strcpy(pNewNode->Data, Data);
        pNewNode->pNext = NULL;
        //链接
        if(*pHead == NULL)//空链表
        {
            *pEnd = pNewNode;//新节点即是头也是尾
        }
        else 
            pNewNode->pNext = *pHead;//连接新头节点和旧尾节点
        *pHead = pNewNode;//头指针指向新节点
    }
}

void AddToEnd(LLNode ** pHead, LLNode ** pEnd, const char Data[])//* 在末尾增加新节点
{
    //创建节点
    LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if(pNewNode != NULL)//存在申请空间失败的可能性
    {
        //节点成员赋值
        strcpy(pNewNode->Data, Data);
        pNewNode->pNext = NULL;//必须
        //链接
        if(*pHead == NULL)//空链表
        {
            *pHead = pNewNode;//新节点成为第一个节点
        }
        else 
            (*pEnd)->pNext = pNewNode;//连接旧尾节点和新尾节点
        *pEnd = pNewNode;//尾指针指向新节点
    }
}

void AddSomeNodeToEnd(LLNode ** pHead, LLNode ** pEnd, unsigned int Number, const char Data[])//* 在尾部增加多个相同内容的节点
{
    for(int i = 0; i < Number; i++)
        AddToEnd(pHead, pEnd, Data);
}

void InsertNodeByIndex(LLNode ** pHead, LLNode ** pEnd, unsigned int Index, const char Data[])//* 通过下标插入节点
{
    if(Index < 0)
    {
        printf("下标小于0，请检查参数");
        return;
    }
    else if(Index == 0)
    {
        AddToHead(pHead, pEnd, Data);
    }
    else
    {
        //寻找插入位置的前一个节点
        LLNode * pFormer = FindNodeByIndex(*pHead, Index - 1);
        if(pFormer != NULL)
        {
            //创建节点
            LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
            //节点成员赋值
            strcpy(pNewNode->Data, Data);
            pNewNode->pNext = NULL;
            //链接
            pNewNode->pNext = pFormer->pNext;
            pFormer->pNext = pNewNode;
        }
        else
            printf("下标越界，查找前节点失败");
    }
}

void DeleteHead(LLNode ** pHead, LLNode ** pEnd)//* 删除头节点
{
    //参数合法性检测
    if(*pHead == NULL)//空链表
        return;
    if((*pHead)->pNext == NULL)//只有一个节点
    {
        free(*pHead);
        *pHead = NULL;
        *pEnd = NULL;
    }
    else
    {
        LLNode * pTemp = *pHead;
        *pHead = (*pHead)->pNext;
        free(pTemp);
    }  
}

void DeleteEnd(LLNode ** pHead, LLNode ** pEnd)//* 删除尾节点
{
    //参数合法性检测
    if(*pHead == NULL)//空链表
        return;
    if((*pHead)->pNext == NULL)//只有一个节点
    {
        free(*pHead);
        *pHead = NULL;
        *pEnd = NULL;
    }
    else
    {
        //找尾节点的前一个
        LLNode * pCurrent = *pHead;
        while(pCurrent->pNext != *pEnd)
        {
            pCurrent = pCurrent->pNext;
        }
        pCurrent->pNext = NULL;
        free(*pEnd);
        *pEnd = pCurrent;
    }  
}

void DeleteNodeByIndex(LLNode ** pHead, LLNode ** pEnd, unsigned int Index)//* 通过下标删除节点
{
    if(Index < 0)
        printf("下标小于零，请检查参数");
    else if(Index == 0)
        DeleteHead(pHead, pEnd);
    else
    {
        LLNode * pLast = FindNodeByIndex(*pHead, Index - 1);
        if(pLast != NULL)
        { 
            if(pLast->pNext == *pEnd)//! 发现该下标是尾节点位置
                DeleteEnd(pHead, pEnd);
            else
            {
                LLNode * pTemp = pLast->pNext;
                pLast->pNext = pTemp->pNext;
                free(pTemp);
            }            
        }
    }
    return; 
}

LLNode * DeleteFirstNodeByData(LLNode ** pHead, LLNode ** pEnd, const char Data[])//* 通过数值删除找到的第一个节点
{
    //参数合法性检测
    if(*pHead == NULL)//空链表
        return NULL;
    if(strcmp((*pHead)->Data, Data) == 0)//数值对应的是头节点
    {
        DeleteHead(pHead, pEnd);
        return *pHead;//! 删除的是头节点，则返回的也是头节点
    }
    //! 这里不能判断尾节点数值，因为存在多个符合要求节点时，会遗漏中间节点，故，必须按节点顺序
    else//找目标节点的前一个
    {
        LLNode * pCurrent = *pHead;
        while(pCurrent->pNext != NULL)
        {
            if(strcmp(pCurrent->pNext->Data, Data) == 0)
            {
                if(pCurrent->pNext == *pEnd)//! 分类讨论，删除尾节点时要同时修改尾指针，其他节点不用
                {
                    DeleteEnd(pHead, pEnd);
                    return NULL;
                }
                else
                {
                    LLNode * pTemp = pCurrent->pNext->pNext;
                    free(pCurrent->pNext);
                    pCurrent->pNext = pTemp;
                    return pCurrent;//! 删除的不是头节点，则返回删除节点的前一个节点,方便DeleteAllNodeByData的节点链接，防止断连
                }
            }
            pCurrent = pCurrent->pNext;
        }
        return NULL;
    }
}

void DeleteAllNodeByData(LLNode ** pHead, LLNode ** pEnd, const char Data[])//* 删除指定数值的所有节点
{
    //参数合法性检测
    if(*pHead == NULL)//空链表
        return;
    LLNode * pStart = DeleteFirstNodeByData(pHead, pEnd, Data);//删除找到的第一个节点
    while(pStart != NULL)
        pStart = DeleteFirstNodeByData(&pStart, pEnd, Data);//! 从删除节点的前一个节点开始循环，删除符合要求的第一个节点

    /* if(strcmp((*pHead)->Data, Data) == 0)//先处理掉特殊的头节点，它没有前节点，无法参与接下来的处理
        DeleteHead(pHead, pEnd);
    LLNode * pCurrent = *pHead;
    LLNode * pTemp = NULL;
    while(pCurrent->pNext != NULL)
    {
        if(strcmp(pCurrent->pNext->Data, Data) == 0)
        {
            pTemp = pCurrent->pNext->pNext;
            free(pCurrent->pNext);
            pCurrent->pNext = pTemp;
        }
        else pCurrent = pCurrent->pNext;//! 一定要加else
        //! 删除某节点后，后面节点pLater补位，此时若pCurrent后移到pLater，下次循环开启时进行数值比较的是pLater的后一个节点，pLater本身就被忽略了，故，删除某节点后，pCurrent不能后移，而是需要再次开启循环，进行补位的后节点的数值比较，直到后节点不需要删除为止
    } */
}

void ChangeFirstDataByData(LLNode * pHead, const char OldData[], const char NewData[])//* 修改指定数值的第一个节点的数
{
    LLNode * pDes = FindFirstNodeByData(pHead, OldData);
    if(pDes != NULL)
        strcpy(pDes->Data, NewData);
    else
        printf("此节点不存在，无法修改\n");
}

void ChangeAllDataByData(LLNode * pHead, const char OldData[], const char NewData[])//* 修改指定数值的全部节点的数值
{
    while(pHead != NULL)
    {
        if(strcmp(pHead->Data, OldData) == 0)  
            strcpy(pHead->Data, NewData); 
        pHead = pHead->pNext;
    }
    /* //方法2：通过调用只修改一次的函数逐次修改全部
    LLNode * pDes = pHead;
    while(pDes != NULL)
    {
        pDes = FindNodeByData(pHead, OldData);
        if(pDes != NULL)
            strcpy(pDes->Data, NewData);
    } */
}

int GetNodeCount(LLNode * pHead)
{
    //参数合法性检测
    if(pHead == NULL)
        return -1;
    int Num = 0;
    while (pHead != NULL)
    {
        Num++;//计数多少个节点
        pHead = pHead->pNext;
    }
    return Num;
}

LLNode * FindNodeByIndex(LLNode * pHead, unsigned int Index)//* 通过下标查找第一个节点
{
    //参数合法性检测
    if(pHead == NULL || Index < 0)
    {
        printf("指针为NULL/下标无效，请检查参数");
        return NULL;
    }
    //轮询链表
    int i = 0;
    while (pHead != NULL)
    {
        if(i == Index)
            return pHead;
        i++;
        pHead = pHead->pNext;
    }
    printf("下标过大，请检查参数");
    return NULL;
}

LLNode * FindFirstNodeByData(LLNode * pHead, const char Data[])//* 通过数值查找第一个节点
{
    //参数合法性检测
    if(pHead == NULL)
        return NULL;//空链表
    while (pHead != NULL)
    {
        if(strcmp(pHead->Data, Data) == 0)
            return pHead;//找到了
        pHead = pHead->pNext;
    }
    return NULL;//链表无符合要求的节点
}

void SwapByData(LLNode * pHead, const char Data1[], const char Data2[])//* 交换两个节点的全部数据
{
    //参数合法性检测
    if(pHead == NULL)
        return;
    LLNode *pData1 = FindFirstNodeByData(pHead, Data1);
    LLNode *pData2 = FindFirstNodeByData(pHead, Data2);
    if(pData1 != NULL && pData2 != NULL)
    {
        /* strcpy(pData1->Data, Data2);
        strcpy(pData2->Data, Data1); *///一个节点的数据量很多时，挨个赋值很麻烦
        //* 注意：结构体成员内存分配遵循对齐原则
        //* 成员的起始地址是其大小的整数倍，例如，先来一个一字节变量，再来一个int四字节变量，则int变量从第五个字节开始存储
        LLNode TempNode = *pData1;
        memcpy(pData1, pData2, 20);
        memcpy(pData2, &TempNode, 20);//* 一次性拷贝节点的所有不同类型数据，注意算清楚数据占字节数，不要拷贝最后的pNext
    } 
}

void SwapByIndex(LLNode * pHead, unsigned int Index1, unsigned int Index2)//* 通过下标交换节点数据
{
    //参数合法性检测
    if(pHead == NULL)
        return;
    LLNode *pData1 = FindNodeByIndex(pHead, Index1);
    LLNode *pData2 = FindNodeByIndex(pHead, Index2);
    if(pData1 != NULL && pData2 != NULL)
    {
        LLNode TempNode = *pData1;
        memcpy(pData1, pData2, 20);
        memcpy(pData2, &TempNode, 20);
    }
}

void ReverseListByData(LLNode * pHead, LLNode * pEnd)//* 翻转链表（计算节点数量，通过下标对换数据）
{
    //参数合法性检测
    if(pHead == NULL || pHead->pNext == NULL)//只有一个节点，无需翻转
        return;
    int EndIndex = GetNodeCount(pHead) - 1;
    for(int i = 0; i < EndIndex; i++, EndIndex--)//! 执行效率低，每次交换数据都要从头开始轮询到节点位置
        SwapByIndex(pHead, i, EndIndex);//挨个交换
}

void ReverseListByHelpSpace(LLNode ** pHead, LLNode ** pEnd)//* 翻转链表（辅助空间）
{
    //参数合法性检测
    if(*pHead == NULL || (*pHead)->pNext == NULL)//只有一个节点，无需翻转
        return;
    LLNode * pCurrent = *pHead;
    LLNode * pNewHead = NULL;LLNode * pNewEnd = NULL;//* 辅助链表的头指针和尾指针
    while (pCurrent != NULL)//! 只需轮询一遍，就能完成链表翻转
    {
        AddToHead(&pNewHead, &pNewEnd, pCurrent->Data);//* 利用头添加函数，把往后轮询的每个节点数据都添加到新链表的头，实现翻转效果
        pCurrent = pCurrent->pNext;
    }
    FreeList(pHead, pEnd);
    //头尾指针指向存放了翻转数据的新链表
    *pHead = pNewHead;
    *pEnd = pNewEnd;
}

void FreeList(LLNode ** pHead, LLNode ** pEnd)//* 释放链表空间，头尾指针清零
{
    LLNode * pCurrent = *pHead;
    while(pCurrent != NULL)
    {
        LLNode * pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        free(pTemp);
    }
    *pHead = NULL;
    *pEnd = NULL;
}

void ShowList_Data(LLNode *  pHead)//* 打印链表
{
    LLNode * pCurrent = pHead;
    while(pCurrent != NULL)
    {
        printf("%s\n", pCurrent->Data);
        pCurrent = pCurrent->pNext;
    }
    printf("\n");
}
