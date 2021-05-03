#pragma once
#include <string>

/*
* Создайте класс, который хранил бы информацию о книге: название, автор, дата
* издания. Создать несколько объектов. Если в конструктор передан символьный параметр,
* например «а», то контролировать, начинается ли имя автора с данной буквы. Если нет, то
* выводить сообщение об ошибке. Если параметр не задан, то контролировать не надо.
*/

class Book
{
public:
	Book();
	Book(std::string name, std::string athor, std::string publishDate);
	Book(const Book& other);
	~Book();

	const std::string &name() const;
	const std::string &author() const;
	const std::string &publishDate() const;

	void setName(const std::string &name);
	void setAuthor(const std::string &author);
	void setPublishDate(const std::string &date);


private:
	std::string *m_name;
	std::string *m_author;
	std::string *m_publishDate;
};

