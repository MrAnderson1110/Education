#include <iostream>

using namespace std;

// �������� �� ������ ������
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW 

//����������� �������
void showHint();
short getCommand();
void showString(const char* str);
unsigned int showWordsNum(const char* str);
const char* enterString(const char *str, size_t size);

int main()
{
	setlocale(0, "Russian");
	cout << "������������ ������ �6.\n��������� �������� ������.\n������� " << (1 - 1) % 30 + 1 << endl;

	short command = -1;
    const size_t size = 1000;
    const char* string = new char[size];

    do {
        command = getCommand();
        switch (command)
        {
        case 0:
            string = enterString(string, size);
            break;
        case 1:
            showString(string);
            break;
        case 2:
            cout << "� ������: " << showWordsNum(string) << " ����\n";
            break;
        case 3:
            showHint();
            break;
        case 4:
            break;
        default:
            cout << "����������� �������\n";
            break;
        }
    } while (command != 4);

    delete[] string;
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
    short com;
    cout << "������� ������� ��� ����������� (3 - �������� ��� �������): ";
    cin >> com;
    while (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "������� ���������� �������� (4 ��� ������): ";
        cin >> com;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return com;
}

void showString(const char* str)
{
    cout << "������� ������:\n" << str << '\n';
}

unsigned int showWordsNum(const char* str)
{
    unsigned int count = 0;
    for (int i = 0; str[i] != '\0'; ++i)
        if (str[i] == '\t' || str[i] == ' ')
            ++count;
    ++count;
    return count;
}

const char* enterString(const char* str, size_t size)
{
    delete[] str;
    char* newStr = new char[size];
    size_t i = 0;
    cout << "������� ������: \n";
    cin.getline(newStr, size);
    return newStr;
}

void showHint()
{
    cout << "0 - ������ ������ � ����������\n";
    cout << "1 - ������� ������ �� �����\n";
    cout << "2 - �������� ���������� ���� � ������\n";
    cout << "3 - �������� ��� �������\n";
    cout << "4 - �����\n";
}