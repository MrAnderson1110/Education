#include "Out_of_range.h"

Out_of_range::Out_of_range(std::string msg)
	: m_massage(msg)
{

}

std::string Out_of_range::what() const
{
	return m_massage;
}
