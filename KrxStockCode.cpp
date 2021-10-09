// KrxStockCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include <map>
#include "StockCode.h"

using namespace std;

char* Byte2Bin(uint8_t ch)
{
	static char s[8 + 1] = { '0', };
	int count = 8;
	do {
		s[--count] = '0' + (char)(ch & 1);
		ch = ch >> 1;
	} while (count);
	return s;
}

std::string ToHex(uint8_t value)
{
	char szTemp[5] = { 0 };
	sprintf_s(szTemp, _countof(szTemp), "0x%02X", value);
	return szTemp;
}

int main()
{
	StockCode sc1(L"075130", 0x01);
	StockCode sc2("005930", 0x00);
	StockCode sc3(L"Q500054", 0x20);
	StockCode sc4("J08280218", 0xFF);
	map<uint64_t, string> mapStockName;
	mapStockName[sc1] = "플랜티넷";
	mapStockName[sc2] = "삼성전자";
	mapStockName[sc3] = "신한 인버스 2X 천연가스 선물 ETN";
	mapStockName[sc4] = "비보존 헬스케어 5WR";

	assert(sc1 == "075130" && "stock code mismatch!");
	assert(sc2 == L"005930" && "stock code mismatch!");
	assert(sc3 == "Q500054" && "stock code mismatch!");
	assert(sc4 == L"J08280218" && "stock code mismatch!");

	cout << "sc1 = " << sc1.code << " " << mapStockName[sc1] << ", flag = " << ToHex(sc1.flag) << endl;
	cout << "sc2 = " << sc2.code << " " << mapStockName[sc2] << ", flag = " << ToHex(sc2.flag) << endl;
	cout << "sc3 = " << sc3.code << " " << mapStockName[sc3] << ", flag = " << ToHex(sc3.flag) << endl;
	cout << "sc4 = " << sc4.code << " " << mapStockName[sc4] << ", flag = " << ToHex(sc4.flag) << endl;
	cout << endl;

	cout << "sizeof(StockCode) = " << sizeof(sc1) << endl;
	wcout << L"sc2 = " << sc2.wcode << L" length = " << sc2.length << endl;
	cout << "sc3 = ";
	int i, len = sc3.length;
	for (i = 0; i < len; i++)
		cout << sc3[i];
	cout << " length = " << len << endl;
	cout << "sc4 = ";
	len = sc4.length;
	for (i = 0; i < len; i++)
		cout << sc4[i];
	cout << " length = " << len << endl;
	cout << endl;

	uint32_t code32 = sc1;
	for (i = 0; i < sizeof(code32); i++) {
		uint8_t ch = ((uint8_t*)&code32)[i];
		printf("%s ", Byte2Bin(ch));
	}
	cout << endl;
	StockCode sc5(code32);
	cout << "sc5 = " << sc5.code << " " << mapStockName[sc5] << ", flag = " << ToHex(sc5.flag) << endl;

	return 0;
}
