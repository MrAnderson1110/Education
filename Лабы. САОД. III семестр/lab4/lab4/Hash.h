#ifndef HASH_H
#define HASH_H

#include <cstdlib>
#include <iostream>
#include <fstream>

const char deletedSegment[7] = "*****\0";
const char emptySegment[7] = "     \0";

class Hash
{
public:
    Hash()
        : m_elements(new Data[m_capacity])
        , m_size(0)
        , m_capacity(3000)
        , m_multiCoef(m_capacity / 102) {}
    ~Hash() { delete[] m_elements; }
    //������� �������� value �� ����� key
    void insert(const char* key, const int& value); 
    //�������� �������� �� ����� key
    bool erase(const char* key); 
    //������������� �����. �������� �� ������ ��������
    bool erase(const unsigned int seg);
    //������ ������� �������
    void clear();
    //��������� �������� �� �����
    int operator[](const char* key) const;
    //��������� �������� �� ��������
    int operator[](const unsigned int seg) const;
    //��������� ��� ����� � ���������� ������
    void keys(char(*keysStorage)[7]) const;
    //��������� ����� �� ������ ��������
    char* key(const unsigned int seg) const { return m_elements[seg].m_key; }
    //�������� �� ������� ���������� ����
    bool hasKey(const char* key) const;
    //�������� ������ �������
    int size() const { return m_size; }
    //��������� ������ �������
    int capacity() const { return m_capacity; }
    bool testDataFile(const char *fileName) const;

private:
    //���������� ������������ ������� �������
    void resize(unsigned int size = 0);
    //���-�������
    unsigned int hashFunction(const char* key) const;
    //������� ������������� �����������
    void quadTesting(int tryNum, unsigned int& seg) const { seg += 1 * tryNum + 1 * tryNum * tryNum; }
    //��������� ��� �������� ������ �������� hash �������
    struct Data {
        //����������� �����������
        Data() : m_val(0), m_key(new char[7]), m_segCalcCount(0) { std::strcpy(m_key, emptySegment); }
        //����� ������ ������ ��� ��������
        ~Data() { delete[] m_key; }
        //���� �������� � �����
        int m_val;
        char* m_key;
        unsigned int m_segCalcCount;
    };
    //�������� ������ �������
    unsigned int m_size;
    //����������� ������ �������
    unsigned int m_capacity;
    //��������� ������� �������
    unsigned int m_multiCoef;

    //������ ���������
    Data* m_elements;
};

#endif // HASH_H
