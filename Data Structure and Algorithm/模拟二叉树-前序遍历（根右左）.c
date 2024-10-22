#include <stdio.h>
#include <malloc.h>

//! 二叉树结构：根节点、叶子节点、兄弟节点、前驱节点、后驱节点、左子树、右子树
//* 前序遍历、中序遍历、后序遍历：根左右、左根右、左右根

//! 栈的最大节点个数取决于二叉树的深度，假设树的深度为4，则栈在入栈出栈过程中的节点数量最大也为4个

//! 前序遍历的关键是节点入栈立马打印

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

//* 使用递归实现前序遍历(根右左)
void Look_1(TreeNode * pRoot) 
{
    if(pRoot != NULL)
    {
        //这三行代码的不同位置可以实现三种遍历方式
        printf("%d ", pRoot->Data);
        //push(pRoot);
        //* 使用一个容量10的栈按顺序装着每次要打印的节点，函数结束后，使用循环打印这个栈即可完成某种顺序的正序/倒序遍历
        Look_1(pRoot->pRight);
        Look_1(pRoot->pLeft);
    }
}

//* 利用数组栈遍历二叉树
void Look_2(TreeNode * pRoot)
{
    if(pRoot == NULL)
        return;
    TreeNode * pCurrent = pRoot;
    while(1)//退出条件：树没有了，栈也没有了
    {
        //遍历右子树，一直到叶子节点
        while(pCurrent != NULL)
        {
            printf("%d ", pCurrent->Data);
            Push(pCurrent);
            pCurrent = pCurrent->pRight;
        }
        //! 判断退出条件写在这里，目的是预防接下来可能使用空指针导致报错
        if(StackTop == -1)//此时pCurrent 一定是NULL，只需要判断栈顶是否为空头即可
            break;

        //取出栈顶节点，转到右节点(然后循环回到开始，遍历右节点的左子树)
        TreeNode * pTemp = Pop();
        pCurrent = pTemp->pLeft;
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
