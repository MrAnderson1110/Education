#pragma once
#include <map>

class Money
{
public:
	enum banknoteDenomination
	{
		Undefined = 0,
		Denomination_10 = 10,
		Denomination_50 = 50,
		Denomination_100 = 100,
		Denomination_500 = 500,
		Denomination_1000 = 1000,
		Denomination_5000 = 5000,
	};

	Money();
	Money(int d10, int d50, int d100, int d500, int d1000, int d5000);

	int summa();

protected:
	int count(banknoteDenomination type);
	void increeceCount(banknoteDenomination type, int delta);
	int decreeceCount(banknoteDenomination type, int delta);

private:
	std::map<banknoteDenomination, int> m_banknoteCount;
};

