#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

//! 栈多用链表实现

//! 栈是操作方法，要求先进后出，后进先出
//! 只要保证插入和删除都在同一端进行，就是栈
//! 数组写栈不用头添加，因为添加一个，后面数据需要全部往后挪，执行效率低，所以采用尾添加

//! 压栈出栈的过程和递归的过程一样，最先执行的函数（最先压栈）最后结束（最后出栈）

#define NUM 10

struct Node
{
    int Arr[NUM];
    int Index;//实际表征数量
};

//* 栈：申请一个栈空头
struct Node * Stack(void);
//* 判断栈是否为空
bool isEmpty(struct Node * pStack);
//* 压栈：添加节点(尾添加)
void Push(struct Node * pStack, int Data);
//* 获取栈顶节点
int Top(struct Node * pStack);
//* 删除栈顶节点(尾节点)
void Pop(struct Node * pStack);
//* 释放栈
void FreeStack(struct Node ** stack);

int main(void)
{
    struct Node * pStack = Stack();
    if(pStack == NULL)
        return 1;   
    int Array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Push(pStack, Array[0]);
    Push(pStack, Array[1]);
    Push(pStack, Array[2]);
    Push(pStack, Array[3]);
    Push(pStack, Array[4]);
    Push(pStack, Array[5]);
    Push(pStack, Array[6]);
    Push(pStack, Array[7]);
    Push(pStack, Array[8]);
    Push(pStack, Array[9]);
    Push(pStack, 11);//超容量，无法加入

    int a = pStack->Arr[Top(pStack)];
    printf("%d\n", a);

    Pop(pStack);
    a = pStack->Arr[Top(pStack)];
    printf("%d\n", a);

    FreeStack(&pStack);
    return 0;
}

struct Node * Stack(void)
{
    struct Node * pArr = (struct Node *)malloc(sizeof(struct Node));
    if(pArr == NULL)
        return NULL;
    pArr->Index = 0;
    return pArr;
}

bool isEmpty(struct Node * pStack)
{
    if(pStack == NULL || pStack->Index == 0)
        return true;
    return false; 
}

void Push(struct Node * pStack, int Data)
{
    if(pStack == NULL || pStack->Index >= NUM)//数组有固定容量，注意不要越界
        return;
    pStack->Arr[pStack->Index] = Data;
    pStack->Index ++;
}

int Top(struct Node * pStack)
{
    if(isEmpty(pStack))
        return 0;
    return pStack->Index - 1;//返回尾数据下标
}

void Pop(struct Node * pStack)
{
    if(isEmpty(pStack))
        return;
    pStack->Index --;
}

void FreeStack(struct Node ** pStack)
{
    if(pStack == NULL || *pStack == NULL || (*pStack)->Index == 0)
        return;
    free(*pStack);
    *pStack = NULL;
}
