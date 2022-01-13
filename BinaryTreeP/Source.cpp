#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

//#define DEBUG

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
		bool is_leaf()const
		{
			return pLeft == pRight;
		}
		friend class UniqueTree;
		friend class Tree;
	}*Root;	//������ ������
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
#ifdef DEBUG
		cout << "Tconstructor:\t" << this << endl;
#endif // DEBUG
	}
	Tree(const Tree& other) :Tree()
	{
		*this = other;
#ifdef DEBUG
		cout << "�CopyConstructor:\t" << this << endl;
#endif // DEBUG
	}
	Tree(Tree&& other) noexcept
	{
		this->Root = other.Root;
		this->Count = other.Count;
		this->Sum = other.Sum;
		other.Root = nullptr;
		other.Count = 0;
		other.Sum = 0;
#ifdef DEBUG
		cout << "MoveConstructor:\t" << this << endl;
#endif // DEBUG
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int i : il)insert(i, Root);
#ifdef DEBUG
		cout << "LISTConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Tree()
	{
		Clean();
#ifdef DEBUG
		cout << "Tdestructor:\t" << this << endl;
#endif // DEBUG
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
	void print2()const
	{
		print2(this->Root, 0);
		cout << endl;
	}
	int depth()const
	{
		return depth(this->Root);
	}
	void print3(int depth)const
	{
		print3(this->Root, depth);
	}
	void tree_print()
	{
		return tree_print(0);
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
		//cout << Data << endl;
		if (this->Root == nullptr) { this->Root = new Element(Data); Count++; Sum += Data; }
		if (Root == nullptr)return;
		if (Data < Root->Data) 
		{
			if (Root->pLeft == nullptr) { Root->pLeft = new Element(Data); Count++; Sum += Data;}		//���� ���� ����� ��� ���������� �������� - ��������� ��-�.
			else insert(Data, Root->pLeft);		//����� ������ �������� �������.
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
	void print2(Element* Root, int l)const
	{
		int i;
		if (Root != NULL)
		{
			print2(Root->pLeft, l + 3);
			for (i = 1; i <= l; i++)cout << " ";
			cout << Root->Data;
			if (l == 0)cout << "------------------";
			cout << endl;
			print2(Root->pRight, l + 3);
		}
	}
	int depth(Element* Root)const
	{
		if (Root == nullptr) return 0;
		else return
			depth(Root->pLeft) + 1 > depth(Root->pRight) + 1 ?
			depth(Root->pLeft) + 1 : depth(Root->pRight) + 1;
	}
	void print3(Element* Root, int depth)const
	{
		if (Root == nullptr||depth ==-1)return;
		if (depth == 1 && Root->pLeft == nullptr)cout << " " << "\t";
		print3(Root->pLeft, depth - 1);
		if (depth == 0)cout << Root->Data << "\t";
		if (depth == 1 && Root->pRight == nullptr)cout << " " << "\t";
		print3(Root->pRight, depth - 1);
	}
	void tree_print(int depth)
	{
		if (depth == this->depth())return;
		for (int i = 0; i < this->depth() - depth; i++)cout << "\t";
		print3(depth);
		for (int i = 0; i < this->depth() - depth; i++)cout << "\t";
		cout << endl;
		tree_print(depth + 1);
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
			if (Root->pLeft == nullptr) { Root->pLeft = new Element(Data); Count++; Sum += Data; }		//���� ���� ����� ��� ���������� �������� - ��������� ��-�.
			else insert(Data, Root->pLeft);		//����� ������ �������� �������.
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
	cout << "������� ���������� ���������: "; cin >> n;
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
	cout << "�� ����������: \t";
	tree.print2();
	cout << "����������� �������� � ������: " << tree.minValue() << endl;
	cout << "������������ �������� � ������: " << tree.maxValue() << endl;
	cout << "���������� ��������� � ������: " << tree.getCount() << endl;
	cout << "����� ���������: " << tree.getSum() << endl;
	cout << "������� ��������������: " << tree.Avg() << endl;
	cout << endl;
	cout << "����������: \t";
	treeU.print();
	cout << "���������� ��������� � ������: " << treeU.Count2() << endl;
	cout << "����� ���������: " << treeU.Sum2() << endl;
	cout << "������� ��������������: " << treeU.Avg2() << endl;
	cout << endl;
#endif // BASECHECK

	/*int n;
	cout << "������� ���������� ���������: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}*/
	Tree tree3 = { 50,25,75,16,32,29,64,80,8,18,48,77,85 };
	cout << "������� ������: " << tree3.depth() << endl;
	tree3.print2();
	tree3.tree_print();
	/*int data;
	cout << "����� ������� �������? "; cin >> data;
	tree3.erase2(data);
	tree3.print();
	cout << "���������� ��������� � ������: " << tree3.getCount() << endl;*/
	/*Tree tree2;
	tree2 = tree;
	tree2.print();
	cout << endl;
	Tree tree3(tree);
	tree3.print();*/

}