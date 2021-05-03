    #include <iostream>
    #include <fstream>
    #include <cstring>
    #include <iomanip>
    #include <Windows.h>
    #include "LinkList.h"
    #include "Worker.h"

    using namespace std;

    // �������� �� ������ ������
    #define _CRTDBG_MAP_ALLOC
    #include <cstdlib>
    #include <crtdbg.h>
    #define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
    #define new DBG_NEW 

    //����������� �������
    //������� ������ �� ������������ �����
    const int askYearForSearch();
    void askFilePath(char *filePath);

    //������� ������ � ����������� ����
    void showHint();
    void respondOnSearchQuery(LinkList<Worker>* li);
    void showAll(LinkList<Worker>* li);
    void askName(char* name);

    //���������������� �������
    short getCommand();
    void addWorker(LinkList<Worker>* workers);
    void removeWorker(LinkList<Worker>* workers);
    void findWorker(const LinkList<Worker>* workers, LinkList<Worker>*li, const int& year);
    bool readFromFile(LinkList<Worker>* workers, const char* filePath);
    bool saveAsFile(const LinkList<Worker>* workers, const char* filePath);
    void clearList(LinkList<Worker>* workers);
    void changeName(LinkList<Worker>* workers, const char *name);
    void changePosition(LinkList<Worker>* workers, const char* name);

    //��������� �������
    LinkList<Worker>::iterator __findWorkerByName(LinkList<Worker>* workers, const char* name);

    int main() 
    {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        cout.setf(ios_base::adjustfield, ios_base::left);
	    cout << "�������� ������.\n������� " << (81 - 1) % 19 + 1 << '\n';

        short command = -1;
        LinkList<Worker> *workers = new LinkList<Worker>;

        do {
            command = getCommand();
            switch (command)
            {
            case 0:
                addWorker(workers);
                break;
            case 1:
                removeWorker(workers);
                break;
            case 2: {
                LinkList<Worker>* li = new LinkList<Worker>;
                findWorker(workers, li, askYearForSearch());
                respondOnSearchQuery(li);
                delete li;
                break;
            }
            case 3:
                workers->sort();
                break;
            case 4: {
                char filePath[100];
                askFilePath(filePath);
                if (!saveAsFile(workers, filePath))
                    cout << "������ � ���� " << filePath << " �� �������\n";
                break;
            }
            case 5: {
                char filePath[100];
                askFilePath(filePath);
                if (!readFromFile(workers, filePath))
                    cout << "������ �� ����� " << filePath << " �� �������\n";
                break;
            }
            case 6: {
                char name[25];
                askName(name);
                changeName(workers, name);
                break;
            }
            case 7: {
                char name[25];
                askName(name);
                changePosition(workers, name);
                break;
            }
            case 8:
                showAll(workers);
                break;
            case 9:
                clearList(workers);
                break;
            case 10:
                showHint();
                break;
            case 11:
                break;
            default:
                cout << "����������� �������\n";
                break;
            }
        } while (command != 11);

        delete workers;

        // ��� ����������� ������ ������
        _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
        _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
        _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
        _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
        _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
        _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
        _CrtDumpMemoryLeaks();

	    return 0;
    }

