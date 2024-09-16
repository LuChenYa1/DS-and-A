#include <stdio.h>
#include <stdio.h>

int main(void)
{
    //* 打印左下角乘法表
    for(unsigned char i = 1; i < 10; i++)
    {
        for(unsigned char j = 1; j <=i; j++)
        {
            printf("%dx%d=%2d ", j, i, i*j);
        }
        printf("\n");
    }

    //* 打印左上角乘法表
    for(unsigned char i = 9; i > 0; i--)
    {
        for(unsigned char j = 1; j <=i; j++)
        {
            printf("%dx%d=%2d ", j, i, i*j);
        }
        printf("\n");
    }

    //* 打印右上角乘法表
    for(unsigned char i = 1; i < 10; i++)
    {
        for(unsigned char j = 1; j <=9; j++)
        {
            if(j >= i) printf("%dx%d=%2d ", j, i, i*j);
            else printf("       "); 
        }
        printf("\n");
    }

    //* 打印右下角乘法表
    for(unsigned char i = 9; i > 0; i--)
    {
        for(unsigned char j = 1; j <=9; j++)
        {
            if(j >= i) printf("%dx%d=%2d ", j, i, i*j);
            else printf("       ");
        }
        printf("\n");
    }
    return 0;
}

