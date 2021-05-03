#include "Hash.h"
#include <cmath>

void Hash::insert(const char* key, const int& value)
{
    //���� �������� ������������ ������ �������, �������� �� ������ 
    //����� ���������� �� �����������, ��� ���� ����-�������� ������� � �������
    //if (m_size > m_capacity * 0.4) resize();
    
    //������� ���-�������
    unsigned int seg = hashFunction(key);
    //���� ���������� ������� �� �� ��������� �������
    for (int i = 0; seg < m_capacity; ++i) {
        //������� ���������� ��������� � ��������
        ++m_elements[seg].m_segCalcCount;
        //���� ������� ����� ����� �� ���� ��� ������������ � �������
        if (!std::strcmp(m_elements[seg].m_key, key)) {
            //�������� �������� �� ������� ������
            m_elements[seg].m_val = value;
            return;
        }
        //���� ������� �� ����������� ������ ���� ��� ������
        else if (!std::strcmp(m_elements[seg].m_key, deletedSegment) ||
            !std::strcmp(m_elements[seg].m_key, emptySegment)) {
            //�������� ����� ������� � �������
            m_elements[seg].m_val = value;
            std::strcpy(m_elements[seg].m_key, key);
            ++m_size;
            return;
        }
        else
            //������� ������� ������������� ����������� ��� ��������� ������ ������
            quadTesting(i, seg);
    }
    //���������� ������� �� ��������� �������
    //���������� �������� ����������� ������ �������, ���� ���� �� ����� �������� � �������
    //��� �����������, ��� ���� ����� �������� � �������
    resize();
    insert(key, value);
}

//� ���� ������� ������ ������������ operator[] ��� ������ �������� �� �����
//��� ��� ��� ���������� ����� � ������� ������� ��� ����� �������� ��������
//� ����� ��� ��������� ��� �� ����������� (���� � ����� ����������� ����� �������, �� ���
//�������� ���. ��� ����� � ���������
bool Hash::erase(const char* key)
{
    //������� ��� �������
    unsigned int seg = hashFunction(key);
    //���� ���������� ������� �� �� ��������� �������
    for (int i = 0; seg < m_capacity; ++i) {
        //���� ���� �� ����������� �������� ����� ����� ���������� � �������
        if (!std::strcmp(key, m_elements[seg].m_key)) {
            //�������� ��� ��� ���������
            std::strcpy(m_elements[seg].m_key, deletedSegment);
            m_elements[seg].m_segCalcCount = 0;
            --m_size;
            return true;
        }
        else
            //������� ������� ������������� �����������
            quadTesting(i, seg);
    }
    //���������� ������� �� ��������� �������. 
    //������� �������� ��� � �������
    return false;
}

bool Hash::erase(const unsigned int seg)
{
    //���� ������� �� ��������� ������� - �������� ����� �������������� ���������
    if (seg >= m_capacity) {
        std::cout << "������� ��������� � ��������������� ��������\n";
        return false;
    }
    //���� ������� �� �������� ��� ������ - �������� �� ����� ������
    else if (!std::strcmp(m_elements[seg].m_key, deletedSegment) ||
        !std::strcmp(m_elements[seg].m_key, emptySegment)) {
        return false;
    }
    //�����, �������� ������� �� �������� ��� ���������
    return erase(m_elements[seg].m_key);
}

void Hash::clear()
{
    //��� � erase ������ ��� ���� ��������� �������
    for (unsigned int i = 0; i < m_capacity; ++i) {
        if (std::strcmp(m_elements[i].m_key, deletedSegment) && 
            std::strcmp(m_elements[i].m_key, emptySegment)) {
            std::strcpy(m_elements[i].m_key, deletedSegment);
            m_elements[i].m_segCalcCount = 0;
            --m_size;
        }
    }
    //������� ������ ������� � �������� ���������
    //����� ����� ������ ������� insert ������ ��������� ������ �������
    m_capacity = 3000;
    delete[] m_elements;
    m_elements = new Data[m_capacity];
    m_multiCoef = static_cast<unsigned int>(m_capacity / 102);
}

