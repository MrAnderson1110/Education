#include <iostream>
#include "Bankomat.h"
#include "Money.h"

int main()
{
	Bankomat b(100, 424, 592, 103, 324, 104);

	int com = -1;
	while (com != 0)
	{
		std::cout << "\nbankomain contanis " << b.summa() << " money\n";
		std::cout << "enter command: ";
		std::cin >> com;
		if (!std::cin) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			std::cout << "try again: ";
			std::cin >> com;
		}

		switch (com)
		{
		case 1: {
			int count, banknote = 0;
			std::cout << "bankomat deposit: ";
			std::cin >> count >> banknote;
			b.deposit(count, static_cast<Money::banknoteDenomination>(banknote));
			break;
		}
		case 2: {
			int count = 0;
			std::cout << "bankomat withdraw: ";
			std::cin >> count;
			b.withdraw(count);
			break;
		}
		case 0:
		default:
			break;
		}
	}
	return 0;
}