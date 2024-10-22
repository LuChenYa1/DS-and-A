#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct ActArrayType
{
    unsigned int Capacity;//空间容量
    int * pArray;//malloc空间指针
    unsigned int Number;//数据数量
};

void Struct_Init(struct ActArrayType * pStruct);//*结构体初始化
void Ensure_EnoughCapacity(struct ActArrayType * pStruct);//* 确保动态数组空间容量充足
void Malloc_Add(struct ActArrayType * pStruct, int Data);//* 动态数组增加元素
void Malloc_Insert(struct ActArrayType *pStruct, int Data, unsigned char Subscript);//* 动态数组插入元素
void Malloc_Delete_End(struct ActArrayType *pStruct);//* 动态数组删除末尾元素
void Malloc_Delete_All(struct ActArrayType *pStruct);//* 动态数组删除全部元素
void Malloc_freeSpace(struct ActArrayType *pStruct);//* 释放当前的动态数组
void Malloc_Delete(struct ActArrayType *pStruct, unsigned char Subscript);//* 删除指定下标的元素
void Print_ActArray(struct ActArrayType *pStruct);//*打印动态数组信息

int main(void)
{
    struct ActArrayType ActArray;
    Struct_Init(&ActArray);

    Malloc_Add(&ActArray, 1);
    Malloc_Add(&ActArray, 2);
    Malloc_Add(&ActArray, 99935);
    Malloc_Add(&ActArray, 4);
    Malloc_Add(&ActArray, 5);
    Malloc_Add(&ActArray, 6);
    Malloc_Add(&ActArray, 7);
    Malloc_Insert(&ActArray, 3, 0);
    Malloc_Insert(&ActArray, 9, 10);

    //Print_ActArray(NULL);
    Print_ActArray(&ActArray);//输出

    Malloc_Delete_End(&ActArray);
    Malloc_Delete_End(&ActArray);
    Malloc_Delete_All(&ActArray);
    Malloc_freeSpace(&ActArray);
    Print_ActArray(&ActArray);//再次输出

    Struct_Init(&ActArray);
    Malloc_Add(&ActArray, 1);
    Malloc_Add(&ActArray, 2);
    Malloc_Add(&ActArray, 4);
    Print_ActArray(&ActArray);//再次输出

    Malloc_Delete(&ActArray, 1);
    Print_ActArray(&ActArray);//再次输出

    free(ActArray.pArray);//*释放旧空间

    //!system("pause");需点击任意键以继续程序运行
    return 0;
}

void Struct_Init(struct ActArrayType * pStruct)//*结构体初始化
{
    pStruct->Capacity = 5;
    pStruct->pArray = (int *)malloc(sizeof(int) * 10);
    pStruct->Number = 0;
}

void Ensure_EnoughCapacity(struct ActArrayType * pStruct)//* 确保malloc空间容量充足
{
    if(NULL == pStruct)
    {
        fprintf(stderr, "参数错误\n"); // 使用stderr输出错误信息
        return;//void函数，返回空
    }
    
    if(pStruct->Capacity == pStruct->Number)//数据数量不小于空间容量
    {
        pStruct->Capacity += 5;//增加容量
        int *pTemp = (int *)malloc(sizeof(int) * pStruct->Capacity);//申请空间
        for (int i = 0; i < pStruct->Number; i++)//原样复制
        {
            pTemp[i] = pStruct->pArray[i];
        }
        free(pStruct->pArray);//*释放旧空间
        pStruct->pArray = pTemp;//将指针指向新空间地址
    }
}

void Malloc_Add(struct ActArrayType * pStruct, int Data)//*malloc动态数组增加元素
{  
    if(NULL == pStruct)
    {
        fprintf(stderr, "参数错误\n"); // 使用stderr输出错误信息
        return;//void函数，返回空
    }

    Ensure_EnoughCapacity(pStruct);

    pStruct->pArray[pStruct->Number] = Data;//*将新元素放到数组里
    pStruct->Number ++;
}

void Malloc_Insert(struct ActArrayType *pStruct, int Data, unsigned char Subscript)//*malloc动态数组插入元素
{
    if(NULL == pStruct)
    {
        fprintf(stderr, "参数错误\n"); // 使用stderr输出错误信息
        return;//void函数，返回空
    }

    Ensure_EnoughCapacity(pStruct);
    
    if(Subscript >= pStruct->Number) Subscript = pStruct->Number;//*下标过大时，排在所有元素末尾

    for(unsigned int i = pStruct->Number; i > Subscript; i--)//*从插入处往后挪，给新元素留空位
    {
        pStruct->pArray[i] = pStruct->pArray[i - 1];
    }

    pStruct->pArray[Subscript] = Data;//数据根据下标赋值到指定位置

    pStruct->Number ++;
}

void Malloc_Delete_End(struct ActArrayType *pStruct)//* malloc动态数组删除末尾元素
{
    if(NULL == pStruct)
    {
        fprintf(stderr, "参数错误\n"); // 使用stderr输出错误信息
        return;
    }
    pStruct->Number --;
    //! 只需要将数量减一，元素没必要清零，清零和保留原值没区别，系统只认元素数量
    // 这里删除元素后如果数量和容量不匹配，一般不需要重新申请空间，尽量减少多余操作，因为大概率后面需要再增加元素
}

void Malloc_Delete_All(struct ActArrayType *pStruct)//* malloc动态数组删除全部元素
{
    if(NULL == pStruct)
    {
        fprintf(stderr, "参数错误\n"); // 使用stderr输出错误信息
        return;
    }
    pStruct->Number = 0;
}

void Malloc_freeSpace(struct ActArrayType *pStruct)// 释放当前的malloc动态数组
{
    if(NULL == pStruct)
    {
        fprintf(stderr, "参数错误\n"); // 使用stderr输出错误信息
        return;
    }
    pStruct->Number = 0;
    pStruct->Capacity = 0;
    free(pStruct->pArray);
    pStruct->pArray = NULL;
}

void Malloc_Delete(struct ActArrayType *pStruct, unsigned char Subscript)//* 删除指定下标的元素
{
    if(NULL == pStruct)
    {
        fprintf(stderr, "参数错误\n"); // 使用stderr输出错误信息
        return;
    }

    for(unsigned int i = Subscript; i < pStruct->Number - 1; i++)//* 从删除点开始，将后面的元素前移
    {
        pStruct->pArray[i] = pStruct->pArray[i + 1];
    }
    pStruct->Number --;
}

void Print_ActArray(struct ActArrayType *pStruct)//*打印malloc动态数组信息
{
    if(NULL == pStruct)
    {
        fprintf(stderr, "参数错误\n"); // 使用stderr输出错误信息
        return;
    }

    printf("Number:%d, Capacity:%d\n", pStruct->Number, pStruct->Capacity);
    printf("现有元素:");
    for (size_t i = 0; i < pStruct->Number; i++)
    {
        // printf("%p\n", &(pStruct.pArray[i]));指针类型是int，故加一空间地址前进四字节
        printf("%d ", pStruct->pArray[i]);
    }
    printf("\n");
}

