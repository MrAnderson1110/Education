#include "Book.h"

#include <iostream>
#include <string>

std::ostream& operator<<(std::ostream& os, const Book& book)
{
	return os << book.name() << ", " << book.author() << ", " << book.publishDate() << '\n';
}

int main()
{
	Book firstBook;
	std::cout << "firstBook: " << firstBook;
	Book bookWithControl('S');
	std::cout << "bookWithControl: " << bookWithControl;
	Book secBook("book name", "book author", "20.01.2002");
	std::cout << "secBook: " << secBook;
	Book filledBookWithControl("book name", "Book author", "20.01.2002", 'B');
	std::cout << "filledBookWithControl: " << filledBookWithControl;
	Book thirdBook(secBook);
	std::cout << "thirdBook: " << thirdBook << '\n';

	std::string book, author, year;
	std::cout << "Enter author, book and year: ";
	std::cin >> author >> book >> year;
	std::cout << '\n';

	firstBook.setAuthor(author);
	firstBook.setName(book);
	firstBook.setPublishDate(year);
	std::cout << "new firstBook: " << firstBook;

	bookWithControl.setAuthor(author);
	bookWithControl.setName(book);
	bookWithControl.setPublishDate(year);
	std::cout << "new bookWithControl: " << bookWithControl;

	secBook.setAuthor(author);
	secBook.setName(book);
	secBook.setPublishDate(year);
	std::cout << "new secBook: " << secBook;

	filledBookWithControl.setAuthor(author);
	filledBookWithControl.setName(book);
	filledBookWithControl.setPublishDate(year);
	std::cout << "new filledBookWithControl: " << filledBookWithControl;

	thirdBook.setAuthor(author);
	thirdBook.setName(book);
	thirdBook.setPublishDate(year);
	std::cout << "new thirdBook: " << thirdBook;

	std::cout << '\n';	std::cout << "Enter author, book and year: ";
	std::cin >> author >> book >> year;
	std::cout << '\n';

	firstBook.setAuthor(author);
	firstBook.setName(book);
	firstBook.setPublishDate(year);
	std::cout << "new firstBook: " << firstBook;

	bookWithControl.setAuthor(author);
	bookWithControl.setName(book);
	bookWithControl.setPublishDate(year);
	std::cout << "new bookWithControl: " << bookWithControl;

	secBook.setAuthor(author);
	secBook.setName(book);
	secBook.setPublishDate(year);
	std::cout << "new secBook: " << secBook;

	filledBookWithControl.setAuthor(author);
	filledBookWithControl.setName(book);
	filledBookWithControl.setPublishDate(year);
	std::cout << "new filledBookWithControl: " << filledBookWithControl;

	thirdBook.setAuthor(author);
	thirdBook.setName(book);
	thirdBook.setPublishDate(year);
	std::cout << "new thirdBook: " << thirdBook;
	std::cout << '\n';

	return 0;
}