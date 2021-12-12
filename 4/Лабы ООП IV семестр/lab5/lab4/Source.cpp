#include <iostream>
#include "Array.h"

int main()
{
	int com = -1;
	while (com != 0) {
		std::cout << "\nenter command: ";
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
			std::cout << "with no exception in constructor\n";
			Array a = { rand() % 100, -rand() % 100, rand() % 100, -rand() % 100, -rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, -rand() % 100, rand() % 100, rand() % 100 };
			std::cout << "array: " << a << '\n';
			int min = 0, max = 0;
			std::cout << "enter range for multiply: ";
			std::cin >> min >> max;
			std::cout << "multiply: " << a.multRange(min, max) << '\n';
			std::cout << "summ: " << a.negativeSum() << '\n';
			break;
		}
		case 2: {
			std::cout << "with exception in constructor\n";
			Array a = { rand() % 100, -rand() % 100, rand() % 100, -rand() % 100, -rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, -rand() % 100, rand() % 100, rand() % 100, rand() % 100 };
			std::cout << "array: " << a << '\n';
			int min = 0, max = 0;
			std::cout << "enter range for multiply: ";
			std::cin >> min >> max;
			std::cout << "multiply: " << a.multRange(min, max) << '\n';
			std::cout << "summ: " << a.negativeSum() << '\n';
			break;
		}
		case 0:
		default:
			break;
		}
	}
	return 0;
}