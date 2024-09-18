#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//! 链接时，如果涉及空头操作，则空头最后处理，防止无法索引原来的节点 （空头是索引整个链表地址的钥匙）
typedef struct Node
{
    int Data;
    struct Node * pPre;
    struct Node * pNext;
}LLNode;

LLNode * CreateNode(int Data);//* 创建一个节点

void AddToEnd(LLNode * stHead, int * NodeCount, int Data);//* 尾添加
void AddToHead(LLNode * stHead, int * NodeCount, int Data);//* 头添加

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

    PrintLList(&stHead, NodeCount);

    LLNode * pTemp = FindNodeByData(&stHead, NodeCount, 6); 
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

LLNode * FindNodeByIndex(LLNode * stHead, int NodeCount, int Index)//* 通过下标查找节点
{
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