int Hash::operator[](const char* key) const
{    
    //������� ���-�������
    unsigned int seg = hashFunction(key);
    //���� ���������� ������� �� �� ��������� �������
    for (int i = 0; seg < m_capacity; ++i) {
        //���� �� �������� ����� ��� �� ����, ��� � ������������ � �������
        if (!std::strcmp(m_elements[seg].m_key, key)) {
            //������� ��������
            return m_elements[seg].m_val;
        }
        //���� ������� �� ����������� �������� ���� ��� ������
        else {
            //������� ������� ������������� ������������ ��� ��������� ������ ������
            quadTesting(i, seg);
            continue;
        }
    }
    //���������� ������� �� ��������� �������.
    //������ ����� � ������� ���
    //! ����� ������� out of range, �� ����� ������ ���
    std::cout << "���� " << key << " �� ������\n";
    return m_elements[0].m_val;
}

int Hash::operator[](const unsigned int seg) const
{
    //���� ������� �� ��������� ������� - �������� ����� �������������� ���������
    //! ����� ������� out of range, �� ����� ������ ���
    if (seg > m_capacity) {
        std::cout << "��������� � ��������������� �������� ���-�������\n";
        return m_elements[0].m_val;
    }

    return m_elements[seg].m_val;
}

void Hash::keys(char(*keysStorage)[7]) const
{
    //�������� ��� �����, �� ���������� ��� ��������� ��� ������ � keysStorage
    for (unsigned int i = 0, j = 0; i < m_capacity; ++i) {
        if (std::strcmp(m_elements[i].m_key, emptySegment) &&
            std::strcmp(m_elements[i].m_key, deletedSegment)) {
            std::strcpy(keysStorage[j], m_elements[i].m_key);
            ++j;
        }
    }
}

bool Hash::hasKey(const char* key) const
{
    for (unsigned int i = 0; i < m_capacity; ++i)
        if (!std::strcmp(key, m_elements[i].m_key))
            return true;
  
    return false;
}

bool Hash::testDataFile(const char* fileName) const
{
    //���������� � ���� ���������� ��������� � ������� ��������
    std::ofstream ofs;
    ofs.open(fileName);
    if (!ofs.is_open()) {
        ofs.clear();
        return false;
    }
    for (unsigned int i = 0; i < m_capacity; ++i)
        ofs << m_elements[i].m_segCalcCount << '\n';
    ofs.close();
    return true;
}

void Hash::resize(unsigned int size)
{
    unsigned int newCapacity = static_cast<unsigned int>(m_capacity * 1.5);

    //��������� ��������� ��������� ��������� �������
    //��� �� �������� ���������� � ��� ���������
    Data* temp = new Data[newCapacity];
    for (unsigned int i = 0; i < m_capacity; ++i) {
        std::strcpy(temp[i].m_key, m_elements[i].m_key);
        temp[i].m_val = m_elements[i].m_val;
    }
    //��������� ������ ������� � ��������� ����� ������ �������
    delete[] m_elements;
    m_elements = new Data[newCapacity];
    //������� ������� � ������������ ������
    //�� ���������� ���������. ����� ���������� �����
    m_capacity = newCapacity;
    m_size = 0;
    for (unsigned int i = 0; i < newCapacity; ++i) {
        if (std::strcmp(temp[i].m_key, deletedSegment) &&
            std::strcmp(temp[i].m_key, emptySegment))
            insert(temp[i].m_key, temp[i].m_val);
    }
    delete[] temp;
}

unsigned int Hash::hashFunction(const char* key) const
{
    unsigned int seg = 0;
    //��� ������� ������� �����
    for (int i = 0; key[i] != '\0'; ++i)
        //��������� ��� ������� � 3 ������� � ����� �����
        seg += static_cast<unsigned int>(std::pow(key[i], 3));
    return ((seg - 339) * m_multiCoef) % (m_capacity);
}
