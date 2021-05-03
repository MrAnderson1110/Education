/* 
* ������������ ������ �2
* ������� 13
* 
* ���� ������������������ ������������� ����� ����� a(1), a(2), ... , a(n).
* �������� ������������������, ���������� �������
* �������������� n ��������� �������� ������������������, ����� n-1 ��������� � �.�.
* K = average(a(1) ... a(n)), average(a(1) ... a(n-1)), ... .average(a(1) , a(2)), a(1)
*/

#include "LinkList.h"
#include <iostream>

using namespace std;


//���������� �������
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
	cout << "������������ ������ �2.\n�������� � ����������� ������\n������� " << (81 % 23) + 1 << "\n\n";
	short command = -1;
	//������� ������
	LinkList<double> inputList;
	//�������� �� ����� ������
	LinkList<double>::iterator endInputIter = inputList.begin();
	//�������� ������
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
			cout << "����������� �������\n";
			break;
		}
	} while (command != 6);
	return 0;
}

//���������� �������

//���������� ��������� � ������ 
//��������� ������� ��������� ������������� �� ��������� inputIterator � ������ list
//���������� �������� �� ����������� �������
//�������, �� ���������� ������� ����� ��������������
LinkList<double>::iterator insertElements(LinkList<double>& list, const LinkList<double>::iterator& iter)
{
	double elem;
	LinkList<double>::iterator tempIter = iter;
	cout << "������� �������� ��� ���������� � ������: ";
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

//�������� ��������� �� ������
//������� ������� ��������� ������������� �� ������
void eraseElement(LinkList<double>& list)
{
	if (list.isEmpty()) {
		cout << "������ ����. ������ �������\n";
		return;
	}
	int count = 0;
	double elem;
	cout << "������� �������� ��� ��������: ";
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
	cout << "������� " << count << " ���������\n";
}

//����� ���������� � ��������� ������� �� �����
void showAll(const LinkList<double> &inList, const LinkList<double> &outList)
{
	cout << "������� ������:\n";
	display_all(inList);

	cout << "�������� ������:\n";
	display_all(outList);
}

//����� ���������
void showHint()
{
	cout << "0 - �������� �������� � ������\n";
	cout << "1 - ������� ������� �� �������� ������\n";
	cout << "2 - ������� ����� ������\n";
	cout << "3 - �������� �������� ������\n";
	cout << "4 - ������� ������ �� �����\n";
	cout << "5 - ������� ���������\n";
	cout << "6 - �����" << endl;
}

//������ ������� �������� �������������
//������ � ���������� ��������� ������������� �������
short getCommand()
{
	short com;
	cout << "������� ������� ��� ����������� (5 - �������� ��� �������): ";
	cin >> com;
	while (!cin) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "������� ��������� �������� (6 ��� ������):";
		cin >> com;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return com;
}

//������� �������� ������
//���������� �������� ������ newList �� ��������� ������ oldList � ������������ � ��������
void computeNewList(const LinkList<double>& oldList, LinkList<double>& newList)
{
	//������� ��������� ������, ���� �� �� ����
	newList.clear();
	//�������� ����������� �������� ������, ����� ��������� ��� ����������� 
	LinkList<double> li = oldList;
	//��������� ��� ������ ����� �������
	LinkList<double>::iterator it = li.begin();
	LinkList<double>::iterator outIt = newList.begin();

	//���� ������� ������ �� ����
	while (!li.isEmpty()) {
		//������� ������ �������� � �������� ������
		outIt = newList.insert(outIt, *it++);
		//���� �� ���������� ����� �������� ������
		while (li.begin() != it->next()) {
			//����������� � ���������� � �������� ������ �������� ���� �������� �������� ������, ����� ����������
			*outIt += *it++;
		}
		//���� �� ������� ������ 1 �������, ������������� � ��� ����� ���������� � ������� ��� 
		if (li.size() > 1) {
			//�������� ��������� ������� �� �������� ������ � ���������� �������� � �������� ������
			*outIt += *it;
			//������� ����������� ���������� �� ���������� ��������� �������� ������ (��������� �������� ���������������)
			*outIt /= li.size();
		}
		//�������� ���������� �������� �� �������� ������ � ������� � ��� ������
		it = li.erase(it);
	}
}

//������� ��� �������� � ������ ������� � ������� � �������
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

//������� ���������� ������
void clearList(LinkList<double>& li)
{
	li.clear();
}
