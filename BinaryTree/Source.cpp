#include<iostream>
#include<conio.h>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define DEBUG

class Element
{
	int Data;
	Element* pright;
	Element* pleft;
public:
	Element(int Data, Element* pright = nullptr, Element* pleft = nullptr) :Data(Data), pright(pright), pleft(pleft)
	{
#ifdef DEBUG
		cout << "Econstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Element()
	{
#ifdef DEBUG
		cout << "Edestructor:\t" << this << endl;
#endif // DEBUG
	}
	friend class BinaryTree;
};

class BinaryTree
{
	Element* Head;
public:
	BinaryTree()
	{
		Head = nullptr;
#ifdef DEBUG
		cout << "Bconstructor:\t" << this << endl;
#endif // DEBUG
	}
	BinaryTree(const initializer_list<int>& il) :BinaryTree()
	{
		for (int const*  it = il.begin(); it !=il.end() ; it++)
		{
			push_back(*it);
		}
	}
	~BinaryTree()
	{
#ifdef DEBUG
		cout << "Bdestructor:\t" << this << endl;
#endif // DEBUG
	}

	//METHODS
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		if (Head == nullptr) { Head = New; return; }
		if (Head->Data >= Data)New->pright = Head;
		else New->pleft = Head;
		New = Head;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data);
		Element* Temp = Head;
		if (Head == nullptr) { Head = New; return; }
		while (true)
		{
			if (Temp->Data >= Data) { if (Temp->pleft == nullptr)break; Temp = Temp->pleft; }
			else { if (Temp->pright == nullptr)break; Temp = Temp->pright; }
		}
		if (Temp->Data >= Data)Temp->pleft = New;
		else Temp->pright = New;
	}
	Element& found_Data(int Data)
	{
		Element* Temp = Head;
		if (Head->Data == Data)return *Temp;
		while (Temp->Data != Data)
		{
			if (Temp->Data >= Data)Temp = Temp->pright;
			else Temp = Temp->pleft;
		}
		return *Temp;
	}

	void print()
	{
		Element* Temp = Head;
		bool esc = true;
		while (esc)
		{
			cout << "\r" << Temp->Data << " " << "pRight: " << Temp->pright << " | " << "pLeft: " << Temp->pleft;
			char key;
			key = _getch();
			switch (key)
			{
			case 'r': if (Temp->pright == nullptr); else Temp = Temp->pright; break;
			case 'l': if (Temp->pleft == nullptr); else Temp = Temp->pleft; break;
			case 'h': Temp = Head; break;
			case 'e': esc = false; cout << endl; break;
			}
		}
	}
};




void main()
{
	setlocale(LC_ALL, "rus");
	BinaryTree Tree = { 5,3,4,1,6,2,10,21 };
	Tree.push_back(0);
	Tree.found_Data(0);
	Tree.print();
	
}