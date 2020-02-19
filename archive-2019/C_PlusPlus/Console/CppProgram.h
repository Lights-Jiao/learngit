
#ifndef __CPP_PROGRAM_H__
#define __CPP_PROGRAM_H__

#include <stdio.h>
#include <assert.h>
#include <iostream>  
#include <vector>  
#include <string>  

using namespace std;

unsigned int mystrlen(const char* s)
{
    unsigned int len = 0;
    for (; *s != '\0'; s++)
    {
        len++;
    }
    return len;
}

//��C++���������ָ�ϡ��е�strcpy
char* mystrcpy(char* strDest, const char* strSrc)
{
    //���Ե��жϻ��Ǻ���Ҫ��
    assert((NULL != strSrc) && (NULL != strDest));
    
    char* address = strDest;
    while ((*address++ = *strSrc++) != '\0')
    {
        NULL;
    }

    /* ���Լ�д�ĸ��Ʒ��� ���ƶ��ˣ�����return �ĵ�ַ���ԣ� ����Ҳ�������
    for (; *strSrc != '\0'; strSrc++)
    {
        *strDest = *strSrc;
        strDest++;
    }
    strDest++;
    *strDest = '\0';
    */

    return strDest; // �˴�����char* ���� ��Ϊ��ʵ����ʽ�� ���� int length = strlen(strcpy(strDest, "hello world!"));
}

void testMyStrcpy()
{
    char* p = "hello world!";
    char* p2 = (char*)malloc(20);

    mystrcpy(p2, p);

    cout << p << endl << p2 << endl;
}



//��д��String�Ĺ��캯������������ �� ��ֵ����
class MyString
{
public:
    MyString(const char* str = NULL); 
    MyString(const MyString& mystringSrc);
    ~MyString(void);

    MyString& operator=(const MyString& mystringSrc);

private:
    char* m_sData;
    unsigned int m_nCapcity;
    unsigned int m_nSize;
};

//���캯����ʱ�� һ���Է��������� �ڴ��ַ�ռ䣬����Ҫ һ��һ��increase�����ǲ���ɵ��
MyString::MyString(const char* str)
{
    //�˴���NULLָ���ж��Ƿ��б�Ҫ����Ϊ��׼�� string���� ��NULLָ��Ĺ���ᱨ��
    if (NULL == str)
    {
        m_sData = (char*)malloc(1);
        *m_sData = '\0';
    }
    else
    {
        m_nSize = mystrlen(str);
        m_nCapcity = m_nSize + 1;

        m_sData = (char*)malloc(m_nCapcity); // new char[m_nCapcity]
        mystrcpy(m_sData, str);
    }
}

MyString::MyString(const MyString& mystringSrc)
{
    m_nSize = mystringSrc.m_nSize;
    m_nCapcity = m_nSize + 1;

    m_sData = (char*)malloc(m_nCapcity);
    mystrcpy(m_sData, mystringSrc.m_sData); //������һ�����ʣ�Ϊ�ο��Է��ʵ� mystring ��˽�г�Ա �������С�����˽�С� ������ʵ����أ������������� ������

}

MyString::~MyString(void)
{
    m_nCapcity = 0;
    m_nSize = 0;
    free(m_sData);
    m_sData = NULL;
}

MyString& MyString::operator =(const MyString& mystringSrc)
{
    //*��Ҫ* ����Ը�ֵ
    if (this == &mystringSrc)
    {
        return *this;
    }

    free(m_sData);
    m_nSize = mystringSrc.m_nSize;
    m_nCapcity = m_nSize + 1;

    m_sData = (char*)malloc(m_nCapcity);

    mystrcpy(m_sData, mystringSrc.m_sData);

    return *this;   // Ϊʲô���� ��return this������ ���ص��Ǳ����������
}


#endif
