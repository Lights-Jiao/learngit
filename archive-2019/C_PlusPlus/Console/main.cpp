#include <iostream>
#include "stdio.h"
#include "stdint.h"
#include "vector"
#include "time.h"
#include <cmath>
#include "string.h"
#include "stdlib.h"

#include "get100.h"                 //����1, 2, ..., 9������Ͻ������ 100
#include "StringWithMySplitFunc.h"  //split����������Ƨ����
#include "reserve_resize.h"         //����STL��reserve & resize ����
#include "knapstack.h"              //0-1 ��������
#include "CppProgram.h"             //��C++��������̡� ��Ĵ���
#include "BigNumMultiply.h"         //������˵�ʵ��
#include "malloc.h"                 //��C++��������̡� �ж��ڴ��˼����ʾ��
#include "NiuKeWangFirstTest.h"     //ţ��������������

#pragma warning(push)
#pragma warning(disable: 4996)
// #pragma warning(disable: 4305) // (33)  ����ʼ����: �ӡ�int������char���ض�
// #pragma warning(disable: 4309) // (33)  ����ʼ����: �ضϳ���ֵ
// #pragma warning(disable: 4018) // (240) ��<��: �з���/�޷��Ų�ƥ�� 
// #pragma warning(disable: 4477) // (67)  ��printf��: ��ʽ�ַ�����%x����Ҫ���͡�unsigned int���Ĳ��������ɱ���� 2 ӵ�������͡�int *��


using namespace std;


typedef uint32_t uint_32_t;

//ͨ��λ�ƣ����ٵļ��㿪���Ų����������������ȷ
float fast_sqrt(float x)
{
    uint_32_t x_bits = 0;
    x_bits = *((uint_32_t*) &x);
    x_bits = (x_bits >> 1) + 532369198;
    return *((float*)&x_bits);
}



//��ɽ�������⣬�ݹ�+ѭ��
int cc(int i)
{
    for (;  i < 4; )
    {
        std::cout << cc(++i);
    }
    return i;
}
void testcc()
{
    cc(1);
    return;
}


//lept_json �̳��� strtod��˵������֤
/* http://en.cppreference.com/w/c/string/byte/strtof */
#include <errno.h>
void test_strtod()
{
    const char *p = "111.11 -2.22 0X1.BC70A3D70A3D7P+6  1.18973e+309";
    printf("Parsing '%s':\n", p);
    char *end;
    for (double f = strtod(p, &end); p != end; f = strtod(p, &end))
    {
        printf("'%.*s' -> ", (int)(end - p), p);
        p = end;
        if (errno == ERANGE) {
            printf("range error, got ");
            errno = 0;
        }
        printf("%f\n", f);
    }
}

void testHuaWeiMianshi()
{
    char* str1 = "abc";
    char* str2 = "abc";
    //char[] str3 = "abc";
    //char[] str4 = "abc";
    const char* str5 = "abc";
    const char* str6 = "abc";
    //const char[] str7 = "bac";
    //const char[] str8 = "bac";

    //cout << (str1 == str2) << endl; //��0 ����false
    //cout << (str5 == str6) << endl; //��0 ����false

    /*
    ���ʼ��Ϊ����, �ؼ��Ǻ���ļ���0
    [1, 2,
     3, 0,
     0, 0]
    */
    int a[3][2] = { 1,2,3 };// ��Ļ��ʼ���������еĿ�Ԫ��Ϊ '0'�������� 

    for (int i = 0; i < 3; i++)
    {
        //cout << "cout<<a[i] = " << a[i] << endl;
        for (int j = 0; j < 2; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

}


//���Ժ���memccpy(����Ŀ���ַ������ֹͣ����)  �ƺ��������ڿ��ٵ�ʶ��һ���ַ��Ƿ����ַ�����
//���Ŀ���ַ�c û�б����ƣ��򷵻�NULL�����򣬷���Ŀ���ַ�c �������һ���ַ�λ�õ�ָ�롣
int testMemccpy(void)
{
    char *src = "This is the source string !";
    char dest[80];
    char *ptr;
    ptr = (char *)memccpy(dest, src, 'i', strlen(src));
    //ptr = (char *)memccpy(dest, src, '!', strlen(src));
    if (ptr)
    {
        *ptr = '\0';
        printf("The character was found: %s\n", dest);
    }
    else
        printf("The character wasn't found\n");
    return 0;
}


int main(void)
{
    NiuKeWangTestMain();

    return 0;
}