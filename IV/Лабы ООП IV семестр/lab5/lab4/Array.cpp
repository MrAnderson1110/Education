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
    //Количество перестановок и сравнений
    int swapNum = 0;
    int compNum = 0;
    //Флаги об окончании сортировки на четных и 
    //нечетных обходах соответственно
    bool evenSwap = false;
    bool oddSwap = false;
    //Побитовый оператор должен работать быстрее логического,
    //но из-за компилятора это скорее всего не так
    while (!(evenSwap & oddSwap)) {
        //В цикле тоже имеется операция сравнения
        ++compNum;
        //На каждой итерации флаги должны быть true
        //Если на данной итерации чет или нечет обход будет иметь перестановку
        //Поднимается соответствующий флаг и алгоритм продолжает работу
        evenSwap = true;
        oddSwap = true;
        //Нечетный обход
        for (int i = 0; i + 1 < m_arrSize; i += 2) {
            if (m_arr[i] > m_arr[i + 1]) {
                //Уже сравнение самих значений
                ++compNum;
                int temp = m_arr[i];
                m_arr[i] = m_arr[i + 1];
                m_arr[i + 1] = temp;
                //И один обмен
                ++swapNum;
                oddSwap = false;
            }
        }
        //Четный обход (все тоже самое, что и для нечетного, кроме флага)
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
