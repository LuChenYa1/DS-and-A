#include <stdio.h>
#include <malloc.h>

//! malloc太多空间，CPU占用率会大幅提高，导致程序卡顿，所以要及时释放空间
//! 双向链表相对单向链表的优势是，要增删节点时不必找到目标节点的前一个节点,操作谁就找谁

typedef struct Node
{
    int Data;
    struct Node * pPre;
    struct Node * pNext; 
}LLNode;

LLNode * pHead_A = NULL, * pEnd_A = NULL;
int NodeCount_A = 0;

LLNode * pHead_B = NULL, * pEnd_B = NULL;
int NodeCount_B = 0;

//增
void AddToHead(LLNode ** pHead, LLNode ** pEnd, int * NodeCount, int Data);//* 头添加
void AddToEnd(LLNode ** pHead, LLNode ** pEnd, int * NodeCount, int Data);//* 尾添加
void AddNodeByIndex(LLNode ** pHead, LLNode ** pEnd, int * NodeCount, int Index, int Count, int Data);//* 在指定下标增加指定数量的节点
void AddNodeBeforeData(LLNode ** pHead, LLNode ** pEnd, int * NodeCount, int PosData, int AddData);//* 在目标节点的前面增加节点

//删
void DeleteNode(LLNode ** pHead, LLNode ** pEnd, int * NodeCount, LLNode * pNode);//* 删除指定地址节点
void DeleteNodeByIndex(LLNode ** pHead, LLNode ** pEnd, int * NodeCount, int Index);//* 通过下标删除节点
void DeleteNodeByData(LLNode ** pHead, LLNode ** pEnd, int * NodeCount, int Data);//* 通过数据删除节点

//改
void ChangeNodeByIndex(LLNode * pHead, int NodeCount, int Index, int Data);//* 修改指定下标数据
void ChangeNodeByData(LLNode * pHead, int PosData, int ChangeData);//* 修改指定数据节点的数据

//查
LLNode * FindNodeByIndex(LLNode * pHead, int NodeCount, int Index);//* 通过下标查找节点
LLNode * FindNodeByData(LLNode * pHead, int Data);//* 通过数据查找节点

//合并有序链表
void MergeLList(LLNode ** pHead_A, LLNode ** pEnd_A, int * NodeCount_A, LLNode ** pHead_B, LLNode ** pEnd_B,  int * NodeCount_B);//* 合并链表到B，确保有序（从小到大）,保留链表A吗，可用于链表排序

void PrintLList(LLNode * pHead, int NodeCount);//* 打印链表
void PrintLList_Z(LLNode * pEnd, int NodeCount);//* 反向打印链表

void FreeLList(LLNode ** pHead, LLNode ** pEnd, int * NodeCount);//* 释放链表

