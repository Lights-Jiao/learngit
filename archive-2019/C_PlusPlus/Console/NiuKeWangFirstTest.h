#ifndef __NIUKEWANG_FIRST_TEST_H__
#define __NIUKEWANG_FIRST_TEST_H__

#include <stdio.h>
#include <stdlib.h> //rand srand
#include <time.h>
#include <iostream>
#include <ostream>
#include <iterator>//ostream_iterator

using namespace std;

//�� 0...n-1 ������ȸ��ʵ����m �����ظ��������������Ǽ��� n Զ���� m
void knuth(int n, int m)
{
    srand((unsigned int)time(0)); //srand(time(NULL))
    for (int i = 0; i < n; i++)
    {
        if (rand() % (n - i) < m)
        {
            cout << i << endl;
            m--;
        }
    }

    return;
}


//�ֽ������������Ϊ��Ҫ�ֽ�����ֺ͸����ֵ���С������(12�� 2)
void prim(int m, int n)
{
    if (m >= n)
    {
        while (m % n) n++;
        m /= n;
        prim(m, n);
        cout << n << endl;
    }

    return;
}


//����д����ȫ�ֱ���ö��ʱ��x�ᱻ��ʼ��Ϊ 0,�ھֲ�����ö��ʱ�������ֵ
enum abc
{
    x1 = 3,
    x2, // = 4
    x3 = 1,
    x4, // = 2
    x5, // = 3
} x;


//���� ���ࡢ���� ���麯������̬����ص�һЩ����
class A
{
public:
    void FuncA()
    {
        printf("FuncA called\n");
    }
    virtual void FuncB()
    {
        printf("FuncB called\n");
    }
};
class B : public A
{
public:
    void FuncA()
    {
        A::FuncA();
        printf("FuncAB called\n");
    }
    virtual void FuncB()
    {
        printf("FuncBB called\n");
    }
};
int TestClassMain(void)
{
    B  b;
    A  *pa;
    pa = &b;
    A *pa2 = new A;
    pa->FuncA();    //pa=&b��̬�󶨵���FuncA�����麯��������FuncA called
    pa->FuncB();    //FuncB���麯�����Ե���B��FuncB��FuncBB called  
    pa2->FuncA();   //pa2��A��ָ�룬���漰�麯�������õĶ���A�к���������FuncA called FuncB called
    pa2->FuncB();
    delete pa2;
    return 0;
}

//�������Ե���������  ��������
int FindSubString(char* pch)
{
    int   count = 0;
    char  * p1 = pch;
    while (*p1 != '\0')
    {
        if (*p1 == p1[1] - 1)
        {
            p1++;
            count++;
        }
        else {
            break;
        }
    }
    int count2 = count;
    while (*p1 != '\0')
    {
        if (*p1 == p1[1] + 1)
        {
            p1++;
            count2--;
        }
        else {
            break;
        }
    }
    if (count2 == 0)
        return(count);
    return(0);
}
void ModifyString(char* pText)
{
    char  * p1 = pText;
    char  * p2 = p1;
    while (*p1 != '\0')
    {
        int count = FindSubString(p1);
        if (count > 0)
        {
            *p2++ = *p1;
            sprintf(p2, "%i", count);
            while (*p2 != '\0')
            {
                p2++;
            }
            p1 += count + count + 1;
        }
        else {
            *p2++ = *p1++;
        }
    }
}
void TestModifyStringMain(void)
{
    char text[32] = "XYBCDCBABABA";
    ModifyString(text);
    printf(text);
}


//�������Ĺ�������������ȫ����
//����copy��swap ����std �ĺ����� ostream_iterator<T>out(os, d),out��һ������������������ΪT��ֵд�������os�У�����ÿ��ֵ���涼���һ��d(premier p359)
void perm(int list[], int k, int m)
{
    if (k == m)
    {
        copy(list, list + m, ostream_iterator<int>(cout, " ")); // ostream_iterator #include<iterator>
        cout << endl;
        return;
    }
    for (int i = k; i < m; i++)
    {
        swap(list[k], list[i]);
        perm(list, k + 1, m);
        swap(list[k], list[i]);
    }
}
void TestPermMain()
{
    int a[] = { 1, 2, 3, 4 };
    perm(a, 0, 4);
}

int NiuKeWangTestMain()
{
    //TestModifyStringMain();
    TestPermMain();

    return 0;
}

#endif