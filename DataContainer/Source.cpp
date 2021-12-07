#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Element
{
	int Data;	//Значение элемента
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "Econstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;	//Указывает на начальный элемент списка
public:
	ForwardList()
	{
		this->Head = nullptr;	//Если голова указывает на 0 = список пуст
	cout << "Lconstructor:\t" << this << endl;
	}
	~ForwardList()
	{cout << "EDestructor:\t" << this << endl;}

	//ADDING ELEMENTS
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (true)
		{
			if (Temp->pNext == nullptr)break;
			else Temp = Temp->pNext;
		}
		Temp->pNext = New;
	}
	void push_in_temp(int Data, int n)
	{
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (n==1)
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
			n--;
		}
		Temp->Data = New->Data;
	}

	//METHODS
	void print()const
	{
		Element* Temp = Head;	//temp - итератор
		while (Temp != nullptr)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;	//Переход на следующий элемент
		}
	}
};

void main()
{
	setlocale(LC_ALL, "rus");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.push_back(8);
	list.print();
	list.push_in_temp(8, 2);
	list.print();
}