int main(void)
{
    //* 增
    AddToEnd(&pHead_A, &pEnd_A, &NodeCount_A, 2);
    AddToEnd(&pHead_A, &pEnd_A, &NodeCount_A, 3);
    AddToEnd(&pHead_A, &pEnd_A, &NodeCount_A, 4);
    AddToHead(&pHead_A, &pEnd_A, &NodeCount_A, 1);
    AddNodeByIndex(&pHead_A, &pEnd_A, &NodeCount_A, 0, 4, 500);
    AddNodeByIndex(&pHead_A, &pEnd_A, &NodeCount_A, NodeCount_A, 1, 600);
    AddNodeByIndex(&pHead_A, &pEnd_A, &NodeCount_A, 5, 3, 700);
    AddNodeBeforeData(&pHead_A, &pEnd_A, &NodeCount_A, 700, 0);
    PrintLList(pHead_A, NodeCount_A);

    //* 删
    DeleteNode(&pHead_A, &pEnd_A, &NodeCount_A, pHead_A);
    DeleteNodeByIndex(&pHead_A, &pEnd_A, &NodeCount_A, 0);
    DeleteNodeByData(&pHead_A, &pEnd_A, &NodeCount_A, 700);
    PrintLList(pHead_A, NodeCount_A);

    //* 改
    ChangeNodeByIndex(pHead_A, NodeCount_A, 0, 1);
    ChangeNodeByData(pHead_A, 0, 999);
    PrintLList(pHead_A, NodeCount_A);

    //* 查
    LLNode * pTemp = FindNodeByIndex(pHead_A, NodeCount_A, 3);
    printf("下标3的数据是%d\n", pTemp->Data);
    pTemp = FindNodeByData(pHead_A, 3);
    printf("指定数据节点的下一个节点的数据是%d\n", pTemp->pNext->Data);

    FreeLList(&pHead_A, &pEnd_A, &NodeCount_A);
    //PrintLList_Z();

    //* A链表
    AddToEnd(&pHead_A, &pEnd_A, &NodeCount_A, 20);
    AddToEnd(&pHead_A, &pEnd_A, &NodeCount_A, 0);
    AddToEnd(&pHead_A, &pEnd_A, &NodeCount_A, 17);
    AddToEnd(&pHead_A, &pEnd_A, &NodeCount_A, 5);
    AddToEnd(&pHead_A, &pEnd_A, &NodeCount_A, 9);
    PrintLList(pHead_A, NodeCount_A);
    //* B链表
    AddToEnd(&pHead_B, &pEnd_B, &NodeCount_B, 1);
    AddToEnd(&pHead_B, &pEnd_B, &NodeCount_B, 5);
    AddToEnd(&pHead_B, &pEnd_B, &NodeCount_B, 10);
    AddToEnd(&pHead_B, &pEnd_B, &NodeCount_B, 15);
    PrintLList(pHead_B, NodeCount_B);
    //* 合并链表
    MergeLList(&pHead_A, &pEnd_A, &NodeCount_A, &pHead_B, &pEnd_B, &NodeCount_B);
    PrintLList(pHead_B, NodeCount_B);
    PrintLList(pHead_A, NodeCount_A);

    FreeLList(&pHead_A, &pEnd_A, &NodeCount_A);
    FreeLList(&pHead_B, &pEnd_B, &NodeCount_B);
    
    return 0;
}

void MergeLList(LLNode ** pHead_A, LLNode ** pEnd_A, int * NodeCount_A, LLNode ** pHead_B, LLNode ** pEnd_B,  int * NodeCount_B)
{
    if(pHead_A == NULL || pHead_B == NULL || *pHead_A == NULL || *NodeCount_A < 1)
        return;
    LLNode * pCurrent = *pHead_A;
    while(pCurrent != NULL)
    {
        LLNode * pInsertPos = NULL;
        LLNode * pInner = *pHead_B;
        LLNode * pPrevInner = NULL;
        //! 查找插入位置
        while(pInner != NULL && pCurrent->Data > pInner->Data)
        {
            pPrevInner = pInner;
            pInner = pInner->pNext;
        }
        //! 如果pInner为NULL，说明pCurrent的数据应该插入到链表B的尾部
        //! 如果pPrevInner为NULL，说明pCurrent的数据应该插入到链表B的头部
        //! 否则，插入到pPrevInner和pInner之间
        if(pInner == NULL)//值最大，尾添加
        {
            AddToEnd(pHead_B, pEnd_B, NodeCount_B, pCurrent->Data);
        }
        else if(pPrevInner == NULL)//值最小，头添加
        {
            AddToHead(pHead_B, pEnd_B, NodeCount_B, pCurrent->Data);
        }
        else//在最大和最小中间
        {
            // 插入新节点
            LLNode *pNewNode = (LLNode *)malloc(sizeof(LLNode));
            if(pNewNode == NULL)
            {
                // 这里可以添加错误处理代码，例如记录错误日志
                return;
            }
            pNewNode->Data = pCurrent->Data;
            pNewNode->pPre = pPrevInner;
            pNewNode->pNext = pInner;
            pPrevInner->pNext = pNewNode;
            pInner->pPre = pNewNode;
            (*NodeCount_B)++;
        }
        pCurrent = pCurrent->pNext;
    }
    FreeLList(pHead_A, pEnd_A, NodeCount_A);
}

void AddToHead(LLNode ** pHead, LLNode ** pEnd, int * NodeCount, int Data)//* 头添加
{
    //参数合法性检测
    if(pHead == NULL || pEnd == NULL)
        return;
    //申请空间
    LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if(pNewNode == NULL)return;
    //节点成员赋值
    pNewNode->Data = Data;
    pNewNode->pPre = NULL;
    pNewNode->pNext = NULL;
    //链接
    if(*pHead == NULL)//空链表
        *pEnd = pNewNode;//新节点即是头，也是尾
    else
    {
        pNewNode->pNext = *pHead;
        (*pHead)->pPre = pNewNode;
    }
    *pHead = pNewNode;
    (*NodeCount) ++;
}

