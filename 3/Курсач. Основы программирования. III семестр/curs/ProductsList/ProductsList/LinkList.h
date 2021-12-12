#pragma once
#include <iostream>

template<typename T> class LinkList;
template<typename Node> class ListIterator;

template<typename T>
class node
{
public:
	using Value = typename T;

	node() : m_data(), m_next(this) {}
	node(Value* data) : m_data(data) { m_next = this; }
	node(Value* data, node* next) : m_data(data), m_next(next) {}

	~node() { delete m_data; }

	//getters
	node* next() const { return m_next; }
	Value* data() const { return m_data; }

	//setters
	void setData(Value* data) { m_data = data; }
	void setNext(node* next) { m_next = next; }

private:
	node* m_next;
	Value* m_data;
};

template<typename Node>
class ListIterator
{
	using ValueType = typename Node::Value;
public:

	//интерфейс пользователя
	explicit ListIterator(Node* data = nullptr) : m_ptr(data) {}

	ValueType operator*() { return *m_ptr->data(); }
	Node* operator->() { return m_ptr; }
	bool operator==(const ListIterator& rightIter) { return m_ptr == rightIter.m_ptr; }
	bool operator!=(const ListIterator& rightIter) { return m_ptr != rightIter.m_ptr; }
	bool operator==(Node* rightPtr) { return m_ptr == rightPtr; }
	bool operator!=(Node* rightPtr) { return m_ptr != rightPtr; }
	bool operator!() { return !m_ptr; }
	operator ValueType* () { return m_ptr->data(); }
	ListIterator operator++(int i) 
	{
		if (m_ptr == nullptr)
			return *this;

		ListIterator temp = *this;
		++(*this);
		return temp;
	}
	ListIterator operator++() 
	{
		if (m_ptr == nullptr) return *this;
		m_ptr = m_ptr->next();
		return *this; 
	}

	bool isValid() const { return m_ptr ? true : false; }

	//интерфейс для связанного списка
	Node* _getPtr() const { return m_ptr; }

private:

	Node* m_ptr;
};

template<typename T> 
class LinkList
{
	using Node = node<T>;
	friend class Node;
public:
	using iterator = ListIterator<Node>;

	LinkList() : m_begin(new Node(nullptr)), m_size(0) {}
	~LinkList()
	{
		clear();
	}

	int size() const { return m_size; }
	bool isEmpty() const { return !m_size; }
	iterator begin() const { return iterator(m_begin); }

	/*
	* Произовдит вставку в связанный список после элемента, на который указывает итератор pos
	* Возвращает итератор, указывающий на вставленный элемент
	*/
	iterator insert(iterator pos, const T& elem)
	{
		if (!m_begin->data()) {
			m_begin->setData(new T(elem));
			++m_size;
			return iterator(m_begin);
		}

		Node* iter = pos._getPtr();
		iter->setNext(new Node(new T(elem), iter->next()));
		++m_size;
		return iterator(iter->next());
	}

	/*
	* Производит удаление элемента следующего за тем, на который указывает итератор pos из списка
	* Возвращает итератор на элемент перед удаляемым
	* Передаваемы в функцию итератор становится невалидным
	*/
	iterator erase_after(iterator pos)
	{
		Node* iter = pos._getPtr();
		if (iter->next() == m_begin) {
			m_begin = m_begin->next();
		}

		Node* newNext = iter->next()->next();
		delete iter->next();
		iter->setNext(newNext);
		--m_size;
		return iterator(iter);
	}

	/*
	*  очищает связанный список
	*/
	void clear()
	{
		Node* iter = m_begin;
		while (!isEmpty()) {
			if (iter->next() == m_begin) {
				m_begin = m_begin->next();
			}

			Node* newNext = iter->next()->next();
			delete iter->next();
			iter->setNext(newNext);
			--m_size;
		}
	}

	/*
	* Производит поиск элемента elem в связанном списке
	* Возвращает итератор на найденный элемент, если элемент elem есть в списке
	* Иначе возвращает итератор на начало списка
	*/
	iterator find(T elem)
	{
		iterator beg = begin();
		iterator it = beg;
		while (++it != beg) {
			if(*it == elem)
				return it;
		}
		return beg;
	}
	/*
	* Перегруженная функция 
	* начинает поиск с элемента на который указывает иетратор pos
	* если елемент не найден возвращает переданный в функцию итератор
	*/
	iterator find(T elem, iterator pos)
	{
		iterator it = pos;
		while (++it != pos) {
			if (*it == elem)
				return it;
		}
		return pos;
	}

private:

	Node* m_begin;

	int m_size;
};

/*
* Выводит все элементы в списке начаная с начального в консоль
*/
void display_all(const LinkList<int> &li) 
{
	LinkList<int>::iterator it = li.begin();
	if (li.isEmpty()) {
		std::cout << "list is empty" << std::endl;
		return;
	}

	for(int i = 0; i < li.size(); ++i) {
		std::cout << "element " << i+1 << " = " << *it++ << std::endl;
	}
}
void display_all(const LinkList<double>& li)
{
	LinkList<double>::iterator it = li.begin();
	if (li.isEmpty()) {
		std::cout << "list is empty" << std::endl;
		return;
	}

	for (int i = 0; i < li.size(); ++i) {
		std::cout << "element N" << i + 1 << ": " << *it++ << std::endl;
	}
}