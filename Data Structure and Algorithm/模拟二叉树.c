#include <stdio.h>
#include <malloc.h>

//! 二叉树结构：根节点、叶子节点、兄弟节点、前驱节点、后驱节点、左子树、右子树
//! 前序遍历、中序遍历、后序遍历：根左右、左根右、左右根

//* 二叉树节点定义
typedef struct TNode
{
    int Data;
    struct TNode * pFather;
    struct TNode * pLeft;
    struct TNode * pRight;
}TreeNode;

//* 栈节点定义
typedef struct SNode
{
    TreeNode * pTreeNode;//装着二叉树节点
    struct SNode * pNext;
    struct SNode * pPre;
}StackNode;

//* 栈的空头
StackNode Head;
//* 栈的栈顶指针（尾指针）
StackNode * pStackTop = &Head;

//* 二叉树节点入栈（尾添加）
void Push(TreeNode * pTreeNode)
{
    //参数合法性检测
    if(pTreeNode == NULL)
        return;
    //申请栈节点
    StackNode * pNewStackNode = (StackNode *)malloc(sizeof(StackNode));
    if(pNewStackNode == NULL)
        return;
    //栈节点成员赋值
    pNewStackNode->pTreeNode = pTreeNode;
    pNewStackNode->pPre = NULL;
    pNewStackNode->pNext = NULL;
    //链接
    pStackTop->pNext = pNewStackNode;
    pNewStackNode->pPre = pStackTop;
    pStackTop = pNewStackNode;
}

//* 二叉树节点出栈（尾删除）
TreeNode * Pop(void)
{
    //栈为空
    if(pStackTop == &Head)
        return NULL;
    //记录要删除的栈顶节点
    TreeNode * pTreeNode = pStackTop->pTreeNode;
    //释放栈顶节点、修改栈顶指针
    pStackTop = pStackTop->pPre;
    free(pStackTop->pNext);
    pStackTop->pNext = NULL;
    //返回删除的二叉树节点
    return pTreeNode;
}

//! 利用递归遍历二叉树时类似栈的入栈出栈过程，一旦开始执行某节点函数的第一句，该节点就算入栈，执行了最后一句（遍历右子树）该节点就出栈
void PrintTreeList(TreeNode * TreeNode) 
{
    if(TreeNode != NULL)
    {
        //这三行代码的不同位置可以实现三种遍历方式
        printf("%d ", TreeNode->Data);
        PrintTreeList(TreeNode->pLeft);
        PrintTreeList(TreeNode->pRight);
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
    
    PrintTreeList(&t1);

    return 0;
}
