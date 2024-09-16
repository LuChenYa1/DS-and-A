#include <stdio.h>
#include <malloc.h>

//! malloc太多空间，CPU占用率会大幅提高，导致程序卡顿，所以要及时释放空间
//! 双向链表相对单向链表的优势是，要增删节点时不必找到目标节点的前一个节点

typedef struct Node
{
    int Data;
    struct Node * pPre;
    struct Node * pNext; 
}LLNode;

LLNode * pHead = NULL, * pEnd = NULL;
int NodeCount = 0;

void AddToHead(int Data);//* 头添加
void AddToEnd(int Data);//* 尾添加
void AddNodeByIndex(int Index, int Count, int Data);//* 在指定下标增加指定数量的节点
void AddNodeBeforeData(int PosData, int AddData);//* 在目标节点的前面增加节点


void PrintLList(void);//* 打印链表
void PrintLList_Z(void);//* 反向打印链表

void FreeLList(void);//* 释放链表

int main(void)
{
    AddToEnd(1);
    AddToEnd(2);
    AddToEnd(3);
    AddToHead(4);
    AddNodeByIndex(0, 2, 500);
    AddNodeByIndex(NodeCount, 1, 600);
    AddNodeByIndex(5, 3, 700);
    PrintLList();
    AddNodeBeforeData(700, 0);

    PrintLList();
    //PrintLList_Z();

    FreeLList();
    return 0;
}

void AddToHead(int Data)//* 头添加
{
    //申请空间
    LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if(pNewNode == NULL)return;
    //节点成员赋值
    pNewNode->Data = Data;
    pNewNode->pPre = NULL;
    pNewNode->pNext = NULL;
    //链接
    if(pHead == NULL)//空链表
        pEnd = pNewNode;//新节点即是头，也是尾
    else
    {
        pNewNode->pNext = pHead;
        pHead->pPre = pNewNode;
    }
    pHead = pNewNode;
    NodeCount ++;
}

void AddToEnd(int Data)//* 尾添加
{
    //申请空间
    LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if(pNewNode == NULL)return;
    //节点成员赋值
    pNewNode->Data = Data;
    pNewNode->pPre = NULL;
    pNewNode->pNext = NULL;
    //链接
    if(pHead == NULL)//空链表
        pHead = pNewNode;//新节点即是头，也是尾
    else
    {
        pEnd->pNext = pNewNode;//修改旧尾节点的pNext
        pNewNode->pPre = pEnd;//记录前节点地址
    }
    pEnd = pNewNode;//尾添加必做：尾指针指向尾节点
    //节点数量加一
    NodeCount ++;
}

void AddNodeByIndex(int Index, int Count, int Data)//* 在指定下标增加指定数量的节点
{
    if(Index < 0 || Index > NodeCount || Count < 1)
        return;
    if(Index == 0)
        for(int i = 0; i < Count; i++)
            AddToHead(Data);
    else if(Index == NodeCount)
        for(int i = 0; i < Count; i++)
            AddToEnd(Data);
    else
    {
        //寻找指定下标节点
        LLNode * pCurrent = pHead;
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
        NodeCount += Count;
    } 
}

void AddNodeBeforeData(int PosData, int AddData)//* 在目标节点的前面增加节点
{
    //空链表检测
    if(pHead == NULL)return;
    //头添加
    if(pHead->Data == PosData)
    {
        AddToHead(AddData);
        return;
    }
    //查找目标节点
    LLNode * pCurrent = pHead;
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
            NodeCount ++;
        }
        pCurrent = pCurrent->pNext;
    }
}


void FreeLList(void)//释放链表
{
    if(pHead == NULL)return;//空链表无需释放，不必往下执行
    LLNode * pCurrent = pHead;
    while(pCurrent != NULL)
    {
        LLNode * pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        free(pCurrent);
    }
    pHead = NULL;
    pEnd = NULL;
    NodeCount = 0;
}

void PrintLList(void)//打印链表
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

void PrintLList_Z(void)//反向打印链表
{
    if(pHead == NULL)return;
    LLNode * pCurrent = pEnd;
    printf("反向打印：链表有%d个节点\n", NodeCount);
    while (pCurrent != NULL)
    {
        printf("%d ", pCurrent->Data);
        pCurrent = pCurrent->pPre;
    }
    putchar('\n');
}