void AddToEnd(LLNode ** pHead, LLNode ** pEnd, int * NodeCount, int Data)//* 尾添加
{
    //参数合法性检测
    if(pHead == NULL || pEnd == NULL)
        return;
    //申请空间
    LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if(pNewNode == NULL)return;
    //节点成员赋值
    pNewNode->Data = Data;
    pNewNode->pPre = NULL;
    pNewNode->pNext = NULL;
    //链接
    if(*pHead == NULL)//空链表
        *pHead = pNewNode;//新节点即是头，也是尾
    else
    {
        (*pEnd)->pNext = pNewNode;//修改旧尾节点的pNext
        pNewNode->pPre = *pEnd;//记录前节点地址
    }
    (*pEnd) = pNewNode;//尾添加必做：尾指针指向尾节点
    //节点数量加一
    (*NodeCount) ++;//! 后置++的优先级比*高，所以要加括号
}

void AddNodeByIndex(LLNode ** pHead, LLNode ** pEnd, int * NodeCount, int Index, int Count, int Data)//* 在指定下标增加指定数量的节点
{
    if(pHead == NULL || pEnd == NULL || Index < 0 || Index > NodeCount_A || Count < 1)
        return;
    if(Index == 0)
        for(int i = 0; i < Count; i++)
            AddToHead(pHead, pEnd, NodeCount, Data);
    else if(Index == NodeCount_A)
        for(int i = 0; i < Count; i++)
            AddToEnd(pHead, pEnd, NodeCount, Data);
    else
    {
        //寻找指定下标节点
        LLNode * pCurrent = *pHead;
        for(int i = 0; i < Index; i++)
            pCurrent = pCurrent->pNext;
        for(int i = 0; i < Count; i++)
        {
            //申请空间
            LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
            if(pNewNode == NULL)return;
            //节点成员赋值
            pNewNode->Data = Data;
            pNewNode->pPre = NULL;
            pNewNode->pNext = NULL;
            //链接
            //新节点和前节点相连
            pCurrent->pPre->pNext = pNewNode;
            pNewNode->pPre = pCurrent->pPre;
            //新节点和后节点相连
            pNewNode->pNext = pCurrent;
            pCurrent->pPre = pNewNode;
        }
        (*NodeCount) += Count;
    } 
}

void AddNodeBeforeData(LLNode ** pHead, LLNode ** pEnd, int * NodeCount, int PosData, int AddData)//* 在目标节点的前面增加节点
{
    //参数合法性检测
    if(pHead == NULL || pEnd == NULL || NodeCount == 0)
        return;
    //头添加
    if((*pHead)->Data == PosData)
    {
        AddToHead(pHead, pEnd, NodeCount, AddData);
        return;
    }
    //查找目标节点
    LLNode * pCurrent = *pHead;
    while(pCurrent != NULL)
    {
        if(pCurrent->Data == PosData)
        {
            //申请空间
            LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
            if(pNewNode == NULL)return;
            //节点成员赋值
            pNewNode->Data = AddData;
            pNewNode->pPre = NULL;
            pNewNode->pNext = NULL;
            //链接
            //新节点和前节点相连
            pCurrent->pPre->pNext = pNewNode;
            pNewNode->pPre = pCurrent->pPre;
            //新节点和后节点相连
            pNewNode->pNext = pCurrent;
            pCurrent->pPre = pNewNode; 
            //节点数量加一
            (*NodeCount) ++;
        }
        pCurrent = pCurrent->pNext;
    }
}

