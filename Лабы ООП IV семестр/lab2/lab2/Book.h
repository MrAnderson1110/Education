#pragma once
#include <string>

class Book
{
public:
	Book(char control = '\0');
	Book(std::string name, std::string athor, std::string publishDate, char control = '\0');
	Book(const Book& other);
	~Book();

	const std::string &name() const;
	const std::string &author() const;
	const std::string &publishDate() const;

	void setName(const std::string &name);
	void setAuthor(const std::string &author);
	void setPublishDate(const std::string &date);


private:
	std::string m_name;
	std::string m_author;
	std::string m_publishDate;
	char m_control;
};

