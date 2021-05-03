#pragma once

/* 
* ������� 1
* ����� ��� ������� ��������� ��������� �=kx+b. ������������ ��������� k, b 
* ����������� � ������� ����� ������������� ����. ��� ������� ���������
* ������������� ����� Root. 
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

