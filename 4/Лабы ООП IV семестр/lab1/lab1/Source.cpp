#include "equationsolution.h"

#include <iostream>
#include <sstream>

void getUserInput(double& val);

int main()
{
	EquationSolution es;

	double b = 0.0, k = 0.0, y = 0.0;
	std::cout << "b: ";
	getUserInput(b);
	es.setB(b);
	std::cout << "k: ";
	getUserInput(k);
	es.setK(k);
	std::cout << "y: ";
	getUserInput(y);
	
	std::stringstream sstr;
	sstr << "Solution of equation [ x * " << k << " + " << b << " = " << y << " ] is: ";

	double x = es.Root(y);
	if (x == INFINITY)
		sstr << "any";
	else
		sstr << x;

	std::cout << sstr.str();

	return 0;
}

void getUserInput(double& var)
{
	std::cin >> var;
	while (!std::cin) {
		std::cout << "incorrect input. re-enter the variable: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> var;
	}
}