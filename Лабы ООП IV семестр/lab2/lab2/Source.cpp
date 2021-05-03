#include "Book.h"

int main()
{
	Book firstBook;
	Book secBook("book name", "book author", "20.01.2002");
	Book thirdBook(secBook);
	return 0;
}