#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

// проверка на утечки памяти
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW 

using namespace std;

//определения функций
void showHint();
short getCommand();
void showMatrix(int ** mat, const unsigned short size);
void randomGenerate(int** mat, const unsigned short size);
int maxNonUnique(int** mat, const unsigned short size);
int notNullStrings(int** mat, const unsigned short size);
void fillFromKeyboard(int** mat, const unsigned short size);

int main()
{
	setlocale(0, "Russian");
	cout << "Лабораторная работа №6.\nОбработка числовых матриц.\nВариант " << (1 - 1) % 20 + 1 << endl;

	short command = -1;
	int** matrix = nullptr;
	unsigned short size = 0;

	//Для тестов, чтобы можно было тестировать на рандомном размере
	cout << "Введите размерность матрицы: ";
	cin >> size;
	while (!cin || !(size > 0)) {
		cout << "Введено неверное значение. Повторите ввод: ";
		std::cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> size;
	}
	matrix = new int* [size];
	for (int i = 0; i < size; ++i) {
		matrix[i] = new int[size];
	}

    do {
        command = getCommand();
        switch (command)
        {
        case 0:
            fillFromKeyboard(matrix, size);
            break;
        case 1:
            randomGenerate(matrix, size);
            break;
        case 2:
            showMatrix(matrix, size);
            break;
        case 3:
            cout << "Количество строк, не содержащих ни одного нулевого элемента: "
                << notNullStrings(matrix, size) << '\n';
            break;
        case 4:
            cout << "Максимальное из чисел, встречающихся матрице более одного раза: "
                << maxNonUnique(matrix, size) << '\n';
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

    for (unsigned short i = 0; i < size; ++i)
        delete[] matrix[i];
    delete[] matrix;

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
    cout << "Введите команду для продолжения (5 - показать все команды): ";
    cin >> com;
    while (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Введите корректное значение (6 для выхода): ";
        cin >> com;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return com;
}

void showMatrix(int** mat, const unsigned short size)
{
    for (unsigned short i = 0; i < size; ++i) {
        for (unsigned short j = 0; j < size; ++j) {
            cout << setw(2) << mat[i][j] << ' ';
        }
        cout << '\n';
    }
}

void randomGenerate(int** mat, const unsigned short size)
{
    srand(clock());

    for (unsigned short i = 0; i < size; ++i) {
        for (unsigned short j = 0; j < size; ++j) {
            mat[i][j] = rand() % 100;
        }
    }
}

int maxNonUnique(int** mat, const unsigned short size)
{
    int max = 0;
    for (unsigned short i = 0; i < size; ++i) {
        for (unsigned short j = 0; j < size; ++j) {
            int searchNum = mat[i][j];
            bool exitFlag = false;
            for (unsigned short k = 0; k < size && !exitFlag; ++k) {
                for (unsigned short n = 0; n < size; ++n) {
                    int el = mat[k][n];
                    if (searchNum == mat[k][n] && !(searchNum < max) && n != j) {
                        max = searchNum;
                        exitFlag = true;
                        break;
                    }
                }
            }
        }
    }
    return max;
}

int notNullStrings(int** mat, const unsigned short size)
{
    unsigned int count = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (mat[i][j] == 0) {
                ++count;
                break;
            }
        }
    }
    return size - count;
}

void fillFromKeyboard(int** mat, const unsigned short size)
{
    int elem = 0;
    cout << "Введите значение элементов для вставки:\n";
    for (int row = 0; row < size; ++row)
    {
        for (int col = 0; col < size; ++col) {
            cout << "Элемент [" << row << "][" << col << "]: ";
            cin >> elem;
            while (!cin) {
                std::cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Введено недопустимое значение. Повторите ввод.\n";
                cout << "Элемент [" << row << "][" << col << "]: ";
                cin >> elem;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            mat[row][col] = elem;
        }
    }
}

void showHint()
{
    cout << "0 - Заполнить матрицу с клавиатуры\n";
    cout << "1 - Заполнить матрицу случайными числами\n";
    cout << "2 - Вывести матрицу на экран\n";
    cout << "3 - Показать количество строк, не содержащих ни одного нулевого элемента\n";
    cout << "4 - Показать максимальное из чисел, встречающихся матрице более одного раза\n";
    cout << "5 - Показать все команды\n";
    cout << "6 - Выход\n";
}