short getCommand()
{
#undef max
    short com;
    cout << "������� ������� ��� ����������� (10 - �������� ��� �������): ";
    cin >> com;
    while (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
     
        cout << "������� ���������� �������� (11 ��� ������): ";
        cin >> com;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return com;
#define max
}

void addWorker(LinkList<Worker>* workers)
{
#undef max
    char name[100];
    char position[100];

    int year = 0;
    cout << "������� ��� � �������� ���������� (�� 25 ��������): ";
    cin.getline(name, 25, '\n');
    while (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "��������� ���������� ����� ������. ��������� ����: ";
        cin.getline(name, 25, '\n');
    }
    cout << "������� ������� ���������� (�� 25 ��������): ";
    cin.getline(position, 25, '\n');
    while (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "��������� ���������� ����� ������. ��������� ����: ";
        cin.getline(position, 25, '\n');
    }
    cout << "������� ��� ����������� �� ������: ";
    cin >> year;
    while (!cin || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "������� ������������ ��������. ��������� ����: ";
        cin >> year;
    }
    workers->insert_before(workers->end(), Worker(name, position, year));
#define max
}

void removeWorker(LinkList<Worker>* workers)
{
#undef max
    char name[100];
    cout << "������� ��� � �������� ���������� (�� 25 ��������): ";
    cin.getline(name, 25);
    while (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "��������� ���������� ����� ������. ��������� ����: ";
        cin.getline(name, 25, '\n');
    }
    LinkList<Worker>::iterator it = __findWorkerByName(workers, name);
    if (!it) {
        cout << "��������� � ����� �������� � ������ ���\n";
        return;
    }
    workers->erase(it);
#define max
}

void findWorker(const LinkList<Worker>* workers, LinkList<Worker> *outList, const int &year)
{
    if (workers->isEmpty())
        return;

    LinkList<Worker>::iterator it = workers->begin();
    while (it != workers->end()) {
        if ((*it).yearOfEmployment() == year)
            outList->insert_before(outList->end(), *it);
        ++it;
    }
}

const int askYearForSearch()
{
#undef max
    int year = 0;
    cout << "������� ��� ��� ������: ";
    cin >> year;
    while (!cin  || cin.peek() != '\n') {
        cout << "������� ������������ ��������. ��������� ����: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> year;
    }
    return year;
#define max
}

bool readFromFile(LinkList<Worker>* outList, const char* filePath)
{
#undef max
    char name[25]{};
    char position[25]{};
    int year = 0;
    fstream fs;
    fs.open(filePath, ios_base::in);
    if (!fs.is_open())
        return false;
    while (!fs.eof()) {
        fs.getline(name, 25, '|');
        fs.getline(position, 25, '|');
        fs >> year;
        fs.ignore(1, '\n');
        outList->insert_before(outList->end(), Worker(name, position, year));
    }
    fs.close();
#define max
    return true;
}

bool saveAsFile(const LinkList<Worker>* workers, const char* filePath)
{
    fstream fs;
    fs.open(filePath, ios_base::out);
    if (!fs.is_open())
        return false;
    LinkList<Worker>::iterator iter = workers->begin();
    while (iter != --workers->end()) {
        fs << iter->name() 
            << '|' << iter->position() 
            << '|' << iter->yearOfEmployment() << '\n';
        ++iter;
    }
    fs << iter->name()
        << '|' << iter->position()
        << '|' << iter->yearOfEmployment();
    fs.close();
    return true;
}

void clearList(LinkList<Worker>* workers)
{
#undef max
    if (workers->isEmpty())
        return;

    char com;
    cout << "�� �������, ��� ������ ������� ��� ������? (y ��� �����������): ";
    cin >> com;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (com != 'y')
        return;
    workers->clear();
#define max
}

void changeName(LinkList<Worker>* workers, const char* name)
{
#undef max
    LinkList<Worker>::iterator iter = __findWorkerByName(workers, name);
    if (!iter) {
        cout << "��������� � ����� �������� � ������ ���\n";
        return;
    }
    char newName[25];
    cout << "������� ����� ������� � �������� (�� 25 ��������): ";
    cin.getline(newName, 25, '\n');
    if (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "��������� ���������� ����� ������. ��������� ����: ";
        cin.getline(newName, 25, '\n');
    }
    iter->setName(newName);
#define max
}

void changePosition(LinkList<Worker>* workers, const char* name)
{
#undef max
    LinkList<Worker>::iterator iter = __findWorkerByName(workers, name);
    if (!iter) {
        cout << "��������� � ����� �������� � ������ ���\n";
        return;
    }
    char pos[25];
    cout << "������� ����� ������� (�� 25 ��������): ";
    cin.getline(pos, 25, '\n');
    if (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "��������� ���������� ����� ������. ��������� ����: ";
        cin.getline(pos, 25, '\n');
    }
    iter->setPosition(pos);
#define max
}

LinkList<Worker>::iterator __findWorkerByName(LinkList<Worker>* workers, const char* name)
{
    LinkList<Worker>::iterator iter = workers->begin();
    while (iter != workers->end()) {
        if (!strcmp(name, iter->name()))
            return iter;
        ++iter;
    }
    return LinkList<Worker>::iterator(nullptr);
}

void askFilePath(char* filePath)
{
#undef max
    cout << "������� ������ ���� � ����� (�� 100 ��������): ";
    cin.getline(filePath, 100);
    while (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "��������� ���������� ����� ������. ��������� ����: ";
        cin.getline(filePath, 100, '\n');
    }
#define max
}

void showHint()
{
    cout << "0  - �������� ������\n";
    cout << "1  - ������� ������\n";
    cout << "2  - ����� ������ �� ���� �����������\n";
    cout << "3  - ����������� �� �����\n";
    cout << "4  - �������� ������ � ����\n";
    cout << "5  - ������ �� �����\n";
    cout << "6  - �������� ������� ����������\n";
    cout << "7  - �������� ������� ����������\n";
    cout << "8  - ������� ������ �� �����\n";
    cout << "9  - �������� ������\n";
    cout << "10 - �������� ���������\n";
    cout << "11 - �����\n";
}

void respondOnSearchQuery(LinkList<Worker>* li)
{
    if (li->isEmpty()) {
        cout << "������ ��������� � ������ ���.\n";
        return;
    }

    LinkList<Worker>::iterator iter = li->begin();
    cout << "������� ������:\n";
    cout << setw(26) << "������� � ��������"
        << setw(26) << "�������"
        << setw(26) << "��� ����������� �� ������" << '\n';
    while (iter != li->end()) {
        cout << setw(26) << iter->name()
            << setw(26) << iter->position()
            << setw(26) << iter->yearOfEmployment() << '\n';
        ++iter;
    }
}

void showAll(LinkList<Worker>* li)
{
    if (li->isEmpty()) {
        cout << "������ ����������� ����\n";
        return;
    }
    LinkList<Worker>::iterator iter = li->begin();
    cout << setw(26) << "������� � ��������"
        << setw(26) << "�������"
        << setw(26) << "��� ����������� �� ������" << '\n';
    while (iter != li->end()) {
        cout << setw(26) << iter->name()
            << setw(26) << iter->position()
            << setw(26) << iter->yearOfEmployment() << '\n';
        ++iter;
    }
}

void askName(char* name)
{
#undef max
    cout << "������� ��� ����������, ������ �������� ����� ��������: ";
    cin.getline(name, 25, '\n');
    while (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "��������� ���������� ����� ������. ��������� ����: ";
        cin.getline(name, 25, '\n');
    }
#define max
}
