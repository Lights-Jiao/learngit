#ifndef __TEST_RESERVS_RESIZE_H__
#define __TEST_RESERVS_RESIZE_H__
#pragma once  

#include <stdio.h>
#include <iostream>  
#include <vector>  
#include <string>  

using namespace std;

class testReserve_Resize
{
public:
	int m_a;

public:
	testReserve_Resize() :m_a(0)
	{}

	testReserve_Resize(int a) :m_a(a)
	{}

	testReserve_Resize(const testReserve_Resize& A) :m_a(A.m_a)
	{}
};

extern int test_Reserve_Resize_Main();

#endif


//��һ�� ̽��Ч�ʵ�˵��
// ���ߣ�Milo Yip
// ���ӣ�https ://zhuanlan.zhihu.com/p/22399604
// ��Դ��֪��
// ����Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
// 
// �����ܷ����󣬷������������һ�д��룺
// 
// // json.cpp
// void escapeString(
// 	StringPiece input,
// 	std::string& out,
// 	const serialization_opts& opts) {
// 	auto hexDigit = [](int c) -> char {
// 		return c < 10 ? c + '0' : c - 10 + 'a';
// 	};
// 
// 	out.reserve(out.size() + input.size() + 2); // <-- ��һ��
// 	out.push_back('\"');
// 	// ...
/****************************************************************************/
// 	����ԭ�������壬Ӧ����ϣ��Ԥ�����ַ�����������壬�����������Ҫ���·��䡣
//  ����һ���ʵ���У�std::string::reserve() �ڿռ䲻��ʱ����ѻ�������Ϊָ���Ĵ�С��
//  ����ÿ�εķ��䶼�Ǹպù��ö��ѣ��´�������ַ����ͱػ������·��䣬��� O(n^2) ������ƿ����
//  �����ֻ���� std::string::push_back()���������¿ռ��Ϊ���д�С����������������������������̯ O(n) ��ʱ�临�Ӷȡ�
//  ���ԣ�����ʵ�飬ֻҪɾȥ���У����ܴﵽ���������ܣ�
/****************************************************************************/