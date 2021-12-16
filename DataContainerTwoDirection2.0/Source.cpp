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
	ForwardList()
	{
		Head = Tail = nullptr;
		size = 0;
#ifdef DEBUG
		cout << "Fconstructor:\t" << this << endl;
#endif // DEBUG
	}
	~ForwardList()
	{
#ifdef DEBUG
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
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPref;
		}
		Element* New = new Element(Data);
		/*New->pNext = Temp;
		New->pPref = Temp->pPref;
		Temp->pPref->pNext = New;
		Temp->pPref = New;*/
		Temp->pPref->pNext = Temp = Temp->pPref = new Element(Data, Temp, Temp->pPref);
		//Temp->pPref = Temp->pPref->pNext = new Element(Data, Temp, Temp->pPref);
		size++;
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
};
void main()
{
	setlocale(LC_ALL, "rus");
	int n;
	cout << "Введите количество элементов списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	//list.print_reverse();

	//cout << endl;
	//list.pop_front();
	//list.print();
	////list.print_reverse();

	//cout << endl;
	//list.pop_back();
	//list.print();
	////list.print_reverse();

	int index;
	int value;
	cout << "Введите индекс: "; cin >> index;
	cout << "Введите значение: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.print_reverse();

}