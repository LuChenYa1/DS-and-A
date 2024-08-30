#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


//! 链表和动态数组一样，只需要一个指针名字装着头节点地址即可，不需要每增加一个节点，就起一个新的名字
//! 都是利用malloc申请内存，然后指针指向这个内存地址，最后再释放掉
//! 区别是，动态数组是连续的内存空间，链表是离散的内存空间，malloc申请空间返回的地址强转类型也不同，链表一定是结构体类型，动态数组按需转换

//* 定义一个单链表节点结构体 */
typedef struct LLNode
{
    char Data[10];//! 10个看得见的字符，不包含'\0'
    struct LLNode *pNext;
}LLNode;

LLNode * Node_Init(char * Data);//* 初始化一个节点，并返回指向该节点的指针 
void Add_Node(LLNode * pHead, char * Data);//* 把节点加到链表尾部 
void Delete_EndNode(LLNode * pHead);//* 删除链表尾部节点
void Delete_Node(LLNode * pHead, char * Data);//* 根据节点值删除链表节点
//* 根据下标查找节点，返回指向该节点的指针
LLNode * Find_Node(LLNode * pHead, char * Data);//* 根据节点值寻找节点
void Change_Node(LLNode * pHead, char * OldData, char * NewData);//* 根据节点值修改节点
void Free_List(LLNode * pHead);//* 释放链表内存空间
void Print_List(LLNode * pHead);//* 遍历链表

int main(void)
{
    LLNode * pHead = NULL; 
    pHead = Node_Init("1234567890");

    printf("增\n");
    Add_Node(pHead, "1111111111");
    Add_Node(pHead, "2222222222");
    Add_Node(pHead, "3333333333");
    Add_Node(pHead, "4444444444");
    Add_Node(pHead, "5555555555");
    Add_Node(pHead, "6666666666");
    Print_List(pHead);
    printf("删\n");
    Delete_EndNode(pHead);
    Print_List(pHead);
    printf("-----------------------\n");
    Delete_Node(pHead, "4444444444");
    Print_List(pHead);
    printf("查-改\n");
    Change_Node(pHead, "2222222222", "7777777777");
    Print_List(pHead);

    Free_List(pHead);
    return 0;
}

LLNode * Node_Init(char * Data)//* 初始化一个节点，并返回指向该节点的指针 
{
    LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if(pNewNode != NULL)
    {
        strcpy(pNewNode->Data, Data);
        pNewNode->pNext = NULL;//! 这里一定要初始化，不然会出问题，会赋值一个随机地址
        return pNewNode;
    }
    else
    {
        printf("malloc failed!\n");
        return NULL;
    }
}

void Add_Node(LLNode * pHead, char * Data)//* 把新节点加到链表尾部 
{
    LLNode * pNewNode = Node_Init(Data);//初始化一个节点
    LLNode * pCurrent = pHead;
    if (pCurrent != NULL)
    {
        while(pCurrent->pNext != NULL)//非尾节点
        {
            pCurrent = pCurrent->pNext;
        }
        pCurrent->pNext = pNewNode;
    }
}

void Delete_EndNode(LLNode * pHead)//* 删除链表尾部节点
{
    LLNode * pCurrent = pHead;
    if (pCurrent->pNext != NULL)
    {
        while((pCurrent->pNext)->pNext != NULL)
        {
            pCurrent = pCurrent->pNext;
        }
        free(pCurrent->pNext);
        pCurrent->pNext = NULL;
    }
}

void Delete_Node(LLNode * pHead, char * Data)//* 根据节点值删除链表节点
{
    LLNode * pCurrent = pHead;
    while(pCurrent->pNext != NULL)
    {
        if(strcmp(pCurrent->pNext->Data, Data) == 0)
        {
            LLNode * pLast = pCurrent->pNext->pNext;
            free(pCurrent->pNext);
            pCurrent->pNext = pLast;
        }
        pCurrent = pCurrent->pNext;
    }
}

LLNode * Find_Node(LLNode * pHead, char * Data)//* 根据节点值寻找节点
{
    LLNode * pCurrent = pHead;
    while(pCurrent != NULL)
    {
        if(strcmp(pCurrent->Data, Data) == 0)
        {
            return pCurrent;
        }
        pCurrent = pCurrent->pNext;
    }
    return NULL;
}

void Change_Node(LLNode * pHead, char * OldData, char * NewData)//* 根据节点值修改节点
{
    LLNode * pCurrent = Find_Node(pHead, OldData);
    if(pCurrent != NULL)
    {
        strcpy(pCurrent->Data, NewData);
    }
}

void Free_List(LLNode * pHead)//* 释放链表内存空间
{
    LLNode * pCurrent = pHead;
    while(pCurrent != NULL)
    {
        free(pCurrent);
        pCurrent = pCurrent->pNext;
    }
}

//* 遍历链表
void Print_List(LLNode * pHead)
{
    LLNode * pCurrent = pHead;
    while (pCurrent != NULL)
    {
        printf("%s\n", pCurrent->Data);
        pCurrent = pCurrent->pNext;
    }
}
