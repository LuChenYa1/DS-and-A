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

void AddToHead(LLNode * stHead, int Data);//头添加
void AddToEnd(LLNode * stHead, int Data);//尾添加

void FreeList(LLNode * stHead);//释放链表

void PrintList(LLNode stHead);//打印链表

int main(void)
{
    //定义一个空头
    LLNode stHead = {0, NULL};

    AddToHead(&stHead, 1);
    AddToEnd(&stHead, 2);
    AddToHead(&stHead, 3);

    PrintList(stHead);
    
    FreeList(&stHead);
    PrintList(stHead);
    return 0;
}

void AddToHead(LLNode * stHead, int Data)//头添加
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
    }
    //计数器加一
    stHead->Data ++;
}

void AddToEnd(LLNode * stHead, int Data)//尾添加
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
    }
    //计数器加一
    stHead->Data ++;
}

void FreeList(LLNode * stHead)//释放链表
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

void PrintList(LLNode stHead)//打印链表
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
