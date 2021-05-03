#pragma once
#include <iostream>

template<typename T> class LinkList;
template<typename Node> class ListIterator;

//Шаблонный класс для хранения элементов и их указателей
template<typename T>
class node
{
public:
	using Value = typename T;

	node() : m_data(nullptr), m_next(nullptr), m_previous(nullptr) {}
	node(Value* data) 
		: m_data(data)
		, m_next(nullptr)
		, m_previous(nullptr) 
	{}
	node(Value* data, node* next, node* previous)
		: m_data(data)
		, m_next(next)
		, m_previous(previous) 
	{}

	~node() { delete m_data; }

	Value* data() const { return m_data; }
	node* next() const { return m_next; }
	node* previous() const { return m_previous; }

	void setData(Value* data) { m_data = data; }
	void setNext(node* next) { m_next = next; }
	void setPrevious(node* previous) { m_previous = previous; }

private:
	node* m_next;
	node* m_previous;
	Value* m_data;
};

//Класс итератора для упращения обхода элементов
template<typename Node>
class ListIterator
{
	using ValueType = typename Node::Value;
public:

	ListIterator(Node* data = nullptr) : m_ptr(data) {}

	ValueType& operator*() { return *m_ptr->data(); }
	ValueType* operator->() { return m_ptr->data(); }
	bool operator==(const ListIterator& rightIter) { return m_ptr == rightIter.m_ptr; }
	bool operator!=(const ListIterator& rightIter) { return !operator==(rightIter); }
	bool operator==(Node* rightPtr) { return m_ptr == rightPtr; }
	bool operator!=(Node* rightPtr) { return !operator==(rightPtr); }
	bool operator!() { return !m_ptr; }
	operator ValueType* () { return m_ptr->data(); }
	ListIterator operator++(int) 
	{
		if (!m_ptr->next())
			return *this;
		ListIterator temp = *this;
		++(*this);
		return temp;
	}
	ListIterator operator++() 
	{
		if (!m_ptr->next())
			return *this;
		m_ptr = m_ptr->next();
		return *this; 
	}
	ListIterator operator--()
	{
		if (!m_ptr)
			return *this;
		m_ptr = m_ptr->previous();
		return *this;
	}
	ListIterator operator--(int)
	{
		if (!m_ptr->previous())
			return *this;
		ListIterator temp = *this;
		--(*this);
		return temp;
	}

	//Чтобы не добавлять класс как дружественный в LinkList<T>, функция объявлена как public
	//Это избавляет от лишней зависимости и позволяет использовать итератор с другими списками
	Node* __getPtr() const { return m_ptr; }

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

	LinkList() : m_begin(nullptr), m_end(nullptr), m_size(0) {}
	LinkList(const LinkList<T>& li)
	{
		LinkList<T>::iterator it = li.begin();
		LinkList<T>::iterator thisIt = begin();
		while (it != li.end()) 
			insert(thisIt++, *it++);
	}
	~LinkList() 
	{ 
		clear(); 
		delete m_end;
	}

	int size() const { return m_size; }
	bool isEmpty() const { return !m_size; }
	iterator begin() const { return iterator(m_begin); }
	iterator end() const { return iterator(m_end); }

