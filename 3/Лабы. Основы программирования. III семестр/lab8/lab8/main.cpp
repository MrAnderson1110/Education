#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

//определения функций
void showHint();
short getCommand();
void setFileName(char* inFile, char* outFile, size_t nameSize);
void readWrite(const char* inFile, const char* outFile);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Лабораторная работа №6.\nОбработка числовых матриц.\nВариант " << (1 - 1) % 20 + 1 << endl;

    short command = -1;
    const size_t fileNameSize = 100;
    char inFile[fileNameSize]{};
    char outFile[fileNameSize]{};

    do {
        command = getCommand();
        switch (command)
        {
        case 0:
            setFileName(inFile, outFile, fileNameSize);
            break;
        case 1:
            readWrite(inFile, outFile);
            break;
        case 2:
            showHint();
            break;
        case 3:
            break;
        default:
            cout << "Неизвестная команда\n";
            break;
        }
    } while (command != 3);

    return 0;
}

short getCommand()
{
#undef max
    short com;
    cout << "Введите команду для продолжения (2 - показать все команды): ";
    cin >> com;
    while (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Введите корректное значение (3 для выхода): ";
        cin >> com;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return com;
#define max
}

void setFileName(char* inFile, char* outFile, size_t nameSize)
{
#undef max
    cout << "Введите полный путь к входному файлу (до 100 символов): ";
    cin.getline(inFile, nameSize);
    cout << "Введите полный путь к выходному файлу (до 100 символов): ";
    cin.getline(outFile, nameSize);
#define max
}

void readWrite(const char* inFile, const char* outFile)
{
    fstream fs;
    fs.open(inFile, ios_base::in);
    if (!fs.is_open()) {
        cerr << "Невозможно открыть файл " << inFile << " для чтения\n";
        return;
    }
    char string[3][1000]{};
    for (int count = 0; count < 3;) {
        for (int i = 0; i < 1000 && !fs.eof(); ++i) {
            fs.get(string[count][i]);
            if (string[count][i] == '.') {
                ++count;
                break;
            }
        }
    }
    fs.close();
    fs.open(outFile, ios_base::out);
    if(!fs.is_open()) {
        cerr << "Невозможно открыть файл " << outFile << " для записи\n";
        return;
    }
    for (int i = 2; !(i < 0); --i) 
        fs << string[i];
    fs.close();
}

void showHint()
{
    cout << "0 - Ввести имена файлов\n";
    cout << "1 - Запустить функцию чтения - записи\n";
    cout << "2 - Показать все команды\n";
    cout << "3 - Выход\n";
}