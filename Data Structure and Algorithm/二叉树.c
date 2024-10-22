#include <stdio.h>
#include <malloc.h>

//! 二叉树结构：根节点、叶子节点、兄弟节点、前驱节点、后驱节点、左子树、右子树
//! 前序遍历、中序遍历、后序遍历：根左右、左根右、左右根


typedef struct Node
{ 
    int Data;
    struct Node * pFather;
    struct Node * pLeft;
    struct Node * pRight;
}TreeNode;

TreeNode * CreateTreeNode(int Data);//* 创建一个二叉树节点

 
int main(void)
{
    
    return 0;
}

TreeNode * CreateTreeNode(int Data)//* 创建一个二叉树节点
{
    //申请节点空间
    TreeNode * pNewNode = (TreeNode *)malloc(sizeof(TreeNode));
    if(pNewNode == NULL)
        return NULL;
    //节点成员们赋值
    pNewNode->Data = Data;
    pNewNode->pFather = NULL;
    pNewNode->pLeft = NULL;
    pNewNode->pRight = NULL;
    //返回节点地址
    return pNewNode;
}
