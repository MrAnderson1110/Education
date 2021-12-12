#include "Worker.h"

Worker::Worker(char* name, char* position, const int& year)
	: m_yearOfEmployment(year)
{
	std::strcpy(m_name, name);
	std::strcpy(m_position, position);
}

Worker::Worker(const Worker& rightVal)
{
	std::strcpy(m_name, rightVal.name());
	std::strcpy(m_position, rightVal.position());
	m_yearOfEmployment = rightVal.yearOfEmployment();
}

bool Worker::operator==(const Worker& rightVal)
{
	return !std::strcmp(m_name, rightVal.name());
}

bool Worker::operator>(const Worker& rightVal)
{
	return std::strcmp(m_name, rightVal.name()) > 0;
}

bool Worker::operator<(const Worker& rightVal)
{
	return std::strcmp(m_name, rightVal.name()) < 0;
}

bool Worker::operator!=(const Worker& rightVal)
{
	return !operator==(rightVal);
}

Worker& Worker::operator=(const Worker& rightVal)
{
	if (this == &rightVal)
		return *this;
	std::strcpy(m_name, rightVal.name());
	std::strcpy(m_position, rightVal.position());
	m_yearOfEmployment = rightVal.m_yearOfEmployment;
	return *this;
}

const char* Worker::name() const
{
	return m_name;
}

const char* Worker::position() const
{
	return m_position;
}

const int Worker::yearOfEmployment() const
{
	return m_yearOfEmployment;
}

void Worker::setName(const char* name)
{
	std::strcpy(m_name, name);
}

void Worker::setPosition(const char* position)
{
	std::strcpy(m_position, position);
}
