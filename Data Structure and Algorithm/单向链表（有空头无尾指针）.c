#include <stdio.h>
#include <string.h>
#include <malloc.h>

//! 没有尾指针，有空头         有空头 简化代码逻辑，少了判断头尾的过程
//! 空头的数据变量用于存储节点数量, 最大程度利用链表空间
//! 加节点计数器，要注意数量变化

//! 实际情况尾添加最频繁，故需要尾指针，避免每次尾添加都要从头轮询到尾节点，提高执行效率

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
void AddSomeNodeByIndex(LLNode * stHead, int Index, int Number, int Data);//* 在指定位置插入多个节点

//* 删
void DeleteNodeByData(LLNode * stHead, int Data);//* 通过数据删除节点
void DeleteNodeByIndex(LLNode * stHead, int Index);//* 通过下标删除节点
void DeleteSame(LLNode * stHead);//* 链表去重

//* 改
void ChangeNodeByData(LLNode * stHead, int OldData, int NewData);//* 通过数据修改节点
void ChangeAllNodeByData(LLNode * stHead, int OldData, int NewData);//* 通过数据修改所有符合要求的节点
void ChangeNodeByIndex(LLNode * stHead, int Index, int Data);//* 通过下标修改节点

//* 查      查找节点不涉及修改，可以传入结构体本身，但执行效率变低
LLNode * FindNodeByData(LLNode * stHead, int Data);//* 通过数据查找节点
LLNode * FindNodeByIndex(LLNode * stHead, int Index);//* 通过下标查找节点


void FreeList(LLNode * stHead);//* 释放链表

void PrintList(LLNode stHead);//* 打印链表

int main(void)
{
    //定义一个空头
    LLNode stHead = {0, NULL};

    //*增
    AddToHead(&stHead, 4);
    AddToEnd(&stHead, 5);
    AddToHead(&stHead, 2);
    AddBehandData(&stHead, 2, 3);
    AddBehandData(&stHead, 2, 2);
    AddNodeByIndex(&stHead, 4, 1);
    AddSomeNodeByIndex(&stHead, 0, 3, 6);
    PrintList(stHead);

    //* 改
    ChangeNodeByData(&stHead, 6, 7);
    ChangeNodeByIndex(&stHead, 7, 8);
    ChangeAllNodeByData(&stHead, 6, 9);
    PrintList(stHead);

    //* 删
    DeleteNodeByIndex(&stHead, 7);
    DeleteNodeByData(&stHead, 9);
    PrintList(stHead);
    //实验去重
    AddToEnd(&stHead, 5);
    AddToEnd(&stHead, 4);
    AddToEnd(&stHead, 3);
    AddToEnd(&stHead, 2);
    AddToEnd(&stHead, 2);
    AddToEnd(&stHead, 10);
    PrintList(stHead);   
    DeleteSame(&stHead);
    PrintList(stHead);
    
    //* 查
    if(FindNodeByData(&stHead, 6) == NULL)
        printf("没找到\n");
    else
        printf("找到了\n");

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
    if(stHead == NULL || stHead->Data < 0 || Index < 0 || Index > stHead->Data)//* 可以尾添加
        return;
    LLNode * pFormer = FindNodeByIndex(stHead, Index - 1);
    if(pFormer != NULL)
    {
        AddToHead(pFormer, Data);
        pFormer->Data --;
        stHead->Data ++;
    }
}

void AddSomeNodeByIndex(LLNode * stHead, int Index, int Number, int Data)//* 在指定位置插入多个节点
{
    //参数合法性检测
    if(stHead == NULL || stHead->Data < 0 || Index < 0 || Index > stHead->Data)//* 可以尾添加
        return;
    LLNode * pFormer = FindNodeByIndex(stHead, Index - 1);
    if(pFormer != NULL)
    {
        for(int i = 0; i < Number; i++)
        {
            AddToHead(pFormer, Data);
            pFormer->Data --;
            stHead->Data ++;
        }    
    }
}

