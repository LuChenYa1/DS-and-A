#include <stdio.h>
#include <malloc.h>

//! 二叉树高度计算原理：利用栈遍历二叉树，入栈出栈过程中栈的元素个数最多时，为二叉树的高度

//* 二叉树节点定义
typedef struct TNode
{
    int Data;
    struct TNode * pFather;
    struct TNode * pLeft;
    struct TNode * pRight;
}TreeNode;

//* 数组栈
#define Deep 5
TreeNode * Stack[Deep];
int StackTop = -1;//初始没有数据，栈顶下标指向-1

int Max_Height;

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

//* 后序遍历，二叉树层数为栈的最大元素数量，更通用，能计算非平衡二叉树
void Look_1(TreeNode * pRoot)
{
    if(pRoot == NULL)
        return;
    TreeNode * pCurrent = pRoot;
    TreeNode * pPre = NULL;
    while(1)
    {
        //遍历左子树，一直到叶子节点
        while(pCurrent != NULL)
        {
            Push(pCurrent);
            pCurrent = pCurrent->pLeft;
        }
        if(StackTop == -1)
            break;

        //* 方法1（数组栈独有）
        //! 利用数组栈的特色：栈顶指针是下标，实时记录栈的元素个数并比较大小
        if(StackTop > Max_Height)
            Max_Height = StackTop;
        printf("%d ", StackTop + 1);

        if(Stack[StackTop]->pRight == NULL || Stack[StackTop]->pRight == pPre)
        {
            pPre = Pop();
            // printf("%d ", pPre->Data); 
        }
        else
            pCurrent = Stack[StackTop]->pRight;
    }
    Max_Height ++;
    printf("\n");
}

//* 前/中序遍历，二叉树层数为栈的最大元素数量加 1（只适用于平衡二叉树，只要多一个不满的层，栈最大数量和二叉树层数差距就加一）
void Look_2(TreeNode * pRoot)
{
    int Height = 0;
    if(pRoot == NULL)
        return;
    TreeNode * pCurrent = pRoot;
    while(1)
    {
        //遍历左子树，一直到叶子节点
        while(pCurrent != NULL)
        {
            // printf("%d ", pCurrent->Data);
            Push(pCurrent);
            pCurrent = pCurrent->pLeft;

            //* 方法二（通用）
            Height ++;
            if(Height > Max_Height)
                Max_Height = Height;
            printf("%d ", Height);
        }
        if(StackTop == -1)
            break;
        TreeNode * pTemp = Pop();
        Height --;
        pCurrent = pTemp->pRight;
    }
    Max_Height ++;
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

    //! 使用前序/中序遍历来计算二叉树层数时，必须保证二叉树为平衡二叉树，即除了叶子层，其他层都是满的
    // t7.pFather = &t5;
    // t8.pFather = &t5;
    // //* 此处有修改，层数变为5
    // t9.pFather = &t6;
    // t9.pRight = &t10;
    // t10.pFather = &t9;

    // 四层
    t6.pRight = &t10;
    t7.pFather = &t5;
    t8.pFather = &t5;
    t9.pFather = &t6;
    t10.pFather = &t6;
    
    printf("后序遍历: ");
    Look_1(&t1);
    printf("二叉树层数为%d\n", Max_Height);

    Max_Height = 0;

    printf("前序遍历: ");
    Look_2(&t1);
    printf("二叉树层数为%d\n", Max_Height);
    return 0;
}