void DeleteNode(LLNode ** pHead, LLNode ** pEnd, int * NodeCount, LLNode * pNode)//* 删除指定地址节点
{
    //参数合法性检测
    if(pHead == NULL || pEnd == NULL ||(*pHead) == NULL || (*pEnd) == NULL || (*NodeCount) == 0)
        return;
    if((*NodeCount) != 1)
    {
        //修改指向
        if(pNode == (*pHead))//头删除
        {
            pNode->pNext->pPre = NULL;
            *pHead = pNode->pNext;
        }
        else if(pNode == (*pEnd))//尾删除
        {
            pNode->pPre->pNext = NULL;
            *pEnd = pNode->pPre;
        }
        else 
        {
            pNode->pPre->pNext = pNode->pNext;
            pNode->pNext->pPre = pNode->pPre;
        }
    }
    else
        *pHead = *pEnd = NULL;
    free(pNode);
    (*NodeCount) --;
}

void DeleteNodeByIndex(LLNode ** pHead, LLNode ** pEnd, int * NodeCount, int Index)//* 通过下标删除节点
{
    //没有参数检测，因为查找节点函数已经检测过
    //查找节点
    LLNode * pTemp = FindNodeByIndex(*pHead, *NodeCount, Index);
    if(pTemp == NULL)return;
    DeleteNode(pHead, pEnd, NodeCount, pTemp);
}

void DeleteNodeByData(LLNode ** pHead, LLNode ** pEnd, int * NodeCount, int Data)//* 通过数据删除节点
{
    // while(1)
    // {
    //     LLNode * pTemp = FindNodeByData(Data);
    //     if(pTemp == NULL)return;
    //     DeleteNode(pTemp);
    // }
    LLNode * pTemp; 
    while ((pTemp = FindNodeByData(*pHead, Data)) != NULL)
        DeleteNode(pHead, pEnd, NodeCount, pTemp);
}

void ChangeNodeByIndex(LLNode * pHead, int NodeCount, int Index, int Data)//* 修改指定下标数据
{
    LLNode * pTemp = FindNodeByIndex(pHead, NodeCount, Index);
    if(pTemp == NULL)return;
    pTemp->Data = Data;
}

void ChangeNodeByData(LLNode * pHead, int PosData, int ChangeData)//* 修改指定数据节点的数据
{
    //参数合法性检测
    if(pHead == NULL)
        return;
    LLNode * pCurrent = pHead;
    while(pCurrent != NULL)
    {
        if(pCurrent->Data == PosData)
            pCurrent->Data = ChangeData;
        pCurrent = pCurrent->pNext;
    }
}

LLNode * FindNodeByIndex(LLNode * pHead, int NodeCount, int Index)//* 通过下标查找节点
{
    //参数合法性检测
    if(pHead == NULL || Index < 0 || Index + 1 > NodeCount)
        return NULL;
    LLNode * pCurrent = pHead;
    for(int i = 0; i < Index; i++)
        pCurrent = pCurrent->pNext;
    return pCurrent;
}

LLNode * FindNodeByData(LLNode * pHead, int Data)//* 通过数据查找节点
{
    //参数合法性检测
    if(pHead == NULL)
        return NULL;
    LLNode * pCurrent = pHead;
    while(pCurrent != NULL)
    {
        if(pCurrent->Data == Data)
            return pCurrent;
        pCurrent = pCurrent->pNext;
    }
    return NULL;
}

void FreeLList(LLNode ** pHead, LLNode ** pEnd, int * NodeCount)//释放链表
{
    if(*pHead == NULL)return;//空链表无需释放，不必往下执行
    LLNode * pCurrent = *pHead;
    while(pCurrent != NULL)
    {
        LLNode * pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        free(pCurrent);
    }
    *pHead = NULL;
    *pEnd = NULL;
    *NodeCount = 0;
}

void PrintLList(LLNode * pHead, int NodeCount)//打印链表
{
    if(pHead == NULL)return;//空链表无需释放，不必往下执行
    LLNode * pCurrent = pHead;
    printf("链表有%d个节点\n", NodeCount);
    while (pCurrent != NULL)
    {
        printf("%d ", pCurrent->Data);
        pCurrent = pCurrent->pNext;
    }
    putchar('\n');
}

void PrintLList_Z(LLNode * pEnd, int NodeCount)//反向打印链表
{
    if(pEnd == NULL)return;
    LLNode * pCurrent = pEnd;
    printf("反向打印：链表有%d个节点\n", NodeCount);
    while (pCurrent != NULL)
    {
        printf("%d ", pCurrent->Data);
        pCurrent = pCurrent->pPre;
    }
    putchar('\n');
}
