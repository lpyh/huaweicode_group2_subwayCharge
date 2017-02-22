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
@ 获取扣费票价，几种情况;
@   1. 里程数为0，按时间收费;
@   2. 里程数不为0;
@ 返回值: 
*/

//进出站为同一站点的情况：
EN_RETURN_CODE EnterEqualExit(int basePrice,EN_CARD_TYPE enCardType, unsigned int balance, unsigned int meters, ST_SUBWAY_TIME &enterTime, ST_SUBWAY_TIME &exitTime, unsigned int &deductPrice)
{
	if (0 != meters)
		return EN_RETURN_SUCC;	//若不属于这种情况，不予处理。

	if (!CHECK_TIME(&enterTime) || !CHECK_TIME(&exitTime))	//校验时间格式
		return EN_RETURN_INVALID_TIME;

	int diffMinutes = 0;
	DIFF_TIME(&exitTime, &enterTime, diffMinutes);	//计算时间差
	if (diffMinutes < 0)   //乘车扣费命令中“进站时间”大于“出站时间”。
		return EN_RETURN_INVALID_TIME;
	//若小于等于30分钟，票卡面值作为扣费票价；
	if (diffMinutes <= 30)
		deductPrice = basePrice;
	else
		deductPrice = MaxValue(basePrice, PRICEGATE);  //单程票：（票卡面值，3元）中“最大值”作为扣费票价；
	return EN_RETURN_SUCC;
}
EN_RETURN_CODE GetDeductPrice(EN_CARD_TYPE enCardType, unsigned int balance, unsigned int meters, ST_SUBWAY_TIME &enterTime, ST_SUBWAY_TIME &exitTime, unsigned int &deductPrice)
{
	//首先计算基础票价
	int basePrice=GetBasePrice(meters);
	if (-1 != basePrice)	//正常情况
	{
		deductPrice = basePrice;
		return EN_RETURN_SUCC;
	}

	//进出站为同一站点的情况
	EnterEqualExit(basePrice,enCardType,balance, meters, enterTime, exitTime, deductPrice);

    return EN_RETURN_SUCC;
}

