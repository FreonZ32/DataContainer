#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define DEBUG

class ForwardList
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPref;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPref = nullptr)
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
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "IConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "IDestructor:\t" << this << endl;
#endif // DEBUG
		}

		Iterator& operator++()
		{Temp = Temp->pNext;return *this;}

		Iterator operator++(int)
		{Iterator old = *this;Temp = Temp->pNext;return old;}

		Iterator& operator--()
		{Temp = Temp->pPref;return *this;}

		Iterator operator--(int)
		{Iterator old = *this;Temp = Temp->pPref;return old;}

		bool operator==(const Iterator& other)const
		{return this->Temp == other.Temp;}
		bool operator!=(const Iterator& other)const
		{return this->Temp != other.Temp;}

		const int& operator*()const
		{return Temp->Data;}
		int& operator*()
		{return Temp->Data;}
	};
	class ReverseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "RIConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ReverseIterator()
		{
#ifdef DEBUG
			cout << "RIDestructor:\t" << this << endl;
#endif // DEBUG
		}

		ReverseIterator& operator++()
		{Temp = Temp->pPref;return *this;}
		ReverseIterator operator++(int)
		{ReverseIterator old = *this; Temp = Temp->pPref; return old;}
		ReverseIterator& operator--()
		{Temp = Temp->pNext;return *this;}
		ReverseIterator operator--(int)
		{ReverseIterator old = *this; Temp = Temp->pNext;return old;}

		bool operator==(const ReverseIterator& other)const
		{return this->Temp == other.Temp;}
		bool operator!=(const ReverseIterator& other)const
		{return this->Temp != other.Temp;}

		const int& operator*()const
		{return Temp->Data;}
		int& operator*()
		{return Temp->Data;}
	};
	Iterator begin()
	{return Head;}
	Iterator end()
	{return nullptr;}

	ReverseIterator rbegin()
	{return Tail;}
	ReverseIterator rend()
	{return nullptr;}

	ForwardList()
	{
		Head = Tail = nullptr;
		size = 0;
#ifdef DEBUG
		cout << "Fconstructor:\t" << this << endl;
#endif // DEBUG
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{push_back(*it);}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)this->push_back(Temp->Data);
		*this = other;
		cout << "FCopyConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
#ifdef DEBUG
		while (Head)pop_front();
		cout << "FDestructor:\t" << this << endl;
#endif // DEBUG
	}

	//MODIFICATION
	void push_front(int Data)
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
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}

	void pop_front()
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
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPref;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	void insert(int Data, int Index)
	{
		if (Index >= size)
		{
			cout << "Error: Выход за пределы списка!" << endl;
			return;
		}
		Element* Temp;
		if (Index < size / 2)
		{Temp = Head;for (int i = 0; i < Index; i++)Temp = Temp->pNext;}
		else
		{Temp = Tail;for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPref;}
		if (Temp == Head) 
		{push_front(Data); return;}
		Temp->pPref->pNext = Temp = Temp->pPref = new Element(Data, Temp, Temp->pPref);
		size++;
	}
	void erase(int Index)
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
		{pop_front(); return;}
		if (Temp == Tail)
		{pop_back(); return;}
		Temp->pPref->pNext = Temp->pNext;
		Temp->pNext->pPref = Temp->pPref;
		delete Temp;
	}

	//METHODS
	void print()const
	{
		cout << "Head: " << "\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPref << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << "Tail: " << "\t" << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void print_reverse()const
	{
		cout << "Tail: " << "\t" << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPref)
			cout << Temp->pPref << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << "Head: " << "\t" << Head << endl;
		cout << "Количество элементов списка: " << size << endl;
	}

	//OPERATORS
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return* this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)this->push_back(Temp->Data);
		cout << "FCopyAssignment:\t" << this << endl;
	}
};

//#define MODIFICATE
//#define ITERATOR_CHECK

void main()
{
	setlocale(LC_ALL, "rus");
#ifdef MODIFICATE
	int n;
	cout << "Введите количество элементов списка: "; cin >> n;
	ForwardList list;
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
	ForwardList list = { 3,5,8,13,21 };
	list.print();

	ForwardList list1;
	list1 = list;
	list.print();
	for (int i : list1)cout << i << "\t";
	cout << endl;

	for (ForwardList::ReverseIterator rit = list.rbegin(); rit != list.rend(); ++rit)cout << *rit << "\t";
	cout << endl;
#endif // ITERATOR_CHECK

	cout << "ssssss";
}