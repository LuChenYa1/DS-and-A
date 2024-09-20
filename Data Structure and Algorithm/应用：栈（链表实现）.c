#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

//! 栈是操作方法，要求先进后出，后进先出，用动态数组或者链表哪种数据结构实现都可以
//! 只要保证插入和删除都在同一端进行，就是栈


typedef struct Node
{
    int Data;
    struct Node * pPre;
    struct Node * pNext;
}LLNode;

//* 栈：申请一个栈空头
LLNode * Stack(void);
//* 判断栈是否为空
bool isEmpty(LLNode * pStack);
//* 压栈：添加节点(尾添加)
void Push(LLNode * pStack, int Data);
//* 获取栈顶节点
LLNode * Top(LLNode * pStack);
//* 删除栈顶节点(尾节点)
void Pop(LLNode * pStack);
//* 释放栈
void FreeStack(LLNode ** stack);

int main(void)
{
    LLNode * pStack = Stack();
    Push(pStack, 1);
    Push(pStack, 2);
    Push(pStack, 3);
    Push(pStack, 4);
    printf("%d\n", pStack->pPre->Data);

    LLNode * pEnd = Top(pStack);
    printf("%d\n", pEnd->Data);

    Pop(pStack);
    printf("%d\n", pStack->pPre->Data);

    FreeStack(&pStack);
    return 0;
}

LLNode * Stack(void)
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

bool isEmpty(LLNode * pStack)
{
    if(pStack == NULL || pStack->pNext == pStack)
        return true;
    return false;
}

void Push(LLNode * pStack, int Data)
{
    //参数检测
    if(pStack == NULL)
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
    pNewNode->pPre = pStack->pPre;
    pNewNode->pNext = pStack;
    //后断
    pStack->pPre->pNext = pNewNode;
    pStack->pPre = pNewNode;
}

LLNode * Top(LLNode * pStack)
{
    if(isEmpty(pStack))
        return NULL;
    return pStack->pPre;
}

void Pop(LLNode * pStack)
{
    if(isEmpty(pStack))
        return;
    //重新链接
    LLNode * pEnd = pStack->pPre;
    pEnd->pPre->pNext = pStack;
    pStack->pPre = pEnd->pPre;
    //释放尾节点
    free(pEnd);
}

void FreeStack(LLNode ** pStack)
{
    //参数合法性检测
    if(pStack == NULL || *pStack == NULL)
        return;
    LLNode * pCurrent = *pStack;
    do//! 妙啊，我怎么没想到可以先执行再判断
    {
        LLNode * pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        free(pTemp);
    }while(pCurrent != *pStack);
    *pStack = NULL;
}
