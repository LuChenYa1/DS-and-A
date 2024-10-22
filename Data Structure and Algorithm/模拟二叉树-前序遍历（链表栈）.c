#include <stdio.h>
#include <malloc.h>

//! 二叉树结构：根节点、叶子节点、兄弟节点、前驱节点、后驱节点、左子树、右子树
//* 前序遍历、中序遍历、后序遍历：根左右、左根右、左右根

//* 栈的最大节点个数取决于二叉树的深度，假设树的深度为4，则栈在入栈出栈过程中的节点数量最大也为4个

//! 前序遍历的关键是节点入栈立马打印

//* 二叉树节点定义
typedef struct TNode
{
    int Data;
    struct TNode * pFather;
    struct TNode * pLeft;
    struct TNode * pRight;
}TreeNode;

//* 链表栈节点定义
typedef struct SNode
{
    TreeNode * pTree;//装着二叉树节点
    struct SNode * pNext;
    struct SNode * pPre;
}StackNode;

//* 链表栈的空头
StackNode Head;
//* 链表栈的栈顶指针（尾指针）
StackNode * pStackTop = &Head;//初始没有数据，指向空头

//* 二叉树节点入链表栈（尾添加）
void Push(TreeNode * pTree)
{
    //参数合法性检测
    if(pTree == NULL)
        return;
    //申请栈节点
    StackNode * pNewStack = (StackNode *)malloc(sizeof(StackNode));
    if(pNewStack == NULL)
        return;
    //栈节点成员赋值
    pNewStack->pTree = pTree;
    pNewStack->pPre = NULL;
    pNewStack->pNext = NULL;
    //链接
    pStackTop->pNext = pNewStack;
    pNewStack->pPre = pStackTop;
    pStackTop = pNewStack;
}

//* 二叉树节点出链表栈（尾删除）
TreeNode * Pop(void)
{
    //栈为空
    if(pStackTop == &Head)
        return NULL;
    //记录要删除的栈顶节点
    TreeNode * pTree = pStackTop->pTree;
    //释放栈顶节点、修改栈顶指针
    pStackTop = pStackTop->pPre;
    free(pStackTop->pNext);
    pStackTop->pNext = NULL;
    //返回删除的二叉树节点
    return pTree;
}

//* 使用递归实现前序遍历
void Look_1(TreeNode * pRoot) 
{
    if(pRoot != NULL)
    {
        //这三行代码的不同位置可以实现三种遍历方式
        printf("%d ", pRoot->Data);
        Look_1(pRoot->pLeft);
        Look_1(pRoot->pRight);
    }
}

//* 利用链表栈遍历二叉树
void Look_2(TreeNode * pRoot)
{
    if(pRoot == NULL)
        return;
    TreeNode * pCurrent = pRoot;
    while(1)//退出条件：树没有了，栈也没有了
    {
        //遍历左子树，一直到叶子节点
        while(pCurrent != NULL)
        {
            printf("%d ", pCurrent->Data);
            Push(pCurrent);
            pCurrent = pCurrent->pLeft;
        }
        //! 判断退出条件写在这里，目的是预防接下来可能使用空指针导致报错
        if(pStackTop == &Head)//此时pCurrent 一定是NULL，只需要判断栈顶是否为空头即可
            break;

        //取出栈顶节点，转到右节点(然后循环回到开始，遍历右节点的左子树)
        TreeNode * pTemp = Pop();
        pCurrent = pTemp->pRight;

        //判断是否遍历全部
        //pStackTop == &Head：已经遍历到根节点的最右边，往左往上的节点都已经出栈且打印了
        //pCurrent == NULL：pTemp 是叶子节点
    }
    printf("\n");
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
    
    Look_1(&t1);
    printf("\n");
    Look_2(&t1);

    return 0;
}
