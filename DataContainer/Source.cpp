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
	int get_Data()const
	{return Data;}

	Element* get_pNext()const
	{return pNext;}

	void set_Data(int Data)
	{this->Data = Data;}

	void set_pNext(Element* pNext)
	{this->pNext = pNext;}
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
	Element* get_Head()const
	{return Head;}
	ForwardList()
	{
		this->Head = nullptr;	//Если голова указывает на 0 = список пуст
	cout << "Fconstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& ForwardList)
	{
		this->Head = new Element(ForwardList.Head->Data);
		for (Element* Temp = ForwardList.Head->pNext; Temp != nullptr; push_back(Temp->Data), Temp = Temp->pNext);
		{cout << "FCopyConstructor:\t" << this << endl; }
	}
	~ForwardList()
	{cout << "FDestructor:\t" << this << endl;}

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
		if (Temp->pNext == nullptr)cout << "Нельзя удалить единственный элемент массива!" << endl;
		else 
		{
			Head->~Element();
			Temp = Temp->pNext;
			Head = Temp;
		}
	}
	void pop_back()
	{
		Element* Temp = Head;
		if (Temp->pNext == nullptr)cout << "Нельзя удалить единственный элемент массива!" << endl;
		else
		{
			for (; Temp->pNext->pNext != nullptr; Temp = Temp->pNext);
			Temp->pNext->~Element();
			Temp->pNext = nullptr;
		}
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
			else {for (; n>1; Temp = Temp->pNext, n--); New->pNext = Temp->pNext; Temp->pNext = New;}
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

	//OPERATORS
	ForwardList& operator=(const ForwardList& other)
	{
		if (&this->Head == &other.Head)return* this;
		else 
		{
			this->Head = new Element(other.Head->Data);
			for (Element* Temp = other.Head->pNext; Temp != nullptr; push_back(Temp->Data), Temp = Temp->pNext);
			{cout << "Foperator=:\t" << this << endl; }
			return *this;
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

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList buffer(left);
	Element* Temp = buffer.get_Head();
	for (; Temp->get_pNext() != nullptr; Temp = Temp->get_pNext());
	Element* Temp2 = right.get_Head();
	for (; Temp2!= nullptr; Temp2 = Temp2->get_pNext(),Temp = Temp->get_pNext())
	{Temp->set_pNext(new Element(Temp2->get_Data()));}
	return buffer;
}

//#define WORK_WITH_ELEMENTS_CHECK

void main()
{
	setlocale(LC_ALL, "rus");
#ifdef WORK_WITH_ELEMENTS_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	cout << "Print of data base: " << endl;
	list.print();
	cout << endl;
	cout << "Puch element back: " << endl;
	list.push_back(8);
	list.print();
	cout << endl;
	cout << "Delete first elemeont of db: " << endl;
	list.pop_front();
	list.print();
	cout << endl;
	cout << "Delete last element of db: " << endl;
	list.pop_back();
	list.print();
	cout << endl;
	cout << "Enter insertion point(from 0 position)?: "; cin >> n;
	list.insert(100, n);
	list.print();
	cout << "Enter the deletion point(from 0 position)?: "; cin >> n;
	list.erase(n);
	list.print();
#endif // WORK_WITH_ELEMENTS_CHECK

	ForwardList list;
	for (int i = 0; i < 5; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();

	cout << endl;
	ForwardList list1(list);
	list1.print();

	cout << endl;
	ForwardList list2;
	list2 = list;
	list2.print();

	cout << endl;
	ForwardList list3;
	list3 = list + list;
	list3.print();
}