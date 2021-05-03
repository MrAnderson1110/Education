#pragma once
#include <cstring>

class Worker
{
public:
	Worker(char* name, char* position, const int& year);
	Worker(const Worker& worker);

	bool operator==(const Worker& rightVal);
	bool operator>(const Worker& rightVal);
	bool operator<(const Worker& rightVal);
	bool operator!=(const Worker& rightVal);
	Worker& operator=(const Worker& rightVal);

	const char* name() const;
	const char* position() const;
	const int yearOfEmployment() const;

	void setName(const char* name);
	void setPosition(const char* position);

private:
	//������������ ����� ����� � ������
	static const int m_maxStringSize = 25;
	//������ ����������� ��� char (� �� const char),
	//����� ���� ����������� �������� ����������� ������� ����������� �����
	char m_name[m_maxStringSize];
	char m_position[m_maxStringSize];
	int m_yearOfEmployment;

};

