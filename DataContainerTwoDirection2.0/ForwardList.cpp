#include"ForwardList.h"

//FORWARDLIST
template<typename T>
typename ForwardList<T>::Iterator ForwardList<T>::begin()
{
	return Head;
}
template<typename T>
typename ForwardList<T>::Iterator ForwardList<T>::end()
{
	return nullptr;
}
template<typename T>
typename ForwardList<T>::ConstIterator ForwardList<T>::cbegin()const
{
	return Head;
}
template<typename T>
typename ForwardList<T>::ConstIterator ForwardList<T>::cend()const
{
	return nullptr;
}
template<typename T>
typename ForwardList<T>::ReverseIterator ForwardList<T>::rbegin()
{
	return Tail;
}
template<typename T>
typename ForwardList<T>::ReverseIterator ForwardList<T>::rend()
{
	return nullptr;
}
template<typename T>
typename ForwardList<T>::ConstReverseIterator ForwardList<T>::crbegin()const
{
	return Tail;
}
template<typename T>
typename ForwardList<T>::ConstReverseIterator ForwardList<T>::crend()const
{
	return nullptr;
}

template<typename T>
ForwardList<T>::ForwardList()
{
	Head = Tail = nullptr;
	size = 0;
#ifdef DEBUG
	cout << "Fconstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>
ForwardList<T>::ForwardList(const std::initializer_list<T>& il) :ForwardList()
{
	for (int const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template<typename T>
ForwardList<T>::ForwardList(const ForwardList<T>& other) :ForwardList()
{
	//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)this->push_back(Temp->Data);
	*this = other;
	cout << "FCopyConstructor:\t" << this << endl;
}
template<typename T>
ForwardList<T>::~ForwardList()
{
#ifdef DEBUG
	while (Head)pop_front();
	cout << "FDestructor:\t" << this << endl;
#endif // DEBUG
}

//MODIFICATION
template<typename T>
void ForwardList<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	Head = Head->pPref = new Element(Data, Head);
	size++;
}
template<typename T>
void ForwardList<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)return push_front(Data);
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template<typename T>
void ForwardList<T>::pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size--;
		return;
	}
	Head = Head->pNext;
	delete Head->pPref;
	Head->pPref = nullptr;
	size--;
}
template<typename T>
void ForwardList<T>::pop_back()
{
	if (Head == Tail)return pop_front();
	Tail = Tail->pPref;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template<typename T>
void ForwardList<T>::insert(T Data, int Index)
{
	if (Index >= size)
	{
		cout << "Error: Выход за пределы списка!" << endl;
		return;
	}
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head; for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail; for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPref;
	}
	if (Temp == Head)
	{
		push_front(Data); return;
	}
	Temp->pPref->pNext = Temp = Temp->pPref = new Element(Data, Temp, Temp->pPref);
	size++;
}
template<typename T>
void ForwardList<T>::erase(int Index)
{
	if (Index >= size)
	{
		cout << "Error: Выход за пределы списка!" << endl;
		return;
	}
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head; for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail; for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPref;
	}
	if (Temp == Head)
	{
		pop_front(); return;
	}
	if (Temp == Tail)
	{
		pop_back(); return;
	}
	Temp->pPref->pNext = Temp->pNext;
	Temp->pNext->pPref = Temp->pPref;
	delete Temp;
}

//METHODS
template<typename T>
void ForwardList<T>::print()const
{
	cout << "Head: " << "\t" << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPref << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
	cout << "Tail: " << "\t" << Tail << endl;
	cout << "Количество элементов списка: " << size << endl;
}
template<typename T>
void ForwardList<T>::print_reverse()const
{
	cout << "Tail: " << "\t" << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPref)
		cout << Temp->pPref << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
	cout << "Head: " << "\t" << Head << endl;
	cout << "Количество элементов списка: " << size << endl;
}

//OPERATORS
template<typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& other)
{
	if (this == &other)return*this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)this->push_back(Temp->Data);
	cout << "FCopyAssignment:\t" << this << endl;
}

//ELEMENT
template <typename T>
ForwardList<T>::Element::Element(T Data, Element* pNext, Element* pPref)
	:Data(Data), pNext(pNext), pPref(pPref)
{
#ifdef DEBUG
	cout << "Econstructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T>
ForwardList<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
}

//BASE ITERATOR
template <typename T>
ForwardList<T>::BaseIterator::BaseIterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "IConstructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T>
ForwardList<T>::BaseIterator::~BaseIterator()
{
#ifdef DEBUG
	cout << "IDestructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T>
bool ForwardList<T>::BaseIterator::operator==(const BaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template <typename T>
bool ForwardList<T>::BaseIterator::operator!=(const BaseIterator& other)const
{
	return this->Temp != other.Temp;
}

template <typename T>
const int& ForwardList<T>::BaseIterator::operator*()const
{
	return Temp->Data;
}


//CONST OPERATOR
template <typename T>
ForwardList<T>::ConstIterator::ConstIterator(Element* Temp) :BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "IConstructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T>
ForwardList<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "IDestructor:\t" << this << endl;
#endif // DEBUG
}

template <typename T>
typename ForwardList<T>::ConstIterator& ForwardList<T>::ConstIterator::operator++()
{
	BaseIterator::Temp = BaseIterator::Temp->pNext; return *this;
}
template <typename T>
typename ForwardList<T>::ConstIterator ForwardList<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this; BaseIterator::Temp = BaseIterator::Temp->pNext; return old;
}
template <typename T>
typename ForwardList<T>::ConstIterator& ForwardList<T>::ConstIterator::operator--()
{
	BaseIterator::Temp = BaseIterator::Temp->pPref; return *this;
}
template <typename T>
typename ForwardList<T>::ConstIterator ForwardList<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this; BaseIterator::Temp = BaseIterator::Temp->pPref; return old;
}


//ITERATOR
template <typename T>
ForwardList<T>::Iterator::Iterator(Element* Temp) :ConstIterator(Temp) {}
template <typename T>
ForwardList<T>::Iterator::~Iterator() {}
template <typename T>
int& ForwardList<T>::Iterator::operator*()
{
	return BaseIterator::Temp->Data;
}


//CONSTREVERSITERATOR
template <typename T>
ForwardList<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RIConstructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T>
ForwardList<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "RIDestructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T>
typename ForwardList<T>::ConstReverseIterator& ForwardList<T>::ConstReverseIterator::operator++()
{
	BaseIterator::Temp = BaseIterator::Temp->pPref; return *this;
}
template <typename T>
typename ForwardList<T>::ConstReverseIterator ForwardList<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this; BaseIterator::Temp = BaseIterator::Temp->pPref; return old;
}
template <typename T>
typename ForwardList<T>::ConstReverseIterator& ForwardList<T>::ConstReverseIterator::operator--()
{
	BaseIterator::Temp = BaseIterator::Temp->pNext; return *this;
}
template <typename T>
typename ForwardList<T>::ConstReverseIterator ForwardList<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this; BaseIterator::Temp = BaseIterator::Temp->pNext; return old;
}


//REVERCEITERATOR
template <typename T>
ForwardList<T>::ReverseIterator::ReverseIterator(Element* Temp) :BaseIterator(Temp) {}
template <typename T>
ForwardList<T>::ReverseIterator::~ReverseIterator() {}
template <typename T>
int& ForwardList<T>::ReverseIterator::operator*()
{
	return BaseIterator::Temp->Data;
}