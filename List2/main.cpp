#include "List2.h"
#include "List2.cpp"

template<typename T> void print(const List<T>& list)
{
	for (typename List<T>::ConstIterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
}
template<typename T> void reverse_print(const List<T>& list)
{
	for (typename List<T>::ConstReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
}

//#define BASE_CHECK
//#define ITERRATORS_CHECK
void main()
{
	setlocale(0, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int value;
	int index;
	cout << "Введите индекс добавляемогоэлемента: "; cin >> index;
	cout << "Введите значение добавляемогоэлемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();

	int index2;
	cout << "Введите индекс удаляемого элемента: "; cin >> index2;
	list.erase(index2);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK
#ifdef ITERRATORS_CHECK
	List list = { 3,5,8,13,21 };
	//list.print();
	//list.reverse_print();

	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERRATORS_CHECK
	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;

	//for (int& i : list3) i *=10;

	//for (int i : list3)cout << i << tab; cout << endl;

	/*for (List::ReverseIterator it = list3.rbegin(); it != list3.rend(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;*/
	print(list3);
	reverse_print(list3);
	List<double> d_list_1 = { 2.7,3.14,8.2 };
	List<double> d_list_2 = { 7.3,5.4 };
	List<double> d_list_3 = d_list_1 + d_list_2;
	for (double i : d_list_1)cout << i << tab; cout << endl;
	for (double i : d_list_2)cout << i << tab; cout << endl;
	print(d_list_3);
	reverse_print(d_list_3);

	List<std::string> s_string_1 = { "Хорошо","живёт","на","свете" };
	List<std::string> s_string_2 = { "Винни","Пух" };
	List<std::string> s_string_3 = s_string_1 + s_string_2;
	for (List<std::string>::Iterator it = s_string_3.begin(); it != s_string_3.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	print(s_string_2);
	print(s_string_3);
	reverse_print(s_string_3);
}