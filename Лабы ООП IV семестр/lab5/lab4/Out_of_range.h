#pragma once
#include <string>

class Out_of_range
{
public:
	Out_of_range(std::string msg);

	std::string what() const;
private:
	std::string m_massage;
};

