#pragma once
#include <initializer_list>
#include <iostream>

class Array
{
	friend std::ostream& operator<< (std::ostream& os, const Array& arr);
public:
	Array(std::initializer_list<int> li);

	int negativeSum() const;
	int multRange(int min, int max) const;

private:
	void sort();

private:
	int m_arr[12];
	int m_arrSize;
};

