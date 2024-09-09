#include <stdio.h>
#include <string.h>
#include <malloc.h>

//! 没有尾指针，有空头

typedef struct Node
{
    char Data[20];
    struct Node *pNext;
}LLNode;

void AddToHead(LLNode * pHead, const char Data[]);
void PrintList(LLNode * pHead);

int main(void)
{
    //定义一个空头
    LLNode stHead = {" ", NULL};

    AddToHead(&stHead, "1");
    PrintList(&stHead);

    return 0;
}

void AddToHead(LLNode * pHead, const char Data[])
{
    //参数合法性检测
    if(pHead == NULL)
        return;
    //创建节点
    LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if(pNewNode != NULL)
    {
        //节点成员赋值
        strcpy(pNewNode->Data, Data);
        //链接
        LLNode * pTemp = pHead->pNext;
        pHead->pNext = pNewNode;
        pNewNode->pNext = pTemp;
    }
}

void PrintList(LLNode * pHead)
{
    //参数合法性检测
    if(pHead == NULL)
        return;
    LLNode * pCurrent = pHead->pNext;
    while(pCurrent != NULL)
    {
        printf("%s\n", pCurrent->Data);
        pCurrent = pCurrent->pNext;
    }
}
