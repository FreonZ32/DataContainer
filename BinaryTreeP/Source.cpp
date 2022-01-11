#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "Econstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
	}*Root;	//Корень дерева
	int Count;
	int Sum;
public:
	Element* getRoot()const
	{
		return Root;
	}
	int getCount()const
	{
		return Count;
	}
	int getSum()const
	{
		return Sum;
	}
	Tree()
	{
		Root = nullptr;
		Count = 0;
		Sum = 0;
		cout << "Tconstructor:\t" << this << endl;
	}
	/*Tree(const Tree& other) :Tree()
	{
		*this = other;
		cout << "ЕCopyConstructor:\t" << this << endl;
	}*/
	Tree(Tree&& other) noexcept
	{
		this->Root = other.Root;
		this->Count = other.Count;
		this->Sum = other.Sum;
		other.Root = nullptr;
		other.Count = 0;
		other.Sum = 0;
		cout << "MoveConstructor:\t" << this << endl;
	}
	~Tree()
	{
		Clean();
		cout << "Tdestructor:\t" << this << endl;
	}

	void insert(int Data)
	{
		insert(Data, this->Root);
	}
	void print()const
	{
		print(this->Root);
	}
	void Clean()
	{
		Clean(this->Root);
	}
	int minValue()const
	{
		return minValue(this->Root);
	}
	int maxValue()const
	{
		return maxValue(this->Root);
	}
	double Avg()const
	{
		return double(Sum) / double(Count);
	}
	
	Element* CopyTree(Element* Root)
	{
		if (Root == nullptr)return nullptr;
		insert(Root->Data);
		Root->pLeft = CopyTree(Root->pLeft);
		Root->pRight = CopyTree(Root->pRight);
		return Root;
	}
	/*Tree& operator=(const Tree& other)
	{
		if (this == &other)return*this;
		
		cout << "FCopyAssignment:\t" << this << endl;
	}*/

private:
	void insert(int Data, Element* Root)
	{
		//cout << Data << endl;
		if (this->Root == nullptr) { this->Root = new Element(Data); Count++; Sum += Data; }
		if (Root == nullptr)return;
		if (Data < Root->Data) 
		{
			if (Root->pLeft == nullptr) { Root->pLeft = new Element(Data); Count++; Sum += Data;}		//Если есть место для добавления элемента - добавляем эл-т.
			else insert(Data, Root->pLeft);		//Иначе заново вызываем функцию.
		}
		else
		{
			if (Root->pRight == nullptr) { Root->pRight = new Element(Data); Count++; Sum += Data;}
			else insert(Data, Root->pRight);
		}
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
	int minValue(Element* Root)const
	{
		/*if (Root->pLeft == nullptr){ return Root->Data; }
		minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr) { return Root->Data; }
		minValue(Root->pRight);*/
		return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
	}
	void Clean(Element* Root) {
		if (Root != nullptr)
		{
			Clean(Root->pLeft);
			Clean(Root->pRight);
			delete Root;
		}
	}
	Element* operator&()
	{
		return Root;
	}
};



void main()
{
	setlocale(LC_ALL, "rus");
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.getCount() << endl;
	cout << "Сумма элементов: " << tree.getSum() << endl;
	cout << "Среднее арифметическое: " << tree.Avg() << endl;
	/*Tree tree2;
	tree2 = tree;
	tree2.print();*/
}