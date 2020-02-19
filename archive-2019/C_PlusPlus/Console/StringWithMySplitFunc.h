#ifndef __STRING_WITH_MY_SPLIT_H__
#define __STRING_WITH_MY_SPLIT_H__

#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma warning(disable: 4996) //strdup strtok

#include "iconv.h" //This file is part of the GNU LIBICONV Library, but not the STD lib of C

using namespace std;

//�ַ�����ת����
class EncodeConvert
{ 
public:
	int code_convert(char *from_charset, char *to_charset, char *inbuf, size_t inlen, char *outbuf, size_t outlen)
	{
		iconv_t cd;
		//int rc;
		char **pin = &inbuf;
		char **pout = &outbuf;

		cd = iconv_open(to_charset, from_charset);
		if (cd == 0) return -1;
		memset(outbuf, 0, outlen);
		if (iconv(cd, pin, &inlen, pout, &outlen) == -1) return -1;
		iconv_close(cd);
		return 0;
	}

	//UNICODE��תΪGB2312��
	int u2g(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
	{
		return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
	}
	//GB2312��תΪUNICODE��
	int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
	{
		//return code_convert("gb2312","utf-8",inbuf,inlen,outbuf,outlen);
		return code_convert("gb18030", "utf-8", inbuf, inlen, outbuf, outlen);
	}
};



class StringWithMySplit : public EncodeConvert
{
public:
	StringWithMySplit()
	{
		m_str = "�||�����㺺�ֺú��ְ�|123|�|���֏|�||abc";
	}

	StringWithMySplit(char* str)
	{
		m_str = str;
	};

	void MysplitString(const char cDelimiter)
	{
		vector<string> vecResult;
		int count = MysplitString(cDelimiter, vecResult);
		for (int i = 0; i < count; i++)
		{
			cout << vecResult[i] << endl;
		}
	}

	int MysplitString(const char cDelimiter, vector<string> & vecResult)
	{
		vecResult.clear();

		const char* src = m_str;

		int i = 0;
		if (*src)
		{
			string temp = "";
			while (*src)
			{
				if (*src != cDelimiter)
				{
					unsigned char p = *src;
					if ((p >> 7) == 1)//���ֱ��������������ֽڣ����ֵĵڶ����ֽ���ʼλ �̶� Ϊ 1, �硾00001111 11110000������ͨ�ַ���һ���ֽڣ��硾01010101��
					{
						temp += *src;
						src++;
						temp += *src;
					}
					else
					{
						temp += *src;
					}
				}
				else
				{
					vecResult.push_back(temp);
					temp = "";
				}
				src++;
			}
			vecResult.push_back(temp);
		}
		return vecResult.size();
	}

	char* m_str;

};




//��splite�����޷�����һ���������, �ַ���Ϊ "�||��ð�|123|�|�|�||abc" ���� "|" Ϊ�ָ���ʱ �����ԭ���� ���� "�|" ��ָ��� "|" ����ͬ��ACSII��
//C++��string �� find�Լ�C ���Ա���� strtok�������޷����������������
int strsplit(const char *str, char *parts[], const char *delimiter)
{
    char *pch;
    int i = 0;
    char *copy = NULL, *tmp = NULL;
    copy = strdup(str);

    if (!copy)
    {
        goto bad;
    }

    pch = strtok(copy, delimiter);
    tmp = strdup(pch);

    if (!tmp)
    {
        goto bad;
    }

    parts[i++] = tmp;

    while (pch)
    {
        pch = strtok(NULL, delimiter);

        if (NULL == pch) { break; }

        tmp = strdup(pch);

        if (!tmp)
        {
            goto bad;
        }

        parts[i++] = tmp;
    }

    free(copy);
    return i;
bad:
    free(copy);

    for (int j = 0; j < i; j++)
    {
        free(parts[j]);
    }

    return -1;
}
//����splite������ �ܹ����պ���Ϊ�ָ������зָ�����ֲ��˺��� "�|" ��ָ��� "|"
void test004()
{
    char str[] = "123�|�����|abc�|";//"�||��ð�|123|�|�|�||abc"
    char *parts[8];
    size_t size = strsplit(str, parts, "�|"); //"|"
    unsigned int i = 0;

    for (; i < size; ++i)
    {
        printf("%s\n", parts[i]);
    }

    return;
}


#endif // !__STRING_WITH_MY_SPLIT_H__
