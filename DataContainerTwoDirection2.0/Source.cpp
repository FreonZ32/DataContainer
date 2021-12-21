#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

//#define DEBUG

template<typename T>
class ForwardList
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPref;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPref = nullptr)
			:Data(Data), pNext(pNext), pPref(pPref)
		{
#ifdef DEBUG
			cout << "Econstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		friend class ForwardList;
	}*Head, * Tail;
	size_t size;
	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "IConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~BaseIterator()
		{
#ifdef DEBUG
			cout << "IDestructor:\t" << this << endl;
#endif // DEBUG
		}
		bool operator==(const BaseIterator& other)const
		{return this->Temp == other.Temp;}
		bool operator!=(const BaseIterator& other)const
		{return this->Temp != other.Temp;}

		const int& operator*()const
		{return Temp->Data;}
	};
public:
	class ConstIterator :public BaseIterator
	{
	public:
		ConstIterator(Element* Temp) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "IConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "IDestructor:\t" << this << endl;
#endif // DEBUG
		}

		ConstIterator& operator++()
		{BaseIterator::Temp = BaseIterator::Temp->pNext;return *this;}

		ConstIterator operator++(int)
		{ConstIterator old = *this; BaseIterator::Temp = BaseIterator::Temp->pNext;return old;}

		ConstIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPref;return *this;}

		ConstIterator operator--(int)
		{ConstIterator old = *this; BaseIterator::Temp = BaseIterator::Temp->pPref;return old;}
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp){}
		~Iterator(){}
		int& operator*()
		{return BaseIterator::Temp->Data;}
	};
	class ConstReverseIterator :public BaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RIConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "RIDestructor:\t" << this << endl;
#endif // DEBUG
		}
		ConstReverseIterator& operator++()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPref;return *this;}

		ConstReverseIterator operator++(int)
		{ConstReverseIterator old = *this; BaseIterator::Temp = BaseIterator::Temp->pPref; return old;}

		ConstReverseIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;return *this;}

		ConstReverseIterator operator--(int)
		{ConstReverseIterator old = *this; BaseIterator::Temp = BaseIterator::Temp->pNext;return old;}
	};
	class ReverseIterator :public BaseIterator
	{
	public:
		ReverseIterator(Element* Temp) :BaseIterator(Temp){}
		~ReverseIterator(){}
		int& operator*()
		{return BaseIterator::Temp->Data;}
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

template<typename T>
typename ForwardList<T>::Iterator ForwardList<T>::begin()
{return Head;}
template<typename T>
typename ForwardList<T>::Iterator ForwardList<T>::end()
{return nullptr;}
template<typename T>
typename ForwardList<T>::ConstIterator ForwardList<T>::cbegin()const
{return Head;}
template<typename T>
typename ForwardList<T>::ConstIterator ForwardList<T>::cend()const
{return nullptr;}
template<typename T>
typename ForwardList<T>::ReverseIterator ForwardList<T>::rbegin()
{return Tail;}
template<typename T>
typename ForwardList<T>::ReverseIterator ForwardList<T>::rend()
{return nullptr;}
template<typename T>
typename ForwardList<T>::ConstReverseIterator ForwardList<T>::crbegin()const
{return Tail;}
template<typename T>
typename ForwardList<T>::ConstReverseIterator ForwardList<T>::crend()const
{return nullptr;}

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

template<typename T>
void print_list(const ForwardList<T>& list)
{
	for (typename ForwardList<T>::ConstIterator it = list.cbegin(); it != list.cend(); ++it)
	{cout << *it << "\t";}
	cout << endl;
}

template<typename T>
void reverse_print_list(const ForwardList<T>& list)
{
	for (typename ForwardList<T>::ConstReverseIterator rit = list.crbegin(); rit != list.crend(); ++rit)
	{cout << *rit << "\t";}
	cout << endl;
}

//#define MODIFICATE
//#define ITERATOR_CHECK


void main()
{
	setlocale(LC_ALL, "rus");
#ifdef MODIFICATE
	int n;
	cout << "Введите количество элементов списка: "; cin >> n;
	ForwardList<int> list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.print_reverse();

	cout << endl;
	list.pop_front();
	list.print();
	//list.print_reverse();

	cout << endl;
	list.pop_back();
	list.print();
	//list.print_reverse();

	int index;
	int value;
	cout << "Введите индекс: "; cin >> index;
	cout << "Введите значение: "; cin >> value;
	list.insert(value, index);
	list.print();
	//list.print_reverse();

	cout << "Введите индекс: "; cin >> index;
	list.erase(index);
	list.print();
	//list.print_reverse();
#endif // MODIFICATE

#ifdef ITERATOR_CHECK
	ForwardList<int> list = { 3,5,8,13,21 };
	list.print();

	ForwardList list1;
	list1 = list;
	list.print();
	for (int i : list1)cout << i << "\t";
	cout << endl;

	for (ForwardList::ReverseIterator rit = list.rbegin(); rit != list.rend(); ++rit)cout << *rit << "\t";
	cout << endl;
#endif // ITERATOR_CHECK

	ForwardList<int> list = { 3,5,8,13,21 };
	print_list(list);
	cout << endl;
	reverse_print_list(list);
}