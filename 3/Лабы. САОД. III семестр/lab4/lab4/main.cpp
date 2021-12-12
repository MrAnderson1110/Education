/*
* проверка на утечки памяти
* #define _CRTDBG_MAP_ALLOC
* #include <cstdlib>
* #include <crtdbg.h>
* #define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
* #define new DBG_NEW
* _CrtDumpMemoryLeaks();

//C:\Users\MrAnderson\Desktop\keysFile.txt
//C:\Users\MrAnderson\Desktop\testFile.txt
*/

/* Вариант 7
 * Составить хеш-функцию в соответствии с заданным вариантом и проанализировать ее. При необходимости доработать хеш-функцию.
 * Используя полученную хеш-функцию разработать на языке программирования высокого уровня программу, которая должна выполнять следующие функции:
 *
 *  создавать хеш-таблицу;
 *  добавлять элементы в хеш-таблицу;
 *  просматривать хеш-таблицу;
 *  искать элементы в хеш-таблице по номеру сегмента/по ключу;
 *  выгружать содержимое хеш-таблицы в файл для построения гистограммы в MS Excel, или в аналогичном подходящем ПО;
 *  удалять элементы из хеш-таблицы;
 *  в программе должна быть реализована проверка формата вводимого ключа;
 *  при удалении элементов из хэш-таблицы, в программе должен быть реализован алгоритм, позволяющий искать элементы, вызвавшие коллизию с удаленным;
 *  в программе должен быть реализован алгоритм, обрабатывающий ситуации с переполнением хэш-таблицы.
 *
 * Метод разрешения коллизий выбрать в соответствии с заданным вариантом.
 * Формат ключа: БцццББ
 * Количество сегментов: 3000
 * Метод хеширования: Квадратичное опробывание
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Hash.h"

using namespace std;

const int quantOfKeys = 9000;

short getCommand();
void saveKeysGenToFile();
void saveKeysGenToTable(Hash& h);
void __keysGen(char(*keysContainer)[7], const int size);
void createTableFromFile(Hash& h);
void addElementToTable(Hash& h);
void deleteElementByKey(Hash& h);
void deleteElementBySegment(Hash& h);
void clearTable(Hash& h);
void showTable(const Hash& h);
void findElementByKey(const Hash& h);
void findElementBySegment(const Hash& h);
void getTableAsFile(const Hash& h);
void showHint();
bool __getAndCheckKey(char* key);
void getTestDataFile(const Hash& h);

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная №4.\nХеширование данных.\nВариант " << (81 % 25) + 1 << "\n\n";
    short command = -1;

    Hash hashTable;
    do {
        command = getCommand();
        switch (command)
        {
        case 0:
            createTableFromFile(hashTable);
            break;
        case 1:
            saveKeysGenToFile();
            break;
        case 2:
            saveKeysGenToTable(hashTable);
            break;
        case 3:
            addElementToTable(hashTable);
            break;
        case 4:
            deleteElementByKey(hashTable);
            break;
        case 5:
            deleteElementBySegment(hashTable);
            break;
        case 6:
            clearTable(hashTable);
            break;
        case 7:
            findElementByKey(hashTable);
            break;
        case 8:
            findElementBySegment(hashTable);
            break;
        case 9:
            getTableAsFile(hashTable);
            break;
        case 10:
            showTable(hashTable);
            break;
        case 11:
            showHint();
            break;
        case 12:
            break;
        case 13:
            getTestDataFile(hashTable);
            break;
        case 14: {
            char(*keys)[7] = new char[quantOfKeys][7];
            hashTable.keys(keys);
            for (int i = 0; i < quantOfKeys; ++i) {
                cout << "ключ: " << keys[i] << " значение: " << hashTable[keys[i]] << '\n' ;
            }
            break;
        }
        default:
            cout << "Неизвестная команда\n";
            break;
        }
    } while (command != 12);

    return 0;
}

short getCommand()
{
    short com;
    cout << "Введите команду для продолжения (11 - показать все команды): ";
    cin >> com;
    while (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Введите коректной значение (12 для выхода):";
        cin >> com;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return com;
}

void saveKeysGenToFile()
{
    const int fileLength = 100;
    cout << "Введите полный путь к файлу (до " << fileLength << " символов): ";
    char filePath[fileLength];
    int i = 0;
    for (i; i < fileLength && cin.peek() != '\n'; ++i) {
        cin >> filePath[i];
    }
    filePath[i] = '\0';
    ofstream ofs;
    ofs.open(filePath);
    if (!ofs.is_open()) {
        cout << "Невозможно открыть файл " << filePath << '\n';
        ofs.clear();
        return;
    }

    char(*keys)[7] = new char[quantOfKeys][7];
    __keysGen(keys, quantOfKeys);
    for (int i = 0; i < quantOfKeys; ++i) {
        ofs << keys[i] << '\n';
    }
    ofs.close();
    delete[] keys;
}

void saveKeysGenToTable(Hash& h)
{
    char(*keys)[7] = new char[quantOfKeys][7];
    __keysGen(keys, quantOfKeys);
    srand(clock());
    int badKeyOnGen = 0;
    for (int i = 0; i < quantOfKeys; ++i) {
        if (h.hasKey(keys[i])) {
            ++badKeyOnGen;
            continue;
        }
        h.insert(keys[i], rand() % 1000);
    }
    cout << "Сгенерированно " << quantOfKeys - badKeyOnGen << " уникальных ключей\n";
    delete[] keys;
}

void __keysGen(char(*keysContainer)[7], const int size)
{
    srand(clock());
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < 7; ++j) {
            switch (j)
            {
            case 0:
            case 4:
            case 5:
                keysContainer[i][j] = static_cast<char>(rand() % 25 + 65);
                break;
            case 1:
            case 2:
            case 3:
                keysContainer[i][j] = static_cast<char>(rand() % 10 + 48);
                break;
            case 6:
                keysContainer[i][j] = '\0';
            default:
                break;
            }
        }
    }
}

void createTableFromFile(Hash& h)
{
    const int fileLength = 100;
    cout << "Введите полный путь к файлу (до " << fileLength << " символов): ";
    char filePath[fileLength];
    int i = 0;
    for (i; i < fileLength && cin.peek() != '\n'; ++i) {
        cin >> filePath[i];
    }
    filePath[i] = '\0';

    ifstream ifs;
    ifs.open(filePath);
    if (!ifs.is_open()) {
        cout << "Невозможно открыть файл " << filePath << '\n';
        ifs.clear();
        return;
    }
    char key[7]{};
    srand(clock());
    while (!ifs.eof())
    {
        ifs >> key;
        if (key[0] == '\0')
            continue;
        h.insert(key, rand()%1000);
    }

    ifs.close();
}

void addElementToTable(Hash& h)
{
    cout << "Введите пару ключ - значение через пробел: ";
    char key[7];
    int val = 0;
    if (!__getAndCheckKey(key)) {
        cout << "Неверный формат ключа\n";
        std::cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (cin.peek() != ' ') {
        cout << "Неверный формат ключа\n";
        std::cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    std::cin >> val;
    if (!std::cin) {
        cout << "Неверный формат ключа\n";
        std::cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    h.insert(key, val);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void deleteElementByKey(Hash& h)
{
    cout << "Введите ключ: ";
    char key[7]{};
    if (!__getAndCheckKey(key)) {
        cout << "Неверный формат ключа\n";
        std::cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if(!h.erase(key)) cout << "Не удалось удалить элемент\n";
}

void deleteElementBySegment(Hash& h)
{
    cout << "Введите номер сегмента: ";
    int seg = 0;
    cin >> seg;
    if (!std::cin) {
        cout << "Ошибка ввода\n";
        std::cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (!h.erase(seg)) cout << "Не удалось удалить элемент\n";
}

void clearTable(Hash& h)
{
    h.clear();
}

void showTable(const Hash& h)
{
    if (h.size() == 0)
        cout << "Таблица пуста\n";
    char(*keys)[7] = new char[h.size()][7]{};
    h.keys(keys);
    for (int i = 0; i < h.size(); ++i)
        cout << "Ключ: " << keys[i] << " значение: " << h[keys[i]] << '\n';
    delete[] keys;
}

void findElementByKey(const Hash& h)
{
    cout << "Введите ключ: ";
    char key[7]{};
    if (!__getAndCheckKey(key)) {
        cout << "Неверный формат ключа\n";
        std::cin.clear();
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cout << "Введенный ключ: " << key << " значение: " << h[key] << '\n';
}

void findElementBySegment(const Hash& h)
{
    cout << "Введите номер сегмента: ";
    int seg = 0;
    cin >> seg;
    if (!std::cin) {
        cout << "Ошибка ввода\n";
        std::cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cout << "Ключ: " << h.key(seg) << " значение: " << h[seg] << '\n';
}

void getTableAsFile(const Hash& h)
{
    const int fileLength = 100;
    cout << "Введите полный путь к файлу (до " << fileLength << " символов): ";
    char filePath[fileLength];
    int i = 0;
    for (i; i < fileLength && cin.peek() != '\n'; ++i) {
        cin >> filePath[i];
    }
    filePath[i] = '\0';

    ofstream ofs;
    ofs.open(filePath);
    if (!ofs.is_open()) {
        cout << "Невозможно открыть файл " << filePath << '\n';
        ofs.clear();
        return;
    }

    for (int i = 0; i < h.capacity(); ++i) 
        ofs << h.key(i) << " " << h[i] << '\n';

    ofs.close();
}

void showHint()
{
    cout << "0 - Создать хеш-таблицу из файла ключей со случайными числами\n";
    cout << "1 - Сгенерировать случайные ключи в файл\n";
    cout << "2 - Сгенерировать случайные ключи в хеш-таблицу со случайными числами\n";
    cout << "3 - Добавить новый элемент в хеш-таблицу\n";
    cout << "4 - Удалить элемент по ключу\n";
    cout << "5 - Удалить элемент по сегменту\n";
    cout << "6 - Очистить хеш-таблицу\n";
    cout << "7 - Найти элемент в хеш-таблице по ключу\n";
    cout << "8 - Найти элемент в хеш-таблицу по сегменту\n";
    cout << "9 - Выгрузить хеш-таблицу в файл\n";
    cout << "10 - Вывести хеш-таблицу на экран\n";
    cout << "11 - Показать все команды\n";
    cout << "12 - Выход\n";
    cout << "13 - Выгрузить тестовые данные в файл\n";
}

bool __getAndCheckKey(char* key)
{
    bool fineFlag = true;
    for (int i = 0; i < 6; ++i) {
        std::cin >> key[i];
        switch (i)
        {
        case 0:
        case 4:
        case 5:
            if (static_cast<int>(key[i]) < 65 ||
                static_cast<int>(key[i]) > 90) {
                fineFlag = false;
            }
            break;
        case 1:
        case 2:
        case 3:
            if (static_cast<int>(key[i]) < 48 ||
                static_cast<int>(key[i]) > 57) {
                fineFlag = false;
            }
            break;
        default:
            break;
        }
    }
    key[6] = '\0';
    return fineFlag;
}

void getTestDataFile(const Hash& h)
{
    const int fileLength = 100;
    cout << "Введите полный путь к файлу (до " << fileLength << " символов): ";
    char filePath[fileLength];
    int i = 0;
    for (i; i < fileLength && cin.peek() != '\n'; ++i) {
        cin >> filePath[i];
    }
    filePath[i] = '\0';

    if (!h.testDataFile(filePath)) {
        cout << "Невозможно открыть файл " << filePath << '\n';
        return;
    }
}
