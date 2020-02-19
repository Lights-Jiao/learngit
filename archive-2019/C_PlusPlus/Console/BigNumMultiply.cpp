#include "BigNumMultiply.h"

void CBigNumMultiply::CharToNum()
{
    unsigned int size_a = m_sA.size();
    unsigned int size_b = m_sB.size();

    for (unsigned int i = 0; i < size_a; i++)
    {
        m_vecA.push_back(m_sA[i] - '0');
    }

    for (unsigned int i = 0; i < size_b; i++)
    {
        m_vecB.push_back(m_sB[i] - '0');
    }
}


void CBigNumMultiply::Multiply()
{
    //��ʼ�� result Vector, �Ƿ��и��õ�д����
    for (unsigned int i = 0; i < m_vecA.size() + m_vecB.size(); i++)
    {
        //m_vecResult[i] = 0;
        m_vecResult.push_back(0);
    }

    //�����Ĳ����ʽ ����
    for (unsigned int i = 0; i < m_vecA.size(); i ++)
    {
        for (unsigned int j = 0; j < m_vecB.size(); j++)
        {
            m_vecResult[i + j] += m_vecA[i] * m_vecB[j];
        }
    }

    //TODO �������� 0 , ��������Ϊ������Ҫ��������0 �����Կ�����Ҫ�����鷭ת�洢 ʹ�� pop_backȥ������� 0
    
    //�����λ
    int c = 0;
    for ( int i = m_vecResult.size() - 1; i >= 0; i--)
    {
        /* �Ժ��еĵ�һ��Ӧд����̫���
        int num = m_vecResult[i] / 10;
        m_vecResult[i] = m_vecResult[i] % 10;
        m_vecResult[i - 1] += num;
        */

        m_vecResult[i] += c;
        c = m_vecResult[i] / 10;
        m_vecResult[i] = m_vecResult[i] % 10; //���ǽ�λ�����⣨999*999���� ����Ҳ��Ҫ��ת�洢
    }
}


void CBigNumMultiply::NumToChar()
{
    for (unsigned int i = 0; i < m_vecResult.size();i++)
    {
        m_sResult.push_back('0' + m_vecResult[i]);
    }
}


string& CBigNumMultiply::GetResult()
{
    CharToNum();
    Multiply();
    NumToChar();

    return m_sResult;
};


void BigNumMultiplyMain()
{
    CBigNumMultiply test(string("999"), string("999"));// 999 * 999�Ľ����ʧ��һλ��λ�����ø��ˡ�����˯��

    cout << test.GetResult() << endl;

    return;
}