void DeleteSame(LLNode * stHead)//* 链表去重
{
    if(stHead == NULL || stHead->Data <= 1)
        return;
    //循环遍历
    LLNode * pCurrent = stHead->pNext;//要被比对数据的节点，不能是空头
    while(pCurrent->pNext != NULL)//尾节点不必再比较，没有可以比较的节点了，但也可以写成pCurrent != NULL
    {
        LLNode * pInner = pCurrent;//始终代表要被删除节点的前一个节点，本身不会被删除
        while(pInner->pNext != NULL)
        {
            if(pInner->pNext->Data == pCurrent->Data)
            {
                LLNode * pTemp = pInner->pNext;
                pInner->pNext = pTemp->pNext;
                free(pTemp);
                stHead->Data--;
            }
            else pInner = pInner->pNext;//防止遗漏补上来的节点
        }
        pCurrent = pCurrent->pNext;
    }
}

void DeleteNodeByData(LLNode * stHead, int Data)//* 通过数据删除节点
{
    //参数合法性检测
    if(stHead == NULL || stHead->Data <= 0)
        return;
    LLNode * pCurrent = stHead;
    while(pCurrent->pNext != NULL)//* 节点不能是尾节点 
    {
        if(pCurrent->pNext->Data == Data)//节点的下一个节点符合要求
        {
            //释放、链接
            LLNode * pTemp = pCurrent->pNext;
            pCurrent->pNext = pTemp->pNext;
            free(pTemp);
            //数量减一
            stHead->Data --;
        }
        else
            pCurrent = pCurrent->pNext;
    }
}

void DeleteNodeByIndex(LLNode * stHead, int Index)//* 通过下标删除节点
{
    //参数合法性检测
    if(stHead == NULL || stHead->Data <= 0 || Index < 0 || Index + 1 > stHead->Data)
        return;
    //循环找到指定节点的前一个节点
    LLNode * pCurrent = stHead;
    for(int i = 0; i < Index; i++)
        pCurrent = pCurrent->pNext;
    //释放节点，重新链接 
    LLNode * pTemp = pCurrent->pNext;
    pCurrent->pNext = pTemp->pNext;
    free(pTemp);
    //节点数量减一
    stHead->Data --;
}

void ChangeNodeByData(LLNode * stHead, int OldData, int NewData)//* 通过数据修改节点
{
    //参数合法性检测
    if(stHead == NULL || stHead->Data <= 0)
        return;
    LLNode * pTemp = FindNodeByData(stHead, OldData);
    if(pTemp == NULL)return;
    pTemp->Data = NewData;
}

void ChangeAllNodeByData(LLNode * stHead, int OldData, int NewData)//* 通过数据修改所有符合要求的节点
{
    //参数合法性检测
    if(stHead == NULL || stHead->Data <= 0)
        return;
    LLNode * pCurrent = stHead->pNext;//! 注意第一个节点是空头，只存放<节点数量>
    while(pCurrent != NULL)
    {
        if(pCurrent->Data == OldData)
            pCurrent->Data = NewData;
        pCurrent = pCurrent->pNext;  
    }
}

void ChangeNodeByIndex(LLNode * stHead, int Index, int Data)//* 通过下标修改节点
{
    //参数合法性检测
    if(stHead == NULL || stHead->Data <= 0 || Index < -1 || Index + 1 > stHead->Data)
        return;
    LLNode * pTemp = FindNodeByIndex(stHead, Index);
    if(pTemp == NULL)return;
    pTemp->Data = Data;
}  

LLNode * FindNodeByData(LLNode * stHead, int Data)//* 通过数据查找节点
{
    //参数合法性检测
    if(stHead == NULL || stHead->Data <= 0)
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
    if(stHead == NULL || stHead->Data <= 0 || Index < -1 || Index + 1 > stHead->Data)//查找已经存在的节点
        return NULL;
    if(Index == -1)
        return stHead;
    LLNode * pCurrent = stHead->pNext;//! 注意第一个节点是空头，只存放<节点数量>
    for(int i = 0; i < Index; i++)//! 已经利用节点数量排除下标过大的可能性，所以一定能找到节点，可以用for循环
        pCurrent = pCurrent->pNext;
    return pCurrent;
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
