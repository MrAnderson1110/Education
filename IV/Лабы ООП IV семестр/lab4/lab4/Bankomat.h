#pragma once

#include "Money.h"
class Bankomat : public Money
{
public:
	Bankomat();
	Bankomat(int d10, int d50, int d100, int d500, int d1000, int d5000);

	void deposit(int count, Money::banknoteDenomination banknoteType);
	void withdraw(int count);

private:
	bool checkBanknoteDenomination(Money::banknoteDenomination type);
};

