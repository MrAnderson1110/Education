#include "Book.h"

Book::Book()
	: m_name(new std::string)
	, m_author(new std::string)
	, m_publishDate(new std::string)
{

}

Book::Book(std::string name, std::string athor, std::string publishDate)
	: m_name(new std::string(name))
	, m_author(new std::string(athor))
	, m_publishDate(new std::string(publishDate))
{
}

Book::Book(const Book& other)
	: m_name(new std::string(*other.m_name))
	, m_author(new std::string(*other.m_author))
	, m_publishDate(new std::string(*other.m_publishDate))
{
}

Book::~Book()
{
	delete m_publishDate;
	delete m_author;
	delete m_name;
}

const std::string& Book::name() const
{
	return *m_name;
}

const std::string& Book::author() const
{
	return *m_author;
}

const std::string& Book::publishDate() const
{
	return *m_publishDate;
}

void Book::setName(const std::string& name)
{
	if (*m_name == name)
		return;

	*m_name = name;
}

void Book::setAuthor(const std::string& author)
{
	if (*m_author == author)
		return;

	*m_author = author;
}

void Book::setPublishDate(const std::string& date)
{
	if (*m_publishDate == date)
		return;

	*m_publishDate = date;
}
