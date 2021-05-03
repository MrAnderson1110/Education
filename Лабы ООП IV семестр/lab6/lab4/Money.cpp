#include "Money.h"
#include <cmath>

Money::Money() 
	: m_banknoteCount()
{
	m_banknoteCount[Denomination_10] = 0;
	m_banknoteCount[Denomination_50] = 0;
	m_banknoteCount[Denomination_100] = 0;
	m_banknoteCount[Denomination_500] = 0;
	m_banknoteCount[Denomination_1000] = 0;
	m_banknoteCount[Denomination_5000] = 0;
}

Money::Money(int d10, int d50, int d100, int d500, int d1000, int d5000)
	: m_banknoteCount()
{
	m_banknoteCount[Denomination_10] = d10;
	m_banknoteCount[Denomination_50] = d50;
	m_banknoteCount[Denomination_100] = d100;
	m_banknoteCount[Denomination_500] = d500;
	m_banknoteCount[Denomination_1000] = d1000;
	m_banknoteCount[Denomination_5000] = d5000;
}

int Money::summa()
{
	int summ = 0;
	for (auto banknotesPair : m_banknoteCount)
		summ += banknotesPair.first * banknotesPair.second;
	return summ;
}

int Money::count(banknoteDenomination type)
{
	return m_banknoteCount[type];
}

void Money::increeceCount(banknoteDenomination type, int delta)
{
	m_banknoteCount[type] += delta;
}

int Money::decreeceCount(banknoteDenomination type, int delta)
{
	m_banknoteCount[type] -= delta;
	if (m_banknoteCount[type] < 0) {
		int remains = std::abs(m_banknoteCount[type]);
		m_banknoteCount[type] = 0;
		return remains;
	}
	return 0;
}
