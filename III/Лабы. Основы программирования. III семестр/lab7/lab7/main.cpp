#include <iostream>

using namespace std;

// проверка на утечки памяти
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW 

//определения функций
void showHint();
short getCommand();
void showString(const char* str);
unsigned int showWordsNum(const char* str);
const char* enterString(const char *str, size_t size);

int main()
{
	setlocale(0, "Russian");
	cout << "Лабораторная работа №6.\nОбработка числовых матриц.\nВариант " << (1 - 1) % 30 + 1 << endl;

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
            cout << "В строке: " << showWordsNum(string) << " слов\n";
            break;
        case 3:
            showHint();
            break;
        case 4:
            break;
        default:
            cout << "Неизвестная команда\n";
            break;
        }
    } while (command != 4);

    delete[] string;
    // Для обнаружения утечек памяти
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
    cout << "Введите команду для продолжения (3 - показать все команды): ";
    cin >> com;
    while (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Введите корректное значение (4 для выхода): ";
        cin >> com;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return com;
}

void showString(const char* str)
{
    cout << "Текущая строка:\n" << str << '\n';
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
    cout << "Введите строку: \n";
    cin.getline(newStr, size);
    return newStr;
}

void showHint()
{
    cout << "0 - Ввести строку с клавиатуры\n";
    cout << "1 - Вывести строку на экран\n";
    cout << "2 - Показать количество слов в строке\n";
    cout << "3 - Показать все команды\n";
    cout << "4 - Выход\n";
}