#include "Bankomat.h"
#include <iostream>

Bankomat::Bankomat()
	: Money()
{
}

Bankomat::Bankomat(int d10, int d50, int d100, int d500, int d1000, int d5000)
	: Money(d10, d50, d100, d500, d1000, d5000)
{

}

void Bankomat::deposit(int count, Money::banknoteDenomination banknoteType)
{
	if (count < 0) {
		std::cerr << "cannot depoosit negative money count\n";
		return;
	}
	else if (count % 10 != 0) {
		std::cerr << "it is not possible to withdraw an amount that is not a multiple of ten\n";
		return;
	}
	else if (count < 0) {
		std::cerr << "it is not possible to deposit negative amount\n";
		return;
	}
	else if (!checkBanknoteDenomination(banknoteType)) {
		std::cerr << "cannot recognise banknote denomination\n";
		return;
	}
	increeceCount(banknoteType, count);
}

void Bankomat::withdraw(int amount)
{
	if (summa() == 0) {
		std::cerr << "Bankomat is empty\n";
		return;
	}
	else if (amount % 10 != 0) {
		std::cerr << "it is not possible to withdraw an amount that is not a multiple of ten\n";
		return;
	}
	else if (amount < 0) {
		std::cerr << "it is not possible to withdraw negative amount\n";
		return;
	}
	int remains = amount;

	int d10 = 0;
	int d50 = 0;
	int d100 = 0;
	int d500 = 0;
	int d1000 = 0;
	int d5000 = 0;

	while (remains != 0) {
		if (Denomination_5000 <= remains && count(Denomination_5000) > 0) {
			int banknotesCount = remains / Denomination_5000;
			int remainsCount = decreeceCount(Denomination_5000, banknotesCount);
			d5000 = (banknotesCount - remainsCount) * Denomination_5000;
			remains -= (banknotesCount - remainsCount) * Denomination_5000;
		}
		else if (Denomination_1000 <= remains && count(Denomination_1000) > 0) {
			int banknotesCount = remains / Denomination_1000;
			int remainsCount = decreeceCount(Denomination_1000, banknotesCount);
			d1000 = (banknotesCount - remainsCount) * Denomination_1000;
			remains -= (banknotesCount - remainsCount) * Denomination_1000;
		}
		else if (Denomination_500 <= remains && count(Denomination_500) > 0) {
			int banknotesCount = remains / Denomination_500;
			int remainsCount = decreeceCount(Denomination_500, banknotesCount);
			d500 = (banknotesCount - remainsCount) * Denomination_500;
			remains -= (banknotesCount - remainsCount) * Denomination_500;
		}
		else if (Denomination_100 <= remains && count(Denomination_100) > 0) {
			int banknotesCount = remains / Denomination_100;
			int remainsCount = decreeceCount(Denomination_100, banknotesCount);
			d100 = (banknotesCount - remainsCount) * Denomination_100;
			remains -= (banknotesCount - remainsCount) * Denomination_100;
		}
		else if (Denomination_50 <= remains && count(Denomination_50) > 0) {
			int banknotesCount = remains / Denomination_50;
			int remainsCount = decreeceCount(Denomination_50, banknotesCount);
			d50 = (banknotesCount - remainsCount) * Denomination_50;
			remains -= (banknotesCount - remainsCount) * Denomination_50;
		}
		else if (Denomination_10 <= remains && count(Denomination_10) > 0) {
			int banknotesCount = remains / Denomination_10;
			int remainsCount = decreeceCount(Denomination_10, banknotesCount);
			d10 = (banknotesCount - remainsCount) * Denomination_10;
			remains -= (banknotesCount - remainsCount) * Denomination_10;
		}
		else break;
	}

	std::cout << "withdraw:\n"
		<< d10 << " banknotes denomination of 10\n"
		<< d50 << " banknotes denomination of 50\n"
		<< d100 << " banknotes denomination of 100\n"
		<< d500 << " banknotes denomination of 500\n"
		<< d1000 << " banknotes denomination of 1000\n"
		<< d5000 << " banknotes denomination of 5000\n"
		<< remains << " did not withdraw\n\n";
}

bool Bankomat::checkBanknoteDenomination(Money::banknoteDenomination type)
{
	return type == Denomination_10
		|| type == Denomination_50
		|| type == Denomination_100
		|| type == Denomination_500
		|| type == Denomination_1000
		|| type == Denomination_5000;
}
