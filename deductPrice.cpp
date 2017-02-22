#include "stdafx.h"
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "include/basePrice.h"
#include "include/deductPrice.h"
#include "subwayPrice.h"
#include <iostream>
using namespace std;

#define PRICEGATE 3
/*
@ ��ȡ�۷�Ʊ�ۣ��������;
@   1. �����Ϊ0����ʱ���շ�;
@   2. �������Ϊ0;
@ ����ֵ: 
*/

//����վΪͬһվ��������
EN_RETURN_CODE EnterEqualExit(int basePrice,EN_CARD_TYPE enCardType, unsigned int balance, unsigned int meters, ST_SUBWAY_TIME &enterTime, ST_SUBWAY_TIME &exitTime, unsigned int &deductPrice)
{
	if (0 != meters)
		return EN_RETURN_SUCC;	//��������������������账��

	if (!CHECK_TIME(&enterTime) || !CHECK_TIME(&exitTime))	//У��ʱ���ʽ
		return EN_RETURN_INVALID_TIME;

	int diffMinutes = 0;
	DIFF_TIME(&exitTime, &enterTime, diffMinutes);	//����ʱ���
	if (diffMinutes < 0)   //�˳��۷������С���վʱ�䡱���ڡ���վʱ�䡱��
		return EN_RETURN_INVALID_TIME;
	//��С�ڵ���30���ӣ�Ʊ����ֵ��Ϊ�۷�Ʊ�ۣ�
	if (diffMinutes <= 30)
		deductPrice = basePrice;
	else
		deductPrice = MaxValue(basePrice, PRICEGATE);  //����Ʊ����Ʊ����ֵ��3Ԫ���С����ֵ����Ϊ�۷�Ʊ�ۣ�
	return EN_RETURN_SUCC;
}
EN_RETURN_CODE GetDeductPrice(EN_CARD_TYPE enCardType, unsigned int balance, unsigned int meters, ST_SUBWAY_TIME &enterTime, ST_SUBWAY_TIME &exitTime, unsigned int &deductPrice)
{
	//���ȼ������Ʊ��
	int basePrice=GetBasePrice(meters);
	if (-1 != basePrice)	//�������
	{
		deductPrice = basePrice;
		return EN_RETURN_SUCC;
	}

	//����վΪͬһվ������
	EnterEqualExit(basePrice,enCardType,balance, meters, enterTime, exitTime, deductPrice);

    return EN_RETURN_SUCC;
}

