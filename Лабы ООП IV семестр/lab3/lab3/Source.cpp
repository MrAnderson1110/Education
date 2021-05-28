#include "Rectangle.h"
#include <iostream>

int main()
{
	Rectangle firtsRect(10, 10, 30, 11);
	Rectangle secRect(5, 0, 13, 4);

	std::cout << "first rectangle:\n"
		<< " width: " << firtsRect.width()
		<< " height: " << firtsRect.height()
		<< " area: " << firtsRect() << '\n';

	std::cout << "second rectangle:\n"
		<< " width: " << secRect.width()
		<< " height: " << secRect.height()
		<< " area: " << secRect() << '\n';

	std::cout << "is first rectangle bigger then second: "
		<< (firtsRect > secRect ? "Yes" : "No") << '\n';

	Rectangle intersectRect = firtsRect * secRect;
	std::cout << "intersection rectangle:\n"
		<< " width: " << intersectRect.width()
		<< " height: " << intersectRect.height()
		<< " area: " << intersectRect() << '\n';
}