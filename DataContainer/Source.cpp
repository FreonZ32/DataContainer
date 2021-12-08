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
	ForwardList(Element* pNext)
	{
		this->Head = pNext;
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
		for (; Temp->pNext != nullptr; Temp = Temp->pNext);
		Temp->pNext = New;
	}
	void pop_front()
	{
		Element* Temp = Head;
		Head->~Element();
		Temp = Temp->pNext;
		Head = Temp;
	}
	void pop_back()
	{
		Element* Temp = Head;
		for (; Temp->pNext->pNext != nullptr; Temp = Temp->pNext);
		Temp->pNext->~Element();
		Temp->pNext = nullptr;
	}
	void insert(int Data, unsigned int n)
	{
		Element* Temp = Head;
		Element* New = new Element(Data);
		int i = 0;
		for (; Temp->pNext != nullptr; Temp = Temp->pNext, i++);
		if (n > i&&i!=0) { cout << "Место вставки выходит за пределы массива! " << endl; }
		else
		{
			Temp = Head;
			if (n == 0)push_front(Data);
			else if (n == i) { for (; Temp->pNext->pNext != nullptr; Temp = Temp->pNext); New->pNext = Temp->pNext;Temp->pNext = New;}
			else {for (; n; Temp = Temp->pNext, n--); New->pNext = Temp->pNext; Temp->pNext = New;}
		}
	}
	void erase(unsigned int n)
	{
		Element* Temp = Head;
		int i = 0;
		for (; Temp->pNext != nullptr; Temp = Temp->pNext, i++);
		if (i == 0) { cout << "Массив и так из 1ого элемента!" << endl; }
		else if (n > i) { cout << "Место удаления выходит за пределы массива! " << endl; }
		else 
		{
			Temp = Head;
			if (n == 0)pop_front();
			else if (n == i)pop_back();
			else { for (; n>1; Temp = Temp->pNext, n--); Element* New = Temp->pNext; Temp->pNext = Temp->pNext->pNext; New->~Element(); }
		}
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
	{list.push_front(rand() % 100);}

	list.print();
	cout << endl;
	list.push_back(8);
	list.print();
	cout << endl;
	list.pop_front();
	list.print();
	cout << endl;
	list.pop_back();
	list.print();
	cout << endl;
	cout << "Какой элемент (начиная с 0) вставить?: "; cin >> n;
	list.insert(100, n);
	list.print();
	cout << "Какой элемент (начиная с 0) удалить?: "; cin >> n;
	list.erase(n);
	list.print();
}