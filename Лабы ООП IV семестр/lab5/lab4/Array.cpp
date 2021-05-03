#include "Array.h"
#include "Out_of_range.h"

Array::Array(std::initializer_list<int> li)
	: m_arr()
	, m_arrSize(12)
{
	try {
		if (li.size() > static_cast<unsigned>(m_arrSize))
			throw Out_of_range("cannot initialize array. Out of range. Everything is 0\n");

		for (size_t i = 0; i < li.size(); ++i)
			m_arr[i] = *(li.begin() + i);

        sort();
	}
	catch (Out_of_range err) {
		std::cerr << err.what();
	}
}

int Array::negativeSum() const
{
	int sum = 0;
	for (int i = 0; i < m_arrSize; ++i)
		if (m_arr[i] < 0)
			sum += m_arr[i];
	return sum;
}

int Array::multRange(int min, int max) const
{
	int mult = 0;
	try {
		if (min < 0)
			throw Out_of_range("min limit out of range\n");
		else if (max > m_arrSize)
			throw Out_of_range("max limit out of range\n");
		else if (min > max)
			throw Out_of_range("min limit cannot be less than max\n");

		mult = 1;
		for (int i = min; i < max; ++i)
			mult *= m_arr[i];
	}
	catch (Out_of_range err) {
		std::cerr << err.what();
	}
	return mult;
}

inline void Array::sort()
{
    //���������� ������������ � ���������
    int swapNum = 0;
    int compNum = 0;
    //����� �� ��������� ���������� �� ������ � 
    //�������� ������� ��������������
    bool evenSwap = false;
    bool oddSwap = false;
    //��������� �������� ������ �������� ������� �����������,
    //�� ��-�� ����������� ��� ������ ����� �� ���
    while (!(evenSwap & oddSwap)) {
        //� ����� ���� ������� �������� ���������
        ++compNum;
        //�� ������ �������� ����� ������ ���� true
        //���� �� ������ �������� ��� ��� ����� ����� ����� ����� ������������
        //����������� ��������������� ���� � �������� ���������� ������
        evenSwap = true;
        oddSwap = true;
        //�������� �����
        for (int i = 0; i + 1 < m_arrSize; i += 2) {
            if (m_arr[i] > m_arr[i + 1]) {
                //��� ��������� ����� ��������
                ++compNum;
                int temp = m_arr[i];
                m_arr[i] = m_arr[i + 1];
                m_arr[i + 1] = temp;
                //� ���� �����
                ++swapNum;
                oddSwap = false;
            }
        }
        //������ ����� (��� ���� �����, ��� � ��� ���������, ����� �����)
        for (int i = 1; i + 1 < m_arrSize; i += 2) {
            if (m_arr[i] > m_arr[i + 1]) {
                ++compNum;
                int temp = m_arr[i];
                m_arr[i] = m_arr[i + 1];
                m_arr[i + 1] = temp;
                ++swapNum;
                evenSwap = false;
            }
        }
    }
}

std::ostream& operator<< (std::ostream& os, const Array& arr)
{
	for (int i = 0; i < arr.m_arrSize; ++i)
		os << arr.m_arr[i] << ' ';
	return os;
}
