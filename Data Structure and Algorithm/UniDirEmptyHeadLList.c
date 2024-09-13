#include <stdio.h>
#include <string.h>
#include <malloc.h>

//! 没有尾指针，有空头
//! 空头的数据变量用于存储节点数量, 最大程度利用链表空间
//! 加节点计数器

typedef struct Node
{
    int Data;
    struct Node *pNext;
}LLNode;

//* 增
void AddToHead(LLNode * stHead, int Data);//* 头添加
void AddToEnd(LLNode * stHead, int Data);//* 尾添加
void AddBehandData(LLNode * stHead, int PosData, int DesData);//* 在目标数据后面插入节点
void AddNodeByIndex(LLNode * stHead, int Index, int Data);//* 在指定下标插入节点


//* 查
LLNode * FindNodeByData(LLNode * stHead, int Data);//* 通过数据查找节点
LLNode * FindNodeByIndex(LLNode * stHead, int Index);//* 通过下标查找节点


void FreeList(LLNode * stHead);//* 释放链表

void PrintList(LLNode stHead);//* 打印链表

int main(void)
{
    //定义一个空头
    LLNode stHead = {0, NULL};

    AddToHead(&stHead, 4);
    AddToEnd(&stHead, 5);
    AddToHead(&stHead, 2);
    AddBehandData(&stHead, 2, 3);
    AddNodeByIndex(&stHead, 1, 1);

    if(FindNodeByData(&stHead, 4) == NULL)
        printf("没找到\n");
    else
        printf("找到了\n");

    PrintList(stHead);
    
    FreeList(&stHead);
    
    return 0;
}

void AddToHead(LLNode * stHead, int Data)//* 头添加
{
    //参数合法性检测
    if(stHead == NULL || stHead->Data < 0)
        return;
    //创建节点
    LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if(pNewNode != NULL)
    {
        //节点成员赋值
        pNewNode->Data = Data;
        pNewNode->pNext = NULL;
        //链接
        LLNode * pTemp = stHead->pNext;
        stHead->pNext = pNewNode;
        pNewNode->pNext = pTemp;
        //计数器加一
        stHead->Data ++;       
    }
}

void AddToEnd(LLNode * stHead, int Data)//* 尾添加
{
    //参数合法性检测
    if(stHead == NULL || stHead->Data < 0)
        return;
    //创建节点
    LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if(pNewNode != NULL)
    {
        //节点成员赋值
        pNewNode->Data = Data;
        pNewNode->pNext = NULL;
        //链接
        LLNode * pCurrent = stHead;
        while(pCurrent->pNext != NULL)
            pCurrent = pCurrent->pNext;
        pCurrent->pNext = pNewNode;
        //计数器加一
        stHead->Data ++;       
    }
}

void AddBehandData(LLNode * stHead, int PosData, int DesData)//* 在目标数据后面插入节点
{
    //参数合法性检测
    if(stHead == NULL || stHead->Data < 0)
        return;
    LLNode * pPosData = FindNodeByData(stHead, PosData);
    if(pPosData != NULL)
    {
        AddToHead(pPosData, DesData);
        pPosData->Data --;
        stHead->Data ++;
    }
}

void AddNodeByIndex(LLNode * stHead, int Index, int Data)//* 在指定下标插入节点
{
    //参数合法性检测
    if(stHead == NULL || stHead->Data < 0 || Index < 0 || Index + 1 > stHead->Data)
        return;
    LLNode * pFormer = FindNodeByIndex(stHead, Index - 1);
    if(pFormer != NULL)
    {
        AddToHead(pFormer, Data);
        pFormer->Data --;
        stHead->Data ++;
    }
}

LLNode * FindNodeByData(LLNode * stHead, int Data)//* 通过数据查找节点
{
    //参数合法性检测
    if(stHead == NULL || stHead->Data < 0)
        return NULL;
    LLNode * pCurrent = stHead->pNext;//! 注意第一个节点是空头，只存放<节点数量>
    while(pCurrent != NULL)
    {
        if(pCurrent->Data == Data)
            return pCurrent;
        pCurrent = pCurrent->pNext;
    }
    return NULL;
}

LLNode * FindNodeByIndex(LLNode * stHead, int Index)//* 通过下标查找节点
{
    //参数合法性检测
    if(stHead == NULL || stHead->Data < 0 || Index < -1)
        return NULL;
    if(Index == -1)
        return stHead;
    LLNode * pCurrent = stHead->pNext;//! 注意第一个节点是空头，只存放<节点数量>
    int i = 0;
    while(pCurrent != NULL)
    {
        if(i == Index)
            return pCurrent;
        pCurrent = pCurrent->pNext;
        i++;
    }
    return NULL;
}

void FreeList(LLNode * stHead)//* 释放链表
{
    //参数合法性检测
    if(stHead == NULL || stHead->Data < 0)
        return;
    LLNode * pCurrent = stHead->pNext;
    while(pCurrent != NULL)//有需要释放的节点
    {
        LLNode * pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        free(pTemp);
    }
    stHead->pNext = NULL;
    stHead->Data = 0;
}

void PrintList(LLNode stHead)//* 打印链表
{
    LLNode * pCurrent = stHead.pNext;
    printf("链表有%d个节点\n", stHead.Data);
    while(pCurrent != NULL)
    {
        printf("%d ", pCurrent->Data);
        pCurrent = pCurrent->pNext;
    }
    putchar('\n');
}
