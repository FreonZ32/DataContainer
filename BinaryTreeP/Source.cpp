#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Tree
{
protected:
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
		bool is_leaf()const
		{
			return pLeft == pRight;
		}
		friend class UniqueTree;
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
	Tree(const Tree& other) :Tree()
	{
		*this = other;
		cout << "ЕCopyConstructor:\t" << this << endl;
	}
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
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int i : il)insert(i, Root);
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
		cout << endl;
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
	double Avg2()const
	{
		return (double)Sum2(Root) / Count2(Root);
	}
	void erase(int Data)
	{
	  erase(this->Root, Data);
	  Count--;
	  Sum -= Data;
	}
	void erase2(int Data)
	{
		erase2( Data,this->Root);
		Count--;
		Sum -= Data;
	}
	Element* CopyTree(Element* Root)
	{
		if (Root == nullptr)return nullptr;
		insert(Root->Data);
		Root->pLeft = CopyTree(Root->pLeft);
		Root->pRight = CopyTree(Root->pRight);
		return Root;
	}
	Tree& operator=(const Tree& other)
	{
		if (this == &other)return*this;
		this->Clean();
		CopyTree(other.Root);
		cout << "FCopyAssignment:\t" << this << endl;
	}
	int Count2()const
	{
		return Count2(Root);
	}
	int Sum2()const
	{
		return Sum2(Root);
	}
private:
	void insert(int Data, Element* Root)
	{
		cout << Data << endl;
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
	void Clean(Element* Root)
	{
		if (Root)
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
	void erase2(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		/*erase2(Data, Root->pLeft);
		erase2(Data, Root->pRight);*/
		if (Data == Root->Data)
		{
			if (Root->is_leaf())	//Root->is_leaf()
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (Count2(Root->pLeft) > Count2(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft));
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight));
				}
			}
		}
		else if (Data < Root->Data)
			erase2(Data,Root->pLeft);
		else
			erase2(Data, Root->pRight);
	}
	Element* erase(Element* Root, int Data)
	{
		if (Root == nullptr)return Root;
		if (Data == Root->Data)
		{
			Element* tmp;
			if (Root->pRight == nullptr)
				tmp = Root->pLeft;
			else 
			{
				Element* ptr = Root->pRight;
				if (ptr->pLeft == nullptr)
				{
					ptr->pLeft = Root->pLeft;
					tmp = ptr;
				}
				else
				{
					Element* pmin = ptr->pLeft;
					while (pmin->pLeft != nullptr)
					{
						ptr = pmin;
						pmin = ptr->pLeft;
					}
					ptr->pLeft = pmin->pRight;
					pmin->pLeft = Root->pLeft;
					pmin->pRight = Root->pRight;
					tmp = pmin;
				}
			}
			if (this->Root == Root) { delete Root; this->Root = tmp; }
			else delete Root;
			return tmp;
		}
		else if (Data < Root->Data)
			Root->pLeft = erase(Root->pLeft, Data);
		else
			Root->pRight = erase(Root->pRight, Data);
		return Root;
	}
	int Count2(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		return Count2(Root->pLeft) + Count2(Root->pRight) + 1;*/
		//return Root ? Count2(Root->pLeft) + Count2(Root->pRight) + 1 : 0;
		return !Root ? 0 : Count2(Root->pLeft) + Count2(Root->pRight) + 1;
	}
	int Sum2(Element* Root)const
	{
		return Root ? Sum2(Root->pLeft) + Sum2(Root->pRight) + Root->Data : 0;
	}
};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		//cout << Data << endl;
		if (this->Root == nullptr) { this->Root = new Element(Data); Count++; Sum += Data; }
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) { Root->pLeft = new Element(Data); Count++; Sum += Data; }		//Если есть место для добавления элемента - добавляем эл-т.
			else insert(Data, Root->pLeft);		//Иначе заново вызываем функцию.
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr) { Root->pRight = new Element(Data); Count++; Sum += Data; }
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data,Root);
	}
};

//#define BASECHECK

void main()
{
	setlocale(LC_ALL, "rus");
#ifdef BASECHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	UniqueTree treeU;
	for (int i = 0; i < n; i++)
	{
		treeU.insert(rand() % 100);
	}
	cout << "Не уникальное: \t";
	tree.print();
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.getCount() << endl;
	cout << "Сумма элементов: " << tree.getSum() << endl;
	cout << "Среднее арифметическое: " << tree.Avg() << endl;
	cout << endl;
	cout << "Уникальное: \t";
	treeU.print();
	cout << "Количество элементов в дереве: " << treeU.Count2() << endl;
	cout << "Сумма элементов: " << treeU.Sum2() << endl;
	cout << "Среднее арифметическое: " << treeU.Avg2() << endl;
	cout << endl;
#endif // BASECHECK

	Tree tree3 = { 50,25,75,16,32,64,80,8,11,48,77,85 };
	tree3.print();
	int data;
	cout << "Какой элемент удалить? "; cin >> data;
	tree3.erase2(data);
	tree3.print();
	cout << "Количество элементов в дереве: " << tree3.getCount() << endl;
	/*Tree tree2;
	tree2 = tree;
	tree2.print();
	cout << endl;
	Tree tree3(tree);
	tree3.print();*/

}