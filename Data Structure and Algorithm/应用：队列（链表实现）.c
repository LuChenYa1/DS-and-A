#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

//! 队列：先进先出，后进后出
//! 让多信息源来的信息能被有序处理，eg.Windows的消息处理机制 

//! 添加的一端叫队尾，出数据的一端叫队头，添加叫入队，出数据叫出队

typedef struct Node
{
    int Data;
    struct Node * pPre;
    struct Node * pNext;
}LLNode;

//* 队列：申请一个栈空头
LLNode * Queue(void);
//* 判断队列是否为空
bool isEmpty(LLNode * pQueue);
//* 入队：添加节点(头添加)
void Push(LLNode * pQueue, int Data);
//* 出队：删除节点（尾删除）
void Pop(LLNode * pQueue);
//* 获取队头
LLNode * Front(LLNode * pQueue);
//* 获取队尾
LLNode * Back(LLNode * pQueue);
//* 释放栈
void FreeQueue(LLNode ** Queue);

int main(void)
{
    LLNode * pQueue = Queue();
    Push(pQueue, 1);
    Push(pQueue, 2);
    Push(pQueue, 3);
    Push(pQueue, 4);

    LLNode * pHead = Front(pQueue);
    printf("%d\n", pHead->Data);
    LLNode * pEnd = Back(pQueue);
    printf("%d\n", pEnd->Data);

    Pop(pQueue);
    printf("%d\n", pQueue->pPre->Data);

    FreeQueue(&pQueue);
    return 0;
}

LLNode * Queue(void)
{
    //申请节点
    LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if(pNewNode == NULL)
        return NULL;
    //节点成员赋值
    pNewNode->Data = -1;
    pNewNode->pPre = pNewNode;
    pNewNode->pNext = pNewNode;
    //返回节点
    return pNewNode;
}

bool isEmpty(LLNode * pQueue)
{
    if(pQueue == NULL || pQueue->pNext == pQueue)
        return true;
    return false;
}

LLNode * Front(LLNode * pQueue)
{
    if(isEmpty(pQueue))
        return NULL; 
    return pQueue->pPre;
}

LLNode * Back(LLNode * pQueue)
{
    if(isEmpty(pQueue))
        return NULL;
    return pQueue->pNext;
}

void Push(LLNode * pQueue, int Data)
{
    //参数检测
    if(pQueue == NULL)
        return;
    //申请节点
    LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if(pNewNode == NULL)
        return;
    //节点成员赋值
    pNewNode->Data = Data;
    pNewNode->pPre = NULL;
    pNewNode->pNext = NULL;
    //链接
    //先连
    pNewNode->pPre = pQueue;
    pNewNode->pNext = pQueue->pNext;
    //后断
    pQueue->pNext->pPre = pNewNode;
    pQueue->pNext = pNewNode;
}

void Pop(LLNode * pQueue)
{
    if(isEmpty(pQueue))
        return;
    //重新链接
    LLNode * pEnd = pQueue->pPre;
    pEnd->pPre->pNext = pQueue;
    pQueue->pPre = pEnd->pPre;
    //释放尾节点
    free(pEnd);
}

void FreeQueue(LLNode ** pQueue)
{
    //参数合法性检测
    if(pQueue == NULL || *pQueue == NULL)
        return;
    LLNode * pCurrent = *pQueue;
    do//! 妙啊，我怎么没想到可以先执行再判断
    {
        LLNode * pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        free(pTemp);
    }while(pCurrent != *pQueue);
    *pQueue = NULL;
}