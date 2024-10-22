#include <stdio.h>
#include <malloc.h>

//* 二叉搜索树特点：
//*  每个子树的根是分界点，左子树都是比根小的，右子树都是比根大的，且左 < 根 <= 右
//* 操作的逻辑顺序类似中序，数据的顺序也是中序的

//* 二叉树节点定义
typedef struct TNode
{
    int Data;
    struct TNode * pFather;
    struct TNode * pLeft;
    struct TNode * pRight;
}TreeNode;

void Insert(TreeNode ** pRoot, int Data)
{
    // 申请节点空间
    TreeNode * pNewNode = (TreeNode *)malloc(sizeof(TreeNode));
    if(pNewNode == NULL)
        return;
    //赋值
    pNewNode->Data = Data;
    pNewNode->pFather = NULL;
    pNewNode->pLeft = NULL;
    pNewNode->pRight = NULL;
    //* 树为空，新节点为根节点
    if(*pRoot == NULL)
        *pRoot = pNewNode;
    
}

int main()
{
    TreeNode * pRoot = NULL;
    Insert(&pRoot, 12);

    return 0;
}
