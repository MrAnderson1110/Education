#pragma once

class Rectangle
{
	friend bool operator==(const Rectangle& left, const Rectangle& right);
	friend bool operator!=(const Rectangle& left, const Rectangle& right);
public:
	Rectangle();
	Rectangle(int x, int y, int width, int height);
	~Rectangle();

	int width() const;
	int height() const;
	int x() const;
	int y() const;

	void setWidth(int w);
	void setHeight(int h);
	void setX(int x);
	void setY(int y);

	Rectangle operator*(const Rectangle& other) const;
	bool operator<(const Rectangle& other) const;
	bool operator>(const Rectangle& other) const;
	int operator()() const;

private:
	//Левый верхний угол
	int m_x;
	int m_y;

	//Размеры
	int m_width;
	int m_height;
};

