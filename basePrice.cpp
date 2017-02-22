#include "stdafx.h"
#include <iostream>
#include  <sstream>
#include "subwayMacro.h"
#include "include/basePrice.h"
using namespace std;

/*
@ 获取基础票价, 即按进站点与出站点之间的最短里程分级计算
@ -1, 查询基础票价失败; 其他, 基础票价
*/
int GetBasePrice(unsigned int meters)
{
	//基本票价计算规则：按进站点与出站点之间的最短里程分级计算
	//若进出站相同，则基础票价为0.
	if (0 == meters)
		return 0;
	//	3千米（包含3千米，但不包括0）以内：2元。
	if (3 >= meters && 0 < meters)
		return 2;
	//	3千米 至 5千米（包含5千米）：3元。
	if (5 >= meters && 3 < meters)
		return 3;
	//	5千米 至 10千米（包含10千米）：4元。
	if (10 >= meters && 5 < meters)
		return 4;
	//	10千米以上：5元。
	if (10 < meters)
		return 5;

    return -1;
}