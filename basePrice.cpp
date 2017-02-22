#include "stdafx.h"
#include <iostream>
#include  <sstream>
#include "subwayMacro.h"
#include "include/basePrice.h"
using namespace std;

/*
@ ��ȡ����Ʊ��, ������վ�����վ��֮��������̷ּ�����
@ -1, ��ѯ����Ʊ��ʧ��; ����, ����Ʊ��
*/
int GetBasePrice(unsigned int meters)
{
	//����Ʊ�ۼ�����򣺰���վ�����վ��֮��������̷ּ�����
	//������վ��ͬ�������Ʊ��Ϊ0.
	if (0 == meters)
		return 0;
	//	3ǧ�ף�����3ǧ�ף���������0�����ڣ�2Ԫ��
	if (3 >= meters && 0 < meters)
		return 2;
	//	3ǧ�� �� 5ǧ�ף�����5ǧ�ף���3Ԫ��
	if (5 >= meters && 3 < meters)
		return 3;
	//	5ǧ�� �� 10ǧ�ף�����10ǧ�ף���4Ԫ��
	if (10 >= meters && 5 < meters)
		return 4;
	//	10ǧ�����ϣ�5Ԫ��
	if (10 < meters)
		return 5;

    return -1;
}