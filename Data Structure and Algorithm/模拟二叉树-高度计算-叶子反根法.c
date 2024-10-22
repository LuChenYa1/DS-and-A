#include <stdio.h>
#include <malloc.h>


typedef struct TNode
{
    int Data;
    struct TNode * pFather;
    struct TNode * pLeft;
    struct TNode * pRight;
}TreeNode;

int Max_Number;

//* 数组栈
#define Deep 5
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

void GetLayers(TreeNode * pLeaf)
{
    //* 如果当前遍历的节点是叶子节点，则开始向根节点反推，累加层数
    if(pLeaf->pLeft == NULL && pLeaf->pRight == NULL)
    {
        int Branch_Number = 0;
        while(pLeaf)
        {
            Branch_Number ++;
            pLeaf = pLeaf->pFather;
        }
        printf("%d ", Branch_Number);
        if(Branch_Number > Max_Number)
            Max_Number = Branch_Number;
    }
}

//* 递归实现
void Look_1(TreeNode * pRoot)
{   
    if(pRoot == NULL)
        return;
    //* 计算当前叶子节点的层数（如果是叶子节点）
    GetLayers(pRoot);
    Look_1(pRoot->pLeft);
    Look_1(pRoot->pRight);
}

//* 非递归实现
void Look_2(TreeNode * pRoot)
{   
    if(pRoot == NULL)
        return;
    while(1)
    {
        while(pRoot)//* 左子树入栈
        {
            Push(pRoot);
            pRoot = pRoot->pLeft;
        }
        //* 遍历到最后一个节点
        if(StackTop == -1)
            break;
        //* 取出最近入栈的节点
        pRoot =  Pop();
        //* 计算当前叶子节点的层数（如果是叶子节点）
        GetLayers(pRoot);
        //* 转到右子树
        pRoot = pRoot->pRight;
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

    t7.pFather = &t5;
    t8.pFather = &t5;
    //* 此处有修改，层数变为5
    t9.pFather = &t6;
    t9.pRight = &t10;

    t10.pFather = &t9;

    Look_1(&t1);
    printf("递归法计算二叉树的高度为 %d \n", Max_Number);
    Look_2(&t1);
    printf("非递归法计算二叉树的高度为 %d \n", Max_Number);

    return 0;
} 
