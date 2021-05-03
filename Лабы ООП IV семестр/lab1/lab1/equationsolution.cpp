#include "equationsolution.h"
#include <iostream>

double EquationSolution::Root(double y) const
{
    // ��� k == 0 ���������  ����� ��� y = b,
    // ��� ��� � ���� ������������ �� ������������ ���������� ��������� ������� ��������� � cerr
    if (!(m_k > 0.0) && !(m_k < 0.0)) {
        if (m_b > y || m_b < y)
            std::cerr << "While k == 0, y cannot be different from b\n";

        return INFINITY;
    }

    return (y - m_b) / m_k;
}

double EquationSolution::k() const
{
    return m_k;
}

double EquationSolution::b() const
{
    return m_b;
}

void EquationSolution::setK(double k)
{
    m_k = round(k * 1000.0) / 1000.0;
}

void EquationSolution::setB(double b)
{
    m_b = round(b * 1000.0) / 1000.0;
}