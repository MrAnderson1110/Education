#include "Book.h"

#include <iostream>

Book::Book(char control)
	: m_name()
	, m_author()
	, m_publishDate()
	, m_control(control)
{

}

Book::Book(std::string name, std::string athor, std::string publishDate, char control)
	: m_name(name)
	, m_author(athor)
	, m_publishDate(publishDate)
	, m_control(control)
{
}

Book::Book(const Book& other)
	: m_name(other.m_name)
	, m_author(other.m_author)
	, m_publishDate(other.m_publishDate)
	, m_control(other.m_control)
{
}

Book::~Book()
{

}

const std::string& Book::name() const
{
	return m_name;
}

const std::string& Book::author() const
{
	return m_author;
}

const std::string& Book::publishDate() const
{
	return m_publishDate;
}

void Book::setName(const std::string& name)
{
	if (m_name == name)
		return;

	m_name = name;
}

void Book::setAuthor(const std::string& author)
{
	if (m_author == author)
		return;

	if (m_control != '\0' && *author.begin() != m_control) 
		std::cerr << "author name must start with " << m_control << '\n';

	m_author = author;
}

void Book::setPublishDate(const std::string& date)
{
	if (m_publishDate == date)
		return;

	m_publishDate = date;
}

