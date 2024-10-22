#include <stdio.h>
#include <malloc.h>

//! 二叉树结构：根节点、叶子节点、兄弟节点、前驱节点、后驱节点、左子树、右子树
//* 前序遍历、中序遍历、后序遍历：根左右、左根右、左右根

//! 栈的最大节点个数取决于二叉树的深度，假设树的深度为4，则栈在入栈出栈过程中的节点数量最大也为4个

//! 后序遍历的关键是节点出栈后立马打印
//* 判断Pop()返回的节点（上一个栈顶节点）是不是当前栈顶节点的右节点，如果是，说明右节点已经遍历过，接下来该使栈顶节点出栈，打印栈顶节点
//* 如果上一个栈顶节点是当前栈顶节点的左节点，则说明刚刚遍历完左节点，接下来该入栈并打印右节点

//* 二叉树节点定义
typedef struct TNode
{
    int Data;
    struct TNode * pFather;
    struct TNode * pLeft;
    struct TNode * pRight;
}TreeNode;

//* 数组栈
#define Deep 4
TreeNode * Stack[Deep];
int StackTop = -1;//初始没有数据，栈顶下标指向-1

//* 二叉树节点入数组栈（尾添加）
void Push(TreeNode * pTree)
{
    //参数合法性检测
    if(pTree == NULL)
        return;
    StackTop ++;
    Stack[StackTop] = pTree;
}

//* 二叉树节点出数组栈（尾删除）
TreeNode * Pop(void)
{
    //栈为空
    if(StackTop == -1)
        return NULL;
    int Temp = StackTop;
    StackTop--;
    return Stack[Temp];
}

//* 使用递归实现后序遍历
void Look_1(TreeNode * pRoot) 
{
    if(pRoot != NULL)
    {
        //这三行代码的不同位置可以实现三种遍历方式
        Look_1(pRoot->pLeft);
        Look_1(pRoot->pRight);
        printf("%d ", pRoot->Data);
    }
}

//* 利用数组栈遍历二叉树
void Look_2(TreeNode * pRoot)
{
    if(pRoot == NULL)
        return;
    TreeNode * pCurrent = pRoot;
    TreeNode * pPre = NULL;
    while(1)//退出条件：树没有了，栈也没有了
    {
        //遍历左子树，一直到叶子节点
        while(pCurrent != NULL)
        {
            Push(pCurrent);
            pCurrent = pCurrent->pLeft;
        }
        //! 判断退出条件写在这里，目的是预防接下来可能使用空指针导致报错
        if(StackTop == -1)//此时pCurrent 一定是NULL，只需要判断栈顶是否为空头即可
            break;
        //* 经过前面的一直遍历左子树，此时栈顶已经是最左节点 ，没有左子树了
        //* 后序遍历是左右根，左已经为空，无需遍历，需要再判断栈顶节点的右子树是否为空
        //* 如果右子树为空，无需遍历，那就轮到根节点，此时栈顶节点出栈并打印
        //* 如果右子树不为空，那就要判断右节点是否已经出栈打印过，没打印过才能让右节点入栈
        //* pPre 用于接收每次出栈的节点，作用是判断该节点是栈顶节点的左节点还是右节点

        if(Stack[StackTop]->pRight == NULL || Stack[StackTop]->pRight == pPre)
        {
            pPre = Pop();
            printf("%d ", pPre->Data); 
        }
        else
            pCurrent = Stack[StackTop]->pRight;
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
