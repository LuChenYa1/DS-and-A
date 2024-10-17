#include <stdio.h>
#include <malloc.h>

//* 原理：层序遍历利用队列实现，节点出队（并打印）时，让它的左右节点入队（先左后右）
//* 实现：同一层节点依次从左到右入队后，下一层节点再依次入队

typedef struct Node
{
    int Data;
    struct Node * pFather;
    struct Node * pLeft;
    struct Node * pRight;
}TreeNode;

//! 链表结构的队列：尾添加、头删除，单向有空头链表
//* 删除节点无需找前一个节点，所以采用单向链表，
//* 有空头可以简化逻辑，不考虑头指针变化，所以采用有空头链表
typedef struct LLNode
{
    TreeNode * pTreeNode;
    struct LLNode * pNext;
}QueueNode;

QueueNode QueueHead;//* 队头
QueueNode * pQueueEnd = &QueueHead;//* 队尾指针

void Push(TreeNode * Node)//尾添加
{
    if(Node == NULL)
        return;
    //创建节点
    QueueNode * pNew = (QueueNode *)malloc(sizeof(QueueNode));
    if(pNew == NULL)
        return;
    //节点成员赋值
    pNew->pTreeNode = Node;
    pNew->pNext = NULL;
    //链接：在队尾加入元素
    pQueueEnd->pNext = pNew;
    pQueueEnd = pNew;
}

//头删除
TreeNode * Pop(void)//* 一定要考虑删除的是尾节点的情况，此时尾指针需要指向空头
{
    //队中无元素，无需出队
    if(pQueueEnd == &QueueHead)
        return NULL;
    //记录队头（即将出队）
    QueueNode * pTemp = QueueHead.pNext;
    //修改指向
    QueueHead.pNext = pTemp->pNext;
    //* 要删除的头节点同时也是尾节点
    if(pTemp->pNext == NULL)
        pQueueEnd = &QueueHead;
    //* 记录队头存储的二叉树节点地址，因为队头存储的所有内容在return 之前已经被释放，包括需要返回的二叉树节点地址
    TreeNode * pNode = pTemp->pTreeNode;
    //释放队头
    free(pTemp);
    //返回原来的队头
    return pNode;
}

void Look(TreeNode * pRoot)
{
    //防止空二叉树
    if(pRoot == NULL)
        return;
    TreeNode * pCurrent = pRoot;
    Push(pCurrent);
    while(1)
    {
        pCurrent =  Pop();
        printf("%d ", pCurrent->Data);
        if(pCurrent->pLeft !=  NULL)
            Push(pCurrent->pLeft);
        if(pCurrent->pRight !=  NULL)
            Push(pCurrent->pRight);
        //* 出队时伴随着下一层节点入队，所以只有下一层没有节点即本层为最后一层时，本层节点全部出队后队列空了，此时二叉树层序遍历结束
        if(pQueueEnd == &QueueHead)
            return;
    }
}

int main(void)
{
    TreeNode t1 = {1};
    TreeNode t2 = {2};
    TreeNode t3 = {3};
    TreeNode t4 = {4};
    TreeNode t5 = {5};
    TreeNode t6 = {6};
    TreeNode t7 = {7};
    TreeNode t8 = {8};
    TreeNode t9 = {9};
    TreeNode t10 = {10};

    t1.pLeft = &t2;
    t1.pRight = &t3;

    t2.pFather = &t1;
    t2.pLeft = &t4;
    t2.pRight = &t5;

    t3.pFather = &t1;
    t3.pRight = &t6;

    t4.pFather = &t2;

    t5.pFather = &t2;
    t5.pLeft = &t7;
    t5.pRight = &t8;

    t6.pFather = &t3;
    t6.pLeft = &t9;
    t6.pRight = &t10;

    t7.pFather = &t5;
    t8.pFather = &t5;
    t9.pFather = &t6;
    t10.pFather = &t6;


    Look(&t1);

    return 0;
} 
