#include "MyClass.h"

#include <set>
#include <algorithm>

std::ostream& operator<<(std::ostream& os, const MyClass& cl)
{
    if (cl.m_vec.size() == 0)
        os << "vector is empty";
    else
        for (auto val : cl.m_vec)
            os << val << ' ';
    os << '\n';
    return os;
}

MyClass::MyClass()
    : m_vec()
    , m_m1(-10)
    , m_m2(10)
{
    std::cout << *this;
}

void MyClass::fillRand()
{
    m_vec.clear();
    while (m_vec.size() < 30)
        m_vec.push_back(rand() % (m_m2 - m_m1) - (m_m2 - m_m1) / 2);
    std::cout << *this;
}

int MyClass::findMax()
{
    return *(std::max_element(m_vec.cbegin(), m_vec.cend()));
}

void MyClass::replace()
{
    std::replace_if(m_vec.begin(), m_vec.end(), [](auto val) {
        return val < 0;
        }, 0);
    std::cout << *this;
}

void MyClass::removeRepeats()
{
    int firstVal = *m_vec.begin();
    std::set<int> tempSet(m_vec.begin() + 1, m_vec.end());
    m_vec = std::vector<int>(tempSet.begin(), tempSet.end());
    m_vec.insert(m_vec.begin(), firstVal);
    std::cout << *this;
}
