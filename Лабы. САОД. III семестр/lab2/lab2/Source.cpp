/* 
* Лабораторная работа №2
* Вариант 13
* 
* Дана последовательность повторяющихся целых чисел a(1), a(2), ... , a(n).
* Получить последовательность, содержащую среднее
* арифметическое n элементов исходной последовательности, затем n-1 элементов и т.д.
* K = average(a(1) ... a(n)), average(a(1) ... a(n-1)), ... .average(a(1) , a(2)), a(1)
*/

#include "LinkList.h"
#include <iostream>

using namespace std;


//Объявления функций
LinkList<double>::iterator insertElements(LinkList<double>& list, const LinkList<double>::iterator& iter);
void eraseElement(LinkList<double>& list);
void showAll(const LinkList<double>& inList, const LinkList<double>& outList);
void showHint();
short getCommand();
void computeNewList(const LinkList<double> &list, LinkList<double>& outList);
void display_all(const LinkList<double>& li);
void clearList(LinkList<double>& li);

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Лабораторная работа №2.\nЛинейные и циклические списки\nВариант " << (81 % 23) + 1 << "\n\n";
	short command = -1;
	//входной список
	LinkList<double> inputList;
	//Итератор на конец списка
	LinkList<double>::iterator endInputIter = inputList.begin();
	//выходной список
	LinkList<double> outputList;

	do {
		command = getCommand();
		switch (command)
		{
		case 0:
			endInputIter = insertElements(inputList, endInputIter);
			break;
		case 1:
			eraseElement(inputList);
			break;
		case 2:
			computeNewList(inputList, outputList);
			break;
		case 3:
			clearList(inputList);
			break;
		case 4:
			showAll(inputList, outputList);
			break;
		case 5:
			showHint();
			break;
		case 6:
			break;
		default:
			cout << "Неизвестная команда\n";
			break;
		}
	} while (command != 6);
	return 0;
}

//Объявления функций

//Добавление элементов в список 
//Добавляет елемент введенный пользователем по итератору inputIterator в список list
//Возвращает итератор на вставленный элемент
//Символы, не являющиеся числами будут игнорироваться
LinkList<double>::iterator insertElements(LinkList<double>& list, const LinkList<double>::iterator& iter)
{
	double elem;
	LinkList<double>::iterator tempIter = iter;
	cout << "Введите элементы для добавления в список: ";
	while(cin.peek() != '\n') {
		cin >> elem;
		if (!cin) {
			cin.clear();
			cin.ignore(sizeof(char));
			continue;
		}
		tempIter = list.insert(tempIter, elem);
	}
	return tempIter;
}

//Удаление элементов из списка
//Удаляет элемент введенный пользователем из списка
void eraseElement(LinkList<double>& list)
{
	if (list.isEmpty()) {
		cout << "Список пуст. Нучего удалять\n";
		return;
	}
	int count = 0;
	double elem;
	cout << "Введите элементы для удаления: ";
	while (cin.peek() != '\n') {
		cin >> elem;
		if (!cin) {
			cin.clear();
			cin.ignore(sizeof(char));
			continue;
		}
		LinkList<double>::iterator it = list.find(elem);
		if (elem == *it) {
			list.erase(it);
			++count;
		}
	}
	cout << "Удалено " << count << " элементов\n";
}

//Вывод начального и конечного списков на экран
void showAll(const LinkList<double> &inList, const LinkList<double> &outList)
{
	cout << "Входной список:\n";
	display_all(inList);

	cout << "Выходной список:\n";
	display_all(outList);
}

//Вывод подсказки
void showHint()
{
	cout << "0 - добавить элементы в список\n";
	cout << "1 - удалить элемент из входного списка\n";
	cout << "2 - создать новый список\n";
	cout << "3 - очистить исходный список\n";
	cout << "4 - вывести списки на экран\n";
	cout << "5 - вывести подсказку\n";
	cout << "6 - выход" << endl;
}

//Чтение команды введеной пользователем
//Читает и возвращает введенную пользователем команду
short getCommand()
{
	short com;
	cout << "Введите команду для продолжения (5 - показать все команды): ";
	cin >> com;
	while (!cin) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Введите коректной значение (6 для выхода):";
		cin >> com;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return com;
}

//Создать выходной список
//Генерирует выходной список newList из выходного списка oldList в соответствии с заданием
void computeNewList(const LinkList<double>& oldList, LinkList<double>& newList)
{
	//Очистка выходного списка, если он не пуст
	newList.clear();
	//Глубокое копирование входного списка, чтобы сохранить его целостность 
	LinkList<double> li = oldList;
	//Итераторы для обхода обоих списков
	LinkList<double>::iterator it = li.begin();
	LinkList<double>::iterator outIt = newList.begin();

	//Пока входной список не пуст
	while (!li.isEmpty()) {
		//Вставка нового элемента в выходной список
		outIt = newList.insert(outIt, *it++);
		//Пока не закончится обход входного списка
		while (li.begin() != it->next()) {
			//Прибавление к созданному в выходном списке элементу всех значений входного списка, кроме последнего
			*outIt += *it++;
		}
		//Если во входном списке 1 элемент, необходимости в еще одном добавлении и делении нет 
		if (li.size() > 1) {
			//Добавить последний элемент из входного списка к созданному элементу в выходном списке
			*outIt += *it;
			//Деление полученного результата на количество элементов входного списка (получение среднего арифметического)
			*outIt /= li.size();
		}
		//Удаление последнего элемента из входного списка и переход к его началу
		it = li.erase(it);
	}
}

//Выводит все элементы в списке начаная с первого в консоль
void display_all(const LinkList<double>& li)
{
	LinkList<double>::iterator it = li.begin();
	if (li.isEmpty()) {
		std::cout << "list is empty" << std::endl;
		return;
	}

	for (int i = 0; i < li.size(); ++i) {
		std::cout << "element N" << i + 1 << ": " << *it++ << std::endl;
	}
}

//Очищает переданный список
void clearList(LinkList<double>& li)
{
	li.clear();
}
