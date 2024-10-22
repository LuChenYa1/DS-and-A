#include <stdio.h>
#include <malloc.h>



typedef struct Node
{
    int Data;
    struct Node * pFather;
    struct Node * pLeft;
    struct Node * pRight;
}TreeNode;

int Count(TreeNode * pRoot)
{   
    if(pRoot == NULL)
        return 0;
    int Left = Count(pRoot->pLeft);
    int Right = Count(pRoot->pRight);
    if(Left >= Right)
        return Left + 1;
    else
        return Right + 1;
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

    printf("二叉树高度为%d\n", Count(&t1));

    return 0;
} 
