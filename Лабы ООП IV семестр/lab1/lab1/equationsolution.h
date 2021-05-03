#pragma once

/* 
* Вариант 1
* Класс для решения линейного уравнения у=kx+b. Коэффициенты уравнения k, b 
* реализовать с помощью полей вещественного типа. Для решения уравнения
* предусмотреть метод Root. 
*/


class EquationSolution
{
public:
	double Root(double y) const;

	//getters
	double k() const;
	double b() const;

	//setters
	void setK(double k);
	void setB(double b);

private:
	double m_k;
	double m_b;
};

