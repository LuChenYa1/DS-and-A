#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int Data;
    struct Node *pNext;
};

struct Node * Search_Element(struct Node *pHead, int Data);
struct Node * Search_Index(struct Node *pHead, int Index);
int Number_Element(struct Node *pHead, int Data);
char ChangeByElement(struct Node *pHead, int OldValue, int NewValue);
char ChangeByIndex(struct Node *pHead, int Index, int NewValue);
int Nodes_Element(struct Node *pHead, struct Node * Arr[4], int Data, int ArrSize);
void PrintList(struct Node *pHead);

int main(void) 
{
    //* 初始化链表
    struct Node a = {1, NULL},
    b = {2, NULL},
    c = {3, NULL},
    d = {4, NULL};
    a.pNext = &b;
    b.pNext = &c;
    c.pNext = &d;
    d.pNext = NULL;

    struct Node * pTemp;

    //* 打印链表
    PrintList(&a);

    //* 查找链表中元素2的节点
    pTemp = Search_Element(&a, 2);
    if(pTemp == NULL)printf("链表中不存在元素2\n");
    else printf("链表中存在元素%d\n", pTemp->Data);

    //* 查找链表中下标为3的元素
    pTemp = Search_Index(&a, 3);
    if(pTemp == NULL)printf("链表中不存在此节点\n");
    else printf("链表中此下标对应元素为%d\n", pTemp->Data);

    //* 查找链表中元素2的个数
    int i = Number_Element(&a, 1);
    printf("链表中此元素的个数为%d\n", i);

    //* 查找链表中元素4对应的节点
    struct Node * Arr[4] = {NULL, NULL, NULL, NULL};// 定义一个数组，用于存储链表中某元素的所有节点
    Nodes_Element(&a, Arr, 4, 2);//! Arr是数组的地址，Arr+索引直接指向实际数组空间，p[0] = *p[0]

    for(int i = 0; i < 4 && Arr[i] != NULL; i++)//! i < 4 放在 p[i] != NULL前面，防止越界
        printf("%d \n", Arr[i]->Data);

    //* 头添加节点
    struct Node e = {1, NULL};
    e.pNext = &a;
    //* 尾添加节点
    struct Node f = {2, NULL};
    d.pNext = &f;
    //* 中间添加节点
    struct Node g = {3, NULL};
    g.pNext = &c;
    b.pNext = &g;
    PrintList(&e);

    //* 删除头节点
    e.pNext = NULL;
    // ...释放
    PrintList(&e);
    //* 删除尾节点
    d.pNext = NULL;
    PrintList(&a);
    //* 删除中间节点
    b.pNext = g.pNext;
    PrintList(&a);

    //* 替换链表中元素1为2
    ChangeByElement(&a, 4, 2);
    PrintList(&a);
    ChangeByIndex(&a, 1, 1);
    PrintList(&a);

    return 0;
}

struct Node * Search_Element(struct Node *pHead, int Data)//* 查找链表中元素Data对应的节点,默认只找一个
{
    //* 遍历链表，直到找到值为Data的节点或者链表为空
    while (pHead != NULL && pHead->Data != Data)
    {
        // 移动指针到下一个节点
        pHead = pHead->pNext;
    } 

    // 返回找到的节点，如果未找到则返回NULL
    if(pHead == NULL)return NULL;
    else return pHead;// 返回找到的节点
} 

struct Node * Search_Index(struct Node *pHead, int Index)//* 查找链表中的指定下标的节点
{
    int i = 0;
    while (pHead != NULL && i < Index)// 遍历链表，直到找到下标为Index的节点或者链表为空
    {
        // 移动指针到下一个节点
        pHead = pHead->pNext;
        i++;
    } 
    if(pHead == NULL)return NULL;
    else return pHead;// 返回找到的节点
}

char ChangeByElement(struct Node *pHead, int OldValue, int NewValue)//* 替换链表中元素OldValue为NewValue
{
    char i = 0;
    while(pHead != NULL)
    {
        if(pHead->Data == OldValue)
        {
            pHead->Data = NewValue;
            i = 1;
        }
        // 移动指针到下一个节点
        pHead = pHead->pNext;
    }
    return i;
}

char ChangeByIndex(struct Node *pHead, int Index, int NewValue)//* 替换链表中的指定下标的元素为NewValue
{
    struct Node *pTarget = Search_Index(pHead, Index);
    if(pTarget == NULL)return 0;//该节点不存在
    else 
    {
        pTarget->Data = NewValue;
        return 1;
    }
}

int Number_Element(struct Node *pHead, int Data)//* 查找链表中某个元素的个数
{
    int i = 0;
    while (pHead != NULL)
    {
        if(pHead->Data == Data)i++;
        // 移动指针到下一个节点
        pHead = pHead->pNext;
    } 
    return i;
}

int Nodes_Element(struct Node *pHead, struct Node * Arr[4], int Data, int ArrSize)//* 查找链表中元素Data对应的节点和个数
{
    int i = 0;
    while (pHead != NULL)
    {
        if(pHead->Data == Data && i < ArrSize)
        {
            Arr[i++] = pHead;
        }
        // 移动指针到下一个节点
        pHead = pHead->pNext;
    } 
    return i;
}

void PrintList(struct Node *pHead)//* 打印链表
{
    printf("链表元素为：");
    while(pHead != NULL)
    {
        printf("%d ", pHead->Data);
        pHead = pHead->pNext;
    }
    printf("\n");
}
