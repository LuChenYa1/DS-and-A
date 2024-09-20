#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//! 链接时，如果涉及空头操作，则空头最后处理，防止无法索引原来的节点 （空头是索引整个链表地址的钥匙）

//! 链表的空间利用率一定高于动态数组吗？
//* 不一定，链表的确没有空闲节点，但每个节点都装了指针，不全是数据，导致利用率降低，而动态数组的空间除了未用到的空间，全装了数据，只申请了一个结构体用于放（容量、余量、头指针）
//* 空间利用率：有效数据（不包括指针）占申请空间的比例

typedef struct Node
{
    int Data;
    struct Node * pPre;
    struct Node * pNext;
}LLNode;

LLNode * CreateNode(int Data);//* 创建一个节点

void AddToEnd(LLNode * stHead, int * NodeCount, int Data);//* 尾添加
void AddToHead(LLNode * stHead, int * NodeCount, int Data);//* 头添加
void AddNodeByIndex(LLNode * stHead, int * NodeCount, int Number, int Index, int Data);//* 在指定下标位置增加节点
void AddNodeBeforeData(LLNode * stHead, int * NodeCount, int DesData, int AddData);//* 在指定数据前面增加节点

void DeleteNodeByIndex(LLNode * stHead, int * NodeCount, int Index);//* 通过下标删除节点
void DeleteNodeBySomeIndex(LLNode * stHead, int * NodeCount, int IndexMin, int IndexMax);//* 通过下标范围删除节点
void DeleteNodeByData(LLNode * stHead, int * NodeCount, int Data);//* 删除指定数据节点

LLNode * FindNodeByIndex(LLNode * stHead, int NodeCount, int Index);//* 通过下标查找节点
LLNode * FindNodeByData(LLNode * stHead, int NodeCount, int Data);//* 通过数据查找节点

void FreeLList(LLNode * stHead, int * NodeCount);//* 释放链表

void PrintLList(LLNode * stHead, int NodeCount);//* 打印链表


int main(void)
{
    //空头
    LLNode stHead = {0, &stHead, &stHead};
    int NodeCount = 0;

    AddToEnd(&stHead, &NodeCount, 1);
    AddToEnd(&stHead, &NodeCount, 2);
    AddToEnd(&stHead, &NodeCount, 3);
    AddToEnd(&stHead, &NodeCount, 4);
    AddToHead(&stHead, &NodeCount, 5);
    AddNodeByIndex(&stHead, &NodeCount, 3, 3, 6);
    AddNodeBeforeData(&stHead, &NodeCount, 4, 7);
    PrintLList(&stHead, NodeCount);

    DeleteNodeByIndex(&stHead, &NodeCount, 0);
    DeleteNodeBySomeIndex(&stHead, &NodeCount, 3, 6);
    PrintLList(&stHead, NodeCount);

    AddNodeByIndex(&stHead, &NodeCount, 3, 3, 8);
    PrintLList(&stHead, NodeCount);
    DeleteNodeByData(&stHead, &NodeCount, 8);
    PrintLList(&stHead, NodeCount);

    LLNode * pTemp = FindNodeByData(&stHead, NodeCount, 1); 
    if(pTemp != NULL)
        printf("找到了\n");
    else
        printf("没找到\n");

    pTemp = FindNodeByIndex(&stHead, NodeCount, 4); 
    if(pTemp != NULL)
        printf("找到了\n");
    else
        printf("没找到\n");

    FreeLList(&stHead, &NodeCount);
    PrintLList(&stHead, NodeCount);

    return 0;
}

LLNode * CreateNode(int Data)//* 创建一个节点
{
    //申请空间
    LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if(pNewNode == NULL)return NULL;
    //节点成员赋值
    pNewNode->Data = Data;
    pNewNode->pPre = NULL;
    pNewNode->pNext = NULL;
    //返回节点
    return pNewNode;
}

void AddToEnd(LLNode * stHead, int * NodeCount, int Data)//* 尾添加
{
    //创建新节点
    LLNode * pNewNode = CreateNode(Data);
    //链接
    //尾节点和新节点相连
    stHead->pPre->pNext = pNewNode;
    pNewNode->pPre = stHead->pPre;
    //新节点和空头相连
    pNewNode->pNext = stHead;
    stHead->pPre = pNewNode;
    //节点数量加一
    (*NodeCount)++;
}

void AddToHead(LLNode * stHead, int * NodeCount, int Data)//* 头添加
{
    //创建新节点
    LLNode * pNewNode = CreateNode(Data);
    //链接
    //新节点和后节点相连
    pNewNode->pNext = stHead->pNext;
    stHead->pNext->pPre = pNewNode;
    //空头和新节点相连
    stHead->pNext = pNewNode;
    pNewNode->pPre = stHead;
    //节点数量加一
    (*NodeCount)++;
}

