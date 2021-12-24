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

public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "Tconstructor:\t" << this << endl;
	}
	~Tree()
	{
		cout << "Tdestructor:\t" << this << endl;
	}

	void insert(int Data)
	{
		insert(Data, this->Root);
	}
	void print()const
	{
		print(this->Root);
		cout << endl;
	}
	int minValue()const
	{
		return minValue(this->Root);
	}
	int maxValue()const
	{
		return maxValue(this->Root);
	}

private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data) 
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);		//Если есть место для добавления элемента - добавляем эл-т.
			else insert(Data, Root->pLeft);		//Иначе заново вызываем функцию.
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
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
		if (Root->pLeft == nullptr){ return Root->Data; }
		minValue();
	}
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr) { return Root->Data; }
		minValue(Root->pRight);*/
		return Root->pRight == nullptr ? Root->Data : maxValue();
	}
	Element* operator&()
	{
		return Root;
	}
public:

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
}