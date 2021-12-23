#pragma once
#include"Stdafx.h"

template<typename T>
class ForwardList
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPref;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPref = nullptr);
		~Element();

		friend class ForwardList;
	}*Head, * Tail;
	size_t size;

	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp);
		~BaseIterator();

		bool operator==(const BaseIterator& other)const;
		bool operator!=(const BaseIterator& other)const;

		const int& operator*()const;
	};
public:
	class ConstIterator :public BaseIterator
	{
	public:
		ConstIterator(Element* Temp);
		~ConstIterator();

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp);
		~Iterator();
		int& operator*();
	};
	class ConstReverseIterator :public BaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp);
		~ConstReverseIterator();

		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class ReverseIterator :public BaseIterator
	{
	public:
		ReverseIterator(Element* Temp);
		~ReverseIterator();
		int& operator*();
	};
	Iterator begin();
	Iterator end();

	ConstIterator cbegin()const;
	ConstIterator cend()const;

	ReverseIterator rbegin();
	ReverseIterator rend();

	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;

	ForwardList();
	ForwardList(const std::initializer_list<T>& il);
	ForwardList(const ForwardList<T>& other);
	~ForwardList();

	//MODIFICATION
	void push_front(T Data);
	void push_back(T Data);

	void pop_front();
	void pop_back();

	void insert(T Data, int Index);
	void erase(int Index);

	//METHODS
	void print()const;
	void print_reverse()const;

	//OPERATORS
	ForwardList<T>& operator=(const ForwardList<T>& other);
};