	LinkList<T>& operator=(const LinkList<T>& li)
	{
		if (this == &li)
			return *this;

		LinkList<T>::iterator it = li.begin();
		LinkList<T>::iterator thisIt = begin();
		while (it != li.end())
			insert(thisIt++, *it++);
		return *this;
	}
	bool operator==(const LinkList<T>& li)
	{
		if (li.size() != size())
			return false;

		LinkList<T>::iterator it = li.begin();
		LinkList<T>::iterator thisIt = begin();

		while (it != li.end()) 
			if (*it++ != *thisIt++)
				return false;

		return true;
	}
	/*
	* Вставляет элемент после итераторв pos
	* Возвращает итератор на вставленный элемент
	*/
	iterator insert(iterator pos, const T& elem)
	{
		//Вставка в пустой список
		if (!pos) {
			if (!isEmpty())
				return pos;
			m_begin = new Node(new T(elem), nullptr, nullptr);
			m_end = new Node(nullptr, nullptr, m_begin);
			m_begin->setNext(m_end);
			++m_size;
			return begin();
		}

		Node* posPtr = pos.__getPtr();
		//Вставка в конец списка
		if (posPtr->next() == m_end) {
			posPtr->setNext(new Node(new T(elem), m_end, posPtr));
			m_end->setPrevious(posPtr->next());
			++m_size;
			return end();
		}

		//Вставка нового элемена 
		posPtr->setNext(new Node(new T(elem), posPtr->next(), posPtr));
		++m_size;
		return iterator(posPtr->next());
	}
	/*
	* Вставляет элемент перед итератором pos
	* Возвращает итератор на вставленный элемент
	*/
	iterator insert_before(iterator pos, const T& elem) 
	{
		//Вставка в пустой список
		if (!pos) 
			return insert(pos, elem);
		
		if (pos != begin())
			return insert(iterator(pos.__getPtr()->previous()), elem);

		Node *newBegin = new Node(new T(elem), m_begin, nullptr);
		m_begin->setPrevious(newBegin);
		m_begin = newBegin;
		return iterator(newBegin);
	}
	/*
	* Удаляет элемент, на который указывает итератор pos
	* Возвращает итератор на элемент после удаляемого
	*/
	iterator erase(iterator pos)
	{
		if (pos == end())
			return pos;

		//Удаление первого элемента
		if (pos == begin()) {
			Node* newBegin = m_begin->next();
			newBegin->setPrevious(nullptr);
			delete m_begin;
			m_begin = newBegin;
			--m_size;
			return begin();
		}

		//удаление элемента
		Node* nextPtr = pos.__getPtr()->next();
		Node* prevPtr = pos.__getPtr()->previous();
		nextPtr->setPrevious(prevPtr);
		prevPtr->setNext(nextPtr);
		delete pos.__getPtr();
		--m_size;
		return iterator(nextPtr);
	}

	void clear()
	{
		iterator it = begin();
		while (!isEmpty())
			erase(it++);
	}
	/*
	* Линейный поиск элемента elem
	* Возвращает итератор на найденный элемент
	* Если такого элемента нет, возвращает итератор на начало списка
	*/
	iterator find(const T& elem)
	{
		if (isEmpty())
			return begin();

		if (elem == *begin())
			return begin();

		iterator it = begin();
		while (it != end()) {
			if(*it == elem)
				return it;
			++it;
		}
		return end();
	}
	/*
	* Сортирует списко в соответствии с флагом order
	* true - по возрастанию
	* false - по убыванию
	* Тип T должен быть простым или иметь прераторы сравнения
	* 
	* Выбрана сортировка перестановками, так как нет произвольного доступа к жлементам
	*/
	void sort() 
	{
		if (isEmpty())
			return;

		Node* ptr = m_begin;
		Node *cmpPtr = m_begin->next();
		while (ptr != m_end) {
			while (cmpPtr != m_end) {
				if (*ptr->data() > *cmpPtr->data()) {
					__swap(ptr, cmpPtr);
					ptr = cmpPtr;
				}
				cmpPtr = cmpPtr->next();
			}
			ptr = ptr->next();
			cmpPtr = ptr->next();
		}
	}

private:
	void __swap(Node* lPtr, Node* rPtr)
	{
		if (lPtr->next() == rPtr) {
			Node* tempNext = rPtr->next();
			Node* tempPrev = lPtr->previous();

			tempNext->setPrevious(lPtr);
			if (tempPrev) 
				tempPrev->setNext(rPtr);
			else
				m_begin = rPtr;

			rPtr->setNext(lPtr);
			rPtr->setPrevious(tempPrev);

			lPtr->setPrevious(rPtr);
			lPtr->setNext(tempNext);
			return;
		}

		Node* tempNext = rPtr->next();
		Node* tempPrev = rPtr->previous();

		tempNext->setPrevious(lPtr);
		tempPrev->setNext(lPtr);

		lPtr->next()->setPrevious(rPtr);
		if (lPtr->previous()) 
			lPtr->previous()->setNext(rPtr);
		else
			m_begin = rPtr;

		rPtr->setNext(lPtr->next());
		rPtr->setPrevious(lPtr->previous());

		lPtr->setNext(tempNext);
		lPtr->setPrevious(tempPrev);
	}

	Node* m_begin;
	Node* m_end;
	int m_size;
};