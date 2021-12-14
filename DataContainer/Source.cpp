#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Element
{
	int Data;	//Значение элемента
	Element* pNext;
	static int count;	//Количество элементов
public:
	int get_Data()const
	{return Data;}

	Element* get_pNext()const
	{return pNext;}

	int get_count()const
	{return count;}

	void set_Data(int Data)
	{this->Data = Data;}

	void set_pNext(Element* pNext)
	{this->pNext = pNext;}
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "Econstructor:\t" << this << endl;
	}
	~Element()
	{
		this->count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0;

class ForwardList
{
	Element* Head;	//Указывает на начальный элемент списка
	size_t size;
public:
	Element* get_Head()const
	{return Head;}

	unsigned int get_size()const
	{return size;}

	void set_size(unsigned int size)
	{this->size = size;}

	ForwardList()
	{
		this->size = 0;
		this->Head->count = 0;
		this->Head = nullptr;	//Если голова указывает на 0 = список пуст
	cout << "Fconstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		for (const int*it = il.begin(); it !=il.end() ; it++)
		{push_back(*it);}
	}
	ForwardList(const ForwardList& other)
	{
		for (Element* Temp = other.Head; Temp != nullptr; push_back(Temp->Data), Temp = Temp->pNext);
		{cout << "FCopyConstructor:\t" << this << endl; }
	}
	ForwardList(ForwardList&& other) noexcept
	{
		*this = std::move(other);
		other.Head = nullptr;
		other.size = 0;
		{cout << "FMoveConstructor:\t" << this << endl; }
	}

	~ForwardList()
	{
		cout << size << endl;
		while (Head)pop_front();
		cout << "FDestructor:\t" << this << endl;
	}

	//ADDING ELEMENTS
	void push_front(int Data)
	{
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head; 
		for (; Temp->pNext != nullptr; Temp = Temp->pNext);
		Temp->pNext = new Element(Data);
		size++;
	}
	void pop_front()
	{
		Element* Temp = Head;
		Head = Head->pNext;
		delete Temp;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		if (Temp->pNext == nullptr)cout << "Нельзя удалить единственный элемент массива!" << endl;
		else
		{
			for (; Temp->pNext->pNext != nullptr; Temp = Temp->pNext);
			delete Temp->pNext;
			Temp->pNext = nullptr;
		}
		size--;
	}
	void insert(int Data, unsigned int n)
	{
		if (n > Head->count) {cout << "Выход за пределы списка! " << endl; return;}
		if (n == 0 || Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		for (int i = 0; i < n - 1; i++)Temp = Temp->pNext;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	void erase(unsigned int n)
	{
		if (n > Head->count-1) { cout << "Выход за пределы списка! " << endl; return; }
		if (Head == nullptr)return;
		if (n==0)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < n - 1; i++)Temp = Temp->pNext;
		Element* New = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete New;
		size--;
	}

	//OPERATORS
	ForwardList& operator=(const ForwardList& other)
	{
		while (Head)pop_front();
		if (this == &other)return* this;
		for (Element* Temp = other.Head; Temp != nullptr; push_back(Temp->Data), Temp = Temp->pNext);
		cout << "Foperator=:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other) noexcept
	{
		this->size = other.size;
		this->Head = other.Head;
		other.Head = nullptr;
		other.size = 0;
		{cout << "FMoveOperatort= :\t" << this << endl; }
		return *this;
	}

	//METHODS
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
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
	buffer.set_size(left.get_size() + right.get_size());
	return buffer;
}

//#define WORK_WITH_ELEMENTS_CHECK
//#define CONSTRUCTORSandOPERATORS

void main()
{
	setlocale(LC_ALL, "rus");
#ifdef WORK_WITH_ELEMENTS_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)list.push_front(rand() % 100);
	cout << "Print of data base: " << endl;
	list.print();
	cout << endl;
	cout << "Puch element back: " << endl;
	list.push_back(123);
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

#ifdef CONSTRUCTORSandOPERATORS
	ForwardList list;
	for (int i = 0; i < 5; i++)
	{list.push_front(rand() % 100);}
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

	cout << list.get_Head() << endl;
	cout << list1.get_Head() << endl;
	cout << list2.get_Head() << endl;
	cout << list3.get_Head() << endl;

#endif // CONSTRUCTORSandOPERATORS

	/*int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		cout << arr[i] << "\t";
	}*/

	ForwardList list = { 3,5,8,13,21 };
	list.print();

}