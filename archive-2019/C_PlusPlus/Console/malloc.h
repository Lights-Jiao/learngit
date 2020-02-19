#ifndef __MALLOC_H__
#define __MALLOC_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

/*
 * ʾ��һ
 * ���������Example_1_GetMemory���������ܴ��ݶ�̬�ڴ棬Example_1_Test�����е�strһֱ��NULL
 */
void Example_1_GetMemory(char* p)
{
    p = (char*)malloc(100);
}

void Example_1_Test(void)
{
    char* str = NULL;
    Example_1_GetMemory(str);
    strcpy(str, "Hello world!");
    printf("%s\n", str);
}


/*
 * ʾ����
 * ���������룬Example_2_Getmemory���ص���ָ��ջ�ڴ桱��ָ�룬��ָ��ĵ�ַ���� NULL������ԭ�ֵ������Ѿ�������������ݲ���֪
 * ����취��ʹ��malloc�������ڴ棻 ����������Ϊstatic����
 */
char* Example_2_Getmemory(void)
{
    char p[] = "Hello world!";

    return p;
}

void Example_2_Test(void)
{
    char* str = NULL;
    str = Example_2_Getmemory();
    printf("%s\n", str);
}


/*
 * ʾ����
 * �������У����ڴ�й©
 */
void Example_3_Getmemory(char**p, int num)
{
    *p = (char*)malloc(num);
}

void Example_3_Test(void)
{
    char* str = NULL;
    Example_3_Getmemory(&str, 100);
    strcpy(str, "Hello world!");
    printf(str);
}


/*
 * ʾ����
 * �۸Ķ�̬�ڴ��������ݣ��������Ԥ�ϣ��ǳ�Σ�ա���Ϊfree(str);֮��str��ΪҰָ�룬if(str != NULL)��䲻�����á�
 * Ұָ����򣺳�ʼ�����ͷŹ���û�м�ʱ��ָ��NULL�����ٴα����ã� ����������ĵ��ã�һ�Դ�����Ϊһ�������򣩣�����ջ����ľֲ�������ַ����Example_2_Getmemory
 * Ұָ�� Wikipedia https://zh.wikipedia.org/wiki/%E8%BF%B7%E9%80%94%E6%8C%87%E9%92%88
 */

void Example_4_Getmemory(char**p, int num)
{
    *p = (char*)malloc(num);
    strcpy(*p, "Hello");
    free(*p);
}
void Example_4_Test(void)
{
    char* str = (char*)malloc(100);
    strcpy(str, "Hello");
    free(str);

    if (NULL != str)
    {
        strcpy(str, "world!");
        printf(str);
    }
}


#endif