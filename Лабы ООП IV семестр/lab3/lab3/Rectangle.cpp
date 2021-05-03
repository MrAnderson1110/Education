#include "Rectangle.h"
#include <algorithm>
#include <iostream>

Rectangle Rectangle::operator*(const Rectangle& other) const
{
    int leftX = std::max(m_x, other.m_x);
    int topY = std::max(m_y, other.m_y);
    int bottomY = std::max(m_y - m_height, other.m_y - other.m_height);
    int rightX = std::min(m_x + m_width, other.m_x + other.m_width);

    if (rightX < leftX || bottomY > topY)
        return Rectangle();

    int intersectionWidth = rightX - leftX;
    int intersectionHeight = topY - bottomY;

    return Rectangle(leftX, topY, intersectionWidth, intersectionHeight);
}

bool Rectangle::operator==(const Rectangle& other) const
{
    return this->operator()() == other();
}

bool Rectangle::operator!=(const Rectangle& other) const
{
    return !this->operator==(other);
}

bool Rectangle::operator<(const Rectangle& other) const
{
    return !(this->operator>(other)) && (this->operator!=(other));
}

bool Rectangle::operator>(const Rectangle& other) const
{
    return this->operator()() > other();
}

int Rectangle::operator()() const
{
    return m_height * m_width;
}

Rectangle::Rectangle()
    : m_x(0)
    , m_y(0)
    , m_width(0)
    , m_height(0)
{
}

Rectangle::Rectangle(int x, int y, int width, int height)
    : m_x(x)
    , m_y(y)
    , m_width(0)
    , m_height(0)
{
    setHeight(height);
    setWidth(width);
}

Rectangle::~Rectangle()
{
}

int Rectangle::width() const
{
    return m_width;
}

int Rectangle::height() const
{
    return m_height;
}

int Rectangle::x() const
{
    return m_x;
}

int Rectangle::y() const
{
    return m_y;
}

void Rectangle::setWidth(int w)
{
    if (w < 0) {
        std::cerr << "width cannot be less than nothing\n";
        return;
    }
    m_width = w;
}

void Rectangle::setHeight(int h)
{
    if (h < 0) {
        std::cerr << "height cannot be less than nothing\n";
        return;
    }
    m_height = h;
}

void Rectangle::setX(int x)
{
    m_x = x;
}

void Rectangle::setY(int y)
{
    m_y = y;
}
