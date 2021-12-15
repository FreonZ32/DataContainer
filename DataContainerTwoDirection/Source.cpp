#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

//#define DEBUG

class Element
{
	int Data;
	Element* pPref;
	Element* pNext;
public:

	//CONSTRUCTORS
	Element(int Data, Element* pNext = nullptr, Element* pPref = nullptr)
	{
		this->Data = Data;
		this->pPref = pPref;
		this->pNext = pNext;
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
	friend class Iterator;
};

class Iterator
{
	Element* temp;
public:
	//CONSTRUCTORS
	Iterator(Element* Head = nullptr)
	{
		this->temp = Head;
#ifdef DEBUG
		cout << "Iconstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Iterator()
	{
#ifdef DEBUG
		cout << "IDestructor:\t" << this << endl;
#endif // DEBUG
	}

	//OPERATORS
	Iterator& operator++()
	{
		this->temp = temp->pNext;
		return *this;
	}
	Iterator operator++(int)
	{
		Element* buf = this->temp;
		this->temp = temp->pNext;
		return buf;
	}
	int& operator*()const
	{
		return temp->Data;
	}
	bool operator==(const Iterator& other)const
	{
		return this->temp == other.temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->temp != other.temp;
	}
	operator bool()const
	{
		return temp;
	}
};

class ForwardList
{
	Element* Head;
	Element* Tail;
	size_t size;
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return Tail;
	}
	//CONSTRUCTORS
	ForwardList()
	{
		this->size = 0;
		this->Head = nullptr;
		this->Tail = nullptr;
#ifdef DEBUG
		cout << "Fconstructor:\t" << this << endl;
#endif // DEBUG
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		for (const int* it = il.begin(); it != il.end(); push_back(*it), it++);
#ifdef DEBUG
		cout << "FListConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~ForwardList()
	{
		while (Head)pop_front();
#ifdef DEBUG
		cout << "FDestructor:\t" << this << endl;
#endif // DEBUG
	}

	//METHODS
	void push_front(int Data)
	{
		Element* New = new Element(Data,Head);
		Head = New;
		if (this->Tail == nullptr) { this->Tail = New; }
		else Head->pNext->pPref = Head;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Tail->pNext = new Element(Data,nullptr,Tail);
		Tail = Tail->pNext;
		size++;
	}
	void pop_front()
	{
		Element* Temp = Head;
		if (Head == nullptr)return;
		if (Head->pNext != nullptr)Head->pPref = nullptr;
		Head = Head->pNext;
		if (Head == nullptr)Tail = Head;
		delete Temp;
		size--;
	}
	void pop_back()
	{
		Element* tail = Tail;
		if (Tail == nullptr)return;
		if (Tail == Head) { Tail = nullptr; Head = nullptr; }
		else { tail->pPref->pNext = nullptr; Tail = tail->pPref; } 
		delete tail;
		size--;
	}
	void insert(int Data, unsigned int n)
	{
		if (n >= size) { cout << "Going beyond the list! " << endl; return; }
		if (n == 0 || Head == nullptr)return push_front(Data);
		if (n <= size / 2)
		{
			Element* Temp = Head;
			for (int i = 0; i < n - 1; i++)Temp = Temp->pNext;
			Temp->pNext = new Element(Data, Temp->pNext,Temp);
			Temp->pNext->pNext->pPref = Temp->pNext;
		}
		else
		{
			Element* tail = Tail;
			for (int i = 0; i < size - n-1; i++)tail = tail->pPref;
			tail->pPref = new Element(Data, tail, tail->pPref);
			tail->pPref->pPref->pNext = tail->pPref;
		}
		size++;
	}
	void print()
	{
		for (Element* Temp = Head; Temp != nullptr; Temp = Temp->pNext)
		{cout << Temp << "\t" << Temp->pPref << "\t" << Temp->Data << "\t" << Temp->pNext << endl;}

		/*for (Iterator Temp = Head; Temp;cout << *Temp << endl, Temp++)
		cout << endl;*/

		Element* head = Head;
		Element* tail = Tail;
		cout << "Size: " << size << "\t\t" << "Head: " << head << "\t" << "Tail: " << tail << endl;
	}
};

#define MODIFICATION_CHECK
//#define OPERATORS_AND_CONSTRUCTOSRS_CHECK

void main()
{
	setlocale(LC_ALL, "rus");

#ifdef MODIFICATION_CHECK
	ForwardList list;
	for (int i = 0; i < 8; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();

	cout << endl;
	list.push_back(100);
	list.print();

	cout << endl;
	list.push_front(100);
	list.print();

	cout << endl;
	list.pop_front();
	list.print();

	cout << endl;
	list.pop_front();
	list.print();

	cout << endl;
	list.pop_back();
	list.print();

	int n;
	cout << "Enter insertion point(from 0 position)?: "; cin >> n;
	list.insert(100, n);
	list.print();

#endif // MODIFICATION_CHECK

#ifdef OPERATORS_AND_CONSTRUCTOSRS_CHECK
	ForwardList list = { 3,5,8,13,21 };
	list.print();
#endif // OPERATORS_AND_CONSTRUCTOSRS_CHECK

}