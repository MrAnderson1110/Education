#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

// �������� �� ������ ������
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW 

using namespace std;

//����������� �������
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
	cout << "������������ ������ �6.\n��������� �������� ������.\n������� " << (1 - 1) % 20 + 1 << endl;

	short command = -1;
	int** matrix = nullptr;
	unsigned short size = 0;

	//��� ������, ����� ����� ���� ����������� �� ��������� �������
	cout << "������� ����������� �������: ";
	cin >> size;
	while (!cin || !(size > 0)) {
		cout << "������� �������� ��������. ��������� ����: ";
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
            cout << "���������� �����, �� ���������� �� ������ �������� ��������: "
                << notNullStrings(matrix, size) << '\n';
            break;
        case 4:
            cout << "������������ �� �����, ������������� ������� ����� ������ ����: "
                << maxNonUnique(matrix, size) << '\n';
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

    for (unsigned short i = 0; i < size; ++i)
        delete[] matrix[i];
    delete[] matrix;

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
    cout << "������� ������� ��� ����������� (5 - �������� ��� �������): ";
    cin >> com;
    while (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "������� ���������� �������� (6 ��� ������): ";
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
    cout << "������� �������� ��������� ��� �������:\n";
    for (int row = 0; row < size; ++row)
    {
        for (int col = 0; col < size; ++col) {
            cout << "������� [" << row << "][" << col << "]: ";
            cin >> elem;
            while (!cin) {
                std::cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "������� ������������ ��������. ��������� ����.\n";
                cout << "������� [" << row << "][" << col << "]: ";
                cin >> elem;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            mat[row][col] = elem;
        }
    }
}

void showHint()
{
    cout << "0 - ��������� ������� � ����������\n";
    cout << "1 - ��������� ������� ���������� �������\n";
    cout << "2 - ������� ������� �� �����\n";
    cout << "3 - �������� ���������� �����, �� ���������� �� ������ �������� ��������\n";
    cout << "4 - �������� ������������ �� �����, ������������� ������� ����� ������ ����\n";
    cout << "5 - �������� ��� �������\n";
    cout << "6 - �����\n";
}