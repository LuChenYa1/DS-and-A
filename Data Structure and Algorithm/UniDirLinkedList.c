#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

//! 链表和动态数组一样，只需要一个指针名字装着头节点地址即可，不需要每增加一个节点，就起一个新的名字
//! 都是利用malloc申请内存，然后指针指向这个内存地址，最后再释放掉
//! 区别是，动态数组是连续的内存空间，链表是离散的内存空间，malloc申请空间返回的地址强转类型也不同，链表一定是结构体类型，动态数组按需转换
//! 有空头节点，保证头节点指针不变,但无论有无空头，头节点都得装数据，区别只在用不用这个数据
//! 动态记录尾指针，优点是末尾增加新节点时无需再从头轮询得到尾指针，提高代码执行效率
//函数内改变指针需要二级指针
//! void函数中的return;起退出函数作用

//* 定义一个单链表节点结构体 */
typedef struct Node
{
    char Data[10];//! 10个看得见的字符，不包含'\0'
    struct Node *pNext;
}LLNode;

void AddToHead(LLNode ** pHead, LLNode ** pEnd, char * Data)//* 在开头增加新节点
{
    //创建节点
    LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if(pNewNode != NULL)
    {
        //节点成员赋值
        strcpy(pNewNode->Data, Data);
        pNewNode->pNext = NULL;
        //链接
        if(*pHead == NULL)//空链表
        {
            *pEnd = pNewNode;//新节点即是头也是尾
        }
        else 
            pNewNode->pNext = *pHead;//连接新头节点和旧尾节点
        *pHead = pNewNode;//头指针指向新节点
    }
}
void AddToEnd(LLNode ** pHead, LLNode ** pEnd, char * Data)//* 在末尾增加新节点
{
    //创建节点
    LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if(pNewNode != NULL)//存在申请空间失败的可能性
    {
        //节点成员赋值
        strcpy(pNewNode->Data, Data);
        pNewNode->pNext = NULL;//必须
        //连上去
        if(*pHead == NULL)//空链表
        {
            *pHead = pNewNode;//新节点成为第一个节点
        }
        else 
            (*pEnd)->pNext = pNewNode;//连接旧尾节点和新尾节点
        *pEnd = pNewNode;//尾指针指向新节点
    }
}

void DeleteHead(LLNode ** pHead, LLNode ** pEnd)
{
    if(*pHead == NULL)//空链表
        return;
    if((*pHead)->pNext == NULL)//只有一个节点
    {
        free(*pHead);
        *pHead = NULL;
        *pEnd = NULL;
    }
    else
    {
        LLNode * pTemp = *pHead;
        *pHead = (*pHead)->pNext;
        free(pTemp);
    }  
}
void DeleteNodeByIndex()
{

}

void AddSomeNodeToEnd(LLNode ** pHead, LLNode ** pEnd, unsigned int Number, char * Data)
{
    for(int i = 0; i < Number; i++)
        AddToEnd(pHead, pEnd, Data);
}

LLNode * FindNodeByIndex(LLNode * pHead, unsigned int Index)//* 通过下标查找节点
{
    //参数合法性检测
    if(pHead == NULL || Index < 0)
    {
        printf("指针为NULL/下标无效，请检查参数");
        return NULL;
    }
    //循环链表
    int i = 0;
    while (pHead != NULL)
    {
        if(i == Index)
            return pHead;
        i++;
        pHead = pHead->pNext;
    }
    printf("下标过大，请检查参数");
    return NULL;
}

LLNode * FindNodeByData(LLNode * pHead, char * Data)//* 通过数值查找节点
{
    if(pHead == NULL)
        return NULL;//空链表
    while (pHead != NULL)
    {
        if(strcmp(pHead->Data, Data) == 0)
            return pHead;//找到了
        pHead = pHead->pNext;
    }
    return NULL;//链表无符合要求的节点
}

void ChangeDataByData(LLNode * pHead, char * OldData, char * NewData)//* 修改指定数值的节点的数值（只修改第一个找到的节点）
{
    LLNode * pDes = FindNodeByData(pHead, OldData);
    if(pDes != NULL)
        strcpy(pDes->Data, NewData);
    else
        printf("查无此节点\n");
}

void ChangeAllDataByData(LLNode * pHead, char * OldData, char * NewData)//* 修改指定数值的节点的数值（全部符合要求的节点都进行修改）
{
    while(pHead != NULL)
    {
        if(strcmp(pHead->Data, OldData) == 0)  
            strcpy(pHead->Data, NewData); 
        pHead = pHead->pNext;
    }
    
    /* //方法2：通过调用只修改一次的函数逐次修改全部
    LLNode * pDes = pHead;
    while(pDes != NULL)
    {
        pDes = FindNodeByData(pHead, OldData);
        if(pDes != NULL)
            strcpy(pDes->Data, NewData);
    } */
}

void InsertNodeByIndex(LLNode ** pHead, LLNode ** pEnd, unsigned int Index, char * Data)//* 通过下标插入节点
{
    if(Index < 0)
    {
        printf("下标小于0，请检查参数");
        return;
    }
    else if(Index == 0)
    {
        AddToHead(pHead, pEnd, Data);
    }
    else
    {
        LLNode * pLast = FindNodeByIndex(*pHead, Index - 1);
        if(pLast != NULL)
        {
            //创建节点
            LLNode * pNewNode = (LLNode *)malloc(sizeof(LLNode));
            //节点成员赋值
            strcpy(pNewNode->Data, Data);
            pNewNode->pNext = NULL;
            //链接
            pNewNode->pNext = pLast->pNext;
            pLast->pNext = pNewNode;
        }
        else
            printf("下标越界，查找前节点失败");
    }
}

void FreeList(LLNode ** pHead, LLNode ** pEnd)//* 释放链表空间，头尾指针清零
{
    LLNode * pCurrent = *pHead;
    while(pCurrent != NULL)
    {
        LLNode * pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        free(pTemp);
    }
    *pHead = NULL;
    *pEnd = NULL;
}

void ShowList_Data(LLNode *  pHead)//* 打印链表
{
    LLNode * pCurrent = pHead;
    while(pCurrent != NULL)
    {
        printf("%s\n", pCurrent->Data);
        pCurrent = pCurrent->pNext;
    }
    printf("\n");
}

int main(void)
{
    struct Node * pHead = NULL;
    struct Node * pEnd = NULL;
    
    //增加节点
    AddToEnd(&pHead, &pEnd, "FFFFFFFFF");
    AddToHead(&pHead, &pEnd, "This is 0");
    AddToEnd(&pHead, &pEnd, "1");
    AddToEnd(&pHead, &pEnd, "22");
    AddToHead(&pHead, &pEnd, "333");
    //根据下标查找节点
    LLNode * pTemp = FindNodeByIndex(pHead, 2);
    //增加多个节点
    AddSomeNodeToEnd(&pHead, &pEnd, 5, "ALL Same");
    //在指定下标插入节点
    InsertNodeByIndex(&pHead, &pEnd, 8, "Hello");
    //根据数值查找节点
    pTemp = FindNodeByData(pHead, "1");
    //修改节点数值
    ChangeDataByData(pHead, "ALL Same", "Not Same");
    //修改节点数值（全部）
    ChangeAllDataByData(pHead, "ALL Same", "All Diff");
    //显示链表
    ShowList_Data(pHead);
    //删除头节点
    DeleteHead(&pHead, &pEnd);
    //显示链表
    ShowList_Data(pHead);
    //释放链表
    FreeList(&pHead, &pEnd);

    return 0;
}
