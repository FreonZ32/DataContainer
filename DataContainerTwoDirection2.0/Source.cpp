#include"Stdafx.h"

#include"ForwardList.h"
#include"ForwardList.cpp"

template<typename T>
void print_list(const ForwardList<T>& list)
{
	for (typename ForwardList<T>::ConstIterator it = list.cbegin(); it != list.cend(); ++it)
	{cout << *it << "\t";}
	cout << endl;
}

template<typename T>
void reverse_print_list(const ForwardList<T>& list)
{
	for (typename ForwardList<T>::ConstReverseIterator rit = list.crbegin(); rit != list.crend(); ++rit)
	{cout << *rit << "\t";}
	cout << endl;
}

//#define MODIFICATE
//#define ITERATOR_CHECK


void main()
{
	setlocale(LC_ALL, "rus");
#ifdef MODIFICATE
	int n;
	cout << "Введите количество элементов списка: "; cin >> n;
	ForwardList<int> list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.print_reverse();

	cout << endl;
	list.pop_front();
	list.print();
	//list.print_reverse();

	cout << endl;
	list.pop_back();
	list.print();
	//list.print_reverse();

	int index;
	int value;
	cout << "Введите индекс: "; cin >> index;
	cout << "Введите значение: "; cin >> value;
	list.insert(value, index);
	list.print();
	//list.print_reverse();

	cout << "Введите индекс: "; cin >> index;
	list.erase(index);
	list.print();
	//list.print_reverse();
#endif // MODIFICATE

#ifdef ITERATOR_CHECK
	ForwardList<int> list = { 3,5,8,13,21 };
	list.print();

	ForwardList list1;
	list1 = list;
	list.print();
	for (int i : list1)cout << i << "\t";
	cout << endl;

	for (ForwardList::ReverseIterator rit = list.rbegin(); rit != list.rend(); ++rit)cout << *rit << "\t";
	cout << endl;
#endif // ITERATOR_CHECK

	ForwardList<int> list = { 3,5,8,13,21 };
	print_list(list);
	cout << endl;
	reverse_print_list(list);
}