void AddNodeByIndex(LLNode * stHead, int * NodeCount, int Index, int Number, int Data)//* 在指定下标位置增加节点
{
    //参数合法性检测
    if(stHead == NULL || NodeCount == NULL || Index > *NodeCount || Index < 0)
        return;
    //查找函数无法检测尾节点后一位和空链表情况，需单独判断
    if(*NodeCount == 0 || Index == (*NodeCount))
        for(int i = 0; i < Number; i++)
            AddToEnd(stHead, NodeCount, Data);
    else
    {
        //找位置
        LLNode * pDes = FindNodeByIndex(stHead, *NodeCount, Index);
        if(pDes == NULL)return;
        for(int i = 0; i < Number; i++)
        {
            //创建节点
            LLNode * pNewNode = CreateNode(Data);
            //链接 
            //前节点和新节点相连
            pDes->pPre->pNext = pNewNode;
            pNewNode->pPre = pDes->pPre;
            //新节点和后节点相连
            pNewNode->pNext = pDes;
            pDes->pPre = pNewNode;
            //节点数量加一
            (*NodeCount)++;            
        }
    }
}

void AddNodeBeforeData(LLNode * stHead, int * NodeCount, int DesData, int AddData)//* 在指定数据前面增加节点
{
    //查找数据
    LLNode * pDes = FindNodeByData(stHead, *NodeCount, DesData);
    if(pDes == NULL)return;
    //创建节点
    LLNode * pNewNode = CreateNode(AddData);
    //链接 
    //前节点和新节点相连
    pDes->pPre->pNext = pNewNode;
    pNewNode->pPre = pDes->pPre;
    //新节点和后节点相连
    pNewNode->pNext = pDes;
    pDes->pPre = pNewNode;
    //节点数量加一
    (*NodeCount)++;
}

void DeleteNodeByIndex(LLNode * stHead, int * NodeCount, int Index)//* 通过下标删除节点
{
    //找位置
    LLNode * pDes = FindNodeByIndex(stHead, *NodeCount, Index);
    if(pDes == NULL)return;
    //修改指向
    pDes->pPre->pNext = pDes->pNext;
    pDes->pNext->pPre = pDes->pPre;
    //释放空间
    free(pDes);
    //数量减一
    (*NodeCount)--;
}

void DeleteNodeBySomeIndex(LLNode * stHead, int * NodeCount, int IndexMin, int IndexMax)//* 通过下标范围删除节点
{
    for(int i = IndexMin; i <= IndexMax; i++)
        DeleteNodeByIndex(stHead, NodeCount, IndexMin);
}

void DeleteNodeByData(LLNode * stHead, int * NodeCount, int Data)//* 删除指定数据节点
{
    while(1)
    {
        //查找数据
        LLNode * pDes = FindNodeByData(stHead, *NodeCount, Data);
        if(pDes == NULL)return;
        //修改指向
        pDes->pPre->pNext = pDes->pNext;
        pDes->pNext->pPre = pDes->pPre;
        //释放空间
        free(pDes); 
        //数量减一
        (*NodeCount)--;
    }
}

LLNode * FindNodeByIndex(LLNode * stHead, int NodeCount, int Index)//* 通过下标查找节点
{
    //参数合法性检测
    if(stHead == NULL || Index + 1 > NodeCount || Index < 0 || NodeCount <= 0)
        return NULL;
    LLNode * pCurrent = stHead->pNext;
    for(int i = 0; i < Index; i++)
        pCurrent = pCurrent->pNext;
    return pCurrent;
}

LLNode * FindNodeByData(LLNode * stHead, int NodeCount, int Data)//* 通过数据查找节点
{
    if(stHead == NULL || NodeCount <= 0)
        return NULL;
    LLNode * pCurrent = stHead->pNext;
    while(pCurrent != stHead)
    {
        if(pCurrent->Data == Data)
            return pCurrent;
        pCurrent = pCurrent->pNext;
    }
    return NULL;
}

void FreeLList(LLNode * stHead, int * NodeCount)//* 释放链表
{
    if(*NodeCount == 0)
        return;
    LLNode * pCurrent = stHead->pNext;
    //释放空头以外的所有节点
    while(pCurrent != stHead)
    {
        LLNode * pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        free(pTemp);
    }
    //处理空头 
    stHead->pNext = stHead;
    stHead->pPre = NULL;
    *NodeCount = 0;
}

void PrintLList(LLNode * stHead, int NodeCount)//* 打印链表
{
    printf("链表节点数量：%d \n", NodeCount);
    if(NodeCount == 0) 
        return;
    LLNode * pCurrent = stHead->pNext;
    while(pCurrent != stHead)
    {
        printf("%d ", pCurrent->Data);
        pCurrent = pCurrent->pNext;
    }
    printf("\n");
}
