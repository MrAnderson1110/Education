#pragma once
#include <vector>
#include <iostream>

class MyClass
{
	friend std::ostream& operator<<(std::ostream& os, const MyClass& cl);
public:
	MyClass();

	void fillRand();
	int findMax();
	void replace();
	void removeRepeats();

private:
	std::vector<int> m_vec;
	const int m_m1;
	const int m_m2;
};

